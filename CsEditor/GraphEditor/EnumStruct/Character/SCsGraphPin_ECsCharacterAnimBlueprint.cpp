// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnimBlueprint.h"
#include "CsEditor.h"

#include "Types/CsTypes_Character.h"


void SCsGraphPin_ECsCharacterAnimBlueprint::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsCharacterAnimBlueprint, EMCsCharacterAnimBlueprint>();
}

void SCsGraphPin_ECsCharacterAnimBlueprint::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterAnimBlueprint>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCharacterAnimBlueprint::OnGetText() const
{
	return OnGetText_Internal<FECsCharacterAnimBlueprint, EMCsCharacterAnimBlueprint>();
}

void SCsGraphPin_ECsCharacterAnimBlueprint::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsCharacterAnimBlueprint, EMCsCharacterAnimBlueprint>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCharacterAnimBlueprint::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCharacterAnimBlueprint>(EnumIndex);
}

FText SCsGraphPin_ECsCharacterAnimBlueprint::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCharacterAnimBlueprint>(EnumIndex);
}



