// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectile.h"
#include "CsEditor.h"

#include "Managers/Projectile/CsTypes_Projectile.h"

// Cached
#pragma region

namespace NCsGraphPinProjectileCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsProjectile::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsProjectile::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsProjectile, FECsProjectile>();
}

void SCsGraphPin_ECsProjectile::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinProjectileCached;

	NCsProjectile::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsProjectile::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsProjectile>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectile::OnGetText() const
{
	return OnGetText_Internal<EMCsProjectile, FECsProjectile>();
}

void SCsGraphPin_ECsProjectile::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsProjectile, FECsProjectile>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectile::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsProjectile>(EnumIndex);
}

FText SCsGraphPin_ECsProjectile::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsProjectile>(EnumIndex);
}