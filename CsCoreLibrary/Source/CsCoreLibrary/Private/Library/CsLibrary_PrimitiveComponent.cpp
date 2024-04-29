// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_PrimitiveComponent.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/PrimitiveComponent.h"

namespace NCsPrimitiveComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPrimitiveComponent::FLibrary, GetPhysicsLinearVelocityChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPrimitiveComponent::FLibrary, GetPhysicsAngularVelocityInDegreesChecked);
			}
		}
	}

	#define MathLibrary NCsMath::FLibrary

	// Movement
	#pragma region

	FVector3f FLibrary::GetPhysicsLinearVelocityChecked(const FString& Context, UPrimitiveComponent* Component, const FName& BoneName /*=NAME_None*/)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetPhysicsLinearVelocity(BoneName));
	}

	FVector3f FLibrary::GetPhysicsAngularVelocityInDegreesChecked(const FString& Context, const UPrimitiveComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		return MathLibrary::Convert(Component->GetPhysicsAngularVelocityInDegrees());
	}

	#pragma endregion Movement

	#undef MathLibrary
}