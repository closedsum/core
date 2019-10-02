// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/Damage/ECsHitTypeCustomization.h"

#include "Types/CsTypes_Damage.h"

#define LOCTEXT_NAMESPACE "ECsHitTypeCustomization"


FECsHitTypeCustomization::FECsHitTypeCustomization()
{
	Init<FECsHitType, EMCsHitType>();
}

TSharedRef<IPropertyTypeCustomization> FECsHitTypeCustomization::MakeInstance()
{
	return MakeShareable(new FECsHitTypeCustomization);
}

void FECsHitTypeCustomization::SetPropertyHandles(TSharedRef<IPropertyHandle> StructPropertyHandle)
{
	SetPropertyHandles_Internal<FECsHitType>(StructPropertyHandle);
}

void FECsHitTypeCustomization::SetEnumWithDisplayName(const FString& DisplayName)
{
	SetEnumWithDisplayName_Internal<FECsHitType, EMCsHitType>(DisplayName);
}

#undef LOCTEXT_NAMESPACE