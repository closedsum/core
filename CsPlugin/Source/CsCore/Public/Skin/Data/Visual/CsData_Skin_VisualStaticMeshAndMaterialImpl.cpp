// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMeshAndMaterialImpl.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// DataTable
#include "Engine/DataTable.h"

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

const FName UCsData_Skin_VisualStaticMeshAndMaterialImpl::Name = FName("UCsData_Skin_VisualStaticMeshAndMaterialImpl");

UCsData_Skin_VisualStaticMeshAndMaterialImpl::UCsData_Skin_VisualStaticMeshAndMaterialImpl(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
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
		Init();
		bLoaded = false;
	}
}

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::BeginDestroy()
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

void UCsData_Skin_VisualStaticMeshAndMaterialImpl::Init()
{
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
		Emu->SetStaticMesh(&(Mesh.Mesh_Internal));
		// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
		Emu->SetMaterials(&(Materials.Materials_Internal));
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

#if WITH_EDITOR
	Init();
#endif // #if WITH_EDITOR
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