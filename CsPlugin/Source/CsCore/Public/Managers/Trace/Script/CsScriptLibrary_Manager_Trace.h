// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Collision/CsTypes_Collision.h"
// Trace
#include "Managers/Trace/CsTraceRequest.h"

#include "CsScriptLibrary_Manager_Trace.generated.h"

class AActor;
class UCapsuleComponent;

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Trace : public UObject
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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Request"))
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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Trace", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Start,End,Channel,ActorsToIgnore", DisplayName = "LineTraceSingleByChannel"))
	static bool LineTraceSingleByChannel(const FString& Context, UObject* WorldContextObject, const FVector& Start, const FVector& End, const TEnumAsByte<ECollisionChannel>& Channel, bool bTraceComplex, bool bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit);

#pragma endregion Line

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
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Params"))
	static bool SweepByCapsuleComponent(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, FCsTraceResponse& OutResponse);


	//static bool DoesSweepbyCapsuleComponentAgainstObject(const FString& Context, UObject* WorldContextObject, UCapsuleComponent* CapsuleComponent, const FCsCollisionQueryParams& Params, UObject* Object, FCsTraceResponse* OutResponse);

#pragma endregion Capsule
};