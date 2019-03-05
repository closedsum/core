// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "../CoreUObject/Public/UObject/Object.h"
#include "CsBlockchainGenesis.generated.h"

UCLASS(transient)
class CSCORE_API UCsBlockchainGenesis : public UObject
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Blockchain Genesis")
	virtual FString ToString();
	UFUNCTION(BlueprintCallable, Category = "Blockchain Genesis")
	virtual void Parse(const FString &Str);
	UFUNCTION(BlueprintCallable, Category = "Blockchain Genesis")
	virtual void ParseFromFilePath(const FString &Path);
};