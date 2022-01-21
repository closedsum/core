// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Playback/CsCVars_Manager_Playback.h"

TAutoConsoleVariable<int32> CsCVarLogManagerPlaybackRecordEvent(
	TEXT("log.manager.playback.record.event"),
	0,
	TEXT("Log Manager Playback Record Event."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogManagerPlaybackPlaybackUpdate(
	TEXT("log.manager.playback.playback.update"),
	0,
	TEXT("Log Manager Playback Playback Update."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogManagerPlaybackPlaybackEvent(
	TEXT("log.manager.playback.playback.event"),
	0,
	TEXT("Log Manager Playback Playback Event."),
	ECVF_SetByConsole | ECVF_SetByCode
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSPLAYBACK_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerPlaybackRecordEvent, "Log Manager Playback Record Event");
	CSPLAYBACK_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerPlaybackPlaybackUpdate, "Log Manager Playback Playback Update");
	CSPLAYBACK_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerPlaybackPlaybackEvent, "Log Manager Playback Playback Event");

	namespace Map
	{
		CSPLAYBACK_API CS_ADD_TO_CVAR_MAP(LogManagerPlaybackRecordEvent, CsCVarLogManagerPlaybackRecordEvent);
		CSPLAYBACK_API CS_ADD_TO_CVAR_MAP(LogManagerPlaybackPlaybackUpdate, CsCVarLogManagerPlaybackPlaybackUpdate);
		CSPLAYBACK_API CS_ADD_TO_CVAR_MAP(LogManagerPlaybackPlaybackEvent, CsCVarLogManagerPlaybackPlaybackEvent);
	}
}

#pragma endregion CVarLog