// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Range/CsDamageRange.h"
#pragma once

struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* Basic implementation of the interface: NCsDamage::NRange::IRange
		*/
		struct CSCORE_API FEmu : public IRange
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			float* MinRange;

			float* MaxRange;

		public:

			FEmu();
			~FEmu();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		// IRange
		#pragma region
		public:

			FORCEINLINE const float& GetMinRange() const
			{
				return *MinRange;
			}

			FORCEINLINE const float& GetMaxRange() const
			{
				return *MaxRange;
			}

		#pragma endregion IRange

		public:

			void SetMinRange(float* Value)
			{
				MinRange = Value;
			}

			void SetMaxValue(float* Value)
			{
				MaxRange = Value;
			}
		};
	}
}