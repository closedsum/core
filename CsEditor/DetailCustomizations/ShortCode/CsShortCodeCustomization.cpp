// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/ShortCode/CsShortCodeCustomization.h"
#include "CsEditor.h"
#include "Common/CsCommon_Asset.h"

#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Editor.h"
#include "CsEdEngine.h"
// Data
#include "Data/CsDataMapping.h"

#define LOCTEXT_NAMESPACE "CsShortCodeCustomization"


FCsShortCodeCustomization::FCsShortCodeCustomization()
{
}

void FCsShortCodeCustomization::Init(const FECsAssetType &AssetType)
{
	ACsDataMapping* DataMapping = Cast<UCsEdEngine>(GEditor)->DataMapping;

	TArray<FCsDataMappingEntry>* EntriesPtr = DataMapping->GetDataMappings(AssetType);
	TArray<FCsDataMappingEntry>& Entries    = *EntriesPtr;

	for (const FCsDataMappingEntry& Entry : Entries)
	{
		DisplayNameList.Add(MakeShareable(new FString(Entry.ShortCode.ToString())));
	}
}

TSharedRef<IPropertyTypeCustomization> FCsShortCodeCustomization::MakeInstance()
{
	return MakeShareable(new FCsShortCodeCustomization);
}

void FCsShortCodeCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	SetPropertyHandles(StructPropertyHandle);

	uint8 AssetTypeAsByte;
	AssetTypeHandle->GetValue(AssetTypeAsByte);

	ACsDataMapping* DataMapping = Cast<UCsEdEngine>(GEditor)->DataMapping;

	const FECsAssetType& AssetType = EMCsAssetType::Get()[AssetTypeAsByte];

	if (TArray<FCsDataMappingEntry>* EntriesPtr = DataMapping->GetDataMappings(AssetType))
	{
		TArray<FCsDataMappingEntry>& Entries = *EntriesPtr;

		for (const FCsDataMappingEntry& Entry : Entries)
		{
			DisplayNameList.Add(MakeShareable(new FString(Entry.ShortCode.ToString())));
		}
	}

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
		.OnGenerateWidget(this, &FCsShortCodeCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FCsShortCodeCustomization::OnSelectionChanged)
		.OnComboBoxOpening(this, &FCsShortCodeCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedDisplayName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FCsShortCodeCustomization::GetComboBoxContent)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
}

void FCsShortCodeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	AssetTypeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ShortCode, Type));
	check(AssetTypeHandle.IsValid());
	ShortCodeHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCsData_ShortCode, ShortCode));
	check(ShortCodeHandle.IsValid());
}

void FCsShortCodeCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

TSharedRef<SWidget> FCsShortCodeCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FCsShortCodeCustomization::OnSelectionChanged(TSharedPtr<FString> DisplayNameItem, ESelectInfo::Type SelectInfo)
{
	if (DisplayNameItem.IsValid())
	{
		SetShortCodeWithDisplayName(*DisplayNameItem);
	}
}

void FCsShortCodeCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		check(DisplayNameComboBox.IsValid());
		DisplayNameComboBox->SetSelectedItem(SelectedDisplayName);
	}
}

TSharedPtr<FString> FCsShortCodeCustomization::GetSelectedDisplayName() const
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

void FCsShortCodeCustomization::SetShortCodeWithDisplayName(const FString& DisplayName)
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

void FCsShortCodeCustomization::GetDisplayNamePropertyValue(FName& OutShortCode) const
{
	check(ShortCodeHandle.IsValid());
	ShortCodeHandle->GetValue(OutShortCode);

}

FText FCsShortCodeCustomization::GetComboBoxContent() const
{
	TSharedPtr<FString> SelectedDisplayName = GetSelectedDisplayName();

	if (SelectedDisplayName.IsValid())
	{
		return FText::FromString(*SelectedDisplayName);
	}
	return LOCTEXT("None", "None");
}

#undef LOCTEXT_NAMESPACE
