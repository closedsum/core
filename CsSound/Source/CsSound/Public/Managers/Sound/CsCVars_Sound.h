// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChange;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeSet;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeClear;
extern CSSOUND_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeCounter;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSSOUND_API const Type LogSoundPooledChange;
	extern CSSOUND_API const Type LogSoundPooledChangeSet;
	extern CSSOUND_API const Type LogSoundPooledChangeClear;
	extern CSSOUND_API const Type LogSoundPooledChangeCounter;

	namespace Map
	{
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChange);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChangeSet);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChangeClear);
		extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSSOUND_API const Type Sound;

	namespace Map
	{
		//extern CSSOUND_API CS_DECLARE_ADD_TO_CVAR_MAP(Sound);
	}
}

#pragma endregion ScopedGroup