// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/UserWidget/SCsGraphPin_ECsUserWidgetClass.h"
#include "CsUIEditor.h"

// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

// Cached
#pragma region

namespace NCsGraphPinUserWidgetClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUserWidgetClass::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE SCsGraphPin_ECsUserWidgetClass
#define EnumMapType EMCsUserWidgetClass
#define EnumType FECsUserWidgetClass

void CLASS_TYPE::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUserWidgetClass::NCached;

	NCsUserWidgetClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
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
	ComboBoxSelectionChanged_Internal<EnumMapType, FECsUserWidgetClass>(NewSelection, SelectInfo);
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