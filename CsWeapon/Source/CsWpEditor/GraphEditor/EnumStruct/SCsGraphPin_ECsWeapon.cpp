// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeapon.h"
#include "CsWpEditor.h"

#include "CsTypes_Weapon.h"

// Cached
#pragma region

namespace NCsGraphPinWeaponCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsWeapon::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsWeapon::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeapon, FECsWeapon>();
}

void SCsGraphPin_ECsWeapon::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinWeaponCached;

	NCsWeapon::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsWeapon::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeapon>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeapon::OnGetText() const
{
	return OnGetText_Internal<EMCsWeapon, FECsWeapon>();
}

void SCsGraphPin_ECsWeapon::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeapon, FECsWeapon>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeapon::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeapon>(EnumIndex);
}

FText SCsGraphPin_ECsWeapon::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeapon>(EnumIndex);
}



