// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Value/CsDamageValue.h"
#include "Value/Range/CsDamageValueRange.h"

struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			/**
			* Basic implementation of the interface: NCsDamage::NValue::IValue
			*/
			struct CSDMG_API FProxy : public IValue,
									  public IRange
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				float* MinValue;

				float* MaxValue;

			public:

				FProxy();
				~FProxy();

				FProxy(const FProxy&) = delete;
				FProxy& operator = (const FProxy&) = delete;

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// IValue
			#pragma region
			public:

			#pragma endregion IValue

			// IRange
			#pragma region
			public:

				FORCEINLINE const float& GetMinValue() const { return *MinValue; }
				FORCEINLINE const float& GetMaxValue() const { return *MaxValue; }

			#pragma endregion IRange

			public:

				void SetMinValue(float* InValue) { MinValue = InValue; }
				void SetMaxValue(float* InValue) { MaxValue = InValue; }
			};
		}
	}
}