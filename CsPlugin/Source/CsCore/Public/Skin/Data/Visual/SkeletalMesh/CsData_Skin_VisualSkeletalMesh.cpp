// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"
#include "CsCore.h"

// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh::Name = FName("NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh");

const FName NCsSkin::NData::NVisual::NSkeletalMesh::FEmu::Name = FName("NCsSkin::NData::NVisual::NSkeletalMesh::FEmu");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMesh
			{
				FEmu::FEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ISkeletalMesh
					Mesh(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FEmu::Name);

					InterfaceMap->Add<ISkeletalMesh>(static_cast<ISkeletalMesh*>(this));
				}

				FEmu::~FEmu()
				{
					delete InterfaceMap;
				}
			}
		}
	}
}


const FName ICsData_Skin_VisualSkeletalMesh::Name = FName("ICsData_Skin_VisualSkeletalMesh");

UCsData_Skin_VisualSkeletalMesh::UCsData_Skin_VisualSkeletalMesh(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}