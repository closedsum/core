// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "CsTypes_Settings.generated.h"

// FCsSettings_Enum
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Enum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DisplayName;

	FCsSettings_Enum() :
		Name(),
		DisplayName()
	{
	}
};

#pragma endregion FCsSettings_Enum