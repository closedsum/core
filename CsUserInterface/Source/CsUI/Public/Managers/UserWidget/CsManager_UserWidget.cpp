// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#include "Managers/UserWidget/CsManager_UserWidget.h"
#include "CsUI.h"

// CVars
#include "Managers/UserWidget/CsCVars_Manager_UserWidget.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Data/CsUILibrary_DataRootSet.h"
// Utility
#include "Utility/CsUILog.h"
// Settings
#include "Settings/CsUserInterfaceSettings.h"
// Data
#include "Data/CsUIDataRootSet.h"
// UserWidget
#include "Blueprint/UserWidget.h"
#include "Managers/UserWidget/Handler/CsManager_UserWidget_ClassHandler.h"
#include "Managers/UserWidget/Handler/CsManager_UserWidget_DataHandler.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImpl.h"

#if WITH_EDITOR
#include "Managers/Singleton/CsGetManagerSingleton.h"
#include "Managers/Singleton/CsManager_Singleton.h"
#include "Managers/UserWidget/CsGetManagerUserWidget.h"

#include "Library/CsLibrary_Common.h"

#include "Engine/World.h"
#include "Engine/Engine.h"

#include "GameFramework/GameStateBase.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

namespace NCsManagerUserWidget
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_UserWidget, SetupInternal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_UserWidget, InitInternalFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_UserWidget, PopulateDataMapFromSettings);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_UserWidget, GetUserWidgetPooled);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_UserWidget, GetUserWidget);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsManager_UserWidget, GetData);
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// Internal
#pragma region

namespace NCsUserWidget
{
	FManager::FManager()
		: Super()
	{
	}
}

#pragma endregion Internal

// static initializations
UCsManager_UserWidget* UCsManager_UserWidget::s_Instance;
bool UCsManager_UserWidget::s_bShutdown = false;

UCsManager_UserWidget::UCsManager_UserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_UserWidget* UCsManager_UserWidget::Get(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerUserWidget(InRoot)->GetManager_UserWidget();
}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
/*static*/ bool UCsManager_UserWidget::IsValid(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerUserWidget(InRoot)->GetManager_UserWidget() != nullptr;
}
#endif // #if WITH_EDITOR

