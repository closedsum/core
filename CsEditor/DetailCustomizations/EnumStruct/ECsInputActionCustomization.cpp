// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsInputActionCustomization.h"

#include "Managers/Input/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsInputActionCustomization"


FECsInputActionCustomization::FECsInputActionCustomization()
{
	bPopulateEnumMapFromUserDefinedEnum 	= true;
	
	Init<FECsInputAction, EMCsInputAction>();
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionCustomization);
}

void FECsInputActionCustomization::CustomPopulateEnumMap()
{
	//FR6EnumEditorUtils::SyncInputAction();
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
	SetEnumWithDisplayName_Internal<FECsInputAction, EMCsInputAction>(DisplayName);
}

#undef LOCTEXT_NAMESPACE
