// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeSet;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeClear;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogSoundPooledChangeCounter;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogSoundPooledChange;
	extern CSCORE_API const Type LogSoundPooledChangeSet;
	extern CSCORE_API const Type LogSoundPooledChangeClear;
	extern CSCORE_API const Type LogSoundPooledChangeCounter;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChangeSet);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChangeClear);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogSoundPooledChangeCounter);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	//extern CSCORE_API const Type Sound;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(Sound);
	}
}

#pragma endregion ScopedGroup