/*static*/ void UCsManager_UserWidget::Init(UObject* InRoot, TSubclassOf<UCsManager_UserWidget> ManagerUserWidgetClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerUserWidget* GetManagerUserWidget = Get_GetManagerUserWidget(InRoot);

	UCsManager_UserWidget* Manager_UserWidget = GetManagerUserWidget->GetManager_UserWidget();

	if (!Manager_UserWidget)
	{
		Manager_UserWidget = NewObject<UCsManager_UserWidget>(InOuter ? InOuter : InRoot, ManagerUserWidgetClass, TEXT("Manager_UserWidget_Singleton"), RF_Transient | RF_Public);

		GetManagerUserWidget->SetManager_UserWidget(Manager_UserWidget);

		Manager_UserWidget->SetMyRoot(InRoot);
		Manager_UserWidget->Initialize();
	}
	else
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_UserWidget>(GetTransientPackage(), ManagerUserWidgetClass, TEXT("Manager_UserWidget_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_UserWidget::Shutdown(UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerUserWidget* GetManagerUserWidget = Get_GetManagerUserWidget(InRoot);
	UCsManager_UserWidget* Manager_UserWidget	  = GetManagerUserWidget->GetManager_UserWidget();
	Manager_UserWidget->CleanUp();

	GetManagerUserWidget->SetManager_UserWidget(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR
/*static*/ bool UCsManager_UserWidget::HasShutdown(UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerUserWidget(InRoot)->GetManager_UserWidget() == nullptr;
}
#endif // #if WITH_EDITOR

#if WITH_EDITOR

/*static*/ ICsGetManagerUserWidget* UCsManager_UserWidget::Get_GetManagerUserWidget(UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_UserWidget::Get_GetManagerUserWidget: InRoot is NULL."));

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_UserWidget::Get_GetManagerUserWidget: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_UserWidget::Get_GetManagerUserWidget: Manager_Singleton is NULL."));

	ICsGetManagerUserWidget* GetManagerUserWidget = Cast<ICsGetManagerUserWidget>(Manager_Singleton);

	checkf(GetManagerUserWidget, TEXT("UCsManager_UserWidget::Get_GetManagerUserWidget: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerUserWidget."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerUserWidget;
}

/*static*/ ICsGetManagerUserWidget* UCsManager_UserWidget::GetSafe_GetManagerUserWidget(UObject* Object)
{
	if (!Object)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::GetSafe_GetManagerUserWidget: Object is NULL."));
		return nullptr;
	}

	ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

	if (!GetManagerSingleton)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::GetSafe_GetManagerUserWidget: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
		return nullptr;
	}

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	if (!Manager_Singleton)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::GetSafe_GetManagerUserWidget: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
		return nullptr;
	}

	return Cast<ICsGetManagerUserWidget>(Manager_Singleton);
}

/*static*/ UCsManager_UserWidget* UCsManager_UserWidget::GetSafe(UObject* Object)
{
	if (ICsGetManagerUserWidget* GetManagerUserWidget = GetSafe_GetManagerUserWidget(Object))
		return GetManagerUserWidget->GetManager_UserWidget();
	return nullptr;
}

/*static*/ UCsManager_UserWidget* UCsManager_UserWidget::GetFromWorldContextObject(const UObject* WorldContextObject)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		// Game State
		if (UCsManager_UserWidget* Manager = GetSafe(World->GetGameState()))
			return Manager;

		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::GetFromWorldContextObject: Failed to Manager FX Actor of type UCsManager_UserWidget from GameState."));

		return nullptr;
	}
	else
	{
		return nullptr;
	}
}

#endif // #if WITH_EDITOR

void UCsManager_UserWidget::Initialize()
{
	SetupInternal();

	bInitialized = true;
}

/*static*/ bool UCsManager_UserWidget::HasInitialized(UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_UserWidget::CleanUp()
{
	Internal.Shutdown();
	Pool.Reset();

	delete ClassHandler;
	ClassHandler = nullptr;

	delete PooledClassHandler;
	PooledClassHandler = nullptr;

	delete DataHandler;
	DataHandler = nullptr;

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_UserWidget::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Internal
#pragma region

void UCsManager_UserWidget::SetupInternal()
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::SetupInternal;

	// Populate EnumMaps
	UWorld* World				= MyRoot->GetWorld();
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;

	NCsUserWidget::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsUserWidgetClass::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsUserWidgetPooled::PopulateEnumMapFromSettings(Context, GameInstance);
	NCsUserWidgetPooledClass::PopulateEnumMapFromSettings(Context, GameInstance);

	// Class Handler
	ConstructClassHandler();

	checkf(ClassHandler, TEXT("%s: Failed to construct ClassHandler."), *Context);

	ConstructPooledClassHandler();

	checkf(PooledClassHandler, TEXT("%s: Failed to construct PooledClassHandler."), *Context);

	// Data Handler
	ConstructDataHandler();

	checkf(DataHandler, TEXT("%s: Failed to construct DataHandler."), *Context);

	// Delegates
	{
		// Log
		Internal.LogTransaction_Impl.BindUObject(this, &UCsManager_UserWidget::LogTransaction);
		// Container
		Internal.ConstructContainer_Impl.BindUObject(this, &UCsManager_UserWidget::ConstructContainer);
		// Payload
		Internal.ConstructPayload_Impl.BindUObject(this, &UCsManager_UserWidget::ConstructPayload);
		// Pool
		Internal.OnAddToPool_Event.AddUObject(this, &UCsManager_UserWidget::OnAddToPool);
		// Update
		Internal.OnPreUpdate_Pool_Impl.BindUObject(this, &UCsManager_UserWidget::OnPreUpdate_Pool);
		Internal.OnUpdate_Object_Event.AddUObject(this, &UCsManager_UserWidget::OnUpdate_Object);
		Internal.OnPostUpdate_Pool_Impl.BindUObject(this, &UCsManager_UserWidget::OnPostUpdate_Pool);

		// Bind delegates for a script interface.
		Internal.Script_GetCache_Impl = Script_GetCache_Impl;
		Internal.Script_Allocate_Impl = Script_Allocate_Impl;
		Internal.Script_Deallocate_Impl = Script_Deallocate_Impl;
		Internal.Script_Update_Impl = Script_Update_Impl;
		Internal.Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;
	}
#if !UE_BUILD_SHIPPING
	//if (FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::EnableManagerUserWidgetUnitTest))
	//{
		// Do Nothing
	//}
	//else
#endif // #if !UE_BUILD_SHIPPING
		// If any settings have been set for Manager_Creep, apply them
	{
		UCsUserInterfaceSettings* ModuleSettings = GetMutableDefault<UCsUserInterfaceSettings>();

		checkf(ModuleSettings, TEXT("UCsManager_UserWidget::SetupInternal: Failed to get settings of type: UCsUserInterfaceSettings."));

		Settings = ModuleSettings->Manager_UserWidget;

		InitInternalFromSettings();
	}
}

void UCsManager_UserWidget::InitInternalFromSettings()
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::InitInternalFromSettings;

	ClassHandler->PopulateClassMapFromSettings(Context);
	PooledClassHandler->PopulateClassMapFromSettings(Context);

	const FCsUIDataRootSet& DataRootSet = NCsUIDataRootSet::FLibrary::GetChecked(Context, MyRoot);

	if (DataRootSet.bUserWidgetsHasData)
		DataHandler->PopulateDataMapFromSettings(Context);

	// TODO: Add support for Data for UserWidgetPooled

	if (Settings.PoolParams.Num() > CS_EMPTY)
	{
		typedef NCsUserWidget::FManager::FParams ManagerParamsType;

		ManagerParamsType ManagerParams;

		ManagerParams.Name  = TEXT("UCsManager_UserWidget::NCsUserWidget::FManager");
		ManagerParams.World = MyRoot->GetWorld();

		for (const TPair<FECsUserWidgetPooled, FCsSettings_Manager_UserWidget_PoolParams>& Pair : Settings.PoolParams)
		{
			const FECsUserWidgetPooled& Type						= Pair.Key;
			const FCsSettings_Manager_UserWidget_PoolParams& Params = Pair.Value;

			typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

			PoolParamsType& PoolParams = ManagerParams.ObjectParams.Add(Type);

			// Get Class
			const FECsUserWidgetPooledClass& ClassType = Params.Class;

			checkf(EMCsUserWidgetPooledClass::Get().IsValidEnum(ClassType), TEXT("%s: Class for NOT Valid."), *Context, ClassType.ToChar());

			FCsUserWidgetPooled* UserWidget = GetUserWidgetPooledChecked(Context, ClassType);
			UClass* Class					= UserWidget->GetClass();

			checkf(Class, TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar());

			PoolParams.Name								= ManagerParams.Name + TEXT("_") + Type.ToChar();
			PoolParams.World							= ManagerParams.World;
			PoolParams.ConstructParams.Outer			= this;
			PoolParams.ConstructParams.Class			= Class;
			PoolParams.ConstructParams.TypeName			= Params.Widget.GetFName();
			PoolParams.ConstructParams.ConstructionType = ECsPooledObjectConstruction::Object;
			PoolParams.bConstructPayloads				= true;
			PoolParams.PayloadSize						= Params.PayloadSize;
			PoolParams.bCreatePool						= true;
			PoolParams.PoolSize							= Params.PoolSize;
		}

		InitInternal(ManagerParams);
	}
}

#define ManagerParamsType NCsUserWidget::FManager::FParams
void UCsManager_UserWidget::InitInternal(const ManagerParamsType& Params)
{
	// Add CVars
	{
		ManagerParamsType& P = const_cast<ManagerParamsType&>(Params);

		typedef NCsPooledObject::NManager::FPoolParams PoolParamsType;

		for (TPair<FECsUserWidgetPooled, PoolParamsType>& Pair : P.ObjectParams)
		{
			PoolParamsType& PoolParams = Pair.Value;

			// Scoped Timer CVars
			PoolParams.ScopedGroup = NCsScopedGroup::ManagerUserWidget;

			PoolParams.CreatePoolScopedTimerCVar		= NCsCVarLog::LogManagerUserWidgetScopedTimerCreatePool;
			PoolParams.UpdateScopedTimerCVar			= NCsCVarLog::LogManagerUserWidgetScopedTimerUpdate;
			PoolParams.UpdateObjectScopedTimerCVar		= NCsCVarLog::LogManagerUserWidgetScopedTimerUpdateObject;
			PoolParams.AllocateScopedTimerCVar			= NCsCVarLog::LogManagerUserWidgetScopedTimerAllocate;
			PoolParams.AllocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerUserWidgetScopedTimerAllocateObject;
			PoolParams.DeallocateScopedTimerCVar		= NCsCVarLog::LogManagerUserWidgetScopedTimerDeallocate;
			PoolParams.DeallocateObjectScopedTimerCVar	= NCsCVarLog::LogManagerUserWidgetScopedTimerDeallocateObject;
			PoolParams.SpawnScopedTimerCVar				= NCsCVarLog::LogManagerUserWidgetScopedTimerSpawn;
			PoolParams.DestroyScopedTimerCVar			= NCsCVarLog::LogManagerUserWidgetScopedTimerDestroy;
		}
	}
	Internal.Init(Params);
}
#undef ManagerParamsType

void UCsManager_UserWidget::Clear()
{
	Internal.Clear();
}

	// Pool
#pragma region

void UCsManager_UserWidget::CreatePool(const FECsUserWidgetPooled& Type, const int32& Size)
{
	const int32& PoolSize = Internal.GetPoolSize(Type);

	if (PoolSize > CS_EMPTY)
	{
		UE_LOG(LogCsUI, Warning, TEXT("UCsManager_UserWidget::CreatePool: Pool for Creep: %s has already been created with Size: %d."), Type.ToChar(), PoolSize);
	}

	Internal.CreatePool(Type, Size);
}

TDelegate<FCsUserWidgetPooled*(const FECsUserWidgetPooled&)>& UCsManager_UserWidget::GetConstructContainer_Impl()
{
	return Internal.ConstructContainer_Impl;
}

FCsUserWidgetPooled* UCsManager_UserWidget::ConstructContainer(const FECsUserWidgetPooled& Type)
{
	return new FCsUserWidgetPooled();
}

#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
TMulticastDelegate<void(const FCsUserWidgetPooled*, const ConstructParamsType&)>& UCsManager_UserWidget::GetOnConstructObject_Event(const FECsUserWidgetPooled& Type)
{
#undef ConstructParamsType
	return Internal.GetOnConstructObject_Event(Type);
}
 
		// Add
#pragma region

			// Pool
#pragma region

const FCsUserWidgetPooled* UCsManager_UserWidget::AddToPool(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object)
{
	return Internal.AddToPool(Type, Object);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::AddToPool(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object)
{
	return Internal.AddToPool(Type, Object->GetObject());
}

const FCsUserWidgetPooled* UCsManager_UserWidget::AddToPool(const FECsUserWidgetPooled& Type, UObject* Object)
{
	return Internal.AddToPool(Type, Object);
}

void UCsManager_UserWidget::OnAddToPool(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object)
{
	Pool.Add(Object->GetObject());
}

#pragma endregion Pool

			// Allocated Objects
#pragma region

const FCsUserWidgetPooled* UCsManager_UserWidget::AddToAllocatedObjects(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Projectile, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Projectile, Object);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::AddToAllocatedObjects(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::AddToAllocatedObjects(const FECsUserWidgetPooled& Type, UObject* Object)
{
	return Internal.AddToAllocatedObjects(Type, Object);
}

#pragma endregion Allocated Objects

#pragma endregion Add

const TArray<FCsUserWidgetPooled*>& UCsManager_UserWidget::GetPool(const FECsUserWidgetPooled& Type)
{
	return Internal.GetPool(Type);
}

const TArray<FCsUserWidgetPooled*>& UCsManager_UserWidget::GetAllocatedObjects(const FECsUserWidgetPooled& Type)
{
	return Internal.GetAllocatedObjects(Type);
}

const int32& UCsManager_UserWidget::GetPoolSize(const FECsUserWidgetPooled& Type)
{
	return Internal.GetPoolSize(Type);
}

int32 UCsManager_UserWidget::GetAllocatedObjectsSize(const FECsUserWidgetPooled& Type)
{
	return Internal.GetAllocatedObjectsSize(Type);
}

bool UCsManager_UserWidget::IsExhausted(const FECsUserWidgetPooled& Type)
{
	return Internal.IsExhausted(Type);
}

	// Find
#pragma region

const FCsUserWidgetPooled* UCsManager_UserWidget::FindObject(const FECsUserWidgetPooled& Type, const int32& Index)
{
	return Internal.FindObject(Type, Index);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::FindObject(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::FindObject(const FECsUserWidgetPooled& Type, UObject* Object)
{
	return Internal.FindObject(Type, Object);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::FindSafeObject(const FECsUserWidgetPooled& Type, const int32& Index)
{
	return Internal.FindSafeObject(Type, Index);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::FindSafeObject(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

const FCsUserWidgetPooled* UCsManager_UserWidget::FindSafeObject(const FECsUserWidgetPooled& Type, UObject* Object)
{
	return Internal.FindSafeObject(Type, Object);
}

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region

void UCsManager_UserWidget::Update(const FCsDeltaTime& DeltaTime)
{
	Internal.Update(DeltaTime);
}

void UCsManager_UserWidget::OnPreUpdate_Pool(const FECsUserWidgetPooled& Type)
{
	CurrentUpdatePoolType		 = Type;
	CurrentUpdatePoolObjectIndex = 0;
}

void UCsManager_UserWidget::OnUpdate_Object(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object)
{
	++CurrentUpdatePoolObjectIndex;
}

void UCsManager_UserWidget::OnPostUpdate_Pool(const FECsUserWidgetPooled& Type)
{
}

#pragma endregion Update

	// Payload
#pragma region

void UCsManager_UserWidget::ConstructPayloads(const FECsUserWidgetPooled& Type, const int32& Size)
{
	Internal.ConstructPayloads(Type, Size);
}

#define PayloadType NCsUserWidget::NPayload::IPayload
PayloadType* UCsManager_UserWidget::ConstructPayload(const FECsUserWidgetPooled& Type)
{
#undef PayloadType

	typedef NCsUserWidget::NPayload::FImpl PayloadImplType;

	return new PayloadImplType();
}

#define PayloadType NCsUserWidget::NPayload::IPayload
PayloadType* UCsManager_UserWidget::AllocatePayload(const FECsUserWidgetPooled& Type)
{
#undef PayloadType
	return Internal.AllocatePayload(Type);
}

#pragma endregion Payload

	// Spawn
#pragma region

#define PayloadType NCsUserWidget::NPayload::IPayload
const FCsUserWidgetPooled* UCsManager_UserWidget::Spawn(const FECsUserWidgetPooled& Type, PayloadType* Payload)
{
#undef PayloadType
	return Internal.Spawn(Type, Payload);
}

#pragma endregion Spawn

	// Destroy
#pragma region

bool UCsManager_UserWidget::Destroy(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object)
{
	return Internal.Destroy(Type, Object);
}

bool UCsManager_UserWidget::Destroy(ICsUserWidgetPooled* Object)
{
	return Internal.Destroy(Object);
}

#pragma endregion Destroy

	// Log
#pragma region

void UCsManager_UserWidget::Log(const FString& Str)
{
	UE_LOG(LogCsUI, Warning, TEXT("%s"), *Str);
}

void UCsManager_UserWidget::LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsUserWidgetPooled* Object)
{
	if (CS_CVAR_LOG_IS_SHOWING(LogManagerUserWidgetTransactions))
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
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s for %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, *ParentName, CurrentTime);
		}
		else 
		if (ObjectOwner)
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s for %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *OwnerName, CurrentTime);
		}
		else
		if (Parent)
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s attached to %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, *ParentName, CurrentTime);
		}
		else
		{
			UE_LOG(LogCsUI, Warning, TEXT("%s: %s %s of Type: %s at %f."), *Context, *TransactionAsString, *ObjectName, *ClassName, CurrentTime);
		}
	}
}

