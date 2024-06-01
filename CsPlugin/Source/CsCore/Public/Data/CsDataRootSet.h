// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath EntryMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath TransitionEntryToMainMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath MainMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data", meta = (AllowedClasses = "/Script/Engine.World"))
	FSoftObjectPath ExitMap;

#pragma endregion Flow

// Startup
#pragma region
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	FName StartupPayload;

#pragma endregion Startup

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	UDataTable* Datas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	UDataTable* ScriptDatas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	UDataTable* DataTables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Data")
	UDataTable* Payloads;

	FCsDataRootSet() :
		EntryMap(),
		TransitionEntryToMainMap(),
		MainMap(),
		ExitMap(),
		StartupPayload(NAME_None),
		Datas(nullptr),
		ScriptDatas(nullptr),
		DataTables(nullptr),
		Payloads(nullptr)
	{
	}

#if WITH_EDITOR

	//void AddDataTable(const FName& EntryName, const TSoftObjectPtr<UDataTable>& DataTable, void(*Log)(const FString&) = &FCsLog::Warning);
	//void AddDataTable(const FName& Entryname, const TSoftObjectPtr<UDataTable>& DataTable, const TSet<FName>& RowNames, void(*Log)(const FString&) = &FCsLog::Warning);

#endif // #if WITH_EDITOR

	enum class EMap : uint8
	{
		Entry,
		Main
	};

	bool IsPersistentLevel(UObject* WorldContext, const EMap& Type) const;

	enum class EMember : uint8
	{
		Datas,
		ScriptDatas,
		DataTables,
		Payloads
	};

	static EMember GetMember(const FName& MemberName);

	bool IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const;

	FORCEINLINE const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const FName& MemberName) const
	{
		return GetDataTableSoftObjectChecked(Context, FCsDataRootSet::GetMember(MemberName));
	}

	UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetDataTableChecked(const FString& Context, const EMember& MemberType) const;

	FORCEINLINE UDataTable* GetDataTableChecked(const FString& Context, const FName& MemberName) const
	{
		return GetDataTableChecked(Context, FCsDataRootSet::GetMember(MemberName));
	}

	UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetSafeDataTable(const FString& Context, const EMember& MemberType) const;

	FORCEINLINE UDataTable* GetSafeDataTable(const FString& Context, const FName& MemberName) const
	{
		return GetSafeDataTable(Context, FCsDataRootSet::GetMember(MemberName));
	}

	uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const;

	template<typename RowStructType>
	RowStructType* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const
	{
		UDataTable* DataTable = GetDataTableChecked(Context, MemberType);
		RowStructType* RowPtr = DataTable->FindRow<RowStructType>(RowName, Context);

		checkf(RowPtr, TEXT("%s: Failed to find Row: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DataTable->GetName()));

		return RowPtr;
	}

	uint8* GetSafeDataTableRow(const FString& Context, const EMember& MemberType, const FName& RowName, void(*Log)(const FString&) = &FCsLog::Warning) const;

	uint8* GetSafeDataTableRow(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName, void(*Log)(const FString&) = &FCsLog::Warning) const;
	
	template<typename RowStructType>
	RowStructType* GetSafeDataTableRow(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (uint8* RowPtr = GetSafeDataTableRow(Context, MemberType, RowStructType::StaticStruct(), RowName, Log))
			return reinterpret_cast<RowStructType*>(RowPtr);
		return nullptr;
	}


	template<typename RowStructType>
	RowStructType* GetSafeDataTableRow(const FString& Context, const EMember& MemberType, const FName& RowName, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (uint8* RowPtr = GetSafeDataTableRow(Context, MemberType, RowStructType::StaticStruct(), RowName, Log))
			return reinterpret_cast<RowStructType*>(RowPtr);
		return nullptr;
	}
};