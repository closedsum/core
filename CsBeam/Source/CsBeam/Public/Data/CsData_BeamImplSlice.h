// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Log
#include "Utility/CsBeamLog.h"
// Data
#include "Data/CsData_Beam.h"

#include "CsData_BeamImplSlice.generated.h"

// NCsBeam::NData::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, FImplSlice)

/**
* Represents a "slice" of data, BeamDataType (NCsBeam::NData::IData).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSBEAM_API FCsData_BeamImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// BeamDataType (NCsBeam::NData::IData)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsBeam|Data", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	FCsData_BeamImplSlice() :
		LifeTime(0.0f)
	{
	}

	using SliceType = NCsBeam::NData::FImplSlice;

	SliceType* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
	SliceType* SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

private:

	SliceType* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsBeam
{
	namespace NData
	{
		/**
		* Represents a "slice" of data, BeamDataType (NCsBeam::NData::IData).
		* 
		* If members are set via points to an "owning" data, then
		* "Emulates" BeamDataType (NCsBeam::NData::IData) by mimicking 
		* the interfaces and having pointers to the appropriate members. 
		*
		* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
		* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
		*/
		struct CSBEAM_API FImplSlice final : public IData
		{
		public:

			static const FName Name;

		private:
			
			// ICsGetInterfaceMap

			/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition) 
				that describe the data. */
			FCsInterfaceMap* InterfaceMap;

			// BeamDataType (NCsBeam::NData::IData)

			CS_DECLARE_MEMBER_WITH_PROXY(LifeTime, float)

		public:

			FImplSlice() :
				InterfaceMap(nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(LifeTime, 0.0f)
			{
				CS_CTOR_SET_MEMBER_PROXY(LifeTime);
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

		// ICsData_Beam
		#pragma region
		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(LifeTime, float)

		#pragma endregion ICsData_Beam

		public:

			static void Deconstruct(void* Ptr)
			{
				delete static_cast<NCsBeam::NData::FImplSlice*>(Ptr);
			}

			static FImplSlice* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

		private:

			static FImplSlice* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& DataName, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) const;
		};
	}
}