// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsCVars_Manager_Projectile.h"

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileTransactions(
	TEXT("log.manager.projectile.transactions"),
	0,
	TEXT("Log Manager Projectile Allocation and DeAllocation."),
	ECVF_SetByConsole
);

// CVarLog
#pragma region

namespace NCsCVarLog
{
	CSPRJ_API CS_CREATE_ENUM_STRUCT_CUSTOM(EMCsCVarLog, LogManagerProjectileTransactions, "Log Manager Projectile Transactions");

	namespace Map
	{
		CSPRJ_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileTransactions, CsCVarLogManagerProjectileTransactions);
	}
}

#pragma endregion CVarLog