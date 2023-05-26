// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsProjectileClassCustomization.h"

// Types
#include "Types/CsTypes_Projectile.h"

#define LOCTEXT_NAMESPACE "ECsProjectileClassCustomization"

// Cached
#pragma region

namespace NCsProjectileClassCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsProjectileClassCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsProjectileClass
#define EnumType FECsProjectileClass

FECsProjectileClassCustomization::FECsProjectileClassCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsProjectileClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsProjectileClassCustomization::NCached;

	NCsProjectileClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsProjectileClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsProjectileClassCustomization);
}

void FECsProjectileClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsProjectileClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsProjectileClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
