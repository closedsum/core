// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/StaticMesh/CsData_Skin_VisualStaticMeshImplSlice.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/StaticMeshComponent.h"

#define SliceType NCsSkin::NData::NVisual::NStaticMesh::FImplSlice

void FCsData_Skin_VisualStaticMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetStaticMesh(Mesh.GetPtr());
}

void FCsData_Skin_VisualStaticMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetStaticMesh(Mesh.Get());
}

#undef SliceType

bool FCsData_Skin_VisualStaticMeshImplSlice::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualStaticMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualStaticMeshImplSlice::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetStaticMesh(Mesh.Get());
}

void FCsData_Skin_VisualStaticMeshImplSlice::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return;

	CS_IS_PTR_NULL_EXIT(Component)

	Component->SetStaticMesh(Mesh.Get());
}

const FName NCsSkin::NData::NVisual::NStaticMesh::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NStaticMesh::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMesh
			{
				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetStaticMesh())
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetStaticMesh())
					return true;
				}

				void FImplSlice::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetStaticMesh(GetStaticMesh());
				}

				void FImplSlice::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return;

					CS_IS_PTR_NULL_EXIT(Component)

					Component->SetStaticMesh(GetStaticMesh());
				}
			}
		}
	}
}
