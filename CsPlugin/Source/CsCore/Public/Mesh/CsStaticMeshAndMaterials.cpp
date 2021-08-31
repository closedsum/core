// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Mesh/CsStaticMeshAndMaterials.h"

// Library
#include "Material/CsLibrary_Material.h"

bool FCsStaticMeshAndMaterials::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	check(Materials.IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	check(MaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()))
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

	typedef NCsMaterial::FLibrary MaterialLibrary;

	if (!MaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
		return false;
	return true;
}