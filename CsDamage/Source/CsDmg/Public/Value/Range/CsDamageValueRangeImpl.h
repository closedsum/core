// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Value/CsDamageValue.h"
#include "Value/Range/CsDamageValueRange.h"
#include "Value/Types/CsGetDamageValueType.h"
#include "Value/Copy/CsDamageValue_Copy.h"
#include "Reset/CsReset.h"
// Types
#include "CsMacro_Proxy.h"
#include "CsMacro_Cached.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_4(NCsDamage, NValue, NRange, NImpl, Impl)

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			namespace NImpl
			{
				using ValueType = NCsDamage::NValue::IValue;
				using RangeValueType = NCsDamage::NValue::NRange::IRange;
				using CopyType = NCsDamage::NValue::NCopy::ICopy;

				/**
				* Basic implementation of the interface: NCsDamage::NValue::IValue
				*/
				struct CSDMG_API FImpl : public ValueType,
										 public RangeValueType,
										 public ICsGetDamageValueType,
										 public CopyType,
										 public ICsReset
				{
				public:

					static const FName Name;

				private:

					CS_USING_CACHED_FUNCTION_NAME_NESTED_4(NCsDamage, NValue, NRange, NImpl, Impl);

				private:

					FCsInterfaceMap* InterfaceMap;
					FCsInterfaceMap InterfaceMap_Internal;

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

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

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

				// ICsGetDamageValueType
				#pragma region
				public:

					FORCEINLINE const FECsDamageValue& GetDamageValueType() const { return NCsDamageValue::Range; }

				#pragma endregion ICsGetDamageValueType

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
			}
		}
	}
}