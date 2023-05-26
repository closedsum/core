// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsEnumStructMaskCustomization.h"
#include "CsEditor.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"
// AssetRegistry
#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
// Blueprint
#include "Factories/BlueprintFactory.h"

#define LOCTEXT_NAMESPACE "ECsEnumStructMaskCustomization"


FECsEnumStructMaskCustomization::FECsEnumStructMaskCustomization()
{
	bPerformDropDownCheck = true;
}

void FECsEnumStructMaskCustomization::Log(const FString& Str)
{
	UE_LOG(LogCsEditor, Warning, TEXT("%s"), *Str);
}

void FECsEnumStructMaskCustomization::CustomPopulateEnumMap()
{
}

void FECsEnumStructMaskCustomization::PopulateEnumMapFromSettings()
{
}

void FECsEnumStructMaskCustomization::AddEnumToMap(const FString& Name)
{
}

const FString& FECsEnumStructMaskCustomization::GetEnumStructName()
{
	return NCsCached::Str::Empty;
}

const FName& FECsEnumStructMaskCustomization::GetEnumStructFName()
{
	return NCsCached::Name::None;
}

const FECsUserDefinedEnum& FECsEnumStructMaskCustomization::GetUserDefinedEnumType()
{
	return EMCsUserDefinedEnum::Get().GetMAX();
}

void FECsEnumStructMaskCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	SetPropertyHandles(StructPropertyHandle);
	
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

	HeaderRow.NameContent()
	[
		SNew(STextBlock)
		.Text(StructPropertyHandle->GetPropertyDisplayName())
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SAssignNew(DisplayNameComboBox, SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&DisplayNameList)
		.OnGenerateWidget(this, &FECsEnumStructMaskCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FECsEnumStructMaskCustomization::OnSelectionChanged)
		.OnComboBoxOpening(this, &FECsEnumStructMaskCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedDisplayName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FECsEnumStructMaskCustomization::GetComboBoxContent)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
}

void FECsEnumStructMaskCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle){}

void FECsEnumStructMaskCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FECsEnumStructMaskCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FECsEnumStructMaskCustomization::OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo)
{
	if (DisplayNameItem.IsValid())
	{
		SetEnumWithDisplayName(*DisplayNameItem);
	}
}

void FECsEnumStructMaskCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		check(DisplayNameComboBox.IsValid());
		DisplayNameComboBox->SetSelectedItem(SelectedDisplayName);
	}
}

TSharedPtr<FString> FECsEnumStructMaskCustomization::GetSelectedDisplayName() const
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

void FECsEnumStructMaskCustomization::SetEnumWithDisplayName(const FString& DisplayName){}

void FECsEnumStructMaskCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const {}

FText FECsEnumStructMaskCustomization::GetComboBoxContent() const
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		return FText::FromString(*SelectedDisplayName);
	}
	return LOCTEXT("Invalid", "Invalid");
}

#undef LOCTEXT_NAMESPACE
