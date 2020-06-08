// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsTdCreep.h"
#include "CsEditor.h"

// Types
#include "Managers/Creep/CsTdTypes_Creep.h"


void SCsGraphPin_ECsTdCreep::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsTdCreep, FECsTdCreep>();
}

void SCsGraphPin_ECsTdCreep::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsTdCreep>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsTdCreep::OnGetText() const
{
	return OnGetText_Internal<EMCsTdCreep, FECsTdCreep>();
}

void SCsGraphPin_ECsTdCreep::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsTdCreep, FECsTdCreep>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsTdCreep::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsTdCreep>(EnumIndex);
}

FText SCsGraphPin_ECsTdCreep::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsTdCreep>(EnumIndex);
}



