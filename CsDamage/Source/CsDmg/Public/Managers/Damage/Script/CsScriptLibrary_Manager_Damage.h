// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

#include "CsScriptLibrary_Manager_Damage.generated.h"

UCLASS()
class CSDMG_API UCsScriptLibrary_Manager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

// Data
#pragma region
public:

	/**
	* Get the Data as UObject (implements interface: DataType (NCsDamage::NData::IData)) associated with Type.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type			Damage type.
	* return				Data that implements the interface: DataType (NCsDamage::NData::IData).
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Manager|Damage", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Type"))
	static UObject* GetData(const FString& Context, const UObject* WorldContextObject, const FECsDamageData& Type);

	/**
	* Get the Data as UObject (implements interface: DataType (NCsDamage::NData::IData)) associated with Type.
	*
	* @param Context		The calling context.
	* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Type			Damage type.
	* return				Data that implements the interface: DataType (NCsDamage::NData::IData).
	*/
	UFUNCTION(BlueprintCallable, Category = "CImpl|Library|Manager|Damage", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Name"))
	static UObject* GetDataByName(const FString& Context, const UObject* WorldContextObject, const FName& Name);

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