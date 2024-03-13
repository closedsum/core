// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Type
#include "Data/Types/CsData_GetBeamType.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsData_GetBeamTypeImplSlice.generated.h"

// NCsBeam::NData::NType::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsBeam, NData, NType, FImplSlice)

/**
* Represents a "slice" of data, ICsGetBeamType.
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_GetBeamTypeImplSlice
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsBeam|Data|Type")
	FECsBeam Type;

public:

	FCsData_GetBeamTypeImplSlice() :
		Type()
	{
	}

#define SliceType NCsBeam::NData::NType::FImplSlice

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

namespace NCsBeam
{
	namespace NData
	{
		namespace NType
		{
			/**
			* Represents a "slice" of data, ICsGetBeamType.
			* 
			* If members are set via points to an "owning" data, then
			* "Emulates" ICsData_GetBeamType by mimicking 
			* the interfaces and having pointers to the appropriate members. 
			* 
			* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
			* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
			*/
			struct CSBEAM_API FImplSlice final : public ICsData_GetBeamType
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
				that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// ICsData_GetBeamType

				CS_DECLARE_MEMBER_WITH_PROXY(BeamType, FECsBeam)

			public:

				FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ICsData_GetBeamType
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(BeamType)
				{
					CS_CTOR_SET_MEMBER_PROXY(BeamType);
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

			// ICsGetBeamType
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(BeamType, FECsBeam)

			#pragma endregion ICsGetBeamType

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsBeam::NData::NType::FImplSlice*>(Ptr);
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

			#undef ParamsType
			};
		}
	}
}