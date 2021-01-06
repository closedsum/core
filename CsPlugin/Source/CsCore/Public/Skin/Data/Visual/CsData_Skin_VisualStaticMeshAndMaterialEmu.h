// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/CsData_Skin_VisualStaticMesh.h"
#include "Skin/Data/Visual/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Types/CsTypes_Material.h"

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
				* "Emulates" an implementation by mimicking the interfaces and having pointers to the appropriate
				* members. The idea behind this struct is to keep the code a cleaner and more readable.
				*/
				struct CSCORE_API FEmu : public DataType,
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

					// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

					UStaticMesh* Mesh;

					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

					TArray<UMaterialInterface*>* Materials;

				public:

					FEmu();
					~FEmu();

					FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

					FORCEINLINE UObject* _getUObject() const { return Outer; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					FORCEINLINE void SetStaticMesh(UStaticMesh* Value) { Mesh = Value; }

				// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region

					FORCEINLINE UStaticMesh* GetStaticMesh() const { return Mesh; }

				#pragma endregion StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

				public:

					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials = Value; }

				// MaterialSkinDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials; }

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