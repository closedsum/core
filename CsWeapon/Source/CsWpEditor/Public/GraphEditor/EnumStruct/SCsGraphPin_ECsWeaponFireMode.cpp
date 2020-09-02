// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponFireMode.h"
#include "CsWpEditor.h"

#include "CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponFireMode::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponFireMode, FECsWeaponFireMode>();
}

void SCsGraphPin_ECsWeaponFireMode::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponFireMode>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponFireMode::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponFireMode, FECsWeaponFireMode>();
}

void SCsGraphPin_ECsWeaponFireMode::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponFireMode, FECsWeaponFireMode>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponFireMode::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponFireMode>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponFireMode::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponFireMode>(EnumIndex);
}