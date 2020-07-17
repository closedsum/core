// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemInteraction.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Item.h"


void SCsGraphPin_ECsItemInteraction::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsItemInteraction, FECsItemInteraction>();
}

void SCsGraphPin_ECsItemInteraction::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsItemInteraction>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsItemInteraction::OnGetText() const
{
	return OnGetText_Internal<EMCsItemInteraction, FECsItemInteraction>();
}

void SCsGraphPin_ECsItemInteraction::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsItemInteraction, FECsItemInteraction>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsItemInteraction::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsItemInteraction>(EnumIndex);
}

FText SCsGraphPin_ECsItemInteraction::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsItemInteraction>(EnumIndex);
}