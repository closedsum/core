// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_ScriptableActor.generated.h"

class AActor;

UCLASS()
class CSJS_API UCsScriptLibrary_ScriptableActor : public UObject
{
	GENERATED_UCLASS_BODY()

// Interface
#pragma region
public:

	/**
	* Get the Scriptable Actor Info from Actor
	*  Actors MUST implement the interface: ICsScriptableActor.
	* 
	* @param Context	The calling context.
	* @param Actor
	* @param OutInfo	(out)
	* return			Whether the Scriptable Actor Info was successfully retrieved or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Actor|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,OutInfo"))
	static bool GetScriptableActorInfo(const FString& Context, const AActor* Actor, FCsScriptableActorInfo& OutInfo);

#pragma endregion Interface

// Get
#pragma region
public:

	/**
	* Get all Scriptable Actors.
	*  Actors MUST implement the interface: ICsScriptableActor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param OutActors		(out)
	* return				Whether GetAll was executed successfully or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Actor|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetAll(const FString& Context, const UObject* WorldContextObject, TArray<AActor*>& OutActors);

	/**
	* Get an Scriptable Actor with the given Tag (checks AActor->Tags)
	*  Actor MUST implement the interface: ICsScriptableActor.
	* NOTE: Find the FIRST Actor the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Actor|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tag"))
	static AActor* GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag);

	/**
	* Get a list of Scriptable Actors with the given Tag (checks AActor->Tags).
	*  Actors MUST implement the interface: ICsScriptableActor.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutActors		(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Actor|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<AActor*>& OutActors);

	/**
	* Get an Scriptable Actor with the given Name.
	*  Actor MUST implement the interface: ICsScriptableActor.
	* 
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Actor|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static AActor* GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name);

	/**
	* Get an Scriptable Actor with the given Label.
	*  Actor MUST implement the interface: ICsScriptableActor.
	* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
	*		  Actor found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsJs|Library|Actor|Scriptable", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Label"))
	static AActor* GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label);

#pragma endregion Get
};