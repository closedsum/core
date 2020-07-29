// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Data/CsDataRootSet.h"

#include "CsDataRootSetImpl.generated.h"

class UDataTable;

UCLASS(Blueprintable)
class CSCORE_API UCsDataRootSetImpl : public UObject,
									  public ICsDataRootSet
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* Datas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* DataTables;

#if WITH_EDITOR

	void AddDataTable(const TSoftObjectPtr<UDataTable>& InDataTable);
	void AddDataTable(const TSoftObjectPtr<UDataTable>& InDataTable, const TSet<FName>& RowNames);

	void AddDataTables(const TSet<TSoftObjectPtr<UDataTable>>& InDataTables);
	void AddDataTables(const TMap<TSoftObjectPtr<UDataTable>, TSet<FName>>& RowNamesByDataTableMap);

#endif // #if WITH_EDITOR

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* Payloads;

// ICsDataRootSet
#pragma region
public:

	FORCEINLINE UDataTable* GetDatas() const
	{
		return Datas;
	}

	FORCEINLINE UDataTable* GetDataTables() const
	{
		return DataTables;
	}

	FORCEINLINE UDataTable* GetPayloads() const
	{
		return Payloads;
	}

#pragma endregion ICsDataRootSet

	// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor

};