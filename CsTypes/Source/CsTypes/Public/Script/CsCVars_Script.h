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
#define CS_SCRIPT_CHECKED(__ExprChecked, __SafeExpr) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		__ExprChecked; \
	} \
	else \
	{ \
		__SafeExpr; \
	}
#define CS_SCRIPT_GET_CHECKED(__ExprChecked, __SafeExpr) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? __ExprChecked : __SafeExpr
#define CS_SCRIPT_SET_CHECKED(__ExprChecked, __SafeExpr) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		__ExprChecked; \
		return true; \
	} \
	return __SafeExpr;
#define CS_SCRIPT_SET_CHECKED_NO_RET(__ExprChecked, __SafeExpr) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		__ExprChecked; \
	} \
	else \
	{ \
		__SafeExpr; \
	}

// Library
#pragma region

// For the follow Script Library related Macros:
//	Assume a private typedef named: NativeLibrary has been defined in the Script Library
//	Assume a static function named LogError has been defined
//	Assume const FString& Ctxt has been defined
//  Assume the "Checked" related Native Library function takes the parameters in "Indices / Slots":
//		Param 1:			const FString&				:	Context (Ctxt will be used in the Script Library)
//  Assume the "Safe" related Native Library function takes the parameters in "Indices / Slots":
//		Param 1:			const FString&				:	Context (Ctxt will be used in the Script Library)
//		Param "2nd Last:	bool&						:	OutSuccess
//		Param "Last":		void(*Log)(const FString&)
//  NOTE:
//		MACRO_NAME_"NUMBER" - "NUMBER" is the number of parameters for the "Safe" related Native Library function

#define CS_SCRIPT_LIBRARY_CHECKED_3(__Fn) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__Fn##Checked(Ctxt); \
	} \
	else \
	{ \
		NativeLibrary::Safe##__Fn(Ctxt, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CHECKED_4(__Fn, __P2) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__Fn##Checked(Ctxt, __P2); \
	} \
	else \
	{ \
		NativeLibrary::Safe##__Fn(Ctxt, __P2, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CHECKED_5(__Fn, __P2, __P3) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3); \
	} \
	else \
	{ \
		NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CHECKED_6(__Fn, __P2, __P3, __P4) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4); \
	} \
	else \
	{ \
		NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, __P4, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CHECKED_7(__Fn, __P2, __P3, __P4, __P5) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5); \
	} \
	else \
	{ \
		NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, __P4, __P5, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CHECKED_8(__Fn, __P2, __P3, __P4, __P5, __P6) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5, __P6); \
	} \
	else \
	{ \
		NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, __P4, __P5, __P6, OutSuccess, LogError); \
	}

#define CS_SCRIPT_LIBRARY_GET_CHECKED_3(__Fn) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__Fn##Checked(Ctxt) : NativeLibrary::Safe##__Fn(Ctxt, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_4(__Fn, __P2) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__Fn##Checked(Ctxt, __P2) : NativeLibrary::Safe##__Fn(Ctxt, __P2, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_5(__Fn, __P2, __P3) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3) : NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_6(__Fn, __P2, __P3, __P4) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4) : NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, __P4, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_7(__Fn, __P2, __P3, __P4, __P5) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5) : __NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, __P4, __P5, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_8(__Fn, __P2, __P3, __P4, __P5, __P6) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5, __P6) : __NativeLibrary::Safe##__Fn(Ctxt, __P2, __P3, __P4, __P5, __P6, OutSuccess, LogError)

