// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsDamage
{
	namespace NModifier
	{
		#define ModifierType NCsDamage::NModifier::IModifier
		#define DataType NCsDamage::NData::IData
		#define ValueType NCsDamage::NValue::IValue
		#define RangeType NCsDamage::NRange::IRange

		bool FLibrary::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			CS_IS_PTR_NULL_CHECKED(To)
			return false;
		}

		bool FLibrary::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(Value)
			return false;
		}

		bool FLibrary::ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, RangeType* Range)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(Range)
			return false;	 
		}

		#undef ModifierType
		#undef DataType
		#undef ValueType
		#undef RangeType
	}
}