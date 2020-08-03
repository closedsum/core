// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsWeaponClass.h"
#include "CsWpEditor.h"

#include "CsTypes_Weapon.h"

// Cached
#pragma region

namespace NCsGraphPinWeaponClassCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsWeaponClass::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsWeaponClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsWeaponClass, FECsWeaponClass>();
}

void SCsGraphPin_ECsWeaponClass::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinWeaponClassCached;

	NCsWeaponClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsWeaponClass::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsWeaponClass>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsWeaponClass::OnGetText() const
{
	return OnGetText_Internal<EMCsWeaponClass, FECsWeaponClass>();
}

void SCsGraphPin_ECsWeaponClass::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsWeaponClass, FECsWeaponClass>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsWeaponClass::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsWeaponClass>(EnumIndex);
}

FText SCsGraphPin_ECsWeaponClass::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsWeaponClass>(EnumIndex);
}