// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Anim/ECsVertexAnimNotifyCustomization.h"

// Types
#include "Animation/Vertex/CsVertexAnimNotify.h"
// Settings
#include "Settings/CsDeveloperSettings.h"

#define LOCTEXT_NAMESPACE "ECsVertexAnimNotifyCustomization"

// Cached
#pragma region

namespace NCsVertexAnimNotifyCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsVertexAnimNotifyCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsVertexAnimNotify
#define EnumType FECsVertexAnimNotify

FECsVertexAnimNotifyCustomization::FECsVertexAnimNotifyCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsVertexAnimNotifyCustomization::CustomPopulateEnumMap()
{
	using namespace NCsVertexAnimNotifyCustomization::NCached;

	NCsVertexAnimNotify::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsVertexAnimNotifyCustomization::MakeInstance()
{
	return MakeShareable(new FECsVertexAnimNotifyCustomization);
}

void FECsVertexAnimNotifyCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsVertexAnimNotifyCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsVertexAnimNotifyCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
