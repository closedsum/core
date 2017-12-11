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
// StringToItemType
typedef TCsItemType(*TCsStringToItemType)(const FString&);

#define CS_DECLARE_ITEM_TYPE	TCsItemType ItemType_MAX;\
								uint8 ITEM_TYPE_MAX; \
								TCsItemTypeToString ItemTypeToString; \
								TCsStringToItemType StringToItemType;

#define CS_DEFINE_ITEM_TYPE	ItemType_MAX = ECsItemType::ECsItemType_MAX; \
							ITEM_TYPE_MAX = (uint8)ItemType_MAX; \
							ItemTypeToString = &ECsItemType::ToString; \
							StringToItemType = &ECsItemType::ToType;

#pragma region

UENUM(BlueprintType)
namespace ECsItemCollection
{
	enum Type
	{
		Single					UMETA(DisplayName = "Single"),
		GroupHomogeneous			UMETA(DisplayName = "Group Homogeneous"),
		GroupMixed				UMETA(DisplayName = "Group Mixed"),
		ECsItemCollection_MAX	UMETA(Hidden),
	};
}

namespace ECsItemCollection
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Single = TCsString(TEXT("Single"), TEXT("single"), TEXT("single"));
		const TCsString GroupHomogeneous = TCsString(TEXT("GroupHomogeneous"), TEXT("grouphomogeneous"), TEXT("group homogeneous"));
		const TCsString GroupMixed = TCsString(TEXT("GroupMixed"), TEXT("groupmixed"), TEXT("group mixed"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Single) { return Str::Single.Value; }
		if (EType == Type::GroupHomogeneous) { return Str::GroupHomogeneous.Value; }
		if (EType == Type::GroupMixed) { return Str::GroupMixed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Single) { return Type::Single; }
		if (String == Str::GroupHomogeneous) { return Type::GroupHomogeneous; }
		if (String == Str::GroupMixed) { return Type::GroupMixed; }
		return Type::ECsItemCollection_MAX;
	}
}

#define ECS_ITEM_COLLECTION_MAX (uint8)ECsItemCollection::ECsItemCollection_MAX
typedef TEnumAsByte<ECsItemCollection::Type> TCsItemCollection;

namespace ECsItemOwner
{
	enum Type : uint8;
}

typedef ECsItemOwner::Type TCsItemOwner;

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

	void Reset()
	{
		Width = 0;
		Height = 0;
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

	void Reset()
	{
		X = 0;
		Y = 0;
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

	void Reset()
	{
		Count = 0;
		MaxCount = 0;
		Dimension.Reset();
		Position.Reset();
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
struct FCsItemHistory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint64 OwnerId;

	TCsItemOwner OwnerType;

	UPROPERTY()
	FString OwnerName;

	TMap<FName, FCsItemMemberValue> Members;

	FCsItemHistory(){}
	~FCsItemHistory(){}

	FCsItemHistory& operator=(const FCsItemHistory& B)
	{
		return *this;
	}

	bool operator==(const FCsItemHistory& B) const
	{
		return true;
	}

	bool operator!=(const FCsItemHistory& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Members.Reset();
	}
};

#define CS_ITEM_POOL_INVALID_INDEX 65535

USTRUCT(BlueprintType)
struct FCsItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint16 Index;

	bool IsAllocated;
	bool IsSaved;

	TCsItemType Type;

	UPROPERTY()
	uint8 Type_Script;
	UPROPERTY()
	FString TypeAsString;

	UPROPERTY()
	uint64 UniqueId;
	UPROPERTY()
	FName Name;
	UPROPERTY()
	FString DisplayName;

	FDateTime Created;
	FTimespan LifeTime;

	TWeakObjectPtr<class ACsData_Item> Data;

	UPROPERTY()
	FCsInventoryItemProperties InventoryProperties;

	FCsItemHistory CurrentHistory;

	TArray<FCsItemHistory> PreviousHistories;

	FCsItem() 
	{
		Index = CS_ITEM_POOL_INVALID_INDEX;

		PreviousHistories.SetNum(0);
		Reset();
	}

	~FCsItem() {}

	FCsItem& operator=(const FCsItem& B)
	{
		Type = B.Type;
		Type_Script = B.Type_Script;
		TypeAsString = B.TypeAsString;
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
		if (TypeAsString != B.TypeAsString) { return false; }
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

	void Init(const uint16 &InIndex)
	{
		Index = InIndex;
	}

	void Reset()
	{
		IsAllocated = false;
		IsSaved = false;
		//Type;
		Type_Script  = 0;
		TypeAsString = TEXT("");
		UniqueId = 0;
		Name = NAME_Name;
		DisplayName = TEXT("");
		InventoryProperties.Reset();
		CurrentHistory.Reset();
		PreviousHistories.Reset();
	}

	class ACsData_Item* GetData() { return Data.IsValid() ? Data.Get() : nullptr; }
};

namespace ECsFileItemHeaderCachedString
{
	namespace Str
	{
		const FString UniqueId = TEXT("UniqueId");
		const FString Name = TEXT("Name");
		const FString DisplayName = TEXT("DisplayName");
		const FString Type = TEXT("Type");
		const FString Created = TEXT("Created");
		const FString LifeTime = TEXT("LifeTime");
		const FString Timespan = TEXT("Timespan");
	}
}

namespace ECsFileItemHistoryHeaderCachedString
{
	namespace Str
	{
		const FString OwnerId = TEXT("OwnerId");
		const FString OwnerName = TEXT("OwnerName");
		const FString OwnerType = TEXT("OwnerType");
	}
}

#pragma endregion Items