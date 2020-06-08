// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Sense/SCsGraphPin_ECsSenseActorType.h"
#include "CsEditor.h"

#include "Managers/Sense/CsTypes_Sense.h"


void SCsGraphPin_ECsSenseActorType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsSenseActorType, FECsSenseActorType>();
}

void SCsGraphPin_ECsSenseActorType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsSenseActorType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsSenseActorType::OnGetText() const
{
	return OnGetText_Internal<EMCsSenseActorType, FECsSenseActorType>();
}

void SCsGraphPin_ECsSenseActorType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsSenseActorType, FECsSenseActorType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsSenseActorType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsSenseActorType>(EnumIndex);
}

FText SCsGraphPin_ECsSenseActorType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsSenseActorType>(EnumIndex);
}



