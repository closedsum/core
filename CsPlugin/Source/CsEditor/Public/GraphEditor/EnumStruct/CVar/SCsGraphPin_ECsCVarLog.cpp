// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/CVar/SCsGraphPin_ECsCVarLog.h"
#include "CsEditor.h"

#include "CsCVars.h"


void SCsGraphPin_ECsCVarLog::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsCVarLog, FECsCVarLog>();
}

void SCsGraphPin_ECsCVarLog::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCVarLog>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCVarLog::OnGetText() const
{
	return OnGetText_Internal<EMCsCVarLog, FECsCVarLog>();
}

void SCsGraphPin_ECsCVarLog::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsCVarLog, FECsCVarLog>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCVarLog::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCVarLog>(EnumIndex);
}

FText SCsGraphPin_ECsCVarLog::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCVarLog>(EnumIndex);
}



