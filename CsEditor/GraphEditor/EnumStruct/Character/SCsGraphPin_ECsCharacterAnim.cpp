// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Character/SCsGraphPin_ECsCharacterAnim.h"
#include "CsEditor.h"

#include "Types/CsTypes_Character.h"


void SCsGraphPin_ECsCharacterAnim::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<FECsCharacterAnim, EMCsCharacterAnim>();
}

void SCsGraphPin_ECsCharacterAnim::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsCharacterAnim>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsCharacterAnim::OnGetText() const
{
	return OnGetText_Internal<FECsCharacterAnim, EMCsCharacterAnim>();
}

void SCsGraphPin_ECsCharacterAnim::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<FECsCharacterAnim, EMCsCharacterAnim>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsCharacterAnim::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsCharacterAnim>(EnumIndex);
}

FText SCsGraphPin_ECsCharacterAnim::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsCharacterAnim>(EnumIndex);
}



