#include "pch-il2cpp.h"
#include "esp.hpp"
#include "DirectX.h"
#include "utility.h"
#include "game.h"
#include "gui-helpers.hpp"

drawing_t* Esp::s_Instance = new drawing_t();
ImGuiWindow* CurrentWindow = nullptr;

static void RenderText(const char* text, const ImVec2& pos, const ImVec4& color, const bool outlined = true, const bool centered = true)
{
	if (!text) return;
	ImVec2 ImScreen = pos;
	if (centered)
	{
		auto size = ImGui::CalcTextSize(text);
		ImScreen.x -= size.x * 0.5f;
		ImScreen.y -= size.y;
	}

	if (outlined)
	{
		CurrentWindow->DrawList->AddText(nullptr, 0.f,
			ImScreen + 0.5f * State.dpiScale,
			ImGui::GetColorU32(IM_COL32_BLACK), text);
	}

	CurrentWindow->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text);
}

static void RenderLine(const ImVec2& start, const ImVec2& end, const ImVec4& color, bool shadow = false) noexcept
{
	if (shadow)
	{
		CurrentWindow->DrawList->AddLine(
			start + 0.5f * State.dpiScale,
			end + 0.5f * State.dpiScale,
			ImGui::GetColorU32(color) & IM_COL32_A_MASK, 1.0f * State.dpiScale);
	}

	CurrentWindow->DrawList->AddLine(start, end, ImGui::GetColorU32(color), 1.0f * State.dpiScale);
}

static void RenderBox(const ImVec2& top, const ImVec2& bottom, const float height, const float width, const ImVec4& color, const bool wantsShadow = true)
{
	const ImVec2 points[] = {
		bottom, { bottom.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) },
		{ bottom.x - 0.5f * State.dpiScale, bottom.y }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), bottom.y },

		{ top.x + 0.5f * State.dpiScale, bottom.y }, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), bottom.y },
		{ top.x, bottom.y }, { top.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) },

		{ bottom.x, top.y }, { bottom.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) },
		{ bottom.x - 0.5f * State.dpiScale, top.y }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), top.y },

		top, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), top.y },
		{ top.x, top.y + 0.5f * State.dpiScale }, { top.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) }
	};

	if (wantsShadow) {
		const ImVec4& shadowColor = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(color) & IM_COL32_A_MASK);
		for (size_t i = 0; i < std::size(points); i += 2) {
			RenderLine(points[i] + 0.5f * State.dpiScale, points[i + 1] + 0.5f * State.dpiScale, shadowColor, false);
		}
	}
	for (size_t i = 0; i < std::size(points); i += 2) {
		RenderLine(points[i], points[i + 1], color, false);
	}
}

void Esp::Render()
{
	extern Color GetRoleColor(GameData_PlayerInfo*);

	CurrentWindow = ImGui::GetCurrentWindow();

	if (!(State.ShowEsp_Box || State.ShowEsp_Distance || State.ShowEsp_Tracers)) {
		// ignore
		return;
	}

	Vector2 localPos = PlayerControl_GetTruePosition(*Game::pLocalPlayer, nullptr);
	ImVec2 localScreenPosition = WorldToScreen(localPos);

	for (auto& it : GetAllPlayerControl()) {
		if (const auto& player = PlayerSelection(it).validate();
			player.has_value()						//Verify PlayerControl hasn't been destroyed (happens when disconnected)
			&& !player.is_Disconnected()		//Sanity check, shouldn't ever be true
			&& !player.is_LocalPlayer()			//Don't highlight yourself, you're ugly
			&& (!player.get_PlayerData()->fields.IsDead || State.ShowEsp_Ghosts)) {
			const Vector2& playerPos = PlayerControl_GetTruePosition(player.get_PlayerControl(), nullptr);
			if (!IsWithinScreenBounds(playerPos))
				continue;

			ImVec4 Color;
			std::string Name;
			if (auto outfit = GetPlayerOutfit(player.get_PlayerData())) {
				Color = State.ShowEsp_RoleBased == false ? AmongUsColorToImVec4(GetPlayerColor(outfit->fields.ColorId))
					: AmongUsColorToImVec4(GetRoleColor(player.get_PlayerData()));
				Name = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
			}
			else {
				Color = State.ShowEsp_RoleBased == false ? ImVec4(0.f, 0.f, 0.f, 1.f)
					: AmongUsColorToImVec4(GetRoleColor(player.get_PlayerData()));
				Name = "<Unknown>";
			}
			const auto& Position = WorldToScreen(playerPos);

			/////////////////////////////////
			//// Box ////////////////////////
			/////////////////////////////////
			if (State.ShowEsp_Box) {
				float width = GetScaleFromValue(35.0f);
				float height = GetScaleFromValue(120.0f);

				ImVec2 top{ Position.x + width, Position.y };
				ImVec2 bottom{ Position.x - width, Position.y - height };

				RenderBox(top, bottom, height, width, Color);
			}
			/////////////////////////////////
			//// Distance ///////////////////
			/////////////////////////////////
			if (State.ShowEsp_Distance) {
				const ImVec2 position{ Position.x, Position.y + 15.0f * State.dpiScale };

				auto Distance = Vector2_Distance(localPos, playerPos, nullptr);
				char distance[32];
				sprintf_s(distance, "[%.0fm]", Distance);

				RenderText(distance, position, Color);
			}
			/////////////////////////////////
			//// Tracers ////////////////////
			/////////////////////////////////
			if (State.ShowEsp_Tracers) {
				RenderLine(localScreenPosition, Position, Color, true);
			}
		}
	}
}
