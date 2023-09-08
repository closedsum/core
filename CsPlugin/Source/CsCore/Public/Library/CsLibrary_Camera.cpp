// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Camera.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Math.h"
// Library
	// Common
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
// Pawn
#include "GameFramework/Pawn.h"
// Actor
#include "GameFramework/Actor.h"
// Camera
#include "Camera/CsGetCameraComponent.h"
#include "Camera/CameraComponent.h"

namespace NCsCamera
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCamera::FLibrary, GetLocationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCamera::FLibrary, GetRotationChecked);
				CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCamera::FLibrary, GetDirectionChecked);
			}
		}
	}

	// Location
	#pragma region

	FVector3f FLibrary::GetLocation(UObject* Object)
	{
		checkf(Object, TEXT("NCsCamera::FLibrary::GetLocation: Object is NULL."));

		typedef NCsMath::FLibrary MathLibrary;

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return MathLibrary::Convert(Camera->GetComponentLocation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return MathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Location);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return MathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Location);
			}
		}
		return FVector3f::ZeroVector;
	}

	FVector3f FLibrary::GetLocation(UObject* Object, const int32& Rules)
	{
	// TODO: Add Rules
		return GetLocation(Object);
	}

	FVector3f FLibrary::GetLocationChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		typedef NCsMath::FLibrary MathLibrary;

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return MathLibrary::Convert(Camera->GetComponentLocation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return MathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Location);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return MathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Location);
			}
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
			}
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		return FVector3f::ZeroVector;
	}

	FVector3f FLibrary::GetLocationChecked(UObject* Object)
	{
		using namespace NCsCamera::NLibrary::NCached;

		const FString& Context = Str::GetLocationChecked;

		return GetLocationChecked(Context, Object);
	}

	#pragma endregion Location

	// Rotation
	#pragma region

	FRotator3f FLibrary::GetRotation(UObject* Object)
	{
		checkf(Object, TEXT("NCsCamera::FLibrary::GetRotation: Object is NULL."));

		typedef NCsMath::FLibrary MathLibrary;

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return MathLibrary::Convert(Camera->GetComponentRotation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return MathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Rotation);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return MathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Rotation);
			}
		}
		return FRotator3f::ZeroRotator;
	}

	FRotator3f FLibrary::GetRotation(UObject* Object, const int32& Rules)
	{
		return NCsRotationRules::GetRotation(GetRotation(Object), Rules);
	}

	FRotator3f FLibrary::GetRotationChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		typedef NCsMath::FLibrary MathLibrary;

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return MathLibrary::Convert(Camera->GetComponentRotation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return MathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Rotation);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return MathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Rotation);
			}
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
			}
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		return FRotator3f::ZeroRotator;
	}

	FRotator3f FLibrary::GetRotationChecked(UObject* Object)
	{
		using namespace NCsCamera::NLibrary::NCached;

		const FString& Context = Str::GetRotationChecked;

		return GetRotationChecked(Context, Object);
	}

	FRotator3f FLibrary::GetRotationChecked(const FString& Context, UObject* Object, const int32& Rules)
	{
		return NCsRotationRules::GetRotationChecked(Context, GetRotationChecked(Context, Object), Rules);
	}

	FRotator3f FLibrary::GetRotationChecked(UObject* Object, const int32& Rules)
	{
		using namespace NCsCamera::NLibrary::NCached;

		const FString& Context = Str::GetRotationChecked;

		return GetRotationChecked(Context, Object, Rules);
	}

	#pragma endregion Rotation
}