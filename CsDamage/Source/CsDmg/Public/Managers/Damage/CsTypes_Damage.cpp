// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"

// DamageType
#pragma region

namespace NCsDamageType
{
	CSDMG_API CS_CREATE_ENUM_STRUCT(Default);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		EMCsDamageType::Get().ClearUserDefinedEnums();
	}
}

#pragma endregion DamageType

// HitDirection
#pragma region

namespace NCsHitDirection
{
	namespace Ref
	{
		CSDMG_API const Type Front = EMCsHitDirection::Get().Add(Type::Front, TEXT("Front"));
		CSDMG_API const Type FrontRight = EMCsHitDirection::Get().Add(Type::FrontRight, TEXT("FrontRight"), TEXT("Front Right"));
		CSDMG_API const Type Right = EMCsHitDirection::Get().Add(Type::Right, TEXT("Right"));
		CSDMG_API const Type BackRight = EMCsHitDirection::Get().Add(Type::BackRight, TEXT("BackRight"), TEXT("Back Right"));
		CSDMG_API const Type Back = EMCsHitDirection::Get().Add(Type::Back, TEXT("Back"));
		CSDMG_API const Type BackLeft = EMCsHitDirection::Get().Add(Type::BackLeft, TEXT("BackLeft"), TEXT("Back Left"));
		CSDMG_API const Type Left = EMCsHitDirection::Get().Add(Type::Left, TEXT("Left"));
		CSDMG_API const Type FrontLeft = EMCsHitDirection::Get().Add(Type::FrontLeft, TEXT("FrontLeft"), TEXT("Front Left"));
		CSDMG_API const Type ECsHitDirection_MAX = EMCsHitDirection::Get().Add(Type::ECsHitDirection_MAX, TEXT("ECsHitDirection_MAX"), TEXT("MAX"));
	}
}

#pragma endregion HitDirection