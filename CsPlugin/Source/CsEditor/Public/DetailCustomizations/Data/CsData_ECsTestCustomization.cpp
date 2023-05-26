// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsData_ECsTestCustomization.h"
#include "CsEditor.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// AssetRegistry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Test
#include "Test/CsData_ECsTest.h"
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionCustomization.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Data
#include "Data/CsGetDataRootSet.h"
// Helper
#include "FileHelpers.h"

#define LOCTEXT_NAMESPACE "CsData_ECsTestCustomization"

TSharedRef<IPropertyTypeCustomization> FCsData_ECsTestCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_ECsTestCustomization);
}

void FCsData_ECsTestCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	ActionHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsTest, Action));

	CustomTypeInterface  = FECsInputActionCustomization::MakeInstance();
	CustomPropertyWidget = MakeShareable(new FDetailWidgetRow);

	CustomTypeInterface->CustomizeHeader(ActionHandle.ToSharedRef(), CustomPropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);
	
	DataHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsTest, Data));

	DataHandle->SetOnPropertyValueChanged(FSimpleDelegate::CreateRaw(this, &FCsData_ECsTestCustomization::OnDataChanged));

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			CustomPropertyWidget->ValueContent().Widget
		];
}

void FCsData_ECsTestCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(/*bUpdateFromSelection=*/ false, /*bLockable=*/ false, /*bAllowSearch=*/ true, /*InNameAreaSettings=*/ FDetailsViewArgs::HideNameArea, /*bHideSelectionTip=*/ true);
	PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

	SAssignNew(DataPathText, STextBlock);

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
					.OnClicked(this, &FCsData_ECsTestCustomization::OnSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_ECsTestCustomization::OnBrowseClicked)
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

	return;

	UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>();

	UClass* Class					  = Settings->DataRootSet.LoadSynchronous();
	UObject* O						  = Class ? Class->GetDefaultObject<UObject>() : nullptr;
	ICsGetDataRootSet* GetDataRootSet = O ? Cast<ICsGetDataRootSet>(O) : nullptr;
	
	if (GetDataRootSet)
	{
		const FCsDataRootSet& DataRootSet = GetDataRootSet->GetCsDataRootSet();

		if (UDataTable* Datas = DataRootSet.Datas)
		{
			const TMap<FName, uint8*>& RowMap = Datas->GetRowMap();

			for (const TPair<FName, uint8*>& Pair : RowMap)
			{
				const FName& RowName	  = Pair.Key;
				FCsDataEntry_Data* RowPtr = reinterpret_cast<FCsDataEntry_Data*>(Pair.Value);

				UClass* C	 = RowPtr->Data.LoadSynchronous();
				UObject* DOb = C ? C->GetDefaultObject() : nullptr;
				
				if (DOb)
				{
					PropertyView->SetObject(DOb);

					StructBuilder.AddCustomRow(LOCTEXT("MyStructRow", "MyStruct"))
						[
							PropertyView.ToSharedRef()
						];
					break;
				}
			}
		}
	}
}

void FCsData_ECsTestCustomization::OnDataChanged()
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

FReply FCsData_ECsTestCustomization::OnSaveClicked()
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

FReply FCsData_ECsTestCustomization::OnBrowseClicked()
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
