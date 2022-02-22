// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Mesh/CsStaticMeshAttachment.h"

// Library
#include "Library/CsLibrary_Valid.h"

bool FCsStaticMeshAttachment::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	CS_IS_VALID_CHECKED(Mesh);
	// Check Materials is Valid
	CS_IS_VALID_CHECKED(Materials);

	typedef NCsMaterial::FLibrary MaterialLibrary;

	check(MaterialLibrary::IsValidChecked(Context, Mesh.Get(), Materials.Get()))
	return true;
}

bool FCsStaticMeshAttachment::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid
	CS_IS_VALID(Mesh)
	// Check Materials is Valid
	CS_IS_VALID(Materials)

	typedef NCsMaterial::FLibrary MaterialLibrary;

	if (!MaterialLibrary::IsValid(Context, Mesh.Get(), Materials.Get(), Log))
		return false;
	return true;
}