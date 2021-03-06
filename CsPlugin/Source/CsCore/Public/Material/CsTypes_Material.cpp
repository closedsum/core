// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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