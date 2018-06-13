// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponAnim.h"
#include "CsEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponAnim::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsWeaponAnim, EMCsWeaponAnim>();
}

void SCsGraphPin_ECsWeaponAnim::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponAnim>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponAnim::OnGetText() const
{
	return OnGetText_Internal<FECsWeaponAnim, EMCsWeaponAnim>();
}

void SCsGraphPin_ECsWeaponAnim::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsWeaponAnim, EMCsWeaponAnim>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponAnim::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponAnim>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponAnim::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponAnim>(EnumIndex);
}



