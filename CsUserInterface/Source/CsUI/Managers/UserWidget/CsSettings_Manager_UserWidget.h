// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "CsSettings_Manager_UserWidget.generated.h"
#pragma once

// FCsSettings_Manager_UserWidget_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_UserWidget_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetPooledClass ContainerClass; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetClass WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_UserWidget_PoolParams() :
		ContainerClass(),
		WidgetClass(),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_FX_Actor_PoolParams

// FCsSettings_Manager_UserWidget
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_UserWidget
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUserWidgetPooled, FCsSettings_Manager_UserWidget_PoolParams> PoolParams;

	FCsSettings_Manager_UserWidget() :
		PoolParams()
	{
	}
};

#pragma endregion FCsSettings_Manager_UserWidget

// FCsSettings_Manager_UserWidget_UnitTest
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_UserWidget_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_UserWidget_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_UserWidget_UnitTest