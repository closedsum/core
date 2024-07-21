// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Camera/PlayerCameraManager.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class APlayerCameraManager;
class AActor;
class APawn;
class APlayerController;

namespace NCsPlayer
{
	namespace NCamera
	{
		struct CSCORELIBRARY_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

		public:

			static bool IsValidChecked(const FString& Context, const FViewTargetTransitionParams& TransitionParams);

			static bool IsValid(const FString& Context, const FViewTargetTransitionParams& TransitionParams, LogLevel);

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
			static APlayerCameraManager* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel);
			FORCEINLINE static APlayerCameraManager* GetSafe(const FString& Context, const UObject* WorldContext, const int32& ControllerId, bool& OutSuccess, LogLevel)
			{
				APlayerCameraManager* PCM = GetSafe(Context, WorldContext, ControllerId, Log);
				OutSuccess				  = PCM != nullptr;
				return PCM;
			}

			/**
			* Get the PlayerCameraManager associated with Player Controller.
			* 
			* @param Context			The calling context.
			* @param PlayerController	
			* return					PlayerCameraManager
			*/
			static APlayerCameraManager* GetChecked(const FString& Context, APlayerController* PlayerController);

			/**
			* Safely get the PlayerCameraManager associated with Player Controller.
			* 
			* @param Context			The calling context.
			* @param PlayerController	
			* @param Log				(optional)
			* return					PlayerCameraManager
			*/
			static APlayerCameraManager* GetSafe(const FString& Context, APlayerController* PlayerController, LogLevel);

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
			static APlayerCameraManager* GetSafe(const FString& Context, const APawn* Pawn, LogLevel);
			FORCEINLINE static APlayerCameraManager* GetSafe(const FString& Context, const APawn* Pawn, bool& OutSuccess, LogLevel)
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

			static bool SetSafeViewTarget(const FString& Context, const UObject* WorldContext, const int32& ControllerId, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams = FViewTargetTransitionParams(), LogLevel);

			static void SetViewTargetChecked(const FString& Context, APlayerController* PlayerController, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams = FViewTargetTransitionParams());

			static bool SetSafeViewTarget(const FString& Context, APlayerController* PlayerController, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, LogLevel);
			FORCEINLINE static bool SetSafeViewTarget(const FString& Context, APlayerController* PlayerController, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeViewTarget(Context, PlayerController, NewViewTarget, TransitionParams, Log);
				return OutSuccess;
			}

			static void SetViewTargetChecked(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams = FViewTargetTransitionParams());

			static bool SetSafeViewTarget(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, LogLevel);
			FORCEINLINE static bool SetSafeViewTarget(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, bool& OutSuccess, LogLevel)
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

			static AActor* GetSafeViewTarget(const FString& Context, const UObject* WorldContext, const int32& ControllerId, LogLevel);

			static AActor* GetViewTargetChecked(const FString& Context, APlayerController* PlayerController);

			static AActor* GetViewTargetChecked(const FString& Context, const APawn* Pawn);

			static AActor* GetSafeViewTarget(const FString& Context, const APawn* Pawn, LogLevel);

			static FVector GetViewTargetOffsetChecked(const FString& Context, const APawn* Pawn);

