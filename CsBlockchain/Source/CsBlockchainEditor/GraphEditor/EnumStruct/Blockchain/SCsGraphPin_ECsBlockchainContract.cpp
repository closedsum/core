// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsBlockchainContract.h"
#include "CsBlockchainEditor.h"

#include "Blockchain/CsBlockchainContract.h"


void SCsGraphPin_ECsBlockchainContract::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsBlockchainContract, EMCsBlockchainContract>();
}

void SCsGraphPin_ECsBlockchainContract::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsBlockchainContract>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsBlockchainContract::OnGetText() const
{
	return OnGetText_Internal<FECsBlockchainContract, EMCsBlockchainContract>();
}

void SCsGraphPin_ECsBlockchainContract::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsBlockchainContract, EMCsBlockchainContract>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsBlockchainContract::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsBlockchainContract>(EnumIndex);
}

FText SCsGraphPin_ECsBlockchainContract::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsBlockchainContract>(EnumIndex);
}



