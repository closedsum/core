// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialImpl.h"

// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Components
#include "Components/StaticMeshComponent.h"

#define ImplType NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl

void FCsData_Skin_VisualStaticMeshAndMaterialImpl::CopyToImpl(ImplType* Impl)
{
	Impl->SetStaticMesh(Mesh.GetPtr());
	Impl->SetMaterials(Materials.GetPtr());
}

void FCsData_Skin_VisualStaticMeshAndMaterialImpl::CopyToImplAsValue(ImplType* Impl) const
{
	Impl->SetStaticMesh(Mesh.Get());
	Impl->SetMaterials(Materials.Get());
}

#undef ImplType

bool FCsData_Skin_VisualStaticMeshAndMaterialImpl::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	check(Materials.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualStaticMeshAndMaterialImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	// Check Mesh is Valid
	if (!Mesh.IsValid(Context, Log))
		return false;
	// Check Materials is Valid
	if (!Materials.IsValid(Context, Log))
		return false;
	return true;
}

void FCsData_Skin_VisualStaticMeshAndMaterialImpl::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
{
	check(IsValidChecked(Context));

	CS_IS_PTR_NULL_CHECKED(Component);

	Component->SetStaticMesh(Mesh.Get());

	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::SetChecked(Context, Component, Materials.Get());
}

bool FCsData_Skin_VisualStaticMeshAndMaterialImpl::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	Component->SetStaticMesh(Mesh.Get());

	typedef NCsMaterial::FLibrary MaterialLibrary;

	return MaterialLibrary::SetSafe(Context, Component, Materials.Get());
}

const FName NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl::Name = FName("NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMeshAndMaterial
			{
				FImpl::FImpl() :
					Outer(nullptr),
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// SkinDataType (NCsSkin::NData::NVisual::IVisual)
					// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(StaticMesh, nullptr),
					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Materials)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsData::IData DataType;
					typedef NCsSkin::NData::NVisual::IVisual SkinDataType;
					typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinDataType;
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<SkinDataType>(static_cast<SkinDataType*>(this));
					InterfaceMap->Add<StaticMeshSkinDataType>(static_cast<StaticMeshSkinDataType*>(this));
					InterfaceMap->Add<MaterialSkinDataType>(static_cast<MaterialSkinDataType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(StaticMesh);
					CS_CTOR_SET_MEMBER_PROXY(Materials);
				}

				FImpl::~FImpl()
				{
					delete InterfaceMap;
				}

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					CS_IS_PTR_NULL_CHECKED(GetStaticMesh())
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetStaticMesh())
					return true;
				}

				void FImpl::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetStaticMesh(GetStaticMesh());

					typedef NCsMaterial::FLibrary MaterialLibrary;

					MaterialLibrary::SetChecked(Context, Component, GetMaterials());
				}

				bool FImpl::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return false;

					CS_IS_PTR_NULL(Component)

					Component->SetStaticMesh(GetStaticMesh());
					
					typedef NCsMaterial::FLibrary MaterialLibrary;

					return MaterialLibrary::SetSafe(Context, Component, GetMaterials());
				}
			}
		}
	}
}