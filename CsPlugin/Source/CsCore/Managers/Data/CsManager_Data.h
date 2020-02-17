// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Load.h"
#include "CsManager_Data.generated.h"

class UDataTable;
class ICsData;
class UScriptStruct;

UCLASS(Blueprintable)
class UCsManager_Data : public UObject
{
	GENERATED_UCLASS_BODY()

// UObject Interface
#pragma region

#pragma endregion UObject Interface

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* Datas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* DataTables;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* Payloads;

	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* Datas_Test;
	*/

protected:

	TMap<FName, FCsDataEntry_Data*> DataEntryMap;
	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Loaded;

	TMap<FName, ICsData*> DataMap_Loaded;

	TMap<FName, FCsDataEntry_DataTable*> DataTableEntryMap;
	TMap<FName, TMap<FName, FCsDataEntry_DataTable*>> DataTableEntryRowMap_Loaded;

	TMap<FName, UDataTable*> DataTableMap_Loaded;
	TMap<FName, TMap<FName, uint8*>> DataTableRowMap_Loaded;

	TMap<FName, FCsPayload*> PayloadMap;
	TMap<FName, FCsPayload*> PayloadMap_Loaded;

public:

	void GenerateMaps();

// Load
#pragma region
public:

	void LoadPayload(const FName& PayloadName);

	// DataTable
#pragma region
public:

	UDataTable* LoadDataTable(const FName& TableName);

	uint8* LoadDataTableRow(const FName& TableName, const FName& RowName);

	bool IsLoadedDataTableRow(const FName& TableName, const FName& RowName);

#pragma endregion DataTable

#pragma endregion Load

// Get
#pragma region
public:

	UDataTable* GetDataTable(const FName& TableName);

	uint8* GetDataTableRow(const FName& TableName, const FName& RowName);

#pragma endregion Get

// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor
};