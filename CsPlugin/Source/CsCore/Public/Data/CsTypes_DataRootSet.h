// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsTypes_DataRootSet.generated.h"

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_DataRootSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<UObject> DataRootSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (LongPackageName))
	FDirectoryPath DirectoryToAlwaysCook;

	FCsSettings_DataRootSet() :
		bApply(false),
		DataRootSet(),
		DirectoryToAlwaysCook()
	{
	}
};