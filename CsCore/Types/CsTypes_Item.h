// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
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
		GroupHomogeneous		UMETA(DisplayName = "Group Homogeneous"),
		GroupMixed				UMETA(DisplayName = "Group Mixed"),
		ECsItemCollection_MAX	UMETA(Hidden),
	};
}

namespace ECsItemCollection
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

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

namespace ECsItemCollectionCachedString
{
	namespace Str
	{
		const FString Single = TEXT("1x");
	}
}

namespace ECsItemOwner
{
	enum Type : uint8;
}

typedef ECsItemOwner::Type TCsItemOwner;

// ItemOwnerToString
typedef FString(*TCsItemOwnerToString)(const TCsItemOwner&);
// StringToItemOwner
typedef TCsItemOwner(*TCsStringToItemOwner)(const FString&);

#define CS_DECLARE_ITEM_OWNER	TCsItemOwner ItemOwner_MAX;\
								uint8 ITEM_OWNER_MAX; \
								TCsItemOwnerToString ItemOwnerToString; \
								TCsStringToItemOwner StringToItemOwner;

#define CS_DEFINE_ITEM_OWNER	ItemOwner_MAX = ECsItemOwner::ECsItemOwner_MAX; \
								ITEM_OWNER_MAX = (uint8)ItemOwner_MAX; \
								ItemOwnerToString = &ECsItemOwner::ToString; \
								StringToItemOwner = &ECsItemOwner::ToType;

#define CS_WORLD_OWNER_ID 0

USTRUCT(BlueprintType)
struct FCsInventoryItemDimension
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 RowSpan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ColumnSpan;

	FCsInventoryItemDimension() {}
	~FCsInventoryItemDimension() {}

	FCsInventoryItemDimension& operator=(const FCsInventoryItemDimension& B)
	{
		RowSpan = B.RowSpan;
		ColumnSpan = B.ColumnSpan;
		return *this;
	}

	bool operator==(const FCsInventoryItemDimension& B) const
	{
		return (RowSpan == B.RowSpan && ColumnSpan == B.ColumnSpan);
	}

	bool operator!=(const FCsInventoryItemDimension& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		RowSpan	= 1;
		ColumnSpan = 1;
	}

	void Set(const uint8 &InRowSpawn, const uint8 &InColumnSpan)
	{
		RowSpan = InRowSpawn;
		ColumnSpan = InColumnSpan;
	}
};

USTRUCT(BlueprintType)
struct FCsInventoryItemPosition
{
	GENERATED_USTRUCT_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 Row;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 Column;

	FCsInventoryItemPosition() {}
	~FCsInventoryItemPosition() {}

	FCsInventoryItemPosition& operator=(const FCsInventoryItemPosition& B)
	{
		Row = B.Row;
		Column = B.Column;
		return *this;
	}

	bool operator==(const FCsInventoryItemPosition& B) const
	{
		return (Row == B.Row && Column == B.Column);
	}

	bool operator!=(const FCsInventoryItemPosition& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Row = 0;
		Column = 0;
	}

	void Set(const uint8 &InRow, const uint8 &InColumn)
	{
		Row = InRow;
		Column = InColumn;
	}
};

USTRUCT(BlueprintType)
struct FCsInventoryItemProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool Visible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 Bag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FCsUint8MatrixDimension Dimension;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FCsUint8MatrixCoordinate Position;

	FCsInventoryItemProperties() {}
	~FCsInventoryItemProperties() {}

	FCsInventoryItemProperties& operator=(const FCsInventoryItemProperties& B)
	{
		Visible = B.Visible;
		Bag = B.Bag;
		Dimension = B.Dimension;
		Position = B.Position;
		return *this;
	}

	bool operator==(const FCsInventoryItemProperties& B) const
	{
		if (Visible != B.Visible) { return false; }
		if (Bag != B.Bag) { return false; }
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
		Visible = false;
		Bag = 0;
		Dimension.Reset();
		Position.Reset();
	}
};

