// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsCVars_Manager_Input.h"

TAutoConsoleVariable<int32> CsCVarLogInputRaw(
	TEXT("log.input.raw"),
	0,
	TEXT("Log Input Raw"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRawAction(
	TEXT("log.input.raw.action"),
	0,
	TEXT("Log Input Raw Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRawAxis(
	TEXT("log.input.raw.axis"),
	0,
	TEXT("Log Input Raw Axis"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInput(
	TEXT("log.input"),
	0,
	TEXT("Log Input"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAction(
	TEXT("log.input.action"),
	0,
	TEXT("Log Input Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAxis(
	TEXT("log.input.axis"),
	0,
	TEXT("Log Input Axis"),
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

TAutoConsoleVariable<int32> CsCVarLogInputRotation(
	TEXT("log.input.rotation"),
	0,
	TEXT("Log Input Rotation"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputGameEvent(
	TEXT("log.input.gameevent"),
	0,
	TEXT("Log Input Game Event"),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{

	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRaw);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRawAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRawAxis);

	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInput);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputAxis);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputTrigger);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputLocation);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRotation);

	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputGameEvent);

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputRaw, CsCVarLogInputRaw);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputRawAction, CsCVarLogInputRawAction);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputRawAxis, CsCVarLogInputRawAxis);

		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInput, CsCVarLogInput);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputAction, CsCVarLogInputAction);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputAxis, CsCVarLogInputAxis);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputTrigger, CsCVarLogInputTrigger);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputLocation, CsCVarLogInputLocation);
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputRotation, CsCVarLogInputRotation);

		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogInputGameEvent, CsCVarLogInputGameEvent);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsScopedGroup, ManagerInput, "Manager Input");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(FCsScopedGroupMap, ManagerInput, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup