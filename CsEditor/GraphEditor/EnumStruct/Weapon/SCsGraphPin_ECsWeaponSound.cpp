// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponSound.h"
#include "CsEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponSound::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsWeaponSound, EMCsWeaponSound>();
}

void SCsGraphPin_ECsWeaponSound::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponSound>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponSound::OnGetText() const
{
	return OnGetText_Internal<FECsWeaponSound, EMCsWeaponSound>();
}

void SCsGraphPin_ECsWeaponSound::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsWeaponSound, EMCsWeaponSound>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponSound::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponSound>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponSound::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponSound>(EnumIndex);
}



