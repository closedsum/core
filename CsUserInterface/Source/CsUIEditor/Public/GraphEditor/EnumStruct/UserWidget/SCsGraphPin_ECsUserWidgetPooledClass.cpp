// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooledClass.h"
#include "CsUIEditor.h"

#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetPooledClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidgetPooledClass::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE SCsGraphPin_ECsUserWidgetPooledClass
#define EnumMapType EMCsUserWidgetPooledClass
#define EnumType FECsUserWidgetPooledClass

void CLASS_TYPE::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetPooledClass::NCached;

	NCsUserWidgetPooledClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void CLASS_TYPE::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EnumMapType>(OutComboBoxIndexes);
}

FString CLASS_TYPE::OnGetText() const
{
	return OnGetText_Internal<EnumMapType, EnumType>();
}

void CLASS_TYPE::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EnumMapType, EnumType>(NewSelection, SelectInfo);
}

FText CLASS_TYPE::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EnumMapType>(EnumIndex);
}

FText CLASS_TYPE::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EnumMapType>(EnumIndex);
}

#undef CLASS_TYPE
#undef EnumMapType
#undef EnumType