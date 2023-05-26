// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Spawner/Modifier/Types/CsTypes_SpawnerModifier.h"
// Pool
#include "Managers/Pool/CsManager_PooledObject_Map.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"
// Spawner
#include "Spawner/Modifier/CsResource_SpawnerModifier.h"

#include "CsManager_Spawner.generated.h"

class ICsGetManagerSpawner;
class UWorld;

UCLASS()
class CSCORE_API UCsManager_Spawner : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Spawner* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Spawner* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR
	
	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Spawner* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Spawner* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static bool IsValid(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? false : s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Spawner> ManagerSpawnerClass, UObject* InOuter = nullptr);
	
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerSpawner* Get_GetManagerSpawner(const UObject* InRoot);
	static ICsGetManagerSpawner* GetSafe_GetManagerSpawner(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(const UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Spawner* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Modifier
#pragma region

#define ModifierResourceType NCsSpawner::NModifier::FResource
#define ModifierManagerType NCsSpawner::NModifier::FManager
#define ModifierType NCsSpawner::NModifier::IModifier
#define ModifierImplType NCsSpawner::NModifier::EImpl

protected:

	TArray<ModifierManagerType> Manager_Modifiers;

	TArray<ModifierImplType> ImplTypeByModifier;

	FORCEINLINE const ModifierImplType& GetModifierImplType(const FECsSpawnerModifier& Type) const
	{
		return ImplTypeByModifier[Type.GetValue()];
	}

	void SetupModifiers();

	ModifierType* ConstructModifier(const ModifierImplType& ImplType);

public:

	ModifierResourceType* AllocateModifier(const FECsSpawnerModifier& Type);

	void DeallocateModifier(const FString& Context, const FECsSpawnerModifier& Type, ModifierResourceType* Modifier);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual const FECsSpawnerModifier& GetModifierType(const FString& Context, const ModifierType* Modifier);

	ModifierResourceType* CreateCopyOfModifier(const FString& Context, const ModifierType* Modifier);

	ModifierResourceType* CreateCopyOfModifier(const FString& Context, const ModifierResourceType* Modifier);

#undef ModifierResourceType
#undef ModifierManagerType
#undef ModifierType
#undef ModifierImplType

#pragma endregion Modifier
};