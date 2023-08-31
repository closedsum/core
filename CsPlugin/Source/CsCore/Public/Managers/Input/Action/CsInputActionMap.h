// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMask_int32.h"
#include "Types/Enum/CsEnumStructMaskMap.h"

#include "CsInputActionMap.generated.h"

USTRUCT(BlueprintType)
struct CSCORE_API FECsInputActionMap : public FECsEnumMask_int32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_MASK_INT32_BODY(FECsInputActionMap)
};

FORCEINLINE uint32 GetTypeHash(const FECsInputActionMap& b)
{
	return GetTypeHash(b.Name_Internal) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsInputActionMap : public TCsEnumStructMaskMap<FECsInputActionMap, int32>
{
	CS_ENUM_STRUCT_MASK_MAP_BODY(EMCsInputActionMap, FECsInputActionMap, int32)
};

namespace NCsInputActionMap
{
	typedef FECsInputActionMap Type;
	typedef EMCsInputActionMap EnumMapType;


	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

// FCsInputActionMapRule
#pragma region

struct CSCORE_API FCsInputActionMapRule
{
	int32 Clear;
	int32 Set;

	FCsInputActionMapRule()
	{
		Clear = 0;
		Set = 0;
	}

	FCsInputActionMapRule(const int32& InClear, const int32& InSet)
	{
		Clear = InClear;
		Set = InSet;
	}

	FCsInputActionMapRule(const FECsInputActionMap& InClear, const FECsInputActionMap& InSet)
	{
		Clear = (int32)InClear;
		Set = (int32)InSet;
	}
	~FCsInputActionMapRule() {}
};

#pragma endregion FCsInputActionMapRule