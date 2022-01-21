// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Skin/Data/Visual/CsData_Skin_VisualSkeletalMeshAndMaterial.h"
#include "CsCore.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// DataTable
#include "Engine/DataTable.h"
// Proxy
#include "Skin/Data/Visual/CsData_Skin_VisualSkeletalMeshAndMaterialImpl.h"

const FName UCsData_Skin_VisualSkeletalMeshAndMaterial::Name = FName("UCsData_Skin_VisualSkeletalMeshAndMaterial");

UCsData_Skin_VisualSkeletalMeshAndMaterial::UCsData_Skin_VisualSkeletalMeshAndMaterial(const FObjectInitializer& ObjectInitializer)
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

void UCsData_Skin_VisualSkeletalMeshAndMaterial::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_Skin_VisualSkeletalMeshAndMaterial>())
	{
		bLoaded = false;
	}
}

void UCsData_Skin_VisualSkeletalMeshAndMaterial::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	if (DataProxy)
	{
		delete DataProxy;
		DataProxy = nullptr;
	}
}

#pragma endregion UObject Interface

void UCsData_Skin_VisualSkeletalMeshAndMaterial::Init()
{
	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRoot<UCsData_Skin_VisualSkeletalMeshAndMaterial>(this);

		typedef ICsData DataType;
		typedef ICsData_Skin_Visual SkinDataType;
		typedef ICsData_Skin_VisualSkeletalMesh SkeletalMeshSkinDataType;
		typedef ICsData_Skin_VisualMaterial MaterialSkinDataType;

		InterfaceMap->Add<DataType>(Cast<DataType>(this));
		InterfaceMap->Add<SkinDataType>(Cast<SkinDataType>(this));
		InterfaceMap->Add<SkeletalMeshSkinDataType>(Cast<SkeletalMeshSkinDataType>(this));
		InterfaceMap->Add<MaterialSkinDataType>(Cast<MaterialSkinDataType>(this));
	}
	if (!DataProxy)
	{
		typedef NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FImpl DataProxyType;

		DataProxy = new DataProxyType();

		DataProxyType* Proxy = (DataProxyType*)DataProxy;
		Proxy->SetOuter(this);
		// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
		Proxy->SetSkeletalMesh(Mesh.GetPtr());
		// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
		Proxy->SetMaterials(Materials.GetPtr());
	}
}

// ICsData
#pragma region

bool UCsData_Skin_VisualSkeletalMeshAndMaterial::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_Skin_VisualSkeletalMeshAndMaterial::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

	Init();

	bLoaded = true;
}

void UCsData_Skin_VisualSkeletalMeshAndMaterial::Unload()
{

}

bool UCsData_Skin_VisualSkeletalMeshAndMaterial::IsLoaded() const
{
#if WITH_EDITOR
	return false;
#else
	return bLoaded;
#endif // #if WITH_EDITOR
}

#pragma endregion ICsData