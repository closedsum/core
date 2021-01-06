// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMesh.h"
#include "Skin/Data/Visual/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Types/CsTypes_Material.h"

#include "CsData_Skin_VisualStaticMeshAndMaterialImpl.generated.h"

struct FCsInterfaceMap;
class USkeletalMesh;
class UMaterialInterface;

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class CSCORE_API UCsData_Skin_VisualStaticMeshAndMaterialImpl : public UObject,
																public ICsData,
																public ICsData_Skin_Visual,
																public ICsData_Skin_VisualStaticMesh,
																public ICsData_Skin_VisualMaterial
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

#define DataType NCsData::IData

private:

	DataType* DataEmu;

// UObject Interface
#pragma region
public:

	virtual void PostLoad() override;

	virtual void BeginDestroy() override;

#pragma endregion UObject Interface

private:

	void Init();
	void Reset();

	FCsInterfaceMap* InterfaceMap;

	// ICsGetInterfaceMap
#pragma region
public:

	FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

#pragma endregion ICsGetInterfaceMap

protected:

	bool bLoaded;

	// ICsData
#pragma region
public:

	FORCEINLINE DataType* _getIData() const { return DataEmu; }

	bool IsValid(const int32& LoadFlags);

	void Load(const int32& LoadFlags);

	void Unload();

	bool IsLoaded() const;

#pragma endregion ICsData

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsStaticMesh Mesh;

// ICsData_Skin_VisualStaticMesh
#pragma region
public:

	FORCEINLINE UStaticMesh* GetStaticMesh() const { return Mesh.Get(); }

#pragma endregion ICsData_Skin_VisualStaticMesh

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsTArrayMaterialnterface Materials;

// ICsData_Skin_VisualMaterial
#pragma region
public:

	FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return Materials.Get(); }

#pragma endregion ICsData_Skin_VisualMaterial

#undef DataType
};