// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Character.h"

// CharacterAnim
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsCharacterAnim)

// CharacterBlendSpace
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsCharacterBlendSpace)

// CharacterAnimBlueprint
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsCharacterAnimBlueprint)

// CharacterAnimVariation
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsCharacterAnimVariation)

// CharacterJumpMovementState
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsCharacterJumpMovementState)

namespace NCsCharacterJumpMovementState
{
	namespace Ref
	{
		CSCORE_API const Type Grounded = EMCsCharacterJumpMovementState::Get().Add(Type::Grounded, TEXT("Grounded"));
		CSCORE_API const Type Up = EMCsCharacterJumpMovementState::Get().Add(Type::Up, TEXT("Up"));
		CSCORE_API const Type Down = EMCsCharacterJumpMovementState::Get().Add(Type::Down, TEXT("Down"));
		CSCORE_API const Type ECsCharacterJumpMovementState_MAX = EMCsCharacterJumpMovementState::Get().Add(Type::ECsCharacterJumpMovementState_MAX, TEXT("ECsCharacterJumpMovementState_MAX"), TEXT("MAX"));
	}
}