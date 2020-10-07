// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#pragma once

struct FCsInterfaceMap;

namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

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

			private:

				typedef NCsDamage::NValue::IValue ValueType;

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

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
				{
					return InterfaceMap;
				}

			#pragma endregion ICsGetInterfaceMap

			// ICsData_Damage
			#pragma region
			public:

				FORCEINLINE const ValueType* GetValue() const
				{
					return Value;
				}

				FORCEINLINE const FECsDamageType& GetType() const
				{
					return const_cast<FECsDamageType&>(*Type);
				}

			#pragma endregion ICsData_Damage

			public:

				void SetValue(float* InValue);

				void SetType(FECsDamageType* InValue)
				{
					Type = InValue;
				}
			};

#undef DataType
		}
	}
}