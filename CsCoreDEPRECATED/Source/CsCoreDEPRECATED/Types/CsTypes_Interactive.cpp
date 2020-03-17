// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interactive.h"

// InteractiveState
#pragma region

namespace ECsInteractiveState
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type None = EMCsInteractiveState::Get().Add(Type::None, TEXT("None"));
		CSCOREDEPRECATED_API const Type FirstFreeze = EMCsInteractiveState::Get().Add(Type::FirstFreeze, TEXT("FirstFreeze"), TEXT("First Freeze"));
		CSCOREDEPRECATED_API const Type Freeze = EMCsInteractiveState::Get().Add(Type::Freeze, TEXT("Freeze"));
		CSCOREDEPRECATED_API const Type FirstUnFreeze = EMCsInteractiveState::Get().Add(Type::FirstUnFreeze, TEXT("FirstUnFreeze"), TEXT("First UnFreeze"));
		CSCOREDEPRECATED_API const Type FirstHold = EMCsInteractiveState::Get().Add(Type::FirstHold, TEXT("FirstHold"), TEXT("First Hold"));
		CSCOREDEPRECATED_API const Type Hold = EMCsInteractiveState::Get().Add(Type::Hold, TEXT("Hold"));
		CSCOREDEPRECATED_API const Type Release = EMCsInteractiveState::Get().Add(Type::Release, TEXT("Release"));
		CSCOREDEPRECATED_API const Type FirstTouch = EMCsInteractiveState::Get().Add(Type::FirstTouch, TEXT("FirstTouch"), TEXT("First Touch"));
		CSCOREDEPRECATED_API const Type Touch = EMCsInteractiveState::Get().Add(Type::Touch, TEXT("Touch"));
		CSCOREDEPRECATED_API const Type FirstHover = EMCsInteractiveState::Get().Add(Type::FirstHover, TEXT("FirstHover"), TEXT("First Hover"));
		CSCOREDEPRECATED_API const Type Hover = EMCsInteractiveState::Get().Add(Type::Hover, TEXT("Hover"));
		CSCOREDEPRECATED_API const Type FirstUnHover = EMCsInteractiveState::Get().Add(Type::FirstUnHover, TEXT("FirstUnHover"), TEXT("First UnHover"));
		CSCOREDEPRECATED_API const Type FirstCollide = EMCsInteractiveState::Get().Add(Type::FirstCollide, TEXT("FirstCollide"), TEXT("First Collide"));
		CSCOREDEPRECATED_API const Type Collide = EMCsInteractiveState::Get().Add(Type::Collide, TEXT("Collide"));
		CSCOREDEPRECATED_API const Type FirstUnCollide = EMCsInteractiveState::Get().Add(Type::FirstUnCollide, TEXT("FirstUnCollide"), TEXT("First UnCollide"));
		CSCOREDEPRECATED_API const Type Remove = EMCsInteractiveState::Get().Add(Type::Remove, TEXT("Remove"));
		CSCOREDEPRECATED_API const Type ECsInteractiveState_MAX = EMCsInteractiveState::Get().Add(Type::ECsInteractiveState_MAX, TEXT("ECsInteractiveState_MAX"), TEXT("MAX"));
	}
}

#pragma endregion InteractiveState

// InteractiveInstigator
#pragma region

namespace ECsInteractiveInstigator
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Look = EMCsInteractiveInstigator::Get().Add(Type::Look, TEXT("Look"));
		CSCOREDEPRECATED_API const Type LeftHand = EMCsInteractiveInstigator::Get().Add(Type::LeftHand, TEXT("LeftHand"), TEXT("Left Hand"));
		CSCOREDEPRECATED_API const Type RightHand = EMCsInteractiveInstigator::Get().Add(Type::RightHand, TEXT("RightHand"), TEXT("Right Hand"));
		CSCOREDEPRECATED_API const Type Actor = EMCsInteractiveInstigator::Get().Add(Type::Actor, TEXT("Actor"));
		CSCOREDEPRECATED_API const Type ECsInteractiveInstigator_MAX = EMCsInteractiveInstigator::Get().Add(Type::ECsInteractiveInstigator_MAX, TEXT("ECsInteractiveInstigator_MAX"), TEXT("MAX"));
	}
}

#pragma endregion InteractiveInstigator

// InteractiveCollision
#pragma region

namespace ECsInteractiveCollision
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Box = EMCsInteractiveCollision::Get().Add(Type::Box, TEXT("Box"));
		CSCOREDEPRECATED_API const Type Sphere = EMCsInteractiveCollision::Get().Add(Type::Sphere, TEXT("Sphere"));
		CSCOREDEPRECATED_API const Type DistanceSquared = EMCsInteractiveCollision::Get().Add(Type::DistanceSquared, TEXT("DistanceSquared"), TEXT("Distance Squared"));
		CSCOREDEPRECATED_API const Type Trace = EMCsInteractiveCollision::Get().Add(Type::Trace, TEXT("Trace"));
		CSCOREDEPRECATED_API const Type Mesh = EMCsInteractiveCollision::Get().Add(Type::Mesh, TEXT("Mesh"));
		CSCOREDEPRECATED_API const Type ECsInteractiveCollision_MAX = EMCsInteractiveCollision::Get().Add(Type::ECsInteractiveCollision_MAX, TEXT("ECsInteractiveCollision_MAX"), TEXT("MAX"));
	}
}

#pragma endregion InteractiveCollision