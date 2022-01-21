// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "CsDmg.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Value/Types/CsGetDamageValueType.h"
#include "Managers/Damage/Value/Copy/CsDamageValue_Copy.h"

namespace NCsDamage
{
	namespace NValue
	{
		#define ValueType NCsDamage::NValue::IValue

		const FECsDamageValue& FLibrary::GetTypeChecked(const FString& Context, const ValueType* Value)
		{
			const ICsGetDamageValueType* GetDamageValueType = GetInterfaceChecked<ICsGetDamageValueType>(Context, Value);

			return GetDamageValueType->GetDamageValueType();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ValueType* From, ValueType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsDamage::NValue::NCopy::ICopy CopyType;

			CopyType* Copy = GetInterfaceChecked<CopyType>(Context, To);

			Copy->Copy(From);
			return true;
		}

		#undef ValueType
	}
}