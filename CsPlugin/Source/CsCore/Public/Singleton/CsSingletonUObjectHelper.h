// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

template<typename SingletonType, typename GetSingletonType>
class FCsSingletonUObjectHelper
{
public:

	struct FCsSingletonUObjectHelperParams
	{
	public:

		FString SingletonName;

		FString Get;
		FString Init;
		FString Shutdown;
		FString Get_GetSingleton;

		SingletonType* (GetSingletonType::*GetSingleton)() const;
		void (GetSingletonType::*SetSingleton)(SingletonType*);

		FCsSingletonUObjectHelperParams() :
			SingletonName(),
			Get(),
			Init(),
			Shutdown(),
			Get_GetSingleton(),
			GetSingleton(nullptr),
			SetSingleton(nullptr)
		{
		}
	};

private:

	static SingletonType* s_Instance;
	static bool s_bShutdown;
	static FCsSingletonUObjectHelperParams s_Params;

public:

	static SingletonType* Get(SingletonType* (GetSingletonType::*GetSingleton), UObject* InRoot /*=nullptr*/)
	{
#if WITH_EDITOR
		GetSingletonType* GetSingletonInterface = Get_GetSingleton<SingletonType, GetSingletonType>(InRoot);
		return GetSingletonInterface->*GetSingleton();
#else
		if (s_bShutdown)
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Get: Manager has already shutdown."));
			return nullptr;
		}
		return s_Instance;
#endif // #if WITH_EDITOR
	}

	static bool IsValid(UObject* InRoot /*=nullptr*/)
	{
#if WITH_EDITOR
		GetSingletonType* GetSingleton = Get_GetSingleton<SingletonType, GetSingletonType>(InRoot);
		return (GetSingleton->*(s_Params.GetSingleton))() != nullptr;
#else
		return s_Instance != nullptr;
#endif // #if WITH_EDITOR
	}

	static void Init(const FCsSingletonUObjectHelperParams* Params, UObject* InRoot, TSubclassOf<SingletonType> SingletonClass, UObject* InOuter /*=nullptr*/)
	{
		s_Params = Params;

#if WITH_EDITOR
		GetSingletonType* GetSingleton = Get_GetSingleton(InRoot);
		SingletonType* Singleton	   = (GetSingleton->*(s_Params.GetSingleton))();

		if (!Singleton)
		{
			Singleton = NewObject<SingletonType>(InOuter ? InOuter : InRoot, SingletonClass, *(s_Params.SingletonName), RF_Transient | RF_Public);

			(GetSingleton->*(s_Params.SetSingleton))(Singleton);

			Singleton->SetMyRoot(InRoot);
			Singleton->Initialize();
		}
		else
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
		}
#else
		s_bShutdown = false;

		if (!s_Instance)
		{
			s_Instance = NewObject<SingletonType>(GetTransientPackage(), SingletonClass, *(s_Params.SingletonName), RF_Transient | RF_Public);
			s_Instance->AddToRoot();
			s_Instance->SetMyRoot(InRoot);
			s_Instance->Initialize();
		}
		else
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Init: Init has already been called."));
		}
#endif // #if WITH_EDITOR
	}

	static void Shutdown(UObject* InRoot /*=nullptr*/)
	{
#if WITH_EDITOR
		GetSingletonType* GetSingleton = Get_GetSingleton(InRoot);
		SingletonType* Singleton	   = (GetSingleton->*(s_Params.GetSingleton))();
		Singleton->CleanUp();

		(GetSingleton->*(s_Params.SetSingleton))(nullptr);
#else
		if (!s_Instance)
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::Shutdown: Manager has already been shutdown."));
			return;
		}

		s_Instance->CleanUp();
		s_Instance->RemoveFromRoot();
		s_Instance = nullptr;
		s_bShutdown = true;
#endif // #if WITH_EDITOR
	}

	static bool HasShutdown(UObject* InRoot /*=nullptr*/)
	{
#if WITH_EDITOR
		GetSingletonType* GetSingleton = Get_GetSingleton<SingletonType, GetSingletonType>(InRoot);
		return (GetSingleton->*(s_Params.GetSingleton))() == nullptr;
#else
		return s_bShutdown;
#endif // #if WITH_EDITOR
	}

#if WITH_EDITOR

	template<typename SingletonType, typename GetSingletonType>
	static GetSingletonType* Get_GetSingleton(UObject* InRoot)
	{
		checkf(InRoot, TEXT("%s: InRoot is NULL."), *(s_Params.Get_GetSingleton));

		ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(InRoot);

		checkf(GetManagerSingleton, TEXT("%s: InRoot: %s with Class: %s does NOT implement interface: ICsGetManagerSingleton."), *(s_Params.Get_GetSingleton), *(InRoot->GetName()), *(InRoot->GetClass()->GetName()));

		UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

		checkf(Manager_Singleton, TEXT("%s: Manager_Singleton is NULL."), *(s_Params.Get_GetSingleton));

		GetSingletonType* GetSingleton = Cast<GetSingletonType>(Manager_Singleton);

		checkf(GetSingleton, TEXT("%s: Manager_Singleton: %s with Class: %s does NOT implement interface: GetSingletonType."), *(s_Params.Get_GetSingleton), *(Manager_Singleton->GetName()), *(Manager_Singleton->GetClass()->GetName()));

		return GetSingleton;
	}

	static GetSingletonType* GetSafe_GetSingleton(UObject* Object)
	{
		if (!Object)
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Object is NULL."));
			return nullptr;
		}

		ICsGetManagerSingleton* GetManagerSingleton = Cast<ICsGetManagerSingleton>(Object);

		if (!GetManagerSingleton)
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Object: %s does NOT implement the interface: ICsGetManagerSingleton."), *(Object->GetName()));
			return nullptr;
		}

		UCsManager_Singleton* Manager_Singleton = GetManagerSingleton->GetManager_Singleton();

		if (!Manager_Singleton)
		{
			//UE_LOG(LogCs, Warning, TEXT("UCsManager_Damage::GetSafe_GetManagerDamage: Failed to get object of type: UCsManager_Singleton from Object: %s."), *(Object->GetName()));
			return nullptr;
		}

		return Cast<GetSingletonType>(Manager_Singleton);
	}

	static SingletonType* GetSafe(UObject* Object)
	{
		if (GetSingletonType* GetSingleton = GetSafe_GetSingleton(Object))
			return (GetSingleton->*(s_Params.GetSingleton))();
		return nullptr;
	}

#endif // #if WITH_EDITOR
};

template<typename SingletonType, typename GetSingletonType>
SingletonType* FCsSingletonUObjectHelper<SingletonType, GetSingletonType>::s_Instance;

template<typename SingletonType, typename GetSingletonType>
bool FCsSingletonUObjectHelper<SingletonType, GetSingletonType>::s_bShutdown;

template<typename SingletonType, typename GetSingletonType>
FCsSingletonUObjectHelper<SingletonType, GetSingletonType>::FCsSingletonUObjectHelperParams FCsSingletonUObjectHelper<SingletonType, GetSingletonType>::s_Params;