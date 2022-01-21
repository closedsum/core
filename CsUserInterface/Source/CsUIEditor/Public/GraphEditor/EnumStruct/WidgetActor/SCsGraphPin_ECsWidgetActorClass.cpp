// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/WidgetActor/SCsGraphPin_ECsWidgetActorClass.h"
#include "CsUIEditor.h"

#include "Managers/WidgetActor/CsTypes_WidgetActor.h"

// Cached
#pragma region

namespace NCsGraphPinWidgetActorClassCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsWidgetActorClass::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsWidgetActorClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWidgetActorClass, FECsWidgetActorClass>();
}

void SCsGraphPin_ECsWidgetActorClass::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinWidgetActorClassCached;

	NCsWidgetActorClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsWidgetActorClass::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWidgetActorClass>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWidgetActorClass::OnGetText() const
{
	return OnGetText_Internal<EMCsWidgetActorClass, FECsWidgetActorClass>();
}

void SCsGraphPin_ECsWidgetActorClass::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWidgetActorClass, FECsWidgetActorClass>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWidgetActorClass::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWidgetActorClass>(EnumIndex);
}

FText SCsGraphPin_ECsWidgetActorClass::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWidgetActorClass>(EnumIndex);
}