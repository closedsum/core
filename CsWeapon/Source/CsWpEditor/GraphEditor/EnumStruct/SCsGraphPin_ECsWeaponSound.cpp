// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponSound.h"
#include "CsWpEditor.h"

#include "CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponSound::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponSound, FECsWeaponSound>();
}

void SCsGraphPin_ECsWeaponSound::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponSound>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponSound::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponSound, FECsWeaponSound>();
}

void SCsGraphPin_ECsWeaponSound::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponSound, FECsWeaponSound>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponSound::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponSound>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponSound::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponSound>(EnumIndex);
}



