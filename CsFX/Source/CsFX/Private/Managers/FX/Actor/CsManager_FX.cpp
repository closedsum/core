// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Actor/CsManager_FX.h"
#include "CsFX.h"

// CVars
#include "Managers/FX/Actor/CsCVars_Manager_FX.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Data
#include "Managers/FX/Data/CsData_FX.h"
#include "Managers/FX/Data/CsData_FXImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
// Package
#include "UObject/Package.h"

#if WITH_EDITOR
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/FX/Actor/CsGetManagerFX.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_FX)

// Cached
#pragma region

namespace NCsManagerFX
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX, InitInternalFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX, BindToOnPause);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_FX, Spawn);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsFX
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_FX* UCsManager_FX::s_Instance;
bool UCsManager_FX::s_bShutdown = false;

UCsManager_FX::UCsManager_FX(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// Singleton
	bInitialized(false),
	MyRoot(nullptr),
	// Settings
	Settings(),
	// Internal
	Internal(),
		// Pool
	CurrentUpdatePoolType(),
	CurrentUpdatePoolObjectIndex(0),
		// Pause
	OnPauseHandleByGroupMap(),
		// Spawn
	OnSpawn_Event(),
	OnSpawn_ScriptEvent(),
		// Destroy
	OnDestroy_Event(),
	// Pool
	Pool(),
	// Script
	Script_GetCache_Impl(),
	Script_Allocate_Impl(),
	Script_Deallocate_Impl(),
	Script_Update_Impl(),
	Script_OnConstructObject_Impl(),
	// Data
	DataMap(),
	ClassMap(),
	DataTables(),
	// Params
	Manager_Parameter_Int(),
	Manager_Parameter_Float(),
	Manager_Parameter_Vector(),
	Manager_Parameter_Scaled_Int(),
	Manager_Parameter_Scaled_Float(),
	Manager_Parameter_Scaled_Vector(),
	Manager_Parameter_DataInterface_SkeletalMesh()
{
}

// Singleton
#pragma region

#if WITH_EDITOR

/*static*/ UCsManager_FX* UCsManager_FX::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerFX(InRoot)->GetManager_FX();
}

/*static*/ UCsManager_FX* UCsManager_FX::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerFX* GetManagerFX = GetSafe_GetManagerFX(Context, InRoot, Log))
		return GetManagerFX->GetManager_FX();
	return nullptr;
}