#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_3(__FnChecked, __SafeFn) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__FnChecked(Ctxt); \
	} \
	else \
	{ \
		NativeLibrary::__SafeFn(Ctxt, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_4(__FnChecked, __SafeFn, __P2) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__FnChecked(Ctxt, __P2); \
	} \
	else \
	{ \
		NativeLibrary::__SafeFn(Ctxt, __P2, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_5(__FnChecked, __SafeFn, __P2, __P3) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__FnChecked(Ctxt, __P2, __P3); \
	} \
	else \
	{ \
		NativeLibrary::__SafeFn(Ctxt, __P2, __P3, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_6(__FnChecked, __SafeFn, __P2, __P3, __P4) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4); \
	} \
	else \
	{ \
		NativeLibrary::__SafeFn(Ctxt, __P2, __P3, __P4, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_7(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5); \
	} \
	else \
	{ \
		NativeLibrary::__SafeFn(Ctxt, __P2, __P3, __P4, __P5, OutSuccess, LogError); \
	}
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_8(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5, __P6) if (CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked)) \
	{ \
		NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5, __P6); \
	} \
	else \
	{ \
		NativeLibrary::__SafeFn(Ctxt, __P2, __P3, __P4, __P5, __P6, OutSuccess, LogError); \
	}

#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_3(__FnChecked, __SafeFn) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__FnChecked(Ctxt) : NativeLibrary::__SafeFn(Ctxt, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(__FnChecked, __SafeFn, __P2) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__FnChecked(Ctxt, __P2) : NativeLibrary::__SafeFn(Ctxt, __P2, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_5(__FnChecked, __SafeFn, __P2, __P3) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__FnChecked(Ctxt, __P2, __P3) : NativeLibrary::__SafeFn(Ctxt, __P2, __P3, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_6(__FnChecked, __SafeFn, __P2, __P3, __P4) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4) : NativeLibrary::__SafeFn(Ctxt, __P2, __P3, __P4, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_7(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5) : NativeLibrary::__SafeFn(Ctxt, __P2, __P3, __P4, __P5, OutSuccess, LogError)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_8(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5, __P6) CS_CVAR_TOGGLE_IS_ENABLED(EnableScriptChecked) ? NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5, __P6) : NativeLibrary::__SafeFn(Ctxt, __P2, __P3, __P4, __P5, __P6, OutSuccess, LogError)

#pragma endregion Library

#else

// Library
#pragma region

// For the follow Script Library related Macros:
//	Assume a private typedef named: NativeLibrary has been defined in the Script Library
//	Assume a static function named LogError has been defined
//	Assume const FString& Ctxt has been defined
//  Assume the "Checked" related Native Library function takes the parameters in "Indices / Slots":
//		Param 1:			const FString&				:	Context (Ctxt will be used in the Script Library)
//  Assume the "Safe" related Native Library function takes the parameters in "Indices / Slots":
//		Param 1:			const FString&				:	Context (Ctxt will be used in the Script Library)
//		Param "2nd Last:	bool&						:	OutSuccess
//		Param "Last":		void(*Log)(const FString&)
//  NOTE:
//		MACRO_NAME_"NUMBER" - "NUMBER" is the number of parameters for the "Safe" related Native Library function

#define CS_SCRIPT_LIBRARY_CHECKED_3(__Fn) NativeLibrary::__Fn##Checked(Ctxt);
#define CS_SCRIPT_LIBRARY_CHECKED_4(__Fn, __P2) NativeLibrary::__Fn##Checked(Ctxt, __P2);
#define CS_SCRIPT_LIBRARY_CHECKED_5(__Fn, __P2, __P3) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3);
#define CS_SCRIPT_LIBRARY_CHECKED_6(__Fn, __P2, __P3, __P4) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4);
#define CS_SCRIPT_LIBRARY_CHECKED_7(__Fn, __P2, __P3, __P4, __P5) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5);
#define CS_SCRIPT_LIBRARY_CHECKED_8(__Fn, __P2, __P3, __P4, __P5, __P6) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5, __P6);

#define CS_SCRIPT_LIBRARY_GET_CHECKED_3(__Fn) NativeLibrary::__Fn##Checked(Ctxt)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_4(__Fn, __P2) NativeLibrary::__Fn##Checked(Ctxt, __P2)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_5(__Fn, __P2, __P3) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_6(__Fn, __P2, __P3, __P4) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_7(__Fn, __P2, __P3, __P4, __P5) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5)
#define CS_SCRIPT_LIBRARY_GET_CHECKED_8(__Fn, __P2, __P3, __P4, __P5, __P6) NativeLibrary::__Fn##Checked(Ctxt, __P2, __P3, __P4, __P5, __P6)

#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_3(__FnChecked, __SafeFn) NativeLibrary::__FnChecked(Ctxt);
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_4(__FnChecked, __SafeFn, __P2) NativeLibrary::__FnChecked(Ctxt, __P2);
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_5(__FnChecked, __SafeFn, __P2, __P3) NativeLibrary::__FnChecked(Ctxt, __P2, __P3);
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_6(__FnChecked, __SafeFn, __P2, __P3, __P4) NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4);
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_7(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5) NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5);
#define CS_SCRIPT_LIBRARY_CUSTOM_CHECKED_8(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5, __P6) NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5, __P6);

#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_3(__FnChecked, __SafeFn) NativeLibrary::__FnChecked(Ctxt)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_4(__FnChecked, __SafeFn, __P2) NativeLibrary::__FnChecked(Ctxt, __P2)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_5(__FnChecked, __SafeFn, __P2, __P3) NativeLibrary::__FnChecked(Ctxt, __P2, __P3)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_6(__FnChecked, __SafeFn, __P2, __P3, __P4) NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_7(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5) NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5)
#define CS_SCRIPT_LIBRARY_GET_CUSTOM_CHECKED_8(__FnChecked, __SafeFn, __P2, __P3, __P4, __P5, __P6) NativeLibrary::__FnChecked(Ctxt, __P2, __P3, __P4, __P5, __P6)

#pragma endregion Library

#define CS_SCRIPT_CHECKED(__ExprChecked, __SafeExpr) __ExprChecked;
#define CS_SCRIPT_GET_CHECKED(__ExprChecked, __SafeExpr) __ExprChecked
#define CS_SCRIPT_SET_CHECKED(__ExprChecked, __SafeExpr) __ExprChecked; return true;
#define CS_SCRIPT_SET_CHECKED_NO_RET(__ExprChecked, __SafeExpr) __ExprChecked;

#endif // #if WITH_EDITOR