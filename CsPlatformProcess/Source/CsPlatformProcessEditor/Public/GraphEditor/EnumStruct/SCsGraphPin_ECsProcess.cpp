// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProcess.h"
#include "CsEditor.h"

#include "Managers/Process/CsProcess.h"

#define EnumMapType EMCsProcess
#define EnumType FECsProcess

void SCsGraphPin_ECsProcess::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsProcess::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EnumMapType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProcess::OnGetText() const
{
	return OnGetText_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsProcess::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EnumMapType, EnumType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProcess::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EnumMapType>(EnumIndex);
}

FText SCsGraphPin_ECsProcess::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EnumMapType>(EnumIndex);
}

#undef EnumMapType
#undef EnumType