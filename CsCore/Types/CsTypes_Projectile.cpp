// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Projectile.h"

// ProjectileRelevance
EMCsProjectileRelevance* EMCsProjectileRelevance::Instance;

EMCsProjectileRelevance& EMCsProjectileRelevance::Get()
{
	if (!Instance)
		Instance = new EMCsProjectileRelevance();
	return *Instance;
}

namespace ECsProjectileRelevance
{
	namespace Ref
	{
		CSCORE_API const Type RealVisible = EMCsProjectileRelevance::Get().Add(Type::RealVisible, TEXT("RealVisible"), TEXT("Real Visible"));
		CSCORE_API const Type RealInvisible = EMCsProjectileRelevance::Get().Add(Type::RealInvisible, TEXT("RealInvisible"), TEXT("Real Invisible"));
		CSCORE_API const Type Fake = EMCsProjectileRelevance::Get().Add(Type::Fake, TEXT("Fake"));
		CSCORE_API const Type ECsProjectileRelevance_MAX = EMCsProjectileRelevance::Get().Add(Type::ECsProjectileRelevance_MAX, TEXT("ECsProjectileRelevance_MAX"), TEXT("MAX"));
	}
}

// ProjectileType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsProjectileType)

// ProjectileState
CS_DEFINE_ENUM_MAP_BODY(EMCsProjectileState)

namespace ECsProjectileState
{
	namespace Ref
	{
		CSCORE_API const Type Active = EMCsProjectileState::Get().Add(Type::Active, TEXT("Active"));
		CSCORE_API const Type DeActivating = EMCsProjectileState::Get().Add(Type::DeActivating, TEXT("DeActivating"));
		CSCORE_API const Type InActive = EMCsProjectileState::Get().Add(Type::InActive, TEXT("InActive"));
		CSCORE_API const Type ECsProjectileState_MAX = EMCsProjectileState::Get().Add(Type::ECsProjectileState_MAX, TEXT("ECsProjectileState_MAX"), TEXT("MAX"));
	}
}

// ProjectileDeActivate
CS_DEFINE_ENUM_MAP_BODY(EMCsProjectileDeActivate)

namespace ECsProjectileDeActivate
{
	namespace Ref
	{
		CSCORE_API const Type Collision = EMCsProjectileDeActivate::Get().Add(Type::Collision, TEXT("Collision"));
		CSCORE_API const Type Movement = EMCsProjectileDeActivate::Get().Add(Type::Movement, TEXT("Movement"));
		CSCORE_API const Type Mesh = EMCsProjectileDeActivate::Get().Add(Type::Mesh, TEXT("Mesh"));
		CSCORE_API const Type ECsProjectileDeActivate_MAX = EMCsProjectileDeActivate::Get().Add(Type::ECsProjectileDeActivate_MAX, TEXT("ECsProjectileDeActivate_MAX"), TEXT("MAX"));
	}
}

// ProjectileMovement
CS_DEFINE_ENUM_MAP_BODY(EMCsProjectileMovement)

namespace ECsProjectileMovement
{
	namespace Ref
	{
		CSCORE_API const Type Simulated = EMCsProjectileMovement::Get().Add(Type::Simulated, TEXT("Simulated"));
		CSCORE_API const Type Function = EMCsProjectileMovement::Get().Add(Type::Function, TEXT("Function"));
		CSCORE_API const Type ECsProjectileMovement_MAX = EMCsProjectileMovement::Get().Add(Type::ECsProjectileMovement_MAX, TEXT("ECsProjectileMovement_MAX"), TEXT("MAX"));
	}
}

// ProjectileMovementFunctionType
CS_DEFINE_ENUM_MAP_BODY(EMCsProjectileMovementFunctionType)

namespace ECsProjectileMovementFunctionType
{
	namespace Ref
	{
		CSCORE_API const Type Linear = EMCsProjectileMovementFunctionType::Get().Add(Type::Linear, TEXT("Linear"));
		CSCORE_API const Type Sine = EMCsProjectileMovementFunctionType::Get().Add(Type::Sine, TEXT("Sine"));
		CSCORE_API const Type ECsProjectileMovementFunctionType_MAX = EMCsProjectileMovementFunctionType::Get().Add(Type::ECsProjectileMovementFunctionType_MAX, TEXT("ECsProjectileMovementFunctionType_MAX"), TEXT("MAX"));
	}
}