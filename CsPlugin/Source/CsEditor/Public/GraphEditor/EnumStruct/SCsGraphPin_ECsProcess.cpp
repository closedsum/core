// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProcess.h"
#include "CsEditor.h"

#include "Managers/Process/CsProcess.h"


void SCsGraphPin_ECsProcess::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsProcess, FECsProcess>();
}

void SCsGraphPin_ECsProcess::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProcess>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProcess::OnGetText() const
{
	return OnGetText_Internal<EMCsProcess, FECsProcess>();
}

void SCsGraphPin_ECsProcess::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsProcess, FECsProcess>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProcess::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProcess>(EnumIndex);
}

FText SCsGraphPin_ECsProcess::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProcess>(EnumIndex);
}



