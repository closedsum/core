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
typedef const FString&(*TCsItemTypeToString)(const TCsItemType&);
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

#define ECS_ITEM_COLLECTION_MAX (uint8)ECsItemCollection::ECsItemCollection_MAX
typedef ECsItemCollection::Type TCsItemCollection;

namespace ECsItemCollection
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString Single = TCsString(TEXT("Single"), TEXT("single"), TEXT("single"));
		const TCsString GroupHomogeneous = TCsString(TEXT("GroupHomogeneous"), TEXT("grouphomogeneous"), TEXT("group homogeneous"));
		const TCsString GroupMixed = TCsString(TEXT("GroupMixed"), TEXT("groupmixed"), TEXT("group mixed"));
	}

	namespace Ref
	{
		const TCsItemCollection Single = Type::Single;
		const TCsItemCollection GroupHomogeneous = Type::GroupHomogeneous;
		const TCsItemCollection GroupMixed = Type::GroupMixed;
		const TCsItemCollection ECsItemCollection_MAX = Type::ECsItemCollection_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Single) { return Str::Single.Value; }
		if (EType == Type::GroupHomogeneous) { return Str::GroupHomogeneous.Value; }
		if (EType == Type::GroupMixed) { return Str::GroupMixed.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::Single) { return Ref::Single; }
		if (String == Str::GroupHomogeneous) { return Ref::GroupHomogeneous; }
		if (String == Str::GroupMixed) { return Ref::GroupMixed; }
		return Ref::ECsItemCollection_MAX;
	}
}

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
typedef const FString&(*TCsItemOwnerToString)(const TCsItemOwner&);
// StringToItemOwner
typedef const TCsItemOwner&(*TCsStringToItemOwner)(const FString&);

#define CS_DECLARE_ITEM_OWNER	TCsItemOwner ItemOwner_MAX;\
								uint8 ITEM_OWNER_MAX; \
								TCsItemOwnerToString ItemOwnerToString; \
								TCsStringToItemOwner StringToItemOwner;

#define CS_DEFINE_ITEM_OWNER	ItemOwner_MAX = ECsItemOwner::ECsItemOwner_MAX; \
								ITEM_OWNER_MAX = (uint8)ItemOwner_MAX; \
								ItemOwnerToString = &ECsItemOwner::ToString; \
								StringToItemOwner = &ECsItemOwner::ToType;

#define CS_WORLD_OWNER_ID 0

#define CS_INVALID_INVENTORY_ITEM_BAG 255
#define CS_INVALID_INVENTORY_ITEM_ROW 255
#define CS_INVALID_INVENTORY_ITEM_COLUMN 255

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsInventoryItemState : uint8
{
	Visible		UMETA(DisplayName = "Visible"),
	Ingredient	UMETA(DisplayName = "Ingredient"),
};

													// (Visible | Ingredient)
													// ((1<<0) | (1<<1))
#define CS_INVENTORY_ITEM_STATE_VISIBLE_AND_INGREDIENT 3

UENUM(BlueprintType)
namespace ECsInventoryItemState_Editor
{
	enum Type
	{
		Visible								UMETA(DisplayName = "Visible"),
		Ingredient							UMETA(DisplayName = "Ingredient"),
		ECsInventoryItemState_Editor_MAX	UMETA(Hidden),
	};
}

#define ECS_INVENTORY_ITEM_STATE_MAX (uint8)ECsInventoryItemState_Editor::ECsInventoryItemState_Editor_MAX
typedef ECsInventoryItemState_Editor::Type TCsInventoryItemState_Editor;

