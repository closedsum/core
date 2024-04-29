// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsUserDefinedEnum.generated.h"

// UserDefinedEnum
#pragma region

USTRUCT(BlueprintType)
struct CSENUM_API FECsUserDefinedEnum : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserDefinedEnum)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserDefinedEnum)

struct CSENUM_API EMCsUserDefinedEnum : public TCsEnumStructMap<FECsUserDefinedEnum, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserDefinedEnum, FECsUserDefinedEnum, uint8)
};

namespace NCsUserDefinedEnum
{
	typedef FECsUserDefinedEnum Type;
	typedef EMCsUserDefinedEnum EnumMapType;

	extern CSENUM_API const Type FECsInputAction;
	extern CSENUM_API const Type FECsInputActionMap;
	extern CSENUM_API const Type FECsGameEvent;
}

#pragma endregion UserDefinedEnum

// FCsUserDefinedEnum
#pragma region

class UUserDefinedEnum;

USTRUCT(BlueprintType)
struct CSENUM_API FCsUserDefinedEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Enum")
	TSoftObjectPtr<UUserDefinedEnum> Enum;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Enum")
	UUserDefinedEnum* Enum_Internal;

	FCsUserDefinedEnum() :
		Enum(),
		Enum_Internal()
	{
	}

	FORCEINLINE UUserDefinedEnum* Get() { return Enum_Internal; }
};

#pragma endregion FCsUserDefinedEnum