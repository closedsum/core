// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/Asset/CsGameplayEffectCustomization.h"

// Types
#include "Effect/CsGameplayEffect.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "CsGameplayEffectCustomization"

#define CLASS_TYPE FCsGameplayEffectCustomization
#define TEMP_GET_MEMBER_NAME_CHECKED GET_MEMBER_NAME_CHECKED(FCsGameplayEffect, Effect)

TSharedRef<IPropertyTypeCustomization> CLASS_TYPE::MakeInstance()
{
	return MakeShareable(new CLASS_TYPE);
}

void CLASS_TYPE::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	PropertyHandle = StructPropertyHandle->GetChildHandle(TEMP_GET_MEMBER_NAME_CHECKED);
	
	TSharedRef<SWidget> PropertyWidget = PropertyHandle->CreatePropertyValueWidget();
	
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
				PropertyHandle->CreateDefaultPropertyButtonWidgets()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				PropertyWidget
			]
		];
}

void CLASS_TYPE::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef CLASS_TYPE
#undef TEMP_GET_MEMBER_NAME_CHECKED

#undef LOCTEXT_NAMESPACE