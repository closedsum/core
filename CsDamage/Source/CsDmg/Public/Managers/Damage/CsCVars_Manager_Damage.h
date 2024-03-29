// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSDMG_API TAutoConsoleVariable<int32> CsCVarLogManagerDamageEvents;
extern CSDMG_API TAutoConsoleVariable<int32> CsCVarLogManagerTransactionEvent;
extern CSDMG_API TAutoConsoleVariable<int32> CsCVarLogManagerTransactionValue;
extern CSDMG_API TAutoConsoleVariable<int32> CsCVarLogManagerTransactionRange;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSDMG_API const Type LogManagerDamageEvents;
	extern CSDMG_API const Type LogManagerDamageTransactionEvent;
	extern CSDMG_API const Type LogManagerDamageTransactionValue;
	extern CSDMG_API const Type LogManagerDamageTransactionRange;

	namespace Map
	{
		extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageEvents);
		extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageTransactionEvent);
		extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageTransactionValue);
		extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageTransactionRange);
	}
}

#pragma endregion CVarLog

extern CSDMG_API TAutoConsoleVariable<int32> CsCVarDrawManagerDamageEvents;

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSDMG_API const Type DrawManagerDamageEvents;

	namespace Map
	{
		extern CSDMG_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawManagerDamageEvents);
	}
}

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSDMG_API const Type ManagerDamage;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerDamage);
	}
}

#pragma endregion ScopedGroup