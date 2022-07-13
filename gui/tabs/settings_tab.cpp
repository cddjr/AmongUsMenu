#include "pch-il2cpp.h"
#include "settings_tab.h"
#include "utility.h"
#include "gui-helpers.hpp"
#include "state.hpp"
#include "game.h"
#include "achievements.hpp"
#include "DirectX.h"
#include "imgui/imgui_impl_win32.h" // ImGui_ImplWin32_GetDpiScaleForHwnd
#include "theme.hpp" // ApplyTheme

namespace SettingsTab {
	void Render() {
		if (ImGui::BeginTabItem("Settings")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			ImGui::Text("Show/Hide Menu Keybind:");
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Menu)) {
				State.Save();
			}

			ImGui::Text("Show/Hide Console Keybind:");
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Console)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale); 
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			if (ImGui::Checkbox("Adjust by DPI", &State.AdjustByDPI)) {
				if (!State.AdjustByDPI) {
					State.dpiScale = 1.0f;
				}
				else {
					State.dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(DirectX::window);
				}
				State.dpiChanged = true;
				State.Save();
			}
#ifdef _DEBUG
			static const std::vector<const char*> DPI_SCALING_LEVEL = { "100%", "125%", "150%", "175%", "200%", "225%", "250%", "275%", "300%" };
			ImGui::SameLine();
			int scaleIndex =(int(std::clamp(State.dpiScale, 1.0f, 3.0f) * 100.0f) - 100) / 25;
			if (CustomListBoxInt("Scaling Level", &scaleIndex, DPI_SCALING_LEVEL, 100 * State.dpiScale)) {
				State.dpiScale = (scaleIndex * 25 + 100) / 100.0f;
				State.dpiChanged = true;
			}
#endif
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

#ifdef _DEBUG
			if (ImGui::Checkbox("Show Debug Tab", &State.showDebugTab)) {
				State.Save();
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#endif
			//Change this to in game only once account is overridden
			{
				constexpr size_t kMaxLen = 10;
				static auto callback = [](ImGuiInputTextCallbackData* data) -> int {
					if (data->BufTextLen <= kMaxLen) return 0;
					// for CJK characters
					if (auto name = convert_to_string({ data->Buf, (size_t)data->BufTextLen });
						app::String_get_Length(name, nullptr) > kMaxLen) {
						data->BufTextLen = convert_from_string(app::String_Substring_1(name, 0, kMaxLen, nullptr)).length();
						data->Buf[data->BufTextLen] = 0;
						data->BufDirty = true;
					}
					return 0;
				};
				std::string userName;
				synchronized(State.nameMutex) {
					userName = State.userName;
				}
				userName.reserve(kMaxLen * 4);
				if (ImGui::InputText("PlayerName", userName.data(), userName.capacity() + 1, ImGuiInputTextFlags_CallbackAlways, callback)) {
					userName.resize(strlen(userName.data()));
					synchronized(State.nameMutex) {
						State.userName = std::move(userName);
					}
				}
				EnableImeIfNeeded();
			}

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			if (ImGui::Button("Unlock all Steam achievements"))
			{
				for (const char* achievement : steamAchievements)
				{
					Game::SteamUserStats_SetAchievement(convert_to_string(std::string(achievement)));
				}
				Game::SteamUserStats_StoreStats();
			}

			ImGui::EndTabItem();
		}
	}
}