// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Character.h"

// CharacterJumpMovementState
#pragma region

namespace NCsCharacterJumpMovementState
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Grounded = EMCsCharacterJumpMovementState::Get().Add(Type::Grounded, TEXT("Grounded"));
		CSCOREDEPRECATED_API const Type Up = EMCsCharacterJumpMovementState::Get().Add(Type::Up, TEXT("Up"));
		CSCOREDEPRECATED_API const Type Down = EMCsCharacterJumpMovementState::Get().Add(Type::Down, TEXT("Down"));
		CSCOREDEPRECATED_API const Type ECsCharacterJumpMovementState_MAX = EMCsCharacterJumpMovementState::Get().Add(Type::ECsCharacterJumpMovementState_MAX, TEXT("ECsCharacterJumpMovementState_MAX"), TEXT("MAX"));
	}
}

#pragma endregion CharacterJumpMovementState