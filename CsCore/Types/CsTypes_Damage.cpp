// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Damage.h"

// DamageType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsDamageType)

// HitType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsHitType)

// HitDirection
CS_DEFINE_ENUM_MAP_BODY(EMCsHitDirection)

namespace NCsHitDirection
{
	namespace Ref
	{
		CSCORE_API const Type Front = EMCsHitDirection::Get().Add(Type::Front, TEXT("Front"));
		CSCORE_API const Type FrontRight = EMCsHitDirection::Get().Add(Type::FrontRight, TEXT("FrontRight"), TEXT("Front Right"));
		CSCORE_API const Type Right = EMCsHitDirection::Get().Add(Type::Right, TEXT("Right"));
		CSCORE_API const Type BackRight = EMCsHitDirection::Get().Add(Type::BackRight, TEXT("BackRight"), TEXT("Back Right"));
		CSCORE_API const Type Back = EMCsHitDirection::Get().Add(Type::Back, TEXT("Back"));
		CSCORE_API const Type BackLeft = EMCsHitDirection::Get().Add(Type::BackLeft, TEXT("BackLeft"), TEXT("Back Left"));
		CSCORE_API const Type Left = EMCsHitDirection::Get().Add(Type::Left, TEXT("Left"));
		CSCORE_API const Type FrontLeft = EMCsHitDirection::Get().Add(Type::FrontLeft, TEXT("FrontLeft"), TEXT("Front Left"));
		CSCORE_API const Type ECsHitDirection_MAX = EMCsHitDirection::Get().Add(Type::ECsHitDirection_MAX, TEXT("ECsHitDirection_MAX"), TEXT("MAX"));
	}
}