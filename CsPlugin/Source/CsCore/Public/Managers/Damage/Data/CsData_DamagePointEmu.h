// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#pragma once

struct FCsInterfaceMap;

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)

namespace NCsDamage
{
	namespace NData
	{
		namespace NPoint
		{
#define DataType NCsDamage::NData::IData

			/**
			*
			*/
			struct CSCORE_API FEmu : public DataType
			{
			public:

				static const FName Name;

			#define ValueType NCsDamage::NValue::IValue

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// ICsData_Damage

				ValueType* Value;

				FECsDamageType* Type;

			public:

				FEmu();
				~FEmu();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				void SetValue(float* InValue);

				void SetType(FECsDamageType* InValue) { Type = InValue; }

			// ICsData_Damage
			#pragma region
			public:

				FORCEINLINE const ValueType* GetValue() const { return Value; }
				FORCEINLINE const FECsDamageType& GetType() const { return const_cast<FECsDamageType&>(*Type); }

			#pragma endregion ICsData_Damage

			#undef ValueType
			};

#undef DataType
		}
	}
}