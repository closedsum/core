// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectile.h"
#include "CsEditor.h"

#include "Managers/Projectile/CsTypes_Projectile.h"


void SCsGraphPin_ECsProjectile::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsProjectile, EMCsProjectile>();
}

void SCsGraphPin_ECsProjectile::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProjectile>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectile::OnGetText() const
{
	return OnGetText_Internal<FECsProjectile, EMCsProjectile>();
}

void SCsGraphPin_ECsProjectile::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsProjectile, EMCsProjectile>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectile::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProjectile>(EnumIndex);
}

FText SCsGraphPin_ECsProjectile::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProjectile>(EnumIndex);
}