// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class AActor;
class UPrimitiveComponent;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NCollision
		{
			/**
			*/
			struct CSPRJ_API ICollision : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;
			public:

				virtual ~ICollision(){}

				/**
				* Get list of the actors to ignore on hit
				* NOTE: For now, only ignore on FIRST hit.
				* 
				*/
				virtual const TArray<AActor*>& GetIgnoreActorsOnHit() const = 0;

				/**
				* Get list of the component to ignore on hit
				* NOTE: For now, only ignore on FIRST hit.
				*
				*/
				virtual const TArray<UPrimitiveComponent*>& GetIgnoreComponentsOnHit() const = 0;
			};
		}
	}
}