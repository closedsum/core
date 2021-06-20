// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"

#include "CsScriptLibrary_Manager_Data.generated.h"

class UDataTable;

UCLASS()
class CSCORE_API UCsScriptLibrary_Manager_Data : public UObject
{
	GENERATED_UCLASS_BODY()

// Get
#pragma region
public:

	// DataTable
#pragma region
public:

	/**
	* 
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param TableName
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,TableName"))
	static UDataTable* GetDataTable(const FString& Context, const UObject* WorldContextObject, const FName& TableName);

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Path
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Path"))
	static UDataTable* GetDataTableByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path);

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param SoftObject
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context"))
	static UDataTable* GetDataTableBySoftObject(const FString& Context, const UObject* WorldContextObject, TSoftObjectPtr<UDataTable> SoftObject);
	
#pragma endregion DataTable

#pragma endregion Get

// Add
#pragma region
public:

	// Data
#pragma region
public:

	/**
	*
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param EntryName
	* @param Data				Object that implements the interface: ICsData and
	*							Data->_getIData() returns an object that implements the interface: NCsData::IData
	* return					Whether Data was successful added to an internal list in Manager_Data.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject"))
	static bool SafeAddDataObject_Loaded(const FString& Context, const UObject* WorldContextObject, const FName& EntryName, UObject* Data);

#pragma endregion Data

#pragma endregion Add
};