// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Action/CsInputAction.h"

#include "CsData_ECsTest.generated.h"

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ECsTest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Test")
	FECsInputAction Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DataTable, meta = (MustImplement = "/Script/CsCore.CsData"))
	TSoftClassPtr<UObject> Data;

	FCsData_ECsTest() :
		Action(),
		Data(nullptr)
	{
	}
};