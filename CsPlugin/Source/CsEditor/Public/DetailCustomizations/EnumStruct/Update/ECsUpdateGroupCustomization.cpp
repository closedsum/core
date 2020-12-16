// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Update/ECsUpdateGroupCustomization.h"

#include "Managers/Time/CsTypes_Update.h"

#define LOCTEXT_NAMESPACE "ECsUpdateGroupCustomization"

// Cached
#pragma region

namespace NCsUpdateGroupCustomization
{
	namespace NCached
	{
		namespace Str
		{
			const FString CustomPopulateEnumMap = TEXT("FECsUpdateGroupCustomization::CustomPopulateEnumMap");
		}
	}
}

#pragma endregion Cached

FECsUpdateGroupCustomization::FECsUpdateGroupCustomization() :
	Super()
{
	Init<EMCsUpdateGroup, FECsUpdateGroup>();
}

void FECsUpdateGroupCustomization::CustomPopulateEnumMap()
{
	using namespace NCsUpdateGroupCustomization::NCached;

	//NCsUpdateGroup::PopulateEnumMapFromSettings(Str::CustomPopulateEnumMap, nullptr);
}

TSharedRef<IPropertyTypeCustomization> FECsUpdateGroupCustomization::MakeInstance()
{
	return MakeShareable(new FECsUpdateGroupCustomization);
}

void FECsUpdateGroupCustomization::AddEnumToMap(const FString& Name)
{
	EMCsUpdateGroup::Get().CreateSafe(Name, true);
}

const FString& FECsUpdateGroupCustomization::GetEnumStructName()
{
	return EMCsUpdateGroup::Get().GetEnumName();
}

const FName& FECsUpdateGroupCustomization::GetEnumStructFName()
{
	return EMCsUpdateGroup::Get().GetEnumFName();
}

void FECsUpdateGroupCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsUpdateGroup>(StructPropertyHandle);
}

void FECsUpdateGroupCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<EMCsUpdateGroup, FECsUpdateGroup>(DisplayName);
}

void FECsUpdateGroupCustomization::GetDisplayNamePropertyValue(FString& OutDisplayName) const
{
	GetDisplayNamePropertyValue_Internal<EMCsUpdateGroup, FECsUpdateGroup>(OutDisplayName);
}

#undef LOCTEXT_NAMESPACE
