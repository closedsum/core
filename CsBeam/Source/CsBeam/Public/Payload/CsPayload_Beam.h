// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Beam.h"
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

			virtual const FVector& GetDirection() const = 0;

			virtual const FVector& GetLocation() const = 0;
		};
	}
}