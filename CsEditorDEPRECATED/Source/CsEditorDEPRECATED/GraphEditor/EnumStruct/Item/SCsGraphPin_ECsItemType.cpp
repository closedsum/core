// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemType.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Item.h"


void SCsGraphPin_ECsItemType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsItemType, FECsItemType>();
}

void SCsGraphPin_ECsItemType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsItemType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsItemType::OnGetText() const
{
	return OnGetText_Internal<EMCsItemType, FECsItemType>();
}

void SCsGraphPin_ECsItemType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsItemType, FECsItemType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsItemType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsItemType>(EnumIndex);
}

FText SCsGraphPin_ECsItemType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsItemType>(EnumIndex);
}