UENUM(BlueprintType)
namespace ECsItemMemberValueType
{
	enum Type
	{
		Bool						UMETA(DisplayName = "bool"),
		Uint8						UMETA(DisplayName = "uint8"),
		Int32						UMETA(DisplayName = "int32"),
		Float						UMETA(DisplayName = "float"),
		ECsItemMemberValueType_MAX	UMETA(Hidden),
	};
}

namespace ECsItemMemberValueType
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Bool = TCsString(TEXT("Bool"), TEXT("bool"));
		const TCsString Uint8 = TCsString(TEXT("Uint8"), TEXT("uint8"));
		const TCsString Int32 = TCsString(TEXT("Int32"), TEXT("int32"));
		const TCsString Float = TCsString(TEXT("Float"), TEXT("float"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::Bool) { return Str::Bool.Value; }
		if (EType == Type::Uint8) { return Str::Uint8.Value; }
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Bool) { return Type::Bool; }
		if (String == Str::Uint8) { return Type::Uint8; }
		if (String == Str::Int32) { return Type::Int32; }
		if (String == Str::Float) { return Type::Float; }
		return Type::ECsItemMemberValueType_MAX;
	}
}

#define ECS_ITEM_MEMBER_VALUE_TYPE_MAX (uint8)ECsItemMemberValueType::ECsItemMemberValueType_MAX
typedef TEnumAsByte<ECsItemMemberValueType::Type> TCsItemMemberValueType;

USTRUCT(BlueprintType)
struct FCsItemMemberValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TEnumAsByte<ECsItemMemberValueType::Type> Type;

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
		Type = B.Type;
		Value_bool = B.Value_bool;
		Value_uint8 = B.Value_uint8;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		return *this;
	}

	bool operator==(const FCsItemMemberValue& B) const
	{
		if (Type != B.Type) { return false; }
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
struct FCsItemMemberDescription
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member")
	TEnumAsByte<ECsItemMemberValueType::Type> Type;

	FCsItemMemberDescription() {}
	~FCsItemMemberDescription() {}

	FCsItemMemberDescription& operator=(const FCsItemMemberDescription& B)
	{
		Name = B.Name;
		Type = B.Type;
		return *this;
	}

	bool operator==(const FCsItemMemberDescription& B) const
	{
		if (Name != B.Name) { return false; }
		if (Type != B.Type) { return false; }
		return true;
	}

	bool operator!=(const FCsItemMemberDescription& B) const
	{
		return !(*this == B);
	}
};

#define CS_INVALID_ITEM_OWNER 255

USTRUCT(BlueprintType)
struct FCsItemHistory
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint64 OwnerId;

	TCsItemOwner OwnerType;

	UPROPERTY()
	uint8 OwnerType_Script;

	UPROPERTY()
	FString OwnerName;

	UPROPERTY()
	TMap<FName, FCsItemMemberValue> Members;

	FCsItemHistory(){}
	~FCsItemHistory(){}

	FCsItemHistory& operator=(const FCsItemHistory& B)
	{
		OwnerId = B.OwnerId;
		OwnerType = B.OwnerType;
		OwnerType_Script = B.OwnerType_Script;
		OwnerName = B.OwnerName;
		Members = B.Members;
		return *this;
	}

	bool operator==(const FCsItemHistory& B) const
	{
		if (OwnerId != B.OwnerId) { return false; }
		if (OwnerType != B.OwnerType) { return false; }
		if (OwnerType_Script != B.OwnerType_Script) { return false; }
		if (OwnerName != B.OwnerName) { return false; }
		
		TArray<FName> OutKeysA;
		Members.GetKeys(OutKeysA);

		TArray<FName> OutKeysB;
		B.Members.GetKeys(OutKeysB);
		
		if (OutKeysA.Num() != OutKeysB.Num())
			return false;

		const int32 Count = OutKeysA.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (OutKeysA[I] != OutKeysB[I])
				return false;

			const FCsItemMemberValue* ValueA = Members.Find(OutKeysA[I]);
			const FCsItemMemberValue* ValueB = B.Members.Find(OutKeysB[I]);

			if (*ValueA != *ValueB)
				return false;
		}
		return true;
	}

	bool operator!=(const FCsItemHistory& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		OwnerId = 0;
		OwnerType = (TCsItemOwner)0;
		OwnerType_Script = CS_INVALID_ITEM_OWNER;
		OwnerName = ECsCachedString::Str::Empty;

		Members.Reset();
	}

	void SetOwnerType(const TCsItemOwner &InOwnerType)
	{
		OwnerType		 = InOwnerType;
		OwnerType_Script = (uint8)OwnerType;
	}
};

