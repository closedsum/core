// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooled.h"
#include "CsUIEditor.h"

#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetPooledCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidgetPooled::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsUserWidgetPooled::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsUserWidgetPooled, FECsUserWidgetPooled>();
}

void SCsGraphPin_ECsUserWidgetPooled::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetPooledCached;

	NCsUserWidgetPooled::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsUserWidgetPooled::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsUserWidgetPooled>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsUserWidgetPooled::OnGetText() const
{
	return OnGetText_Internal<EMCsUserWidgetPooled, FECsUserWidgetPooled>();
}

void SCsGraphPin_ECsUserWidgetPooled::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsUserWidgetPooled, FECsUserWidgetPooled>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsUserWidgetPooled::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsUserWidgetPooled>(EnumIndex);
}

FText SCsGraphPin_ECsUserWidgetPooled::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsUserWidgetPooled>(EnumIndex);
}