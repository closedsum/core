// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CoreMinimal.h"


class UPrimitiveComponent;

namespace NCsPrimitiveComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORELIBRARY_API const FString GetPhysicsLinearVelocityChecked;
				extern CSCORELIBRARY_API const FString GetPhysicsAngularVelocityInDegreesChecked;
			}
		}
	}

	/**
	* Library of functions related to UPrimitiveComponent
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	#define USING_NS_CACHED using namespace NCsPrimitiveComponent::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsPrimitiveComponent::NLibrary::NCached; \
		const FString& Context = Str::__FunctionName

	// Movement
	#pragma region
	public:

		static FVector3f GetPhysicsLinearVelocityChecked(const FString& Context, UPrimitiveComponent* Component, const FName& BoneName = NAME_None);
		FORCEINLINE static FVector3f GetPhysicsLinearVelocityChecked(UPrimitiveComponent* Component, const FName& BoneName = NAME_None)
		{
			SET_CONTEXT(GetPhysicsLinearVelocityChecked);

			return GetPhysicsLinearVelocityChecked(Context, Component, BoneName);
		}

		static FVector3f GetPhysicsAngularVelocityInDegreesChecked(const FString& Context, const UPrimitiveComponent* Component);
		FORCEINLINE static FVector3f GetPhysicsAngularVelocityInDegreesChecked(const UPrimitiveComponent* Component)
		{
			SET_CONTEXT(GetPhysicsAngularVelocityInDegreesChecked);

			return GetPhysicsAngularVelocityInDegreesChecked(Context, Component);
		}

	#pragma endregion Movement

	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	};
}

using CsPrimitiveComponentLibrary = NCsPrimitiveComponent::FLibrary;