// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterBlendSpace.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Character.h"


void SCsGraphPin_ECsCharacterBlendSpace::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsCharacterBlendSpace, EMCsCharacterBlendSpace>();
}

void SCsGraphPin_ECsCharacterBlendSpace::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterBlendSpace>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCharacterBlendSpace::OnGetText() const
{
	return OnGetText_Internal<FECsCharacterBlendSpace, EMCsCharacterBlendSpace>();
}

void SCsGraphPin_ECsCharacterBlendSpace::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsCharacterBlendSpace, EMCsCharacterBlendSpace>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCharacterBlendSpace::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCharacterBlendSpace>(EnumIndex);
}

FText SCsGraphPin_ECsCharacterBlendSpace::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCharacterBlendSpace>(EnumIndex);
}



