// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"
#pragma once

struct FCsInterfaceMap;

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			/**
			* Basic implementation of the interface: NCsDamage::NValue::IValue
			*/
			struct CSCORE_API FEmu : public IValue,
									 public IPoint
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// IPoint

				float* Value;

			public:

				FEmu();
				~FEmu();

				FEmu(const FEmu&) = delete;
				FEmu& operator = (const FEmu&) = delete;

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// IValue
			#pragma region
			public:

			#pragma endregion IValue

			// IPoint
			#pragma region
			public:

				FORCEINLINE const float& GetValue() const { return *Value; }

			#pragma endregion IPoint

			public:

				void SetValue(float* InValue) { Value = InValue; }
			};
		}
	}
}