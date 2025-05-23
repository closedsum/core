// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Interfaces
#include "Data/ICsData.h"
#include "Data/Visual/CsData_Skin_Visual.h"
#include "Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"
#include "Data/Visual/Material/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsData_Skin_VisualStaticMeshAndMaterial.generated.h"

struct FCsInterfaceMap;
class USkeletalMesh;
class UMaterialInterface;

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class CSSKIN_API UCsData_Skin_VisualStaticMeshAndMaterial : public UObject,
															public ICsData,
															public ICsData_Skin_Visual,
															public ICsData_Skin_VisualStaticMesh,
															public ICsData_Skin_VisualMaterial
{
	GENERATED_UCLASS_BODY()

public:

	static const FName Name;

private:

	CsDataType* DataProxy;

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

	FORCEINLINE CsDataType* _getIData() const { return DataProxy; }

	bool IsValid(const int32& LoadFlags);

	void Load(const int32& LoadFlags);

	void TopLoad();

	void Unload();

	bool IsLoaded() const;

#pragma endregion ICsData

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skin|Data|Visual")
	FCsStaticMesh Mesh;

// ICsData_Skin_VisualStaticMesh
#pragma region
public:

	FORCEINLINE UStaticMesh* GetStaticMesh() const { return Mesh.Get(); }

#pragma endregion ICsData_Skin_VisualStaticMesh

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Skin|Data|Visual")
	FCsTArrayMaterialInterface Materials;

// ICsData_Skin_VisualMaterial
#pragma region
public:

	FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return Materials.Get(); }

#pragma endregion ICsData_Skin_VisualMaterial
};