// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/Update/SCsGraphPin_ECsUpdateGroup.h"
#include "CsEditor.h"

#include "Managers/Time/CsTypes_Update.h"

// Cached
#pragma region

namespace NCsGraphPinUpdateGroup
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsUpdateGroup::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsUpdateGroup::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsUpdateGroup, FECsUpdateGroup>();
}

void SCsGraphPin_ECsUpdateGroup::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinUpdateGroup::NCached;

	//NCsUpdateGroup::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsUpdateGroup::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsUpdateGroup>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsUpdateGroup::OnGetText() const
{
	return OnGetText_Internal<EMCsUpdateGroup, FECsUpdateGroup>();
}

void SCsGraphPin_ECsUpdateGroup::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsUpdateGroup, FECsUpdateGroup>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsUpdateGroup::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsUpdateGroup>(EnumIndex);
}

FText SCsGraphPin_ECsUpdateGroup::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsUpdateGroup>(EnumIndex);
}



