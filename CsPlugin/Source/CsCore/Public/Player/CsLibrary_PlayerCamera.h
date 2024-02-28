// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Camera/PlayerCameraManager.h"
// Log
#include "Utility/CsLog.h"

class APlayerCameraManager;
class AActor;
class APawn;

namespace NCsPlayer
{
	namespace NCamera
	{
		struct CSCORE_API FLibrary
		{
		public:

			static bool IsValidChecked(const FString& Context, const FViewTargetTransitionParams& TransitionParams);

			static bool IsValid(const FString& Context, const FViewTargetTransitionParams& TransitionParams, void(*Log)(const FString&) = &FCsLog::Warning);

		// Get
		#pragma region
		public:

			/**
			* Get the PlayerCameraManager associated with PlayerController with ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* return				PlayerCameraManager
			*/
			static APlayerCameraManager* GetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			/**
			* Safely get the PlayerCameraManager associated with PlayerController with ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param Log			(optional)
			* return				PlayerCameraManager
			*/
			static APlayerCameraManager* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static APlayerCameraManager* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				APlayerCameraManager* PCM = GetSafe(Context, WorldContext, ControllerId, Log);
				OutSuccess				  = PCM != nullptr;
				return PCM;
			}

			/**
			* Get the PlayerCameraManager associated with Pawn.
			* 
			* @param Context	The calling context.
			* @param Pawn		Object that contains a reference to a Controller of type: APlayerController.
			* return			PlayerCameraManager
			*/
			static APlayerCameraManager* GetChecked(const FString& Context, const APawn* Pawn);

			/**
			* Safely get the PlayerCameraManager associated with Pawn.
			* 
			* @param Context	The calling context.
			* @param Pawn		Object that contains a reference to a Controller of type: APlayerController.
			* @param Log		(optional)
			* return			PlayerCameraManager
			*/
			static APlayerCameraManager* GetSafe(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static APlayerCameraManager* GetSafe(const FString& Context, const APawn* Pawn, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				APlayerCameraManager* PCM = GetSafe(Context, Pawn, Log);
				OutSuccess				  = PCM != nullptr;
				return PCM;
			}

		#pragma endregion Get

		// Orientation
		#pragma region
		public:

			/**
			* Get the PlayerCameraManager's location which is associated with PlayerController with
			* ControllerId.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* return				Location for PlayerCameraManager.
			*/
			static FVector3f GetActorLocationChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			/**
			* Get the Camera location which is associated with PlayerController with
			* ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* return				Location for Camera.
			*/
			static FVector3f GetLocationChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			/**
			* Get the Camera location and rotation which is associated with PlayerController with
			* ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param OutLocation	(out) Camera's current location.
			* @param OutRotation	(out) Camera's current rotation.
			*/
			static void GetLocationAndRotationChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FVector3f& OutLocation, FRotator3f& OutRotation);

			/**
			* Get the Camera location and rotation which is associated with PlayerController with
			* ControllerId.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ControllerId
			* @param OutLocation	(out) Camera's current location.
			* @param OutDirection	(out) Camera's current direction.
			*/
			static void GetLocationAndDirectionChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, FVector3f& OutLocation, FVector3f& OutDirection);

		#pragma endregion Orientation

		// View Target
		#pragma region
		public:

