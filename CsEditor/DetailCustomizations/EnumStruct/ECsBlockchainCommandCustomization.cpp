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

		DisplayNameList.Add(MakeShareable(new FString(Command.DisplayName)));
	}
}

TSharedRef<IPropertyTypeCustomization> FECsBlockchainCommandCustomization::MakeInstance()
{
	return MakeShareable(new FECsBlockchainCommandCustomization);
}

void FECsBlockchainCommandCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
	FECsEnumCustomization::CustomizeHeader(StructPropertyHandle, HeaderRow, StructCustomizationUtils);
}

void FECsBlockchainCommandCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	ValueHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FECsBlockchainCommand, Value));
	check(ValueHandle.IsValid());
	NameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FECsBlockchainCommand, Name));
	check(NameHandle.IsValid());
	DisplayNameHandle = StructPropertyHandle->GetChildHandle(GET_MEMBER_NAME_CHECKED(FECsBlockchainCommand, DisplayName));
	check(DisplayNameHandle.IsValid());
}

void FECsBlockchainCommandCustomization::CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{
}

void FECsBlockchainCommandCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	check(DisplayNameHandle.IsValid());

	FString OldDisplayName;
	DisplayNameHandle->GetValue(OldDisplayName);

	if (OldDisplayName != DisplayName)
	{
		DisplayNameHandle->SetValue(DisplayName);

		const FECsBlockchainCommand& Command = EMCsBlockchainCommand::Get().GetEnumByDisplayName(DisplayName);

		check(ValueHandle.IsValid());
		ValueHandle->SetValue(Command.Value);
		check(NameHandle.IsValid());
		NameHandle->SetValue(Command.Name);
	}
}

#undef LOCTEXT_NAMESPACE
