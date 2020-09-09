// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarDraw.h"
#include "CsEditor.h"

#include "CsCVars.h"


void SCsGraphPin_ECsCVarDraw::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsCVarDraw, FECsCVarDraw>();
}

void SCsGraphPin_ECsCVarDraw::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCVarDraw>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCVarDraw::OnGetText() const
{
	return OnGetText_Internal<EMCsCVarDraw, FECsCVarDraw>();
}

void SCsGraphPin_ECsCVarDraw::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsCVarDraw, FECsCVarDraw>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCVarDraw::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCVarDraw>(EnumIndex);
}

FText SCsGraphPin_ECsCVarDraw::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCVarDraw>(EnumIndex);
}



