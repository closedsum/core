// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerDamageEvents;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTransactionEvent;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTransactionValue;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTransactionRange;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSCORE_API const Type LogManagerDamageEvents;
	extern CSCORE_API const Type LogManagerDamageTransactionEvent;
	extern CSCORE_API const Type LogManagerDamageTransactionValue;
	extern CSCORE_API const Type LogManagerDamageTransactionRange;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageEvents);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageTransactionEvent);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageTransactionValue);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDamageTransactionRange);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerDamage;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerDamage);
	}
}

#pragma endregion ScopedGroup