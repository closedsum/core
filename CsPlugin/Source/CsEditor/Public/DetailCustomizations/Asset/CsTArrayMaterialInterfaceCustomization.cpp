// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Asset/CsTArrayMaterialInterfaceCustomization.h"
#include "CsEditor.h"

// Types
#include "Material/CsTypes_Material.h"

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

#define LOCTEXT_NAMESPACE "CsTArrayMaterialInterfaceCustomization"

TSharedRef<IPropertyTypeCustomization> FCsTArrayMaterialInterfaceCustomization::MakeInstance()
{
	return MakeShareable(new FCsTArrayMaterialInterfaceCustomization);
}

void FCsTArrayMaterialInterfaceCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	MaterialsHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsTArrayMaterialInterface, Materials));
	
	TSharedRef<SWidget> MaterialsWidget = MaterialsHandle->CreatePropertyValueWidget();
	
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
				MaterialsHandle->CreateDefaultPropertyButtonWidgets()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				MaterialsWidget
			]
		];
}

void FCsTArrayMaterialInterfaceCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef LOCTEXT_NAMESPACE
