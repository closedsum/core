// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
#include "Managers/UserWidget/Payload/CsTypes_Payload_UserWidget.h"
// Log
#include "Utility/CsUILog.h"

#include "CsSettings_Manager_UserWidget.generated.h"

// FCsSettings_Manager_UserWidget_PoolParams
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FCsSettings_Manager_UserWidget_PoolParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget")
	FECsUserWidgetPooledClass Class; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget")
	FECsUserWidget Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget", meta = (ClampMin = "4", UIMin = "4"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget", meta = (ClampMin = "4", UIMin = "4"))
	int32 PayloadSize;

	FCsSettings_Manager_UserWidget_PoolParams() :
		Class(),
		Widget(),
		PoolSize(4),
		PayloadSize(4)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget")
	TMap<FECsUserWidgetPooled, FECsUserWidgetPooled> TypeMap;

	/** Which payload to support. The payload is "dynamically" built to some extent.
		The approach assume a UOWYN (Use Only What you Need). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget")
	TSet<FECsUserWidgetPayload> PayloadTypes;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget")
	FECsUserWidgetPooled DefaultType;

	/** Describes any pool parameters (i.e. class, pool size, payload size, ... etc) for each UserWidget type. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget")
	TMap<FECsUserWidgetPooled, FCsSettings_Manager_UserWidget_PoolParams> PoolParams;

	/** Describes the pool size of members related to setting the position of a User Widget in the viewport.
		(i.e. Size of array of Vectors, Vector2Ds, ... etc for World Position, Screen Position, ... etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget", meta = (DisplayName = "Set Position in Viewport: Pool Size", ClampMin = "4", UIMin = "4"))
	int32 SetPositionInViewports_PoolSize;

	FCsSettings_Manager_UserWidget() :
		TypeMap(),
		PayloadTypes(),
		DefaultType(),
		PoolParams(),
		SetPositionInViewports_PoolSize(1024)
	{
	}

	static const FCsSettings_Manager_UserWidget& Get();

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
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