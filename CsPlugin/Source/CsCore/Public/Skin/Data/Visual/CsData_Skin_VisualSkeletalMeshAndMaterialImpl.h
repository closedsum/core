// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/CsData_Skin_VisualSkeletalMesh.h"
#include "Skin/Data/Visual/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Types/CsTypes_Material.h"

#include "CsData_Skin_VisualSkeletalMeshAndMaterialImpl.generated.h"

// FEmu
#pragma region

struct FCsInterfaceMap;
class USkeletalMesh;
class UMaterialInterface;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NSkeletalMeshAndMaterial
			{
#define DataType NCsData::IData
#define SkinDataType IVisual
#define SkeletalMeshSkinDataType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
#define MaterialSkinDataType NCsSkin::NData::NVisual::NMaterial::IMaterial

				/**
				* "Emulates" UCsData_Skin_VisualSkeletalMeshAndMaterialImpl by mimicking the interfaces and having pointers to the appropriate
				* members. The idea behind this struct is to keep the code a cleaner and more readable.
				*/
				struct CSCORE_API FEmu : public DataType,
										 public SkinDataType,
										 public SkeletalMeshSkinDataType,
										 public MaterialSkinDataType
				{
				public:

					static const FName Name;

				private:

					UObject* Outer;

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)

					USkeletalMesh** Mesh;

					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

					TArray<UMaterialInterface*>* Materials;

				public:

					FEmu();
					~FEmu();

					FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE void SetSkeletalMesh(USkeletalMesh** Value) { Mesh = Value; }

				// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
				#pragma region

					FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return *Mesh; }

				#pragma endregion SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)

				public:

					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials = Value; }

				// MaterialSkinDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials; }

				#pragma endregion MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				};

#undef DataType
#undef SkinDataType
#undef SkeletalMeshSkinDataType
#undef MaterialSkinDataType
			}
		}
	}
}

#pragma endregion FEmu

struct FCsInterfaceMap;
class USkeletalMesh;
class UMaterialInterface;

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class CSCORE_API UCsData_Skin_VisualSkeletalMeshAndMaterialImpl : public UObject,
																  public ICsData,
																  public ICsData_Skin_Visual,
																  public ICsData_Skin_VisualSkeletalMesh,
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
	FCsSkeletalMesh Mesh;

// ICsData_Skin_VisualSkeletalMesh
#pragma region
public:

	FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return Mesh.Get(); }

#pragma endregion ICsData_Skin_VisualSkeletalMesh

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