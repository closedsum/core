// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/StaticMesh/ECsStaticMeshActorCustomization.h"

// Managers
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "ECsStaticMeshActorCustomization"

// Cached
#pragma region

namespace NCsStaticMeshActorCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsStaticMeshActorCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

FECsStaticMeshActorCustomization::FECsStaticMeshActorCustomization() :
	Super()
{
	Init<EMCsStaticMeshActor, FECsStaticMeshActor>();
}

void FECsStaticMeshActorCustomization::CustomPopulateEnumMap()
{
	using namespace NCsStaticMeshActorCustomization::NCached;

	NCsStaticMeshActor::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsStaticMeshActorCustomization::MakeInstance()
{
	return MakeShareable(new FECsStaticMeshActorCustomization);
}

void FECsStaticMeshActorCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsStaticMeshActor>(StructPropertyHandle);
}

void FECsStaticMeshActorCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsStaticMeshActor, FECsStaticMeshActor>(DisplayName);
}

void FECsStaticMeshActorCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsStaticMeshActor, FECsStaticMeshActor>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