			static void SetViewTargetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams = FViewTargetTransitionParams());

			static bool SetSafeViewTarget(const FString& Context, const UObject* WorldContext, const int32& ControllerId, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams = FViewTargetTransitionParams(), void(*Log)(const FString&) = &FCsLog::Warning);

			static void SetViewTargetChecked(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams = FViewTargetTransitionParams());

			static bool SetSafeViewTarget(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeViewTarget(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeViewTarget(Context, Pawn, NewViewTarget, TransitionParams, Log);
				return OutSuccess;
			}

			/**
			* Set the View Target on the Player Camera Manager of the Player Controller associated with Pawn to Pawn.
			*  NOTE: Pawn MUST have a Controller of type: APlayerController.
			* 
			* @param Context	The calling context.
			* @param Pawn
			*/
			static void SetViewTargetChecked(const FString& Context, APawn* Pawn);

			static AActor* GetViewTargetChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static AActor* GetSafeViewTarget(const FString& Context, const UObject* WorldContext, const int32& ControllerId, void(*Log)(const FString&) = &FCsLog::Warning);

			static AActor* GetViewTargetChecked(const FString& Context, const APawn* Pawn);

			static AActor* GetSafeViewTarget(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning);

			static FVector GetViewTargetOffsetChecked(const FString& Context, const APawn* Pawn);

			static FVector GetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static FVector GetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				bool OutSuccess = false;
				return GetSafeViewTargetOffset(Context, Pawn, OutSuccess, Log);
			}

			static void SetViewTargetOffsetChecked(const FString& Context, const APawn* Pawn, const FVector& Offset);

			static bool SetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, const FVector& Offset, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, const FVector& Offset, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				bool OutSuccess = false;
				return SetSafeViewTargetOffset(Context, Pawn, Offset, OutSuccess, Log);
			}

		#pragma endregion View Target

		// FOV
		#pragma region
		public:

			static void SetFOVChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV);

			static bool SetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeFOV(Context, WorldContext, ControllerId, FOV, Log);
				return OutSuccess;
			}

			static void SetFOVChecked(const FString& Context, const APawn* Pawn, const float& FOV);

			static bool SetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeFOV(Context, Pawn, FOV, Log);
				return OutSuccess;
			}

			static float GetFOVChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static float GetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static float GetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				bool OutSuccess = false;
				return GetSafeFOV(Context, WorldContext, ControllerId, FOV, OutSuccess, Log);
			}

			static float GetFOVChecked(const FString& Context, const APawn* Pawn);

			static float GetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static float GetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				bool OutSuccess = false;
				return GetSafeFOV(Context, Pawn, FOV, OutSuccess, Log);
			}

		#pragma endregion FOV

		// View
		#pragma region
		public:
	
			// Pitch

				// Min

			static void SetViewPitchMinChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MinPitch);

			static bool SetSafeViewPitchMin(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MinPitch, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeViewPitchMin(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MinPitch, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeViewPitchMin(Context, WorldContext, ControllerId, MinPitch, Log);
				return OutSuccess;
			}

			static void SetViewPitchMinChecked(const FString& Context, const APawn* Pawn, const float& MinPitch);

			static bool SetSafeViewPitchMin(const FString& Context, const APawn* Pawn, const float& MinPitch, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeViewPitchMin(const FString& Context, const APawn* Pawn, const float& MinPitch, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeViewPitchMin(Context, Pawn, MinPitch, Log);
				return OutSuccess;
			}

				// Max

			static void SetViewPitchMaxChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MaxPitch);

			static bool SetSafeViewPitchMax(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MaxPitch, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeViewPitchMax(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MaxPitch, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeViewPitchMax(Context, WorldContext, ControllerId, MaxPitch, Log);
				return OutSuccess;
			}

			static void SetViewPitchMaxChecked(const FString& Context, const APawn* Pawn, const float& MaxPitch);

			static bool SetSafeViewPitchMax(const FString& Context, const APawn* Pawn, const float& MaxPitch, void(*Log)(const FString&) = &FCsLog::Warning);
			FORCEINLINE static bool SetSafeViewPitchMax(const FString& Context, const APawn* Pawn, const float& MaxPitch, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SetSafeViewPitchMax(Context, Pawn, MaxPitch, Log);
				return OutSuccess;
			}

		#pragma endregion View
		};

		namespace NLocal
		{
			namespace NFirst
			{
				struct CSCORE_API FLibrary
				{
					/**
					* Set the View Target on the Player Camera Manager of the FIRST LOCAL Player Controller associated with Pawn to Pawn.
					*  NOTE: Pawn MUST have a Controller of type: APlayerController.
					* 
					* @param Context		The calling context.
					* @param WorldContext
					* @param Pawn
					*/
					static void SetViewTargetChecked(const FString& Context, const UObject* WorldContext, APawn* Pawn);
				};
			}
		}
	}
}