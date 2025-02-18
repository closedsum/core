// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

class USceneComponent;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NTarget
		{
			/**
			*/
			struct CSPRJ_API ITarget : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			public:

				virtual ~ITarget(){}

				virtual const bool& HasTarget() const = 0;

				virtual USceneComponent* GetTargetComponent() const = 0;

				virtual const FVector& GetTargetLocation() const = 0;

				virtual const FName& GetTargetBone() const = 0;

				virtual const int32& GetTargetID() const = 0;
			};
		}
	}
}