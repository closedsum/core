// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Data/ICsData.h"
#include "Managers/Damage/Data/CsData_Damage.h"

struct FCsInterfaceMap;

// (ValueType) NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
			namespace  NProxy
			{
				/**
				* "Emulates" an object by mimicking the interfaces and having pointers to the appropriate
				* members. The idea behind this struct is to keep the code a cleaner and more readable.
				*/
				struct CSDMG_API FProxy : public CsDataType,
										  public CsDamageDataType
				{
				public:

					static const FName Name;

				private:

					using ValueType = NCsDamage::NValue::IValue;

				private:

					UObject* Outer;

				// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

				// CsDamageDataType (NCsDamage::NData::IData)

					ValueType* Value;

					FECsDamageType* Type;

				public:

					FProxy();
					~FProxy();

					FORCEINLINE void SetOuter(UObject* InOuter) { Outer = InOuter; }

					FORCEINLINE UObject* _getUObject() const { return Outer; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					void SetValue(float* InValue);
					void SetType(FECsDamageType* InValue) { Type = InValue; }

				// DamageDataType (NCsDamage::NData::IData)
				#pragma region
				public:

					FORCEINLINE const ValueType* GetValue() const { return Value; }
					FORCEINLINE const FECsDamageType& GetType() const { return const_cast<FECsDamageType&>(*Type); }

				#pragma endregion DamageDataType (NCsDamage::NData::IData)
				};
			}
		}
	}
}