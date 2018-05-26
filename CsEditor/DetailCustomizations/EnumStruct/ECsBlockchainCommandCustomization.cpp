// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "ECsBlockchainCommandCustomization.h"

#include "Blockchain/CsBlockchainCommand.h"

#define LOCTEXT_NAMESPACE "ECsBlockchainCommandCustomization"


FECsBlockchainCommandCustomization::FECsBlockchainCommandCustomization()
{
	Init<FECsBlockchainCommand, EMCsBlockchainCommand>();
}

TSharedRef<IPropertyTypeCustomization> FECsBlockchainCommandCustomization::MakeInstance()
{
	return MakeShareable(new FECsBlockchainCommandCustomization);
}

void FECsBlockchainCommandCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsBlockchainCommand>(StructPropertyHandle);
}

void FECsBlockchainCommandCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsBlockchainCommand, EMCsBlockchainCommand>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
