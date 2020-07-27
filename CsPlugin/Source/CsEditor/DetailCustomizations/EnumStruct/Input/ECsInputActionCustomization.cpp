// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Input/ECsInputActionCustomization.h"

#include "Managers/Input/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsInputActionCustomization"

// Cached
#pragma region

namespace NCsInputActionCustomizationCached
{
	namespace Str
	{
		const FString CustomPopulateEnumMap = TEXT("FECsInputActionCustomization::CustomPopulateEnumMap");
	}
}

#pragma endregion Cached

FECsInputActionCustomization::FECsInputActionCustomization() :
	Super()
{
	Init<EMCsInputAction, FECsInputAction>();
}

void FECsInputActionCustomization::CustomPopulateEnumMap()
{
	using namespace NCsInputActionCustomizationCached;

	NCsInputAction::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionCustomization);
}

void FECsInputActionCustomization::AddEnumToMap(const FString& Name)
{
	EMCsInputAction::Get().CreateSafe(Name, true);
}

const FString& FECsInputActionCustomization::GetEnumStructName()
{
	return EMCsInputAction::Get().GetEnumName();
}

const FName& FECsInputActionCustomization::GetEnumStructFName()
{
	return EMCsInputAction::Get().GetEnumFName();
}

const FECsUserDefinedEnum& FECsInputActionCustomization::GetUserDefinedEnumType()
{
	return NCsUserDefinedEnum::FECsInputAction;
}

void FECsInputActionCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsInputAction>(StructPropertyHandle);
}

void FECsInputActionCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsInputAction, FECsInputAction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
