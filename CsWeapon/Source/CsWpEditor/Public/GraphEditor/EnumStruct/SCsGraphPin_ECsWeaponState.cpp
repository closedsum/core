// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponState.h"
#include "CsWpEditor.h"

#include "Types/CsTypes_Weapon.h"

// Cached
#pragma region

namespace NCsGraphPinWeaponStateCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsWeaponState::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsWeaponState::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponState, FECsWeaponState>();
}

void SCsGraphPin_ECsWeaponState::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinWeaponStateCached;

	NCsWeaponState::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsWeaponState::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponState>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponState::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponState, FECsWeaponState>();
}

void SCsGraphPin_ECsWeaponState::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponState, FECsWeaponState>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponState::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponState>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponState::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponState>(EnumIndex);
}



