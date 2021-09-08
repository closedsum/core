// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsStatusEffectEvent.h"
#include "CsSeEditor.h"

#include "CsTypes_StatusEffect.h"

// Cached
#pragma region

namespace NCsGraphPinStatusEffectEventCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsStatusEffectTriggerCondition::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsStatusEffectEvent::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsStatusEffectEvent, FECsStatusEffectEvent>();
}

void SCsGraphPin_ECsStatusEffectEvent::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsStatusEffectEvent>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsStatusEffectEvent::OnGetText() const
{
	return OnGetText_Internal<EMCsStatusEffectEvent, FECsStatusEffectEvent>();
}

void SCsGraphPin_ECsStatusEffectEvent::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsStatusEffectEvent, FECsStatusEffectEvent>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsStatusEffectEvent::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsStatusEffectEvent>(EnumIndex);
}

FText SCsGraphPin_ECsStatusEffectEvent::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsStatusEffectEvent>(EnumIndex);
}