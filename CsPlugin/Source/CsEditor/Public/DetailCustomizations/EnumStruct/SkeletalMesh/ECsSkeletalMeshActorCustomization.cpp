// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/SkeletalMesh/ECsSkeletalMeshActorCustomization.h"

// Managers
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "ECsSkeletalMeshActorCustomization"

// Cached
#pragma region

namespace NCsSkeletalMeshActorCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsSkeletalMeshActorCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsSkeletalMeshActor
#define EnumType FECsSkeletalMeshActor

FECsSkeletalMeshActorCustomization::FECsSkeletalMeshActorCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsSkeletalMeshActorCustomization::CustomPopulateEnumMap()
{
	using namespace NCsSkeletalMeshActorCustomization::NCached;

	NCsSkeletalMeshActor::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsSkeletalMeshActorCustomization::MakeInstance()
{
	return MakeShareable(new FECsSkeletalMeshActorCustomization);
}

void FECsSkeletalMeshActorCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsSkeletalMeshActorCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsSkeletalMeshActorCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
