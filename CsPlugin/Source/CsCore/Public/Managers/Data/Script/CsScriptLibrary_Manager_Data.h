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

	// Data
#pragma region
public:

	/**
	* Get a Data by SoftObjectPath.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param EntryName			Row Name in the master Data list.
	* return					Data as UObject.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,EntryName"))
	static UObject* GetDataObject(const FString& Context, const UObject* WorldContextObject, const FName& EntryName);

	/**
	* Get a Data by SoftObjectPath.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Path				Soft path to a data.
	* return					Data as UObject.
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Path"))
	static UObject* GetDataObjectByPath(const FString& Context, const UObject* ContextObject, const FSoftObjectPath& Path);

#pragma endregion Data

	// DataTable
#pragma region
public:

	/**
	* Get a DataTable by EntryName.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param EntryName			Row Name in the master DataTable list.
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,EntryName"))
	static UDataTable* GetDataTable(const FString& Context, const UObject* WorldContextObject, const FName& EntryName);

	/**
	* Get a DataTable by SoftObjectPath.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param Path				Soft path to a data table.
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "Context,Path"))
	static UDataTable* GetDataTableByPath(const FString& Context, const UObject* WorldContextObject, const FSoftObjectPath& Path);

	/**
	* Get a DataTable by SoftObjectPtr.
	*
	* @param Context			The calling context.
	* @param WorldContextObject	Object that contains a reference to a World (GetWorld() is Valid).
	* @param SoftObject			Soft reference to a data table.
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