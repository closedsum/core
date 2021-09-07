// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "World"))
	FSoftObjectPath ExitMap;

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
		EntryMap(),
		TransitionEntryToMainMap(),
		MainMap(),
		ExitMap(),
		StartupPayload(NAME_None),
		Datas(nullptr),
		DataTables(nullptr),
		Payloads(nullptr)
	{
	}

#if WITH_EDITOR

	void AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, void(*Log)(const FString&) = &FCsLog::Warning);
	void AddDataTable(const FName& Entryname, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames, void(*Log)(const FString&) = &FCsLog::Warning);

#endif // #if WITH_EDITOR

	enum class EMap : uint8
	{
		Entry,
		Main
	};

	bool IsPersistentLevel(UObject* WorldContext, const EMap& Type) const;
};