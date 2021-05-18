// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsTypes_Data_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"

bool FCsPrjStaticMesh::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;

	CS_IS_FLOAT_GREATER_THAN(Scale.X, 0.0f)

	CS_IS_FLOAT_GREATER_THAN(Scale.Y, 0.0f)

	CS_IS_FLOAT_GREATER_THAN(Scale.Z, 0.0f)

	return true;
}