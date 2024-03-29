// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsSeLog.h"
// Engine
#include "Engine/DataTable.h"

#include "CsSeDataRootSet.generated.h"

class UObject;
class UScriptStruct;

USTRUCT(BlueprintType)
struct CSSE_API FCsSeDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	/** Status Effect Datas */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> StatusEffects;

	FCsSeDataRootSet() :
		StatusEffects()
	{
	}

	enum class EMember : uint8
	{
		StatusEffects
	};

	static EMember GetMember(const FName& MemberName);

	bool IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const;

	FORCEINLINE const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const FName& MemberName) const
	{
		return GetDataTableSoftObjectChecked(Context, FCsSeDataRootSet::GetMember(MemberName));
	}

	bool GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) const;

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
#if !UE_BUILD_SHIPPING
				if (Log)
					Log(FString::Printf(TEXT("%s: Failed to find Row: %s from DataTable: %s."), *Context, *(RowName.ToString()), *(DataTable->GetName())));
#endif // #if !UE_BUILD_SHIPPING
			}
		}
		return nullptr;
	}

	uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const;
};