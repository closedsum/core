// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileClass.h"
#include "CsPrjEditor.h"

#include "Managers/Projectile/CsTypes_Projectile.h"

// Cached
#pragma region

namespace NCsGraphPinProjectileClassCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsProjectileClass::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsProjectileClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsProjectileClass, FECsProjectileClass>();
}

void SCsGraphPin_ECsProjectileClass::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinProjectileClassCached;

	NCsProjectileClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsProjectileClass::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProjectileClass>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectileClass::OnGetText() const
{
	return OnGetText_Internal<EMCsProjectileClass, FECsProjectileClass>();
}

void SCsGraphPin_ECsProjectileClass::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsProjectileClass, FECsProjectileClass>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectileClass::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProjectileClass>(EnumIndex);
}

FText SCsGraphPin_ECsProjectileClass::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProjectileClass>(EnumIndex);
}