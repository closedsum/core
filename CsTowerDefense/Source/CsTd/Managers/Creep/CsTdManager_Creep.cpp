// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/Creep/CsTdManager_Creep.h"
#include "CsTd.h"
#include "CsCVars.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/Creep/CsTdGetManagerCreep.h"

#include "Library/CsLibrary_Common.h"

#include "Classes/Engine/World.h"
#include "Classes/Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Internal
#pragma region

FCsTdManager_Creep_Internal::FCsTdManager_Creep_Internal()
	: Super()
{
}

#pragma endregion Internal

// static initializations
UCsTdManager_Creep* UCsTdManager_Creep::s_Instance;
bool UCsTdManager_Creep::s_bShutdown = false;

UCsTdManager_Creep::UCsTdManager_Creep(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsTdManager_Creep::BeginDestroy()
{
	Super::BeginDestroy();

	UCsTdManager_Creep::Shutdown(this);
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsTdManager_Creep::OnRegister()
{
	Super::OnRegister();

	Init(this);
}

#pragma endregion UActorComponent Interface

// Singleton
#pragma region

/*static*/ UCsTdManager_Creep* UCsTdManager_Creep::Get(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerCreep(InRoot)->GetManager_Creep();
#else
	if (s_bShutdown)
		return nullptr;

	if (!s_Instance)
	{
		UE_LOG(LogCsTd, Warning, TEXT("UCsTdManager_Creep::Get: Manager must be attached and registered on a game object in order to call Get()."));
		return nullptr;
	}

	return s_Instance;
#endif // #if WITH_EDITOR
}

/*static*/ void UCsTdManager_Creep::Init(UCsTdManager_Creep* Manager)
{
	s_bShutdown = false;

	if (s_Instance)
	{
		UE_LOG(LogCsTd, Warning, TEXT("UCsTdManager_Creep::Init: This is being called before the previous instance of the manager has been Shutdown."));
	}
	s_Instance = Manager;

	s_Instance->Initialize();
}

/*static*/ void UCsTdManager_Creep::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsTdGetManagerCreep* GetManagerCreep = Get_GetManagerCreep(InRoot);
	UCsTdManager_Creep* Manager_Creep	  = GetManagerCreep->GetManager_Creep();
	Manager_Creep->CleanUp();

	GetManagerCreep->SetManager_Creep(nullptr);
#else
	if (!s_Instance)
		return;

	s_Instance->CleanUp();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsTdGetManagerCreep* UCsTdManager_Creep::Get_GetManagerCreep(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: Manager_Singleton is NULL."));

	ICsTdGetManagerCreep* GetManagerCreep = Cast<ICsTdGetManagerCreep>(Manager_Singleton);

	checkf(GetManagerCreep, TEXT("UCsTdManager_Creep::Get_GetManagerCreep: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsTdGetManagerCreep."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerCreep;
}

/*static*/ ICsTdGetManagerCreep* UCsTdManager_Creep::GetSafe_GetManagerCreep(UObject* Object)
{
	if (!Object)
		return nullptr;

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
		return nullptr;

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
		return nullptr;

	return Cast<ICsTdGetManagerCreep>(Manager_Singleton);
}

/*static*/ UCsTdManager_Creep* UCsTdManager_Creep::GetSafe(UObject* Object)
{
	if (ICsTdGetManagerCreep* GetManagerCreep = GetSafe_GetManagerCreep(Object))
		return GetManagerCreep->GetManager_Creep();
	return nullptr;
}

/*static*/ UCsTdManager_Creep* UCsTdManager_Creep::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game Instance
		if (UCsTdManager_Creep* Manager = GetSafe(World->GetGameInstance()))
			return Manager;
		// Game State
		if (UCsTdManager_Creep* Manager = GetSafe(World->GetGameState()))
			return Manager;

		// Player Controller
		TArray<APlayerController*> Controllers;

		//UCsLibrary_Common::GetAllLocalPlayerControllers(World, Controllers);

		if (Controllers.Num() == CS_EMPTY)
			return nullptr;

		for (APlayerController* Controller : Controllers)
		{
			if (UCsTdManager_Creep* Manager = GetSafe(Controller))
				return Manager;
		}

		UE_LOG(LogCsTd, Warning, TEXT("UCsTdManager_Creep::GetFromWorldContextObject: Failed to Manager Item of type UCsTdManager_Creep from GameInstance, GameState, or PlayerController."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsTdManager_Creep::Initialize()
{
	ConstructInternal();
}

void UCsTdManager_Creep::CleanUp()
{
	Internal->Shutdown();
	Pool.Reset();
	delete Internal;
}

#pragma endregion Singleton

// Internal
#pragma region

void UCsTdManager_Creep::ConstructInternal()
{
	Internal = new FCsTdManager_Creep_Internal();

	Internal->OnCreatePool_AddToPool_Event.AddUObject(this, &UCsTdManager_Creep::OnCreatePool_AddToPool);
	Internal->OnPreUpdate_Pool_Impl.BindUObject(this, &UCsTdManager_Creep::OnPreUpdate_Pool);
	Internal->OnUpdate_Object_Event.AddUObject(this, &UCsTdManager_Creep::OnUpdate_Object);
	Internal->OnPostUpdate_Pool_Impl.BindUObject(this, &UCsTdManager_Creep::OnPostUpdate_Pool);

	// Bind delegates for a script interface.
	Internal->Script_GetCache_Impl = Script_GetCache_Impl;
	Internal->Script_Allocate_Impl = Script_Allocate_Impl;
	Internal->Script_Update_Impl = Script_Update_Impl;
	Internal->Script_Deallocate_Impl = Script_Deallocate_Impl;
}

void UCsTdManager_Creep::InitInternal(const TCsTdManager_Internal::FCsManagerPooledObjectMapParams& Params)
{
	Internal->Init(Params);
}

void UCsTdManager_Creep::Clear()
{
	Internal->Clear();
}

	// Pool
#pragma region

void UCsTdManager_Creep::CreatePool(const FECsTdCreep& Type, const int32& Size)
{
	checkf(Size > 0, TEXT("UCsTdManager_Creep::CreatePool: Size must be GREATER THAN 0."));

	// TODO: Check if the pool has already been created

	TArray<FCsTdCreepPooled>& Creeps = Pools.FindOrAdd(Type);
	Creeps.Reserve(Size);
	TArray<FCsTdCreepPooled>& Objects = AllocatedObjects.FindOrAdd(Type);
	Objects.Reserve(Size);

	Internal->CreatePool(Type, Size);
}

void UCsTdManager_Creep::OnCreatePool_AddToPool(const FECsTdCreep& Type, const FCsPooledObject& Object)
{
	AddToPool_Internal(Type, Object);
}

		// Add
#pragma region

			// Pool
#pragma region

TArray<FCsTdCreepPooled>& UCsTdManager_Creep::CheckAndAddType_Pools(const FECsTdCreep& Type)
{
	TArray<FCsTdCreepPooled>* ValuePtr = Pools.Find(Type);

	if (!ValuePtr)
	{
		TArray<FCsTdCreepPooled>& Value = Pools.Add(Type);
		AllocatedObjects.Add(Type);
		return Value;
	}
	return *ValuePtr;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToPool(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	checkf(Object, TEXT("UCsTdManager_Creep::AddToPool: Object is NULL."));

	// UObject
	if (UObject* O = Object->_getUObject())
	{
		UClass* Class = O->GetClass();

		// Check ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(O))
		{
			const FCsPooledObject& PooledObject =  Internal->AddToPool(Type, Interface, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& PooledObject = Internal->AddToPool(Type, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsTdManager_Creep::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Interface, TEXT("UCsTdManager_Creep::AddToPool: Interface is NULL or does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& PooledObject = Internal->AddToPool(Type, Interface);

		return AddToPool_Internal(Type, PooledObject);
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToPool(const FECsTdCreep& Type, const FCsTdCreepPooled& Object)
{
	if (UObject* O = Object.GetObject())
	{
		UClass* Class = O->GetClass();

		// Add ICsPooledObject interface

			// Interface
		if (ICsPooledObject* Interface = Object.GetInterface())
		{
			const FCsPooledObject& PooledObject = Internal->AddToPool(Type, Interface, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& PooledObject = Internal->AddToPool(Type, O);

			return AddToPool_Internal(Type, PooledObject);
		}
			// INVALID
		else
		{
			checkf(false, TEXT("UCsTdManager_Creep::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
		// Add ICsPooledObject interface
		ICsPooledObject* Interface = Object.GetInterface();

		checkf(Interface, TEXT("UCsTdManager_Creep::AddToPool: Interface is NULL."));

		const FCsPooledObject& PooledObject = Internal->AddToPool(Type, Interface);

		return AddToPool_Internal(Type, PooledObject);
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToPool(const FECsTdCreep& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsTdManager_Creep::AddToPool: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Add ICsPooledObject interface

		// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& O = Internal->AddToPool(Type, Interface);

		return AddToPool_Internal(Type, O);
	}
		// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& O = Internal->AddToPool(Type, Object);

		return AddToPool_Internal(Type, O);
	}
		// INVALID
	else
	{
		checkf(false, TEXT("UCsTdManager_Creep::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(Object->GetName()), *(Class->GetName()));
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToPool_Internal(const FECsTdCreep& Type, const FCsPooledObject& Object)
{
	TArray<FCsTdCreepPooled>& Creeps = CheckAndAddType_Pools(Type);

	Creeps.AddDefaulted();
	FCsTdCreepPooled& C = Creeps.Last();

	const int32 Index = Creeps.Num() - 1;

	checkf(Index == Object.GetCache()->GetIndex(), TEXT("UCsTdManager_Creep::OnAddToPool: Mismatch between Creep (%d) and Pooled Object (%s)"), Index, Object.GetCache()->GetIndex());

	C.SetPooledObject(Object);

	// UObject
	if (UObject* O = C.GetObject())
	{
		UClass* Class = O->GetClass();

		// Interface
		if (ICsTdCreep* Creep = Cast<ICsTdCreep>(O))
		{
			C.SetCreep(Creep);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsTdCreep::StaticClass()))
		{
			C.SetScriptCreep();

			// Check and bind delegates for the script interface.

			/*
			// GetOwner
			if (!C.Script_GetOwner_Impl.IsBound())
				C.Script_GetOwner_Impl = Script_GetOwner_Impl;

			checkf(P.Script_GetOwner_Impl.IsBound(), TEXT("UCsTdManager_Creep::OnAddToPool: Object: %s with Class: %s does NOT have Script_GetOwner_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));

			// GetInstigator
			if (!C.Script_GetInstigator_Impl.IsBound())
				C.Script_GetInstigator_Impl = Script_GetInstigator_Impl;

			checkf(P.Script_GetInstigator_Impl.IsBound(), TEXT("UCsTdManager_Creep::OnAddToPool: Object: %s with Class: %s does NOT have Script_GetInstigator_Impl Bound to any function."), *(O->GetName()), *(Class->GetName()));
			*/
		}
		// INVALID
		else
		{
			checkf(false, TEXT("UCsTdManager_Creep::AddToPool: Object: %s with Class: %s does NOT implement interface: ICsTdCreep."), *(O->GetName()), *(Class->GetName()));
		}
	}
	else
	{
		ICsPooledObject* Interface = Object.GetInterface();

#if !UE_BUILD_SHIPPING
		ICsTdCreep* Creep = dynamic_cast<ICsTdCreep*>(Interface);
#else
		ICsTdCreep* Creep = (ICsTdCreep*)Interface;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Creep, TEXT("UCsTdManager_Creep::OnAddToPool: Creep is NULL or does NOT implement interface: ICsTdCreep."));

		C.SetCreep(Creep);
	}
	return C;
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

TArray<FCsTdCreepPooled>& UCsTdManager_Creep::CheckAndAddType_AllocatedObjects(const FECsTdCreep& Type)
{
	TArray<FCsTdCreepPooled>* ValuePtr = AllocatedObjects.Find(Type);

	if (!ValuePtr)
	{
		Pools.Add(Type);
		TArray<FCsTdCreepPooled>& Value = AllocatedObjects.Add(Type);
		return Value;
	}
	return *ValuePtr;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToAllocatedObjects(const FECsTdCreep& Type, ICsTdCreep* PooledObject, UObject* Object)
{
	checkf(PooledObject, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: PooledObject is NULL."));

	checkf(Object, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Interface, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* InterfaceObject = dynamic_cast<ICsPooledObject*>(PooledObject);
#else
		ICsPooledObject* InterfaceObject = (ICsPooledObject*)PooledObject;
#endif // #if !UE_BUILD_SHIPPING

		checkf(InterfaceObject, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: InterfaceObject is NULL or does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, InterfaceObject);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToAllocatedObjects(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	checkf(Object, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: Object is NULL."));
		
	if (UObject* O = Object->_getUObject())
	{
		UClass* Class = O->GetClass();

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(O))
		{
			const FCsPooledObject& PooledObject = Internal->AddToAllocatedObjects(Type, Interface, O);

			return AddToAllocatedObjects_Internal(Type, PooledObject);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& PooledObject = Internal->AddToAllocatedObjects(Type, O);

			return AddToAllocatedObjects_Internal(Type, PooledObject);
		}
		// INVALID
		else
		{
			checkf(false, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: Object does NOT implement interface: ICsPooledObject."));
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* InterfaceObject = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* InterfaceObject = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(InterfaceObject, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: InterfaceObject is NULL or does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& PooledObject = Internal->AddToAllocatedObjects(Type, InterfaceObject);

		return AddToAllocatedObjects_Internal(Type, PooledObject);
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToAllocatedObjects(const FECsTdCreep& Type, UObject* Object)
{
	checkf(Object, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: Object is NULL."));

	UClass* Class = Object->GetClass();

	// Interface
	if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Interface, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	// Script Interface
	else
	if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
	{
		const FCsPooledObject& O = Internal->AddToAllocatedObjects(Type, Object);

		return AddToAllocatedObjects_Internal(Type, O);
	}
	else
	{
		checkf(false, TEXT("UCsTdManager_Creep::AddToAllocatedObjects: Object does NOT implement interface: ICsPooledObject."));
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::AddToAllocatedObjects_Internal(const FECsTdCreep& Type, const FCsPooledObject& Object)
{
	TArray<FCsTdCreepPooled>& Objects = CheckAndAddType_AllocatedObjects(Type);

	Objects.AddDefaulted();
	FCsTdCreepPooled& O = Objects.Last();

	const int32& Index = Object.GetCache()->GetIndex();

	O = Pools[Type][Index];

	return O;
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsTdCreepPooled>& UCsTdManager_Creep::GetPool(const FECsTdCreep& Type)
{
	return CheckAndAddType_AllocatedObjects(Type);
}

const TArray<FCsTdCreepPooled>& UCsTdManager_Creep::GetAllocatedObjects(const FECsTdCreep& Type)
{
	return CheckAndAddType_Pools(Type);
}

const int32& UCsTdManager_Creep::GetPoolSize(const FECsTdCreep& Type)
{
	return Internal->GetPoolSize(Type);
}

int32 UCsTdManager_Creep::GetAllocatedObjectsSize(const FECsTdCreep& Type)
{
	return Internal->GetAllocatedObjectsSize(Type);
}

bool UCsTdManager_Creep::IsExhausted(const FECsTdCreep& Type)
{
	return Internal->IsExhausted(Type);
}

	// Find
#pragma region

const FCsTdCreepPooled& UCsTdManager_Creep::FindObject(const FECsTdCreep& Type, const int32& Index)
{
	const FCsPooledObject& O = Internal->FindObject(Type, Index);

	return CheckAndAddType_Pools(Type)[Index];
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindObject(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	if (UObject* U = Object->_getUObject())
	{
		UClass* Class = U->GetClass();

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, Interface);

			return FindObject_Internal(Type, O);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, U);

			return FindObject_Internal(Type, O);
		}
		// INVALID
		else
		{
			checkf(false, TEXT("UCsTdManager_Creep::FindObject: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *(U->GetName()), *(Class->GetName()));
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		checkf(Interface, TEXT("UCsTdManager_Creep::FindObject: Object does NOT implement interface: ICsPooledObject."));

		const FCsPooledObject& O = Internal->FindObject(Type, Interface);

		return FindObject_Internal(Type, O);
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindObject(const FECsTdCreep& Type, UObject* Object)
{
	const FCsPooledObject& O = Internal->FindObject(Type, Object);
	const int32& Index		 = O.GetCache()->GetIndex();

	return CheckAndAddType_Pools(Type)[Index];
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindObject_Internal(const FECsTdCreep& Type, const FCsPooledObject& Object)
{
	const int32& Index = Object.GetCache()->GetIndex();

	return CheckAndAddType_Pools(Type)[Index];
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindSafeObject(const FECsTdCreep& Type, const int32& Index)
{
	if (Index < 0)
		return FCsTdCreepPooled::Empty;

	const FCsPooledObject& O = Internal->FindSafeObject(Type, Index);

	if (!O.IsValid())
		return FCsTdCreepPooled::Empty;

	TArray<FCsTdCreepPooled>& Creeps = CheckAndAddType_Pools(Type);

	if (Index >= Creeps.Num())
		return FCsTdCreepPooled::Empty;

	return Creeps[Index];
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindSafeObject(const FECsTdCreep& Type, ICsTdCreep* Object)
{
	if (!Object)
		return FCsTdCreepPooled::Empty;

	if (UObject* U = Object->_getUObject())
	{
		UClass* Class = U->GetClass();

		// Interface
		if (ICsPooledObject* Interface = Cast<ICsPooledObject>(U))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, Interface);

			return FindSafeObject_Internal(Type, O);
		}
		// Script Interface
		else
		if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
		{
			const FCsPooledObject& O = Internal->FindObject(Type, U);

			return FindSafeObject_Internal(Type, O);
		}
		// INVALID
		else
		{
			return FCsTdCreepPooled::Empty;
		}
	}
	else
	{
#if !UE_BUILD_SHIPPING
		ICsPooledObject* Interface = dynamic_cast<ICsPooledObject*>(Object);
#else
		ICsPooledObject* Interface = (ICsPooledObject*)Object;
#endif // #if !UE_BUILD_SHIPPING

		if (!Interface)
			return FCsTdCreepPooled::Empty;

		const FCsPooledObject& O = Internal->FindObject(Type, Interface);

		return FindSafeObject_Internal(Type, O);
	}
	return FCsTdCreepPooled::Empty;
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindSafeObject(const FECsTdCreep& Type, UObject* Object)
{
	if (!Object)
		return FCsTdCreepPooled::Empty;

	const FCsPooledObject& O = Internal->FindObject(Type, Object);

	return FindSafeObject_Internal(Type, O);
}

const FCsTdCreepPooled& UCsTdManager_Creep::FindSafeObject_Internal(const FECsTdCreep& Type, const FCsPooledObject& Object)
{
	if (!Object.IsValid())
		return FCsTdCreepPooled::Empty;

	const int32& Index = Object.GetCache()->GetIndex();

	TArray<FCsTdCreepPooled>& Creeps = CheckAndAddType_Pools(Type);

	if (Index >= Creeps.Num())
		return FCsTdCreepPooled::Empty;

	return Creeps[Index];
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsTdManager_Creep::Update(const FCsDeltaTime& DeltaTime)
{
	Internal->Update(DeltaTime);
}

void UCsTdManager_Creep::OnPreUpdate_Pool(const FECsTdCreep& Type)
{
	CurrentUpdatePoolType = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsTdManager_Creep::OnUpdate_Object(const FECsTdCreep& Type, const FCsPooledObject& Object)
{
	const int32& Index = Object.GetCache()->GetIndex();

	TArray<FCsTdCreepPooled>& Creeps = AllocatedObjects[Type];

	Creeps[CurrentUpdatePoolObjectIndex] = Creeps[Index];

	++CurrentUpdatePoolObjectIndex;
}

void UCsTdManager_Creep::OnPostUpdate_Pool(const FECsTdCreep& Type)
{
	TArray<FCsTdCreepPooled>& Creeps = AllocatedObjects[Type];
	const int32 CreepSize		     = Creeps.Num();

	for (int32 I = CreepSize - 1; I >= CurrentUpdatePoolObjectIndex; --I)
	{
		Creeps.RemoveAt(I, 1, false);
	}
}

#pragma endregion Update

	// Payload
#pragma region

void UCsTdManager_Creep::ConstructPayloads(const FECsTdCreep& Type, const int32& Size)
{
	Internal->DeconstructPayloads(Type);

	ICsManager_PooledObject* Interface = Internal->GetManagerPooledObjects(Type);
	FCsManager_PooledObject* P		   = (FCsManager_PooledObject*)Interface;

	P->GetConstructPayloads_Impl().Unbind();
	P->GetConstructPayloads_Impl().BindRaw(P, &FCsManager_PooledObject::ConstructPayloads<FCsTdCreepPayload>);

	Internal->ConstructPayloads(Type, Size);
}

FCsTdCreepPayload* UCsTdManager_Creep::AllocatePayload(const FECsTdCreep& Type)
{
	return Internal->AllocatePayload<FCsTdCreepPayload>(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

const FCsTdCreepPooled& UCsTdManager_Creep::Spawn(const FECsTdCreep& Type, ICsPooledObjectPayload* Payload)
{
	checkf(Payload, TEXT("UCsTdManager_Creep::Spawn: Payload is NULL."));

	const FCsPooledObject& Object = Internal->Spawn(Type, Payload);

	ICsPooledObject* Interface = Object.GetInterface();
	const int32& Index		   = Interface->GetCache()->GetIndex();

	TArray<FCsTdCreepPooled>& Creeps = Pools[Type];
	const FCsTdCreepPooled& C		 = Creeps[Index];

	AllocatedObjects[Type].Add(C);

	OnSpawn_Event.Broadcast(Type, C);

	if (OnSpawn_ScriptEvent.IsBound() &&
		C.IsObject())
	{
		OnSpawn_ScriptEvent.Broadcast(Type, TScriptInterface<ICsTdCreep>(C.GetSafeObject()));
	}
	return C;
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsTdManager_Creep::Destroy(const FECsTdCreep& Type, ICsTdCreep* Creep)
{
	checkf(EMCsTdCreep::Get().IsValidEnum(Type), TEXT("UCsTdManager_Creep::Destroy: Type: %s is NOT a valid Enum."), *(Type.Name));
	
	checkf(Creep, TEXT("UCsTdManager_Creep::Destroy: Creep is NULL."));

	// TODO: do _getUObject

#if !UE_BUILD_SHIPPING
	ICsPooledObject* O = dynamic_cast<ICsPooledObject*>(Creep);
#else
	ICsPooledObject* O = (ICsPooledObject*)Creep;
#endif // #if !UE_BUILD_SHIPPING

	checkf(O, TEXT("UCsTdManager_Creep::Destroy: Creep is NULL or does NOT implement interface: ICsPooledObject."));

	if (Internal->Destroy(Type, O))
	{
		// Remove from AllocatedObjects

		TArray<FCsTdCreepPooled>& Creeps = Pools[Type];

		const int32& ProjectileIndex = O->GetCache()->GetIndex();
		const FCsTdCreepPooled& C	 = Creeps[ProjectileIndex];

		// Rebuild AllocatedObjects from Internal AllocatedObjects

		TArray<FCsTdCreepPooled>& Objects = AllocatedObjects[Type];

		const int32 OldSize = Objects.Num();

		const TArray<FCsPooledObject>& Internal_AllocatedObjects = Internal->GetAllocatedObjects(Type);

		const int32 NewSize = Internal_AllocatedObjects.Num();

		for (int32 I = 0; I <= NewSize; ++I)
		{
			const FCsPooledObject& Container = Internal_AllocatedObjects[I];
			const int32& Index				 = Container.GetCache()->GetIndex();

			Objects[I] = Creeps[Index];
		}

		for (int32 I = OldSize - 1; I >= NewSize; --I)
		{
			Objects.RemoveAt(I, 1, false);
		}
		OnDestroy_Event.Broadcast(Type, C);
		return true;
	}
	return false;
}

bool UCsTdManager_Creep::Destroy(ICsTdCreep* Creep)
{
	checkf(Creep, TEXT("UCsTdManager_Creep::Destroy: Creep is NULL."));

#if !UE_BUILD_SHIPPING
	ICsPooledObject* O = dynamic_cast<ICsPooledObject*>(Creep);
#else
	ICsPooledObject* O = (ICsPooledObject*)Creep;
#endif // #if !UE_BUILD_SHIPPING

	checkf(O, TEXT("UCsTdManager_Creep::Destroy: Creep is NULL or does NOT implement interface: ICsPooledObject."));

	const int32& Index = O->GetCache()->GetIndex();

	bool TypeFound = false;

	for (TPair<FECsTdCreep, TArray<FCsTdCreepPooled>>& Pair : Pools)
	{
		const FECsTdCreep& Type			 = Pair.Key;
		TArray<FCsTdCreepPooled>& Creeps = Pair.Value;

		if (Index >= Creeps.Num())
			continue;

		for (FCsTdCreepPooled& C : Creeps)
		{
			ICsPooledObject* Interface = C.GetInterface();
			
			if (Index == Interface->GetCache()->GetIndex())
			{
				return Destroy(Type, C.GetCreep());
			}
		}
	}
	return false;
}


#pragma endregion Destroy

#pragma endregion Internal