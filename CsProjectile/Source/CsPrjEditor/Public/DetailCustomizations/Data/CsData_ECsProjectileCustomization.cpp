// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/Data/CsData_ECsProjectileCustomization.h"
#include "CsEditor.h"

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
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Helper
#include "FileHelpers.h"

#define LOCTEXT_NAMESPACE "CsData_ECsTestCustomization"

// Cached
#pragma region

namespace NCsDataECsProjectileCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString GetDataAssociatedWithValue = TEXT("FCsData_ECsProjectileCustomization::GetDataAssociatedWithValue");
			const FString OnValueChanged = TEXT("FCsData_ECsProjectileCustomization::OnValueChanged");
		}
	}
}

#pragma endregion Cached

TSharedRef<IPropertyTypeCustomization> FCsData_ECsProjectileCustomization::MakeInstance()
{
	return MakeShareable(new FCsData_ECsProjectileCustomization);
}

void FCsData_ECsProjectileCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ECsProjectile, Value));

	ValueTypeInterface  = FECsProjectileCustomization::MakeInstance();
	ValuePropertyWidget = MakeShareable(new FDetailWidgetRow);

	ValueTypeInterface->CustomizeHeader(ValueHandle.ToSharedRef(), ValuePropertyWidget.ToSharedRef().Get(), StructCustomizationUtils);
	
	FECsProjectileCustomization* Instance = (FECsProjectileCustomization*)(ValueTypeInterface.Get());
	Instance->OnSelectionChanged_Event.AddRaw(this, &FCsData_ECsProjectileCustomization::OnValueChanged);

	HeaderRow.NameContent()
		[
			StructPropertyHandle->CreatePropertyNameWidget()
		]
	.ValueContent()
		[
			ValuePropertyWidget->ValueContent().Widget
		];
}

void FCsData_ECsProjectileCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FPropertyEditorModule& EditModule = FModuleManager::Get().GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(/*bUpdateFromSelection=*/ false, /*bLockable=*/ false, /*bAllowSearch=*/ true, /*InNameAreaSettings=*/ FDetailsViewArgs::HideNameArea, /*bHideSelectionTip=*/ true);
	PropertyView = EditModule.CreateDetailView(DetailsViewArgs);

	SAssignNew(DataPathText, STextBlock);

	OnValueChanged();

	StructBuilder.AddCustomRow(LOCTEXT("MyStructRow", "MyStruct"))
		[
			SNew(SVerticalBox)
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
					.OnClicked(this, &FCsData_ECsProjectileCustomization::OnSaveClicked)
					.Content()
					[
						SNew(STextBlock).Text(FText::FromString("Save"))
					]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &FCsData_ECsProjectileCustomization::OnBrowseClicked)
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

UObject* FCsData_ECsProjectileCustomization::GetDataAssociatedWithValue()
{
	using namespace NCsDataECsProjectileCustomization::NCached;

	const FString& Context = Str::GetDataAssociatedWithValue;

	ValueTypeInterface					  = FECsProjectileCustomization::MakeInstance();
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
			return Row->Data.SafeLoad(Context);
		}
	}
	return nullptr;
}

void FCsData_ECsProjectileCustomization::OnValueChanged()
{
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

FReply FCsData_ECsProjectileCustomization::OnSaveClicked()
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

FReply FCsData_ECsProjectileCustomization::OnBrowseClicked()
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
