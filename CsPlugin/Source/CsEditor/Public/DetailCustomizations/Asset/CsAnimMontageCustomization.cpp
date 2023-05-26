// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Asset/CsAnimMontageCustomization.h"
#include "CsEditor.h"

// Types
#include "Animation/CsTypes_Anim.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// AssetRegistry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Helper
#include "FileHelpers.h"
//#include "PropertyEditor/Private/PropertyEditorHelpers.h"

#define LOCTEXT_NAMESPACE "CsAnimMontageCustomization"

TSharedRef<IPropertyTypeCustomization> FCsAnimMontageCustomization::MakeInstance()
{
	return MakeShareable(new FCsAnimMontageCustomization);
}

void FCsAnimMontageCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	AnimHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsAnimMontage, Anim));
	
	TSharedRef<SWidget> AnimWidget = AnimHandle->CreatePropertyValueWidget();
	
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
				AnimHandle->CreateDefaultPropertyButtonWidgets()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				AnimWidget
			]
		];
}

void FCsAnimMontageCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef LOCTEXT_NAMESPACE
