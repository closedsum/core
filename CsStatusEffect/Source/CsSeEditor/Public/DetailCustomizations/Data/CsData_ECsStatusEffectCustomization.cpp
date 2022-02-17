// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsData_ECsStatusEffectCustomization.h"
#include "CsSeEditor.h"

// Types
#include "Types/CsTypes_StatusEffect.h"
#include "DetailCustomizations/EnumStruct/ECsStatusEffectCustomization.h"
// Library
#include "Data/CsSeLibrary_DataRootSet.h"

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

#define LOCTEXT_NAMESPACE "CsData_ECsStatusEffectCustomization"

// Cached
#pragma region

namespace NCsDataECsStatusEffectCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString OnDataTableBrowseClicked = TEXT("FCsData_ECsStatusEffectCustomization::OnDataTableBrowseClicked");
			const FString GetDataAssociatedWithValue = TEXT("FCsData_ECsStatusEffectCustomization::GetDataAssociatedWithValue");
			const FString OnValueChanged = TEXT("FCsData_ECsStatusEffectCustomization::OnValueChanged");
		}
	}
}

#pragma endregion Cached

TSharedRef<IPropertyTypeCustomization> FCsData_ECsStatusEffectCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_ECsStatusEffectCustomization);
}

void FCsData_ECsStatusEffectCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsStatusEffect, Value));

	ValueTypeInterface  = FECsStatusEffectCustomization::MakeInstance();
	ValuePropertyWidget = MakeShareable(new FDetailWidgetRow);

	ValueTypeInterface->CustomizeHeader(ValueHandle.ToSharedRef(), ValuePropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);
	
	FECsStatusEffectCustomization* Instance = (FECsStatusEffectCustomization*)(ValueTypeInterface.Get());
	Instance->OnSelectionChanged_Event.AddRaw(this, &FCsData_ECsStatusEffectCustomization::OnValueChanged);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			ValuePropertyWidget->ValueContent().Widget
		];
}

void FCsData_ECsStatusEffectCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
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
					.OnClicked(this, &FCsData_ECsStatusEffectCustomization::OnDataTableBrowseClicked)
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
					.OnClicked(this, &FCsData_ECsStatusEffectCustomization::OnDataSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_ECsStatusEffectCustomization::OnDataBrowseClicked)
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

FReply FCsData_ECsStatusEffectCustomization::OnDataTableBrowseClicked()
{
	using namespace NCsDataECsStatusEffectCustomization::NCached;

	const FString& Context = Str::OnDataTableBrowseClicked;

	typedef NCsStatusEffect::NDataRootSet::FLibrary DataRootSetLibrary;
	typedef FCsSeDataRootSet::EMember MemberType;

	UObject* O = DataRootSetLibrary::GetSafeDataTable(Context, nullptr, MemberType::StatusEffects);

	if (O)
	{
		TArray<UObject*> Objects;
		Objects.Add(O);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

UObject* FCsData_ECsStatusEffectCustomization::GetDataAssociatedWithValue()
{
	using namespace NCsDataECsStatusEffectCustomization::NCached;

	const FString& Context = Str::GetDataAssociatedWithValue;

	FECsStatusEffectCustomization* Instance = (FECsStatusEffectCustomization*)(ValueTypeInterface.Get());

	TSharedPtr<FString> DisplayName = Instance->GetSelectedDisplayName();
	const FString& DisplayNameRef	= DisplayName.ToSharedRef().Get();

	if (EMCsStatusEffect::Get().IsValidEnumByDisplayName(DisplayNameRef))
	{
		const FECsStatusEffect& Enum = EMCsStatusEffect::Get().GetEnumByDisplayName(DisplayNameRef);

		typedef NCsStatusEffect::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsSeDataRootSet::EMember MemberType;

		if (FCsStatusEffectEntry* Row = DataRootSetLibrary::GetSafeDataTableRow<FCsStatusEffectEntry>(Context, nullptr, MemberType::StatusEffects, Enum.GetFName()))
		{
			return Row->Data.SafeLoadSoftClass(Context);
		}
	}
	return nullptr;
}

void FCsData_ECsStatusEffectCustomization::OnValueChanged()
{
	using namespace NCsDataECsStatusEffectCustomization::NCached;

	const FString& Context = Str::OnValueChanged;

	// DataTable
	{
		typedef NCsStatusEffect::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsSeDataRootSet::EMember MemberType;

		FString Path;

		if (DataRootSetLibrary::GetSafeDataTablePath(Context, nullptr, MemberType::StatusEffects, Path))
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

FReply FCsData_ECsStatusEffectCustomization::OnDataSaveClicked()
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

FReply FCsData_ECsStatusEffectCustomization::OnDataBrowseClicked()
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
