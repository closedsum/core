// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "DetailCustomizations/Data/CsData_DamagePtrCustomization.h"
#include "CsDmgEditor.h"

// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"

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
////#include "PropertyEditor/Private/PropertyEditorHelpers.h"

#define LOCTEXT_NAMESPACE "CsData_DamagePtrCustomization"

TSharedRef<IPropertyTypeCustomization> FCsData_DamagePtrCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_DamagePtrCustomization);
}

void FCsData_DamagePtrCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	DataHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_DamagePtr, Data));

	DataHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateRaw(this, &FCsData_DamagePtrCustomization::OnDataChanged));

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		];
}

void FCsData_DamagePtrCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.bHideSelectionTip = true;
	PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

	SAssignNew(DataPathText, STextBlock);

	// If Data is populated with a Class, update PropertyView and DataPathText
	{
		// Get the Data as a string path
		FString S;
		DataHandle->GetValueAsFormattedString(S);
		// Convert to SoftClassPath
		FSoftClassPath ClassPath;
		ClassPath.SetPath(S);
		
		if (UObject* O = ClassPath.TryLoad())
		{
			PropertyView->SetObject(O);

			// Update Path to Data
			FString Path = O->GetPathName();
			int32 Index = INDEX_NONE;
			Path.FindLastChar('.', Index);
			Path = Path.Left(Index);
			DataPathText->SetText(FText::FromString(Path));
		}
	}

	StructBuilder.AddCustomRow(LOCTEXT("MyStructRow", "MyStruct"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(0.0f, 0.0f, 5.0f, 0.0f)
				[
					DataHandle->CreatePropertyNameWidget()
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					DataHandle->CreatePropertyValueWidget()
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 0.0f, 0.0f, 2.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					DataPathText.ToSharedRef()
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_DamagePtrCustomization::OnSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_DamagePtrCustomization::OnBrowseClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Browse"))
					]
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				PropertyView.ToSharedRef()
			]
		];
}

void FCsData_DamagePtrCustomization::OnDataChanged()
{
	UObject* O = nullptr;
	DataHandle->GetValue(O);

	PropertyView->SetObject(O);

	if (O)
	{
		FString Path = O->GetPathName();
		int32 Index = INDEX_NONE;
		Path.FindLastChar('.', Index);
		Path = Path.Left(Index);
		DataPathText->SetText(FText::FromString(Path));
	}
}

FReply FCsData_DamagePtrCustomization::OnSaveClicked()
{
	UObject* O = nullptr;
	DataHandle->GetValue(O);

	if (O)
	{
		TArray<UPackage*> PackagesToSave;
		PackagesToSave.Add(O->GetOutermost());
		FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, /*bCheckDirty=*/ false, /*bPromptToSave=*/ false);
	}
	return FReply::Handled();
}

FReply FCsData_DamagePtrCustomization::OnBrowseClicked()
{
	UObject* O = nullptr;
	DataHandle->GetValue(O);

	if (O)
	{
		TArray<UObject*> Objects;
		Objects.Add(O);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