/*static*/ bool UCsManager_FX::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerFX(InRoot)->GetManager_FX() != nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_FX::Init(UObject* InRoot, TSubclassOf<UCsManager_FX> ManagerFXClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFX* GetManagerFX = Get_GetManagerFX(InRoot);

	UCsManager_FX* Manager_FX = GetManagerFX->GetManager_FX();

	if (!Manager_FX)
	{
		Manager_FX = NewObject<UCsManager_FX>(InOuter ? InOuter : InRoot, ManagerFXClass, TEXT("Manager_FX_Singleton"), RF_Transient | RF_Public);

		GetManagerFX->SetManager_FX(Manager_FX);

		Manager_FX->SetMyRoot(InRoot);
		Manager_FX->Initialize();
	}
	else
	{
		UE_LOG(LogCsFX, Warning, TEXT("UCsManager_FX::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_FX>(GetTransientPackage(), ManagerFXClass, TEXT("Manager_FX_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsFX, Warning, TEXT("UCsManager_FX::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_FX::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerFX* GetManagerFX = Get_GetManagerFX(InRoot);
	UCsManager_FX* Manager_FX	= GetManagerFX->GetManager_FX();
	Manager_FX->CleanUp();

	GetManagerFX->SetManager_FX(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsFX, Warning, TEXT("UCsManager_FX::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_FX::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerFX(InRoot)->GetManager_FX() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerFX* UCsManager_FX::Get_GetManagerFX(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_FX::Get_GetManagerProjectile: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_FX::Get_GetManagerFX: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_FX::Get_GetManagerFX: Manager_Singleton is NULL."));

	ICsGetManagerFX* GetManagerFX = Cast<ICsGetManagerFX>(Manager_Singleton);

	checkf(GetManagerFX, TEXT("UCsManager_FX::Get_GetManagerFX: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerFX."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerFX;
}

/*static*/ ICsGetManagerFX* UCsManager_FX::GetSafe_GetManagerFX(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	CS_IS_PTR_NULL_RET_NULL(InRoot)

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	if (!GetManagerSingleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Singleton from InRoot: %s with Class: %s."), *Context, *(InRoot->GetName()), *(InRoot->GetClass()->GetName())));
		return nullptr;
	}
	return Cast<ICsGetManagerFX>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_FX::Initialize()
{
	SetupInternal();

	State = EState::Active;
	bInitialized = true;
}

/*static*/ bool UCsManager_FX::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_FX::CleanUp()
{
	State = EState::BeginShutdown;

	// Unbind delegates for Time related events
	{
		typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

		if (UCsManager_Time* Manager_Time = TimeManagerLibrary::GetSafe(MyRoot))
		{
			for (const TPair<FECsUpdateGroup, FDelegateHandle>& Pair : OnPauseHandleByGroupMap)
			{
				const FECsUpdateGroup& Group = Pair.Key;
				const FDelegateHandle& Handle = Pair.Value;

				Manager_Time->RemoveOnPause(Group, Handle);
			}
		}
		OnPauseHandleByGroupMap.Reset();
	}

	Internal.Shutdown();
	
	// Editor Preview - Make sure to mark pending kill or destroy objects
#if WITH_EDITOR
	if (UWorld* World = MyRoot->GetWorld())
	{
		if (World->WorldType == EWorldType::EditorPreview)
		{
			for (UObject* O : Pool)
			{
				if (IsValid(O))
				{
					if (AActor* A = Cast<AActor>(O))
						A->Destroy();
					else
						O->MarkAsGarbage();
				}
			}
		}
	}
#endif // #if WITH_EDITOR
	Pool.Reset();

	for (TPair<FName, ICsData_FX*>& Pair : DataMap)
	{
		ICsData_FX* Data = Pair.Value;
		DeconstructData(Data);
		Pair.Value = nullptr;
	}
	DataMap.Reset();
	// Params
	Manager_Parameter_Int.Shutdown();
	Manager_Parameter_Float.Shutdown();
	Manager_Parameter_Vector.Shutdown();
	Manager_Parameter_Scaled_Int.Shutdown();
	Manager_Parameter_Scaled_Float.Shutdown();
	Manager_Parameter_Scaled_Vector.Shutdown();
	Manager_Parameter_DataInterface_SkeletalMesh.Shutdown();

	State = EState::None;
	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_FX::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_FX::SetupInternal()
{
	using namespace NCsManagerFX::NCached;

	const FString& Context = Str::SetupInternal;

	typedef NCsGameInstance::FLibrary GameInstanceLibrary;

	// Populate EnumMaps

	UObject* ContextRoot = GameInstanceLibrary::GetSafeAsObject(Context, MyRoot, nullptr);

	NCsFX::PopulateEnumMapFromSettings(Context, ContextRoot);

	// Delegates
	{
		// Log
		Internal.Log_Impl.BindStatic(&FCsLog::Warning);
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_FX::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_FX::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_FX::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_FX::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_FX::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_FX::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_FX::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerFXUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Creep, apply them
	{
		Settings = FCsSettings_Manager_FX::GetChecked(Context);

		InitInternalFromSettings();
	}
	// Params
	{
		const FCsSettings_Manager_FX& Manager_FX = FCsSettings_Manager_FX::GetChecked(Context);

		const int32 (&PoolSizes)[(uint8)ECsFXParameterValue::ECsFXParameterValue_MAX] = Manager_FX.Parameters.PoolSizes;
		
		// Int
		{
			const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Int];

			checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Int] is NOT > 0."), *Context);

			Manager_Parameter_Int.CreatePool(Size);

			typedef NCsFX::NParameter::NInt::FResource ResourceContainerType;
			typedef NCsFX::NParameter::NInt::FIntType ResourceType;

			const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_Int.GetPool();

			const int32 Count = ParamPool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ResourceType* R = ParamPool[I]->Get();
				R->SetIndex(I);
			}
		}
		// Float
		{
			const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Float];

			checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Float] is NOT > 0."), *Context);

			Manager_Parameter_Float.CreatePool(Size);

			typedef NCsFX::NParameter::NFloat::FResource ResourceContainerType;
			typedef NCsFX::NParameter::NFloat::FFloatType ResourceType;

			const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_Float.GetPool();
	
			const int32 Count = ParamPool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ResourceType* R = ParamPool[I]->Get();
				R->SetIndex(I);
			}
		}
		// Vector
		{
			const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Float];

			checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Vector] is NOT > 0."), *Context);

			Manager_Parameter_Vector.CreatePool(Size);

			typedef NCsFX::NParameter::NVector::FResource ResourceContainerType;
			typedef NCsFX::NParameter::NVector::FVectorType ResourceType;

			const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_Vector.GetPool();

			const int32 Count = ParamPool.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				ResourceType* R = ParamPool[I]->Get();
				R->SetIndex(I);
			}
		}

		// Scaled
		{
			// Int
			{
				const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Int];

				checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Int] is NOT > 0."), *Context);

				Manager_Parameter_Scaled_Int.CreatePool(Size);

				typedef NCsFX::NParameter::NScaled::NInt::FResource ResourceContainerType;
				typedef NCsFX::NParameter::NScaled::NInt::FIntType ResourceType;

				const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_Scaled_Int.GetPool();

				const int32 Count = ParamPool.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ResourceType* R = ParamPool[I]->Get();
					R->SetIndex(I);
				}
			}
			// Float
			{
				const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Float];

				checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Float] is NOT > 0."), *Context);

				Manager_Parameter_Scaled_Float.CreatePool(Size);

				typedef NCsFX::NParameter::NScaled::NFloat::FResource ResourceContainerType;
				typedef NCsFX::NParameter::NScaled::NFloat::FFloatType ResourceType;

				const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_Scaled_Float.GetPool();
	
				const int32 Count = ParamPool.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ResourceType* R = ParamPool[I]->Get();
					R->SetIndex(I);
				}
			}
			// Vector
			{
				const int32& Size = PoolSizes[(uint8)ECsFXParameterValue::Float];

				checkf(Size > 0, TEXT("%s: UCsDeveloperSettings->Manager_FX.Parameters.PoolSizes[Vector] is NOT > 0."), *Context);

				Manager_Parameter_Scaled_Vector.CreatePool(Size);

				typedef NCsFX::NParameter::NScaled::NVector::FResource ResourceContainerType;
				typedef NCsFX::NParameter::NScaled::NVector::FVectorType ResourceType;

				const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_Scaled_Vector.GetPool();

				const int32 Count = ParamPool.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ResourceType* R = ParamPool[I]->Get();
					R->SetIndex(I);
				}
			}
		}
		// Data Interface
		{
			// Skeletal Mesh
			{
				// TODO: Get from Settings
				const int32 Size = 8;

				Manager_Parameter_DataInterface_SkeletalMesh.CreatePool(Size);

				typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::FResource ResourceContainerType;
				typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType ResourceType;

				const TArray<ResourceContainerType*>& ParamPool = Manager_Parameter_DataInterface_SkeletalMesh.GetPool();

				const int32 Count = ParamPool.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ResourceType* R = ParamPool[I]->Get();
					R->SetIndex(I);
				}
			}
		}
	}

	typedef NCsFX::NPayload::NChange::FCounter ChangeCounter;

	ChangeCounter::Get().Reset();
}

