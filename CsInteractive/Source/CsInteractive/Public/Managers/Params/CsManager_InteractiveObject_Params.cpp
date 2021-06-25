// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Params/CsManager_InteractiveObject_Params.h"
#include "CsInteractive.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Params/CsGetManagerInteractiveObjectParams.h"
#endif // #if WITH_EDITOR

// static initializations
UCsManager_InteractiveObject_Params* UCsManager_InteractiveObject_Params::s_Instance;
bool UCsManager_InteractiveObject_Params::s_bShutdown = false;

UCsManager_InteractiveObject_Params::UCsManager_InteractiveObject_Params(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

/*static*/ UCsManager_InteractiveObject_Params* UCsManager_InteractiveObject_Params::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerInteractiveObjectParams(InRoot)->GetManager_InteractiveObject_Params();
#else
	if (s_bShutdown)
		return nullptr;

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_InteractiveObject_Params::Init(UObject* InRoot)
{
#if WITH_EDITOR
	ICsGetManagerInteractiveObjectParams* GetManagerInteractiveObjectParams = Get_GetManagerInteractiveObjectParams(InRoot);

	UCsManager_InteractiveObject_Params* Manager_InteractiveObject_Params = NewObject<UCsManager_InteractiveObject_Params>(InRoot, UCsManager_InteractiveObject_Params::StaticClass(), TEXT("Manager_InteractiveObject_Params_Singleton"), RF_Transient | RF_Public);

	GetManagerInteractiveObjectParams->SetManager_InteractiveObject_Params(Manager_InteractiveObject_Params);

	Manager_InteractiveObject_Params->SetMyRoot(InRoot);
	Manager_InteractiveObject_Params->Initialize();
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_InteractiveObject_Params>(GetTransientPackage(), UCsManager_InteractiveObject_Params::StaticClass(), TEXT("Manager_InteractiveObject_Params_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_InteractiveObject_Params::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerInteractiveObjectParams* GetManagerInteractiveObjectParams = Get_GetManagerInteractiveObjectParams(InRoot);
	UCsManager_InteractiveObject_Params* Manager_InteractiveObject_Params   = GetManagerInteractiveObjectParams->GetManager_InteractiveObject_Params();
	Manager_InteractiveObject_Params->CleanUp();

	GetManagerInteractiveObjectParams->SetManager_InteractiveObject_Params(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerInteractiveObjectParams* UCsManager_InteractiveObject_Params::Get_GetManagerInteractiveObjectParams(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_InteractiveObject_Params::Get: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_InteractiveObject_Params::Get: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_InteractiveObject_Params::Get: Manager_Singleton is NULL."));

	ICsGetManagerInteractiveObjectParams* GetManagerInteractiveObjectParams = Cast<ICsGetManagerInteractiveObjectParams>(Manager_Singleton);

	checkf(GetManagerInteractiveObjectParams, TEXT("UCsManager_InteractiveObject_Params::Get: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerInteractiveObjectParams."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerInteractiveObjectParams;
}

#endif // #if WITH_EDITOR

void UCsManager_InteractiveObject_Params::Initialize()
{
	const int32 PoolSize = 4;

	Manager_HoldParams.ConstructResourceType_Impl.BindUObject(this, &UCsManager_InteractiveObject_Params::ConstructHoldParams);
	Manager_HoldParams.CreatePool(PoolSize);
}

void UCsManager_InteractiveObject_Params::CleanUp()
{
}

#pragma endregion Singleton

ICsInteractiveObjectHoldParams* UCsManager_InteractiveObject_Params::ConstructHoldParams()
{
	return new FCsInteractiveObjectHoldParams();
}

FCsResource_InteractiveObjectHoldParams* UCsManager_InteractiveObject_Params::AllocateHoldParams()
{
	return Manager_HoldParams.Allocate();
}

void UCsManager_InteractiveObject_Params::DeallocateHoldParams(FCsResource_InteractiveObjectHoldParams* Params)
{
	Manager_HoldParams.Deallocate(Params);
}