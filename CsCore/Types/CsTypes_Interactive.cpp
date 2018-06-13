// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Interactive.h"
#include "CsCore.h"

// InteractiveType
EMCsInteractiveType* EMCsInteractiveType::Instance;

EMCsInteractiveType& EMCsInteractiveType::Get()
{
	if (!Instance)
		Instance = new EMCsInteractiveType();
	return *Instance;
}

// InteractiveState
EMCsInteractiveState* EMCsInteractiveState::Instance;

EMCsInteractiveState& EMCsInteractiveState::Get()
{
	if (!Instance)
		Instance = new EMCsInteractiveState();
	return *Instance;
}

namespace ECsInteractiveState
{
	namespace Ref
	{
		CSCORE_API const Type None = EMCsInteractiveState::Get().Add(Type::None, TEXT("None"));
		CSCORE_API const Type FirstFreeze = EMCsInteractiveState::Get().Add(Type::FirstFreeze, TEXT("FirstFreeze"), TEXT("First Freeze"));
		CSCORE_API const Type Freeze = EMCsInteractiveState::Get().Add(Type::Freeze, TEXT("Freeze"));
		CSCORE_API const Type FirstUnFreeze = EMCsInteractiveState::Get().Add(Type::FirstUnFreeze, TEXT("FirstUnFreeze"), TEXT("First UnFreeze"));
		CSCORE_API const Type FirstHold = EMCsInteractiveState::Get().Add(Type::FirstHold, TEXT("FirstHold"), TEXT("First Hold"));
		CSCORE_API const Type Hold = EMCsInteractiveState::Get().Add(Type::Hold, TEXT("Hold"));
		CSCORE_API const Type Release = EMCsInteractiveState::Get().Add(Type::Release, TEXT("Release"));
		CSCORE_API const Type FirstTouch = EMCsInteractiveState::Get().Add(Type::FirstTouch, TEXT("FirstTouch"), TEXT("First Touch"));
		CSCORE_API const Type Touch = EMCsInteractiveState::Get().Add(Type::Touch, TEXT("Touch"));
		CSCORE_API const Type FirstHover = EMCsInteractiveState::Get().Add(Type::FirstHover, TEXT("FirstHover"), TEXT("First Hover"));
		CSCORE_API const Type Hover = EMCsInteractiveState::Get().Add(Type::Hover, TEXT("Hover"));
		CSCORE_API const Type FirstUnHover = EMCsInteractiveState::Get().Add(Type::FirstUnHover, TEXT("FirstUnHover"), TEXT("First UnHover"));
		CSCORE_API const Type FirstCollide = EMCsInteractiveState::Get().Add(Type::FirstCollide, TEXT("FirstCollide"), TEXT("First Collide"));
		CSCORE_API const Type Collide = EMCsInteractiveState::Get().Add(Type::Collide, TEXT("Collide"));
		CSCORE_API const Type FirstUnCollide = EMCsInteractiveState::Get().Add(Type::FirstUnCollide, TEXT("FirstUnCollide"), TEXT("First UnCollide"));
		CSCORE_API const Type Remove = EMCsInteractiveState::Get().Add(Type::Remove, TEXT("Remove"));
		CSCORE_API const Type ECsInteractiveState_MAX = EMCsInteractiveState::Get().Add(Type::ECsInteractiveState_MAX, TEXT("ECsInteractiveState_MAX"), TEXT("MAX"));
	}
}

// InteractiveInstigator
EMCsInteractiveInstigator* EMCsInteractiveInstigator::Instance;

EMCsInteractiveInstigator& EMCsInteractiveInstigator::Get()
{
	if (!Instance)
		Instance = new EMCsInteractiveInstigator();
	return *Instance;
}

namespace ECsInteractiveInstigator
{
	namespace Ref
	{
		CSCORE_API const Type Look = EMCsInteractiveInstigator::Get().Add(Type::Look, TEXT("Look"));
		CSCORE_API const Type LeftHand = EMCsInteractiveInstigator::Get().Add(Type::LeftHand, TEXT("LeftHand"), TEXT("Left Hand"));
		CSCORE_API const Type RightHand = EMCsInteractiveInstigator::Get().Add(Type::RightHand, TEXT("RightHand"), TEXT("Right Hand"));
		CSCORE_API const Type Actor = EMCsInteractiveInstigator::Get().Add(Type::Actor, TEXT("Actor"));
		CSCORE_API const Type ECsInteractiveInstigator_MAX = EMCsInteractiveInstigator::Get().Add(Type::ECsInteractiveInstigator_MAX, TEXT("ECsInteractiveInstigator_MAX"), TEXT("MAX"));
	}
}

// InteractiveCollision
EMCsInteractiveCollision* EMCsInteractiveCollision::Instance;

EMCsInteractiveCollision& EMCsInteractiveCollision::Get()
{
	if (!Instance)
		Instance = new EMCsInteractiveCollision();
	return *Instance;
}

namespace ECsInteractiveCollision
{
	namespace Ref
	{
		CSCORE_API const Type Box = EMCsInteractiveCollision::Get().Add(Type::Box, TEXT("Box"));
		CSCORE_API const Type Sphere = EMCsInteractiveCollision::Get().Add(Type::Sphere, TEXT("Sphere"));
		CSCORE_API const Type DistanceSquared = EMCsInteractiveCollision::Get().Add(Type::DistanceSquared, TEXT("DistanceSquared"), TEXT("Distance Squared"));
		CSCORE_API const Type Trace = EMCsInteractiveCollision::Get().Add(Type::Trace, TEXT("Trace"));
		CSCORE_API const Type Mesh = EMCsInteractiveCollision::Get().Add(Type::Mesh, TEXT("Mesh"));
		CSCORE_API const Type ECsInteractiveCollision_MAX = EMCsInteractiveCollision::Get().Add(Type::ECsInteractiveCollision_MAX, TEXT("ECsInteractiveCollision_MAX"), TEXT("MAX"));
	}
}

// PickupFX
EMCsPickupFX* EMCsPickupFX::Instance;

EMCsPickupFX& EMCsPickupFX::Get()
{
	if (!Instance)
		Instance = new EMCsPickupFX();
	return *Instance;
}

// PickupSound
EMCsPickupSound* EMCsPickupSound::Instance;

EMCsPickupSound& EMCsPickupSound::Get()
{
	if (!Instance)
		Instance = new EMCsPickupSound();
	return *Instance;
}