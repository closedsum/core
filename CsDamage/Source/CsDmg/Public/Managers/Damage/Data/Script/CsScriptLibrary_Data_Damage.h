// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Data
#include "Managers/Damage/Data/Point/CsData_DamagePointImplSlice.h"

#include "CsScriptLibrary_Data_Damage.generated.h"

UCLASS()
class CSDMG_API UCsScriptLibrary_Data_Damage : public UObject
{ 
	GENERATED_UCLASS_BODY() 

public:

	/**
	* Constructs a data that implements the interface: NCsDamage::NData::IData and
	* is of type: NCsDamage::NData::NPoint::FImplSlice
	* 
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @oaram Slice
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Damage", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name,Slice"))
	static bool Construct_Point(const FString& Context, const UObject* WorldContextObject, const FString& Name, const FCsData_DamagePointImplSlice& Slice);

	/**
	* Constructs a data that implements the interface: NCsDamage::NData::IData with Name.
	* Adds slice of type: NCsDamage::NData::NPoint::FImplSlice.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Name				Name of the data.
	* @param Object
	* return					Whether the data was successful created.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Data|Damage", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static bool ConstructFromObject_Point(const FString& Context, const UObject* WorldContextObject, const FString& Name, UObject* Object);
};