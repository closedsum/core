// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceState;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceStateTransition;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceCanFire;
// Scoped Timers
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceScopedTimer;
extern CSWP_API TAutoConsoleVariable<int32> CsCVarLogWeaponPointSequenceScopedTimerFire;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSWP_API const Type LogWeaponPointSequenceState;
	extern CSWP_API const Type LogWeaponPointSequenceStateTransition;
	extern CSWP_API const Type LogWeaponPointSequenceCanFire;
	// Scoped Timers
	extern CSWP_API const Type LogWeaponPointSequenceScopedTimer;
	extern CSWP_API const Type LogWeaponPointSequenceScopedTimerFire;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointSequenceState);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointSequenceStateTransition);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointSequenceCanFire);
		// Scoped Timers
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointSequenceScopedTimer);
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(LogWeaponPointSequenceScopedTimerFire);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSWP_API const Type WeaponPointSequence;

	namespace Map
	{
		extern CSWP_API CS_DECLARE_ADD_TO_CVAR_MAP(WeaponPointSequence);
	}
}

#pragma endregion ScopedGroup