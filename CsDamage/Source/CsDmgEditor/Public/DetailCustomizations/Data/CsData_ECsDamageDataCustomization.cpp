// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsData_ECsDamageDataCustomization.h"
#include "CsDmgEditor.h"

// Types
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
#include "DetailCustomizations/EnumStruct/ECsDamageDataCustomization.h"
// Library
#include "Data/CsDmgLibrary_DataRootSet.h"

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

#define LOCTEXT_NAMESPACE "CsData_ECsDamageDataCustomization"

// Cached
#pragma region

namespace NCsDataECsDamageDataCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString OnDataTableBrowseClicked = TEXT("FCsData_ECsDamageDataCustomization::OnDataTableBrowseClicked");
			const FString GetDataAssociatedWithValue = TEXT("FCsData_ECsDamageDataCustomization::GetDataAssociatedWithValue");
			const FString OnValueChanged = TEXT("FCsData_ECsDamageDataCustomization::OnValueChanged");
		}
	}
}

#pragma endregion Cached

TSharedRef<IPropertyTypeCustomization> FCsData_ECsDamageDataCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_ECsDamageDataCustomization);
}

void FCsData_ECsDamageDataCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsDamageData, Value));

	ValueTypeInterface  = FECsDamageDataCustomization::MakeInstance();
	ValuePropertyWidget = MakeShareable(new FDetailWidgetRow);

	ValueTypeInterface->CustomizeHeader(ValueHandle.ToSharedRef(), ValuePropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);
	
	FECsDamageDataCustomization* Instance = (FECsDamageDataCustomization*)(ValueTypeInterface.Get());
	Instance->OnSelectionChanged_Event.AddRaw(this, &FCsData_ECsDamageDataCustomization::OnValueChanged);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			ValuePropertyWidget->ValueContent().Widget
		];
}

void FCsData_ECsDamageDataCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(/*bUpdateFromSelection=*/ false, /*bLockable=*/ false, /*bAllowSearch=*/ true, /*InNameAreaSettings=*/ FDetailsViewArgs::HideNameArea, /*bHideSelectionTip=*/ true);
	PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

	SAssignNew(DataPathText, STextBlock);
	SAssignNew(DataTablePathText, STextBlock);

	OnValueChanged();

	StructBuilder.AddCustomRow(LOCTEXT("MyStructRow", "MyStruct"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(FText::FromString("Data Table Path:"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5.0f, 0.0f, 0.0f, 0.0f)
				.VAlign(VAlign_Center)
				[
					DataTablePathText.ToSharedRef()
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_ECsDamageDataCustomization::OnDataTableBrowseClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Browse"))
					]
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
					SNew(STextBlock).Text(FText::FromString("Data Path:"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5.0f, 0.0f, 0.0f, 0.0f)
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
					.OnClicked(this, &FCsData_ECsDamageDataCustomization::OnDataSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_ECsDamageDataCustomization::OnDataBrowseClicked)
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

FReply FCsData_ECsDamageDataCustomization::OnDataTableBrowseClicked()
{
	using namespace NCsDataECsDamageDataCustomization::NCached;

	const FString& Context = Str::OnDataTableBrowseClicked;

	typedef NCsDamage::NDataRootSet::FLibrary DataRootSetLibrary;
	typedef FCsDmgDataRootSet::EMember MemberType;

	UObject* O = DataRootSetLibrary::GetSafeDataTable(Context, nullptr, MemberType::Damages);

	if (O)
	{
		TArray<UObject*> Objects;
		Objects.Add(O);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

UObject* FCsData_ECsDamageDataCustomization::GetDataAssociatedWithValue()
{
	using namespace NCsDataECsDamageDataCustomization::NCached;

	const FString& Context = Str::GetDataAssociatedWithValue;

	FECsDamageDataCustomization* Instance = (FECsDamageDataCustomization*)(ValueTypeInterface.Get());

	TSharedPtr<FString> DisplayName = Instance->GetSelectedDisplayName();
	const FString& DisplayNameRef	= DisplayName.ToSharedRef().Get();

	if (EMCsDamageData::Get().IsValidEnumByDisplayName(DisplayNameRef))
	{
		const FECsDamageData& Enum = EMCsDamageData::Get().GetEnumByDisplayName(DisplayNameRef);

		typedef NCsDamage::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsDmgDataRootSet::EMember MemberType;

		if (FCsDamageDataEntry* Row = DataRootSetLibrary::GetSafeDataTableRow<FCsDamageDataEntry>(Context, nullptr, MemberType::Damages, Enum.GetFName()))
		{
			return Row->Data.SafeLoadSoftClass(Context);
		}
	}
	return nullptr;
}

void FCsData_ECsDamageDataCustomization::OnValueChanged()
{
	using namespace NCsDataECsDamageDataCustomization::NCached;

	const FString& Context = Str::OnValueChanged;

	// DataTable
	{
		typedef NCsDamage::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsDmgDataRootSet::EMember MemberType;

		FString Path;

		if (DataRootSetLibrary::GetSafeDataTablePath(Context, nullptr, MemberType::Damages, Path))
		{
			DataTablePathText->SetText(FText::FromString(Path));
		}
	}
	// Data
	UObject* O = GetDataAssociatedWithValue();

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

FReply FCsData_ECsDamageDataCustomization::OnDataSaveClicked()
{
	UObject* O = GetDataAssociatedWithValue();

	if (O)
	{
		TArray<UPackage*> PackagesToSave;
		PackagesToSave.Add(O->GetOutermost());
		FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, /*bCheckDirty=*/ false, /*bPromptToSave=*/ false);
	}
	return FReply::Handled();
}

FReply FCsData_ECsDamageDataCustomization::OnDataBrowseClicked()
{
	UObject* O = GetDataAssociatedWithValue();

	if (O)
	{
		TArray<UObject*> Objects;
		Objects.Add(O);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE
