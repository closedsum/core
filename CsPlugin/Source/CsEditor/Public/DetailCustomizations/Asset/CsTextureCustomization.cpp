// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Asset/CsTextureCustomization.h"
#include "CsEditor.h"

// Types
#include "Types/CsTypes_Texture.h"

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

#define LOCTEXT_NAMESPACE "CsTextureCustomization"

TSharedRef<IPropertyTypeCustomization> FCsTextureCustomization::MakeInstance()
{
	return MakeShareable(new FCsTextureCustomization);
}

void FCsTextureCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	TextureHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsTexture, Texture));
	
	TSharedRef<SWidget> TextureWidget = TextureHandle->CreatePropertyValueWidget();
	
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
				TextureHandle->CreateDefaultPropertyButtonWidgets()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				TextureWidget
			]
		];
}

void FCsTextureCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef LOCTEXT_NAMESPACE
