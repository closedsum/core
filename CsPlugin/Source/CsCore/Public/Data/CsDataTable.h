// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsDataTable.generated.h"

// FCsDataTable
#pragma region

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDataTable
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Load")
	TSoftObjectPtr<UDataTable> Data;

	UPROPERTY(BlueprintReadOnly, Category = "CsCore|Load")
	int32 Data_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UDataTable* Data_Internal;

	FCsDataTable() :
		Data(nullptr),
		Data_LoadFlags(0),
		Data_Internal(nullptr)
	{
	}

	FORCEINLINE bool operator==(const FCsDataTable& B) const
	{
		return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	}

	FORCEINLINE bool operator!=(const FCsDataTable& B) const
	{
		return !(*this == B);
	}

	/**
	* Get the Hard reference to the UDataTable asset.
	*
	* return DataTable
	*/
	FORCEINLINE UDataTable* Get() const { return Data_Internal; }

	/**
	* Get the pointer to the Hard reference to the UDataTable asset.
	*
	* return DataTable
	*/
	FORCEINLINE UDataTable** GetPtr() { return &Data_Internal; }

	/**
	* Get the Hard reference to the UDataTable asset.
	*
	* @param Context	The calling context.
	* return			DataTable
	*/
	FORCEINLINE UDataTable* GetChecked(const FString& Context) const
	{
		checkf(Data.ToSoftObjectPath().IsValid(), TEXT("%s: Data is NULL."), *Context);

		checkf(Data_Internal, TEXT("%s: Data has NOT been loaded from Path @ %s."), *Context, *(Data.ToSoftObjectPath().ToString()));

		return Data_Internal;
	}

	/**
	* Get the Hard reference to the UDataTable asset.
	*
	* return DataTable
	*/
	FORCEINLINE UDataTable* GetChecked() const
	{
		checkf(Data.ToSoftObjectPath().IsValid(), TEXT("FCsDataTable::GetChecked: Data is NULL."));

		checkf(Data_Internal, TEXT("FCsDataTable::GetChecked: Data has NOT been loaded from Path @ %s."), *(Data.ToSoftObjectPath().ToString()));

		return Data_Internal;
	}

	UDataTable* GetSafe(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!Data.ToSoftObjectPath().IsValid())
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Data is NULL."), *Context));
			return nullptr;
		}

		if (!Data_Internal)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: Data has NOT been loaded from Path @ %s."), *Context, *(Data.ToSoftObjectPath().ToString())));
		}
		return Data_Internal;
	}

	UDataTable* GetSafe()
	{
		if (!Data.ToSoftObjectPath().IsValid())
			return nullptr;
		return Data_Internal;
	}

	bool IsValidChecked(const FString& Context) const
	{
		check(GetChecked(Context));
		return true;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const
	{
		if (!GetSafe(Context, Log))
			return false;
		return true;
	}
};

#pragma endregion FCsDataTable