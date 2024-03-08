// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Type
#include "Managers/FX/CsTypes_FX.h"
// Data
#include "Data/CsDataTable.h"
#include "Data/Visual/Impact/CsData_Beam_VisualImpact.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsData_Beam_VisualImpactImplSlice.generated.h"


// NCsBeam::NData::NVisual::NImpact::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsBeam, NData, NVisual, NImpact, FImplSlice)

/**
* Represents a "slice" of data, ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_Beam_VisualImpactImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsDataTable ImpactFXs;

	FCsData_Beam_VisualImpactImplSlice() :
		ImpactFXs()
	{
	}

#define SliceType NCsBeam::NData::NVisual::NImpact::FImplSlice

	SliceType* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
	SliceType* AddSafeSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

private:

	SliceType* AddSafeSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
};

struct FCsInterfaceMap;
struct FCsFXImpact;

namespace NCsBeam
{
	namespace NData
	{
		namespace NVisual
		{
			namespace NImpact
			{
			#define VisualImpactDataType NCsBeam::NData::NVisual::NImpact::IImpact

				/**
				* Represents a "slice" of data, ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact).
				* 
				* If members are set via points to an "owning" data, then
				* "Emulates" ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact) by mimicking 
				* the interfaces and having pointers to the appropriate members. 
				* 
				* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
				* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
				*/
				struct CSBEAM_API FImplSlice final : public VisualImpactDataType
				{
				public:

					static const FName Name;

				private:
			
					// ICsGetInterfaceMap

					/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition) 
						that describe the data. */
					FCsInterfaceMap* InterfaceMap;

					// ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact)

					CS_DECLARE_MEMBER_WITH_PROXY(ImpactFXs, UDataTable*)

					TArray<FCsFXImpact*> ImpactFXRows;

				public:

					FImplSlice() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(ImpactFXs, nullptr),
						ImpactFXRows()
					{
						CS_CTOR_SET_MEMBER_PROXY(ImpactFXs);
					}

					~FImplSlice(){}

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				public:

					FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(ImpactFXs, UDataTable)

				// CollisionDataType (NCsBeam::NData::NCollision::ICollision)
				#pragma region
				public:

					const FCsFX& GetImpactFX(const EPhysicalSurface& SurfaceType) const;

				#pragma endregion CollisionDataType (NCsBeam::NData::NCollision::ICollision)

				public:

					void GenerateCached();

					static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsBeam::NData::NVisual::NImpact::FImplSlice*>(Ptr);
					}

					static FImplSlice* AddSafeSlice(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Object, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
				};

			#undef VisualImpactDataType
			}
		}
	}
}