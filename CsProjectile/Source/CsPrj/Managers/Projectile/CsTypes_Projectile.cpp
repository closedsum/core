// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsTypes_Projectile.h"

// ProjectileRelevance
#pragma region

namespace NCsProjectileRelevance
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, RealVisible, "Real Visible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, RealInvisible, "Real Invisible");
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileRelevance, Fake);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileRelevance, ECsProjectileRelevance_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileRelevance_MAX;
}

#pragma endregion ProjectileRelevance

// ProjectileState
#pragma region

namespace NCsProjectileState
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, Active);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, DeActivating);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileState, InActive);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileState, ECsProjectileState_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileState_MAX;
}

#pragma endregion ProjectileState

// ProjectileDeActivate
#pragma region

namespace NCsProjectileDeActivate
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Collision);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Movement);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileDeActivate, Mesh);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileDeActivate, ECsProjectileDeActivate_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileDeActivate_MAX;
}

#pragma endregion ProjectileDeActivate

// ProjectileMovement
#pragma region

namespace NCsProjectileMovement
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovement, Simulated);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovement, Function);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileMovement, ECsProjectileMovement_MAX,"MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovement_MAX;
}

#pragma endregion ProjectileMovement

// ProjectileMovementFunctionType
#pragma region

namespace NCsProjectileMovementFunctionType
{
	namespace Ref
	{
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovementFunctionType, Linear);
		CSPRJ_API CS_ADD_TO_ENUM_MAP(EMCsProjectileMovementFunctionType, Sine);
		CSPRJ_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsProjectileMovementFunctionType, ECsProjectileMovementFunctionType_MAX, "MAX");
	}

	CSPRJ_API const uint8 MAX = (uint8)Type::ECsProjectileMovementFunctionType_MAX;
}

#pragma endregion ProjectileMovementFunctionType

// ICsProjectilePayload
#pragma region

const FName ICsProjectilePayload::Name = FName("ICsProjectilePayload");

#pragma endregion ICsProjectilePayload