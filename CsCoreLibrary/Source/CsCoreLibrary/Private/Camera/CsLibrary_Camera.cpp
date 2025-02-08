// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Camera/CsLibrary_Camera.h"

// Types
#include "CsMacro_Misc.h"
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Math_Library.h"
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
// Pawn
#include "GameFramework/Pawn.h"
// Camera
#include "Camera/CsGetCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
// Utility
#include "EngineUtils.h"
// World
#include "Engine/World.h"

// NCsCamera::FLibrary
//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_1(NCsCamera, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetLocation3f)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetLocation)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetLocation3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetLocationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetRotation3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetRotationChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetRotation3f)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetRotation)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetDirection3fChecked)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsCamera::FLibrary, GetDirectionChecked)
CS_END_CACHED_FUNCTION_NAME_NESTED_1

#pragma endregion Cached

namespace NCsCamera
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCamera::FLibrary, GetDirection3fChecked);
				CSCORELIBRARY_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCamera::FLibrary, GetDirectionChecked);
			}
		}
	}

	// Get
	#pragma region

	ACameraActor* FLibrary::GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
	{
		UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

		CS_IS_NAME_NONE_CHECKED(Tag)

	#if UE_BUILD_SHIPPING
		for (TActorIterator<ACameraActor> Itr(World); Itr; ++Itr)
		{
			ACameraActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				return A;
			}
		}
	#else
		ACameraActor* Actor = nullptr;
		
		for (TActorIterator<ACameraActor> Itr(World); Itr; ++Itr)
		{
			ACameraActor* A = *Itr;

			// Check is Valid and NOT getting destroyed
			if (!IsValid(A))
				continue;
			if (A->Tags.Contains(Tag))
			{
				if (!Actor)
				{
					Actor = A;
				}
				else
				{
					checkf(0, TEXT("%s: There are more than one Cameras with the Tag: %s."), *Context, *(Tag.ToString()));
				}
			}
		}

		if (Actor)
			return Actor;
	#endif // UE_BUILD_SHIPPING

		checkf(0, TEXT("%s: Failed to find Cameras with Tag: %s."), *Context, *(Tag.ToString()));
		return nullptr;
	}

	#pragma endregion Get

	// Is
	#pragma region
	
	bool FLibrary::IsCameraComponent(const UActorComponent* Component)
	{
		return Cast<UCameraComponent>(Component) != nullptr;
	}
		
	#pragma endregion Is

	// Spawn
	#pragma region

		ACameraActor* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const UCameraComponent* Component)
		{
			CS_IS_PENDING_KILL_CHECKED(Component)

			ACameraActor* Camera = CsWorldLibrary::SpawnChecked<ACameraActor>(Context, WorldContext);
			
			CopyChecked(Context, Component, Camera);
			return Camera;				
		}

	#pragma endregion Spawn

	// Copy
	#pragma region

		void FLibrary::CopyChecked(const FString& Context, const UCameraComponent* From, ACameraActor* To)
		{
			CS_IS_PENDING_KILL_CHECKED(From)
			CS_IS_PENDING_KILL_CHECKED(To)

			UCameraComponent* ToComponent = To->GetCameraComponent();

			To->Tags = From->ComponentTags;

			// Orientation
			To->SetActorLocationAndRotation(From->GetComponentLocation(), From->GetComponentQuat());
			To->SetActorScale3D(From->GetComponentScale());

			// Properties
			ToComponent->SetFieldOfView(From->FieldOfView);
			ToComponent->SetOrthoWidth(From->OrthoWidth);
			ToComponent->SetOrthoNearClipPlane(From->OrthoNearClipPlane);
			ToComponent->SetOrthoFarClipPlane(From->OrthoFarClipPlane);
			ToComponent->SetAspectRatio(From->AspectRatio);
			ToComponent->SetConstraintAspectRatio(From->bConstrainAspectRatio);
			ToComponent->SetUseFieldOfViewForLOD(From->bUseFieldOfViewForLOD);
			ToComponent->bLockToHmd = From->bLockToHmd;
			ToComponent->bUsePawnControlRotation = From->bUsePawnControlRotation;
			ToComponent->SetProjectionMode(From->ProjectionMode);
			ToComponent->SetPostProcessBlendWeight(From->PostProcessBlendWeight);
			ToComponent->PostProcessSettings = From->PostProcessSettings;

			// Visibility
			To->SetActorHiddenInGame(From->bHiddenInGame);
		}

	#pragma endregion Copy

	// Destroy
	#pragma region
	
		void FLibrary::SimulateDestroyChecked(const FString& Context, UCameraComponent* Component)
		{
			CS_IS_PENDING_KILL_CHECKED(Component)

			Component->SetVisibleFlag(false);
			Component->SetHiddenInGame(true);
			Component->SetComponentTickEnabled(false);
			Component->Deactivate();
			Component->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		}

		void FLibrary::SimulateDestroyByActorComponentChecked(const FString& Context, UActorComponent* Component)
		{
			SimulateDestroyChecked(Context, CS_CAST_CHECKED(Component, UActorComponent, UCameraComponent));
		}

	#pragma endregion Destroy

	// Location
	#pragma region

	FVector3f FLibrary::GetLocation3f(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLocation3f);

		CS_IS_PTR_NULL_CHECKED(Object)

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return CsMathLibrary::Convert(Camera->GetComponentLocation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return CsMathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Location);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return CsMathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Location);
			}
		}
		return FVector3f::ZeroVector;
	}

	FVector FLibrary::GetLocation(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLocation);

		CS_IS_PTR_NULL_CHECKED(Object)

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

	FVector3f FLibrary::GetLocation3f(UObject* Object, const int32& Rules)
	{
	// TODO: Add Rules
		return GetLocation3f(Object);
	}

	FVector FLibrary::GetLocation(UObject* Object, const int32& Rules)
	{
	// TODO: Add Rules
		return GetLocation(Object);
	}

	FVector3f FLibrary::GetLocation3fChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return CsMathLibrary::Convert(Camera->GetComponentLocation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return CsMathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Location);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return CsMathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Location);
			}
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
			}
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		return FVector3f::ZeroVector;
	}

	FVector3f FLibrary::GetLocation3fChecked(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLocation3fChecked);

		return GetLocation3fChecked(Context, Object);
	}

	FVector FLibrary::GetLocationChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

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

	FVector FLibrary::GetLocationChecked(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetLocationChecked);

		return GetLocationChecked(Context, Object);
	}

	#pragma endregion Location

	// Rotation
	#pragma region

	FRotator3f FLibrary::GetRotation3f(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotation3f);

		CS_IS_PTR_NULL_CHECKED(Object)

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return CsMathLibrary::Convert(Camera->GetComponentRotation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return CsMathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Rotation);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return CsMathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Rotation);
			}
		}
		return FRotator3f::ZeroRotator;
	}

	FRotator FLibrary::GetRotation(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotation);

		CS_IS_PTR_NULL_CHECKED(Object)

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

	FRotator3f FLibrary::GetRotation3f(UObject* Object, const int32& Rules)
	{
		return NCsRotationRules::GetRotation(GetRotation3f(Object), Rules);
	}

	FRotator FLibrary::GetRotation(UObject* Object, const int32& Rules)
	{
		return NCsRotationRules::GetRotation(GetRotation(Object), Rules);
	}

	FRotator3f FLibrary::GetRotation3fChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

		// Try to get camera through the object

		// ICsGetCameraComponent
		if (ICsGetCameraComponent* GetCameraComponent = Cast<ICsGetCameraComponent>(Object))
		{
			UCameraComponent* Camera = GetCameraComponent->GetCameraComponent();
			return CsMathLibrary::Convert(Camera->GetComponentRotation());
		}
		// PlayerController
		else
		if (APlayerController* PC = Cast<APlayerController>(Object))
		{
			return CsMathLibrary::Convert(PC->PlayerCameraManager->ViewTarget.POV.Rotation);
		}
		// Pawn
		else
		if (APawn* Pawn = Cast<APawn>(Object))
		{
			// PlayerController
			if (APlayerController* C = Cast<APlayerController>(Pawn->Controller))
			{
				return CsMathLibrary::Convert(C->PlayerCameraManager->ViewTarget.POV.Rotation);
			}
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
			}
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from Object: %s."), *Context, *(Object->GetName()));
		return FRotator3f::ZeroRotator;
	}

	FRotator3f FLibrary::GetRotation3fChecked(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotation3fChecked);

		return GetRotation3fChecked(Context, Object);
	}

	FRotator FLibrary::GetRotationChecked(const FString& Context, UObject* Object)
	{
		CS_IS_PTR_NULL_CHECKED(Object)

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

	FRotator FLibrary::GetRotationChecked(UObject* Object)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotationChecked);

		return GetRotationChecked(Context, Object);
	}

	FRotator3f FLibrary::GetRotation3fChecked(const FString& Context, UObject* Object, const int32& Rules)
	{
		return NCsRotationRules::GetRotationChecked(Context, GetRotation3fChecked(Context, Object), Rules);
	}

	FRotator3f FLibrary::GetRotation3fChecked(UObject* Object, const int32& Rules)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotation3fChecked);

		return GetRotation3fChecked(Context, Object, Rules);
	}

	FRotator FLibrary::GetRotationChecked(const FString& Context, UObject* Object, const int32& Rules)
	{
		return NCsRotationRules::GetRotationChecked(Context, GetRotationChecked(Context, Object), Rules);
	}

	FRotator FLibrary::GetRotationChecked(UObject* Object, const int32& Rules)
	{
		CS_SET_CONTEXT_AS_FUNCTION_NAME(GetRotationChecked);

		return GetRotationChecked(Context, Object, Rules);
	}

	#pragma endregion Rotation
}