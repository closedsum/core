// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGameEventCoordinatorGroup.h"
#include "CsEditor.h"

#include "Coordinators/GameEvent/CsTypes_Coordinator_GameEvent.h"

void SCsGraphPin_ECsGameEventCoordinatorGroup::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>();
}

void SCsGraphPin_ECsGameEventCoordinatorGroup::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsGameEventCoordinatorGroup>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsGameEventCoordinatorGroup::OnGetText() const
{
	return OnGetText_Internal<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>();
}

void SCsGraphPin_ECsGameEventCoordinatorGroup::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsGameEventCoordinatorGroup, FECsGameEventCoordinatorGroup>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsGameEventCoordinatorGroup::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsGameEventCoordinatorGroup>(EnumIndex);
}

FText SCsGraphPin_ECsGameEventCoordinatorGroup::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsGameEventCoordinatorGroup>(EnumIndex);
}