// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Team/SCsGraphPin_ECsTeam.h"
#include "CsEditor.h"

// Types
#include "Team/CsTypes_Team.h"


void SCsGraphPin_ECsTeam::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsTeam, FECsTeam>();
}

void SCsGraphPin_ECsTeam::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsTeam>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsTeam::OnGetText() const
{
	return OnGetText_Internal<EMCsTeam, FECsTeam>();
}

void SCsGraphPin_ECsTeam::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsTeam, FECsTeam>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsTeam::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsTeam>(EnumIndex);
}

FText SCsGraphPin_ECsTeam::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsTeam>(EnumIndex);
}



