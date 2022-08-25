#include "pch-il2cpp.h"
#include "_events.h"
#include "utility.h"

TaskCompletedEvent::TaskCompletedEvent(const EVENT_PLAYER& source, const std::optional<TaskTypes__Enum>& taskType, const Vector2& position) : BaseEvent(source, EVENT_TYPES::EVENT_TASK) {
	this->taskType = taskType;
	this->position = position;
	this->systemType = GetSystemTypes(position);
	this->countDuringMeeting = false;
}

void TaskCompletedEvent::Output() {
	ImGui::TextColored(AmongUsColorToImVec4(GetPlayerColor(source.colorId)), source.playerName.c_str());
	ImGui::SameLine();
	ImGui::Text("> %s (%s)", (taskType.has_value()) ? TranslateTaskTypes(*taskType) : "UNKOWN" , TranslateSystemTypes(systemType));
	ImGui::SameLine();
	ImGui::Text("[%s ago]", std::format("{:%OM:%OS}", GetTimeAgo()).c_str());
}

void TaskCompletedEvent::ColoredEventOutput() {
	ImGui::Text("[");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "TASK");
	ImGui::SameLine();
	ImGui::Text("]");
}