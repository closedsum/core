// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Managers/Damage/Value/Range/CsDamageValueRange.h"
#include "Managers/Damage/Value/Copy/CsDamageValue_Copy.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
		#define ValueType NCsDamage::NValue::IValue
		#define RangeValueType NCsDamage::NValue::NRange::IRange
		#define CopyType NCsDamage::NValue::NCopy::ICopy

			/**
			* Basic implementation of the interface: NCsDamage::NValue::IValue
			*/
			struct CSCORE_API FImpl : public ValueType,
									  public RangeValueType,
									  public CopyType,
									  public ICsReset
			{
			public:

				static const FName Name;

			private:

				FCsInterfaceMap InterfaceMap;

			public:

				CS_DECLARE_MEMBER_WITH_PROXY(MinValue, float)
				CS_DECLARE_MEMBER_WITH_PROXY(MaxValue, float)

			public:

				FImpl();

				FImpl(const FImpl&) = delete;
				FImpl& operator = (const FImpl&) = delete;

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return const_cast<FCsInterfaceMap*>(&InterfaceMap); }

			#pragma endregion ICsGetInterfaceMap

			// ValueType (NCsDamage::NValue::IValue)
			#pragma region
			public:

			#pragma endregion ValueType (NCsDamage::NValue::IValue)

			// RangeValueType (NCsDamage::NValue::NRange::IRange)
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinValue, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxValue, float)

			#pragma endregion RangeValueType (NCsDamage::NValue::NRange::IRange)

			// CopyType (NCsDamage::NValue::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const ValueType* From);

			#pragma endregion CopyType (NCsDamage::NValue::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset
			};

		#undef ValueType
		#undef RangeValueType
		#undef CopyType
		}
	}
}