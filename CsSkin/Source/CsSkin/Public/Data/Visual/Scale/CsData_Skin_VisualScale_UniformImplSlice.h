// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Data
#include "Data/Visual/Scale/CsData_Skin_VisualScale_Uniform.h"
// Log
#include "Utility/CsSkinLog.h"

#include "CsData_Skin_VisualScale_UniformImplSlice.generated.h"

// NCsSkin::NData::NVisual::NScale::NUniform::NImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsSkin, NData, NVisual, NScale, NUniform, FImplSlice)

class USceneComponent;
struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualScale_UniformImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skin|Data|Visual|Scale", meta = (UIMin = "0.001", ClampMin = "0.001"))
	float Scale;

	FCsData_Skin_VisualScale_UniformImplSlice() :
		Scale(1.0f)
	{
	}

	using SliceType = NCsSkin::NData::NVisual::NScale::NUniform::FImplSlice;

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

	void SetChecked(const FString& Context, USceneComponent* Component) const;
	bool SetSafe(const FString& Context, USceneComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
};

struct FCsInterfaceMap;
class USceneComponent;
class ICsDeconstructInterfaceSliceMap;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NScale
			{
				namespace NUniform
				{
					/**
					* Represents a "slice" of data, CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform).
					* 
					* If members are set via pointers to an "owning" data, then
					* "Emulates" CsUniformScaleSkinDataType (NNCsSkin::NData::NVisual::NScale::NUniform::IUniform) by mimicking 
					* the interfaces and having pointers to the appropriate members.
					*
					* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
					* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
					*/
					struct CSSKIN_API FImplSlice final : public CsUniformScaleSkinDataType
					{
					public:

						static const FName Name;

					private:

						// ICsGetInterfaceMap

						/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition)
							that describe the data. */
						FCsInterfaceMap* InterfaceMap;

						// CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)

						CS_DECLARE_MEMBER_WITH_PROXY(UniformScale, float)

					public:

						FImplSlice() :
							InterfaceMap(nullptr),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(UniformScale, 1.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(UniformScale);
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

					// CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)
					#pragma region
					public:

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(UniformScale, float)

					#pragma endregion CsUniformScaleSkinDataType (NCsSkin::NData::NVisual::NScale::NUniform::IUniform)

					public:

						static void Deconstruct(void* Ptr)
						{
							delete static_cast<NCsSkin::NData::NVisual::NScale::NUniform::FImplSlice*>(Ptr);
						}

						static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &NCsSkin::FLog::Warning);

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;

						void SetChecked(const FString& Context, USceneComponent* Component) const;
						bool SetSafe(const FString& Context, USceneComponent* Component, void(*Log)(const FString&) = &NCsSkin::FLog::Warning) const;
					};
				}
			}
		}
	}
}