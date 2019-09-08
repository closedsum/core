// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/AI/SCsGraphPin_ECsAIType.h"
#include "CsEditor.h"

#include "Types/CsTypes_AI.h"


void SCsGraphPin_ECsAIType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsAIType, EMCsAIType>();
}

void SCsGraphPin_ECsAIType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsAIType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsAIType::OnGetText() const
{
	return OnGetText_Internal<FECsAIType, EMCsAIType>();
}

void SCsGraphPin_ECsAIType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsAIType, EMCsAIType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsAIType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsAIType>(EnumIndex);
}

FText SCsGraphPin_ECsAIType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsAIType>(EnumIndex);
}



