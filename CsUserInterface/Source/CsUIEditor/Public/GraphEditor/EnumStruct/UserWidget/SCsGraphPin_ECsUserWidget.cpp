// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidget.h"
#include "CsUIEditor.h"

#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidget::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsUserWidget::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsUserWidget, FECsUserWidget>();
}

void SCsGraphPin_ECsUserWidget::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetCached;

	NCsUserWidget::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsUserWidget::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsUserWidget>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsUserWidget::OnGetText() const
{
	return OnGetText_Internal<EMCsUserWidget, FECsUserWidget>();
}

void SCsGraphPin_ECsUserWidget::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsUserWidget, FECsUserWidget>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsUserWidget::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsUserWidget>(EnumIndex);
}

FText SCsGraphPin_ECsUserWidget::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsUserWidget>(EnumIndex);
}