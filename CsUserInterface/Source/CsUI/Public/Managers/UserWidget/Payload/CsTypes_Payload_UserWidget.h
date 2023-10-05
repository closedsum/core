// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Payload_UserWidget.generated.h"

// UserWidgetPayload
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsUserWidgetPayload : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserWidgetPayload)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserWidgetPayload)

struct CSUI_API EMCsUserWidgetPayload : public TCsEnumStructMap<FECsUserWidgetPayload, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserWidgetPayload, FECsUserWidgetPayload, uint8)
};

namespace NCsUserWidgetPayload
{
	typedef FECsUserWidgetPayload Type;
	typedef EMCsUserWidgetPayload EnumMapType;

	extern CSUI_API const Type UserWidget;
	extern CSUI_API const Type Text;
}

#pragma endregion UserWidgetPayload