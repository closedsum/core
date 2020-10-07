// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Data/CsData_Weapon.h"

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NData
	{
		/**
		*/
		struct CSWP_API FEmuSlice : public IData
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

		public:

			FEmuSlice() :
				InterfaceMap(nullptr)
			{
			}
			~FEmuSlice(){}

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		public:

			FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map)
			{
				InterfaceMap = Map;
			}

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap
		};
	}
}