// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/Asset/CsUserWidgetPtrCustomization.h"
#include "CsUIEditor.h"

// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// AssetRegistry
#include "AssetRegistry/AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Helper
#include "FileHelpers.h"

#define LOCTEXT_NAMESPACE "CsUserWidgetPtrCustomization"

#define CLASS_TYPE FCsUserWidgetPtrCustomization
#define AssetType FCsUserWidgetPtr

TSharedRef<IPropertyTypeCustomization> CLASS_TYPE::MakeInstance()
{
	return MakeShareable(new CLASS_TYPE);
}

void CLASS_TYPE::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	Handle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(AssetType, Widget));
	
	TSharedRef<SWidget> Widget = Handle->CreatePropertyValueWidget();
	
	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				Handle->CreateDefaultPropertyButtonWidgets()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				Widget
			]
		];
}

void CLASS_TYPE::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef LOCTEXT_NAMESPACE

#undef CLASS_TYPE
#undef AssetType