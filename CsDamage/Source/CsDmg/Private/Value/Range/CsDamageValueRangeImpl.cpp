// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/Range/CsDamageValueRangeImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Value/CsLibrary_DamageValue.h"

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(NCsDamage::NValue::NRange::NImpl::FImpl);

CS_START_CACHED_FUNCTION_NAME_NESTED_4(NCsDamage, NValue, NRange, NImpl, Impl)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NValue::NRange::NImpl::FImpl, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_4

namespace NCsDamage
{
	namespace NValue
	{
		namespace NRange
		{
			namespace NImpl
			{
				FImpl::FImpl() :
					InterfaceMap(nullptr),
					InterfaceMap_Internal(),
					// RangeValueType (NCsDamage::NValue::NRange::IRange)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MinValue, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxValue, 0.0f)
				{
					InterfaceMap = &InterfaceMap_Internal;

					CS_INTERFACE_MAP_SET_ROOT(FImpl);

					CS_INTERFACE_MAP_ADD(ValueType);
					CS_INTERFACE_MAP_ADD(RangeValueType);
					CS_INTERFACE_MAP_ADD(ICsGetDamageValueType);
					CS_INTERFACE_MAP_ADD(CopyType);
					CS_INTERFACE_MAP_ADD(ICsReset);

					CS_CTOR_SET_MEMBER_PROXY(MinValue);
					CS_CTOR_SET_MEMBER_PROXY(MaxValue);
				}

				using ValueLibrary = NCsDamage::NValue::NLibrary::FLibrary;

				// CopyType (NCsDamage::NValue::NCopy::ICopy)
				#pragma region

				void FImpl::Copy(const ValueType* From)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

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
}