void UCsManager_FX::InitInternalFromSettings()
{
	using namespace NCsManagerFX::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsFX::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_FX::NCsFX::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsFX, FCsSettings_Manager_FX_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsFX& Type								= Pair.Key;
			const FCsSettings_Manager_FX_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			checkf(Params.Class.ToSoftObjectPath().IsValid(), TEXT("%s: Class for Type: %s is NOT a Valid Path."), *Context, Type.ToChar());

#if !UE_BUILD_SHIPPING
			if (!Params.Class.Get())
			{
				UE_LOG(LogCsFX, Warning, TEXT("%s: Class @ for Type: %s is NOT already loaded in memory."), *Context, *(Params.Class.ToString()), Type.ToChar());
			}
#endif // #if !UE_BUILD_SHIPPING

			UClass* Class = Params.Class.LoadSynchronous();

			checkf(Class, TEXT("%s: Failed to load Class @ for Type: %s."), *Context, *(Params.Class.ToString()), Type.ToChar());

			ClassMap.Add(Type, Class);

			PoolParams.Name							  = ManagerParams.Name + TEXT("_") + Type.GetName();
			PoolParams.World						  = ManagerParams.World;
			PoolParams.ConstructParams.Outer		  = this;
			PoolParams.ConstructParams.Class		  = Class;
			PoolParams.ConstructParams.ConstructionType = NCsPooledObject::EConstruction::Object;
			PoolParams.bConstructPayloads			  = true;
			PoolParams.PayloadSize					  = Params.PayloadSize;
			PoolParams.bCreatePool					  = true;
			PoolParams.PoolSize						  = Params.PoolSize;
		}

		InitInternal(ManagerParams);
	}
}

