// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Material/CsTypes_Material.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"

// FCsTArrayMaterialInterface
#pragma region

void FCsTArrayMaterialInterface::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
{
	check(IsValidChecked(Context))

	CS_IS_PTR_NULL_CHECKED(Component)

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Component, Materials_Internal);
}

bool FCsTArrayMaterialInterface::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context))
		return false;

	CS_IS_PTR_NULL(Component)

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials_Internal, Log);
}

#pragma endregion FCsTArrayMaterialInterface

// FCsMaterialParameterFloat
#pragma region

bool FCsMaterialParameterFloat::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}
bool FCsMaterialParameterFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const 
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialParameterFloat

// FCsMaterialParameterFloatRange
#pragma region

bool FCsMaterialParameterFloatRange::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Max, Min)
	return true;
}
bool FCsMaterialParameterFloatRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Max, Min)
	return true;
}

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NFloat
		{
			bool FRange::IsValidChecked(const FString& Context) const
			{
				CS_IS_NAME_NONE_CHECKED(GetName())
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetMax(), GetMin())
				return true;
			}
			bool FRange::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_NAME_NONE(GetName())
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetMax(), GetMin())
				return true;
			}
		}
	}
}

#pragma endregion FCsMaterialParameterFloatRange

// FCsMaterialParameterColor
#pragma region

bool FCsMaterialParameterColor::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)
	return true;
}
bool FCsMaterialParameterColor::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)
	return true;
}

#pragma endregion FCsMaterialParameterColor