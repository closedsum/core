// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Range/CsDamageRangeImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Range/CsLibrary_DamageRange.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NRange::NImpl::FImpl);

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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NRange::NImpl::FImpl, Copy);
				}
			}

			FImpl::FImpl() :
				InterfaceMap(),
				// RangeType (NCsDamage::NRange::IRange)
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MinRange, 0.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(MaxRange, 0.0f)
			{
				InterfaceMap = &InterfaceMap_Internal;

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(RangeType);
				CS_INTERFACE_MAP_ADD(ICsReset);
				CS_INTERFACE_MAP_ADD(CopyType);

				CS_CTOR_SET_MEMBER_PROXY(MinRange);
				CS_CTOR_SET_MEMBER_PROXY(MaxRange);
			}

			using RangeType = NCsDamage::NRange::IRange;

			// CopyType (NCsDamage::NRange::NCopy::ICopy)
			#pragma region
			
			void FImpl::Copy(const RangeType* From)
			{
				using namespace NCsDamage::NRange::NImpl::NCached;

				const FString& Context = Str::Copy;

				const FImpl* FromImpl = CsDamageRangeLibrary::PureStaticCastChecked<FImpl>(Context, From);

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
}