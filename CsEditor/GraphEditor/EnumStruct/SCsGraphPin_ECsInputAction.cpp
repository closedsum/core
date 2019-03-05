// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsInputAction.h"
#include "CsEditor.h"

#include "Types/CsTypes_Input.h"


void SCsGraphPin_ECsInputAction::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsInputAction, EMCsInputAction>();
}

void SCsGraphPin_ECsInputAction::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsInputAction>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsInputAction::OnGetText() const
{
	return OnGetText_Internal<FECsInputAction, EMCsInputAction>();
}

void SCsGraphPin_ECsInputAction::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsInputAction, EMCsInputAction>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsInputAction::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsInputAction>(EnumIndex);
}

FText SCsGraphPin_ECsInputAction::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsInputAction>(EnumIndex);
}



