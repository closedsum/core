// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsGestureType.h"
#include "CsEditor.h"

#include "Types/CsTypes.h"


void SCsGraphPin_ECsGestureType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsGestureType, EMCsGestureType>();
}

void SCsGraphPin_ECsGestureType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterAnim>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsGestureType::OnGetText() const
{
	return OnGetText_Internal<FECsGestureType, EMCsGestureType>();
}

void SCsGraphPin_ECsGestureType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsGestureType, EMCsGestureType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsGestureType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsGestureType>(EnumIndex);
}

FText SCsGraphPin_ECsGestureType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsGestureType>(EnumIndex);
}



