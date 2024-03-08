// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "Range/CsDamageRange.h"
#include "Range/Copy/CsDamageRange_Copy.h"
#include "Reset/CsReset.h"
// Types
#include "Types/CsTypes_Macro.h"
// Container
#include "Containers/CsInterfaceMap.h"

namespace NCsDamage
{
	namespace NRange
	{
	#define RangeType NCsDamage::NRange::IRange
	#define CopyType NCsDamage::NRange::NCopy::ICopy

		/**
		* Basic implementation of the interface: RangeType (NCsDamage::NRange::IRange)
		*/
		struct CSDMG_API FImpl : public RangeType,
								 public CopyType,
								 public ICsReset
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap InterfaceMap;

		// RangeType (NCsDamage::NRange::IRange)

			CS_DECLARE_MEMBER_WITH_PROXY(MinRange, float)
			CS_DECLARE_MEMBER_WITH_PROXY(MaxRange, float)

		public:

			FImpl();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return const_cast<FCsInterfaceMap*>(&InterfaceMap); }

		#pragma endregion ICsGetInterfaceMap

		// RangeType (NCsDamage::NRange::IRange)
		#pragma region
		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinRange, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxRange, float)

		#pragma endregion RangeType (NCsDamage::NRange::IRange)

		// CopyType (NCsDamage::NRange::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const RangeType* From);

		#pragma endregion CopyType (NCsDamage::NRange::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset
		};

	#undef RangeType
	#undef CopyType
	}
}