// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterialImplSlice.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"

#define SliceType NCsSkin::NData::NVisual::NMaterial::FImplSlice

void FCsData_Skin_VisualMaterialImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetMaterials(Materials.GetPtr());
}

void FCsData_Skin_VisualMaterialImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetMaterials(Materials.Get());
}

#undef SliceType

bool FCsData_Skin_VisualMaterialImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Materials.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualMaterialImplSlice::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
{
	check(Materials.IsValidChecked(Context));

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Component, Materials.Get());
}

bool FCsData_Skin_VisualMaterialImplSlice::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Materials.IsValid(Context, Log))
		return false;

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials.Get(), Log);
}

const FName NCsSkin::NData::NVisual::NMaterial::FImplSlice::Name = FName("NCsSkin::NData::NVisual::NMaterial::FImplSlice");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					CS_IS_ARRAY_EMPTY_CHECKED(GetMaterials(), UMaterialInterface*)

					CS_IS_ARRAY_ANY_NULL_CHECKED(GetMaterials(), UMaterialInterface)
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_ARRAY_EMPTY(GetMaterials(), UMaterialInterface*)

					CS_IS_ARRAY_ANY_NULL(GetMaterials(), UMaterialInterface)
					return true;
				}

				void FImplSlice::SetChecked(const FString& Context, UPrimitiveComponent* Component) const
				{
					typedef NCsMaterial::FLibrary MaterialLibrary;

					MaterialLibrary::SetChecked(Context, Component, GetMaterials());
				}

				bool FImplSlice::SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					typedef NCsMaterial::FLibrary MaterialLibrary;

					return MaterialLibrary::SetSafe(Context, Component, GetMaterials(), Log);
				}
			}
		}
	}
}
