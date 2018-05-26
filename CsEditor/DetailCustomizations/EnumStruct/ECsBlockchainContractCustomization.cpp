// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "ECsBlockchainContractCustomization.h"

#include "Blockchain/CsBlockchainContract.h"

#define LOCTEXT_NAMESPACE "ECsBlockchainContractCustomization"


FECsBlockchainContractCustomization::FECsBlockchainContractCustomization()
{
	Init<FECsBlockchainContract, EMCsBlockchainContract>();
}

TSharedRef<IPropertyTypeCustomization> FECsBlockchainContractCustomization::MakeInstance()
{
	return MakeShareable(new FECsBlockchainContractCustomization);
}

void FECsBlockchainContractCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsBlockchainContract>(StructPropertyHandle);
}

void FECsBlockchainContractCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsBlockchainContract, EMCsBlockchainContract>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