#pragma endregion Log

#pragma endregion Internal

// Class
#pragma region

void UCsManager_UserWidget::ConstructClassHandler()
{
	typedef NCsUserWidget::NManager::NHandler::FClass ClassHandlerType;

	ClassHandler = new ClassHandlerType();
	ClassHandler->Outer = this;
	ClassHandler->MyRoot = MyRoot;
}

FCsUserWidgetPooled* UCsManager_UserWidget::GetUserWidgetPooled(const FECsUserWidgetPooled& Type)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetUserWidgetPooled;

	return PooledClassHandler->GetClassByType<EMCsUserWidgetPooled, FECsUserWidgetPooled>(Context, Type);
}

FCsUserWidgetPooled* UCsManager_UserWidget::GetUserWidgetPooled(const FECsUserWidgetPooledClass& Type)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetUserWidgetPooled;

	return PooledClassHandler->GetClassByClassType<EMCsUserWidgetPooledClass>(Context, Type);
}

FCsUserWidgetPooled* UCsManager_UserWidget::GetUserWidgetPooledChecked(const FString& Context, const FECsUserWidgetPooledClass& Type)
{
	return PooledClassHandler->GetClassByClassTypeChecked<EMCsUserWidgetPooledClass>(Context, Type);
}

void UCsManager_UserWidget::ConstructPooledClassHandler()
{
	typedef NCsUserWidget::NManager::NHandler::FPooledClass ClassHandlerType;

	PooledClassHandler = new ClassHandlerType();
	PooledClassHandler->Outer = this;
	PooledClassHandler->MyRoot = MyRoot;
}

FCsUserWidgetPtr* UCsManager_UserWidget::GetUserWidget(const FECsUserWidget& Type)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetUserWidget;

	return ClassHandler->GetClassByType<EMCsUserWidget, FECsUserWidget>(Context, Type);
}

FCsUserWidgetPtr* UCsManager_UserWidget::GetUserWidgetChecked(const FString& Context, const FECsUserWidget& Type)
{
	return ClassHandler->GetClassByTypeChecked<EMCsUserWidget, FECsUserWidget>(Context, Type);
}

FCsUserWidgetPtr* UCsManager_UserWidget::GetUserWidget(const FECsUserWidgetClass& Type)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetUserWidget;

	return ClassHandler->GetClassByClassType<EMCsUserWidgetClass>(Context, Type);
}

FCsUserWidgetPtr* UCsManager_UserWidget::GetUserWidgetChecked(const FString& Context, const FECsUserWidgetClass& Type)
{
	return ClassHandler->GetClassByClassTypeChecked<EMCsUserWidgetClass>(Context, Type);
}

#pragma endregion Class

// Data
#pragma region

void UCsManager_UserWidget::ConstructDataHandler()
{
	typedef NCsUserWidget::NManager::NHandler::FData DataHandlerType;

	DataHandler = new DataHandlerType();
	DataHandler->Outer = this;
	DataHandler->MyRoot = MyRoot;
}

