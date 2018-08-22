// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Character.h"

// CharacterAnim
EMCsCharacterAnim* EMCsCharacterAnim::Instance;

EMCsCharacterAnim& EMCsCharacterAnim::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterAnim();
	return *Instance;
}

// CharacterBlendSpace
EMCsCharacterBlendSpace* EMCsCharacterBlendSpace::Instance;

EMCsCharacterBlendSpace& EMCsCharacterBlendSpace::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterBlendSpace();
	return *Instance;
}

// CharacterAnimBlueprint
EMCsCharacterAnimBlueprint* EMCsCharacterAnimBlueprint::Instance;

EMCsCharacterAnimBlueprint& EMCsCharacterAnimBlueprint::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterAnimBlueprint();
	return *Instance;
}

// CharacterAnimVariation
EMCsCharacterAnimVariation* EMCsCharacterAnimVariation::Instance;

EMCsCharacterAnimVariation& EMCsCharacterAnimVariation::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterAnimVariation();
	return *Instance;
}

// CharacterJumpMovementState
EMCsCharacterJumpMovementState* EMCsCharacterJumpMovementState::Instance;

EMCsCharacterJumpMovementState& EMCsCharacterJumpMovementState::Get()
{
	if (!Instance)
		Instance = new EMCsCharacterJumpMovementState();
	return *Instance;
}

namespace ECsCharacterJumpMovementState
{
	namespace Ref
	{
		CSCORE_API const Type Grounded = EMCsCharacterJumpMovementState::Get().Add(Type::Grounded, TEXT("Grounded"));
		CSCORE_API const Type Up = EMCsCharacterJumpMovementState::Get().Add(Type::Up, TEXT("Up"));
		CSCORE_API const Type Down = EMCsCharacterJumpMovementState::Get().Add(Type::Down, TEXT("Down"));
		CSCORE_API const Type ECsCharacterJumpMovementState_MAX = EMCsCharacterJumpMovementState::Get().Add(Type::ECsCharacterJumpMovementState_MAX, TEXT("ECsCharacterJumpMovementState_MAX"), TEXT("MAX"));
	}
}