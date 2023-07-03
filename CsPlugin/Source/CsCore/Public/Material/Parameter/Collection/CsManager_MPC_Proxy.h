// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Material
#include "Material/Parameter/Collection/CsMaterialParameterCollectionInstanceProxy.h"

namespace NCsMaterial
{
	namespace NParameter
	{
		namespace NCollection
		{
			namespace NProxy
			{
			#define ProxyType NCsMaterial::NParameter::NCollection::FProxy

				/**
				* Container for holding a reference to the object ProxyType (NCsMaterial::NParameter::NCollection::FProxy).
				* This serves as an easy way for a Manager Resource to keep track of the resource.
				*/
				struct FResource : public TCsResourceContainer<ProxyType> {};

				/**
				* A manager handling allocating and deallocating the object ProxyType (NCsMaterial::NParameter::NCollection::FProxy) and
				* are wrapped in the container: NCsMaterial::NParameter::NCollection::NProxy::FResource.
				*/
				struct FManager : public NCsResource::NManager::NValue::TFixed<ProxyType, FResource, 0> {};

			#undef ProxyType
			}
		}
	}
}