// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/ShortCode/CsDataShortCodeCustomization.h"
#include "CsEditor.h"

// Library
#include "Library/CsLibrary_Asset.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Editor.h"
#include "CsEdEngine.h"
// Data
#include "Data/CsDataMapping.h"

#define LOCTEXT_NAMESPACE "CsShortCodeCustomization"


FCsDataShortCodeCustomization::FCsDataShortCodeCustomization()
{
}

void FCsDataShortCodeCustomization::Init()
{
	uint8 DataTypeAsByte;
	AssetTypeHandle->GetValue(DataTypeAsByte);

	UCsDataMapping* DataMapping = Cast<UCsEdEngine>(GEditor)->DataMapping;

	const FECsDataType& DataType = EMCsDataType::Get()[DataTypeAsByte];

	if (TArray<FCsDataMappingEntry>* EntriesPtr = DataMapping->GetDataMappings(DataType))
	{
		TArray<FCsDataMappingEntry>& Entries = *EntriesPtr;

		for (const FCsDataMappingEntry& Entry : Entries)
		{
			DisplayNameList.Add(MakeShareable(new FString(Entry.ShortCode.ToString())));
		}
	}
}

TSharedRef<IPropertyTypeCustomization> FCsDataShortCodeCustomization::MakeInstance()
{
	return MakeShareable(new FCsDataShortCodeCustomization);
}

void FCsDataShortCodeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	SetPropertyHandles(StructPropertyHandle);

	Init();

	TSharedPtr<FString> InitialSelectedDisplayName = GetSelectedDisplayName();

	if (InitialSelectedDisplayName.IsValid())
	{
		SetShortCodeWithDisplayName(*InitialSelectedDisplayName.Get());
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
		.OnGenerateWidget(this, &FCsDataShortCodeCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FCsDataShortCodeCustomization::OnSelectionChanged)
		.OnComboBoxOpening(this, &FCsDataShortCodeCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedDisplayName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FCsDataShortCodeCustomization::GetComboBoxContent)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
}

void FCsDataShortCodeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	AssetTypeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ShortCode, Type));
	check(AssetTypeHandle.IsValid());
	ShortCodeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ShortCode, ShortCode));
	check(ShortCodeHandle.IsValid());
}

void FCsDataShortCodeCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FCsDataShortCodeCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FCsDataShortCodeCustomization::OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo)
{
	if (DisplayNameItem.IsValid())
	{
		SetShortCodeWithDisplayName(*DisplayNameItem);
	}
}

void FCsDataShortCodeCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		check(DisplayNameComboBox.IsValid());
		DisplayNameComboBox->SetSelectedItem(SelectedDisplayName);
	}
}

TSharedPtr<FString> FCsDataShortCodeCustomization::GetSelectedDisplayName() const
{
	const int32 Count = DisplayNameList.Num();

	if (Count <= 0)
	{
		return NULL;
	}

	FName ShortCode;
	GetDisplayNamePropertyValue(ShortCode);

	const FString& DisplayName = ShortCode.ToString();

	for (int32 I = 0; I < Count; ++I)
	{
		if (DisplayName == *DisplayNameList[I].Get())
		{
			return DisplayNameList[I];
		}
	}
	return DisplayNameList[0];
}

void FCsDataShortCodeCustomization::SetShortCodeWithDisplayName(const FString& DisplayName)
{
	check(ShortCodeHandle.IsValid());

	FName OldShortCode;
	ShortCodeHandle->GetValue(OldShortCode);

	const FName ShortCode = FName(*DisplayName);

	if (OldShortCode != ShortCode)
	{
		ShortCodeHandle->SetValue(ShortCode);
	}
}

void FCsDataShortCodeCustomization::GetDisplayNamePropertyValue(FName& OutShortCode) const
{
	check(ShortCodeHandle.IsValid());
	ShortCodeHandle->GetValue(OutShortCode);

}

FText FCsDataShortCodeCustomization::GetComboBoxContent() const
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		return FText::FromString(*SelectedDisplayName);
	}
	return LOCTEXT("None", "None");
}

#undef LOCTEXT_NAMESPACE
