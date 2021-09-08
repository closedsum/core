// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSPLAYBACK_API TAutoConsoleVariable<int32> CsCVarLogManagerPlaybackRecordEvent;
extern CSPLAYBACK_API TAutoConsoleVariable<int32> CsCVarLogManagerPlaybackPlaybackUpdate;
extern CSPLAYBACK_API TAutoConsoleVariable<int32> CsCVarLogManagerPlaybackPlaybackEvent;

namespace NCsCVarLog
{
	extern CSPLAYBACK_API const Type LogManagerPlaybackRecordEvent;
	extern CSPLAYBACK_API const Type LogManagerPlaybackPlaybackUpdate;
	extern CSPLAYBACK_API const Type LogManagerPlaybackPlaybackEvent;

	namespace Map
	{
		extern CSPLAYBACK_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerPlaybackRecordEvent);
		extern CSPLAYBACK_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerPlaybackPlaybackUpdate);
		extern CSPLAYBACK_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerPlaybackPlaybackEvent);
	}
}