#define CS_ITEM_POOL_INVALID_INDEX 65535
#define CS_INVALID_ITEM_TYPE 255

USTRUCT(BlueprintType)
struct FCsItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint16 Index;

	UPROPERTY()
	bool IsAllocated;
	UPROPERTY()
	bool IsSaved;

	TCsItemType Type;

	UPROPERTY()
	uint8 Type_Script;
	UPROPERTY()
	FString TypeAsString;

	UPROPERTY()
	uint64 UniqueId;
	UPROPERTY()
	FName ShortCode;
	UPROPERTY()
	FString DisplayName;
	UPROPERTY()
	FString FileName;


	FDateTime Created;
	FTimespan LifeTime;

	/** Array of Item UniqueIds this Item is "Holding" */
	UPROPERTY()
	TArray<uint64> Contents;

	TWeakObjectPtr<class ACsData_Item> Data;
	/** Data for Actor spawned when Item leaves Inventory */
	TWeakObjectPtr<class ACsData_Interactive> Data_Actor;

	UPROPERTY()
	FCsInventoryItemProperties InventoryProperties;
	UPROPERTY()
	FCsItemHistory CurrentHistory;
	UPROPERTY()
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
		ShortCode = B.ShortCode;
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
		if (ShortCode != B.ShortCode) { return false; }
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
		Type = (TCsItemType)0;
		Type_Script  = CS_INVALID_ITEM_TYPE;
		TypeAsString = ECsCachedString::Str::Empty;
		UniqueId = 0;
		ShortCode = CS_INVALID_SHORT_CODE;
		DisplayName = ECsCachedString::Str::Empty;
		FileName = ECsCachedString::Str::Empty;
		LifeTime = FTimespan::Zero();
		Contents.Reset();
		//Data.Reset();
		//Data = nullptr;
		//Data_Actor.Reset();
		//Data_Actor = nullptr;
		InventoryProperties.Reset();
		CurrentHistory.Reset();
		PreviousHistories.Reset();
	}

	class ACsData_Item* GetData() const { return Data.IsValid() ? Data.Get() : nullptr; }
	class ACsData_Interactive* GetData_Actor() const { return Data_Actor.IsValid() ? Data_Actor.Get() : nullptr; }

	void SetType(const TCsItemType &InType)
	{
		Type		= InType;
		Type_Script = (uint8)Type;
	}
};

namespace ECsFileItemHeaderCachedString
{
	namespace Str
	{
		const FString Header = TEXT("Header");
		const FString UniqueId = TEXT("UniqueId");
		const FString ShortCode = TEXT("ShortCode");
		const FString DisplayName = TEXT("DisplayName");
		const FString Type = TEXT("Type");
		const FString Created = TEXT("Created");
		const FString LifeTime = TEXT("LifeTime");
		const FString Timespan = TEXT("Timespan");
		const FString Contents = TEXT("Contents");
	}
}

namespace ECsFileItemHistoryHeaderCachedString
{
	namespace Str
	{
		const FString CurrentHistory = TEXT("CurrentHistory");
		const FString PreviousHistories = TEXT("PreviousHistories");
		const FString OwnerId = TEXT("OwnerId");
		const FString OwnerName = TEXT("OwnerName");
		const FString OwnerType = TEXT("OwnerType");
		const FString Members = TEXT("Members");
		const FString Value = TEXT("Value");
	}
}

#pragma endregion Items