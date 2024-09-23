// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Spawner/CsManager_Spawner.h"
#include "CsSpawner.h"

// CVars
//#include "Managers/Spawner/CCVars_Manager_Spawner.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
	// Modifier
#include "Modifier/CsLibrary_SpawnerModifier.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
// Settings
#include "Managers/Spawner/CsGetSettingsManagerSpawner.h"
// Spawner
#include "Modifier/Types/CsGetSpawnerModifierType.h"
#include "Modifier/CsSpawnerModifierImpl.h"

#if WITH_EDITOR
#include "Singleton/CsGetManagerSingleton.h"
#include "Singleton/CsManager_Singleton.h"
#include "Managers/Spawner/CsGetManagerSpawner.h"
#endif // #if WITH_EDITOR

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsManager_Spawner)

// Cached
#pragma region

namespace NCManagerSpawner
{
	namespace NCached
	{
		namespace Str
		{
		}

		namespace Name
		{
		}
	}
}

#pragma endregion Cached

// static initializations
UCsManager_Spawner* UCsManager_Spawner::s_Instance;
bool UCsManager_Spawner::s_bShutdown = false;

UCsManager_Spawner::UCsManager_Spawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Singleton
#pragma region

#if WITH_EDITOR
/*static*/ UCsManager_Spawner* UCsManager_Spawner::Get(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerSpawner(InRoot)->GetManager_Spawner();
}
/*static*/ UCsManager_Spawner* UCsManager_Spawner::GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
{
	if (ICsGetManagerSpawner* GetManagerSpawner = GetSafe_GetManagerSpawner(Context, InRoot, Log))
		return GetManagerSpawner->GetManager_Spawner();
	return nullptr;
}

/*static*/ bool UCsManager_Spawner::IsValid(const UObject* InRoot /*=nullptr*/)
{
	return Get_GetManagerSpawner(InRoot)->GetManager_Spawner() != nullptr;
}

#endif // #if WITH_EDITOR

/*static*/ void UCsManager_Spawner::Init(UObject* InRoot, TSubclassOf<UCsManager_Spawner> ManagerSpawnerClass, UObject* InOuter /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSpawner* GetManagerSpawner = Get_GetManagerSpawner(InRoot);

	UCsManager_Spawner* Manager_Spawner = GetManagerSpawner->GetManager_Spawner();

	if (!Manager_Spawner)
	{
		Manager_Spawner = NewObject<UCsManager_Spawner>(InOuter ? InOuter : InRoot, ManagerSpawnerClass, TEXT("Manager_Spawner_Singleton"), RF_Transient | RF_Public);

		GetManagerSpawner->SetManager_Spawner(Manager_Spawner);

		Manager_Spawner->SetMyRoot(InRoot);
		Manager_Spawner->Initialize();
	}
	else
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("UCsManager_Spawner::Init: Init has already been called."));
	}
#else
	s_bShutdown = false;

	if (!s_Instance)
	{
		s_Instance = NewObject<UCsManager_Spawner>(GetTransientPackage(), ManagerSpawnerClass, TEXT("Manager_Spawner_Singleton"), RF_Transient | RF_Public);
		s_Instance->AddToRoot();
		s_Instance->SetMyRoot(InRoot);
		s_Instance->Initialize();
	}
	else
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("UCsManager_Spawner::Init: Init has already been called."));
	}
#endif // #if WITH_EDITOR
}

/*static*/ void UCsManager_Spawner::Shutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	ICsGetManagerSpawner* GetManagerSpawner = Get_GetManagerSpawner(InRoot);
	UCsManager_Spawner* Manager_Spawner	    = GetManagerSpawner->GetManager_Spawner();
	Manager_Spawner->CleanUp();

	GetManagerSpawner->SetManager_Spawner(nullptr);
#else
	if (!s_Instance)
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("UCsManager_Spawner::Shutdown: Manager has already been shutdown."));
		return;
	}

	s_Instance->CleanUp();
	s_Instance->RemoveFromRoot();
	s_Instance = nullptr;
	s_bShutdown = true;
