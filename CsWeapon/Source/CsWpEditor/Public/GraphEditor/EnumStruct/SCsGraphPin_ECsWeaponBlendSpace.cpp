// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponBlendSpace.h"
#include "CsWpEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponBlendSpace::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponBlendSpace, FECsWeaponBlendSpace>();
}

void SCsGraphPin_ECsWeaponBlendSpace::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponBlendSpace>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponBlendSpace::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponBlendSpace, FECsWeaponBlendSpace>();
}

void SCsGraphPin_ECsWeaponBlendSpace::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponBlendSpace, FECsWeaponBlendSpace>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponBlendSpace::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponBlendSpace>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponBlendSpace::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponBlendSpace>(EnumIndex);
}