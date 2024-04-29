// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Value/Point/CsDamageValuePointImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Value/CsLibrary_DamageValue.h"

const FName NCsDamage::NValue::NPoint::FImpl::Name = FName("NCsDamage::NValue::NPoint::FImpl");

namespace NCsDamage
{
	namespace NValue
	{
		namespace NPoint
		{
			namespace NImpl
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NValue::NPoint::FImpl, Copy);
					}
				}
			}

			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(),
				// PointValueType (NCsDamage::NValue::NPoint::IPoint)
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
			{
				// ICsGetInterfaceMap
				InterfaceMap.SetRoot<FImpl>(this);

				typedef NCsDamage::NValue::IValue ValueType;
				typedef NCsDamage::NValue::NPoint::IPoint PointValueType;
				typedef NCsDamage::NValue::NCopy::ICopy CopyType;

				InterfaceMap.Add<ValueType>(static_cast<ValueType*>(this));
				InterfaceMap.Add<PointValueType>(static_cast<PointValueType*>(this));
				InterfaceMap.Add<ICsGetDamageValueType>(static_cast<ICsGetDamageValueType*>(this));
				InterfaceMap.Add<CopyType>(static_cast<CopyType*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));

				CS_CTOR_SET_MEMBER_PROXY(Value);
			}

			// CopyType (NCsDamage::NValue::NCopy::ICopy)
			#pragma region

			#define ValueType NCsDamage::NValue::IValue
			void FImpl::Copy(const ValueType* From)
			{
			#undef ValueType

				using namespace NCsDamage::NValue::NPoint::NImpl::NCached;

				const FString& Context = Str::Copy;

				typedef NCsDamage::NValue::FLibrary ValueLibrary;

				const FImpl* FromImpl = ValueLibrary::PureStaticCastChecked<FImpl>(Context, From);

				SetValue(FromImpl->GetValue());
			}

			#pragma endregion CopyType (NCsDamage::NValue::NCopy::ICopy)

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Value, 0.0f)
			}

			#pragma endregion ICsReset
		}
	}
}