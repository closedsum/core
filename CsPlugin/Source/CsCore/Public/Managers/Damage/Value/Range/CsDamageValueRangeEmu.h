// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"
#pragma once

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
			struct CSCORE_API FEmu : public IValue,
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

				FEmu();
				~FEmu();

				FEmu(const FEmu&) = delete;
				FEmu& operator = (const FEmu&) = delete;

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
				{
					return InterfaceMap;
				}

			#pragma endregion ICsGetInterfaceMap

			// IValue
			#pragma region
			public:

			#pragma endregion IValue

			// IRange
			#pragma region
			public:

				FORCEINLINE const float& GetMinValue() const
				{
					return *MinValue;
				}

				FORCEINLINE const float& GetMaxValue() const
				{
					return *MaxValue;
				}

			#pragma endregion IRange

			public:

				void SetMinValue(float* InValue)
				{
					MinValue = InValue;
				}

				void SetMaxValue(float* InValue)
				{
					MaxValue = InValue;
				}
			};
		}
	}
}