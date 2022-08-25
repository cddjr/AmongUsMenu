#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

ProtectPlayerEvent::ProtectPlayerEvent(const EVENT_PLAYER& source, const EVENT_PLAYER& target) : BaseEvent(source, EVENT_TYPES::EVENT_PROTECTPLAYER) {
	this->target = target;
	this->countDuringMeeting = false;
}

void ProtectPlayerEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text(">");
	ImGui::SameLine();
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(target.colorId)), target.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", GetTimeAgo()).c_str());
}

void ProtectPlayerEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.1f, 0.75f, 0.75f, 1.f), "PROTECT");
	ImGui::SameLine();
	ImGui::Text("]");
}