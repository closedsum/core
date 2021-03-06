// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffectTriggerCondition.h"
#include "CsSeEditor.h"

#include "CsTypes_StatusEffect.h"

// Cached
#pragma region

namespace NCsGraphPinStatusEffectTriggerConditionCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsStatusEffectTriggerCondition::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsStatusEffectTriggerCondition::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition>();
}

void SCsGraphPin_ECsStatusEffectTriggerCondition::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsStatusEffectTriggerCondition>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsStatusEffectTriggerCondition::OnGetText() const
{
	return OnGetText_Internal<EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition>();
}

void SCsGraphPin_ECsStatusEffectTriggerCondition::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsStatusEffectTriggerCondition, FECsStatusEffectTriggerCondition>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsStatusEffectTriggerCondition::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsStatusEffectTriggerCondition>(EnumIndex);
}

FText SCsGraphPin_ECsStatusEffectTriggerCondition::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsStatusEffectTriggerCondition>(EnumIndex);
}