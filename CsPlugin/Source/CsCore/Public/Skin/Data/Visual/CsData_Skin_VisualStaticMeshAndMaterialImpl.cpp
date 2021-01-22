// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialImpl.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// DataTable
#include "Engine/DataTable.h"
// Emu
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialEmu.h"

const FName UCsData_Skin_VisualStaticMeshAndMaterialImpl::Name = FName("UCsData_Skin_VisualStaticMeshAndMaterialImpl");

UCsData_Skin_VisualStaticMeshAndMaterialImpl::UCsData_Skin_VisualStaticMeshAndMaterialImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	DataEmu(nullptr),
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsData
	bLoaded(false),
	// ICsData_Skin_VisualStaticMesh
	Mesh(),
	// ICsData_Skin_VisualMaterial
	Materials()
{
}

// UObject Interface
#pragma region

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_Skin_VisualStaticMeshAndMaterialImpl>())
	{
		//Init();
		bLoaded = false;
	}
}

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::BeginDestroy()
{
	Super::BeginDestroy();

	Reset();
}

#pragma endregion UObject Interface

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::Init()
{
	Reset();

	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRootName(UCsData_Skin_VisualStaticMeshAndMaterialImpl::Name);

		typedef ICsData DataType;
		typedef ICsData_Skin_Visual SkinDataType;
		typedef ICsData_Skin_VisualStaticMesh StaticMeshSkinDataType;
		typedef ICsData_Skin_VisualMaterial MaterialSkinDataType;

		InterfaceMap->Add<DataType>(Cast<DataType>(this));
		InterfaceMap->Add<SkinDataType>(Cast<SkinDataType>(this));
		InterfaceMap->Add<StaticMeshSkinDataType>(Cast<StaticMeshSkinDataType>(this));
		InterfaceMap->Add<MaterialSkinDataType>(Cast<MaterialSkinDataType>(this));
	}
	if (!DataEmu)
	{
		typedef NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FEmu DataEmuType;

		DataEmu = new DataEmuType();

		DataEmuType* Emu = (DataEmuType*)DataEmu;
		Emu->SetOuter(this);
		// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
		Emu->SetStaticMesh(Mesh.GetPtr());
		// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
		Emu->SetMaterials(Materials.GetPtr());
	}
}

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::Reset()
{
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

// ICsData
#pragma region

bool UCsData_Skin_VisualStaticMeshAndMaterialImpl::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

	Init();

	bLoaded = true;
}

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::Unload()
{

}

bool UCsData_Skin_VisualStaticMeshAndMaterialImpl::IsLoaded() const
{
	return bLoaded;
}

#pragma endregion ICsData