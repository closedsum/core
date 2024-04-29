// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsProjectileClass.h"
#include "CsPrjEditor.h"

#include "Types/CsTypes_Projectile.h"

// Cached
#pragma region

namespace NCsGraphPinProjectileClass
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsProjectileClass::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsProjectileClass
#define EnumType FECsProjectileClass

void SCsGraphPin_ECsProjectileClass::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsProjectileClass::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinProjectileClass::NCached;

	NCsProjectileClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsProjectileClass::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EnumMapType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsProjectileClass::OnGetText() const
{
	return OnGetText_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsProjectileClass::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EnumMapType, EnumType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsProjectileClass::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EnumMapType>(EnumIndex);
}

FText SCsGraphPin_ECsProjectileClass::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EnumMapType>(EnumIndex);
}

#undef EnumMapType
#undef EnumType