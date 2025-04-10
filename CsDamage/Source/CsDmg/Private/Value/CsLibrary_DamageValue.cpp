// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/CsLibrary_DamageValue.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Value/Types/CsGetDamageValueType.h"
#include "Value/Copy/CsDamageValue_Copy.h"

namespace NCsDamage
{
	namespace NValue
	{
		namespace NLibrary
		{
			using CopyType = NCsDamage::NValue::NCopy::ICopy;

			const FECsDamageValue& FLibrary::GetTypeChecked(const FString& Context, const ValueType* Value)
			{
				const ICsGetDamageValueType* GetDamageValueType = GetInterfaceChecked<ICsGetDamageValueType>(Context, Value);

				return GetDamageValueType->GetDamageValueType();
			}

			bool FLibrary::CopyChecked(const FString& Context, const ValueType* From, ValueType* To)
			{
				CS_IS_PTR_NULL_CHECKED(From)

				CopyType* Copy = GetInterfaceChecked<CopyType>(Context, To);

				Copy->Copy(From);
				return true;
			}
		}
	}
}