// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsData_Skin_VisualSkeletalMeshAndMaterialImpl.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Components
#include "Components/SkeletalMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Skin_VisualSkeletalMeshAndMaterialImpl)

#define ImplType NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FImpl

void FCsData_Skin_VisualSkeletalMeshAndMaterialImpl::CopyToImpl(ImplType* Impl)
{
	Impl->SetSkeletalMesh(Mesh.GetPtr());
	Impl->SetMaterials(Materials.GetPtr());
}

void FCsData_Skin_VisualSkeletalMeshAndMaterialImpl::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetSkeletalMesh(Mesh.Get());
	Impl->SetMaterials(Materials.Get());
}

#undef ImplType

bool FCsData_Skin_VisualSkeletalMeshAndMaterialImpl::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	check(Materials.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualSkeletalMeshAndMaterialImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
{
	// Check Mesh is Valid
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Materials is Valid
	if (!Materials.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualSkeletalMeshAndMaterialImpl::SetChecked(const FString& Context, USkeletalMeshComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetSkeletalMesh(Mesh.Get());

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Component, Materials.Get());
}

bool FCsData_Skin_VisualSkeletalMeshAndMaterialImpl::SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	Component->SetSkeletalMesh(Mesh.Get());

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials.Get());
}

const FName NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FImpl::Name = FName("NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FImpl");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMeshAndMaterial
			{
				FImpl::FImpl() :
					Outer(nullptr),
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// SkinDataType (NCsSkin::NData::NVisual::IVisual)
					// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(SkeletalMesh, nullptr),
					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Materials)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsData::IData DataType;
					typedef NCsSkin::NData::NVisual::IVisual SkinDataType;
					typedef NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh SkeletalMeshSkinDataType;
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<SkinDataType>(static_cast<SkinDataType*>(this));
					InterfaceMap->Add<SkeletalMeshSkinDataType>(static_cast<SkeletalMeshSkinDataType*>(this));
					InterfaceMap->Add<MaterialSkinDataType>(static_cast<MaterialSkinDataType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(SkeletalMesh);
					CS_CTOR_SET_MEMBER_PROXY(Materials);
				}

				FImpl::~FImpl()
				{
					delete InterfaceMap;
				}

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetSkeletalMesh())
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetSkeletalMesh())
					return true;
				}

				void FImpl::SetChecked(const FString& Context, USkeletalMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetSkeletalMesh(GetSkeletalMesh());

					typedef NCsMaterial::FLibrary MaterialLibrary;

					MaterialLibrary::SetChecked(Context, Component, GetMaterials());
				}

				bool FImpl::SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return false;

					CS_IS_PTR_NULL(Component)

					Component->SetSkeletalMesh(GetSkeletalMesh());
					
					typedef NCsMaterial::FLibrary MaterialLibrary;

					return MaterialLibrary::SetSafe(Context, Component, GetMaterials());
				}
			}
		}
	}
}