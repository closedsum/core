// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileData.h"
#include "CsPrjEditor.h"

#include "Types/CsTypes_Projectile.h"

void SCsGraphPin_ECsProjectileData::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsProjectileData, FECsProjectileData>();
}

void SCsGraphPin_ECsProjectileData::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProjectileData>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectileData::OnGetText() const
{
	return OnGetText_Internal<EMCsProjectileData, FECsProjectileData>();
}

void SCsGraphPin_ECsProjectileData::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsProjectileData, FECsProjectileData>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectileData::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProjectileData>(EnumIndex);
}

FText SCsGraphPin_ECsProjectileData::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProjectileData>(EnumIndex);
}