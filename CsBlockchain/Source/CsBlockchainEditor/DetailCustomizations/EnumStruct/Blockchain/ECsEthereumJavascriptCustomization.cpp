// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Blockchain/ECsEthereumJavascriptCustomization.h"

#include "Blockchain/Ethereum/CsEthereum.h"

#define LOCTEXT_NAMESPACE "ECsEthereumJavascriptCustomization"


FECsEthereumJavascriptCustomization::FECsEthereumJavascriptCustomization() :
	Super()
{
	Init<EMCsEthereumJavascript, FECsEthereumJavascript>();
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
	SetEnumWithDisplayName_Internal<EMCsEthereumJavascript, FECsEthereumJavascript>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
