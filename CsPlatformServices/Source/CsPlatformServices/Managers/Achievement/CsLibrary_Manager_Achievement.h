// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Managers/Achievement/CsTypes_Achievement.h"
#include "CsLibrary_Manager_Achievement.generated.h"

// Delegates
#pragma region

// Complete
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsLibraryManagerAchievement_OnComplete, bool, WasSuccessful, const FECsAchievement&, Achievement);
// Progress
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsLibraryManagerAchievement_OnProgress, bool, WasSuccessful, const FECsAchievement&, Achievement, const float&, Progress);

#pragma endregion Delegates


UCLASS()
class CSPLATFORMSERVICES_API UCsLibrary_Manager_Achievement : public UObject
{
	GENERATED_UCLASS_BODY()

// Complete
#pragma region
public:

	/**
	* 
	*
	* @param WorldContextObject
	* @param Achievement
	*/
	UFUNCTION(BlueprintCallable, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static void Complete(const UObject* WorldContextObject, const FECsAchievement& Achievement);

	/**
	*
	*
	* @param WorldContextObject
	* @param Event / Delegate
	*/
	UFUNCTION(BlueprintCallable, Category = "Respawn|Library|Manager|Achievement", meta = (DisplayName = "BindToEvent: OnComplete", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static void BindToEvent_OnComplete(const UObject* WorldContextObject, const FECsAchievement& Achievement, UPARAM(DisplayName = "Event") FCsLibraryManagerAchievement_OnComplete Delegate);

	/**
	*
	*
	* @param WorldContextObject
	* @param Achievement
	* return						If the Achievement is already complete.
	*/
	UFUNCTION(BlueprintPure, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static bool IsCompleted(const UObject* WorldContextObject, const FECsAchievement& Achievement);

	/**
	*
	*
	* @param WorldContextObject
	* return						Number of achievements already completed.
	*/
	UFUNCTION(BlueprintPure, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject"))
	static int32 GetNumCompleted(const UObject* WorldContextObject);

#pragma endregion Complete

// Reset
#pragma region
public:

	/**
	*
	*
	* @param WorldContextObject
	* @param Achievement
	*/
	UFUNCTION(BlueprintCallable, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement,Percent"))
	static void Reset(const UObject* WorldContextObject, const FECsAchievement& Achievement, const float& Percent = 0);

	/**
	*
	*
	* @param WorldContextObject
	*/
	UFUNCTION(BlueprintCallable, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject"))
	static void ResetAll(const UObject* WorldContextObject);

#pragma endregion Reset

// Progress
#pragma region
public:

	/**
	*
	*
	* @param WorldContextObject
	* @param Achievement
	* return						Progress completed. Value range is dictated by ProgressType.
	*/
	UFUNCTION(BlueprintPure, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static float GetProgress(const UObject* WorldContextObject, const FECsAchievement& Achievement);

	/**
	*
	*
	* @param WorldContextObject
	* return						Total progress completed [0-1] as a percent.
	*/
	UFUNCTION(BlueprintPure, Category = "Respawn|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject"))
	static float GetTotalProgress(const UObject* WorldContextObject);

#pragma endregion Progress
};