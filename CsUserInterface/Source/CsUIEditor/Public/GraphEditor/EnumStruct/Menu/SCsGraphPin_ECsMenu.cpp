// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Menu/SCsGraphPin_ECsMenu.h"
#include "CsUIEditor.h"

#include "Managers/Menu/CsTypes_Menu.h"

void SCsGraphPin_ECsMenu::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsMenu, FECsMenu>();
}

void SCsGraphPin_ECsMenu::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsMenu>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsMenu::OnGetText() const
{
	return OnGetText_Internal<EMCsMenu, FECsMenu>();
}

void SCsGraphPin_ECsMenu::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsMenu, FECsMenu>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsMenu::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsMenu>(EnumIndex);
}

FText SCsGraphPin_ECsMenu::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsMenu>(EnumIndex);
}