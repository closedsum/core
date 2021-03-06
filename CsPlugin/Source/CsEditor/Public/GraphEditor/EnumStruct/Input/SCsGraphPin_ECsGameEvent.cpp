// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Input/SCsGraphPin_ECsGameEvent.h"
#include "CsEditor.h"

#include "Managers/Input/CsTypes_Input.h"

// Cached
#pragma region

namespace NCsGraphPinGameEventCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsGameEvent::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsGameEvent::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsGameEvent, FECsGameEvent>();
}

void SCsGraphPin_ECsGameEvent::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinGameEventCached;

	NCsGameEvent::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsGameEvent::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsGameEvent>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsGameEvent::OnGetText() const
{
	return OnGetText_Internal<EMCsGameEvent, FECsGameEvent>();
}

void SCsGraphPin_ECsGameEvent::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsGameEvent, FECsGameEvent>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsGameEvent::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsGameEvent>(EnumIndex);
}

FText SCsGraphPin_ECsGameEvent::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsGameEvent>(EnumIndex);
}