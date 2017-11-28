// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Item.generated.h"
#pragma once

// Items
#pragma region

namespace ECsItemType
{
	enum Type : uint8;
}

typedef ECsItemType::Type TCsItemType;

// ItemTypeToString
typedef FString(*TCsItemTypeToString)(const TCsItemType&);
// StringToInteractiveType
typedef TCsItemType(*TCsStringToItemType)(const FString&);

#define CS_DECLARE_ITEM_TYPE_FUNCTIONS	TCsItemTypeToString ItemTypeToString; \
										TCsStringToItemType StringToItemType;

#define CS_DEFINE_ITEM_TYPE_FUNCTIONS	ItemTypeToString = &ECsItemType::ToString; \
										StringToItemType = &ECsItemType::ToType;

USTRUCT(BlueprintType)
struct FCsInventoryItemDimension
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 Width;
	UPROPERTY()
	int32 Height;

	FCsInventoryItemDimension() {}
	~FCsInventoryItemDimension() {}

	FCsInventoryItemDimension& operator=(const FCsInventoryItemDimension& B)
	{
		Width = B.Width;
		Height = B.Height;
		return *this;
	}

	bool operator==(const FCsInventoryItemDimension& B) const
	{
		return (Width == B.Width && Height == B.Height);
	}

	bool operator!=(const FCsInventoryItemDimension& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsInventoryItemPosition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 X;
	UPROPERTY()
	int32 Y;

	FCsInventoryItemPosition() {}
	~FCsInventoryItemPosition() {}

	FCsInventoryItemPosition& operator=(const FCsInventoryItemPosition& B)
	{
		X = B.X;
		Y = B.Y;
		return *this;
	}

	bool operator==(const FCsInventoryItemPosition& B) const
	{
		return (X == B.X && Y == B.Y);
	}

	bool operator!=(const FCsInventoryItemPosition& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsInventoryItemProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 Count;
	UPROPERTY()
	int32 MaxCount;

	UPROPERTY()
	FCsInventoryItemDimension Dimension;
	UPROPERTY()
	FCsInventoryItemPosition Position;

	FCsInventoryItemProperties() {}
	~FCsInventoryItemProperties() {}

	FCsInventoryItemProperties& operator=(const FCsInventoryItemProperties& B)
	{
		Count = B.Count;
		MaxCount = B.MaxCount;
		Dimension = B.Dimension;
		Position = B.Position;
		return *this;
	}

	bool operator==(const FCsInventoryItemProperties& B) const
	{
		if (Count != B.Count) { return false; }
		if (MaxCount != B.MaxCount) { return false; }
		if (Dimension != B.Dimension) { return false; }
		if (Position != B.Position) { return false; }
		return true;
	}

	bool operator!=(const FCsInventoryItemProperties& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsItemMemberValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool Value_bool;
	UPROPERTY()
	uint8 Value_uint8;
	UPROPERTY()
	int32 Value_int32;
	UPROPERTY()
	float Value_float;

	FCsItemMemberValue() {}
	~FCsItemMemberValue() {}

	FCsItemMemberValue& operator=(const FCsItemMemberValue& B)
	{
		Value_bool = B.Value_bool;
		Value_uint8 = B.Value_uint8;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		return *this;
	}

	bool operator==(const FCsItemMemberValue& B) const
	{
		if (Value_bool != B.Value_bool) { return false; }
		if (Value_uint8 != B.Value_uint8) { return false; }
		if (Value_int32 != B.Value_int32) { return false; }
		if (Value_float != B.Value_float) { return false; }
		return true;
	}

	bool operator!=(const FCsItemMemberValue& B) const
	{
		return !(*this == B);
	}

	bool GetBool() { return Value_bool; }
	uint8 GetUint8() { return Value_uint8; }
	int32 GetInt32() { return Value_int32; }
	float GetFloat() { return Value_float; }
};

USTRUCT(BlueprintType)
struct FCsItem
{
	GENERATED_USTRUCT_BODY()

	TCsItemType Type;

	UPROPERTY()
	uint8 Type_Script;

	UPROPERTY()
	uint64 UniqueId;
	UPROPERTY()
	FName Name;
	UPROPERTY()
	FString DisplayName;

	UPROPERTY()
	FCsInventoryItemProperties InventoryProperties;

	TMap<FName, FCsItemMemberValue> Members;

	FCsItem() {}
	~FCsItem() {}

	FCsItem& operator=(const FCsItem& B)
	{
		Type = B.Type;
		Type_Script = B.Type_Script;
		UniqueId = B.UniqueId;
		Name = B.Name;
		DisplayName = B.DisplayName;
		InventoryProperties = B.InventoryProperties;
		return *this;
	}

	bool operator==(const FCsItem& B) const
	{
		if (Type != B.Type) { return false; }
		if (Type_Script != B.Type_Script) { return false; }
		if (UniqueId != B.UniqueId) { return false; }
		if (Name != B.Name) { return false; }
		if (DisplayName != B.DisplayName) { return false; }
		if (InventoryProperties != B.InventoryProperties) { return false; }
		return true;
	}

	bool operator!=(const FCsItem& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion Items