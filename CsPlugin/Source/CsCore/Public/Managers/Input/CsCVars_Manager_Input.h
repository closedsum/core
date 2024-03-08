// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInput;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputEventChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputActionEventChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAxis;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAxisEventChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTrigger;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputLocation;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputLocationEventChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRotation;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputMouseAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputMouseActionEventChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputMouseLocation;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputMouseLocationEventChange;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTouchAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTouchActionEventChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTouchLocation;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTouchLocationEventChange;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputFrame;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputGameEvent;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputGameEventDefinition;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputActiveMode;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	// Input
	extern CSCORE_API const Type LogInput;
	extern CSCORE_API const Type LogInputEventChange;
	extern CSCORE_API const Type LogInputAction;
	extern CSCORE_API const Type LogInputActionEventChange;
	extern CSCORE_API const Type LogInputAxis;
	extern CSCORE_API const Type LogInputAxisEventChange;
	extern CSCORE_API const Type LogInputTrigger;
	extern CSCORE_API const Type LogInputLocation;
	extern CSCORE_API const Type LogInputLocationEventChange;
	extern CSCORE_API const Type LogInputRotation;

	extern CSCORE_API const Type LogInputMouseAction;
	extern CSCORE_API const Type LogInputMouseActionEventChange;
	extern CSCORE_API const Type LogInputMouseLocation;
	extern CSCORE_API const Type LogInputMouseLocationEventChange;

	extern CSCORE_API const Type LogInputTouchAction;
	extern CSCORE_API const Type LogInputTouchActionEventChange;
	extern CSCORE_API const Type LogInputTouchLocation;
	extern CSCORE_API const Type LogInputTouchLocationEventChange;

	extern CSCORE_API const Type LogInputFrame;

	extern CSCORE_API const Type LogInputGameEvent;
	extern CSCORE_API const Type LogInputGameEventDefinition;

	extern CSCORE_API const Type LogInputActiveMode;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInput);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputEventChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAction);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputActionEventChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAxis);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAxisEventChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTrigger);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputLocation);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputLocationEventChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputRotation);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseAction);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseActionEventChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseLocation);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseLocationEventChange);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchAction);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchActionEventChange);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchLocation);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchLocationEventChange);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputFrame);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputGameEvent);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputGameEventDefinition);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputActiveMode);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerInput;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerInput);
	}
}

#pragma endregion ScopedGroup