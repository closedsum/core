// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInput);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputEventChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputActionEventChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputAxis);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputAxisEventChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputTrigger);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputLocation);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputLocationEventChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputRotation);

	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputMouseAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputMouseActionEventChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputMouseLocation);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputMouseLocationEventChange);

	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputTouchAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputTouchActionEventChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputTouchLocation);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputTouchLocationEventChange);

	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputFrame);

	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputGameEvent);
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputGameEventDefinition);

	CSCORE_API CS_CREATE_ENUM_STRUCT(LogInputActiveMode);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInput, CsCVarLogInput);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputEventChange, CsCVarLogInputEventChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputAction, CsCVarLogInputAction);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputActionEventChange, CsCVarLogInputActionEventChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputAxis, CsCVarLogInputAxis);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputAxisEventChange, CsCVarLogInputAxisEventChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputTrigger, CsCVarLogInputTrigger);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputLocation, CsCVarLogInputLocation);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputLocationEventChange, CsCVarLogInputLocationEventChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputRotation, CsCVarLogInputRotation);

		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputMouseAction, CsCVarLogInputMouseAction);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputMouseActionEventChange, CsCVarLogInputMouseActionEventChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputMouseLocation, CsCVarLogInputMouseLocation);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputMouseLocationEventChange, CsCVarLogInputMouseLocationEventChange);

		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputTouchAction, CsCVarLogInputTouchAction);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputTouchActionEventChange, CsCVarLogInputTouchActionEventChange);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputTouchLocation, CsCVarLogInputTouchLocation);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputTouchLocationEventChange, CsCVarLogInputTouchLocationEventChange);

		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputFrame, CsCVarLogInputFrame);

		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputGameEvent, CsCVarLogInputGameEvent);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputGameEventDefinition, CsCVarLogInputGameEventDefinition);

		CSCORE_API CS_ADD_TO_CVAR_MAP(LogInputActiveMode, CsCVarLogInputActiveMode);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerInput, "Manager Input");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(ManagerInput, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup