// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"

// Types
#include "CsMacro_Interface.h"
// Containers
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_Skin_VisualSkeletalMesh)

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh);
CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsSkin::NData::NVisual::NSkeletalMesh::FProxy);

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

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(ICsData_Skin_VisualSkeletalMesh);

UCsData_Skin_VisualSkeletalMesh::UCsData_Skin_VisualSkeletalMesh(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}