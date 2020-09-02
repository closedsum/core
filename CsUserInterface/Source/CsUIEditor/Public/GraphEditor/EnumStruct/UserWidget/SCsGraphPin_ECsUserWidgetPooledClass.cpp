// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooledClass.h"
#include "CsUIEditor.h"

#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetPooledClassCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidgetPooledClass::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsUserWidgetPooledClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass>();
}

void SCsGraphPin_ECsUserWidgetPooledClass::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetPooledClassCached;

	NCsUserWidgetPooledClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsUserWidgetPooledClass::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsUserWidgetPooledClass>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsUserWidgetPooledClass::OnGetText() const
{
	return OnGetText_Internal<EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass>();
}

void SCsGraphPin_ECsUserWidgetPooledClass::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsUserWidgetPooledClass::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsUserWidgetPooledClass>(EnumIndex);
}

FText SCsGraphPin_ECsUserWidgetPooledClass::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsUserWidgetPooledClass>(EnumIndex);
}