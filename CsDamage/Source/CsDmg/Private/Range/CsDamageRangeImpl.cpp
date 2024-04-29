// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Range/CsDamageRangeImpl.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Range/CsLibrary_DamageRange.h"

const FName NCsDamage::NRange::FImpl::Name = FName("NCsDamage::NRange::FImpl");

namespace NCsDamage
{
	namespace NRange
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NRange::FImpl, Copy);
				}
			}
		}

		FImpl::FImpl() :
			InterfaceMap(),
			// RangeType (NCsDamage::NRange::IRange)
			CS_CTOR_INIT_MEMBER_WITH_PROXY(MinRange, 0.0f),
			CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxRange, 0.0f)
		{
			InterfaceMap.SetRoot<FImpl>(this);

			typedef NCsDamage::NRange::IRange RangeType;
			typedef NCsDamage::NRange::NCopy::ICopy CopyType;

			InterfaceMap.Add<RangeType>(static_cast<RangeType*>(this));
			InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
			InterfaceMap.Add<CopyType>(static_cast<CopyType*>(this));

			CS_CTOR_SET_MEMBER_PROXY(MinRange);
			CS_CTOR_SET_MEMBER_PROXY(MaxRange);
		}

		// CopyType (NCsDamage::NRange::NCopy::ICopy)
		#pragma region

		#define RangeType NCsDamage::NRange::IRange
		void FImpl::Copy(const RangeType* From)
		{
		#undef RangeType

			using namespace NCsDamage::NRange::NImpl::NCached;

			const FString& Context = Str::Copy;

			typedef NCsDamage::NRange::FLibrary ValueLibrary;

			const FImpl* FromImpl = ValueLibrary::PureStaticCastChecked<FImpl>(Context, From);

			SetMinRange(FromImpl->GetMinRange());
			SetMaxRange(FromImpl->GetMaxRange());
		}

		#pragma endregion CopyType (NCsDamage::NRange::NCopy::ICopy)

		// ICsReset
		#pragma region

		void FImpl::Reset()
		{
			CS_RESET_MEMBER_WITH_PROXY(MinRange, 0.0f)
			CS_RESET_MEMBER_WITH_PROXY(MaxRange, 0.0f)
		}

		#pragma endregion ICsReset
	}
}