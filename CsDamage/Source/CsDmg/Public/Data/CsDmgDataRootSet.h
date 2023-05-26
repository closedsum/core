// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsDmgLog.h"
// Engine
#include "Engine/DataTable.h"

#include "CsDmgDataRootSet.generated.h"

class UDataTable;

/**
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDmgDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	/** Damage Datas */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> Damages;

	FCsDmgDataRootSet() :
		Damages(nullptr)
	{
	}

	enum class EMember : uint8
	{
		Damages
	};

	bool IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const;

	bool GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

	UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetDataTableChecked(const FString& Context, const EMember& MemberType) const;

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

	uint8* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const;
};