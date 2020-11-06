// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

// Managers
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Types
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
				namespace NParams
				{
					/**
					*/
					struct CSCORE_API FParams
					{
					#define AnimType NCsAnim::N2D::NFlipbook::NTexture::FFlipbook

					public:

						/** Context for the Coroutine Scheduler. This is 
							usually a reference to the GameInstance. */
						UObject* Context;
		
						FECsUpdateGroup UpdateGroup;

						UObject* Owner;

						UStaticMeshComponent* Component;

						AnimType Anim;

						FParams() :
							Context(nullptr),
							UpdateGroup(),
							Owner(nullptr),
							Component(nullptr),
							Anim()
						{
						}

					#undef AnimType
					};

					struct CSCORE_API FResource : public TCsResourceContainer<FParams>
					{
					};

					#define CS_PARAMS_PAYLOAD_SIZE 16

					struct CSCORE_API FManager : public TCsManager_ResourceValueType_Fixed<FParams, FResource, CS_PARAMS_PAYLOAD_SIZE>
					{
					};

					#undef CS_PARAMS_PAYLOAD_SIZE
				}
			}
		}
	}
}