// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_EnumStructMask.h"
#include "CsEditor.h"

#include "Editor/GraphEditor/Public/SGraphPinComboBox.h"

#include "Widgets/Input/SComboButton.h"
#include "Widgets/Views/SListView.h"

// Cache
#pragma region

namespace NCsGraphPinEnumStructMaskCached
{
	namespace Str
	{
		CSEDITOR_API const FString INVALID = TEXT("(INVALID)");
	}

	namespace Txt
	{
		CSEDITOR_API const FText INVALID = FText::FromString(TEXT("(INVALID)"));
	}
}

#pragma endregion Cache

void SCsGraphPin_EnumStructMask::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
}

void SCsGraphPin_EnumStructMask::CustomPopulateEnumMap(){}

void SCsGraphPin_EnumStructMask::AddPropertyChange() {}

TSharedRef<SWidget>	SCsGraphPin_EnumStructMask::GetDefaultValueWidget()
{
	// Get list of enum indexes
	TArray<TSharedPtr<int32>> ComboItems;
	GenerateComboBoxIndexes(ComboItems);

	// Create widget
	return SAssignNew(ComboBox, SPinComboBox)
		.ComboItemList(ComboItems)
		.VisibleText(this, &SCsGraphPin_EnumStructMask::OnGetText)
		.OnSelectionChanged(this, &SCsGraphPin_EnumStructMask::ComboBoxSelectionChanged)
		.Visibility(this, &SGraphPin::GetDefaultValueVisibility)
		.OnGetDisplayName(this, &SCsGraphPin_EnumStructMask::OnGetFriendlyName)
		.OnGetTooltip(this, &SCsGraphPin_EnumStructMask::OnGetTooltip);
}

void SCsGraphPin_EnumStructMask::GenerateComboBoxIndexes(TArray< TSharedPtr<int32> >& OutComboBoxIndexes){}

FString SCsGraphPin_EnumStructMask::OnGetText() const
{
	return NCsGraphPinEnumStructMaskCached::Str::INVALID;
}

void SCsGraphPin_EnumStructMask::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo){}

FText SCsGraphPin_EnumStructMask::OnGetFriendlyName(int32 EnumIndex)
{
	return NCsGraphPinEnumStructMaskCached::Txt::INVALID;
}

FText SCsGraphPin_EnumStructMask::OnGetTooltip(int32 EnumIndex)
{
	return NCsGraphPinEnumStructMaskCached::Txt::INVALID;
}

