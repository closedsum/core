// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectilePayload.h"
#include "CsPrjEditor.h"

#include "Payload/CsTypes_Payload_Projectile.h"

void SCsGraphPin_ECsProjectilePayload::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsProjectilePayload, FECsProjectilePayload>();
}

void SCsGraphPin_ECsProjectilePayload::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProjectilePayload>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectilePayload::OnGetText() const
{
	return OnGetText_Internal<EMCsProjectilePayload, FECsProjectilePayload>();
}

void SCsGraphPin_ECsProjectilePayload::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsProjectilePayload, FECsProjectilePayload>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectilePayload::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProjectilePayload>(EnumIndex);
}

FText SCsGraphPin_ECsProjectilePayload::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProjectilePayload>(EnumIndex);
}