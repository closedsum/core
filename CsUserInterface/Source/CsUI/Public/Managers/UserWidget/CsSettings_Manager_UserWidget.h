// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#include "CsSettings_Manager_UserWidget.generated.h"

// FCsSettings_Manager_UserWidget_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_UserWidget_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetPooledClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidget Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_UserWidget_PoolParams() :
		Class(),
		Widget(),
		PoolSize(4),
		PayloadSize(4)
	{
	}
};

#pragma endregion FCsSettings_Manager_UserWidget_PoolParams

// FCsSettings_Manager_UserWidget
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_UserWidget
{
	GENERATED_USTRUCT_BODY()

public:

	/** General Idea: Pool Sharing via Mapping of Types.
		Describes the mapping of a UserWidget type to underlying UserWidget type
		in terms the pool of UserWidget.

		i.e. If Type 'A' is mapped to Type 'B' (TypeMap[A] = B), then
			 when a UserWidget of type 'A' is spawned it will be allocated from
			 the pool of UserWidget of type 'B'.

		The idea behind behind this mapping is UserWidgets of a different type may
		not have underlying code differences and just be differences in the data
		each respective user widget type uses. This provides the ability to save on both
		the number of pools created and the number of objects created for a pool. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUserWidgetPooled, FECsUserWidgetPooled> TypeMap;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsUserWidgetPooled DefaultType;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each UserWidget type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUserWidgetPooled, FCsSettings_Manager_UserWidget_PoolParams> PoolParams;

	FCsSettings_Manager_UserWidget() :
		TypeMap(),
		DefaultType(),
		PoolParams()
	{
	}

	static const FCsSettings_Manager_UserWidget& Get();
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