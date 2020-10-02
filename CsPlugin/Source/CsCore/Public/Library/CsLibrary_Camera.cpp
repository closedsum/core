// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Camera.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Math.h"
// Player
#include "GameFramework/PlayerController.h"
// Pawn
#include "GameFramework/Pawn.h"
// Actor
#include "GameFramework/Actor.h"
// Camera
#include "Camera/CsGetCameraComponent.h"
#include "Camera/CameraComponent.h"

namespace NCsLibraryCameraCached
{
	namespace Str
	{
		CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Camera, GetLocationChecked);
		CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetRotationChecked);
		CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetDirectionChecked);
	}
}

// Location
#pragma region

FVector FCsLibrary_Camera::GetLocation(UObject* Object)
{
	checkf(Object, TEXT("FCsLibrary_Camera::GetLocation: Object is NULL."));

	// Try to get camera through the object

	// ICsGetCameraComponent
	if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
	{
		UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
		return Camera->GetComponentLocation();
	}
	// PlayerController
	else
	if (APlayerController* PC = Cast<APlayerController>(Object))
	{
		return PC->PlayerCameraManager->ViewTarget.POV.Location;
	}
	// Pawn
	else
	if (APawn* Pawn = Cast<APawn>(Object))
	{
		// PlayerController
		if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
		{
			return C->PlayerCameraManager->ViewTarget.POV.Location;
		}
	}
	return FVector::ZeroVector;
}

FVector FCsLibrary_Camera::GetLocation(UObject* Object, const int32& Rules)
{
// TODO: Add Rules
	return GetLocation(Object);
}

FVector FCsLibrary_Camera::GetLocationChecked(const FString& Context, UObject* Object)
{
	checkf(Object, TEXT("%s: Object is NULL."), *Context);

	// Try to get camera through the object

	// ICsGetCameraComponent
	if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
	{
		UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
		return Camera->GetComponentLocation();
	}
	// PlayerController
	else
	if (APlayerController* PC = Cast<APlayerController>(Object))
	{
		return PC->PlayerCameraManager->ViewTarget.POV.Location;
	}
	// Pawn
	else
	if (APawn* Pawn = Cast<APawn>(Object))
	{
		// PlayerController
		if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
		{
			return C->PlayerCameraManager->ViewTarget.POV.Location;
		}
		else
		{
			checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		}
	}
	checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
	return FVector::ZeroVector;
}

FVector FCsLibrary_Camera::GetLocationChecked(UObject* Object)
{
	using namespace NCsLibraryCameraCached;

	const FString& Context = Str::GetLocationChecked;

	return GetLocationChecked(Context, Object);
}

#pragma endregion Location

// Rotation
#pragma region

FRotator FCsLibrary_Camera::GetRotation(UObject* Object)
{
	checkf(Object, TEXT("FCsLibrary_Camera::GetRotation: Object is NULL."));

	// Try to get camera through the object

	// ICsGetCameraComponent
	if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
	{
		UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
		return Camera->GetComponentRotation();
	}
	// PlayerController
	else
	if (APlayerController* PC = Cast<APlayerController>(Object))
	{
		return PC->PlayerCameraManager->ViewTarget.POV.Rotation;
	}
	// Pawn
	else
	if (APawn* Pawn = Cast<APawn>(Object))
	{
		// PlayerController
		if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
		{
			return C->PlayerCameraManager->ViewTarget.POV.Rotation;
		}
	}
	return FRotator::ZeroRotator;
}

FRotator FCsLibrary_Camera::GetRotation(UObject* Object, const int32& Rules)
{
	return NCsRotationRules::GetRotation(GetRotation(Object), Rules);
}

FRotator FCsLibrary_Camera::GetRotationChecked(const FString& Context, UObject* Object)
{
	checkf(Object, TEXT("%s: Object is NULL."), *Context);

	// Try to get camera through the object

	// ICsGetCameraComponent
	if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
	{
		UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
		return Camera->GetComponentRotation();
	}
	// PlayerController
	else
	if (APlayerController* PC = Cast<APlayerController>(Object))
	{
		return PC->PlayerCameraManager->ViewTarget.POV.Rotation;
	}
	// Pawn
	else
	if (APawn* Pawn = Cast<APawn>(Object))
	{
		// PlayerController
		if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
		{
			return C->PlayerCameraManager->ViewTarget.POV.Rotation;
		}
		else
		{
			checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		}
	}
	checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
	return FRotator::ZeroRotator;
}

FRotator FCsLibrary_Camera::GetRotationChecked(UObject* Object)
{
	using namespace NCsLibraryCameraCached;

	const FString& Context = Str::GetRotationChecked;

	return GetRotationChecked(Context, Object);
}

FRotator FCsLibrary_Camera::GetRotationChecked(const FString& Context, UObject* Object, const int32& Rules)
{
	return NCsRotationRules::GetRotation(GetRotationChecked(Context, Object), Rules);
}

FRotator FCsLibrary_Camera::GetRotationChecked(UObject* Object, const int32& Rules)
{
	using namespace NCsLibraryCameraCached;

	const FString& Context = Str::GetRotationChecked;

	return GetRotationChecked(Context, Object, Rules);
}

#pragma endregion Rotation