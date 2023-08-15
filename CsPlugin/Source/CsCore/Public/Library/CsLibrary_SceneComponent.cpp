// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_SceneComponent.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/SceneComponent.h"

namespace NCsSceneComponent
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetScaleChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetScaleChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetRelativeScaleChecked);
				// Orientation
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetRotationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetRotationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetRelativeRotationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetQuatChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetTransformChecked);
				// Movement
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetLocationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetLocationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, SetRelativeLocationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetSocketLocationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSceneComponent::FLibrary, GetUpChecked);
			}
		}
	}

	FVector3f FLibrary::GetScaleChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetComponentScale());
	}

	void FLibrary::SetScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		Component->SetWorldScale3D(MathLibrary::Convert(Scale));
	}

	void FLibrary::SetRelativeScaleChecked(const FString& Context, USceneComponent* Component, const FVector3f& Scale)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		Component->SetRelativeScale3D(MathLibrary::Convert(Scale));

	}

	// Orientation
	#pragma region

	FRotator3f FLibrary::GetRotationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetComponentRotation());
	}

	void FLibrary::SetRotationChecked(const FString& Context, USceneComponent* Component, const FRotator3f& Rotation)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		Component->SetWorldRotation(MathLibrary::Convert(Rotation));
	}

	FRotator3f FLibrary::GetRelativeRotationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetRelativeRotation());
	}

	FQuat4f FLibrary::GetQuatChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetComponentQuat());
	}

	FTransform3f FLibrary::GetTransformChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetComponentTransform());
	}

	#pragma endregion Orientation

	// Movement
	#pragma region
	
	FVector3f FLibrary::GetLocationChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetComponentLocation());
	}

	void FLibrary::SetLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		Component->SetWorldLocation(MathLibrary::Convert(Location));
	}

	void FLibrary::SetRelativeLocationChecked(const FString& Context, USceneComponent* Component, const FVector3f& Location)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		Component->SetRelativeLocation(MathLibrary::Convert(Location));
	}

	FVector3f FLibrary::GetSocketLocationChecked(const FString& Context, const USceneComponent* Component, const FName& SocketName)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_NAME_NONE_CHECKED(SocketName)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetSocketLocation(SocketName));
	}

	FVector3f FLibrary::GetUpChecked(const FString& Context, const USceneComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		typedef NCsMath::FLibrary MathLibrary;

		return MathLibrary::Convert(Component->GetUpVector());
	}

	#pragma endregion Movement
}