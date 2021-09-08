// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsBeamClassCustomization.h"

// Types
#include "Types/CsTypes_Beam.h"

#define LOCTEXT_NAMESPACE "ECsBeamClassCustomization"

// Cached
#pragma region

namespace NCsBeamClassCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsBeamClassCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define EnumMapType EMCsBeamClass
#define EnumType FECsBeamClass

FECsBeamClassCustomization::FECsBeamClassCustomization() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void FECsBeamClassCustomization::CustomPopulateEnumMap()
{
	using namespace NCsBeamClassCustomization::NCached;

	NCsBeamClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsBeamClassCustomization::MakeInstance()
{
	return MakeShareable(new FECsBeamClassCustomization);
}

void FECsBeamClassCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void FECsBeamClassCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void FECsBeamClassCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
