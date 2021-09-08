// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Data/CsData.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Skin/Data/Visual/SkeletalMesh/CsData_Skin_VisualSkeletalMesh.h"
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_SkeletalMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsData_Skin_VisualSkeletalMeshAndMaterialImpl.generated.h"

// NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NSkeletalMeshAndMaterial, FImpl)

class UStaticMeshComponent;

/**
* Represents an implementation of data which implement the interfaces:
* - DataType (NCsData::IData)
* - SkinDataType (NCsSkin::NData::NVisual::IVisual)
* - SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
* - MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_Skin_VisualSkeletalMeshAndMaterialImpl
{
	GENERATED_USTRUCT_BODY()

public:

// SkeletalMeshVisualDataType(NCsSkin::NData::NVisual::NSkeletalMesh::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsSkeletalMesh Mesh;

// MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsTArrayMaterialInterface Materials;

	FCsData_Skin_VisualSkeletalMeshAndMaterialImpl() :
		Mesh(),
		Materials()
	{
	}

#define ImplType NCsSkin::NData::NVisual::NSkeletalMeshAndMaterial::FImpl
	void CopyToImpl(ImplType* Impl);
	void CopyToImplAsValue(ImplType* Impl) const;
#undef ImplType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, USkeletalMeshComponent* Component) const;
	bool SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
};


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
				* If members are set via pointers to an "owning" data, then "Emulates":
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

					CS_DECLARE_MEMBER_WITH_PROXY(SkeletalMesh, USkeletalMesh*)

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

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(SkeletalMesh, USkeletalMesh)

				// SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)
				#pragma region

				#pragma endregion SkeletalMeshSkinDataType (NCsSkin::NData::NVisual::NSkeletalMesh::ISkeletalMesh)

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
					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { check(Value); Materials_Proxy = Value; }

				// MaterialSkinDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Proxy; }

				#pragma endregion MaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

					void SetChecked(const FString& Context, USkeletalMeshComponent* Component) const;
					bool SetSafe(const FString& Context, USkeletalMeshComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};

			#undef DataType
			#undef SkinDataType
			#undef SkeletalMeshSkinDataType
			#undef MaterialSkinDataType
			}
		}
	}
}