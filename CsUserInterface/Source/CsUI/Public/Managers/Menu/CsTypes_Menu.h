// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Menu.generated.h"

// Menu
#pragma region

/**
* Enum for Menu types.
*/
USTRUCT(BlueprintType)
struct CSUI_API FECsMenu : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsMenu)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsMenu)

struct CSUI_API EMCsMenu final : public TCsEnumStructMap<FECsMenu, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsMenu, FECsMenu, uint8)
};

namespace NCsMenu
{
	typedef FECsMenu Type;
	typedef EMCsMenu EnumMapType;
}

#pragma endregion Menu

// MenuEvent
#pragma region

USTRUCT(BlueprintType)
struct CSUI_API FECsMenuEvent : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsMenuEvent)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsMenuEvent)

struct CSUI_API EMCsMenuEvent final : public TCsEnumStructMap<FECsMenuEvent, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsMenuEvent, FECsMenuEvent, uint8)
};

namespace NCsMenuEvent
{
	typedef FECsMenuEvent Type;
	typedef EMCsMenuEvent EnumMapType;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSUI_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion MenuEvent