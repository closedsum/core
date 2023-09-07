// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/Range/CsDamageValueRangeImpl.h"
#include "CsDmg.h"

// Library
#include "Value/CsLibrary_DamageValue.h"

const FName NCsDamage::NValue::NRange::FImpl::Name = FName("NCsDamage::NValue::NRange::FImpl");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			namespace NImpl
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NValue::NRange::FImpl, Copy);
					}
				}
			}

			FImpl::FImpl() :
				InterfaceMap(),
				// RangeValueType (NCsDamage::NValue::NRange::IRange)
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MinValue, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxValue, 0.0f)
			{
				InterfaceMap.SetRoot<FImpl>(this);

				typedef NCsDamage::NValue::IValue ValueType;
				typedef NCsDamage::NValue::NRange::IRange RangeValueType;
				typedef NCsDamage::NValue::NCopy::ICopy CopyType;

				InterfaceMap.Add<ValueType>(static_cast<ValueType*>(this));
				InterfaceMap.Add<RangeValueType>(static_cast<RangeValueType*>(this));
				InterfaceMap.Add<ICsGetDamageValueType>(static_cast<ICsGetDamageValueType*>(this));
				InterfaceMap.Add<CopyType>(static_cast<CopyType*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));

				CS_CTOR_SET_MEMBER_PROXY(MinValue);
				CS_CTOR_SET_MEMBER_PROXY(MaxValue);
			}

			// CopyType (NCsDamage::NValue::NCopy::ICopy)
			#pragma region

			#define ValueType NCsDamage::NValue::IValue
			void FImpl::Copy(const ValueType* From)
			{
			#undef ValueType

				using namespace NCsDamage::NValue::NRange::NImpl::NCached;

				const FString& Context = Str::Copy;

				typedef NCsDamage::NValue::FLibrary ValueLibrary;

				const FImpl* FromImpl = ValueLibrary::PureStaticCastChecked<FImpl>(Context, From);

				SetMinValue(FromImpl->GetMinValue());
				SetMaxValue(FromImpl->GetMaxValue());
			}

			#pragma endregion CopyType (NCsDamage::NValue::NCopy::ICopy)

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(MinValue, 0.0f)
				CS_RESET_MEMBER_WITH_PROXY(MaxValue, 0.0f)
			}

			#pragma endregion ICsReset
		}
	}
}