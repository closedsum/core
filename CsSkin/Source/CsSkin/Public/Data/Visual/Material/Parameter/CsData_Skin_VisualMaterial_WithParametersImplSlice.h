// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Data
#include "Data/Visual/Material/Parameter/CsData_Skin_VisualMaterial_WithParameters.h"

#include "CsData_Skin_VisualMaterial_WithParametersImplSlice.generated.h"

// NCsSkin::NData::NVisual::NMaterial::NWithParameters::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsSkin, NData, NVisual, NMaterial, NWithParameters, FImplSlice)

class UPrimitiveComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, MaterialWithParamsVisualDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualMaterial_WithParametersImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// MaterialWithParamsVisualDataType(NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual|Material")
	TArray<FCsMaterialInterface_WithRangeParameters> Materials;

	FCsData_Skin_VisualMaterial_WithParametersImplSlice() :
		Materials()
	{
	}

#define SliceType NCsSkin::NData::NVisual::NMaterial::NWithParameters::FImplSlice

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &FCsLog::Warning) const;

#undef SliceType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class UPrimitiveComponent;
class UMaterialInstanceDynamic;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NMaterial
			{
				namespace NWithParameters
				{
				#define MaterialWithParamsVisualDataType NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters

					/**
					* Represents a "slice" of data, MaterialWithParamsVisualDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters).
					* 
					* If members are set via pointers to an "owning" data, then
					* "Emulates" MaterialWithParamsVisualDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters) by mimicking 
					* the interfaces and having pointers to the appropriate members.
					*
					* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
					* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
					*/
					struct CSSKIN_API FImplSlice final : public MaterialWithParamsVisualDataType
					{
					public:

						static const FName Name;

					#define MaterialType NCsMaterial::NInterface::FWithRangeParameters

					private:

						// ICsGetInterfaceMap

						/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition)
							that describe the data. */
						FCsInterfaceMap* InterfaceMap;

						// MaterialWithParamsVisualDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)

						CS_DECLARE_MEMBER_WITH_PROXY(Materials, TArray<MaterialType>)

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

						FORCEINLINE void SetMaterials(const TArray<MaterialType>& Value)
						{
							Materials.Reset(Value.Num());

							for (const MaterialType& M : Value)
							{
								MaterialType& Mat = Materials.AddDefaulted_GetRef();
								Mat.CopyAsValue(M);
							}
							Materials_Proxy = &Materials;
						}
						FORCEINLINE void SetMaterials(TArray<MaterialType>* Value) { Materials_Proxy = Value; }

					// MaterialWithParamsVisualDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)
					#pragma region
					public:

						FORCEINLINE const TArray<MaterialType>& GetMaterials() const { return *Materials_Proxy; }

					#pragma endregion MaterialWithParamsVisualDataType (NCsSkin::NData::NVisual::NMaterial::NWithParameters::IWithParameters)

					public:

						static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsSkin::NData::NVisual::NMaterial::NWithParameters::FImplSlice*>(Ptr);
						}

						static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

						void SetChecked(const FString& Context, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs) const;
						bool SetSafe(const FString& Context, UPrimitiveComponent* Component, TArray<UMaterialInstanceDynamic*>& OutMIDs, void(*Log)(const FString&) = &FCsLog::Warning) const;

					#undef MaterialType
					};

				#undef MaterialWithParamsVisualDataType
				}
			}
		}
	}
}