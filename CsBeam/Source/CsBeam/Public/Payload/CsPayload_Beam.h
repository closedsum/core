// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Beam.h"
#include "Types/CsTypes_AttachDetach.h"
// Container
#include "Containers/CsGetInterfaceMap.h"

namespace NCsBeam
{
	namespace NPayload
	{
		/**
		*/
		struct CSBEAM_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			virtual const FECsBeam& GetType() const = 0;

			virtual const ECsAttachmentTransformRules& GetAttachRules() const = 0;

			virtual const FVector& GetLocation() const = 0;

			virtual const FVector& GetDirection() const = 0;

			virtual const FVector& GetScale() const = 0;
		};
	}
}