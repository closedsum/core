// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

class UObject;
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
			#define SkinDataType NCsSkin::NData::NVisual::IVisual
			#define SkeletalMeshSkinDataType NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh
			#define MaterialSkinDataType NCsSkin::NData::NVisual::NMaterial::IMaterial

				/**
				* Represents an implementation of data which implement the interfaces: 
				* - DataType (NCsData::IData)
				* - SkinDataType (NCsSkin::NData::NVisual::IVisual)
				* - SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
				* - MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				* 
				* If members are set via points to an "owning" data, then "Emulates":
				* - DataType (NCsData::IData).
				* - SkinDataType (NCsSkin::NData::NVisual::IVisual)
				* - SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
				* - MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				* by mimicking the interfaces and having pointers to the appropriate members. 
				* 
				* The idea behind "emulating" another object (usually a UObject) is to keep the code a cleaner and more readable.
				*/
				struct CSCORE_API FImpl : public DataType,
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

					// SkinDataType (NCsSkin::NData::NVisual::IVisual)
					
					// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)

					USkeletalMesh* Mesh;
					USkeletalMesh** Mesh_Emu;

					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

					TArray<UMaterialInterface*> Materials;
					TArray<UMaterialInterface*>* Materials_Emu;

				public:

					FImpl();
					~FImpl();

					FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

					FORCEINLINE UObject* _getUObject() const { return Outer; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE void SetSkeletalMesh(USkeletalMesh* Value)
					{
						Mesh = Value;
						Mesh_Emu = &Mesh;
					}
					FORCEINLINE void SetSkeletalMesh(USkeletalMesh** Value) { check(Value); Mesh_Emu = Value; }

				// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
				#pragma region

					FORCEINLINE USkeletalMesh* GetSkeletalMesh() const { return *Mesh_Emu; }

				#pragma endregion SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)

				public:

					FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& Value)
					{
						Materials.Reset(Value.Num());

						for (UMaterialInterface* M : Value)
						{
							Materials.Add(M);
						}
						Materials_Emu = &Materials;
					}
					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { check(Value); Materials_Emu = Value; }

				// MaterialSkinDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Emu; }

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