// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Item.h"

// ItemCollection
#pragma region

namespace NCsItemCollection
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Single = EMCsItemCollection::Get().Add(Type::Single, TEXT("Single"));
		CSCOREDEPRECATED_API const Type GroupHomogeneous = EMCsItemCollection::Get().Add(Type::GroupHomogeneous, TEXT("GroupHomogeneous"), TEXT("Group Homogeneous"));
		CSCOREDEPRECATED_API const Type GroupMixed = EMCsItemCollection::Get().Add(Type::GroupMixed, TEXT("GroupMixed"), TEXT("Group Mixed"));
		CSCOREDEPRECATED_API const Type ECsItemCollection_MAX = EMCsItemCollection::Get().Add(Type::ECsItemCollection_MAX, TEXT("ECsItemCollection_MAX"), TEXT("MAX"));
	};

	CSCOREDEPRECATED_API const uint8 MAX = (uint8)Type::ECsItemCollection_MAX;
}

#pragma endregion ItemCollection

// ItemCollectionCached
#pragma region

namespace NCsItemCollectionCached
{
	namespace Str
	{
		CSCOREDEPRECATED_API const FString Single = TEXT("1x");
	}
}

#pragma endregion ItemCollectionCached

// InventoryItemState_Editor
#pragma region

namespace NCsInventoryItemState_Editor
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Visible = EMCsInventoryItemState_Editor::Get().Add(Type::Visible, TEXT("Visible"));
		CSCOREDEPRECATED_API const Type Ingredient = EMCsInventoryItemState_Editor::Get().Add(Type::Ingredient, TEXT("Ingredient"));
		CSCOREDEPRECATED_API const Type ECsInventoryItemState_Editor_MAX = EMCsInventoryItemState_Editor::Get().Add(Type::ECsInventoryItemState_Editor_MAX, TEXT("ECsInventoryItemState_Editor_MAX"), TEXT("MAX"));
	};

	CSCOREDEPRECATED_API const uint8 MAX = (uint8)Type::ECsInventoryItemState_Editor_MAX;
}

#pragma endregion InventoryItemState_Editor

// ItemMemberValueType
#pragma region

namespace ECsItemMemberValueType
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Bool = EMCsItemMemberValueType::Get().Add(Type::Bool, TEXT("Bool"));
		CSCOREDEPRECATED_API const Type Uint8 = EMCsItemMemberValueType::Get().Add(Type::Uint8, TEXT("Uint8"));
		CSCOREDEPRECATED_API const Type Int32 = EMCsItemMemberValueType::Get().Add(Type::Int32, TEXT("Int32"));
		CSCOREDEPRECATED_API const Type Float = EMCsItemMemberValueType::Get().Add(Type::Float, TEXT("Float"));
		CSCOREDEPRECATED_API const Type ECsItemMemberValueType_MAX = EMCsItemMemberValueType::Get().Add(Type::ECsItemMemberValueType_MAX, TEXT("ECsItemMemberValueType_MAX"), TEXT("MAX"));
	};
}

#pragma endregion ItemMemberValueType

// FileItemProductHeaderCached
#pragma region

namespace ECsFileItemProductHeaderCached
{
	namespace Str
	{
		CSCOREDEPRECATED_API const FString Products = TEXT("Products");
		CSCOREDEPRECATED_API const FString Name = TEXT("Name");
		CSCOREDEPRECATED_API const FString Id = TEXT("Id");
	}
}

#pragma endregion FileItemProductHeaderCached

// FileItemHeaderCached
#pragma region

namespace ECsFileItemHeaderCached
{
	namespace Str
	{
		CSCOREDEPRECATED_API const FString Header = TEXT("Header");
		CSCOREDEPRECATED_API const FString Id = TEXT("Id");
		CSCOREDEPRECATED_API const FString ShortCode = TEXT("ShortCode");
		CSCOREDEPRECATED_API const FString DisplayName = TEXT("DisplayName");
		CSCOREDEPRECATED_API const FString Type = TEXT("Type");
		CSCOREDEPRECATED_API const FString Created = TEXT("Created");
		CSCOREDEPRECATED_API const FString LifeTime = TEXT("LifeTime");
		CSCOREDEPRECATED_API const FString Timespan = TEXT("Timespan");
		CSCOREDEPRECATED_API const FString Contents = TEXT("Contents");
	}
}

#pragma endregion FileItemHeaderCached

// FileItemHistoryHeaderCached
#pragma region

namespace ECsFileItemHistoryHeaderCached
{
	namespace Str
	{
		CSCOREDEPRECATED_API const FString CurrentHistory = TEXT("CurrentHistory");
		CSCOREDEPRECATED_API const FString PreviousHistories = TEXT("PreviousHistories");
		CSCOREDEPRECATED_API const FString OwnerId = TEXT("OwnerId");
		CSCOREDEPRECATED_API const FString OwnerName = TEXT("OwnerName");
		CSCOREDEPRECATED_API const FString OwnerType = TEXT("OwnerType");
		CSCOREDEPRECATED_API const FString Members = TEXT("Members");
		CSCOREDEPRECATED_API const FString Value = TEXT("Value");
	}
}

#pragma endregion FileItemHistoryHeaderCached

// ItemOnConsumeContentAction
#pragma region

namespace ECsItemOnConsumeContentAction
{
	namespace Ref
	{
		CSCOREDEPRECATED_API const Type Consume = EMCsItemOnConsumeContentAction::Get().Add(Type::Consume, TEXT("Consume"));
		CSCOREDEPRECATED_API const Type Drop = EMCsItemOnConsumeContentAction::Get().Add(Type::Drop, TEXT("Drop"));
		CSCOREDEPRECATED_API const Type Retain = EMCsItemOnConsumeContentAction::Get().Add(Type::Retain, TEXT("Retain"));
		CSCOREDEPRECATED_API const Type ECsItemOnConsumeContentAction_MAX = EMCsItemOnConsumeContentAction::Get().Add(Type::ECsItemOnConsumeContentAction_MAX, TEXT("ECsItemOnConsumeContentAction_MAX"), TEXT("MAX"));
	};
}

#pragma endregion ItemOnConsumeContentAction