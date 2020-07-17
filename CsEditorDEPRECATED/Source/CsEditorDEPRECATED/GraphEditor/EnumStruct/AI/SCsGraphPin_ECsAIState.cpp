// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAIState.h"
#include "CsEditorDEPRECATED.h"

#include "AI/CsTypes_AI.h"


void SCsGraphPin_ECsAIState::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsAIState, FECsAIState>();
}

void SCsGraphPin_ECsAIState::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsAIState>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsAIState::OnGetText() const
{
	return OnGetText_Internal<EMCsAIState, FECsAIState>();
}

void SCsGraphPin_ECsAIState::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsAIState, FECsAIState>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsAIState::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsAIState>(EnumIndex);
}

FText SCsGraphPin_ECsAIState::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsAIState>(EnumIndex);
}



