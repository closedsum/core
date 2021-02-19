// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// DataTable
#include "Engine/DataTable.h"

#include "CsUIDataRootSet.generated.h"

class UDataTable;
class UCsUserWidget_Fade;

USTRUCT(BlueprintType)
struct CSUI_API FCsUIDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	// Fade

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCsUserWidget_Fade> FadeWidget;

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
		FadeWidget(nullptr),
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
		_WidgetActorClasses,
		_WidgetActors,
		_UserWidgetPooledClasses,
		_UserWidgetPooled,
		_UserWidgetClasses,
		_UserWidgets
	};

	bool IsValidChecked(const FString& Context, UObject* Object, const EMember& MemberType) const;

	UDataTable* GetSafeDataTable(const FString& Context, UObject* Object, const EMember& MemberType) const;

	template<typename RowStructType>
	RowStructType* GetSafeDataTableRow(const FString& Context, UObject* Object, const EMember& MemberType, const FName& RowName, void(*Log)(const FString&)) const
	{
		if (UDataTable* DataTable = GetSafeDataTable(Context, Object, MemberType))
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
};