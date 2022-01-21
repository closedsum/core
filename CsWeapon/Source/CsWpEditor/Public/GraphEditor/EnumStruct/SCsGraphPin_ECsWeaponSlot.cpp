// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponSlot.h"
#include "CsWpEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponSlot::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponSlot, FECsWeaponSlot>();
}

void SCsGraphPin_ECsWeaponSlot::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponSlot>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponSlot::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponSlot, FECsWeaponSlot>();
}

void SCsGraphPin_ECsWeaponSlot::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponSlot, FECsWeaponSlot>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponSlot::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponSlot>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponSlot::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponSlot>(EnumIndex);
}



