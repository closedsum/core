// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsCVars_Manager_Damage.h"

TAutoConsoleVariable<int32> CsCVarLogManagerDamageEvents(
	TEXT("log.manager.damage.events"),
	0,
	TEXT("Log Manager Damage Events.\n")
	TEXT("\n")
	TEXT("[Non-Shipping]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerDamageTransactionEvent(
	TEXT("log.manager.damage.transaction.event"),
	0,
	TEXT("Log Manager Damage Transaction Event.\n")
	TEXT("\n")
	TEXT("[Non-Shipping]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerDamageTransactionValue(
	TEXT("log.manager.damage.transaction.value"),
	0,
	TEXT("Log Manager Damage Transaction Value.\n")
	TEXT("\n")
	TEXT("[Non-Shipping]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerDamageTransactionRange(
	TEXT("log.manager.damage.transaction.range"),
	0,
	TEXT("Log Manager Damage Transaction Range.\n")
	TEXT("\n")
	TEXT("[Non-Shipping]\n")
	TEXT("0 - (default) DON'T	show log.\n")
	TEXT("1 -			SHOW	log."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageEvents, "Log Manager Damage Events");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageTransactionEvent, "Log Manager Damage Transaction Event");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageTransactionValue, "Log Manager Damage Transaction Value");
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(LogManagerDamageTransactionRange, "Log Manager Damage Transaction Range");

	namespace Map
	{
		CSDMG_API CS_ADD_TO_CVAR_MAP(LogManagerDamageEvents, CsCVarLogManagerDamageEvents);
		CSDMG_API CS_ADD_TO_CVAR_MAP(LogManagerDamageTransactionEvent, CsCVarLogManagerDamageTransactionEvent);
		CSDMG_API CS_ADD_TO_CVAR_MAP(LogManagerDamageTransactionValue, CsCVarLogManagerDamageTransactionValue);
		CSDMG_API CS_ADD_TO_CVAR_MAP(LogManagerDamageTransactionRange, CsCVarLogManagerDamageTransactionRange);
	}
}

#pragma endregion CVarLog

TAutoConsoleVariable<int32> CsCVarDrawManagerDamageEvents(
	TEXT("draw.manager.damage.events"),
	0,
	TEXT("Draw Manager Damage Events\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("0 - (default) DON'T DRAW.\n")
	TEXT("1 -			DRAW."),
	ECVF_SetByConsole
);

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawManagerDamageEvents, "Draw Manager Damage Events");

	namespace Map
	{
		CSDMG_API CS_ADD_TO_CVAR_MAP(DrawManagerDamageEvents, CsCVarDrawManagerDamageEvents);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(ManagerDamage, "Manager Damage");

	namespace Map
	{
		//extern CSDMG_API CS_ADD_TO_CVAR_MAP(ManagerDamage, CsCVarLogManagerDamageScopedTimer);
	}
}

#pragma endregion ScopedGroup