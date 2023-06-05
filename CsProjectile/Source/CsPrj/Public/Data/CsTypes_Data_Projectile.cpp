// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsTypes_Data_Projectile.h"

// Library
#include "Library/CsLibrary_Valid.h"

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
				return true;
			}

			bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_PTR_NULL(Mesh)
				CS_IS_VECTOR_COMPONENTS_GREATER_THAN(GetScale(), 0.0f)
				return true;
			}
		}
	}
}