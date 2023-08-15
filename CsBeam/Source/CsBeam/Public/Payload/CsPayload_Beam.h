// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

			virtual const FAttachmentTransformRules& GetAttachRules() const = 0;

			virtual const FVector3f& GetLocation() const = 0;

			virtual const FVector3f& GetDirection() const = 0;

			virtual const FVector3f& GetScale() const = 0;
		};
	}
}