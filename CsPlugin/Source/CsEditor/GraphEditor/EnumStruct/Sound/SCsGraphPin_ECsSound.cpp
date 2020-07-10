// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Sound/SCsGraphPin_ECsSound.h"
#include "CsEditor.h"

// Types
#include "Managers/Sound/CsTypes_Sound.h"


void SCsGraphPin_ECsSound::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsSound, FECsSound>();
}

void SCsGraphPin_ECsSound::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsSound>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsSound::OnGetText() const
{
	return OnGetText_Internal<EMCsSound, FECsSound>();
}

void SCsGraphPin_ECsSound::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsSound, FECsSound>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsSound::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsSound>(EnumIndex);
}

FText SCsGraphPin_ECsSound::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsSound>(EnumIndex);
}