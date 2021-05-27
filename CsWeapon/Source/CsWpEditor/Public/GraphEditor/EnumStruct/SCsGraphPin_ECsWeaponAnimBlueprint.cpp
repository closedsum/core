// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponAnimBlueprint.h"
#include "CsWpEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponAnimBlueprint::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint>();
}

void SCsGraphPin_ECsWeaponAnimBlueprint::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponAnimBlueprint>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponAnimBlueprint::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint>();
}

void SCsGraphPin_ECsWeaponAnimBlueprint::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponAnimBlueprint, FECsWeaponAnimBlueprint>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponAnimBlueprint::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponAnimBlueprint>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponAnimBlueprint::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponAnimBlueprint>(EnumIndex);
}