			static FVector GetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, bool& OutSuccess, LogLevel);
			FORCEINLINE static FVector GetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, LogLevel)
			{
				bool OutSuccess = false;
				return GetSafeViewTargetOffset(Context, Pawn, OutSuccess, Log);
			}

			static void SetViewTargetOffsetChecked(const FString& Context, const APawn* Pawn, const FVector& Offset);

			static bool SetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, const FVector& Offset, bool& OutSuccess, LogLevel);
			FORCEINLINE static bool SetSafeViewTargetOffset(const FString& Context, const APawn* Pawn, const FVector& Offset, LogLevel)
			{
				bool OutSuccess = false;
				return SetSafeViewTargetOffset(Context, Pawn, Offset, OutSuccess, Log);
			}

		#pragma endregion View Target

		// FOV
		#pragma region
		public:

			static void SetFOVChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV);

			static bool SetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, LogLevel);
			FORCEINLINE static bool SetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeFOV(Context, WorldContext, ControllerId, FOV, Log);
				return OutSuccess;
			}

			static void SetFOVChecked(const FString& Context, const APawn* Pawn, const float& FOV);

			static bool SetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, LogLevel);
			FORCEINLINE static bool SetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeFOV(Context, Pawn, FOV, Log);
				return OutSuccess;
			}

			static float GetFOVChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId);

			static float GetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, bool& OutSuccess, LogLevel);
			FORCEINLINE static float GetSafeFOV(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& FOV, LogLevel)
			{
				bool OutSuccess = false;
				return GetSafeFOV(Context, WorldContext, ControllerId, FOV, OutSuccess, Log);
			}

			static float GetFOVChecked(const FString& Context, const APawn* Pawn);

			static float GetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess, LogLevel);
			FORCEINLINE static float GetSafeFOV(const FString& Context, const APawn* Pawn, const float& FOV, LogLevel)
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

			static bool SetSafeViewPitchMin(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MinPitch, LogLevel);
			FORCEINLINE static bool SetSafeViewPitchMin(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MinPitch, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeViewPitchMin(Context, WorldContext, ControllerId, MinPitch, Log);
				return OutSuccess;
			}

			static void SetViewPitchMinChecked(const FString& Context, const APawn* Pawn, const float& MinPitch);

			static bool SetSafeViewPitchMin(const FString& Context, const APawn* Pawn, const float& MinPitch, LogLevel);
			FORCEINLINE static bool SetSafeViewPitchMin(const FString& Context, const APawn* Pawn, const float& MinPitch, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeViewPitchMin(Context, Pawn, MinPitch, Log);
				return OutSuccess;
			}

				// Max

			static void SetViewPitchMaxChecked(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MaxPitch);

			static bool SetSafeViewPitchMax(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MaxPitch, LogLevel);
			FORCEINLINE static bool SetSafeViewPitchMax(const FString& Context, const UObject* WorldContext, const int32& ControllerId, const float& MaxPitch, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeViewPitchMax(Context, WorldContext, ControllerId, MaxPitch, Log);
				return OutSuccess;
			}

			static void SetViewPitchMaxChecked(const FString& Context, const APawn* Pawn, const float& MaxPitch);

			static bool SetSafeViewPitchMax(const FString& Context, const APawn* Pawn, const float& MaxPitch, LogLevel);
			FORCEINLINE static bool SetSafeViewPitchMax(const FString& Context, const APawn* Pawn, const float& MaxPitch, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SetSafeViewPitchMax(Context, Pawn, MaxPitch, Log);
				return OutSuccess;
			}

		#pragma endregion View

		#undef LogLevel
		};

		namespace NLocal
		{
			namespace NFirst
			{
				struct CSCORELIBRARY_API FLibrary
				{
				#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

				public:

					/**
					* Safely get the Player Camera Manager of the FIRST LOCAL Player Controller.
					* 
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param Log			(optional)
					* return				Player Camera Manager
					*/
					static APlayerCameraManager* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

					/**
					* Safely get the View Target on the Player Camera Manager of the FIRST LOCAL Player Controller.
					* 
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param Log			(optional)
					* return				View Target
					*/
					static AActor* GetSafeViewTarget(const FString& Context, const UObject* WorldContext, LogLevel);

					/**
					* Set the View Target on the Player Camera Manager of the FIRST LOCAL Player Controller to Pawn.
					*  NOTE: Pawn MUST have a Controller of type: APlayerController.
					* 
					* @param Context		The calling context.
					* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
					* @param Pawn
					*/
					static void SetViewTargetChecked(const FString& Context, const UObject* WorldContext, AActor* ViewTarget);

				#undef LogLevel
				};
			}
		}
	}
}

using CsPlayerCameraLibrary = NCsPlayer::NCamera::FLibrary;