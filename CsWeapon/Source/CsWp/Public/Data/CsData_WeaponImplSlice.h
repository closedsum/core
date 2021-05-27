// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_Weapon.h"

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

			/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
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
		};
	}
}