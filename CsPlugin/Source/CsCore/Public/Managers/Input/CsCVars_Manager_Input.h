// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRaw;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRawAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRawAxis;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInput;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAxis;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTrigger;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputLocation;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRotation;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputGameEvent;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputGameEventDefinition;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputActiveMode;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	// Input
	extern CSCORE_API const Type LogInputRaw;
	extern CSCORE_API const Type LogInputRawAction;
	extern CSCORE_API const Type LogInputRawAxis;

	extern CSCORE_API const Type LogInput;
	extern CSCORE_API const Type LogInputAction;
	extern CSCORE_API const Type LogInputAxis;
	extern CSCORE_API const Type LogInputTrigger;
	extern CSCORE_API const Type LogInputLocation;
	extern CSCORE_API const Type LogInputRotation;

	extern CSCORE_API const Type LogInputGameEvent;
	extern CSCORE_API const Type LogInputGameEventDefinition;

	extern CSCORE_API const Type LogInputActiveMode;

	namespace Map
	{
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputRaw);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputRawAction);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputRawAxis);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInput);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAction);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputAxis);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputTrigger);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputLocation);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputRotation);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputGameEvent);
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputGameEventDefinition);

		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogInputActiveMode);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSCORE_API const Type ManagerInput;

	namespace Map
	{
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(ManagerInput);
	}
}

#pragma endregion ScopedGroup