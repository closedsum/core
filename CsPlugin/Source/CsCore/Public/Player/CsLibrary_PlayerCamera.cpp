// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Player/CsLibrary_PlayerCamera.h"
#include "CsCore.h"

// Library
#include "Player/CsLibrary_Player.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

namespace NCsPlayer
{
	namespace NCamera
	{
		#define PlayerControllerLibrary NCsPlayer::NController::FLibrary
		#define ObjectLibrary NCsObject::FLibrary
		#define MathLibrary NCsMath::FLibrary

		bool FLibrary::IsValidChecked(const FString& Context, const FViewTargetTransitionParams& TransitionParams)
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TransitionParams.BlendTime, 0.0f)
			checkf(TransitionParams.BlendFunction != EViewTargetBlendFunction::VTBlend_MAX, TEXT("%s: TransitionParams.BlendFunction == EViewTargetBlendFunction::VTBlend_MAX is NOT Valid."), *Context);
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(TransitionParams.BlendExp, 0.0f)
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const FViewTargetTransitionParams& TransitionParams, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TransitionParams.BlendTime, 0.0f)

			if (TransitionParams.BlendFunction == EViewTargetBlendFunction::VTBlend_MAX)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TransitionParams.BlendFunction == EViewTargetBlendFunction::VTBlend_MAX is NOT Valid."), *Context));
				return false;
			}
			
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(TransitionParams.BlendExp, 0.0f)
			return true;
		}

		// Get
		#pragma region

		APlayerCameraManager* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);

			checkf(PC->PlayerCameraManager, TEXT("%s: Player Controller: %s has NO Player Camera Manager."), *Context, *(PC->GetName()));

			return PC->PlayerCameraManager;
		}

		APlayerCameraManager* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId))
			{
				if (!PC->PlayerCameraManager)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player Controller: %s has NO Player Camera Manager."), *Context, *(PC->GetName())));
				}
				return PC->PlayerCameraManager;
			}
			return nullptr;
		}

		APlayerCameraManager* FLibrary::GetChecked(const FString& Context, const APawn* Pawn)
		{
			CS_IS_PENDING_KILL_CHECKED(Pawn)

			AController* Controller = Pawn->GetController();

			checkf(Controller, TEXT("%s: %s does NOT have a controller."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn));

			APlayerController* PC = Cast<APlayerController>(Controller);

			checkf(PC, TEXT("%s: %s does NOT have a controller of type: APlayerController."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn));

			APlayerCameraManager* PCM = PC->PlayerCameraManager;

			checkf(PCM, TEXT("%s: Player Controller: %s has NO Player Camera Manager."), *Context, *(PC->GetName()));
			return PCM;
		}

		APlayerCameraManager* FLibrary::GetSafe(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PENDING_KILL_RET_NULL(Pawn)

			AController* Controller = Pawn->GetController();

			if (!Controller)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT have a controller."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn)));
				return nullptr;
			}

			APlayerController* PC = Cast<APlayerController>(Controller);

			if (!PC)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT have a controller of type: APlayerController."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn)));
				return nullptr;
			}

			APlayerCameraManager* PCM = PC->PlayerCameraManager;

			if (!PCM)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Player Controller: %s has NO Player Camera Manager."), *Context, *(PC->GetName())));
				return nullptr;
			}
			return PCM;
		}

		#pragma endregion Get

		// Orientation
		#pragma region

		FVector3f FLibrary::GetActorLocationChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			APlayerCameraManager* PCM = GetChecked(Context, WorldContext, ControllerId);

			return MathLibrary::Convert(Cast<AActor>(PCM)->GetActorLocation());
		}

		FVector3f FLibrary::GetLocationChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
			return MathLibrary::Convert(GetChecked(Context, WorldContext, ControllerId)->GetCameraLocation());
		}

		void FLibrary::GetLocationAndRotationChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FVector3f& OutLocation, FRotator3f& OutRotation)
		{
			APlayerCameraManager* PCM = GetChecked(Context, WorldContext, ControllerId);

			OutLocation = MathLibrary::Convert(PCM->GetCameraLocation());
			OutRotation = MathLibrary::Convert(PCM->GetCameraRotation());
		}

		void FLibrary::GetLocationAndDirectionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FVector3f& OutLocation, FVector3f& OutDirection)
		{
			APlayerCameraManager* PCM = GetChecked(Context, WorldContext, ControllerId);

			OutLocation  = MathLibrary::Convert(PCM->GetCameraLocation());
			OutDirection = MathLibrary::Convert(PCM->GetCameraRotation().Vector());
		}

		#pragma endregion Orientation

		// View Target
		#pragma region

		void FLibrary::SetViewTargetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams /*=FViewTargetTransitionParams()*/)
		{
			CS_IS_PENDING_KILL_CHECKED(NewViewTarget)
			check(IsValidChecked(Context, TransitionParams));

		#if UE_BUILD_SHIPPING
			GetChecked(Context, WorldContext, ControllerId)->SetViewTarget(NewViewTarget, TransitionParams);
		#else
			APlayerCameraManager* PCM = GetChecked(Context, WorldContext, ControllerId);
			APlayerController* PC	  = PCM->PCOwner.Get();

			checkf(ObjectLibrary::IsValidObject(PC), TEXT("%s: PlayerCameraManager associated with ControllerId: %d has an Invalid reference to a PlayerController."), *Context, ControllerId);

			PCM->SetViewTarget(NewViewTarget, TransitionParams);
		#endif // #if UE_BUILD_SHIPPING
		}

		bool FLibrary::SetSafeViewTarget(const FString& Context, const UObject* WorldContext, const int32& ControllerId, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams /*=FViewTargetTransitionParams()*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PENDING_KILL(NewViewTarget)
			
			if (!IsValid(Context, TransitionParams, Log))
				return false;

			APlayerCameraManager* PCM = GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PCM)
				return false;

			APlayerController* PC = PCM->PCOwner.Get();

			if (!ObjectLibrary::IsValidObject(PC))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerCameraManager associated with ControllerId: %d has an Invalid reference to a PlayerController."), *Context, ControllerId));
				return false;
			}
			PCM->SetViewTarget(NewViewTarget, TransitionParams);
			return true;
		}

		void FLibrary::SetViewTargetChecked(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams /*=FViewTargetTransitionParams()*/)
		{
			CS_IS_PENDING_KILL_CHECKED(NewViewTarget)
			check(IsValidChecked(Context, TransitionParams));

		#if UE_BUILD_SHIPPING
			GetChecked(Context, Pawn)->SetViewTarget(NewViewTarget, TransitionParams);
		#else
			APlayerCameraManager* PCM = GetChecked(Context, Pawn);
			APlayerController* PC	  = PCM->PCOwner.Get();

			checkf(ObjectLibrary::IsValidObject(PC), TEXT("%s: PlayerCameraManager associated with %s has an Invalid reference to a PlayerController."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn));

			PCM->SetViewTarget(NewViewTarget, TransitionParams);
		#endif // #if UE_BUILD_SHIPPING
		}

		bool FLibrary::SetSafeViewTarget(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams /*=FViewTargetTransitionParams()*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PENDING_KILL(NewViewTarget)
			
			if (!IsValid(Context, TransitionParams, Log))
				return false;

			APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log);

			if (!PCM)
				return false;

			APlayerController* PC = PCM->PCOwner.Get();

			if (!ObjectLibrary::IsValidObject(PC))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: PlayerCameraManager associated with %s has an Invalid reference to a PlayerController."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn)));
				return false;
			}
			PCM->SetViewTarget(NewViewTarget, TransitionParams);
			return true;
		}

		AActor* FLibrary::GetViewTargetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId)
		{
		#if UE_BUILD_SHIPPING
			AActor* VT = GetChecked(Context, WorldContext, ControllerId)->GetViewTarget();

			checkf(VT, TEXT("%s: Failed to get View Target for PlayerCameraManager associated with ControllerId: %d."), *Context, ControllerId);
			return VT;
		#else
			return GetChecked(Context, WorldContext, ControllerId)->GetViewTarget();
		#endif // #if UE_BUILD_SHIPPING
		}

		AActor* FLibrary::GetSafeViewTarget(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			APlayerCameraManager* PCM = GetSafe(Context, WorldContext, ControllerId, Log);

			if (!PCM)
				return nullptr;

			AActor* VT = PCM->GetViewTarget();

			if (!VT)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get View Target for PlayerCameraManager associated with ControllerId: %d."), *Context, ControllerId));
				return nullptr;
			}
			return VT;
		}

		AActor* FLibrary::GetViewTargetChecked(const FString& Context, const APawn* Pawn)
		{
			APlayerCameraManager* PCM = GetChecked(Context, Pawn);

			checkf(PCM, TEXT("%s: %s has NO Player Camera Manager."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn));

			AActor* VT = PCM->GetViewTarget();

			checkf(VT, TEXT("%s: Failed to get View Target for PlayerCameraManager associated with %s."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn));
			return VT;
		}

		AActor* FLibrary::GetSafeViewTarget(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log);

			if (!PCM)
				return nullptr;

			AActor* VT = PCM->GetViewTarget();

			if (!VT)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get View Target for PlayerCameraManager associated with %s."), *Context, *ObjectLibrary::PrintNameAndClass(Pawn)));
				return nullptr;
			}
			return VT;
		}

		FVector FLibrary::GetViewTargetOffsetChecked(const FString& Context, const APawn* Pawn)
		{
			return GetChecked(Context, Pawn)->ViewTargetOffset;
		}

		FVector FLibrary::GetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutSuccess = false;

			if (APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log))
			{
				OutSuccess = true;
				return PCM->ViewTargetOffset;
			}
			return FVector::ZeroVector;
		}

		void FLibrary::SetViewTargetOffsetChecked(const FString& Context, const APawn* Pawn, const FVector& Offset)
		{
			GetChecked(Context, Pawn)->ViewTargetOffset = Offset;
		}

		bool FLibrary::SetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, const FVector& Offset, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutSuccess = false;

			if (APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log))
			{
				PCM->ViewTargetOffset = Offset;
				OutSuccess = true;
				return true;
			}
			return false;
		}

		#pragma endregion View Target

		// FOV
		#pragma region
		
		void FLibrary::SetFOVChecked(const FString& Context, const APawn* Pawn, const float& FOV)
		{
			CS_IS_FLOAT_GREATER_THAN_CHECKED(FOV, 0.0f)
			CS_IS_FLOAT_LESS_THAN_CHECKED(FOV, 180.0f)

			GetChecked(Context, Pawn)->SetFOV(FOV);
		}

		bool FLibrary::SetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log))
			{
				CS_IS_FLOAT_GREATER_THAN(FOV, 0.0f)
				CS_IS_FLOAT_LESS_THAN(FOV, 180.0f)

				PCM->SetFOV(FOV);
				return true;
			}
			return false;
		}

		float FLibrary::GetFOVChecked(const FString& Context, const APawn* Pawn)
		{
			return GetChecked(Context, Pawn)->GetFOVAngle();
		}

		float FLibrary::GetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			OutSuccess = false;

			if (APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log))
			{
				OutSuccess = true;
				return PCM->GetFOVAngle();
			}
			return 0.0f;
		}

		#pragma endregion FOV

		#undef PlayerControllerLibrary
		#undef ObjectLibrary
		#undef MathLibrary
	}
}