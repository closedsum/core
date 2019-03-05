// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponBlendSpace.h"
#include "CsEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponBlendSpace::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsWeaponBlendSpace, EMCsWeaponBlendSpace>();
}

void SCsGraphPin_ECsWeaponBlendSpace::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponBlendSpace>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponBlendSpace::OnGetText() const
{
	return OnGetText_Internal<FECsWeaponBlendSpace, EMCsWeaponBlendSpace>();
}

void SCsGraphPin_ECsWeaponBlendSpace::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsWeaponBlendSpace, EMCsWeaponBlendSpace>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponBlendSpace::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponBlendSpace>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponBlendSpace::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponBlendSpace>(EnumIndex);
}



