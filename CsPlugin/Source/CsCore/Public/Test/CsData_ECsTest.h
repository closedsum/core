// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/Action/CsInputAction.h"

#include "CsData_ECsTest.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FCsData_ECsTest
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Input")
	FECsInputAction Action;

	UPROPERTY(VisibleDefaultsOnly, Category = "CsCore|Input")
	bool Action_Data;

	FCsData_ECsTest() :
		Action(),
		Action_Data(nullptr)
	{
	}
};