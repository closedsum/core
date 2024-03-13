// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Templates/SubclassOf.h"

#include "CsFadeDataRootSet.generated.h"

class UCsUserWidget_Fade;
class UClass;

USTRUCT(BlueprintType)
struct CSFADE_API FCsFadeDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	// Fade

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsFade|Data")
	TSubclassOf<UCsUserWidget_Fade> FadeWidget;

	FCsFadeDataRootSet() :
		FadeWidget(nullptr)
	{
	}

	UClass* GetFadeWidgetClassChecked(const FString& Context) const;
};