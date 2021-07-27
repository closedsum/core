// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsData_Skin_VisualStaticMeshAndMaterialImpl.generated.h"
#pragma once

// NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMeshAndMaterial, FImpl)

class UStaticMeshComponent;

/**
* Represents an implementation of data which implement the interfaces:
* - DataType (NCsData::IData)
* - SkinDataType (NCsSkin::NData::NVisual::IVisual)
* - StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
* - MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_Skin_VisualStaticMeshAndMaterialImpl
{
	GENERATED_USTRUCT_BODY()

public:

// StaticMeshVisualDataType(NCsSkin::NData::NVisual::NSkeletalMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsStaticMesh Mesh;

// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsTArrayMaterialInterface Materials;

	FCsData_Skin_VisualStaticMeshAndMaterialImpl() :
		Mesh(),
		Materials()
	{
	}

#define ImplType NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl
	void CopyToImpl(ImplType* Impl);
	void CopyToImplAsValue(ImplType* Impl) const;
#undef ImplType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
	bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

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
				* If members are set via pointers to an "owning" data, then "Emulates":
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

					CS_DECLARE_MEMBER_WITH_PROXY(StaticMesh, UStaticMesh*)

					// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

					CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)

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

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(StaticMesh, UStaticMesh)

				// StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region

				#pragma endregion StaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

				public:

					FORCEINLINE void SetMaterials(const TArray<UMaterialInterface*>& Value)
					{
						Materials.Reset(Value.Num());

						for (UMaterialInterface* M : Value)
						{
							Materials.Add(M);
						}
						Materials_Proxy = &Materials;
					}
					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Proxy = Value; }

				// MaterialSkinDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Proxy; }

				#pragma endregion MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

					void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
					bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};

			#undef DataType
			#undef SkinDataType
			#undef StaticMeshSkinDataType
			#undef MaterialSkinDataType
			}
		}
	}
}