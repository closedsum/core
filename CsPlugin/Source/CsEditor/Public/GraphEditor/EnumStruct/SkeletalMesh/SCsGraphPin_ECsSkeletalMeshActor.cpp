// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "GraphEditor/EnumStruct/SkeletalMesh/SCsGraphPin_ECsSkeletalMeshActor.h"
#include "CsEditor.h"

#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"

// Cached
#pragma region

namespace NCsGraphPinSkeletalMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("SCsGraphPin_ECsSkeletalMeshActor::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

void SCsGraphPin_ECsSkeletalMeshActor::Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);

	Construct_Internal<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>();
}

void SCsGraphPin_ECsSkeletalMeshActor::CustomPopulateEnumMap()
{
	using namespace NCsGraphPinSkeletalMeshActor::NCached;

	NCsSkeletalMeshActor::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

void SCsGraphPin_ECsSkeletalMeshActor::GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
{
	GenenerateComboBoxIndexes_Internal<EMCsSkeletalMeshActor>(OutComboBoxIndexes);
}

FString SCsGraphPin_ECsSkeletalMeshActor::OnGetText() const
{
	return OnGetText_Internal<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>();
}

void SCsGraphPin_ECsSkeletalMeshActor::ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo)
{
	ComboBoxSelectionChanged_Internal<EMCsSkeletalMeshActor, FECsSkeletalMeshActor>(NewSelection, SelectInfo);
}

FText SCsGraphPin_ECsSkeletalMeshActor::OnGetFriendlyName(int32 EnumIndex)
{
	return OnGetFriendlyName_Internal<EMCsSkeletalMeshActor>(EnumIndex);
}

FText SCsGraphPin_ECsSkeletalMeshActor::OnGetTooltip(int32 EnumIndex)
{
	return OnGetTooltip_Internal<EMCsSkeletalMeshActor>(EnumIndex);
}