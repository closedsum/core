// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// DataTable
#include "Engine/DataTable.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUIDataRootSet.generated.h"

class UDataTable;
class UCsWidget_ConsoleCommand;

USTRUCT(BlueprintType)
struct CSUI_API FCsUIDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	// Console Command
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCsWidget_ConsoleCommand> ConsoleCommandWidget;

	// Widget Actor

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> WidgetActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> WidgetActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bWidgetActorsHasData;

	// User Widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgetPooledClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgetPooled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUserWidgetPooledHasData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgetClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUserWidgetsHasData;

	FCsUIDataRootSet() :
		ConsoleCommandWidget(nullptr),
		WidgetActorClasses(nullptr),
		WidgetActors(nullptr),
		bWidgetActorsHasData(false),
		UserWidgetPooledClasses(nullptr),
		UserWidgetPooled(nullptr),
		bUserWidgetPooledHasData(false),
		UserWidgetClasses(nullptr),
		UserWidgets(nullptr),
		bUserWidgetsHasData(false)
	{
	}

	enum class EMember : uint8
	{
		WidgetActorClasses,
		WidgetActors,
		UserWidgetPooledClasses,
		UserWidgetPooled,
		UserWidgetClasses,
		UserWidgets
	};

	static EMember GetMember(const FName& MemberName);

	bool IsValidChecked(const FString& Context, UObject* Object, const EMember& MemberType) const;

	const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const EMember& MemberType) const;

	FORCEINLINE const TSoftObjectPtr<UDataTable>& GetDataTableSoftObjectChecked(const FString& Context, const FName& MemberName) const
	{
		return GetDataTableSoftObjectChecked(Context, FCsUIDataRootSet::GetMember(MemberName));
	}

	bool GetSafeDataTableSoftObject(const FString& Context, const EMember& MemberType, TSoftObjectPtr<UDataTable>& OutSoftObject, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

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