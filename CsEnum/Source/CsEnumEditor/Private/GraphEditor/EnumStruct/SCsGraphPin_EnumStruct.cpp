// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_EnumStruct.h"
#include "CsEnumEditor.h"

#include "Editor/GraphEditor/Public/SGraphPinComboBox.h"

#include "Widgets/Input/SComboButton.h"
#include "Widgets/Views/SListView.h"

// Cache
#pragma region

namespace NCsGraphPinEnumStructCached
{
	namespace Str
	{
		CSENUMEDITOR_API const FString INVALID = TEXT("(INVALID)");
	}

	namespace Txt
	{
		CSENUMEDITOR_API const FText INVALID = FText::FromString(TEXT("(INVALID)"));
	}
}

#pragma endregion Cache

void SCsGraphPin_EnumStruct::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

void SCsGraphPin_EnumStruct::CustomPopulateEnumMap() {}

void SCsGraphPin_EnumStruct::AddPropertyChange() {}

TSharedRef<SWidget>	SCsGraphPin_EnumStruct::GetDefaultValueWidget()
{
	// Get list of enum indexes
	TArray<TSharedPtr<int32>> ComboItems;
	GenerateComboBoxIndexes(ComboItems);

	// Create widget
	return SAssignNew(ComboBox, SPinComboBox)
		.ComboItemList(ComboItems)
		.VisibleText(this, &SCsGraphPin_EnumStruct::OnGetText)
		.OnSelectionChanged(this, &SCsGraphPin_EnumStruct::ComboBoxSelectionChanged)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.OnGetDisplayName(this, &SCsGraphPin_EnumStruct::OnGetFriendlyName)
		.OnGetTooltip(this, &SCsGraphPin_EnumStruct::OnGetTooltip);
}

void SCsGraphPin_EnumStruct::GenerateComboBoxIndexes(TArray< TSharedPtr<int32> >& OutComboBoxIndexes){}

FString SCsGraphPin_EnumStruct::OnGetText() const
{
	return NCsGraphPinEnumStructCached::Str::INVALID;
}

void SCsGraphPin_EnumStruct::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo){}

FText SCsGraphPin_EnumStruct::OnGetFriendlyName(int32 EnumIndex)
{
	return NCsGraphPinEnumStructCached::Txt::INVALID;
}

FText SCsGraphPin_EnumStruct::OnGetTooltip(int32 EnumIndex)
{
	return NCsGraphPinEnumStructCached::Txt::INVALID;
}

