// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponGrip.h"
#include "CsWpEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponGrip::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponGrip, FECsWeaponGrip>();
}

void SCsGraphPin_ECsWeaponGrip::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponGrip>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponGrip::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponGrip, FECsWeaponGrip>();
}

void SCsGraphPin_ECsWeaponGrip::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponGrip, FECsWeaponGrip>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponGrip::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponGrip>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponGrip::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponGrip>(EnumIndex);
}



