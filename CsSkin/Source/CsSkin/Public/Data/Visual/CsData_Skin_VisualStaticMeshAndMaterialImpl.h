// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Data/ICsData.h"
#include "Data/Visual/CsData_Skin_Visual.h"
#include "Data/Visual/StaticMesh/CsData_Skin_VisualStaticMesh.h"
#include "Data/Visual/Material/CsData_Skin_VisualMaterial.h"
// Types
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"
// Log
#include "Utility/CsSkinLog.h"

#include "CsData_Skin_VisualStaticMeshAndMaterialImpl.generated.h"

struct FCsData_Skin_VisualStaticMeshAndMaterialImpl;

// NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMeshAndMaterial, FImpl)

namespace NCsData_Skin_VisualStaticMeshAndMaterialImpl
{
	using ThisType = FCsData_Skin_VisualStaticMeshAndMaterialImpl;
	using ImplType = NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl;

	// Separate implementation to allow for clearer use of aliases
	struct CSSKIN_API FImpl
	{
	public:

		static void CopyToImpl(ThisType* This, ImplType* Impl);
		static void CopyToImplAsValue(const ThisType* This, ImplType* Impl);
	};
}

// NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NStaticMeshAndMaterial, FImpl)

class UStaticMeshComponent;

/**
* Represents an implementation of data which implement the interfaces:
* - DataType (NCsData::IData)
* - CsSkinDataType (NCsSkin::NData::NVisual::IVisual)
* - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualStaticMeshAndMaterialImpl
{
	GENERATED_USTRUCT_BODY()

public:

// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual")
	FCsStaticMesh Mesh;

// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual")
	FCsTArrayMaterialInterface Materials;

	FCsData_Skin_VisualStaticMeshAndMaterialImpl() :
		Mesh(),
		Materials()
	{
	}

	using ImplType = NCsSkin::NData::NVisual::NStaticMeshAndMaterial::FImpl;
	using _Impl = NCsData_Skin_VisualStaticMeshAndMaterialImpl::FImpl;

	FORCEINLINE void CopyToImpl(ImplType* Impl)					{ _Impl::CopyToImpl(this, Impl); }
	FORCEINLINE void CopyToImplAsValue(ImplType* Impl) const	{ _Impl::CopyToImplAsValue(this, Impl); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
	bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
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
				/**
				* Represents an implementation of data which implement the interfaces:
				* - CsDataType (NCsData::IData)
				* - CsSkinDataType (NCsSkin::NData::NVisual::IVisual)
				* - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				*
				* If members are set via pointers to an "owning" data, then "Emulates":
				* - CsDataType (NCsData::IData).
				* - CsSkinDataType (NCsSkin::NData::NVisual::IVisual)
				* - CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				* - CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				* by mimicking the interfaces and having pointers to the appropriate members.
				*
				* The idea behind "emulating" another object (usually a UObject) is to keep the code a cleaner and more readable.
				*/
				struct CSSKIN_API FImpl : public CsDataType,
										  public CsSkinDataType,
										  public CsStaticMeshSkinDataType,
										  public CsMaterialSkinDataType
				{
				public:

					static const FName Name;

				private:

					UObject* Outer;

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// CsSkinDataType (NCsSkin::NData::NVisual::IVisual)

					// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

					CS_DECLARE_MEMBER_WITH_PROXY(StaticMesh, UStaticMesh*)

					// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

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

				// CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)
				#pragma region

				#pragma endregion CsStaticMeshSkinDataType (NCsSkin::NData::NVisual::NStaticMesh::IStaticMesh)

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

				// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Proxy; }

				#pragma endregion CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

					void SetChecked(const FString& Context, UStaticMeshComponent* Component) const;
					bool SetSafe(const FString& Context, UStaticMeshComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
				};
			}
		}
	}
}