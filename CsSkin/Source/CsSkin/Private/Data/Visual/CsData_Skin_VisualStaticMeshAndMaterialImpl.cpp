// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Components
#include "Components/StaticMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Skin_VisualStaticMeshAndMaterialImpl)

namespace NCsData_Skin_VisualStaticMeshAndMaterialImpl
{
	void FImpl::CopyToImpl(ThisType* This, ImplType* Impl)
	{
		Impl->SetStaticMesh(This->Mesh.GetPtr());
		Impl->SetMaterials(This->Materials.GetPtr());
	}

	void FImpl::CopyToImplAsValue(const ThisType* This, ImplType* Impl)
	{
		Impl->SetStaticMesh(This->Mesh.Get());
		Impl->SetMaterials(This->Materials.Get());
	}
}

bool FCsData_Skin_VisualStaticMeshAndMaterialImpl::IsValidChecked(const FString& Context) const
{
	// Check Mesh is Valid
	check(Mesh.IsValidChecked(Context));
	// Check Materials is Valid
	check(Materials.IsValidChecked(Context));
	return true;
}

bool FCsData_Skin_VisualStaticMeshAndMaterialImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
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
	CsMaterialLibrary::SetChecked(Context, Component, Materials.Get());
}

bool FCsData_Skin_VisualStaticMeshAndMaterialImpl::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return false;

	CS_IS_PTR_NULL(Component)

	Component->SetStaticMesh(Mesh.Get());
	return CsMaterialLibrary::SetSafe(Context, Component, Materials.Get());
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl);

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
					// CsSkinDataType (NCsSkin::NData::NVisual::IVisual)
					// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(StaticMesh, nullptr),
					// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Materials)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					InterfaceMap->Add<CsDataType>(static_cast<CsDataType*>(this));
					InterfaceMap->Add<CsSkinDataType>(static_cast<CsSkinDataType*>(this));
					InterfaceMap->Add<CsStaticMeshSkinDataType>(static_cast<CsStaticMeshSkinDataType*>(this));
					InterfaceMap->Add<CsMaterialSkinDataType>(static_cast<CsMaterialSkinDataType*>(this));

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

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
				{
					CS_IS_PTR_NULL(GetStaticMesh())
					return true;
				}

				void FImpl::SetChecked(const FString& Context, UStaticMeshComponent* Component) const
				{
					check(IsValidChecked(Context));

					CS_IS_PTR_NULL_CHECKED(Component);

					Component->SetStaticMesh(GetStaticMesh());
					CsMaterialLibrary::SetChecked(Context, Component, GetMaterials());
				}

				bool FImpl::SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) /*=&NCsSkin::FLog::Warning*/) const
				{
					if (!IsValid(Context, Log))
						return false;

					CS_IS_PTR_NULL(Component)

					Component->SetStaticMesh(GetStaticMesh());		
					return CsMaterialLibrary::SetSafe(Context, Component, GetMaterials());
				}
			}
		}
	}
}