#define ManagerParamsType NCsFX::FManager::FParams
void UCsManager_FX::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsFX, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerFX;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerFXScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerFXScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerFXScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerFXScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerFXScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerFXScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar = NCsCVarLog::LogManagerFXScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerFXScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerFXScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}
#undef ManagerParamsType

void UCsManager_FX::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_FX::CreatePool(const FECsFX& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsFX, Warning, TEXT("UCsManager_FX::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TDelegate<FCsFXActorPooled*(const FECsFX&)>& UCsManager_FX::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsFXActorPooled* UCsManager_FX::ConstructContainer(const FECsFX& Type)
{
	return new FCsFXActorPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsFXActorPooled*, const ConstructParamsType&)>& UCsManager_FX::GetOnConstructObject_Event(const FECsFX& Type)
{
#undef ConstructParamsType
	return Internal.GetOnConstructObject_Event(Type);
}

		// Add
#pragma region

			// Pool
#pragma region

const FCsFXActorPooled* UCsManager_FX::AddToPool(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX::AddToPool(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsFXActorPooled* UCsManager_FX::AddToPool(const FECsFX& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_FX::OnAddToPool(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsFXActorPooled* UCsManager_FX::AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsFXActorPooled* UCsManager_FX::AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX::AddToAllocatedObjects(const FECsFX& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsFXActorPooled*>& UCsManager_FX::GetPool(const FECsFX& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsFXActorPooled*>& UCsManager_FX::GetAllocatedObjects(const FECsFX& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

void UCsManager_FX::LogAllocatedObjects() const
{
#if WITH_EDITOR

	static TArray<FECsFX> Types;
	Internal.GetPoolTypes(Types);

	for (const FECsFX& Type : Types)
	{
		UE_LOG(LogCsFX, Warning, TEXT("UCsManager_FX:: Pool: %s"), Type.ToChar());
		
		const TArray<FCsFXActorPooled*>& AllocatedObjects = Internal.GetAllocatedObjects(Type);
		
		const int32 Count = AllocatedObjects.Num();

		UE_LOG(LogCsFX, Warning, TEXT(" AllocatedObjects: %d"), Count);

		for (FCsFXActorPooled* FXPooled : AllocatedObjects)
		{
			FXPooled->GetFXActorPooled()->PrintDescription(2);	
		}
	}

#endif // #if WITH_EDITOR
}

const int32& UCsManager_FX::GetPoolSize(const FECsFX& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_FX::GetAllocatedObjectsSize(const FECsFX& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_FX::IsExhausted(const FECsFX& Type)
{
	return Internal.IsExhausted(Type);
}

bool UCsManager_FX::IsAnyAllocated() const
{
	return Internal.IsAnyAllocated();
}

bool UCsManager_FX::IsNoneAllocated() const
{
	return Internal.IsNoneAllocated();
}

	// Find
#pragma region

const FCsFXActorPooled* UCsManager_FX::FindObject(const FECsFX& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsFXActorPooled* UCsManager_FX::FindObject(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX::FindObject(const FECsFX& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX::FindSafeObject(const FECsFX& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsFXActorPooled* UCsManager_FX::FindSafeObject(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsFXActorPooled* UCsManager_FX::FindSafeObject(const FECsFX& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_FX::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_FX::OnPreUpdate_Pool(const FECsFX& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_FX::OnUpdate_Object(const FECsFX& Type, const FCsFXActorPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_FX::OnPostUpdate_Pool(const FECsFX& Type)
{
}

#pragma endregion Update

	// Pause
#pragma region

void UCsManager_FX::Pause(const FECsUpdateGroup& Group, bool bPaused)
{
	Internal.Pause(bPaused);
}

void UCsManager_FX::Pause(const FECsFX& Type, bool bPaused)
{
	Internal.Pause(Type, bPaused);
}

void UCsManager_FX::BindToOnPause(const FECsUpdateGroup& Group)
{
	using namespace NCsManagerFX::NCached;

	const FString& Context = Str::BindToOnPause;

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	UObject* ContextRoot   = TimeManagerLibrary::GetContextRootChecked(Context, GetOuter());
	FDelegateHandle Handle = UCsManager_Time::Get(ContextRoot)->GetOnPause_Event(Group).AddUObject(this, &UCsManager_FX::Pause);

	OnPauseHandleByGroupMap.Add(Group, Handle);
}

#pragma endregion Pause

	// Allocate / Deallocate
#pragma region

void UCsManager_FX::QueueDeallocateAll()
{
	Internal.QueueDeallocateAll();
}

#pragma endregion Allocate / Deallocate

	// Payload
#pragma region

void UCsManager_FX::ConstructPayloads(const FECsFX& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

#define PayloadType NCsFX::NPayload::IPayload

PayloadType* UCsManager_FX::ConstructPayload(const FECsFX& Type)
{
	typedef NCsFX::NPayload::FImpl PayloadImplType;

	PayloadImplType* Payload = new PayloadImplType();

	Payload->SetRoot(MyRoot);

	return Payload;
}

PayloadType* UCsManager_FX::AllocatePayload(const FECsFX& Type)
{
	return Internal.AllocatePayload(Type);
}

#undef PayloadType

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsFX::NPayload::IPayload
const FCsFXActorPooled* UCsManager_FX::Spawn(const FECsFX& Type, PayloadType* Payload)
{
#undef PayloadType

	using namespace NCsManagerFX::NCached;

	const FString& Context = Str::Spawn;

	typedef NCsFX::NPayload::FLibrary FXPayloadLibrary;

	check(FXPayloadLibrary::IsValidChecked(Context, Payload));

	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_FX::Destroy(const FECsFX& Type, ICsFXActorPooled* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_FX::Destroy(ICsFXActorPooled* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_FX::Log(const FString& Str)
{
	UE_LOG(LogCsFX, Warning, TEXT("%s"), *Str);
}

void UCsManager_FX::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsFXActorPooled* Object)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerFXTransactions))
	{
		const FString& TransactionAsString = EMCsPoolTransaction::Get().ToString(Transaction);

		ICsPooledObject* Interface  = Object->GetInterface();
		const FString ClassName		= Object->GetObject()->GetClass()->GetName();
		const FString ObjectName	= Object->GetObject()->GetName();
		const UObject* ObjectOwner	= Interface->GetCache()->GetOwner();
		const FString OwnerName		= ObjectOwner ? ObjectOwner->GetName() : NCsCached::Str::None;
		const UObject* Parent		= Interface->GetCache()->GetParent();
		const FString ParentName	= Parent ? Parent->GetName() : NCsCached::Str::None;
		const float CurrentTime		= GetWorld()->GetTimeSeconds();

		if (ObjectOwner && Parent)
		{
			UE_LOG(LogCsFX, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCsFX, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCsFX, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCsFX, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log

#pragma endregion Internal

// Data
#pragma region

void UCsManager_FX::DeconstructData(ICsData_FX* Data)
{
	FCsInterfaceMap* InterfaceMap = Data->GetInterfaceMap();

	checkf(InterfaceMap, TEXT("UCsManager_FX::DeconstructData: Data failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));
	
	// FCsData_FXImpl
	if (InterfaceMap->GetRootName() == FCsData_FXImpl::Name)
	{
		delete static_cast<FCsData_FXImpl*>(Data);
	}
	else
	{
		checkf(0, TEXT("UCsManager_FX::DeconstructData: Failed to delete Data."));
	}
}

ICsData_FX* UCsManager_FX::GetData(const FName& Name)
{
	checkf(Name != NAME_None, TEXT("UCsManager_FX::GetData: Name = None is NOT Valid."));

	ICsData_FX** DataPtr = DataMap.Find(Name);

	checkf(DataPtr, TEXT("UCsManager_FX::GetData: Failed to find Data for Name: %s."), *(Name.ToString()));

	return *DataPtr;
}

#pragma endregion Data

// Params
#pragma region

#define ParameterType NCsFX::NParameter::IParameter
void UCsManager_FX::DeallocateValue(ParameterType* Value)
{
#undef ParameterType
	checkf(Value, TEXT("UCsManager_FX::DeallocateValue: Value is NULL."));

	typedef NCsFX::NParameter::EValue ParameterValueType;

	const ParameterValueType& ValueType = Value->GetValueType();

	// Int
	if (ValueType == ParameterValueType::Int)
		DeallocateValue((NCsFX::NParameter::NInt::FIntType*)Value);
	// Float
	if (ValueType == ParameterValueType::Float)
		DeallocateValue((NCsFX::NParameter::NFloat::FFloatType*)Value);
	// Vector
	else
	if (ValueType == ParameterValueType::Vector)
		DeallocateValue((NCsFX::NParameter::NVector::FVectorType*)Value);
}

	// Scaled
#pragma region

#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled
void UCsManager_FX::DeallocateValue(ScaledParameterType* Value)
{
#undef ScaledParameterType
	checkf(Value, TEXT("UCsManager_FX::DeallocateValue: Value is NULL."));

	typedef NCsFX::NParameter::EValue ParameterValueType;

	const ParameterValueType& ValueType = Value->GetParameter()->GetValueType();

	// Int
	if (ValueType == ParameterValueType::Int)
		DeallocateValue((NCsFX::NParameter::NScaled::NInt::FIntType*)Value);
	// Float
	if (ValueType == ParameterValueType::Float)
		DeallocateValue((NCsFX::NParameter::NScaled::NFloat::FFloatType*)Value);
	// Vector
	else
	if (ValueType == ParameterValueType::Vector)
		DeallocateValue((NCsFX::NParameter::NScaled::NVector::FVectorType*)Value);
}

#pragma endregion Scaled

#pragma endregion Params