// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Asset/CsAnimBlueprintCustomization.h"
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

#define LOCTEXT_NAMESPACE "CsAnimBlueprintCustomization"

TSharedRef<IPropertyTypeCustomization> FCsAnimBlueprintCustomization::MakeInstance()
{
	return MakeShareable(new FCsAnimBlueprintCustomization);
}

void FCsAnimBlueprintCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	BlueprintHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsAnimBlueprint, Blueprint));
	
	TSharedRef<SWidget> BlueprintWidget = BlueprintHandle->CreatePropertyValueWidget();
	
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
				BlueprintHandle->CreateDefaultPropertyButtonWidgets()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				BlueprintWidget
			]
		];
}

void FCsAnimBlueprintCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

#undef LOCTEXT_NAMESPACE
