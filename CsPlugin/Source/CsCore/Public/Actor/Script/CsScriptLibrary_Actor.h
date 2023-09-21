// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Movement.h"
#include "Coroutine/CsRoutineHandle.h"

#include "CsScriptLibrary_Actor.generated.h"

class AActor;
class UActorComponent;
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
	* Get an Actor with the given Tags (checks AActor->Tags)
	* NOTE: Find the FIRST Actor the given Tags.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* return				Actor
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Tags"))
	static AActor* GetByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags);

	/**
	* Get a list of Actors with the given Tag (checks AActor->Tags).
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Tags
	* @param OutActors		(out)
	* return				Whether any actors were found with Tags.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static bool GetAnyByTags(const FString& Context, UObject* WorldContextObject, const TArray<FName>& Tags, TArray<AActor*>& OutActors);

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

// Component
#pragma region
public:

	/**
	* Get a Component with Tag from Actor.
	*
	* @param Context	The calling context.
	* @param Actor
	* @param Tag
	* return			Component
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,Tag"))
	static UActorComponent* GetComponentByTag(const FString& Context, const AActor* Actor, const FName& Tag);

#pragma endregion Component

// Visibility
#pragma region
public:

	/**
	* Set an Actor to be hidden or visible with option to set the visibility of any attached children.
	* 
	* @param Context				The calling context.
	* @param Actor
	* @param NewHidden				True = Hide. False = Visible.
	* @param ApplyToAttachChildren
	* return						Whether the visibility change was successfully set.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,NewHidden,ApplyToAttachChildren"))
	static bool SetHiddenInGame(const FString& Context, AActor* Actor, const bool& NewHidden, const bool& ApplyToAttachChildren);

#pragma endregion Visibility

// Orientation
#pragma region

	/** 
	* Returns the quaternion of the RootComponent of this Actor.
	* 
	* @param Context	The calling context
	* @param Actor
	* return			Quat
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static FQuat GetQuat(const FString& Context, AActor* Actor);

	/**
	* Rotate an Actor by Pitch in Degrees
	* 
	* @param Context	The calling context.
	* @param Actor
	* @param Degrees
	* return			Whether the Rotation was performed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,Degrees,Teleport"))
	static bool RotateByPitch(const FString& Context, AActor* Actor, const double& Degrees, const ETeleportType& Teleport = ETeleportType::None);

	/**
	* Rotate an Actor by Yaw in Degrees
	* 
	* @param Context	The calling context.
	* @param Actor
	* @param Degrees
	* return			Whether the Rotation was performed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,Degrees,Teleport"))
	static bool RotateByYaw(const FString& Context, AActor* Actor, const double& Degrees, const ETeleportType& Teleport = ETeleportType::None);

	/**
	* Rotate an Actor by Roll in Degrees
	* 
	* @param Context	The calling context.
	* @param Actor
	* @param Degrees
	* return			Whether the Rotation was performed or not.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,Degrees,Teleport"))
	static bool RotateByRoll(const FString& Context, AActor* Actor, const double& Degrees, const ETeleportType& Teleport = ETeleportType::None);

#pragma endregion Orientation

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
	static FCsRoutineHandle MoveByInterp(const FString& Context, const UObject* WorldContextObject, const FCsMoveByInterp_Params& Params);

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
	static AActor* SpawnBySoftObjectPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path);

	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Path"))
	static AActor* SpawnByStringPath(const FString& Context, const UObject* WorldContextObject, const FString& Path);

#pragma endregion Spawn

// Distance
#pragma region
public:

	/**
	* Get the distance squared between A and B.
	*
	* @param Context	The calling context.
	* @param A
	* @param B
	* return			Distance squared between A and B.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static float GetDistanceSq(const FString& Context, AActor* A, AActor* B);

	/**
	* Get the distance squared 2D between A and B.
	*
	* @param Context	The calling context.
	* @param A
	* @param B
	* return			Distance squared 2D between A and B.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static float GetDistanceSq2D(const FString& Context, AActor* A, AActor* B);

	/**
	* Check if the distance squared 2D between A and B is Less Than or Equal to R^2 (R squared).
	*
	* @param Context	The calling context.
	* @param A
	* @param B
	* @param R
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context,R"))
	static bool IsDistanceSq2D_LessThanOrEqual(const FString& Context, AActor* A, AActor* B, const float& R);

#pragma endregion Distance

// Normal
#pragma region
public:

	/**
	* Gets the normal between A and B (AB or B - A)
	* 
	* @param Context		The calling context.
	* @param A
	* @param B
	* @param OutNormal
	* @param OutDistanceSq	The distance squared between A and B
	* @param OutDistance
	* return				Whether the normal was found successfully.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static bool GetNormalAtoB(const FString& Context, AActor* A, AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance);

	/**
	* Gets the normal 2d between A and B (AB or B - A)
	*
	* @param Context		The calling context.
	* @param A
	* @param B
	* @param OutNormal
	* @param OutDistanceSq	The distance squared between A and B
	* @param OutDistance
	* return				Whether the normal was found successfully.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Actor", meta = (AutoCreateRefTerm = "Context"))
	static bool GetNormal2DAtoB(const FString& Context, AActor* A, AActor* B, FVector3f& OutNormal, float& OutDistanceSq, float& OutDistance);

#pragma endregion Normal
};