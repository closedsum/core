// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SCsGraphPin_ECsBeam.h"
#include "CsBeamEditor.h"

#include "Types/CsTypes_Beam.h"

// Cached
#pragma region

namespace NCsGraphPinBeamCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsBeam::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

#define EnumMapType EMCsBeam
#define EnumType FECsBeam

void SCsGraphPin_ECsBeam::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EnumMapType, FECsBeam>();
}

void SCsGraphPin_ECsBeam::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinBeamCached;

	NCsBeam::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsBeam::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EnumMapType>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsBeam::OnGetText() const
{
	return OnGetText_Internal<EnumMapType, EnumType>();
}

void SCsGraphPin_ECsBeam::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EnumMapType, EnumType>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsBeam::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EnumMapType>(EnumIndex);
}

FText SCsGraphPin_ECsBeam::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EnumMapType>(EnumIndex);
}

#undef EnumMapType
#undef EnumType