// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnimVariation.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Character.h"


void SCsGraphPin_ECsCharacterAnimVariation::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsCharacterAnimVariation, EMCsCharacterAnimVariation>();
}

void SCsGraphPin_ECsCharacterAnimVariation::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterAnimVariation>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCharacterAnimVariation::OnGetText() const
{
	return OnGetText_Internal<FECsCharacterAnimVariation, EMCsCharacterAnimVariation>();
}

void SCsGraphPin_ECsCharacterAnimVariation::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsCharacterAnimVariation, EMCsCharacterAnimVariation>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCharacterAnimVariation::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCharacterAnimVariation>(EnumIndex);
}

FText SCsGraphPin_ECsCharacterAnimVariation::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCharacterAnimVariation>(EnumIndex);
}



