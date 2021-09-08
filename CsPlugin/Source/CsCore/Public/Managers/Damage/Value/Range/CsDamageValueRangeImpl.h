// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			/**
			* Basic implementation of the interface: NCsDamage::NValue::IValue
			*/
			struct CSCORE_API FImpl : public IValue,
									  public IRange,
									  public ICsReset
			{
			public:

				static const FName Name;

			private:

				FCsInterfaceMap InterfaceMap;

			public:

				float MinValue;

				float MaxValue;

			public:

				FImpl();

				FImpl(const FImpl&) = delete;
				FImpl& operator = (const FImpl&) = delete;

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
				{
					return const_cast<FCsInterfaceMap*>(&InterfaceMap);
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
					return MinValue;
				}

				FORCEINLINE const float& GetMaxValue() const
				{
					return MaxValue;
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
}