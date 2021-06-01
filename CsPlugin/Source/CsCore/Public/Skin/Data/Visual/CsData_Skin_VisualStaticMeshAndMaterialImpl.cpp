// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialImpl.h"

// Container
#include "Containers/CsInterfaceMap.h"

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
					Mesh(nullptr),
					Mesh_Emu(nullptr),
					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
					Materials(),
					Materials_Emu(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FImpl::Name);

					typedef NCsData::IData DataType;
					typedef NCsSkin::NData::NVisual::IVisual SkinDataType;
					typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinDataType;
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<SkinDataType>(static_cast<SkinDataType*>(this));
					InterfaceMap->Add<StaticMeshSkinDataType>(static_cast<StaticMeshSkinDataType*>(this));
					InterfaceMap->Add<MaterialSkinDataType>(static_cast<MaterialSkinDataType*>(this));

					Mesh_Emu = &Mesh;
					Materials_Emu = &Materials;
				}

				FImpl::~FImpl()
				{
					delete InterfaceMap;
				}
			}
		}
	}
}