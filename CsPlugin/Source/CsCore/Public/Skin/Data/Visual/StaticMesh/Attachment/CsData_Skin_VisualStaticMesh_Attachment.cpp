// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Skin/Data/Visual/StaticMesh/Attachment/CsData_Skin_VisualStaticMesh_Attachment.h"
#include "CsCore.h"

const FName NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment::Name = FName("NCsSkin::NData::NVisual::NStaticMesh::NAttachment::IAttachment");

const FName ICsData_Skin_VisualStaticMesh_Attachment::Name = FName("ICsData_Skin_VisualStaticMesh_Attachment");

UCsData_Skin_VisualStaticMesh_Attachment::UCsData_Skin_VisualStaticMesh_Attachment(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}