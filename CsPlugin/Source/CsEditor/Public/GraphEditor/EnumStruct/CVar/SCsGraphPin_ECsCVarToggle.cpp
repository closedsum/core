// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarToggle.h"
#include "CsEditor.h"

#include "CsCVars.h"


void SCsGraphPin_ECsCVarToggle::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsCVarToggle, FECsCVarToggle>();
}

void SCsGraphPin_ECsCVarToggle::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCVarToggle>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCVarToggle::OnGetText() const
{
	return OnGetText_Internal<EMCsCVarToggle, FECsCVarToggle>();
}

void SCsGraphPin_ECsCVarToggle::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsCVarToggle, FECsCVarToggle>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCVarToggle::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCVarToggle>(EnumIndex);
}

FText SCsGraphPin_ECsCVarToggle::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCVarToggle>(EnumIndex);
}



