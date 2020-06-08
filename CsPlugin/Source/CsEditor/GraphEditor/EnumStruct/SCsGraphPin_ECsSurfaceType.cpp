// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsSurfaceType.h"
#include "CsEditor.h"

#include "Types/CsTypes.h"


void SCsGraphPin_ECsSurfaceType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsSurfaceType, FECsSurfaceType>();
}

void SCsGraphPin_ECsSurfaceType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsSurfaceType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsSurfaceType::OnGetText() const
{
	return OnGetText_Internal<EMCsSurfaceType, FECsSurfaceType>();
}

void SCsGraphPin_ECsSurfaceType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsSurfaceType, FECsSurfaceType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsSurfaceType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsSurfaceType>(EnumIndex);
}

FText SCsGraphPin_ECsSurfaceType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsSurfaceType>(EnumIndex);
}