namespace ECsInventoryItemState_Editor
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Visible = TCsString(TEXT("Visible"), TEXT("visible"));
		const TCsString Ingredient = TCsString(TEXT("Ingredient"), TEXT("ingredient"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Visible) { return Str::Visible.Value; }
		if (EType == Type::Ingredient) { return Str::Ingredient.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const FString& ToString(const int32 &State)
	{
		FString String = ECsCachedString::Str::Empty;
		bool IsFirst   = true;

		for (int32 I = 0; I < ECS_INVENTORY_ITEM_STATE_MAX; ++I)
		{
			if (CS_TEST_BLUEPRINT_BITFLAG(State, (ECsInventoryItemState)I))
			{
				if (!IsFirst)
				{
					String += TEXT(" | ");
				}
				String += ToString((TCsInventoryItemState_Editor)I);
				IsFirst = false;
			}
		}
		return String;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::Visible) { return Type::Visible; }
		if (String == Str::Ingredient) { return Type::Ingredient; }
		return Type::ECsInventoryItemState_Editor_MAX;
	}

	FORCEINLINE ECsInventoryItemState ToBaseType(const Type &EType)
	{
		if (EType == Type::Visible) { return ECsInventoryItemState::Visible; }
		if (EType == Type::Ingredient) { return ECsInventoryItemState::Ingredient; }
		return ECsInventoryItemState::Visible;
	}

	FORCEINLINE ECsInventoryItemState ToFlag(const FString &String)
	{
		if (String == Str::Visible) { return ECsInventoryItemState::Visible; }
		if (String == Str::Ingredient) { return ECsInventoryItemState::Ingredient; }
		return ECsInventoryItemState::Visible;;
	}
}

USTRUCT(BlueprintType)
struct FCsInventoryItemProperties
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (Bitmask, BitmaskEnum = "ECsInventoryItemState"))
	int32 State;
	/** The current Bag in the Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	uint8 Bag;

	/** The RowSpan, ColumnSpan Slots occupied in the Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FCsUint8MatrixDimension Dimension;
	/** The Row, Column position in the Inventory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FCsUint8MatrixCoordinate Position;
	/** How many of this ItemType can be stored in a Slot. Copied from Data->Capacity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Capacity;

	FCsInventoryItemProperties() {}
	~FCsInventoryItemProperties() {}

	FCsInventoryItemProperties& operator=(const FCsInventoryItemProperties& B)
	{
		State = B.State;
		Bag = B.Bag;
		Dimension = B.Dimension;
		Position = B.Position;
		Capacity = B.Capacity;
		return *this;
	}

	bool operator==(const FCsInventoryItemProperties& B) const
	{
		if (State != B.State) { return false; }
		if (Bag != B.Bag) { return false; }
		if (Dimension != B.Dimension) { return false; }
		if (Position != B.Position) { return false; }
		if (Capacity != B.Capacity) { return false; }
		return true;
	}

	bool operator!=(const FCsInventoryItemProperties& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		State = 0;
		Bag = CS_INVALID_INVENTORY_ITEM_BAG;
		Dimension.Reset();
		Position.Set(CS_INVALID_INVENTORY_ITEM_ROW, CS_INVALID_INVENTORY_ITEM_COLUMN);
		Capacity = CS_EMPTY;
	}

	void SetVisible()
	{
		CS_SET_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Visible);
	}

	void ClearVisible()
	{
		CS_CLEAR_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Visible);
	}

	bool IsVisible()
	{
		return CS_TEST_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Visible);
	}

	void SetIngredient()
	{
		CS_SET_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Ingredient);
	}

	bool IsIngredient()
	{
		return CS_TEST_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Ingredient);
	}

	void SetVisibleAndIngredient()
	{
		CS_SET_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Visible);
		CS_SET_BLUEPRINT_BITFLAG(State, ECsInventoryItemState::Ingredient);
	}

	bool IsState(const int32& InState)
	{
		for (int32 I = 0; I < ECS_INVENTORY_ITEM_STATE_MAX; ++I)
		{
			if (CS_TEST_BLUEPRINT_BITFLAG(InState, I) &&
				!CS_TEST_BLUEPRINT_BITFLAG(State, I))
			{
				return false;
			}
		}
		return true;
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

#define ECS_ITEM_MEMBER_VALUE_TYPE_MAX (uint8)ECsItemMemberValueType::ECsItemMemberValueType_MAX
typedef ECsItemMemberValueType::Type TCsItemMemberValueType;

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

	namespace Ref
	{
		const TCsItemMemberValueType Bool = Type::Bool;
		const TCsItemMemberValueType Uint8 = Type::Uint8;
		const TCsItemMemberValueType Int32 = Type::Int32;
		const TCsItemMemberValueType Float = Type::Float;
		const TCsItemMemberValueType ECsItemMemberValueType_MAX = Type::ECsItemMemberValueType_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Bool) { return Str::Bool.Value; }
		if (EType == Type::Uint8) { return Str::Uint8.Value; }
		if (EType == Type::Int32) { return Str::Int32.Value; }
		if (EType == Type::Float) { return Str::Float.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::Bool) { return Ref::Bool; }
		if (String == Str::Uint8) { return Ref::Uint8; }
		if (String == Str::Int32) { return Ref::Int32; }
		if (String == Str::Float) { return Ref::Float; }
		return Ref::ECsItemMemberValueType_MAX;
	}
}

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

	FCsItemMemberValue() 
	{
		ResetValues();
	}
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

	void ResetValues()
	{
		Value_bool = false;
		Value_uint8 = 0;
		Value_int32 = 0;
		Value_float = 0.0f;
	}
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

USTRUCT(BlueprintType)
struct FCsInventoryLoadoutRecipe
{
	GENERATED_USTRUCT_BODY()

	/** ShortCode for the Recipe */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName ShortCode;
	/** Number of Recipes / Items */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Count;

	FCsInventoryLoadoutRecipe()
	{
		Count = 1;
	}
	~FCsInventoryLoadoutRecipe() {}

	FCsInventoryLoadoutRecipe& operator=(const FCsInventoryLoadoutRecipe& B)
	{
		ShortCode = B.ShortCode;
		Count = B.Count;
		return *this;
	}

	bool operator==(const FCsInventoryLoadoutRecipe& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Count != B.Count) { return false; }
		return true;
	}

	bool operator!=(const FCsInventoryLoadoutRecipe& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsInventoryLoadoutItem
{
	GENERATED_USTRUCT_BODY()

	/** ShortCode for the Item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName ShortCode;
	/** Number of Items */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Count;

	FCsInventoryLoadoutItem()
	{
		Count = 1;
	}
	~FCsInventoryLoadoutItem() {}

	FCsInventoryLoadoutItem& operator=(const FCsInventoryLoadoutItem& B)
	{
		ShortCode = B.ShortCode;
		Count = B.Count;
		return *this;
	}

	bool operator==(const FCsInventoryLoadoutItem& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Count != B.Count) { return false; }
		return true;
	}

	bool operator!=(const FCsInventoryLoadoutItem& B) const
	{
		return !(*this == B);
	}
};

USTRUCT(BlueprintType)
struct FCsInventoryLoadout
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCsInventoryLoadoutRecipe> Recipes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCsInventoryLoadoutItem> Items;

	FCsInventoryLoadout() {}
	~FCsInventoryLoadout() {}

	FCsInventoryLoadout& operator=(const FCsInventoryLoadout& B)
	{
		Items.Reset();

		const int32 ItemCount = B.Items.Num();

		for (int32 I = 0; I < ItemCount; ++I)
		{
			Items.AddDefaulted();
			Items[I] = B.Items[I];
		}

		Recipes.Reset();

		const int32 RecipeCount = B.Recipes.Num();

		for (int32 I = 0; I < RecipeCount; ++I)
		{
			Recipes.AddDefaulted();
			Recipes[I] = B.Recipes[I];
		}
		return *this;
	}

	bool operator==(const FCsInventoryLoadout& B) const
	{
		if (Items.Num() != B.Items.Num())
			return false;
		if (Recipes.Num() != B.Recipes.Num())
			return false;

		const int32 ItemCount = B.Items.Num();

		for (int32 I = 0; I < ItemCount; ++I)
		{
			if (Items[I] != B.Items[I])
				return false;
		}


		const int32 RecipeCount = B.Recipes.Num();

		for (int32 I = 0; I < RecipeCount; ++I)
		{
			if (Recipes[I] != B.Recipes[I])
				return false;
		}
		return true;
	}

	bool operator!=(const FCsInventoryLoadout& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsItemOnConsumeContentAction
{
	enum Type
	{
		Consume								UMETA(DisplayName = "Cnnsume"),
		Drop								UMETA(DisplayName = "Drop"),
		Retain								UMETA(DisplayName = "Retain"),
		ECsItemOnConsumeContentAction_MAX	UMETA(Hidden),
	};
}

#define ECS_ITEM_ON_CONSUME_CONTENT_ACTION_MAX (uint8)ECsItemOnConsumeContentAction::ECsItemOnConsumeContentAction_MAX
typedef ECsItemOnConsumeContentAction::Type TCsItemOnConsumeContentAction;

namespace ECsItemOnConsumeContentAction
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString Consume = TCsString(TEXT("Consume"), TEXT("consume"));
		const TCsString Drop = TCsString(TEXT("Drop"), TEXT("drop"));
		const TCsString Retain = TCsString(TEXT("Retain"), TEXT("retain"));
	}

	namespace Ref
	{
		const TCsItemOnConsumeContentAction Consume = Type::Consume;
		const TCsItemOnConsumeContentAction Drop = Type::Drop;
		const TCsItemOnConsumeContentAction Retain = Type::Retain;
		const TCsItemOnConsumeContentAction ECsItemOnConsumeContentAction_MAX = Type::ECsItemOnConsumeContentAction_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Consume) { return Str::Consume.Value; }
		if (EType == Type::Drop) { return Str::Drop.Value; }
		if (EType == Type::Retain) { return Str::Retain.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::Consume) { return Ref::Consume; }
		if (String == Str::Drop) { return Ref::Drop; }
		if (String == Str::Retain) { return Ref::Retain; }
		return Ref::ECsItemOnConsumeContentAction_MAX;
	}
}

USTRUCT(BlueprintType)
struct FCsItemOnConsumeContentRule
{
	GENERATED_USTRUCT_BODY()

	/** ShortCode for the Item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName ShortCode;
	/** Action (Consume, Drop, Retain, ... etc) to execute on the Item when the Parent Item is Consumed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TEnumAsByte<ECsItemOnConsumeContentAction::Type> Action;

	FCsItemOnConsumeContentRule(){}
	~FCsItemOnConsumeContentRule() {}

	FCsItemOnConsumeContentRule& operator=(const FCsItemOnConsumeContentRule& B)
	{
		ShortCode = B.ShortCode;
		Action = B.Action;
		return *this;
	}

	bool operator==(const FCsItemOnConsumeContentRule& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Action != B.Action) { return false; }
		return true;
	}

	bool operator!=(const FCsItemOnConsumeContentRule& B) const
	{
		return !(*this == B);
	}
};

UENUM(BlueprintType)
namespace ECsItemAction
{
	enum Type
	{
		FireWeapon			UMETA(DisplayName = "Fire Weapon"),
		HitEnemy			UMETA(DisplayName = "Hit Enemy"),
		ECsItemAction_MAX	UMETA(Hidden),
	};
}

#define ECS_ITEM_ACTION_MAX (uint8)ECsItemAction::ECsItemAction_MAX
typedef ECsItemAction::Type TCsItemAction;

namespace ECsItemAction
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString FireWeapon = TCsString(TEXT("FireWeapon"), TEXT("fireweapon"), TEXT("fire weapon"));
		const TCsString HitEnemy = TCsString(TEXT("HitEnemy"), TEXT("hitenemy"), TEXT("hit enemy"));
	}

	namespace Ref
	{
		const TCsItemAction FireWeapon = Type::FireWeapon;
		const TCsItemAction HitEnemy = Type::HitEnemy;
		const TCsItemAction ECsItemAction_MAX = Type::ECsItemAction_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::FireWeapon) { return Str::FireWeapon.Value; }
		if (EType == Type::HitEnemy) { return Str::HitEnemy.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::FireWeapon) { return Ref::FireWeapon; }
		if (String == Str::HitEnemy) { return Ref::HitEnemy; }
		return Ref::ECsItemAction_MAX;
	}
}

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