// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"

namespace NCsResource
{
	namespace NManager
	{
		namespace NValue
		{
			namespace NFixed
			{
				namespace NInt32
				{
					struct FResource final : public TCsResourceContainer<int32>
					{
					};

					struct FManager final : public NCsResource::NManager::NValue::TFixed<int32, FResource, 0>
					{
					};
				}
			}
		}
	}
}