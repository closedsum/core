// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Animation/2D/CsTypes_Anim2D.h"
#include "Managers/Time/CsTypes_Update.h"

#pragma once

class UObject;
class UStaticMeshComponent;

namespace NCsAnim
{
	namespace N2D
	{
		namespace NPlay
		{
			namespace NStaticMesh
			{
				/**
				*/
				struct CSCORE_API FParams
				{
				#define PlayRateType NCsAnim::N2D::EPlayRate

				public:

					/** Context for the Coroutine Scheduler. This is 
						usually a reference to the GameInstance. */
					UObject* Context;
		
					FECsUpdateGroup UpdateGroup;

					UObject* Owner;

					UStaticMeshComponent* Component;

					PlayRateType PlayRate;

					float DeltaTime;

					FParams() :
						Context(nullptr),
						UpdateGroup(),
						Owner(nullptr),
						Component(nullptr),
						PlayRate(PlayRateType::PR_60Fps),
						DeltaTime(0.0f)
					{
					}

				#undef PlayRateType
				};
			}
		}
	}
}