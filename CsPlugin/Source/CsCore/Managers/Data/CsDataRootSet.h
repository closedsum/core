// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "CsDataRootSet.generated.h"

class UDataTable;

UCLASS(Blueprintable)
class CSCORE_API UCsDataRootSet : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* Datas;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* DataTables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Root")
	UDataTable* Payloads;
};