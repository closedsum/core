// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Managers
#include "Managers/Pool/CsManager_PooledObject_Map.h"
// Types
#include "Managers/Sound/CsTypes_SoundPooled.h"
#include "Managers/Time/CsTypes_Update.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_Sound.h"
#include "Managers/Sound/CsSoundPooled.h"
#include "Managers/Sound/CsSettings_Manager_Sound.h"

#include "CsManager_Sound.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerSound_OnSpawn, const FECsSound&, Type, TScriptInterface<ICsSoundPooled>, FXActor);

#pragma endregion Delegates

// Internal
#pragma region

class ICsSoundPooled;

namespace NCsSound
{
	namespace NManager
	{
		namespace NInternal
		{
			using PayloadType = NCsSound::NPayload::IPayload;
			using ManagerMapType = NCsPooledObject::NManager::TTMap<ICsSoundPooled, FCsSoundPooled, PayloadType, FECsSound>;
		
			class CSSOUND_API FManager : public ManagerMapType
			{
			private:

				using Super = ManagerMapType;

			public:

				FManager();

				FORCEINLINE virtual const FString& KeyTypeToString(const FECsSound& Type) const override
				{
					return Type.GetName();
				}

				FORCEINLINE virtual bool IsValidKey(const FECsSound& Type) const override
				{
					return EMCsSound::Get().IsValidEnum(Type);
				}
			};
		}
	}
}

#pragma endregion Internal

class ICsGetManagerSound;
class ICsData_Sound;
class UDataTable;

UCLASS()
class CSSOUND_API UCsManager_Sound : public UObject
{
	GENERATED_UCLASS_BODY()

private:	

