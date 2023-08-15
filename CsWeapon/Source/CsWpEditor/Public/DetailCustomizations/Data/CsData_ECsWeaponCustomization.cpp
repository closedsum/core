// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsData_ECsWeaponCustomization.h"
#include "CsWpEditor.h"

// Types
#include "Types/CsTypes_Weapon.h"
#include "DetailCustomizations/EnumStruct/ECsWeaponCustomization.h"
// Library
#include "Data/CsWpLibrary_DataRootSet.h"

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

#define LOCTEXT_NAMESPACE "CsData_ECsWeaponCustomization"

// Cached
#pragma region

namespace NCsDataECsWeaponCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString OnDataTableBrowseClicked = TEXT("FCsData_ECsWeaponCustomization::OnDataTableBrowseClicked");
			const FString GetDataAssociatedWithValue = TEXT("FCsData_ECsWeaponCustomization::GetDataAssociatedWithValue");
			const FString OnValueChanged = TEXT("FCsData_ECsWeaponCustomization::OnValueChanged");
		}
	}
}

#pragma endregion Cached

TSharedRef<IPropertyTypeCustomization> FCsData_ECsWeaponCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_ECsWeaponCustomization);
}

void FCsData_ECsWeaponCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsWeapon, Value));

	ValueTypeInterface  = FECsWeaponCustomization::MakeInstance();
	ValuePropertyWidget = MakeShareable(new FDetailWidgetRow);

	ValueTypeInterface->CustomizeHeader(ValueHandle.ToSharedRef(), ValuePropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);
	
	FECsWeaponCustomization* Instance = (FECsWeaponCustomization*)(ValueTypeInterface.Get());
	Instance->OnSelectionChanged_Event.AddRaw(this, &FCsData_ECsWeaponCustomization::OnValueChanged);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			ValuePropertyWidget->ValueContent().Widget
		];
}

void FCsData_ECsWeaponCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
					.OnClicked(this, &FCsData_ECsWeaponCustomization::OnDataTableBrowseClicked)
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
					.OnClicked(this, &FCsData_ECsWeaponCustomization::OnDataSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_ECsWeaponCustomization::OnDataBrowseClicked)
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

FReply FCsData_ECsWeaponCustomization::OnDataTableBrowseClicked()
{
	using namespace NCsDataECsWeaponCustomization::NCached;

	const FString& Context = Str::OnDataTableBrowseClicked;

	typedef NCsWeapon::NDataRootSet::FLibrary DataRootSetLibrary;
	typedef FCsWpDataRootSet::EMember MemberType;

	UObject* O = DataRootSetLibrary::GetSafeDataTable(Context, nullptr, MemberType::Weapons);

	if (O)
	{
		TArray<UObject*> Objects;
		Objects.Add(O);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

UObject* FCsData_ECsWeaponCustomization::GetDataAssociatedWithValue()
{
	using namespace NCsDataECsWeaponCustomization::NCached;

	const FString& Context = Str::GetDataAssociatedWithValue;

	FECsWeaponCustomization* Instance = (FECsWeaponCustomization*)(ValueTypeInterface.Get());

	TSharedPtr<FString> DisplayName = Instance->GetSelectedDisplayName();
	const FString& DisplayNameRef	= DisplayName.ToSharedRef().Get();

	if (EMCsWeapon::Get().IsValidEnumByDisplayName(DisplayNameRef))
	{
		const FECsWeapon& Enum = EMCsWeapon::Get().GetEnumByDisplayName(DisplayNameRef);

		typedef NCsWeapon::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsWpDataRootSet::EMember MemberType;

		if (FCsWeaponEntry* Row = DataRootSetLibrary::GetSafeDataTableRow<FCsWeaponEntry>(Context, nullptr, MemberType::Weapons, Enum.GetFName()))
		{
			return Row->Data.SafeLoadSoftClass(Context);
		}
	}
	return nullptr;
}

void FCsData_ECsWeaponCustomization::OnValueChanged()
{
	using namespace NCsDataECsWeaponCustomization::NCached;

	const FString& Context = Str::OnValueChanged;

	// DataTable
	{
		typedef NCsWeapon::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsWpDataRootSet::EMember MemberType;

		FString Path;

		if (DataRootSetLibrary::GetSafeDataTablePath(Context, nullptr, MemberType::Weapons, Path))
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

FReply FCsData_ECsWeaponCustomization::OnDataSaveClicked()
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

FReply FCsData_ECsWeaponCustomization::OnDataBrowseClicked()
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
