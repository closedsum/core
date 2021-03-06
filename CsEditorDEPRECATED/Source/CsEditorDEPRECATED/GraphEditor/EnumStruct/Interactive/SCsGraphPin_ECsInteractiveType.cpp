// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Interactive/SCsGraphPin_ECsInteractiveType.h"
#include "CsEditorDEPRECATED.h"

#include "Types/CsTypes_Interactive.h"


void SCsGraphPin_ECsInteractiveType::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsInteractiveType, FECsInteractiveType>();
}

void SCsGraphPin_ECsInteractiveType::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsInteractiveType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsInteractiveType::OnGetText() const
{
	return OnGetText_Internal<EMCsInteractiveType, FECsInteractiveType>();
}

void SCsGraphPin_ECsInteractiveType::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsInteractiveType, FECsInteractiveType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsInteractiveType::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsInteractiveType>(EnumIndex);
}

FText SCsGraphPin_ECsInteractiveType::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsInteractiveType>(EnumIndex);
}



