// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsSettings_Manager_Playback.generated.h"
#pragma once

// FCsSettings_Manager_Playback
#pragma region

USTRUCT(BlueprintType)
struct CSPLAYBACK_API FCsSettings_Manager_Playback
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CustomUsername;

	/** Maximum time to recorde a playback. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float MaxRecordTime;

	FCsSettings_Manager_Playback() :
		CustomUsername(),
		MaxRecordTime(60.0f)
	{
	}
};

#pragma endregion FCsSettings_Manager_Playback

// FCsSettings_Manager_Playback_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSPLAYBACK_API FCsSettings_Manager_Playback_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Playback_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Playback_UnitTest