// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
// Types
#include "Material/CsTypes_Material.h"
#include "CsMacro_Misc.h"
// Log
#include "Utility/CsSkinLog.h"
// Data
#include "Data/Visual/Material/CsData_Skin_VisualMaterial.h"

#include "CsData_Skin_VisualMaterialImplSlice.generated.h"
#pragma once

// NCsSkin::NData::NVisual::NMaterial::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NMaterial, FImplSlice)

class UPrimitiveComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualMaterialImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual|Material")
	FCsTArrayMaterialInterface Materials;

	FCsData_Skin_VisualMaterialImplSlice() :
		Materials()
	{
	}

	using SliceType = NCsSkin::NData::NVisual::NMaterial::FImplSlice;

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UMaterialInterface;
class UPrimitiveComponent;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				/**
				* Represents a "slice" of data, CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial).
				* 
				* If members are set via pointers to an "owning" data, then
				* "Emulates" CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSSKIN_API FImplSlice final : public CsMaterialSkinDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

					CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<UMaterialInterface*>)

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Materials)
					{
						CS_CTOR_SET_MEMBER_PROXY(Materials);
					}

					~FImplSlice()
					{
					}

				public:

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				public:

					FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

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
				public:

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Proxy; }

				#pragma endregion CsMaterialSkinDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSkin::NData::NVisual::NMaterial::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &NCsSkin::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

					void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;
					bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
				};
			}
		}
	}
}