// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Blockchain/ECsEthereumJavascriptCustomization.h"

#include "Blockchain/Ethereum/CsEthereum.h"

#define LOCTEXT_NAMESPACE "ECsEthereumJavascriptCustomization"


FECsEthereumJavascriptCustomization::FECsEthereumJavascriptCustomization()
{
	Init<FECsEthereumJavascript, EMCsEthereumJavascript>();
}

TSharedRef<IPropertyTypeCustomization> FECsEthereumJavascriptCustomization::MakeInstance()
{
	return MakeShareable(new FECsEthereumJavascriptCustomization);
}

void FECsEthereumJavascriptCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsEthereumJavascript>(StructPropertyHandle);
}

void FECsEthereumJavascriptCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsEthereumJavascript, EMCsEthereumJavascript>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
