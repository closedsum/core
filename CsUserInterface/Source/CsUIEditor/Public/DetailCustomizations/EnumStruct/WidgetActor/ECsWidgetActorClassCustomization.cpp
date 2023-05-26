// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/WidgetActor/ECsWidgetActorClassCustomization.h"

// Types
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"

#define LOCTEXT_NAMESPACE "ECsWidgetActorClassCustomization"

// Cached
#pragma region

namespace NCsWidgetActorClassCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsWidgetActorClassCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

#define CLASS_TYPE FECsWidgetActorClassCustomization
#define EnumMapType EMCsWidgetActorClass
#define EnumType FECsWidgetActorClass

CLASS_TYPE::CLASS_TYPE() :
	Super()
{
	Init<EnumMapType, EnumType>();
}

void CLASS_TYPE::CustomPopulateEnumMap()
{
	using namespace NCsWidgetActorClassCustomization::NCached;

	NCsWidgetActorClass::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> CLASS_TYPE::MakeInstance()
{
	return MakeShareable(new CLASS_TYPE);
}

void CLASS_TYPE::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<EnumType>(StructPropertyHandle);
}

void CLASS_TYPE::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EnumMapType, EnumType>(DisplayName);
}

void CLASS_TYPE::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EnumMapType, EnumType>(OutDisplayName);
}

#undef CLASS_TYPE
#undef EnumMapType
#undef EnumType

#undef LOCTEXT_NAMESPACE
