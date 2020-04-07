// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAISetup.h"
#include "CsEditorDEPRECATED.h"

#include "AI/CsTypes_AI.h"


void SCsGraphPin_ECsAISetup::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsAISetup, EMCsAISetup>();
}

void SCsGraphPin_ECsAISetup::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsAISetup>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsAISetup::OnGetText() const
{
	return OnGetText_Internal<FECsAISetup, EMCsAISetup>();
}

void SCsGraphPin_ECsAISetup::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsAISetup, EMCsAISetup>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsAISetup::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsAISetup>(EnumIndex);
}

FText SCsGraphPin_ECsAISetup::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsAISetup>(EnumIndex);
}



