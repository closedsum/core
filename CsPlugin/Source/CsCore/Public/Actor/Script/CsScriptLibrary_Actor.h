// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Movement.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_Actor.generated.h"

class AActor;
class USceneComponent;

UCLASS()
class CSCORE_API UCsScriptLibrary_Actor : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Set the RootComponent for an Actor.
	*
	* @param Context	The calling context.
	* @param Actor
	* @param Component
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static void SetRootComponent(const FString& Context, AActor* Actor, USceneComponent* Component);

	/**
	* Sets the value of Role without causing other side effects to this instance.
	*
	* @param Context	The calling context.
	* @param Actor
	* @param Role
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,Role"))
	static void SetRole(const FString& Context, AActor* Actor, const ENetRole& Role);

// Get
#pragma region
public:

	/**
	* Get an Actor with the given Tag (checks AActor->Tags)
	* NOTE: Find the FIRST Actor the given Tag.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tag
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tag"))
	static AActor* GetByTag(const FString& Context, UObject* WorldContextObject, const FName& Tag);

	/**
	* Get an Actor with the given Name.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static AActor* GetByName(const FString& Context, UObject* WorldContextObject, const FName& Name);

	/**
	* Get an Actor with the given Label.
	* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
	*		  Actor found in the search will be returned.
	*		- Only valid in Editor.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Label"))
	static AActor* GetByLabel(const FString& Context, UObject* WorldContextObject, const FString& Label);

#pragma endregion Get

// Move
#pragma region
public:

	/**
	* Move an Object via interpolation (i.e. an simple easing function) with the given Params.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Params				Information describing how to interpolate the Object.
	* return					Handle to the movement coroutine.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static FCsRoutineHandle MoveByInterp(const FString& Context, UObject* WorldContextObject, UPARAM(ref) FCsMoveByInterp_Params& Params);

#pragma endregion Move

// Material
#pragma region
public:

	/**
	* Set the Material at the given Index for the RootComponent, of type UPrimitiveComponent, on Actor.
	*
	* @param Context	The calling context.
	* @param Actor		Actor whose RootComponent would have the Material set at Index.
	* @param Material
	* @param Index
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Index"))
	static void SetMaterial(const FString& Context, AActor* Actor, UMaterialInterface* Material, const int32& Index);

	/**
	* Set the Materials for the RootComponent, of type UPrimitiveComponent, on Actor.
	*
	* @param Context	The calling context.
	* @param Actor		Actor whose RootComponent would have the Material set at Index.
	* @param Materials
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static void SetMaterials(const FString& Context, AActor* Actor, const TArray<UMaterialInterface*>& Materials);

#pragma endregion Material

// Spawn
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Path"))
	static AActor* SpawnBySoftObjectPath(const FString& Context, UObject* WorldContextObject, const FSoftObjectPath& Path);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Path"))
	static AActor* SpawnByStringPath(const FString& Context, UObject* WorldContextObject, const FString& Path);

#pragma endregion Spawn
};