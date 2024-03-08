// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Payload/CsPayload_Projectile.h"
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsProjectile
{
	namespace NPayload
	{
	#define PayloadType NCsProjectile::NPayload::IPayload

		/**
		*/
		struct CSPRJ_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		public:

			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsPooledObject::NPayload::FImplSlice (NCsPooledObject::NPayload::IPayload)
			*  NCsProjectile::NPayload::FImplSlice (NCsProjectile::NPayload::IPayload)
			*
			* @param Context	The calling context.
			* @param From		What to copy.
			* @param To			What to copy to.
			* return			Whether the From copied to To successfully.
			*/
			static bool CopyChecked(const FString& Context, const PayloadType* From, PayloadType* To);

			// NOTE:

			/**
			* Copy the slice of values from From to To with checks.
			* Currently supports To types of:
			*  NCsPooledObject::NPayload::FImplSlice (NCsPooledObject::NPayload::IPayload)
			*  NCsProjectile::NPayload::FImplSlice (NCsProjectile::NPayload::IPayload)
			*
			* @param Context	The calling context.
			* @param From		What to copy.
			* @param To			What to copy to.
			* return			Whether the From copied to To successfully.
			*/
			//template<typename SliceType, typename SliceInterfaceType>
			//static bool CopySliceChecked(const FString& Context, const InterfaceType* From, InterfaceType* To)
		};

	#undef PayloadType
	}
}