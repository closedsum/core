// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Blockchain/ECsBlockchainContractFunctionCustomization.h"

#include "Blockchain/CsBlockchainContract.h"

#define LOCTEXT_NAMESPACE "ECsBlockchainContractFunctionCustomization"


FECsBlockchainContractFunctionCustomization::FECsBlockchainContractFunctionCustomization() :
	Super()
{
	Init<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>();
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
	SetEnumWithDisplayName_Internal<EMCsBlockchainContractFunction, FECsBlockchainContractFunction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
