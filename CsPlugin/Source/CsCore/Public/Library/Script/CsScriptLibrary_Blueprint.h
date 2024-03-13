// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Actor/CsActor.h"
#include "Types/CsTypes_Texture.h"
#include "Types/CsTypes_Sound.h"
#include "Types/CsTypes_SkeletalMesh.h"
// Actor
#include "Actor/CsActor.h"
// Data
#include "Data/CsDataTable.h"

#include "CsScriptLibrary_Blueprint.generated.h"

class UBlueprint;
class UBlueprintGeneratedClass;
class USoundCue;
class UDataTable;
class USkeletalMesh;
class UTexture;

UCLASS()
class CSCORE_API UCsScriptLibrary_Blueprint : public UObject
{
	GENERATED_UCLASS_BODY()

// Load
#pragma region
public:

	/**
	* Load a Blueprint at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		SoftObjectPath to the Blueprint to load.
	* return			Blueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Blueprint", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlueprint* LoadBySoftObjectPath(const FString& Context, const FSoftObjectPath& Path);

	/**
	* Load a Blueprint at the given Path.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the Blueprint to load.
	* return			Blueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Blueprint", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlueprint* LoadByStringPath(const FString& Context, const FString& Path);

	/**
	* Load a Blueprint at the given Path and get the UClass (Generated Class) associated with the Blueprint.
	* 
	* @param Context	The calling context.
	* @param Path		FString path to the Blueprint to load.
	* return			Blueprint
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Blueprint", meta = (AutoCreateRefTerm = "Context,Path"))
	static UBlueprintGeneratedClass* LoadAndGetGeneratedClassByStringPath(const FString& Context, const FString& Path);

	/**
	* Load a Blueprint at the given Path and get the Default Object associated with the Blueprint.
	*
	* @param Context	The calling context.
	* @param Path		FString path to the Blueprint to load.
	* return			Default Object
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Blueprint", meta = (AutoCreateRefTerm = "Context,Path"))
	static UObject* LoadAndGetDefaultObjectByStringPath(const FString& Context, const FString& Path);

#pragma endregion Load

// Get
#pragma region
public:

	/**
	* Get the UClass (Generated Class) associated with the Blueprint.
	* 
	* @param Context	The calling context.
	* @param Blueprint	
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Blueprint", meta = (AutoCreateRefTerm = "Context"))
	static UBlueprintGeneratedClass* GetGeneratedClass(const FString& Context, UBlueprint* Blueprint);

	/**
	* Get the Default Object associated with the Blueprint.
	*
	* @param Context	The calling context.
	* @param Blueprint
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Blueprint", meta = (AutoCreateRefTerm = "Context"))
	static UObject* GetDefaultObject(const FString& Context, UBlueprint* Blueprint);

#pragma endregion Get

// TSoftObjectPtr
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get Name", BlueprintThreadSafe))
	static FString GetName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get FName", BlueprintThreadSafe))
	static FName GetFName_SoftObjectPtr(const TSoftObjectPtr<UObject>& SoftObject);

// Container
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (SoundCue)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static USoundCue* Conv_CsSoundCueToInternal(const FCsSoundCue& Container);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (DataTable)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static UDataTable* Conv_CsDataTableToInternal(const FCsDataTable& Container);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (Actor)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static AActor* Conv_CsActorToInternal(const FCsActor& Container);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (Class)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static UClass* Conv_CsActorToClass(const FCsActor& Container);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (SubclassOf)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static TSubclassOf<AActor> Conv_CsActorToSubclassOf(const FCsActor& Container);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (SkeletalMesh)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static USkeletalMesh* Conv_CsSkeletalMeshToInternal(const FCsSkeletalMesh& Container);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get (Texture)", CompactNodeTitle = "->", BlueprintThreadSafe))
	static UTexture* Conv_CsTextureToInternal(const FCsTexture& Container);

#pragma endregion Container

#pragma endregion TSoftObjectPtr

// TSoftClassPtr
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get Name", BlueprintThreadSafe))
	static FString GetName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass);

	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Blueprint", meta = (DisplayName = "Get FName", BlueprintThreadSafe))
	static FName GetFName_SoftClassPtr(const TSoftClassPtr<UObject>& SoftClass);

#pragma endregion TSoftClassPtr
};