	using ManagerType = NCsSound::NManager::NInternal::FManager;
	using ManagerParamsType = NCsSound::NManager::NInternal::FManager::FParams;
	using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
	using PayloadType = NCsSound::NPayload::IPayload;

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Sound* Get(UObject* InRoot = nullptr);
#else
	static UCsManager_Sound* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Sound* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Sound* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
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

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Sound> ManagerSoundClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerSound* Get_GetManagerSound(const UObject* InRoot);
	static ICsGetManagerSound* GetSafe_GetManagerSound(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Sound* s_Instance;
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

// Settings
#pragma region
protected:

	FCsSettings_Manager_Sound Settings;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_Sound& InSettings)
	{
		Settings = InSettings;
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of sounds. */
	ManagerType Internal;
	
	/**
	* Setup the internal manager for handling the pool of projectiles.
	*/
	virtual void SetupInternal();

public:

	/**
	*
	*/
	void InitInternalFromSettings();

	/**
	*
	*
	* @param Params
	*/
	void InitInternal(const ManagerParamsType& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsSound& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsSoundPooled*(const FECsSound&)>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsSoundPooled* ConstructContainer(const FECsSound& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void(const FCsSoundPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsSound& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsSound& Type, const FCsSoundPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsSoundPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsSoundPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* AddToPool(const FECsSound& Type, ICsSoundPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsSoundPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* AddToPool(const FECsSound& Type, const FCsSoundPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsSoundPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* AddToPool(const FECsSound& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsSoundPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsSoundPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* AddToAllocatedObjects(const FECsSound& Type, ICsSoundPooled* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsSoundPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* AddToAllocatedObjects(const FECsSound& Type, ICsSoundPooled* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsSoundPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* AddToAllocatedObjects(const FECsSound& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsSoundPooled.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsSoundPooled*>& GetPool(const FECsSound& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsSoundPooled.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsSoundPooled*>& GetAllocatedObjects(const FECsSound& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsSound& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsSound& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsSound& Type);

	// Find
#pragma region
public:

	/**
	* Find the container holding reference to a pooled object from the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* FindObject(const FECsSound& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsSoundPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* FindObject(const FECsSound& Type, ICsSoundPooled* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsSoundPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* FindObject(const FECsSound& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsSoundPooled* FindSafeObject(const FECsSound& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* FindSafeObject(const FECsSound& Type, ICsSoundPooled* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSoundPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSoundPooled.
	*/
	const FCsSoundPooled* FindSafeObject(const FECsSound& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
private:

	/** Whether TypesByUpdateGroup is used or not. */
	bool bTypesByUpdateGroup;

	TArray<TArray<FECsSound>> TypesByUpdateGroup;

public:

	/**
	* Update ALL sounds of ALL types (FECsSound) with DeltaTime.
	* 
	* @param DeltaTime
	*/
	void Update(const FCsDeltaTime& DeltaTime);

	/**
	* Update ALL sounds associated with Group (TypesByUpdateGroup[Group.GetValue()])
	* with DeltaTime
	* 
	* @param Group		UpdateGroup sounds are associated with.
	* @param DeltaTime
	*/
	void Update(const FECsUpdateGroup& Group, const FCsDeltaTime& DeltaTime);

	/**
	* Update ALL sounds of Type (FECsSound) with DeltaTime.
	* 
	* @param Type
	* @param DeltaTime
	*/
	void Update(const FECsSound& Type, const FCsDeltaTime& DeltaTime);

private:

	FECsSound CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsSound& Type);

	void OnUpdate_Object(const FECsSound& Type, const FCsSoundPooled* Object);

	void OnPostUpdate_Pool(const FECsSound& Type);

#pragma endregion Update

	// Pause
#pragma region
public:

	/**
	* Set the pause flag for ALL sounds associated with the Group (TypesByUpdateGroup[Group.GetValue()]).
	* 
	* @param Group
	* @param bPaused	True = pause. False = un-pause.
	*/
	void Pause(const FECsUpdateGroup& Group, bool bPaused);

	/**
	* Set th pause flag for ALL sounds associated with Type: (FECsSound).
	* 
	* @param Type
	* @param bPaused	True = pause. False = un-pause.
	*/
	void Pause(const FECsSound& Type, bool bPaused);

private:

	TMap<FECsUpdateGroup, FDelegateHandle> OnPauseHandleByGroupMap;

public:

	void BindToOnPause(const FECsUpdateGroup& Group);

#pragma endregion Pause

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Size
	*/
	void ConstructPayloads(const FECsSound& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual PayloadType* ConstructPayload(const FECsSound& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsSound::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsSound::NPayload::IPayload.
	*/
	PayloadType* AllocatePayload(const FECsSound& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsSound::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsSound::NPayload::IPayload.
	*/
	template<typename PayloadImplType>
	FORCEINLINE PayloadImplType* AllocatePayload(const FECsSound& Type)
	{
		return Internal.AllocatePayload<PayloadImplType>(Type);
	}

#pragma endregion Payload

	// Spawn
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Payload
	*/
	const FCsSoundPooled* Spawn(const FECsSound& Type, PayloadType* Payload);

	/**
	* Delegate type after a Sound has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsSound& /*Type*/, const FCsSoundPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerSound_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	virtual bool Destroy(const FECsSound& Type, ICsSoundPooled* Object);

	virtual bool Destroy(ICsSoundPooled* Object);

	/**
	* Delegate type after a Sound has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsSound& /*Type*/, const FCsSoundPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& Str);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsSoundPooled* Object);

#pragma endregion Log

#pragma endregion Internal

// Pool
#pragma region
protected:

	UPROPERTY()
	TArray<UObject*> Pool;

#pragma endregion Pool

// Script
#pragma region
public:

	// ICsSoundPooled
#pragma region
public:

#pragma endregion ICsSoundPooled

	// ICsPooledObject
#pragma region
public:

	/** Delegate for getting the Cache associated with a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

	/** Delegate called after allocating a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

	/** Delegate called after allocating a Pooled Object. 
		 The Pooled Object implements a script interface of type: ICsPooledObject.*/
	FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

#pragma endregion ICsPooledObject

	// ICsUpdate
#pragma region
public:

	/** Delegate for updating a Pooled Object.
		The Pooled Object implements a script interface of type: ICsPooledObject. */
	FCsPooledObject::FScript_Update Script_Update_Impl;

#pragma endregion ICsUpdate

	// ICsOnConstructObject
#pragma region

	/** Delegate to execute after an object has been constructed.
		 The object implements a script interface of type: ICsOnConstructObject. */
	FCsPooledObject::FScript_OnConstructObject Script_OnConstructObject_Impl;

#pragma endregion ICsOnConstructObject

#pragma endregion Script

// Data
#pragma region
protected:

	TMap<FName, ICsData_Sound*> DataMap;

public:

	virtual void PopulateDataMapFromSettings();

	virtual void DeconstructData(ICsData_Sound* Data);

	ICsData_Sound* GetData(const FName& Name);

private:

	UPROPERTY()
	TMap<FECsSound, UClass*> ClassMap;

	UPROPERTY()
	TArray<UDataTable*> DataTables;

#pragma endregion Data
};