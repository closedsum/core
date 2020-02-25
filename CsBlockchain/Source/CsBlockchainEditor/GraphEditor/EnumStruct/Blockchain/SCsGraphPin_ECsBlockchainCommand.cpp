// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Blockchain/SCsGraphPin_ECsBlockchainCommand.h"
#include "CsBlockchainEditor.h"

#include "Blockchain/CsBlockchainCommand.h"


void SCsGraphPin_ECsBlockchainCommand::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsBlockchainCommand, EMCsBlockchainCommand>();
}

void SCsGraphPin_ECsBlockchainCommand::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsBlockchainCommand>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsBlockchainCommand::OnGetText() const
{
	return OnGetText_Internal<FECsBlockchainCommand, EMCsBlockchainCommand>();
}

void SCsGraphPin_ECsBlockchainCommand::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsBlockchainCommand, EMCsBlockchainCommand>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsBlockchainCommand::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsBlockchainCommand>(EnumIndex);
}

FText SCsGraphPin_ECsBlockchainCommand::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsBlockchainCommand>(EnumIndex);
}



