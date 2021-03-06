// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnimBlueprint.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Character.h"


void SCsGraphPin_ECsCharacterAnimBlueprint::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsCharacterAnimBlueprint, FECsCharacterAnimBlueprint>();
}

void SCsGraphPin_ECsCharacterAnimBlueprint::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterAnimBlueprint>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCharacterAnimBlueprint::OnGetText() const
{
	return OnGetText_Internal<EMCsCharacterAnimBlueprint, FECsCharacterAnimBlueprint>();
}

void SCsGraphPin_ECsCharacterAnimBlueprint::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsCharacterAnimBlueprint, FECsCharacterAnimBlueprint>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCharacterAnimBlueprint::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCharacterAnimBlueprint>(EnumIndex);
}

FText SCsGraphPin_ECsCharacterAnimBlueprint::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCharacterAnimBlueprint>(EnumIndex);
}



