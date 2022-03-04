// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Value/CsDamageValue.h"
#include "Value/Point/CsDamageValuePoint.h"

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
			struct CSDMG_API FProxy : public IValue,
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

				FProxy();
				~FProxy();

				FProxy(const FProxy&) = delete;
				FProxy& operator = (const FProxy&) = delete;

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