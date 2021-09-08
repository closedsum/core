// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/WidgetActor/SCsGraphPin_ECsWidgetActor.h"
#include "CsUIEditor.h"

#include "Managers/WidgetActor/CsTypes_WidgetActor.h"

// Cached
#pragma region

namespace NCsGraphPinWidgetActorCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsWidgetActor::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsWidgetActor::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWidgetActor, FECsWidgetActor>();
}

void SCsGraphPin_ECsWidgetActor::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinWidgetActorCached;

	NCsWidgetActor::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsWidgetActor::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWidgetActor>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWidgetActor::OnGetText() const
{
	return OnGetText_Internal<EMCsWidgetActor, FECsWidgetActor>();
}

void SCsGraphPin_ECsWidgetActor::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWidgetActor, FECsWidgetActor>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWidgetActor::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWidgetActor>(EnumIndex);
}

FText SCsGraphPin_ECsWidgetActor::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWidgetActor>(EnumIndex);
}