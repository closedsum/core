// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsTypes_Data_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Data_Projectile)

#define InfoType NCsProjectile::NVisual::NStaticMesh::FInfo

void FCsPrjStaticMesh::CopyToInfo(InfoType* Info)
{
	Info->SetMesh(Mesh.GetPtr());
	Info->SetScale(&Scale);
	Info->SetbScaleByCollisionRadius(&bScaleByCollisionRadius);
}

void FCsPrjStaticMesh::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetMesh(Mesh.Get());
	Info->SetScale(Scale);
	Info->SetbScaleByCollisionRadius(bScaleByCollisionRadius);
}

#undef InfoType

bool FCsPrjStaticMesh::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Mesh);
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_CHECKED(Scale, 0.0f)
	return true;
}

bool FCsPrjStaticMesh::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(Mesh)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN(Scale, 0.0f)
	return true;
}

#define InfoType NCsProjectile::NVisual::NStaticMesh::FInfo

void FCsProjectile_Visual_StaticMeshInfo::CopyToInfo(InfoType* Info)
{
	Info->SetMesh(Mesh.GetPtr());
	Info->SetScale(&Scale);
	Info->SetbScaleByCollisionRadius(&bScaleByCollisionRadius);
	Info->SetScaleByCollisionRadiusMultiplier(&ScaleByCollisionRadiusMultiplier);
}

void FCsProjectile_Visual_StaticMeshInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetMesh(Mesh.Get());
	Info->SetScale(Scale);
	Info->SetbScaleByCollisionRadius(bScaleByCollisionRadius);
	Info->SetScaleByCollisionRadiusMultiplier(ScaleByCollisionRadiusMultiplier);
}

#undef InfoType

bool FCsProjectile_Visual_StaticMeshInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Mesh);
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN_CHECKED(Scale, 0.0f)

	if (bScaleByCollisionRadius)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(ScaleByCollisionRadiusMultiplier, 0.0f)
	}
	return true;
}

bool FCsProjectile_Visual_StaticMeshInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_VALID(Mesh)
	CS_IS_VECTOR_COMPONENTS_GREATER_THAN(Scale, 0.0f)

	if (bScaleByCollisionRadius)
	{
		CS_IS_FLOAT_GREATER_THAN(ScaleByCollisionRadiusMultiplier, 0.0f)
	}
	return true;
}

namespace NCsProjectile
{
	namespace NVisual
	{
		namespace NStaticMesh
		{
			bool FInfo::IsValidChecked(const FString& Context) const
			{
				CS_IS_PTR_NULL_CHECKED(GetMesh())
				CS_IS_VECTOR_COMPONENTS_GREATER_THAN_CHECKED(GetScale(), 0.0f)

				if (GetbScaleByCollisionRadius())
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(GetScaleByCollisionRadiusMultiplier(), 0.0f)
				}
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_PTR_NULL(Mesh)
				CS_IS_VECTOR_COMPONENTS_GREATER_THAN(GetScale(), 0.0f)

				if (GetbScaleByCollisionRadius())
				{
					CS_IS_FLOAT_GREATER_THAN(GetScaleByCollisionRadiusMultiplier(), 0.0f)
				}
				return true;
			}
		}
	}
}