// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Sound.h"
#include "CsLibrary_Manager_AI_Sense.generated.h"

class AActor;

UCLASS()
class CSCORE_API UCsLibrary_Manager_AI_Sense : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Report Noise Event
	* @param WorldContext
	* @param EventType
	* @param Location
	* @param Loudness
	* @param Instigator
	* @param MaxRange
	* @param Tag
	*/
	UFUNCTION(BlueprintCallable, Category = "Library|Manager|AI|Sense", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "EventType,Location,Loudness,MaxRange,Tag"))
	static void ReportNoiseEvent(const UObject* WorldContextObject, const FECsNoiseEvent& EventType, const FVector& Location, const float& Loudness = 1.0f, AActor* Instigator = nullptr, const float& MaxRange = 0.0f, const FName& Tag = NAME_None);
};