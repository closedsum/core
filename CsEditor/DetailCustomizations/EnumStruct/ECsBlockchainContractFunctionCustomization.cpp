// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsBlockchainContractFunctionCustomization.h"

#include "Blockchain/CsBlockchainContract.h"

#define LOCTEXT_NAMESPACE "ECsBlockchainContractFunctionCustomization"


FECsBlockchainContractFunctionCustomization::FECsBlockchainContractFunctionCustomization()
{
	Init<FECsBlockchainContractFunction, EMCsBlockchainContractFunction>();
}

TSharedRef<IPropertyTypeCustomization> FECsBlockchainContractFunctionCustomization::MakeInstance()
{
	return MakeShareable(new FECsBlockchainContractFunctionCustomization);
}

void FECsBlockchainContractFunctionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsBlockchainContractFunction>(StructPropertyHandle);
}

void FECsBlockchainContractFunctionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsBlockchainContractFunction, EMCsBlockchainContractFunction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
