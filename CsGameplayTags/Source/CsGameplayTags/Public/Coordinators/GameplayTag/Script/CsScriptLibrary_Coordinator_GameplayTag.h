// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Coordinators/GameplayTag/CsTypes_Coordinator_GameplayTag.h"

#include "CsScriptLibrary_Coordinator_GameplayTag.generated.h"

class UCsCoordinator_GameplayTag;

UCLASS()
class CSGAMEPLAYTAGS_API UCsScriptLibrary_Coordinator_GameplayTag : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	/**
	* Get Coordinator_GameplayTag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* return				Coordinator_GameplayTag
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinator|GameplayTag", meta = (DisplayName = "Coordinator GameplayTag: Get", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsCoordinator_GameplayTag* Get(const FString& Context, const UObject* WorldContextObject);

	/**
	* Get Coordinator_GameplayTag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutSuccess		(out)
	* return				Coordinator_GameplayTag
	*/
	UFUNCTION(BlueprintPure, Category = "CsGameplayTags|Library|Coordinator|GameplayTag", meta = (DisplayName = "Coordinator GameplayTag: Get (Checked)", WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context"))
	static UCsCoordinator_GameplayTag* GetChecked(const FString& Context, const UObject* WorldContextObject, bool& OutSuccess);

#pragma endregion Get

public:

	/**
	* Broadcast a GameplayTagEvent routed to the appropriated Group. 
	*  Some values may be optional (i.e. Flag, Value, ... etc).
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Group				The route / "group" to direct the GameplayTag Event.
	* @param Info				GameplayTag Event to broadcast.
	* return					Whether the info was broadcasted or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsGameplayTags|Library|Coordinator|GameplayTag", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Group,Event"))
	static bool BroadcastGameplayTagEvent(const FString& Context, const UObject* WorldContextObject, const FECsGameplayTagCoordinatorGroup& Group, const  FCsGameplayTagEvent& Event);

	/**
	* Broadcast a GameplayTagEvent routed to the Group: GameInstance.
	*  Some values may be optional (i.e. Flag, Value, ... etc).
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Event				GameplayTag Event to broadcast.
	* return					Whether the info was broadcasted or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsGameplayTags|Library|Coordinator|GameplayTag", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "Context,Tag"))
	static bool BroadcastGameplayTag_GameInstance(const FString& Context, const UObject* WorldContextObject, const FGameplayTag& Tag);
};