// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Damage/SCsGraphPin_ECsDamageType.h"
#include "CsEditor.h"

#include "Types/CsTypes_Damage.h"


void SCsGraphPin_ECsDamageType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsDamageType, EMCsDamageType>();
}

void SCsGraphPin_ECsDamageType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsDamageType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsDamageType::OnGetText() const
{
	return OnGetText_Internal<FECsDamageType, EMCsDamageType>();
}

void SCsGraphPin_ECsDamageType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsDamageType, EMCsDamageType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsDamageType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsDamageType>(EnumIndex);
}

FText SCsGraphPin_ECsDamageType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsDamageType>(EnumIndex);
}



