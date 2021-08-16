// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Damage.generated.h"
#pragma once

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

// Data
#pragma region
public:

	/**
	* 
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Data
	* @param Instigator
	* @param Causer
	* @param HitResult
	*/
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Managers/Damage", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,HitResult"))
	static bool ProcessData(const FString& Context, const UObject* WorldContextObject, UObject* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

#pragma endregion Data
};