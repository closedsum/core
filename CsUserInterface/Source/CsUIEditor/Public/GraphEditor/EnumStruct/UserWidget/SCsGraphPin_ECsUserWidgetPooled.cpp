// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetPooled.h"
#include "CsUIEditor.h"

#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetPooled
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidgetPooled::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE SCsGraphPin_ECsUserWidgetPooled
#define EnumMapType EMCsUserWidgetPooled
#define EnumType FECsUserWidgetPooled

void CLASS_TYPE::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetPooled::NCached;

	NCsUserWidgetPooled::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
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