// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"

#include "CsSettings_Manager_WidgetActor.generated.h"

// FCsSettings_Manager_WidgetActor_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_WidgetActor_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor|Settings", meta = (MustImplement = "/Script/CsUI.CsWidgetActor"))
	FECsWidgetActorClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor|Settings", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor|Settings", meta = (ClampMin = "4", UIMin = "4"))
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

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor|Settings")
	TMap<FECsWidgetActor, FECsWidgetActor> TypeMap;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor|Settings")
	FECsWidgetActor DefaultType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|Widget Actor|Settings")
	TMap<FECsWidgetActor, FCsSettings_Manager_WidgetActor_PoolParams> PoolParams;

	FCsSettings_Manager_WidgetActor() :
		TypeMap(),
		DefaultType(),
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