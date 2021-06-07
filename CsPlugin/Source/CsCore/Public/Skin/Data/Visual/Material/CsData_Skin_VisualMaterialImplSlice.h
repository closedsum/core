// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Material/CsTypes_Material.h"
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"
// Data
#include "Skin/Data/Visual/Material/CsData_Skin_VisualMaterial.h"

#include "CsData_Skin_VisualMaterialImplSlice.generated.h"
#pragma once

// NCsSkin::NData::NVisual::NMaterial::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsSkin, NData, NVisual, NMaterial, FImplSlice)

class UPrimitiveComponent;
class UMaterialInterface;

/**
* Represents a "slice" of data, MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsData_Skin_VisualMaterialImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// MaterialVisualDataType(NCsSkin::NData::NVisual::NMaterial::IMaterial)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsTArrayMaterialInterface Materials;

	FCsData_Skin_VisualMaterialImplSlice() :
		Materials()
	{
	}

#define SliceType NCsSkin::NData::NVisual::NMaterial::FImplSlice
	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;
#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
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
			#define MaterialVisualDataType NCsSkin::NData::NVisual::NMaterial::IMaterial

				/**
				* Represents a "slice" of data, MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial).
				* 
				* If members are set via pointers to an "owning" data, then
				* "Emulates" MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial) by mimicking 
				* the interfaces and having pointers to the appropriate members.
				*
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSCORE_API FImplSlice final : public MaterialVisualDataType
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

					TArray<UMaterialInterface*> Materials;
					TArray<UMaterialInterface*>* Materials_Emu;

				public:

					FImplSlice() :
						InterfaceMap(nullptr),
						Materials(),
						Materials_Emu(nullptr)
					{
						Materials_Emu = &Materials;
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
						Materials_Emu = &Materials;
					}
					FORCEINLINE void SetMaterials(TArray<UMaterialInterface*>* Value) { Materials_Emu = Value; }

				// MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)
				#pragma region
				public:

					FORCEINLINE const TArray<UMaterialInterface*>& GetMaterials() const { return *Materials_Emu; }

				#pragma endregion MaterialVisualDataType (NCsSkin::NData::NVisual::NMaterial::IMaterial)

				public:

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsSkin::NData::NVisual::NMaterial::FImplSlice*>(Ptr);
					}

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

					void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;
					bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;
				};

			#undef MaterialVisualDataType
			}
		}
	}
}