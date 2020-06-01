// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Blockchain/ECsBlockchainCommandCustomization.h"

#include "Blockchain/CsBlockchainCommand.h"

#define LOCTEXT_NAMESPACE "ECsBlockchainCommandCustomization"


FECsBlockchainCommandCustomization::FECsBlockchainCommandCustomization() :
	Super()
{
	Init<EMCsBlockchainCommand, FECsBlockchainCommand>();
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
	SetEnumWithDisplayName_Internal<EMCsBlockchainCommand, FECsBlockchainCommand>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
