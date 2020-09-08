// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsDataRootSet.generated.h"

class UDataTable;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDataRootSet
{
	GENERATED_USTRUCT_BODY()

	// Flow
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath EntryMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath TransitionEntryToMainMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath MainMap;

#pragma endregion Flow

// Startup
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StartupPayload;

#pragma endregion Startup

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* Datas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DataTables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* Payloads;

	FCsDataRootSet() :
		StartupPayload(NAME_None),
		Datas(nullptr),
		DataTables(nullptr),
		Payloads(nullptr)
	{
	}

#if WITH_EDITOR

	void AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable);
	void AddDataTable(const FName& Entryname, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames);

#endif // #if WITH_EDITOR
};