#define DataType NCsUserWidget::NData::IData

DataType* UCsManager_UserWidget::GetData(const FName& Name)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData(Context, Name);
}

DataType* UCsManager_UserWidget::GetData(const FECsUserWidget& Type)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData<EMCsUserWidget, FECsUserWidget>(Context, Type);
}

DataType* UCsManager_UserWidget::GetData(const FECsUserWidgetPooled& Type)
{
	using namespace NCsManagerUserWidget::NCached;

	const FString& Context = Str::GetData;

	return DataHandler->GetData<EMCsUserWidgetPooled, FECsUserWidgetPooled>(Context, Type);
}

DataType* UCsManager_UserWidget::GetDataChecked(const FString& Context, const FName& Name)
{
	return DataHandler->GetDataChecked(Context, Name);
}

DataType* UCsManager_UserWidget::GetDataChecked(const FString& Context, const FECsUserWidget& Type)
{
	return DataHandler->GetDataChecked<EMCsUserWidget, FECsUserWidget>(Context, Type);
}

DataType* UCsManager_UserWidget::GetDataChecked(const FString& Context, const FECsUserWidgetPooled& Type)
{
	return DataHandler->GetDataChecked<EMCsUserWidgetPooled, FECsUserWidgetPooled>(Context, Type);
}

#undef DataType

#pragma endregion Data