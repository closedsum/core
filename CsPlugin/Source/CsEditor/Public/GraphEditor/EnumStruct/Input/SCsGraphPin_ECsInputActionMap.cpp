// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsInputActionMap.h"
#include "CsEditor.h"

#include "Managers/Input/Action/CsInputActionMap.h"

// Cached
#pragma region

namespace NCsGraphPinInputActionMap
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsInputActionMap::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsInputActionMap
#define EnumType FECsInputActionMap

void SCsGraphPin_ECsInputActionMap::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsInputActionMap::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinInputActionMap::NCached;

	NCsInputActionMap::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsInputActionMap::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EnumMapType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsInputActionMap::OnGetText() const
{
	return OnGetText_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsInputActionMap::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EnumMapType, EnumType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsInputActionMap::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EnumMapType>(EnumIndex);
}

FText SCsGraphPin_ECsInputActionMap::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EnumMapType>(EnumIndex);
}

#undef EnumMapType
#undef EnumType