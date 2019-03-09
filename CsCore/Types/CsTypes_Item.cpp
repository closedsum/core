// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Item.h"

// ItemType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsItemType)

// ItemCollection
CS_DEFINE_ENUM_MAP_BODY(EMCsItemCollection)

namespace ECsItemCollection
{
	namespace Ref
	{
		CSCORE_API const Type Single = EMCsItemCollection::Get().Add(Type::Single, TEXT("Single"));
		CSCORE_API const Type GroupHomogeneous = EMCsItemCollection::Get().Add(Type::GroupHomogeneous, TEXT("GroupHomogeneous"), TEXT("Group Homogeneous"));
		CSCORE_API const Type GroupMixed = EMCsItemCollection::Get().Add(Type::GroupMixed, TEXT("GroupMixed"), TEXT("Group Mixed"));
		CSCORE_API const Type ECsItemCollection_MAX = EMCsItemCollection::Get().Add(Type::ECsItemCollection_MAX, TEXT("ECsItemCollection_MAX"), TEXT("MAX"));
	};
}

namespace ECsItemCollectionCached
{
	namespace Str
	{
		CSCORE_API const FString Single = TEXT("1x");
	}
}

// ItemOwner
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsItemOwner)

// ItemMemberValueType
CS_DEFINE_ENUM_MAP_BODY(EMCsItemMemberValueType)

namespace ECsItemMemberValueType
{
	namespace Ref
	{
		CSCORE_API const Type Bool = EMCsItemMemberValueType::Get().Add(Type::Bool, TEXT("Bool"));
		CSCORE_API const Type Uint8 = EMCsItemMemberValueType::Get().Add(Type::Uint8, TEXT("Uint8"));
		CSCORE_API const Type Int32 = EMCsItemMemberValueType::Get().Add(Type::Int32, TEXT("Int32"));
		CSCORE_API const Type Float = EMCsItemMemberValueType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type ECsItemMemberValueType_MAX = EMCsItemMemberValueType::Get().Add(Type::ECsItemMemberValueType_MAX, TEXT("ECsItemMemberValueType_MAX"), TEXT("MAX"));
	};
}

namespace ECsFileItemProductHeaderCached
{
	namespace Str
	{
		CSCORE_API const FString Products = TEXT("Products");
		CSCORE_API const FString Name = TEXT("Name");
		CSCORE_API const FString Id = TEXT("Id");
	}
}

namespace ECsFileItemHeaderCached
{
	namespace Str
	{
		CSCORE_API const FString Header = TEXT("Header");
		CSCORE_API const FString Id = TEXT("Id");
		CSCORE_API const FString ShortCode = TEXT("ShortCode");
		CSCORE_API const FString DisplayName = TEXT("DisplayName");
		CSCORE_API const FString Type = TEXT("Type");
		CSCORE_API const FString Created = TEXT("Created");
		CSCORE_API const FString LifeTime = TEXT("LifeTime");
		CSCORE_API const FString Timespan = TEXT("Timespan");
		CSCORE_API const FString Contents = TEXT("Contents");
	}
}

namespace ECsFileItemHistoryHeaderCached
{
	namespace Str
	{
		CSCORE_API const FString CurrentHistory = TEXT("CurrentHistory");
		CSCORE_API const FString PreviousHistories = TEXT("PreviousHistories");
		CSCORE_API const FString OwnerId = TEXT("OwnerId");
		CSCORE_API const FString OwnerName = TEXT("OwnerName");
		CSCORE_API const FString OwnerType = TEXT("OwnerType");
		CSCORE_API const FString Members = TEXT("Members");
		CSCORE_API const FString Value = TEXT("Value");
	}
}

// ItemOnConsumeContentAction
EMCsItemOnConsumeContentAction* EMCsItemOnConsumeContentAction::Instance;

EMCsItemOnConsumeContentAction& EMCsItemOnConsumeContentAction::Get()
{
	if (!Instance)
		Instance = new EMCsItemOnConsumeContentAction();
	return *Instance;
}

namespace ECsItemOnConsumeContentAction
{
	namespace Ref
	{
		CSCORE_API const Type Consume = EMCsItemOnConsumeContentAction::Get().Add(Type::Consume, TEXT("Consume"));
		CSCORE_API const Type Drop = EMCsItemOnConsumeContentAction::Get().Add(Type::Drop, TEXT("Drop"));
		CSCORE_API const Type Retain = EMCsItemOnConsumeContentAction::Get().Add(Type::Retain, TEXT("Retain"));
		CSCORE_API const Type ECsItemOnConsumeContentAction_MAX = EMCsItemOnConsumeContentAction::Get().Add(Type::ECsItemOnConsumeContentAction_MAX, TEXT("ECsItemOnConsumeContentAction_MAX"), TEXT("MAX"));
	};
}

// ItemInteraction
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsItemInteraction)