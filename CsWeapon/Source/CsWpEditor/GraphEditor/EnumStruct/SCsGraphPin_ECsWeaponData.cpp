// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponData.h"
#include "CsWpEditor.h"

#include "CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponData::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponData, FECsWeaponData>();
}

void SCsGraphPin_ECsWeaponData::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponData>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponData::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponData, FECsWeaponData>();
}

void SCsGraphPin_ECsWeaponData::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponData, FECsWeaponData>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponData::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponData>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponData::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponData>(EnumIndex);
}



