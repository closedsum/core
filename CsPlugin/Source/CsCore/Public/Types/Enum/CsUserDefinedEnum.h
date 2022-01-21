// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsUserDefinedEnum.generated.h"
#pragma once

// UserDefinedEnum
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsUserDefinedEnum : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsUserDefinedEnum)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsUserDefinedEnum)

struct CSCORE_API EMCsUserDefinedEnum : public TCsEnumStructMap<FECsUserDefinedEnum, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsUserDefinedEnum, FECsUserDefinedEnum, uint8)
};

namespace NCsUserDefinedEnum
{
	typedef FECsUserDefinedEnum Type;
	typedef EMCsUserDefinedEnum EnumMapType;

	extern CSCORE_API const Type FECsDataType;
	extern CSCORE_API const Type FECsDataCollectionType;
	extern CSCORE_API const Type FECsInputAction;
	extern CSCORE_API const Type FECsInputActionMap;
	extern CSCORE_API const Type FECsGameEvent;
}

#pragma endregion UserDefinedEnum

// FCsUserDefinedEnum
#pragma region

class UUserDefinedEnum;

USTRUCT(BlueprintType)
struct CSCORE_API FCsUserDefinedEnum
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UUserDefinedEnum> Enum;

	UPROPERTY(Transient, BlueprintReadOnly)
	UUserDefinedEnum* Enum_Internal;

	FCsUserDefinedEnum() :
		Enum(),
		Enum_Internal()
	{
	}

	FORCEINLINE UUserDefinedEnum* Get() { return Enum_Internal; }
};

#pragma endregion FCsUserDefinedEnum