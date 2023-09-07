// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Value/CsDamageValue.h"
#include "Value/Point/CsDamageValuePoint.h"
#include "Value/Types/CsGetDamageValueType.h"
#include "Value/Copy/CsDamageValue_Copy.h"
#include "Reset/CsReset.h"
// Container
#include "Containers/CsInterfaceMap.h"

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
		#define ValueType NCsDamage::NValue::IValue
		#define PointValueType NCsDamage::NValue::NPoint::IPoint
		#define CopyType NCsDamage::NValue::NCopy::ICopy

			/**
			* Basic implementation of the interface: NCsDamage::NValue::IValue
			*/
			struct CSDMG_API FImpl : public ValueType,
									 public PointValueType,
									 public ICsGetDamageValueType,
									 public CopyType,
									 public ICsReset
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap InterfaceMap;

				// PointValueType (NCsDamage::NValue::NPoint::IPoint)

				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

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

			// PointValueType (NCsDamage::NValue::NPoint::IPoint)
			#pragma region
			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)

			#pragma endregion PointValueType (NCsDamage::NValue::NPoint::IPoint)

			// ICsGetDamageValueType
			#pragma region
			public:

				FORCEINLINE const FECsDamageValue& GetDamageValueType() const { return NCsDamageValue::Point; }

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

		#undef ValueType
		#undef PointValueType
		#undef CopyType
		}
	}
}