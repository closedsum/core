// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

extern CSTYPES_API TAutoConsoleVariable<bool> CsCVarEnableScriptChecked;

// CVarToggle
#pragma region

namespace NCsCVarToggle
{
	extern CSTYPES_API const Type EnableScriptChecked;

	namespace Map
	{
		extern CSTYPES_API CS_DECLARE_ADD_TO_CVAR_MAP(EnableScriptChecked);
	}
}

#pragma endregion CVarToggle

#if WITH_EDITOR
#define CS_SCRIPT_CHECKED(ExprChecked, SafeExpr) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		ExprChecked; \
	} \
	else \
	{ \
		SafeExpr; \
	}
#define CS_SCRIPT_GET_CHECKED(ExprChecked, SafeExpr) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? ExprChecked : SafeExpr
#define CS_SCRIPT_SET_CHECKED(ExprChecked, SafeExpr) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		ExprChecked; \
		return true; \
	} \
	return SafeExpr;
#define CS_SCRIPT_SET_CHECKED_NO_RET(ExprChecked, SafeExpr) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		ExprChecked; \
	} \
	else \
	{ \
		SafeExpr; \
	}
#else
#define CS_SCRIPT_CHECKED(ExprChecked, SafeExpr) ExprChecked;
#define CS_SCRIPT_GET_CHECKED(ExprChecked, SafeExpr) ExprChecked
#define CS_SCRIPT_SET_CHECKED(ExprChecked, SafeExpr) ExprChecked; return true;
#define CS_SCRIPT_SET_CHECKED_NO_RET(ExprChecked, SafeExpr) ExprChecked;
#endif // #if WITH_EDITOR