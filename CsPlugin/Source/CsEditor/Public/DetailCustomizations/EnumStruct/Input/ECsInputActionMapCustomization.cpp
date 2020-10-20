// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionMapCustomization.h"

#include "Managers/Input/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsInputActionMapCustomization"

// Cached
#pragma region

namespace NCsInputActionMapCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsInputActionMapCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

FECsInputActionMapCustomization::FECsInputActionMapCustomization() :
	Super()
{
	Init<EMCsInputActionMap, FECsInputActionMap>();
}

void FECsInputActionMapCustomization::CustomPopulateEnumMap()
{
	using namespace NCsInputActionMapCustomization::NCached;

	NCsInputActionMap::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionMapCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionMapCustomization);
}

void FECsInputActionMapCustomization::AddEnumToMap(const FString& Name)
{
	EMCsInputActionMap::Get().CreateSafe(Name, true);
}

const FString& FECsInputActionMapCustomization::GetEnumStructName()
{
	return EMCsInputActionMap::Get().GetEnumName();
}

const FName& FECsInputActionMapCustomization::GetEnumStructFName()
{
	return EMCsInputActionMap::Get().GetEnumFName();
}

void FECsInputActionMapCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsInputActionMap>(StructPropertyHandle);
}

void FECsInputActionMapCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsInputActionMap, FECsInputActionMap, int32>(DisplayName);
}

void FECsInputActionMapCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsInputActionMap, FECsInputActionMap>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
