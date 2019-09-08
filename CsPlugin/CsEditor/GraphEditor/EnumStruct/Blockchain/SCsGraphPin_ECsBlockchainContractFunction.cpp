// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsBlockchainContractFunction.h"
#include "CsEditor.h"

#include "Blockchain/CsBlockchainContract.h"


void SCsGraphPin_ECsBlockchainContractFunction::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsBlockchainContractFunction, EMCsBlockchainContractFunction>();
}

void SCsGraphPin_ECsBlockchainContractFunction::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsBlockchainContractFunction>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsBlockchainContractFunction::OnGetText() const
{
	return OnGetText_Internal<FECsBlockchainContractFunction, EMCsBlockchainContractFunction>();
}

void SCsGraphPin_ECsBlockchainContractFunction::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsBlockchainContractFunction, EMCsBlockchainContractFunction>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsBlockchainContractFunction::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsBlockchainContractFunction>(EnumIndex);
}

FText SCsGraphPin_ECsBlockchainContractFunction::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsBlockchainContractFunction>(EnumIndex);
}



