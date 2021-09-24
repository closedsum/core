// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Managers/Achievement/CsTypes_Achievement.h"

#include "CsScriptLibrary_Manager_Achievement.generated.h"

// Delegates
#pragma region

// Complete
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCsScriptLibraryManagerAchievement_OnComplete, bool, WasSuccessful, const FECsAchievement&, Achievement);
// Progress
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FCsScriptLibraryManagerAchievement_OnProgress, bool, WasSuccessful, const FECsAchievement&, Achievement, const float&, Progress);

#pragma endregion Delegates


UCLASS()
class CSPLATFORMSERVICES_API UCsScriptLibrary_Manager_Achievement : public UObject
{
	GENERATED_UCLASS_BODY()

// Complete
#pragma region
public:

	/**
	* 
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Achievement
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Achievement"))
	static void Complete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement);

	/**
	*
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event / Delegate
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Achievement", meta = (DisplayName = "BindToEvent: OnComplete", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static void BindToEvent_OnComplete(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerAchievement_OnComplete Delegate);

	/**
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Achievement
	* return						If the Achievement is already complete.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static bool IsCompleted(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement);

	/**
	*
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* return						Number of achievements already completed.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject"))
	static int32 GetNumCompleted(const FString& Context, UObject* WorldContextObject);

#pragma endregion Complete

// Reset
#pragma region
public:

	/**
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Achievement
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement,Percent"))
	static void Reset(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement, const float& Percent = 0);

	/**
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject"))
	static void ResetAll(const FString& Context, UObject* WorldContextObject);

#pragma endregion Reset

// Progress
#pragma region
public:

	/**
	*
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param Achievement
	* return						Progress completed. Value range is dictated by ProgressType.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Achievement"))
	static float GetProgress(const FString& Context, UObject* WorldContextObject, const FECsAchievement& Achievement);

	/**
	*
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* return						Total progress completed [0-1] as a percent.
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Manager|Achievement", meta = (WorldContext = "WorldContextObject"))
	static float GetTotalProgress(const FString& Context, UObject* WorldContextObject);

#pragma endregion Progress
};