// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Asset/CsAnimSequenceCustomization.h"
#include "CsEditor.h"

// Types
#include "Animation/CsTypes_Anim.h"

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
//#include "PropertyEditor/Private/PropertyEditorHelpers.h"

#define LOCTEXT_NAMESPACE "CsAnimSequenceCustomization"

TSharedRef<IPropertyTypeCustomization> FCsAnimSequenceCustomization::MakeInstance()
{
	return MakeShareable(new FCsAnimSequenceCustomization);
}

void FCsAnimSequenceCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	AnimHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsAnimSequence, Anim));
	
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

void FCsAnimSequenceCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef LOCTEXT_NAMESPACE
