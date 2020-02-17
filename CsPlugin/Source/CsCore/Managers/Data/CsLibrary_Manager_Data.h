// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "CsLibrary_Manager_Data.generated.h"

class UDataTable;

UCLASS()
class CSCORE_API UCsLibrary_Manager_Data : public UObject
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
	* @param WorldContextObject
	* @param TableName
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "TableName"))
	static UDataTable* GetDataTable(const UObject* WorldContextObject, const FName& TableName);

	/**
	*
	*
	* @param WorldContextObject
	* @param Path
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject"))
	static UDataTable* GetDataTableByPath(const UObject* WorldContextObject, const FSoftObjectPath& Path);

	/**
	*
	*
	* @param WorldContextObject
	* @param SoftObject
	* return					DataTable
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Data", meta = (WorldContext = "WorldContextObject"))
	static UDataTable* GetDataTableBySoftObject(const UObject* WorldContextObject, TSoftObjectPtr<UDataTable> SoftObject);

#pragma endregion DataTable

#pragma endregion Get
};