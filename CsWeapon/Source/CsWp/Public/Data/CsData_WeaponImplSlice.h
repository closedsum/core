// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
// Data
#include "Data/CsData_Weapon.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsData_WeaponImplSlice.generated.h"
#pragma once

// NCsWeapon::NData::FImplSlice
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, FImplSlice)

/**
* Represents a "slice" of data, WeaponDataType (NCsWeapon::NData::IData).
* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsData_WeaponImplSlice
{
	GENERATED_USTRUCT_BODY()

public:

// WeaponDataType (NCsWeapon::NData::IData)

	FCsData_WeaponImplSlice()
	{
	}

#define SliceType NCsWeapon::NData::FImplSlice

	SliceType* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
	SliceType* SafeConstructAsValue(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

private:

	SliceType* SafeConstruct_Internal(const FString& Context, const UObject* WorldContext, const FString& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;

public:

	void CopyToSlice(SliceType* Slice);
	void CopyToSliceAsValue(SliceType* Slice) const;

#undef SliceType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NData
	{
		/**
		* Represents a "slice" of data, WeaponDataType (NCsWeapon::NData::IData).
		*
		* If members are set via points to an "owning" data, then
		* "Emulates" WeaponDataType (NCsWeapon::NData::IData) by mimicking
		* the interfaces and having pointers to the appropriate members.
		*
		* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
		* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
		*/
		struct CSWP_API FImplSlice : public IData
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			/** Pointer to the "root" object for all "Impl Slices". That object acts as the hub for the separate objects (via composition)
				that describe the data. */
			FCsInterfaceMap* InterfaceMap;

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

		public:

			static void Deconstruct(void* Ptr)
			{
				delete static_cast<NCsWeapon::NData::FImplSlice*>(Ptr);
			}

			static FImplSlice* SafeConstruct(const FString& Context, const UObject* WorldContext, const FString& DataName, UObject* Object, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
		};
	}
}