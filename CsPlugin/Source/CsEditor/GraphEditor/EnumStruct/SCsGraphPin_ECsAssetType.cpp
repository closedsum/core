// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsAssetType.h"
#include "CsEditor.h"

#include "Types/CsTypes_Load.h"


void SCsGraphPin_ECsAssetType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsAssetType, EMCsAssetType>();
}

void SCsGraphPin_ECsAssetType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsAssetType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsAssetType::OnGetText() const
{
	return OnGetText_Internal<FECsAssetType, EMCsAssetType>();
}

void SCsGraphPin_ECsAssetType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsAssetType, EMCsAssetType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsAssetType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsAssetType>(EnumIndex);
}

FText SCsGraphPin_ECsAssetType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsAssetType>(EnumIndex);
}



