// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ECsBlockchainCommandCustomization.h"
#include "IDetailChildrenBuilder.h"
#include "DetailWidgetRow.h"
#include "IDetailGroup.h"
#include "DetailLayoutBuilder.h"

#include "Blockchain/CsBlockchainCommand.h"

#define LOCTEXT_NAMESPACE "ECsBlockchainCommandCustomization"


FECsBlockchainCommandCustomization::FECsBlockchainCommandCustomization()
{
	const int32 Count = EMCsBlockchainCommand::Get().Num();

	for (int32 I = 0; I < Count - 1; ++I)
	{
		const FECsBlockchainCommand& Command = EMCsBlockchainCommand::Get().GetEnumAt(I);

		NameList.Add(MakeShareable(new FString(Command.Name)));
	}
}

TSharedRef<IPropertyTypeCustomization> FECsBlockchainCommandCustomization::MakeInstance()
{
	return MakeShareable(new FECsBlockchainCommandCustomization);
}

void FECsBlockchainCommandCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	NameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FECsBlockchainCommand, Name));
	check(NameHandle.IsValid());

	TSharedPtr<FString> InitialSelectedName = GetSelectedName();
	if (InitialSelectedName.IsValid())
	{
		SetPropertyWithName(*InitialSelectedName.Get());
	}

	HeaderRow.NameContent()
	[
		SNew(STextBlock)
		.Text(StructPropertyHandle->GetPropertyDisplayName())
		.Font(IDetailLayoutBuilder::GetDetailFont())
	]
	.ValueContent()
	[
		SAssignNew(NameComboBox, SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&NameList)
		.OnGenerateWidget(this, &FECsBlockchainCommandCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FECsBlockchainCommandCustomization::OnSelectionChanged)
		.OnComboBoxOpening(this, &FECsBlockchainCommandCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FECsBlockchainCommandCustomization::GetProfileComboBoxContent)
			.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	];
}

void FECsBlockchainCommandCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	/*
	NameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FCollisionProfileName, Name));
	check(NameHandle.IsValid());

	TSharedPtr<FName> InitialSelectedName = GetSelectedName();
	if (InitialSelectedName.IsValid())
	{
		SetPropertyWithName(*InitialSelectedName.Get());
	}

	IDetailGroup& CollisionGroup = StructBuilder.AddGroup(TEXT("Collision"), LOCTEXT("CollisionPresetName", "Collision Preset"));
	CollisionGroup.HeaderRow()
		.NameContent()
		[
			SNew(STextBlock)
			.Text(StructPropertyHandle->GetPropertyDisplayName())
		.Font(IDetailLayoutBuilder::GetDetailFont())
		]
	.ValueContent()
		[
			SAssignNew(NameComboBox, SComboBox<TSharedPtr<FName>>)
			.OptionsSource(&NameList)
		.OnGenerateWidget(this, &FCollisionProfileNameCustomization::OnGenerateWidget)
		.OnSelectionChanged(this, &FCollisionProfileNameCustomization::OnSelectionChanged, &CollisionGroup)
		.OnComboBoxOpening(this, &FCollisionProfileNameCustomization::OnComboBoxOpening)
		.InitiallySelectedItem(InitialSelectedName)
		.IsEnabled(FSlateApplication::Get().GetNormalExecutionAttribute())
		.ContentPadding(FMargin(2.0f, 2.0f))
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &FCollisionProfileNameCustomization::GetProfileComboBoxContent)
		.Font(IDetailLayoutBuilder::GetDetailFont())
		.ToolTipText(this, &FCollisionProfileNameCustomization::GetProfileComboBoxToolTip)
		]
		];
		*/
}

TSharedRef<SWidget> FECsBlockchainCommandCustomization::OnGenerateWidget(TSharedPtr<FString> InItem)
{
	return
		SNew(STextBlock)
		.Text(FText::FromString(*InItem))
		.Font(IDetailLayoutBuilder::GetDetailFont());
}

void FECsBlockchainCommandCustomization::OnSelectionChanged(TSharedPtr<FString> NameItem, ESelectInfo::Type SelectInfo)
{
	if (NameItem.IsValid())
	{
		SetPropertyWithName(*NameItem);
	}
}

void FECsBlockchainCommandCustomization::OnComboBoxOpening()
{
	TSharedPtr<FString> SelectedName = GetSelectedName();
	if (SelectedName.IsValid())
	{
		check(NameComboBox.IsValid());
		NameComboBox->SetSelectedItem(SelectedName);
	}
}

TSharedPtr<FString> FECsBlockchainCommandCustomization::GetSelectedName() const
{
	int32 NameCount = NameList.Num();

	if (NameCount <= 0)
	{
		return NULL;
	}

	FString Name;
	GetPropertyAsName(Name);

	for (int32 NameIndex = 0; NameIndex < NameCount; ++NameIndex)
	{
		if (Name == *NameList[NameIndex].Get())
		{
			return NameList[NameIndex];
		}
	}

	return NameList[0];
}

void FECsBlockchainCommandCustomization::SetPropertyWithName(const FString& Name)
{
	check(NameHandle.IsValid());

	FString OldName;
	NameHandle->GetValue(OldName);

	if (OldName != Name)
	{
		NameHandle->SetValue(Name);
	}
}

void FECsBlockchainCommandCustomization::GetPropertyAsName(FString& OutName) const
{
	check(NameHandle.IsValid());
	NameHandle->GetValue(OutName);
}

FText FECsBlockchainCommandCustomization::GetProfileComboBoxContent() const
{
	TSharedPtr<FString> SelectedName = GetSelectedName();
	if (SelectedName.IsValid())
	{
		return FText::FromString(*SelectedName);
	}

	return LOCTEXT("Invalid", "Invalid");
}

#undef LOCTEXT_NAMESPACE
