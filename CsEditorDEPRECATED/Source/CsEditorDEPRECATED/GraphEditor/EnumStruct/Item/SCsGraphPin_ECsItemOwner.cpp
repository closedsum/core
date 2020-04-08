// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Item/SCsGraphPin_ECsItemOwner.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Item.h"


void SCsGraphPin_ECsItemOwner::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsItemOwner, EMCsItemOwner>();
}

void SCsGraphPin_ECsItemOwner::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsItemOwner>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsItemOwner::OnGetText() const
{
	return OnGetText_Internal<FECsItemOwner, EMCsItemOwner>();
}

void SCsGraphPin_ECsItemOwner::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsItemOwner, EMCsItemOwner>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsItemOwner::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsItemOwner>(EnumIndex);
}

FText SCsGraphPin_ECsItemOwner::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsItemOwner>(EnumIndex);
}



