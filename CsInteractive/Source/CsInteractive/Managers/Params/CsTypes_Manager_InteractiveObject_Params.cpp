// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Params/CsTypes_Manager_InteractiveObject_Params.h"

// Managers
#include "Managers/Params/CsManager_InteractiveObject_Params.h"

// FCsScopedInteractiveObjectHoldParams
#pragma region

FCsScopedInteractiveObjectHoldParams::FCsScopedInteractiveObjectHoldParams() :
	Root(nullptr),
	ResourceContainer(nullptr)
{
	ResourceContainer = UCsManager_InteractiveObject_Params::Get()->AllocateHoldParams();
}

FCsScopedInteractiveObjectHoldParams::FCsScopedInteractiveObjectHoldParams(UObject* InRoot) :
	Root(nullptr),
	ResourceContainer(nullptr)
{
	Root			  = InRoot;
	ResourceContainer = UCsManager_InteractiveObject_Params::Get(InRoot)->AllocateHoldParams();
}

FCsScopedInteractiveObjectHoldParams::~FCsScopedInteractiveObjectHoldParams()
{
	UCsManager_InteractiveObject_Params::Get(Root)->DeallocateHoldParams(ResourceContainer);
	ResourceContainer = nullptr;
}

ICsInteractiveObjectHoldParams* FCsScopedInteractiveObjectHoldParams::Get() const
{
	return ResourceContainer->Get();
}

#pragma endregion FCsScopedInteractiveObjectHoldParams