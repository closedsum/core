// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/StaticMesh/ECsStaticMeshActorCustomization.h"

// Managers
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

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

#define EnumMapType EMCsStaticMeshActor
#define EnumType FECsStaticMeshActor

FECsStaticMeshActorCustomization::FECsStaticMeshActorCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
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
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsStaticMeshActorCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsStaticMeshActorCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
