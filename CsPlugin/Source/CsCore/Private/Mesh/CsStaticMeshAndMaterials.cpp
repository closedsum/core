// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Mesh/CsStaticMeshAndMaterials.h"

// Library
#include "Material/CsLibrary_Material.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsStaticMeshAndMaterials)

bool FCsStaticMeshAndMaterials::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	check(Materials.IsValidChecked(Context));
	check(CsMaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()))
	return true;
}

bool FCsStaticMeshAndMaterials::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Materials is Valid
	if (!Materials.IsValid(Context, Log))
		return false;
	if (!CsMaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
		return false;
	return true;
}