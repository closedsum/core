// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Crafting/SCsGraphPin_ECsRecipeType.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Recipe.h"


void SCsGraphPin_ECsRecipeType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsRecipeType, EMCsRecipeType>();
}

void SCsGraphPin_ECsRecipeType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsItemType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsRecipeType::OnGetText() const
{
	return OnGetText_Internal<FECsRecipeType, EMCsRecipeType>();
}

void SCsGraphPin_ECsRecipeType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsRecipeType, EMCsRecipeType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsRecipeType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsRecipeType>(EnumIndex);
}

FText SCsGraphPin_ECsRecipeType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsRecipeType>(EnumIndex);
}



