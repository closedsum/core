// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Range/CsDamageRange.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* Basic implementation of the interface: NCsDamage::NRange::IRange
		*/
		struct CSCORE_API FImpl : public IRange,
								  public ICsReset
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap InterfaceMap;

		public:

			float MinRange;

			float MaxRange;

		public:

			FImpl();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return const_cast<FCsInterfaceMap*>(&InterfaceMap);
			}

		#pragma endregion ICsGetInterfaceMap

		// IRange
		#pragma region
		public:

			FORCEINLINE const float& GetMinRange() const
			{
				return MinRange;
			}

			FORCEINLINE const float& GetMaxRange() const
			{
				return MaxRange;
			}

		#pragma endregion IRange

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset
		};
	}
}