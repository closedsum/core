// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourcePointerType_Fixed.h"

class UInstancedStaticMeshComponent;

namespace NCsStaticMesh
{
	namespace NInstanced
	{
		namespace NComponent
		{ 
			// ModifierType (NCAbility::NModifier::IModifier)

			/**
			* Container for holding a reference to an UInstancedStaticMeshComponent.
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSCORE_API FResource : public TCsResourceContainer<UInstancedStaticMeshComponent> {};

			/**
			* A manager handling allocating and deallocating UInstancedStaticMeshComponent
			* and are wrapped in the container: ModifierType (NCAbility::NModifer::FResource).
			*/
			struct CSCORE_API FManager : public NCsResource::NManager::NPointer::TFixed<UInstancedStaticMeshComponent, FResource, 0> {};
		}
	}
}