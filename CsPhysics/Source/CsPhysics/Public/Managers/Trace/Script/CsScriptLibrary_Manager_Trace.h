// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Collision/CsTypes_Collision.h"
// Trace
#include "Managers/Trace/CsTraceRequest.h"

#include "CsScriptLibrary_Manager_Trace.generated.h"

class AActor;
class UCapsuleComponent;
class USkeletalMeshComponent;

UCLASS()
class CSPHYSICS_API UCsScriptLibrary_Manager_Trace : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Perform a trace with the given Request.
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Request
	* @param OutResponse		(out)
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Request"))
	static void Trace(const FString& Context, const UObject* WorldContextObject, const FCsTraceRequest& Request, FCsTraceResponse& OutResponse);

// Line
#pragma region
public:

	/**
	* Does a collision trace along the given line and returns the first hit encountered.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Start				Start of line segment.
	* @param End				End of line segment.
	* @param bTraceComplex		True to test against complex collision, false to test against simplified collision.
	* @param Channel		
	* @param OutHit				Properties of the trace hit.
	* @return					True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Start,End,Channel,ActorsToIgnore"))
	static bool LineTraceSingleByChannel(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const TEnumAsByte<ECollisionChannel>& Channel, bool bTraceComplex, bool bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit);

#pragma endregion Line

// Sphere
#pragma region
public:

	/**
	* Sweeps a sphere along the given line and returns the first blocking hit encountered.
	* This trace finds the objects that RESPONDS to the given Collision Channel
	* 
	* @param Context			The calling context
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Start				Start of line segment.
	* @param End				End of line segment.
	* @param Radius				Radius of the sphere to sweep
	* @param Channel
	* @param bTraceComplex		True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf
	* @param OutHit				Properties of the trace hit.
	* @return					True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta= (bIgnoreSelf="true", WorldContext = "WorldContextObject", AutoCreateRefTerm="Context,Start,End,Radius,Channel,sbTraceComplex,bIgnoreSelf,ActorsToIgnore"))
	static bool SphereTraceSingleByChannel(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const float& Radius, const TEnumAsByte<ECollisionChannel>& Channel, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit);

	/**
	* Sweeps a sphere along the given Bone location for Component  and returns the first blocking hit encountered.
	* This trace finds the objects that RESPONDS to the given Collision Channel
	* 
	* @param Context			The calling context
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Component			
	* @param BoneOrSocket		Bone or Socket on SkeletalMesh for Component (Component->GetSkeletalMeshAsset())
	* @param Radius				Radius of the sphere to sweep
	* @param Channel
	* @param bTraceComplex		True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf
	* @param OutHit				Properties of the trace hit.
	* @return					True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta= (bIgnoreSelf="true", WorldContext = "WorldContextObject", AutoCreateRefTerm="Context,BoneRoSocket,Radius,Channel,bTraceComplex,bIgnoreSelf,ActorsToIgnore"))
	static bool SphereTraceSingleByChannelAtBone(const FString& Context, UObject* WorldContextObject, const USkeletalMeshComponent* Component, const FName& BoneOrSocket, const float& Radius, const TEnumAsByte<ECollisionChannel>& Channel, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit);

	/**
	* Sweeps a sphere along the given line and returns the first blocking hit encountered.
	* This trace finds the objects that RESPONDS to the given Collision Channel
	* 
	* @param Context			The calling context
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Start				Start of line segment.
	* @param End				End of line segment.
	* @param Radius				Radius of the sphere to sweep
	* @param ObjectTypes
	* @param bTraceComplex		True to test against complex collision, false to test against simplified collision.
	* @param bIgnoreSelf
	* @param OutHit				Properties of the trace hit.
	* @return					True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta= (bIgnoreSelf="true", WorldContext = "WorldContextObject", AutoCreateRefTerm="Context,Start,End,Radius,ObjectTypes,bTraceComplex,bIgnoreSelf,ActorsToIgnore"))
	static bool SphereTraceSingleByObjectType(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const float& Radius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, const bool& bTraceComplex, const bool& bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit);

#pragma endregion Sphere

// Capsule
#pragma region
public:

	/**
	* Perform a sweep using the collision information from the CapsuleComponent.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Component
	* @param Params
	* @param Log			(optional)
	* @param
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static bool SweepByCapsuleComponent(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, FCsTraceResponse& OutResponse);

	/**
	* Perform a sweep using the collision information from the CapsuleComponent and check if Object
	* has been hit or overlapped.
	* NOTE: OutResponse may include other objects (not Object) that have been hit or overlapped from the sweep.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Component
	* @param Params
	* @param Log			(optional)
	* @param
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static bool SweepByCapsuleComponentAgainstObject(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, UObject* Object, FCsTraceResponse& OutResponse);

	/**
	* Perform a sweep using the collision information from the CapsuleComponent and check if Object
	* has been hit or overlapped.
	* NOTE: OutResponse ONLY includes a hit or overlaps from the sweep with Object.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Component
	* @param Params
	* @param Log			(optional)
	* @param
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPhyics|Library|Manager|Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static bool SweepByCapsuleComponentAgainstObjectOnly(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, UObject* Object, FCsTraceResponse& OutResponse);

#pragma endregion Capsule
};