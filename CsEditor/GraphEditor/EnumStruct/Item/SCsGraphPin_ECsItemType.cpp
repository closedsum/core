// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemType.h"
#include "CsEditor.h"

#include "Types/CsTypes_Item.h"


void SCsGraphPin_ECsItemType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsItemType, EMCsItemType>();
}

void SCsGraphPin_ECsItemType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsItemType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsItemType::OnGetText() const
{
	return OnGetText_Internal<FECsItemType, EMCsItemType>();
}

void SCsGraphPin_ECsItemType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsItemType, EMCsItemType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsItemType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsItemType>(EnumIndex);
}

FText SCsGraphPin_ECsItemType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsItemType>(EnumIndex);
}



