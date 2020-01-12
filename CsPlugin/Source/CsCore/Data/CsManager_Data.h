// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Types/CsTypes_Load.h"
#include "CsManager_Data.generated.h"

class UDataTable;
class ICsData;

UINTERFACE(Blueprintable)
class UCsManager_Data : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* Datas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* DataTables;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	UDataTable* Datas_Test;

	TMap<FName, FCsDataEntry_Data*> DataEntryMap;
	TMap<FName, FCsDataEntry_Data*> DataEntryMap_Loaded;

	TMap<FName, ICsData*> DataMap;
};