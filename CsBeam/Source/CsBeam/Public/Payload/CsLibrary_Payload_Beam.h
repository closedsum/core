// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Beam.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsBeam
{
	namespace NPayload
	{
	#define PayloadType NCsBeam::NPayload::IPayload

		/**
		*/
		struct CSBEAM_API FLibrary final : public NCsInterfaceMap::TLibrary<PayloadType>
		{
		public:

			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsPooledObject::NPayload::FImplSlice (NCsPooledObject::NPayload::IPayload)
			*  NCsBeam::NPayload::FImplSlice (NCsBeam::NPayload::IPayload)
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
			*  NCsBeam::NPayload::FImplSlice (NCsBeam::NPayload::IPayload)
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