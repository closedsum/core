// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Damage/SCsGraphPin_ECsHitType.h"
#include "CsEditor.h"

#include "Types/CsTypes_Damage.h"


void SCsGraphPin_ECsHitType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsHitType, FECsHitType>();
}

void SCsGraphPin_ECsHitType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsHitType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsHitType::OnGetText() const
{
	return OnGetText_Internal<EMCsHitType, FECsHitType>();
}

void SCsGraphPin_ECsHitType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsHitType, FECsHitType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsHitType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsHitType>(EnumIndex);
}

FText SCsGraphPin_ECsHitType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsHitType>(EnumIndex);
}



