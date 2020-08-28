// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsUIDataRootSet.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct CSUI_API FCsUIDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	// Widget Actor

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> WidgetActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> WidgetActors;

	// User Widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgetPooledClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgetPooleds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgetClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> UserWidgets;

	FCsUIDataRootSet() :
		WidgetActorClasses(nullptr),
		WidgetActors(nullptr),
		UserWidgetPooledClasses(nullptr),
		UserWidgetPooleds(nullptr),
		UserWidgetClasses(nullptr),
		UserWidgets(nullptr)
	{
	}
};