// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Utility
#include "Utility/CsWpLog.h"
// Engine
#include "Engine/DataTable.h"

#include "CsWpDataRootSet.generated.h"

class UDataTable;
class UScriptStruct;
class UObject;

USTRUCT(BlueprintType)
struct CSWP_API FCsWpDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp")
	TSoftObjectPtr<UDataTable> WeaponClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp")
	TSoftObjectPtr<UDataTable> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp")
	TSoftObjectPtr<UDataTable> WeaponSkins;

	FCsWpDataRootSet() :
		WeaponClasses(nullptr),
		Weapons(nullptr),
		WeaponSkins(nullptr)
	{
	}

	enum class EMember : uint8
	{
		WeaponClasses,
		Weapons,
		WeaponSkins
	};

	static EMember GetMember(const FName& MemberName);

	bool IsValidChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const;

	FORCEINLINE const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const FName& MemberName) const
	{
		return GetDataTableSoftObjectChecked(Context, FCsWpDataRootSet::GetMember(MemberName));
	}

	bool GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

	UDataTable* GetSafeDataTable(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetDataTableChecked(const FString& Context, const UObject* WorldContext, const EMember& MemberType) const;

	UDataTable* GetDataTableChecked(const FString& Context, const EMember& MemberType) const;

	template<typename RowStructType>
	RowStructType* GetSafeDataTableRow(const FString& Context, const UObject* WorldContext, const EMember& MemberType, const FName& RowName, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const
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

	uint8* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const FName& RowName) const;

	uint8* GetDataTableRowChecked(const FString& Context, const EMember& MemberType, const UScriptStruct* RowStruct, const FName& RowName) const;
};