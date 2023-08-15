// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UPrimitiveComponent;

namespace NCsPrimitiveComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetPhysicsLinearVelocityChecked;
				extern CSCORE_API const FString GetPhysicsAngularVelocityInDegreesChecked;
			}
		}
	}

	/**
	* Library of functions related to UPrimitiveComponent
	*/
	struct CSCORE_API FLibrary final
	{
	// Movement
	#pragma region
	public:

		static FVector3f GetPhysicsLinearVelocityChecked(const FString& Context, UPrimitiveComponent* Component, const FName& BoneName = NAME_None);
		FORCEINLINE static FVector3f GetPhysicsLinearVelocityChecked(UPrimitiveComponent* Component, const FName& BoneName = NAME_None)
		{
			using namespace NCsPrimitiveComponent::NLibrary::NCached;

			const FString& Context = Str::GetPhysicsLinearVelocityChecked;

			return GetPhysicsLinearVelocityChecked(Context, Component, BoneName);
		}

		static FVector3f GetPhysicsAngularVelocityInDegreesChecked(const FString& Context, const UPrimitiveComponent* Component);
		FORCEINLINE static FVector3f GetPhysicsAngularVelocityInDegreesChecked(const UPrimitiveComponent* Component)
		{
			using namespace NCsPrimitiveComponent::NLibrary::NCached;

			const FString& Context = Str::GetPhysicsAngularVelocityInDegreesChecked;

			return GetPhysicsAngularVelocityInDegreesChecked(Context, Component);
		}

	#pragma endregion Movement
	};
}