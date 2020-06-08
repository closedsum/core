// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsEthereumJavascript.h"
#include "CsBlockchainEditor.h"

#include "Blockchain/Ethereum/CsEthereum.h"


void SCsGraphPin_ECsEthereumJavascript::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsEthereumJavascript, FECsEthereumJavascript>();
}

void SCsGraphPin_ECsEthereumJavascript::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsEthereumJavascript>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsEthereumJavascript::OnGetText() const
{
	return OnGetText_Internal<EMCsEthereumJavascript, FECsEthereumJavascript>();
}

void SCsGraphPin_ECsEthereumJavascript::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsEthereumJavascript, FECsEthereumJavascript>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsEthereumJavascript::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsEthereumJavascript>(EnumIndex);
}

FText SCsGraphPin_ECsEthereumJavascript::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsEthereumJavascript>(EnumIndex);
}



