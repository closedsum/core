// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_StatusEffect.h"

// NCsStatusEffect::IStatusEffect
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, IStatusEffect)
// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)

namespace NCsStatusEffect
{
	namespace NCopy
	{
		/**
		* Interface for a Status Effect performing various Copy commands.
		*/
		struct CSSE_API ICopy : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		#define StatusEffectType NCsStatusEffect::IStatusEffect
		#define DataType NCsStatusEffect::NData::IData

		public:

			virtual ~ICopy(){}

			virtual void Copy(const StatusEffectType* From) = 0;

			virtual void CopyFromData(const FECsStatusEffect& Type, const DataType* Data) = 0;

		#undef StatusEffectType
		#undef DataType
		};
	}
}