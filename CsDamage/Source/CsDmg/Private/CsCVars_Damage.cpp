// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars_Damage.h"

TAutoConsoleVariable<int32> CsCVarDrawDamageEventSphere(
	TEXT("draw.damage.event.sphere"),
	0,
	TEXT("Draw Damage Event Sphere\n")
	TEXT("\n")
	TEXT("[Editor]\n")
	TEXT("Draw the Damage Event for damage in the shape of a sphere.\n")
	TEXT("0 - (default) HIDE	drawing.\n")
	TEXT("1 -			SHOW	drawing."),
	ECVF_SetByConsole
);

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(DrawDamageEventSphere, "Draw Damage Event Sphere");

	namespace Map
	{
		CSDMG_API CS_ADD_TO_CVAR_MAP(DrawDamageEventSphere, CsCVarDrawDamageEventSphere);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	CSDMG_API CS_CREATE_ENUM_STRUCT_CUSTOM(Damage, "Damage");

	namespace Map
	{
		//extern CSDMG_API CS_ADD_TO_CVAR_MAP(Damage, CsCVarLogPickupScopedTimer);
	}
}

#pragma endregion ScopedGroup