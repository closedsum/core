// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMeshImplSlice.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Components
#include "Components/SkeletalMeshComponent.h"

#define SliceType NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice

void FCsData_Skin_VisualSkeletalMeshImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetSkeletalMesh(Mesh.GetPtr());
}

void FCsData_Skin_VisualSkeletalMeshImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetSkeletalMesh(Mesh.Get());
}

#undef SliceType

bool FCsData_Skin_VisualSkeletalMeshImplSlice::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualSkeletalMeshImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualSkeletalMeshImplSlice::SetChecked(const FString& Context, USkeletalMeshComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetSkeletalMesh(Mesh.Get());
}

void FCsData_Skin_VisualSkeletalMeshImplSlice::SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return;

	CS_IS_PTR_NULL_EXIT(Component)

	Component->SetSkeletalMesh(Mesh.Get());
}

const FName NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NSkeletalMesh::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMesh
			{
				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetSkeletalMesh())
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetSkeletalMesh())
					return true;
				}

				void FImplSlice::SetChecked(const FString& Context, USkeletalMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetSkeletalMesh(GetSkeletalMesh());
				}

				void FImplSlice::SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return;

					CS_IS_PTR_NULL_EXIT(Component)

					Component->SetSkeletalMesh(GetSkeletalMesh());
				}
			}
		}
	}
}
