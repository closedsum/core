// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetClass.h"
#include "CsUIEditor.h"

#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetClassCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidgetClass::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsUserWidgetClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsUserWidgetClass, FECsUserWidgetClass>();
}

void SCsGraphPin_ECsUserWidgetClass::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetClassCached;

	NCsUserWidgetClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsUserWidgetClass::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsUserWidgetClass>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsUserWidgetClass::OnGetText() const
{
	return OnGetText_Internal<EMCsUserWidgetClass, FECsUserWidgetClass>();
}

void SCsGraphPin_ECsUserWidgetClass::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsUserWidgetClass, FECsUserWidgetClass>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsUserWidgetClass::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsUserWidgetClass>(EnumIndex);
}

FText SCsGraphPin_ECsUserWidgetClass::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsUserWidgetClass>(EnumIndex);
}