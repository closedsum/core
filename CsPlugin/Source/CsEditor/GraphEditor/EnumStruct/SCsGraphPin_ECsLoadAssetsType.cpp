// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsLoadAssetsType.h"
#include "CsEditor.h"

#include "Types/CsTypes_Load.h"


void SCsGraphPin_ECsLoadAssetsType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsLoadAssetsType, FECsLoadAssetsType>();
}

void SCsGraphPin_ECsLoadAssetsType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsLoadAssetsType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsLoadAssetsType::OnGetText() const
{
	return OnGetText_Internal<EMCsLoadAssetsType, FECsLoadAssetsType>();
}

void SCsGraphPin_ECsLoadAssetsType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsLoadAssetsType, FECsLoadAssetsType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsLoadAssetsType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsLoadAssetsType>(EnumIndex);
}

FText SCsGraphPin_ECsLoadAssetsType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsLoadAssetsType>(EnumIndex);
}



