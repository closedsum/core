// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Weapon/SCsGraphPin_ECsWeaponOwner.h"
#include "CsEditor.h"

#include "Types/CsTypes_Weapon.h"


void SCsGraphPin_ECsWeaponOwner::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsWeaponOwner, EMCsWeaponOwner>();
}

void SCsGraphPin_ECsWeaponOwner::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponOwner>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponOwner::OnGetText() const
{
	return OnGetText_Internal<FECsWeaponOwner, EMCsWeaponOwner>();
}

void SCsGraphPin_ECsWeaponOwner::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsWeaponOwner, EMCsWeaponOwner>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponOwner::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponOwner>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponOwner::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponOwner>(EnumIndex);
}



