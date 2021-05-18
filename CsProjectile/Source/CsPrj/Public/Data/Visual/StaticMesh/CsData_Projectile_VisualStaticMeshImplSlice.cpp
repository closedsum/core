// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Visual/StaticMesh/CsData_Projectile_VisualStaticMeshImplSlice.h"

#define SliceType NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice
void FCsData_Projectile_VisualStaticMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetStaticMesh(&Mesh);
}

void FCsData_Projectile_VisualStaticMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetStaticMesh(Mesh);
}

#undef SliceType

bool FCsData_Projectile_VisualStaticMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice::Name = FName("NCsProjectile::NData::NVisual::NStaticMesh::FImplSlice");
