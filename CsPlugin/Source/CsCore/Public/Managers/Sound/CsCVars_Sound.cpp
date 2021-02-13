// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/CsCVars_Sound.h"

TAutoConsoleVariable<int32> CsCVarLogSoundPooledChange(
	TEXT("log.sound.pooled.change"),
	0,
	TEXT("Log Sound Pooled Changes (Preserved between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeSet(
	TEXT("log.sound.pooled.change.set"),
	0,
	TEXT("Log Sound Pooled Changes Set (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeClear(
	TEXT("log.sound.pooled.change.clear"),
	0,
	TEXT("Log Sound Pooled Changes Clear (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeCounter(
	TEXT("log.sound.pooled.change.counter"),
	0,
	TEXT("Log Sound Pooled Changes Counter (Between Allocate and Deallocate)."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSoundPooledChange, "Log Sound Pooled Changes (Preserved between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSoundPooledChangeSet, "Log Sound Pooled Changes Set (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSoundPooledChangeClear, "Log Sound Pooled Changes Clear (Between Allocate and Deallocate)");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogSoundPooledChangeCounter, "Log Sound Pooled Changes Counter (Between Allocate and Deallocate)");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSoundPooledChange, CsCVarLogSoundPooledChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSoundPooledChangeSet, CsCVarLogSoundPooledChangeSet);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSoundPooledChangeClear, CsCVarLogSoundPooledChangeClear);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogSoundPooledChangeCounter, CsCVarLogSoundPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(Sound, "Sound");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(Sound, CsCVarLogSoundScopedTimer);
	}
}

#pragma endregion ScopedGroup