#endif // #if WITH_EDITOR
}

/*static*/ bool UCsManager_Spawner::HasShutdown(const UObject* InRoot /*=nullptr*/)
{
#if WITH_EDITOR
	return Get_GetManagerSpawner(InRoot)->GetManager_Spawner() == nullptr;
#else
	return s_bShutdown;
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

/*static*/ ICsGetManagerSpawner* UCsManager_Spawner::Get_GetManagerSpawner(const UObject* InRoot)
{
	checkf(InRoot, TEXT("UCsManager_Spawner::Get_GetManagerSpawner: InRoot is NULL."));

	const ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

	checkf(GetManagerSingleton, TEXT("UCsManager_Spawner::Get_GetManagerSpawner: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

	UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

	checkf(Manager_Singleton, TEXT("UCsManager_Spawner::Get_GetManagerSpawner: Manager_Singleton is NULL."));

	ICsGetManagerSpawner* GetManagerSpawner = Cast<ICsGetManagerSpawner>(Manager_Singleton);

	checkf(GetManagerSpawner, TEXT("UCsManager_Spawner::Get_GetManagerSpawner: Manager_Singleton: %s with Class: %s does NOT implement interface: ICsGetManagerWeapon."), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

	return GetManagerSpawner;
}

/*static*/ ICsGetManagerSpawner* UCsManager_Spawner::GetSafe_GetManagerSpawner(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) /*=nullptr*/)
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
	return Cast<ICsGetManagerSpawner>(Manager_Singleton);
}

#endif // #if WITH_EDITOR

void UCsManager_Spawner::Initialize()
{
	SetupModifiers();

	bInitialized = true;
}

/*static*/ bool UCsManager_Spawner::HasInitialized(const UObject* InRoot)
{
	if (!HasShutdown(InRoot))
		return Get(InRoot)->bInitialized;
	return false;
}

void UCsManager_Spawner::CleanUp()
{
	for (CsSpawnerModifierManagerType& ModifierManager : Manager_Modifiers)
	{
		const TArray<CsSpawnerModifierResourceType*>& Containers = ModifierManager.GetPool();

		for (CsSpawnerModifierResourceType* Container : Containers)
		{
			CsSpawnerModifierType* M = Container->Get();
			delete M;
			Container->Set(nullptr);
		}
	}
	Manager_Modifiers.Reset();

	bInitialized = false;
}

	// Root
#pragma region

void UCsManager_Spawner::SetMyRoot(UObject* InRoot)
{
	MyRoot = InRoot;
}

#pragma endregion Root

#pragma endregion Singleton

// Modifier
#pragma region

void UCsManager_Spawner::SetupModifiers()
{
	Manager_Modifiers.Reset((uint8)CsSpawnerModifierImplType::EImpl_MAX);
	Manager_Modifiers.AddDefaulted((uint8)CsSpawnerModifierImplType::EImpl_MAX);

	const int32& PoolSize = 256;//Settings.Modifier.PoolSize;

	// Int
	{
		CsSpawnerModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)CsSpawnerModifierImplType::Int];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(CsSpawnerModifierImplType::Int));
		}
	}
	// Float
	{
		CsSpawnerModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)CsSpawnerModifierImplType::Float];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(CsSpawnerModifierImplType::Float));
		}
	}
	// Toggle
	{
		CsSpawnerModifierManagerType& ModifierManager = Manager_Modifiers[(uint8)CsSpawnerModifierImplType::Toggle];

		ModifierManager.CreatePool(PoolSize);

		for (int32 I = 0; I < PoolSize; ++I)
		{
			ModifierManager.Add(ConstructModifier(CsSpawnerModifierImplType::Toggle));
		}
	}

	ImplTypeByModifier.Reset(EMCsSpawnerModifier::Get().Num());
	ImplTypeByModifier.AddDefaulted(EMCsSpawnerModifier::Get().Num());

	// Movement
	ImplTypeByModifier[NCsSpawnerModifier::MovementSpeed.GetValue()]				  = CsSpawnerModifierImplType::Float;
	ImplTypeByModifier[NCsSpawnerModifier::SteeringSeparateForcePriority.GetValue()]  = CsSpawnerModifierImplType::Int;
	ImplTypeByModifier[NCsSpawnerModifier::SteeringSeparateForceRadius.GetValue()]	  = CsSpawnerModifierImplType::Float;
	// Collision
	ImplTypeByModifier[NCsSpawnerModifier::CollisionRadius.GetValue()]  = CsSpawnerModifierImplType::Float;
	ImplTypeByModifier[NCsSpawnerModifier::KnockbackEnabled.GetValue()] = CsSpawnerModifierImplType::Toggle;
	// Attack
	ImplTypeByModifier[NCsSpawnerModifier::AttackSpeed.GetValue()] = CsSpawnerModifierImplType::Float;
}

