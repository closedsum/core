// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Managers/Damage/Range/CsDamageRange.h"

struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* Basic implementation of the interface: NCsDamage::NRange::IRange
		*/
		struct CSDMG_API FProxy : public IRange
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

			FProxy();
			~FProxy();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// IRange
		#pragma region
		public:

			FORCEINLINE const float& GetMinRange() const { return *MinRange; }
			FORCEINLINE const float& GetMaxRange() const { return *MaxRange; }

		#pragma endregion IRange

		public:

			void SetMinRange(float* Value) { MinRange = Value; }
			void SetMaxValue(float* Value) { MaxRange = Value; }
		};
	}
}