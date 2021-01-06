// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialEmu.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FEmu::Name = FName("NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FEmu");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMeshAndMaterial
			{
				FEmu::FEmu() :
					Outer(nullptr),
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
					Mesh(nullptr),
					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
					Materials(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FEmu::Name);

					typedef NCsData::IData DataType;
					typedef NCsSkin::NData::NVisual::IVisual SkinDataType;
					typedef NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh StaticMeshSkinDataType;
					typedef NCsSkin::NData::NVisual::NMaterial::IMaterial MaterialSkinDataType;

					InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
					InterfaceMap->Add<SkinDataType>(static_cast<SkinDataType*>(this));
					InterfaceMap->Add<StaticMeshSkinDataType>(static_cast<StaticMeshSkinDataType*>(this));
					InterfaceMap->Add<MaterialSkinDataType>(static_cast<MaterialSkinDataType*>(this));
				}

				FEmu::~FEmu()
				{
					delete InterfaceMap;
				}
			}
		}
	}
}