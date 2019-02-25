// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "DetailCustomizations/EnumStruct/ECsInputActionCustomization.h"

#include "Types/CsTypes_Input.h"

#define LOCTEXT_NAMESPACE "ECsInputActionCustomization"


FECsInputActionCustomization::FECsInputActionCustomization()
{
	UserDefinedEnumObjectPath		= FName("");
	bPopulateEnumMapFromUserDefinedEnum 	= true;
	
	Init<FECsInputAction, EMCsInputAction>();
}

void FECsInputActionCustomization::CustomPopulateEnumMap()
{
	//FR6EnumEditorUtils::SyncInputAction();
}

void FECsInputActionCustomization::AddEnumToMap(const FString& Name)
{
	EMCsInputAction::Get().CreateSafe(Name, true);
}

FString FECsInputActionCustomization::GetEnumStructName()
{
	return TEXT("FECsInputAction");
}

TSharedRef<IPropertyTypeCustomization> FECsInputActionCustomization::MakeInstance()
{
	return MakeShareable(new FECsInputActionCustomization);
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
