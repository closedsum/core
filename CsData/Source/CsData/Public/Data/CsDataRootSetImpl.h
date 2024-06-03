// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Interfaces
#include "Data/CsGetDataRootSet.h"

#include "CsDataRootSetImpl.generated.h"

class UDataTable;

UCLASS(Blueprintable)
class CSDATA_API UCsDataRootSetImpl : public UObject,
									  public ICsGetDataRootSet
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Root", meta = (DisplayName = "Core: DataRootSet"))
	FCsDataRootSet Core_DataRootSet;

// ICsGetDataRootSet
#pragma region
public:

	FORCEINLINE const FCsDataRootSet& GetCsDataRootSet() const
	{
		return Core_DataRootSet;
	}

#pragma endregion ICsGetDataRootSet

#if WITH_EDITOR

	void AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable);
	void AddDataTable(const FName& Entryname, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames);

#endif // #if WITH_EDITOR

	// Editor
#pragma region
#if WITH_EDITOR
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;

#endif // #if WITH_EDITOR
#pragma endregion Editor

};