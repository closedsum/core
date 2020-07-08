// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsSoundType.h"
#include "CsEditor.h"

// Types
#include "Managers/Sound/CsTypes_Sound.h"


void SCsGraphPin_ECsSoundType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsSoundType, FECsSoundType>();
}

void SCsGraphPin_ECsSoundType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsSoundType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsSoundType::OnGetText() const
{
	return OnGetText_Internal<EMCsSoundType, FECsSoundType>();
}

void SCsGraphPin_ECsSoundType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsSoundType, FECsSoundType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsSoundType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsSoundType>(EnumIndex);
}

FText SCsGraphPin_ECsSoundType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsSoundType>(EnumIndex);
}