CsSpawnerModifierType* UCsManager_Spawner::ConstructModifier(const CsSpawnerModifierImplType& ImplType)
{
	// Int
	if (ImplType == CsSpawnerModifierImplType::Int)
		return new NCsSpawner::NModifier::FInt();
	// Float
	if (ImplType == CsSpawnerModifierImplType::Float)
		return new NCsSpawner::NModifier::FFloat();
	// Toggle
	if (ImplType == CsSpawnerModifierImplType::Toggle)
		return new NCsSpawner::NModifier::FToggle();
	check(0);
	return nullptr;
}

CsSpawnerModifierResourceType* UCsManager_Spawner::AllocateModifier(const FECsSpawnerModifier& Type)
{
	checkf(EMCsSpawnerModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Spawner::AllocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	return Manager_Modifiers[(uint8)GetModifierImplType(Type)].Allocate();
}

void UCsManager_Spawner::DeallocateModifier(const FString& Context, const FECsSpawnerModifier& Type, CsSpawnerModifierResourceType* Modifier)
{
	checkf(EMCsSpawnerModifier::Get().IsValidEnum(Type), TEXT("UCsManager_Spawner::DeallocateModifier: Type: %s is NOT Valid."), Type.ToChar());

	CS_IS_PTR_NULL_CHECKED(Modifier)

	// Reset
	if (ICsReset* IReset = CsSpawnerModifierLibrary::GetSafeInterfaceChecked<ICsReset>(Context, Modifier->Get()))
		IReset->Reset();

	Manager_Modifiers[(uint8)GetModifierImplType(Type)].Deallocate(Modifier);
}

const FECsSpawnerModifier& UCsManager_Spawner::GetModifierType(const FString& Context, const CsSpawnerModifierType* Modifier)
{
	const ICsGetSpawnerModifierType* GetSpawnerModifierType = CsSpawnerModifierLibrary::GetInterfaceChecked<ICsGetSpawnerModifierType>(Context, Modifier);
	const FECsSpawnerModifier& Type					        = GetSpawnerModifierType->GetSpawnerModifierType();

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, Type);

	return Type;
}

CsSpawnerModifierResourceType* UCsManager_Spawner::CreateCopyOfModifier(const FString& Context, const CsSpawnerModifierType* Modifier)
{
	const FECsSpawnerModifier& Type			 = GetModifierType(Context, Modifier);
	CsSpawnerModifierResourceType* Container = AllocateModifier(Type);
	CsSpawnerModifierType* Copy				 = Container->Get();

	typedef NCsSpawner::NModifier::NCopy::ICopy CopyType;

	CopyType* ICopy = CsSpawnerModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

	ICopy->Copy(Modifier);

	return Container;
}

CsSpawnerModifierResourceType* UCsManager_Spawner::CreateCopyOfModifier(const FString& Context, const CsSpawnerModifierResourceType* Modifier)
{
	return CreateCopyOfModifier(Context, Modifier->Get());
}

#pragma endregion Modifier