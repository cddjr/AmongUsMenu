#include "pch-il2cpp.h"
#include "_events.h"
#include "state.hpp"

std::chrono::system_clock::duration BaseEvent::GetTimeAgo() const {
	if (State.InMeeting && !countDuringMeeting) {
		return State.MeetingStart - this->timestamp;
	}
	return __super::GetTimeAgo();
}