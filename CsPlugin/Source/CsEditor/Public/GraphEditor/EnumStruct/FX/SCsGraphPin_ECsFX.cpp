// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/FX/SCsGraphPin_ECsFX.h"
#include "CsEditor.h"

#include "Managers/FX/CsTypes_FX.h"

// Cached
#pragma region

namespace NCsGraphPinFXCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsFX::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsFX::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsFX, FECsFX>();
}

void SCsGraphPin_ECsFX::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinFXCached;

	NCsFX::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsFX::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsFX>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsFX::OnGetText() const
{
	return OnGetText_Internal<EMCsFX, FECsFX>();
}

void SCsGraphPin_ECsFX::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsFX, FECsFX>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsFX::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsFX>(EnumIndex);
}

FText SCsGraphPin_ECsFX::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsFX>(EnumIndex);
}