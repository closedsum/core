// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsEnumStructCustomization.h"
#include "CsEnumEditor.h"

// Types

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// AssetRegistry
#include "AssetRegistry/AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Blueprint
#include "Factories/BlueprintFactory.h"

#include "Engine/UserDefinedEnum.h"

#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"

#define LOCTEXT_NAMESPACE "ECsEnumStructCustomization"

namespace NCsEnumStructCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString Empty = TEXT("");
;		}

		namespace Name
		{
			const FName None = NAME_None;
		}
	}
}

FECsEnumStructCustomization::FECsEnumStructCustomization()
{
	bPerformDropDownCheck = true;
}

void FECsEnumStructCustomization::Log(const FString& Str)
{
	UE_LOG(LogCsEnumEditor, Warning, TEXT("%s"), *Str);
}

void FECsEnumStructCustomization::CustomPopulateEnumMap()
{
}

void FECsEnumStructCustomization::PopulateEnumMapFromSettings()
{
}

void FECsEnumStructCustomization::AddPropertyChange()
{
}

void FECsEnumStructCustomization::AddEnumToMap(const FString& Name)
{
}

const FString& FECsEnumStructCustomization::GetEnumStructName()
{
	return NCsEnumStructCustomization::NCached::Str::Empty;
}

const FName& FECsEnumStructCustomization::GetEnumStructFName()
{
	return NCsEnumStructCustomization::NCached::Name::None;
}

const FECsUserDefinedEnum& FECsEnumStructCustomization::GetUserDefinedEnumType()
{
	return EMCsUserDefinedEnum::Get().GetMAX();
}

void FECsEnumStructCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	SetPropertyHandles(StructPropertyHandle);
	
	AddPropertyChange();

	// Alter DisplayNameList for Properties that are visible and should NOT be edited
	if (bPerformDropDownCheck)
	{
		FProperty* Property	= StructPropertyHandle->GetProperty();
		UPackage* Package   = Cast<UPackage>(Property->GetOutermost());

		bool EditingTemplate = Package && Package->GetName().StartsWith(TEXT("/Script"));

		if (Property->HasAnyPropertyFlags(CPF_EditConst) ||					// NOT Editable in Editor
			(EditingTemplate &&												// EditDefaultsOnly
			 Property->HasAnyPropertyFlags(CPF_DisableEditOnTemplate)))
		{
			const int32 Count = DisplayNameList.Num();

			FString DisplayName;
			GetDisplayNamePropertyValue(DisplayName);

			for (int32 I = Count - 1; I >= 0; --I)
			{
				if (DisplayName == *DisplayNameList[I].Get())
					continue;
				DisplayNameList.RemoveAt(I);
			}
		}
	}

	TSharedPtr<FString> InitialSelectedDisplayName = GetSelectedDisplayName();

	if (InitialSelectedDisplayName.IsValid())
	{
		SetEnumWithDisplayName(*InitialSelectedDisplayName.Get());
	}

	StructPropertyHandle->MarkResetToDefaultCustomized();

	HeaderRow.NameContent()
	[
		SNew(STextBlock)
		.Text(StructPropertyHandle->GetPropertyDisplayName())
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			SAssignNew(DisplayNameComboBox, SComboBox<TSharedPtr<FString>>)
			.OptionsSource(&DisplayNameList)
			.OnGenerateWidget(this, &FECsEnumStructCustomization::OnGenerateWidget)
			.OnSelectionChanged(this, &FECsEnumStructCustomization::OnSelectionChanged)
			.OnComboBoxOpening(this, &FECsEnumStructCustomization::OnComboBoxOpening)
			.InitiallySelectedItem(InitialSelectedDisplayName)
			.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
			.ContentPadding(FMargin(2.0f, 2.0f))
			.Content()
			[
				SNew(STextBlock)
				.Text(this, &FECsEnumStructCustomization::GetComboBoxContent)
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		[
			StructPropertyHandle->CreateDefaultPropertyButtonWidgets()
		]
	];
}

void FECsEnumStructCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle){}

void FECsEnumStructCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FECsEnumStructCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FECsEnumStructCustomization::OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo)
{
	if (DisplayNameItem.IsValid())
	{
		SetEnumWithDisplayName(*DisplayNameItem);

		OnSelectionChanged_Event.Broadcast();
	}
}

void FECsEnumStructCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		check(DisplayNameComboBox.IsValid());
		DisplayNameComboBox->SetSelectedItem(SelectedDisplayName);
	}
}

TSharedPtr<FString> FECsEnumStructCustomization::GetSelectedDisplayName() const
{
	const int32 Count = DisplayNameList.Num();

	if (Count <= 0)
	{
		return NULL;
	}

	FString DisplayName;
	GetDisplayNamePropertyValue(DisplayName);

	for (int32 I = 0; I < Count; ++I)
	{
		if (DisplayName == *DisplayNameList[I].Get())
		{
			return DisplayNameList[I];
		}
	}
	return DisplayNameList[0];
}

void FECsEnumStructCustomization::SetEnumWithDisplayName(const FString& DisplayName){}

void FECsEnumStructCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const {}

FText FECsEnumStructCustomization::GetComboBoxContent() const
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		return FText::FromString(*SelectedDisplayName);
	}
	return LOCTEXT("Invalid", "Invalid");
}

#undef LOCTEXT_NAMESPACE
