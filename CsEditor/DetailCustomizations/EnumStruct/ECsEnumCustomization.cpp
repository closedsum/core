// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsEnumCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Types/CsTypes_Primitive.h"

#define LOCTEXT_NAMESPACE "ECsEnumCustomization"


FECsEnumCustomization::FECsEnumCustomization()
{
}

void FECsEnumCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	SetPropertyHandles(StructPropertyHandle);
	
	// Alter DisplayNameList for Properties that are visible and should NOT be edited
	UProperty* Property				   = StructPropertyHandle->GetProperty();
	const uint64 DisplayAsDropDownMask = (1 << UP::EditAnywhere);

	if (!Property->HasAnyPropertyFlags(DisplayAsDropDownMask))
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
		.OnGenerateWidget(this, &FECsEnumCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FECsEnumCustomization::OnSelectionChanged)
		.OnComboBoxOpening(this, &FECsEnumCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedDisplayName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FECsEnumCustomization::GetComboBoxContent)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
}

void FECsEnumCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle){}

void FECsEnumCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FECsEnumCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FECsEnumCustomization::OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo)
{
	if (DisplayNameItem.IsValid())
	{
		SetEnumWithDisplayName(*DisplayNameItem);
	}
}

void FECsEnumCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		check(DisplayNameComboBox.IsValid());
		DisplayNameComboBox->SetSelectedItem(SelectedDisplayName);
	}
}

TSharedPtr<FString> FECsEnumCustomization::GetSelectedDisplayName() const
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

void FECsEnumCustomization::SetEnumWithDisplayName(const FString& DisplayName){}

void FECsEnumCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	check(DisplayNameHandle.IsValid());
	DisplayNameHandle->GetValue(OutDisplayName);
}

FText FECsEnumCustomization::GetComboBoxContent() const
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		return FText::FromString(*SelectedDisplayName);
	}
	return LOCTEXT("Invalid", "Invalid");
}

#undef LOCTEXT_NAMESPACE
