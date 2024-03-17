// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Macro/CsMacro_Namespace.h"
// Log
#include "Utility/CsLog.h"
// Data
#include "Data/Visual/CsData_Skin_Visual.h"

#include "CsData_Skin_VisualImplSlice.generated.h"

// NCsSkin::NData::NVisual::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkin, NData, NVisual, FImplSlice)

struct FCsInterfaceMap;
class ICsDeconstructInterfaceSliceMap;

/**
* Represents a "slice" of data, SkinDataType (NCsskin::NData::NVisual::IVisual).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSSKIN_API FCsData_Skin_VisualImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// SkinDataType (NCsskin::NData::NVisual::IVisual)

	FCsData_Skin_VisualImplSlice()
	{
	}

#define SliceType NCsSkin::NData::NVisual::FImplSlice

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	SliceType* AddSafeSliceAsValue(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, void(*Log)(const FString&) = &FCsLog::Warning) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;
class ICsDeconstructInterfaceSliceMap;

namespace NCsSkin
{
	namespace NData
	{
		namespace NVisual
		{
			/**
			* Represents a "slice" of data, SkinDataType (NCsskin::NData::NVisual::IVisual).
			* 
			* If members are set via points to an "owning" data, then
			* "Emulates" SkinDataType (NCsskin::NData::NVisual::IVisual) by mimicking 
			* the interfaces and having pointers to the appropriate members. 
			*
			* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
			* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
			*/
			struct CSSKIN_API FImplSlice final : public IVisual
			{
			public:

				static const FName Name;

			private:
			
				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Proxy Slices". That object acts as the hub for the separate objects (via composition) 
					that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// SkinDataType (NCsskin::NData::NVisual::IVisual)

			public:

				FImplSlice() :
					InterfaceMap(nullptr)
				{
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

			// SkinDataType (NCsskin::NData::NVisual::IVisual)
			#pragma region
			public:

			#pragma endregion SkinDataType (NCsskin::NData::NVisual::IVisual)

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsSkin::NData::NVisual::FImplSlice*>(Ptr);
				}

				static FImplSlice* AddSafeSlice(const FString& Context, FCsInterfaceMap* InterfaceMap, ICsDeconstructInterfaceSliceMap* DeconstructInterfaceSliceMap, UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
			};
		}
	}
}