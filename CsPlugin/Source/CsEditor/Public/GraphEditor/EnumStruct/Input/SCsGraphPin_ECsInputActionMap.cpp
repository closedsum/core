// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsInputActionMap.h"
#include "CsEditor.h"

#include "Managers/Input/CsTypes_Input.h"

// Cached
#pragma region

namespace NCsGraphPinInputActionMapCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsInputActionMap::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsInputActionMap::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsInputActionMap, FECsInputActionMap>();
}

void SCsGraphPin_ECsInputActionMap::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinInputActionMapCached;

	NCsInputAction::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsInputActionMap::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsInputActionMap>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsInputActionMap::OnGetText() const
{
	return OnGetText_Internal<EMCsInputActionMap, FECsInputActionMap>();
}

void SCsGraphPin_ECsInputActionMap::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsInputActionMap, FECsInputActionMap>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsInputActionMap::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsInputActionMap>(EnumIndex);
}

FText SCsGraphPin_ECsInputActionMap::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsInputActionMap>(EnumIndex);
}