// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Item.h"

// ItemType
EMCsItemType* EMCsItemType::Instance;

EMCsItemType& EMCsItemType::Get()
{
	if (!Instance)
		Instance = new EMCsItemType();
	return *Instance;
}

// ItemCollection
EMCsItemCollection* EMCsItemCollection::Instance;

EMCsItemCollection& EMCsItemCollection::Get()
{
	if (!Instance)
		Instance = new EMCsItemCollection();
	return *Instance;
}

// ItemOwner
EMCsItemOwner* EMCsItemOwner::Instance;

EMCsItemOwner& EMCsItemOwner::Get()
{
	if (!Instance)
		Instance = new EMCsItemOwner();
	return *Instance;
}

// ItemMemberValueType
EMCsItemMemberValueType* EMCsItemMemberValueType::Instance;

EMCsItemMemberValueType& EMCsItemMemberValueType::Get()
{
	if (!Instance)
		Instance = new EMCsItemMemberValueType();
	return *Instance;
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

// ItemInteraction
EMCsItemInteraction* EMCsItemInteraction::Instance;

EMCsItemInteraction& EMCsItemInteraction::Get()
{
	if (!Instance)
		Instance = new EMCsItemInteraction();
	return *Instance;
}