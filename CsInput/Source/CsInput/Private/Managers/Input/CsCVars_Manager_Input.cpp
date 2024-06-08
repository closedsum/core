// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/CsCVars_Manager_Input.h"

TAutoConsoleVariable<int32> CsCVarLogInput(
	TEXT("log.input"),
	0,
	TEXT("Log Input"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputEventChange(
	TEXT("log.input.event.change"),
	0,
	TEXT("Log Input Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAction(
	TEXT("log.input.action"),
	0,
	TEXT("Log Input Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputActionEventChange(
	TEXT("log.input.action.event.change"),
	0,
	TEXT("Log Input Action Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAxis(
	TEXT("log.input.axis"),
	0,
	TEXT("Log Input Axis"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAxisEventChange(
	TEXT("log.input.axis.event.change"),
	0,
	TEXT("Log Input Axis Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputTrigger(
	TEXT("log.input.trigger"),
	0,
	TEXT("Log Input Trigger"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputLocation(
	TEXT("log.input.location"),
	0,
	TEXT("Log Input Locaton"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputLocationEventChange(
	TEXT("log.input.location.event.change"),
	0,
	TEXT("Log Input Locaton Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRotation(
	TEXT("log.input.rotation"),
	0,
	TEXT("Log Input Rotation"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputMouseAction(
	TEXT("log.input.mouse.action"),
	0,
	TEXT("Log Input Mouse Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputMouseActionEventChange(
	TEXT("log.input.mouse.action.event.change"),
	0,
	TEXT("Log Input Mouse Action Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputMouseLocation(
	TEXT("log.input.mouse.location"),
	0,
	TEXT("Log Input Mouse Location"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputMouseLocationEventChange(
	TEXT("log.input.mouse.location.event.change"),
	0,
	TEXT("Log Input Mouse Location Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputTouchAction(
	TEXT("log.input.touch.action"),
	0,
	TEXT("Log Input Touch Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputTouchActionEventChange(
	TEXT("log.input.touch.action.event.change"),
	0,
	TEXT("Log Input Touch Action Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputTouchLocation(
	TEXT("log.input.touch.location"),
	0,
	TEXT("Log Input Touch Location"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputTouchLocationEventChange(
	TEXT("log.input.touch.location.event.change"),
	0,
	TEXT("Log Input Touch Location Event Change"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputFrame(
	TEXT("log.input.frame"),
	0,
	TEXT("Log Input Frame"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputGameEvent(
	TEXT("log.input.gameevent"),
	0,
	TEXT("Log Input Game Event"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputGameEventDefinition(
	TEXT("log.input.gameevent.definition"),
	0,
	TEXT("Log Input Game Event Definition"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputActiveMode(
	TEXT("log.input.activemode"),
	0,
	TEXT("Log Input - ActiveInputMode"),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInput);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputEventChange);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputAction);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputActionEventChange);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputAxis);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputAxisEventChange);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputTrigger);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputLocation);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputLocationEventChange);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputRotation);

	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputMouseAction);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputMouseActionEventChange);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputMouseLocation);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputMouseLocationEventChange);

	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputTouchAction);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputTouchActionEventChange);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputTouchLocation);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputTouchLocationEventChange);

	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputFrame);

	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputGameEvent);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputGameEventDefinition);

	CSINPUT_API CS_CREATE_ENUM_STRUCT(LogInputActiveMode);

	namespace Map
	{
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInput, CsCVarLogInput);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputEventChange, CsCVarLogInputEventChange);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputAction, CsCVarLogInputAction);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputActionEventChange, CsCVarLogInputActionEventChange);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputAxis, CsCVarLogInputAxis);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputAxisEventChange, CsCVarLogInputAxisEventChange);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputTrigger, CsCVarLogInputTrigger);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputLocation, CsCVarLogInputLocation);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputLocationEventChange, CsCVarLogInputLocationEventChange);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputRotation, CsCVarLogInputRotation);

		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputMouseAction, CsCVarLogInputMouseAction);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputMouseActionEventChange, CsCVarLogInputMouseActionEventChange);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputMouseLocation, CsCVarLogInputMouseLocation);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputMouseLocationEventChange, CsCVarLogInputMouseLocationEventChange);

		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputTouchAction, CsCVarLogInputTouchAction);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputTouchActionEventChange, CsCVarLogInputTouchActionEventChange);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputTouchLocation, CsCVarLogInputTouchLocation);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputTouchLocationEventChange, CsCVarLogInputTouchLocationEventChange);

		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputFrame, CsCVarLogInputFrame);

		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputGameEvent, CsCVarLogInputGameEvent);
		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputGameEventDefinition, CsCVarLogInputGameEventDefinition);

		CSINPUT_API CS_ADD_TO_CVAR_MAP(LogInputActiveMode, CsCVarLogInputActiveMode);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSINPUT_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerInput, "Manager Input");

	namespace Map
	{
		//extern CSINPUT_API CS_ADD_TO_CVAR_MAP(ManagerInput, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup