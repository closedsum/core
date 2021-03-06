// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsCVars_Manager_Damage.h"

TAutoConsoleVariable<int32> CsCVarLogManagerDamageEvents(
	TEXT("log.manager.damage.events"),
	0,
	TEXT("Log Manager Damage Events."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerDamageTransactionEvent(
	TEXT("log.manager.damage.transaction.event"),
	0,
	TEXT("Log Manager Damage Transaction Event."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerDamageTransactionValue(
	TEXT("log.manager.damage.transaction.value"),
	0,
	TEXT("Log Manager Damage Transaction Value."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerDamageTransactionRange(
	TEXT("log.manager.damage.transaction.range"),
	0,
	TEXT("Log Manager Damage Transaction Range."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageEvents, "Log Manager Damage Events");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageTransactionEvent, "Log Manager Damage Transaction Event");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageTransactionValue, "Log Manager Damage Transaction Value");
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageTransactionRange, "Log Manager Damage Transaction Range");

	namespace Map
	{
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerDamageEvents, CsCVarLogManagerDamageEvents);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerDamageTransactionEvent, CsCVarLogManagerDamageTransactionEvent);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerDamageTransactionValue, CsCVarLogManagerDamageTransactionValue);
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerDamageTransactionRange, CsCVarLogManagerDamageTransactionRange);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSCORE_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerDamage, "Manager Damage");

	namespace Map
	{
		//extern CSCORE_API CS_ADD_TO_CVAR_MAP(ManagerDamage, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup