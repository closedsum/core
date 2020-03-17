// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsTypes_Enum.h"
#include "Types/CsTypes_Async.h"

#include "CsTypes_Item.generated.h"
#pragma once

// ItemType
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsItemType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsItemType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsItemType)

struct CSCOREDEPRECATED_API EMCsItemType : public TCsEnumStructMap<FECsItemType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsItemType, FECsItemType, uint8)
};

#pragma endregion ItemType

// ItemCollection
#pragma region

UENUM(BlueprintType)
enum class ECsItemCollection : uint8
{
	Single					UMETA(DisplayName = "Single"),
	GroupHomogeneous		UMETA(DisplayName = "Group Homogeneous"),
	GroupMixed				UMETA(DisplayName = "Group Mixed"),
	ECsItemCollection_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsItemCollection : public TCsEnumMap<ECsItemCollection>
{
	CS_ENUM_MAP_BODY(EMCsItemCollection, ECsItemCollection)
};

namespace NCsItemCollection
{
	typedef ECsItemCollection Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Single;
		extern CSCOREDEPRECATED_API const Type GroupHomogeneous;
		extern CSCOREDEPRECATED_API const Type GroupMixed;
		extern CSCOREDEPRECATED_API const Type ECsItemCollection_MAX;
	};

	extern CSCOREDEPRECATED_API const uint8 MAX;
}

#pragma endregion ItemCollection

// ItemCollectionCached
#pragma region

namespace NCsItemCollectionCached
{
	namespace Str
	{
		extern CSCOREDEPRECATED_API const FString Single;// = TEXT("1x");
	}
}

#pragma endregion ItemCollectionCached

// ItemOwner
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsItemOwner : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsItemOwner)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsItemOwner)

struct CSCOREDEPRECATED_API EMCsItemOwner : public TCsEnumStructMap<FECsItemOwner, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsItemOwner, FECsItemOwner, uint8)
};

#pragma endregion ItemOwner

namespace ECsItemOwnerId
{
	const FGuid None = FGuid();
	const FGuid World = FGuid();
}

#define CS_WORLD_OWNER_ID ECsItemOwnerId::World

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

// InventoryItemState_Editor
#pragma region

UENUM(BlueprintType)
enum class ECsInventoryItemState_Editor : uint8
{
	Visible								UMETA(DisplayName = "Visible"),
	Ingredient							UMETA(DisplayName = "Ingredient"),
	ECsInventoryItemState_Editor_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsInventoryItemState_Editor : public TCsEnumMap<ECsInventoryItemState_Editor>
{
	CS_ENUM_MAP_BODY(EMCsInventoryItemState_Editor, ECsInventoryItemState_Editor)
};

namespace NCsInventoryItemState_Editor
{
	typedef ECsInventoryItemState_Editor Type;

	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Visible;
		extern CSCOREDEPRECATED_API const Type Ingredient;
	}

	extern CSCOREDEPRECATED_API const uint8 MAX;

	FORCEINLINE const FString& ToString(const int32& State)
	{
		FString String = NCsCached::Str::Empty;
		bool IsFirst   = true;

		const int32& Count = EMCsInventoryItemState_Editor::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			if (CS_TEST_BLUEPRINT_BITFLAG(State, I))
			{
				if (!IsFirst)
				{
					String += TEXT(" | ");
				}
				String += EMCsInventoryItemState_Editor::Get().ToString(I);
				IsFirst = false;
			}
		}
		return String;
	}

	FORCEINLINE ECsInventoryItemState ToBaseType(const Type& EType)
	{
		if (EType == Ref::Visible) { return ECsInventoryItemState::Visible; }
		if (EType == Ref::Ingredient) { return ECsInventoryItemState::Ingredient; }
		return ECsInventoryItemState::Visible;
	}

	FORCEINLINE ECsInventoryItemState ToFlag(const FString& String)
	{
		const ECsInventoryItemState_Editor& EType = EMCsInventoryItemState_Editor::Get().GetSafeEnum(String);

		if (EType == Ref::Visible) { return ECsInventoryItemState::Visible; }
		if (EType == Ref::Ingredient) { return ECsInventoryItemState::Ingredient; }
		return ECsInventoryItemState::Visible;
	}
}

#define ECS_INVENTORY_ITEM_STATE_MAX (uint8)NCsInventoryItemState_Editor::MAX

#pragma endregion InventoryItemState_Editor

// FCsInventoryItemProperties

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsInventoryItemProperties
{
	GENERATED_USTRUCT_BODY()

	/** Whether the Item has the flags Visible, Ingredient, ... etc */
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

	FCsInventoryItemProperties() 
	{
		Reset();
	}
	~FCsInventoryItemProperties() {}

	FORCEINLINE FCsInventoryItemProperties& operator=(const FCsInventoryItemProperties& B)
	{
		State = B.State;
		Bag = B.Bag;
		Dimension = B.Dimension;
		Position = B.Position;
		Capacity = B.Capacity;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInventoryItemProperties& B) const
	{
		if (State != B.State) { return false; }
		if (Bag != B.Bag) { return false; }
		if (Dimension != B.Dimension) { return false; }
		if (Position != B.Position) { return false; }
		if (Capacity != B.Capacity) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInventoryItemProperties& B) const
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

#pragma endregion FCsInventoryItemProperties

// ItemMemberValueType
#pragma region

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

typedef ECsItemMemberValueType::Type TCsItemMemberValueType;

struct CSCOREDEPRECATED_API EMCsItemMemberValueType : public TCsEnumMap<ECsItemMemberValueType::Type>
{
	CS_ENUM_MAP_BODY(EMCsItemMemberValueType, ECsItemMemberValueType::Type)
};

namespace ECsItemMemberValueType
{
	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Bool;
		extern CSCOREDEPRECATED_API const Type Uint8;
		extern CSCOREDEPRECATED_API const Type Int32;
		extern CSCOREDEPRECATED_API const Type Float;
		extern CSCOREDEPRECATED_API const Type ECsItemMemberValueType_MAX;
	};
}

#pragma endregion ItemMemberValueType

// FCsItemMemberValue
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemMemberValue
{
	GENERATED_USTRUCT_BODY()

	/** bool, uint8, int32, or float */
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

	FCsItemMemberValue() :
		Type(ECsItemMemberValueType::ECsItemMemberValueType_MAX)
	{
		ResetValues();
	}
	~FCsItemMemberValue() {}

	FORCEINLINE FCsItemMemberValue& operator=(const FCsItemMemberValue& B)
	{
		Type = B.Type;
		Value_bool = B.Value_bool;
		Value_uint8 = B.Value_uint8;
		Value_int32 = B.Value_int32;
		Value_float = B.Value_float;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsItemMemberValue& B) const
	{
		if (Type != B.Type) { return false; }
		if (Value_bool != B.Value_bool) { return false; }
		if (Value_uint8 != B.Value_uint8) { return false; }
		if (Value_int32 != B.Value_int32) { return false; }
		if (Value_float != B.Value_float) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsItemMemberValue& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool GetBool() { return Value_bool; }
	FORCEINLINE uint8 GetUint8() { return Value_uint8; }
	FORCEINLINE int32 GetInt32() { return Value_int32; }
	FORCEINLINE float GetFloat() { return Value_float; }

	FORCEINLINE void Increment()
	{
		if (Type == ECsItemMemberValueType::Uint8)
			++Value_uint8;
		if (Type == ECsItemMemberValueType::Int32)
			++Value_int32;
	}

	void ResetValues()
	{
		Value_bool = false;
		Value_uint8 = 0;
		Value_int32 = 0;
		Value_float = 0.0f;
	}
};

#pragma endregion FCsItemMemberValue

// FCsItemMemberDescription
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemMemberDescription
{
	GENERATED_USTRUCT_BODY()

	/** Name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Member")
	TEnumAsByte<ECsItemMemberValueType::Type> Type;

	FCsItemMemberDescription() :
		Name(NAME_None),
		Type(ECsItemMemberValueType::ECsItemMemberValueType_MAX)
	{
	}

	~FCsItemMemberDescription() {}

	FORCEINLINE FCsItemMemberDescription& operator=(const FCsItemMemberDescription& B)
	{
		Name = B.Name;
		Type = B.Type;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsItemMemberDescription& B) const
	{
		if (Name != B.Name) { return false; }
		if (Type != B.Type) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsItemMemberDescription& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsItemMemberDescription

typedef FGuid TCsItemOwnerId;

#define CS_INVALID_ITEM_OWNER 255

// FCsItemHistory
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemHistory
{
	GENERATED_USTRUCT_BODY()

	/** OwnerId */
	UPROPERTY()
	FGuid OwnerId;

	UPROPERTY()
	FECsItemOwner OwnerType;

	UPROPERTY()
	FString OwnerName;

	UPROPERTY()
	TMap<FName, FCsItemMemberValue> Members;

	FCsItemHistory(){}
	~FCsItemHistory(){}

	FORCEINLINE FCsItemHistory& operator=(const FCsItemHistory& B)
	{
		OwnerId = B.OwnerId;
		OwnerType = B.OwnerType;
		OwnerName = B.OwnerName;

		Members.Empty();

		TArray<FName> Keys;
		B.Members.GetKeys(Keys);

		for (const FName& Key : Keys)
		{
			Members.Add(Key, B.Members[Key]);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsItemHistory& B) const
	{
		if (OwnerId != B.OwnerId) { return false; }
		if (OwnerType != B.OwnerType) { return false; }
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

	FORCEINLINE bool operator!=(const FCsItemHistory& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		OwnerId = ECsItemOwnerId::None;
		OwnerType = EMCsItemOwner::Get().GetMAX();
		OwnerName = NCsCached::Str::Empty;

		Members.Reset();
	}
};

#define CS_ITEM_POOL_INVALID_INDEX 65535
#define CS_INVALID_ITEM_TYPE 255
#define CS_CURRENT_HISTORY -1

#pragma endregion FCsItemHistory

// FCsItemProduct
#pragma region

typedef FGuid TCsItemProductId;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemProduct
{
	GENERATED_USTRUCT_BODY()

	/** Name */
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	FCsItemHistory CurrentHistory;
	UPROPERTY()
	TArray<FCsItemHistory> PreviousHistories;

	FCsItemProduct()
	{
		PreviousHistories.SetNum(0);
	}

	~FCsItemProduct() {}

	FORCEINLINE FCsItemProduct& operator=(const FCsItemProduct& B)
	{
		Name = B.Name;
		Id = B.Id;

		CurrentHistory = B.CurrentHistory;

		PreviousHistories.Reset();

		const int32 HistoryCount = B.PreviousHistories.Num();

		for (int32 I = 0; I < HistoryCount; ++I)
		{
			PreviousHistories.AddDefaulted();
			PreviousHistories[I] = B.PreviousHistories[I];
		}
		return *this;
	}

	FORCEINLINE bool operator==(const FCsItemProduct& B) const
	{
		if (Name != B.Name) { return false; }
		if (Id != B.Id) { return false; }
		if (CurrentHistory != B.CurrentHistory) { return false; }

		if (PreviousHistories.Num() != B.PreviousHistories.Num()) { return false; }

		const int32 HistoryCount = B.PreviousHistories.Num();

		for (int32 I = 0; I < HistoryCount; ++I)
		{
			if (PreviousHistories[I] != B.PreviousHistories[I])
				return false;
		}
		return true;
	}

	FORCEINLINE bool operator!=(const FCsItemProduct& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FCsItemMemberValue* GetMemberValue(const int32 &HistoryIndex, const FName& InName)
	{
		if (HistoryIndex == CS_CURRENT_HISTORY)
			return CurrentHistory.Members.Find(InName);
		if (HistoryIndex < PreviousHistories.Num())
			return PreviousHistories[HistoryIndex].Members.Find(InName);
		return nullptr;
	}

	FORCEINLINE void IncrementMemberValue(const int32 &HistoryIndex, const FName& InName)
	{
		FCsItemMemberValue* Value = GetMemberValue(HistoryIndex, InName);
		Value->Increment();
	}

	void Reset()
	{
		Name = NCsCached::Str::Empty;
		Id	 = ECsItemOwnerId::None;
		CurrentHistory.Reset();
		PreviousHistories.Reset();
	}
};

#pragma endregion FCsItemProduct

// FCsItem
#pragma region

typedef FGuid TCsItemId;

class UCsData_Item;
class UCsData_Interactive;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItem
{
	GENERATED_USTRUCT_BODY()

	/** Pool Index */
	UPROPERTY()
	uint16 Index;

	UPROPERTY()
	bool bAllocated;
	UPROPERTY()
	bool IsSaved;

	UPROPERTY()
	FECsItemType Type;

	UPROPERTY()
	FGuid Id;
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
	TArray<FGuid> Contents;

	TWeakObjectPtr<UCsData_Item> Data;
	/** Data for Actor spawned when Item leaves Inventory */
	TWeakObjectPtr<UCsData_Interactive> Data_Actor;

	UPROPERTY()
	FCsInventoryItemProperties InventoryProperties;
	UPROPERTY()
	TMap<FGuid, FCsItemProduct> Products;

	FCsMutex AsycTaskMutex;

	FCsItem() 
	{
		Index = CS_ITEM_POOL_INVALID_INDEX;
		Reset();
	}

	~FCsItem() {}

	FCsItem& operator=(const FCsItem& B)
	{
		Type = B.Type;
		Id = B.Id;
		ShortCode = B.ShortCode;
		DisplayName = B.DisplayName;
		FileName = B.FileName;
		Created = B.Created;
		LifeTime = B.LifeTime;

		Contents.Reset();

		for (const FGuid& Content : B.Contents)
		{
			Contents.Add(Content);
		}
		Data = B.Data;
		Data_Actor = B.Data_Actor;
		InventoryProperties = B.InventoryProperties;

		Products.Reset();

		TArray<FGuid> Keys;
		B.Products.GetKeys(Keys);

		for (const FGuid& Key : Keys)
		{
			Products.Add(Key, B.Products[Key]);
		}
		return *this;
	}

	bool operator==(const FCsItem& B) const
	{
		if (Type != B.Type) { return false; }
		if (Id != B.Id) { return false; }
		if (ShortCode != B.ShortCode) { return false; }
		if (DisplayName != B.DisplayName) { return false; }
		if (Created != B.Created) { return false; }
		if (LifeTime != B.LifeTime) { return false; }

		if (Contents.Num() != B.Contents.Num()) { return false; }

		const int32 ContentCount = B.Contents.Num();

		for (int32 I = 0; I < ContentCount; ++I)
		{
			if (Contents[I]!= B.Contents[I])
				return false;
		}

		if (Data != B.Data) { return false; }
		if (Data_Actor != B.Data_Actor) { return false; }
		if (InventoryProperties != B.InventoryProperties) { return false; }

		if (Products.Num() != B.Products.Num()) { return false; }

		TArray<TCsItemProductId> Keys;
		B.Products.GetKeys(Keys);

		for (const TCsItemProductId& Key : Keys)
		{
			const FCsItemProduct* P1 = Products.Find(Key);
			const FCsItemProduct* P2 = B.Products.Find(Key);

			if ((P1 && !P2) || (!P1 && P2))
				return false;
			if (*P1 != *P2)
				return false;
		}
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

	FORCEINLINE FCsItemProduct* GetProduct(const TCsItemProductId &ProductId)
	{
		return Products.Find(ProductId);
	}

	FORCEINLINE FCsItemHistory& GetCurrentHistory(const TCsItemProductId &ProductId)
	{
		FCsItemProduct* Product = Products.Find(ProductId);
		return Product->CurrentHistory;
	}

	FORCEINLINE FCsItemMemberValue* GetMemberValue(const TCsItemProductId &ProductId, const int32 &HistoryIndex, const FName& Name)
	{
		if (FCsItemProduct* Product = Products.Find(ProductId))
			return Product->GetMemberValue(HistoryIndex, Name);
		return nullptr;
	}

	FORCEINLINE void IncrementMemberValue(const TCsItemProductId &ProductId, const int32 &HistoryIndex, const FName& Name)
	{
		if (FCsItemProduct* Product = Products.Find(ProductId))
			Product->IncrementMemberValue(HistoryIndex, Name);
	}

	void Reset()
	{
		bAllocated = false;
		IsSaved = false;
		Type = EMCsItemType::Get().GetMAX();
		Id = ECsItemOwnerId::None;
		ShortCode = CS_INVALID_SHORT_CODE;
		DisplayName = NCsCached::Str::Empty;
		FileName = NCsCached::Str::Empty;
		LifeTime = FTimespan::Zero();
		Contents.Reset();
		//Data.Reset();
		//Data = nullptr;
		//Data_Actor.Reset();
		//Data_Actor = nullptr;
		InventoryProperties.Reset();
		Products.Reset();
		AsycTaskMutex.Reset();
	}

	FORCEINLINE UCsData_Item* GetData() const { return Data.IsValid() ? Data.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData() { return Cast<T>(GetData()); }

	FORCEINLINE UCsData_Interactive* GetData_Actor() const { return Data_Actor.IsValid() ? Data_Actor.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetData_Actor() const { return Cast<T>(GetData_Actor()); }
};

#pragma endregion FCsItem

// FCsInventoryLoadoutRecipe
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsInventoryLoadoutRecipe
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

	FORCEINLINE FCsInventoryLoadoutRecipe& operator=(const FCsInventoryLoadoutRecipe& B)
	{
		ShortCode = B.ShortCode;
		Count = B.Count;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInventoryLoadoutRecipe& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Count != B.Count) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInventoryLoadoutRecipe& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsInventoryLoadoutRecipe

// FCsInventoryLoadoutItem
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsInventoryLoadoutItem
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

	FORCEINLINE FCsInventoryLoadoutItem& operator=(const FCsInventoryLoadoutItem& B)
	{
		ShortCode = B.ShortCode;
		Count = B.Count;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsInventoryLoadoutItem& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Count != B.Count) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsInventoryLoadoutItem& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsInventoryLoadoutItem

// FCsInventoryLoadout
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsInventoryLoadout
{
	GENERATED_USTRUCT_BODY()

	/** Recipes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCsInventoryLoadoutRecipe> Recipes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCsInventoryLoadoutItem> Items;

	FCsInventoryLoadout() {}
	~FCsInventoryLoadout() {}

	FORCEINLINE FCsInventoryLoadout& operator=(const FCsInventoryLoadout& B)
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

	FORCEINLINE bool operator==(const FCsInventoryLoadout& B) const
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

	FORCEINLINE bool operator!=(const FCsInventoryLoadout& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsInventoryLoadout

// ItemOnConsumeContentAction
#pragma region

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

typedef ECsItemOnConsumeContentAction::Type TCsItemOnConsumeContentAction;

struct CSCOREDEPRECATED_API EMCsItemOnConsumeContentAction : public TCsEnumMap<ECsItemOnConsumeContentAction::Type>
{
	CS_ENUM_MAP_BODY(EMCsItemOnConsumeContentAction, ECsItemOnConsumeContentAction::Type)
};

namespace ECsItemOnConsumeContentAction
{
	namespace Ref
	{
		extern CSCOREDEPRECATED_API const Type Consume;
		extern CSCOREDEPRECATED_API const Type Drop;
		extern CSCOREDEPRECATED_API const Type Retain;
		extern CSCOREDEPRECATED_API const Type ECsItemOnConsumeContentAction_MAX;
	};
}

#pragma endregion ItemOnConsumeContentAction

// FCsItemOnConsumeContentRule
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsItemOnConsumeContentRule
{
	GENERATED_USTRUCT_BODY()

	/** ShortCode for the Item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName ShortCode;
	/** Action (Consume, Drop, Retain, ... etc) to execute on the Item when the Parent Item is Consumed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TEnumAsByte<ECsItemOnConsumeContentAction::Type> Action;

	FCsItemOnConsumeContentRule() :
		ShortCode(NAME_None),
		Action(ECsItemOnConsumeContentAction::ECsItemOnConsumeContentAction_MAX)
	{
	}

	~FCsItemOnConsumeContentRule() {}

	FORCEINLINE FCsItemOnConsumeContentRule& operator=(const FCsItemOnConsumeContentRule& B)
	{
		ShortCode = B.ShortCode;
		Action = B.Action;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsItemOnConsumeContentRule& B) const
	{
		if (ShortCode != B.ShortCode) { return false; }
		if (Action != B.Action) { return false; }
		return true;
	}

	FORCEINLINE bool operator!=(const FCsItemOnConsumeContentRule& B) const
	{
		return !(*this == B);
	}
};

#pragma endregion FCsItemOnConsumeContentRule

// ItemInteraction
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsItemInteraction : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsItemInteraction)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsItemInteraction)

struct CSCOREDEPRECATED_API EMCsItemInteraction : public TCsEnumStructMap<FECsItemInteraction, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsItemInteraction, FECsItemInteraction, uint8)
};

#pragma endregion ItemInteraction

// FileItemProductHeaderCached
#pragma region

namespace ECsFileItemProductHeaderCached
{
	namespace Str
	{
		extern CSCOREDEPRECATED_API const FString Products;// = TEXT("Products");
		extern CSCOREDEPRECATED_API const FString Name;// = TEXT("Name");
		extern CSCOREDEPRECATED_API const FString Id;// = TEXT("Id");
	}
}

#pragma endregion FileItemProductHeaderCached

// FileItemHeaderCached
#pragma region

namespace ECsFileItemHeaderCached
{
	namespace Str
	{
		extern CSCOREDEPRECATED_API const FString Header;// = TEXT("Header");
		extern CSCOREDEPRECATED_API const FString Id;// = TEXT("Id");
		extern CSCOREDEPRECATED_API const FString ShortCode;// = TEXT("ShortCode");
		extern CSCOREDEPRECATED_API const FString DisplayName;// = TEXT("DisplayName");
		extern CSCOREDEPRECATED_API const FString Type;// = TEXT("Type");
		extern CSCOREDEPRECATED_API const FString Created;// = TEXT("Created");
		extern CSCOREDEPRECATED_API const FString LifeTime;// = TEXT("LifeTime");
		extern CSCOREDEPRECATED_API const FString Timespan;// = TEXT("Timespan");
		extern CSCOREDEPRECATED_API const FString Contents;// = TEXT("Contents");
	}
}

#pragma endregion FileItemHeaderCached

// FileItemHistoryHeaderCached
#pragma region

namespace ECsFileItemHistoryHeaderCached
{
	namespace Str
	{
		extern CSCOREDEPRECATED_API const FString CurrentHistory;// = TEXT("CurrentHistory");
		extern CSCOREDEPRECATED_API const FString PreviousHistories;// = TEXT("PreviousHistories");
		extern CSCOREDEPRECATED_API const FString OwnerId;// = TEXT("OwnerId");
		extern CSCOREDEPRECATED_API const FString OwnerName;// = TEXT("OwnerName");
		extern CSCOREDEPRECATED_API const FString OwnerType;// = TEXT("OwnerType");
		extern CSCOREDEPRECATED_API const FString Members;// = TEXT("Members");
		extern CSCOREDEPRECATED_API const FString Value;// = TEXT("Value");
	}
}

#pragma endregion FileItemHistoryHeaderCached