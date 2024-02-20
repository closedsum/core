// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_PlayerCamera.generated.h"

class APlayerCameraManager;
class APawn;

UCLASS()
class CSCORE_API UCsScriptLibrary_PlayerCamera : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get the PlayerCameraManager associated with PlayerController with ControllerId.
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* @param ControllerId
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static APlayerCameraManager* Get(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId);

	/**
	* Get the PlayerCameraManager associated with PlayerController with ControllerId.
	*
	* @param Context			The calling context
	* @param WorldContextObject
	* @param ControllerId
	* @param OutSuccess			(out)
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static APlayerCameraManager* GetChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess);

	/**
	* Get the PlayerCameraManager associated with Pawn.
	*
	* @param Context			The calling context
	* @param Pawn
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (AutoCreateRefTerm = "Context"))
	static APlayerCameraManager* GetByPawn(const FString& Context, const APawn* Pawn);

	/**
	* Get the PlayerCameraManager associated with Pawn.
	*
	* @param Context			The calling context
	* @param Pawn
	* @param OutSuccess			(out)
	* return					PlayerCameraManager
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get by Pawn (Checked)", AutoCreateRefTerm = "Context,ControllerId"))
	static APlayerCameraManager* GetByPawnChecked(const FString& Context, const APawn* Pawn, bool& OutSuccess);

#pragma endregion Get

// Orientation
#pragma region
public:

#pragma endregion Orientation

// View Target
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Target by Pawn", AutoCreateRefTerm = "Context,TransitionParams"))
	static bool SetViewTargetByPawn(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Target by Pawn (Checked)", AutoCreateRefTerm = "Context,TransitionParams"))
	static void SetViewTargetByPawnChecked(const FString& Context, const APawn* Pawn, AActor* NewViewTarget, const FViewTargetTransitionParams& TransitionParams, bool& OutSuccess);

#pragma endregion View Target

// FOV
#pragma region
public:

	/** 
	* Locks the FOV to the given value for the Camera associated with PlayerController with Id: ControllerId.
	* Unlock with UnlockFOV.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		The Id for the Player Controller.
	* @param FOV				New full FOV angle to use, in degrees.
	* return					Whether the FOV was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,FOV"))
	static bool SetFOV(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& FOV);

	/** 
	* Locks the FOV to the given value for the Camera associated with PlayerController with Id: ControllerId.
	* Unlock with UnlockFOV.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		The Id for the Player Controller.
	* @param FOV				New full FOV angle to use, in degrees.
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set FOV (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,FOV"))
	static void SetFOVChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& FOV, bool& OutSuccess);

	/** 
	* Locks the FOV to the given value for the Camera associated with Pawn.
	* Pawn MUST possessed by a PlayerController.
	* Unlock with UnlockFOV.
	* 
	* @param Context	The calling context.
	* @param Pawn		Pawn possessed by a PlayerController.
	* @param FOV		New full FOV angle to use, in degrees.
	* return			Whether the FOV was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set FOV by Pawn", AutoCreateRefTerm = "Context,FOV"))
	static bool SetFOVByPawn(const FString& Context, const APawn* Pawn, const float& FOV);

	/** 
	* Locks the FOV to the given value for the Camera associated with Pawn.
	* Pawn MUST possessed by a PlayerController.
	* Unlock with UnlockFOV.
	* 
	* @param Context		The calling context.
	* @param Pawn			Pawn possessed by a PlayerController.
	* @param FOV			New full FOV angle to use, in degrees.
	* @param OutSuccess		(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set FOV by Pawn (Checked)", AutoCreateRefTerm = "Context,FOV"))
	static void SetFOVByPawnChecked(const FString& Context, const APawn* Pawn, const float& FOV, bool& OutSuccess);

	/** 
	* Returns the Camera associated with PlayerController with Id: ControllerId current full FOV angle, in degrees.
	* 
	* @param Context				The calling context
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId			The Id for the Player Controller.
	* @param OutSuccess				(out)
	* return						FOV angle in degrees.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static float GetFOV(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess);

	/** 
	* Returns the Camera associated with PlayerController with Id: ControllerId current full FOV angle, in degrees.
	* 
	* @param Context				The calling context
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId			The Id for the Player Controller.
	* @param OutSuccess				(out)
	* return						FOV angle in degrees.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get FOV (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId"))
	static float GetFOVChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, bool& OutSuccess);

	/** 
	* Returns the Camera associated with Pawn current full FOV angle, in degrees.
	* Pawn MUST possessed by a PlayerController.
	* 
	* @param Context		The calling context
	* @param Pawn			Pawn possessed by a PlayerController.
	* @param OutSuccess		(out)
	* return				FOV angle in degrees.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get FOV by Pawn", AutoCreateRefTerm = "Context"))
	static float GetFOVByPawn(const FString& Context, const APawn* Pawn, bool& OutSuccess);

	/** 
	* Returns the Camera associated with Pawn current full FOV angle, in degrees.
	* Pawn MUST possessed by a PlayerController.
	* 
	* @param Context		The calling context
	* @param Pawn			Pawn possessed by a PlayerController.
	* @param OutSuccess		(out)
	* return				FOV angle in degrees.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Get FOV by Pawn (Checked)", AutoCreateRefTerm = "Context"))
	static float GetFOVByPawnChecked(const FString& Context, const APawn* Pawn, bool& OutSuccess);

#pragma endregion FOV

// View
#pragma region
public:

	// Pitch

		// Min

	/** 
	* Set Minimum view pitch, in degrees for the Camera associated with PlayerController with Id: ControllerId.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		The Id for the Player Controller.
	* @param MinPitch			
	* return					Whether the minimum view pitch was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,MinPitch"))
	static bool SetViewPitchMin(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MinPitch);

	/** 
	* Set Minimum view pitch, in degrees for the Camera associated with PlayerController with Id: ControllerId.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		The Id for the Player Controller.
	* @param MinPitch			
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Pitch Min (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,MinPitch"))
	static void SetViewPitchMinChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MinPitch, bool& OutSuccess);

	/** 
	* Set Minimum view pitch, in degrees for the Camera associated with Pawn.
	* Pawn MUST possessed by a PlayerController.
	* 
	* @param Context	The calling context.
	* @param Pawn		Pawn possessed by a PlayerController.
	* @param MinPitch	
	* return			Whether the minimum view pitch was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Pitch Min by Pawn", AutoCreateRefTerm = "Context,MinPitch"))
	static bool SetViewPitchMinByPawn(const FString& Context, const APawn* Pawn, const float& MinPitch);

	/** 
	* Set Minimum view pitch, in degrees for the Camera associated with Pawn.
	* Pawn MUST possessed by a PlayerController.
	* 
	* @param Context		The calling context.
	* @param Pawn			Pawn possessed by a PlayerController.
	* @param MinPitch		
	* @param OutSuccess		(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Pitch Min by Pawn (Checked)", AutoCreateRefTerm = "Context,MinPitch"))
	static void SetViewPitchMinByPawnChecked(const FString& Context, const APawn* Pawn, const float& MinPitch, bool& OutSuccess);

			// Max

	/** 
	* Set Maximum view pitch, in degrees for the Camera associated with PlayerController with Id: ControllerId.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		The Id for the Player Controller.
	* @param MaxPitch			
	* return					Whether the maximum view pitch was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,MaxPitch"))
	static bool SetViewPitchMax(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MaxPitch);

	/** 
	* Set Maximum view pitch, in degrees for the Camera associated with PlayerController with Id: ControllerId.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param ControllerId		The Id for the Player Controller.
	* @param MaxPitch			
	* @param OutSuccess			(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Pitch Max (Checked)", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,ControllerId,MaxPitch"))
	static void SetViewPitchMaxChecked(const FString& Context, const UObject* WorldContextObject, const int32& ControllerId, const float& MaxPitch, bool& OutSuccess);

	/** 
	* Set Maximum view pitch, in degrees for the Camera associated with Pawn.
	* Pawn MUST possessed by a PlayerController.
	* 
	* @param Context	The calling context.
	* @param Pawn		Pawn possessed by a PlayerController.
	* @param MaxPitch	
	* return			Whether the maximum view pitch was set or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Pitch Max by Pawn", AutoCreateRefTerm = "Context,MaxPitch"))
	static bool SetViewPitchMaxByPawn(const FString& Context, const APawn* Pawn, const float& MaxPitch);

	/** 
	* Set Maximum view pitch, in degrees for the Camera associated with Pawn.
	* Pawn MUST possessed by a PlayerController.
	* 
	* @param Context		The calling context.
	* @param Pawn			Pawn possessed by a PlayerController.
	* @param MaxPitch		
	* @param OutSuccess		(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Player|Camera", meta = (DisplayName = "Set View Pitch Max by Pawn (Checked)", AutoCreateRefTerm = "Context,MaxPitch"))
	static void SetViewPitchMaxByPawnChecked(const FString& Context, const APawn* Pawn, const float& MaxPitch, bool& OutSuccess);

#pragma endregion View
};