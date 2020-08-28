// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/CsTypes_WidgetActor.h"
#include "CsSettings_Manager_WidgetActor.generated.h"
#pragma once

// FCsSettings_Manager_WidgetActor_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_WidgetActor_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement ="CsWidgetActor"))
	FECsWidgetActorClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_WidgetActor_PoolParams() :
		Class(),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_WidgetActor_PoolParams

// FCsSettings_Manager_WidgetActor
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_WidgetActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsWidgetActor, FCsSettings_Manager_WidgetActor_PoolParams> PoolParams;

	FCsSettings_Manager_WidgetActor() :
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_WidgetActor

// FCsSettings_Manager_WidgetActor_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_WidgetActor_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_WidgetActor_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_WidgetActor_UnitTest