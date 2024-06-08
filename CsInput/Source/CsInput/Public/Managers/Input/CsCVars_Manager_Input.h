// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInput;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputEventChange;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputAction;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputActionEventChange;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputAxis;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputAxisEventChange;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputTrigger;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputLocation;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputLocationEventChange;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputRotation;

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputMouseAction;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputMouseActionEventChange;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputMouseLocation;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputMouseLocationEventChange;

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputTouchAction;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputTouchActionEventChange;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputTouchLocation;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputTouchLocationEventChange;

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputFrame;

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputGameEvent;
extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputGameEventDefinition;

extern CSINPUT_API TAutoConsoleVariable<int32> CsCVarLogInputActiveMode;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	// Input
	extern CSINPUT_API const Type LogInput;
	extern CSINPUT_API const Type LogInputEventChange;
	extern CSINPUT_API const Type LogInputAction;
	extern CSINPUT_API const Type LogInputActionEventChange;
	extern CSINPUT_API const Type LogInputAxis;
	extern CSINPUT_API const Type LogInputAxisEventChange;
	extern CSINPUT_API const Type LogInputTrigger;
	extern CSINPUT_API const Type LogInputLocation;
	extern CSINPUT_API const Type LogInputLocationEventChange;
	extern CSINPUT_API const Type LogInputRotation;

	extern CSINPUT_API const Type LogInputMouseAction;
	extern CSINPUT_API const Type LogInputMouseActionEventChange;
	extern CSINPUT_API const Type LogInputMouseLocation;
	extern CSINPUT_API const Type LogInputMouseLocationEventChange;

	extern CSINPUT_API const Type LogInputTouchAction;
	extern CSINPUT_API const Type LogInputTouchActionEventChange;
	extern CSINPUT_API const Type LogInputTouchLocation;
	extern CSINPUT_API const Type LogInputTouchLocationEventChange;

	extern CSINPUT_API const Type LogInputFrame;

	extern CSINPUT_API const Type LogInputGameEvent;
	extern CSINPUT_API const Type LogInputGameEventDefinition;

	extern CSINPUT_API const Type LogInputActiveMode;

	namespace Map
	{
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInput);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputEventChange);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAction);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputActionEventChange);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAxis);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAxisEventChange);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTrigger);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputLocation);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputLocationEventChange);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputRotation);

		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseAction);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseActionEventChange);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseLocation);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputMouseLocationEventChange);

		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchAction);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchActionEventChange);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchLocation);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTouchLocationEventChange);

		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputFrame);

		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputGameEvent);
		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputGameEventDefinition);

		extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputActiveMode);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSINPUT_API const Type ManagerInput;

	namespace Map
	{
		//extern CSINPUT_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerInput);
	}
}

#pragma endregion ScopedGroup