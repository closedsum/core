// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Engine/EngineTypes.h"

#include "CsScriptLibrary_Manager_Trace.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates

class AActor;

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Trace : public UObject
{
	GENERATED_UCLASS_BODY()

// Line
#pragma region

	/**
	* Does a collision trace along the given line and returns the first hit encountered.
	*
	* @param WorldContext	World context
	* @param Start			Start of line segment.
	* @param End			End of line segment.
	* @param bTraceComplex	True to test against complex collision, false to test against simplified collision.
	* @param Channel		
	* @param OutHit			Properties of the trace hit.
	* @return				True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|Trace", meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", DisplayName = "LineTraceSingleByChannel"))
	static bool LineTraceSingleByChannel(UObject* WorldContextObject, const FVector Start, const FVector End, const TEnumAsByte<ECollisionChannel>& Channel, bool bTraceComplex, bool bIgnoreSelf, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit);

#pragma endregion Line
};