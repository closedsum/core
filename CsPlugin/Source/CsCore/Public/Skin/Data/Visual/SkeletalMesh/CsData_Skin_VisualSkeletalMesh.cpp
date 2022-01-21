// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"
#include "CsCore.h"

// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh::Name = FName("NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh");

const FName NCsSkin::NData::NVisual::NSkeletalMesh::FProxy::Name = FName("NCsSkin::NData::NVisual::NSkeletalMesh::FProxy");

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMesh
			{
				FProxy::FProxy() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ISkeletalMesh
					Mesh(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FProxy>(this);

					InterfaceMap->Add<ISkeletalMesh>(static_cast<ISkeletalMesh*>(this));
				}

				FProxy::~FProxy()
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