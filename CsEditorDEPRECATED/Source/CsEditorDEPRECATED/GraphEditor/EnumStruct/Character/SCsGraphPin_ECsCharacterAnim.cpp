// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnim.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Character.h"


void SCsGraphPin_ECsCharacterAnim::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsCharacterAnim, FECsCharacterAnim>();
}

void SCsGraphPin_ECsCharacterAnim::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterAnim>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCharacterAnim::OnGetText() const
{
	return OnGetText_Internal<EMCsCharacterAnim, FECsCharacterAnim>();
}

void SCsGraphPin_ECsCharacterAnim::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsCharacterAnim, FECsCharacterAnim>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCharacterAnim::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCharacterAnim>(EnumIndex);
}

FText SCsGraphPin_ECsCharacterAnim::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCharacterAnim>(EnumIndex);
}



