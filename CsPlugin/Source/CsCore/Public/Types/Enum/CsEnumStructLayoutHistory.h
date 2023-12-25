// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Load/CsSoftObjectPath.h"

#include "CsEnumStructLayoutHistory.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FCsEnumStructLayoutHistory_NameAndValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	int32 Value;

	FCsEnumStructLayoutHistory_NameAndValue() :
		Name(NAME_None),
		Value(INDEX_NONE)
	{
	}
};

class UDataTable;

USTRUCT(BlueprintType)
struct CSCORE_API FCsEnumStructLayoutHistory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	bool bChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	TArray<FCsEnumStructLayoutHistory_NameAndValue> NameAndValues;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	bool bSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	TSoftObjectPtr<UDataTable> DataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	TSet<FSoftObjectPath> References;

	FCsEnumStructLayoutHistory() :
		bChanged(false),
		NameAndValues(),
		bSettings(false),
		DataTable(nullptr),
		References()
	{
	}

	FORCEINLINE bool HasChanged() const { return bChanged; }

	void DetermineChange(const TArray<FName>& NewNames)
	{
		const int32 OldCount = NameAndValues.Num();
		const int32 NewCount = NewNames.Num();
		const int32 Count	 = FMath::Min(OldCount, NewCount);

		bool NameOrValueChanged = false;

		for (int32 I = 0; I < Count; ++I)
		{
			int32 Value = I;

			NameOrValueChanged |= (NewNames[I] != NameAndValues[I].Name);
			NameOrValueChanged |= (Value != NameAndValues[I].Value);
		}

		// Change if any Name or Value CHANGED or if the number types DECREASED
		bChanged = NameOrValueChanged || (NewCount < OldCount);
	}
};