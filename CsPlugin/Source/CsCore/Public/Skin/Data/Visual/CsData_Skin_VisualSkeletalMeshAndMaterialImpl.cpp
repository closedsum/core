// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualSkeletalMeshAndMaterialImpl.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// DataTable
#include "Engine/DataTable.h"
// Emu
#include "Skin/Data/Visual/CsData_Skin_VisualSkeletalMeshAndMaterialEmu.h"

const FName UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::Name = FName("UCsData_Skin_VisualSkeletalMeshAndMaterialImpl");

UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::UCsData_Skin_VisualSkeletalMeshAndMaterialImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsData
	bLoaded(false),
	// ICsData_Skin_VisualSkeletalMesh
	Mesh(),
	// ICsData_Skin_VisualMaterial
	Materials()
{
}

// UObject Interface
#pragma region

void UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_Skin_VisualSkeletalMeshAndMaterialImpl>())
	{
		Init();
		bLoaded = false;
	}
}

void UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	if (DataEmu)
	{
		delete DataEmu;
		DataEmu = nullptr;
	}
}

#pragma endregion UObject Interface

void UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::Init()
{
	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRootName(UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::Name);

		typedef ICsData DataType;
		typedef ICsData_Skin_Visual SkinDataType;
		typedef ICsData_Skin_VisualSkeletalMesh SkeletalMeshSkinDataType;
		typedef ICsData_Skin_VisualMaterial MaterialSkinDataType;

		InterfaceMap->Add<DataType>(Cast<DataType>(this));
		InterfaceMap->Add<SkinDataType>(Cast<SkinDataType>(this));
		InterfaceMap->Add<SkeletalMeshSkinDataType>(Cast<SkeletalMeshSkinDataType>(this));
		InterfaceMap->Add<MaterialSkinDataType>(Cast<MaterialSkinDataType>(this));
	}
	if (!DataEmu)
	{
		typedef NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FEmu DataEmuType;

		DataEmu = new DataEmuType();

		DataEmuType* Emu = (DataEmuType*)DataEmu;
		Emu->SetOuter(this);
		// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
		Emu->SetSkeletalMesh(Mesh.GetPtr());
		// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
		Emu->SetMaterials(Materials.GetPtr());
	}
}

// ICsData
#pragma region

bool UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

#if WITH_EDITOR
	Init();
#endif // #if WITH_EDITOR
	bLoaded = true;
}

void UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::Unload()
{

}

bool UCsData_Skin_VisualSkeletalMeshAndMaterialImpl::IsLoaded() const
{
	return bLoaded;
}

#pragma endregion ICsData