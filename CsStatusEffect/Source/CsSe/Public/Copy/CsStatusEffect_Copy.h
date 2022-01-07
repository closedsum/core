// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsTypes_StatusEffect.h"

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

		#define DataType NCsStatusEffect::NData::IData

		public:

			virtual ~ICopy(){}

			virtual void CopyFromData(const FECsStatusEffect& Type, const DataType* Data) = 0;

		#undef DataType
		};
	}
}