// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Engine
#include "Engine/DataTable.h"
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

	/** Damage Datas */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> Damages;

	FCsDataRootSet() :
		EntryMap(),
		TransitionEntryToMainMap(),
		MainMap(),
		ExitMap(),
		StartupPayload(NAME_None),
		Datas(nullptr),
		DataTables(nullptr),
		Payloads(nullptr),
		Damages(nullptr)
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

	enum class EMember : uint8
	{
		Damages
	};

	bool IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const;

	UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	template<typename RowStructType>
	RowStructType* GetSafeDataTableRow(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName, void(*Log)(const FString&)) const
	{
		if (UDataTable* DataTable = GetSafeDataTable(Context, WorldContext, MemberType))
		{
			if (RowStructType* RowPtr = DataTable->FindRow<RowStructType>(RowName, Context))
			{
				return RowPtr;
			}
			else
			{
				Log(FString::Printf(TEXT("%s: Failed to find Row: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DataTable->GetName())));
			}
		}
		return nullptr;
	}

	uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const;
};