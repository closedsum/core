// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsDataNoPropertyView_ECsProjectileCustomization.h"
#include "CsPrjEditor.h"

// Types
#include "Types/CsTypes_Projectile.h"
#include "DetailCustomizations/EnumStruct/ECsProjectileCustomization.h"
// Library
#include "Data/CsPrjLibrary_DataRootSet.h"

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

#define LOCTEXT_NAMESPACE "CsData_ECsTestCustomization"

// Cached
#pragma region

namespace NCsDataNoPropertyViewECsProjectileCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString OnDataTableBrowseClicked = TEXT("FCsData_ECsProjectileCustomization::OnDataTableBrowseClicked");
			const FString GetDataAssociatedWithValue = TEXT("FCsData_ECsProjectileCustomization::GetDataAssociatedWithValue");
			const FString OnValueChanged = TEXT("FCsData_ECsProjectileCustomization::OnValueChanged");
		}
	}
}

#pragma endregion Cached

TSharedRef<IPropertyTypeCustomization> FCsDataNoPropertyView_ECsProjectileCustomization::MakeInstance()
{
	return MakeShareable(new FCsDataNoPropertyView_ECsProjectileCustomization);
}

void FCsDataNoPropertyView_ECsProjectileCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	StructPropertyHandle->MarkResetToDefaultCustomized();

	ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsDataNoPropertyView_ECsProjectile, Value));

	ValueTypeInterface  = FECsProjectileCustomization::MakeInstance();
	ValuePropertyWidget = MakeShareable(new FDetailWidgetRow);

	ValueTypeInterface->CustomizeHeader(ValueHandle.ToSharedRef(), ValuePropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);
	
	FECsProjectileCustomization* Instance = (FECsProjectileCustomization*)(ValueTypeInterface.Get());
	Instance->OnSelectionChanged_Event.AddRaw(this, &FCsDataNoPropertyView_ECsProjectileCustomization::OnValueChanged);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			ValuePropertyWidget->ValueContent().Widget
		];
}

void FCsDataNoPropertyView_ECsProjectileCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
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
					.OnClicked(this, &FCsDataNoPropertyView_ECsProjectileCustomization::OnDataTableBrowseClicked)
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
					.OnClicked(this, &FCsDataNoPropertyView_ECsProjectileCustomization::OnDataSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsDataNoPropertyView_ECsProjectileCustomization::OnDataBrowseClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Browse"))
					]
				]
			]
		];
}

FReply FCsDataNoPropertyView_ECsProjectileCustomization::OnDataTableBrowseClicked()
{
	using namespace NCsDataNoPropertyViewECsProjectileCustomization::NCached;

	const FString& Context = Str::OnDataTableBrowseClicked;

	typedef NCsProjectile::NDataRootSet::FLibrary DataRootSetLibrary;
	typedef FCsPrjDataRootSet::EMember MemberType;

	UObject* O = DataRootSetLibrary::GetSafeDataTable(Context, nullptr, MemberType::Projectiles);

	if (O)
	{
		TArray<UObject*> Objects;
		Objects.Add(O);

		GEditor->SyncBrowserToObjects(Objects);
	}
	return FReply::Handled();
}

UObject* FCsDataNoPropertyView_ECsProjectileCustomization::GetDataAssociatedWithValue()
{
	using namespace NCsDataNoPropertyViewECsProjectileCustomization::NCached;

	const FString& Context = Str::GetDataAssociatedWithValue;

	FECsProjectileCustomization* Instance = (FECsProjectileCustomization*)(ValueTypeInterface.Get());

	TSharedPtr<FString> DisplayName = Instance->GetSelectedDisplayName();
	const FString& DisplayNameRef	= DisplayName.ToSharedRef().Get();

	if (EMCsProjectile::Get().IsValidEnumByDisplayName(DisplayNameRef))
	{
		FECsProjectile Enum = EMCsProjectile::Get().GetEnumByDisplayName(DisplayNameRef);

		typedef NCsProjectile::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsPrjDataRootSet::EMember MemberType;

		if (FCsProjectileEntry* Row = DataRootSetLibrary::GetSafeDataTableRow<FCsProjectileEntry>(Context, nullptr, MemberType::Projectiles, Enum.GetFName()))
		{
			return Row->Data.SafeLoadSoftClass(Context);
		}
	}
	return nullptr;
}

void FCsDataNoPropertyView_ECsProjectileCustomization::OnValueChanged()
{
	using namespace NCsDataNoPropertyViewECsProjectileCustomization::NCached;

	const FString& Context = Str::OnValueChanged;

	// DataTable
	{
		typedef NCsProjectile::NDataRootSet::FLibrary DataRootSetLibrary;
		typedef FCsPrjDataRootSet::EMember MemberType;

		FString Path;

		if (DataRootSetLibrary::GetSafeDataTablePath(Context, nullptr, MemberType::Projectiles, Path))
		{
			DataTablePathText->SetText(FText::FromString(Path));
		}
	}
	// Data
	UObject* O = GetDataAssociatedWithValue();

	if (O)
	{
		FString Path = O->GetPathName();
		int32 Index = INDEX_NONE;
		Path.FindLastChar('.', Index);
		Path = Path.Left(Index);
		DataPathText->SetText(FText::FromString(Path));
	}
}

FReply FCsDataNoPropertyView_ECsProjectileCustomization::OnDataSaveClicked()
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

FReply FCsDataNoPropertyView_ECsProjectileCustomization::OnDataBrowseClicked()
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
