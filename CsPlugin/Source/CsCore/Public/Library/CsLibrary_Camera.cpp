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
		//CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPlayerControllerChecked);
		//CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPlayerStateChecked);
		//CSCORE_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsLibrary_Player, GetFirstLocalPawnChecked);
	}
}

FVector FCsLibrary_Camera::GetLocation(UObject* Object)
{
	// Try to get camera through the object
	if (Object)
	{
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
	}
	return FVector::ZeroVector;
}

FVector FCsLibrary_Camera::GetLocation(UObject* Object, const int32& Rules)
{
	// Try to get camera through the object
	if (Object)
	{
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
	}
	return FVector::ZeroVector;
}

FVector FCsLibrary_Camera::GetLocationChecked(const FString& Context, UObject* Object)
{
	// Try to get camera through the object
	if (Object)
	{
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
		else
		{
			checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		}
	}
	// TODO: For now assert
	else
	{
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component."), *Context);
	}
	return FVector::ZeroVector;
}

FVector FCsLibrary_Camera::GetLocationChecked(UObject* Object)
{
	return FVector::ZeroVector;
}