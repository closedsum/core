// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "CsSettings_Manager_Input.generated.h"
#pragma once

// FCsSettings_Manager_Input
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Input
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 InputPoolSize;
	 
	FCsSettings_Manager_Input() :
		InputPoolSize(2048)
	{
	}
};

#pragma endregion FCsSettings_Manager_Input

// FCsSettings_Manager_Input_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Input_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Input_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Input_UnitTest