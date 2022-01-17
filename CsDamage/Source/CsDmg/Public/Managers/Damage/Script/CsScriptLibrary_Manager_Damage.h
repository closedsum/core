// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Damage.generated.h"

UCLASS()
class CSDMG_API UCsScriptLibrary_Manager_Damage : public UObject
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
	UFUNCTION(BlueprintPure, Category = "CsCore|Library|Managers/Damage", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,DataName,HitResult"))
	static bool ProcessData(const FString& Context, const UObject* WorldContextObject, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

#pragma endregion Data
};