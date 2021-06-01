// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMesh.h"
#include "Skin/Data/Visual/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

class UObject;
struct FCsInterfaceMap;
class UStaticMesh;
class UMaterialInterface;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NStaticMeshAndMaterial
			{
			#define DataType NCsData::IData
			#define SkinDataType IVisual
			#define StaticMeshSkinDataType NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh
			#define MaterialSkinDataType NCsSkin::NData::NVisual::NMaterial::IMaterial

				/**
				* Represents an implementation of data which implement the interfaces:
				* - DataType (NCsData::IData)
				* - SkinDataType (NCsSkin::NData::NVisual::IVisual)
				* - StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				* - MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				*
				* If members are set via points to an "owning" data, then "Emulates":
				* - DataType (NCsData::IData).
				* - SkinDataType (NCsSkin::NData::NVisual::IVisual)
				* - StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				* - MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				* by mimicking the interfaces and having pointers to the appropriate members.
				*
				* The idea behind "emulating" another object (usually a UObject) is to keep the code a cleaner and more readable.
				*/
				struct CSCORE_API FImpl : public DataType,
										  public SkinDataType,
										  public StaticMeshSkinDataType,
										  public MaterialSkinDataType
				{
				public:

					static const FName Name;

				private:

					UObject* Outer;

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// SkinDataType (NCsSkin::NData::NVisual::IVisual)

					// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

					UStaticMesh* Mesh;
					UStaticMesh** Mesh_Emu;

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

					FORCEINLINE void SetStaticMesh(UStaticMesh* Value)
					{
						Mesh = Value;
						Mesh_Emu = &Mesh;
					}
					FORCEINLINE void SetStaticMesh(UStaticMesh** Value) { Mesh_Emu = Value; }

				// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region

					FORCEINLINE UStaticMesh* GetStaticMesh() const { return *Mesh_Emu; }

				#pragma endregion StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

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
					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Emu = Value; }

				// MaterialSkinDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Emu; }

				#pragma endregion MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				};

			#undef DataType
			#undef SkinDataType
			#undef StaticMeshSkinDataType
			#undef MaterialSkinDataType
			}
		}
	}
}