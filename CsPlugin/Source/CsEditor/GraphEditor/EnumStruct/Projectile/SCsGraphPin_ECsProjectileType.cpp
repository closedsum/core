// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Projectile/SCsGraphPin_ECsProjectileType.h"
#include "CsEditor.h"

#include "Managers/Projectile/CsTypes_Projectile.h"


void SCsGraphPin_ECsProjectileType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsProjectileType, EMCsProjectileType>();
}

void SCsGraphPin_ECsProjectileType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProjectileType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectileType::OnGetText() const
{
	return OnGetText_Internal<FECsProjectileType, EMCsProjectileType>();
}

void SCsGraphPin_ECsProjectileType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsProjectileType, EMCsProjectileType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectileType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProjectileType>(EnumIndex);
}

FText SCsGraphPin_ECsProjectileType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProjectileType>(EnumIndex);
}



