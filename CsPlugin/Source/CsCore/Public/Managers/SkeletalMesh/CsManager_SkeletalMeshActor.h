// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "UObject/Object.h"
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/SkeletalMesh/CsTypes_SkeletalMeshActor.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType.h"
// Managers
 #include "Managers/Pool/CsManager_PooledObject_Map.h"
// SkeletalMeshActor
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActor.h"
#include "Managers/SkeletalMesh/CsSkeletalMeshActor.h"
#include "Managers/SkeletalMesh/CsSkeletalMeshActorPooled.h"
#include "Managers/SkeletalMesh/CsSettings_Manager_SkeletalMeshActor.h"

#include "CsManager_SkeletalMeshActor.generated.h"
#pragma once

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerSkeletalMeshActor_OnSpawn, const FECsSkeletalMeshActor&, Type, TScriptInterface<ICsSkeletalMeshActor>, FXActor);

#pragma endregion Delegates

// Internal
#pragma region

class ICsSkeletalMeshActor;

namespace NCsSkeletalMeshActor
{
#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload

	class CSCORE_API FManager : public ManagerMapType<ICsSkeletalMeshActor, FCsSkeletalMeshActorPooled, PayloadType, FECsSkeletalMeshActor>
	{
	private:

		typedef ManagerMapType<ICsSkeletalMeshActor, FCsSkeletalMeshActorPooled, PayloadType, FECsSkeletalMeshActor> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsSkeletalMeshActor& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsSkeletalMeshActor& Type) const override
		{
			return EMCsSkeletalMeshActor::Get().IsValidEnum(Type);
		}
	};
#undef PayloadType
}

#pragma endregion Internal

class ICsGetManagerSkeletalMeshActor;
class ICsData_SkeletalMeshActor;
class UDataTable;

UCLASS()
class CSCORE_API UCsManager_SkeletalMeshActor : public UObject
{
	GENERATED_UCLASS_BODY()

#define ManagerType NCsSkeletalMeshActor::FManager
#define ManagerParamsType NCsSkeletalMeshActor::FManager::FParams
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_SkeletalMeshActor* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_SkeletalMeshActor* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR
	
	template<typename T>
	FORCEINLINE static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_SkeletalMeshActor> ManagerSoundClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerSkeletalMeshActor* Get_GetManagerSkeletalMeshActor(UObject* InRoot);
	static ICsGetManagerSkeletalMeshActor* GetSafe_GetManagerSkeletalMeshActor(UObject* Object);

	static UCsManager_SkeletalMeshActor* GetSafe(UObject* Object);

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
	static UCsManager_SkeletalMeshActor* s_Instance;
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

	FCsSettings_Manager_SkeletalMeshActor Settings;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_SkeletalMeshActor& InSettings)
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
	virtual void CreatePool(const FECsSkeletalMeshActor& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsSkeletalMeshActorPooled*(const FECsSkeletalMeshActor&)>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsSkeletalMeshActorPooled* ConstructContainer(const FECsSkeletalMeshActor& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void(const FCsSkeletalMeshActorPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsSkeletalMeshActor& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsSkeletalMeshActor& Type, const FCsSkeletalMeshActorPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsSkeletalMeshActor.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* AddToPool(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* AddToPool(const FECsSkeletalMeshActor& Type, const FCsSkeletalMeshActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsSkeletalMeshActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* AddToPool(const FECsSkeletalMeshActor& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsSkeletalMeshActor.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* AddToAllocatedObjects(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* AddToAllocatedObjects(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsSkeletalMeshActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* AddToAllocatedObjects(const FECsSkeletalMeshActor& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsSkeletalMeshActorPooled*>& GetPool(const FECsSkeletalMeshActor& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsSkeletalMeshActorPooled*>& GetAllocatedObjects(const FECsSkeletalMeshActor& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsSkeletalMeshActor& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsSkeletalMeshActor& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsSkeletalMeshActor& Type);

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
	*				Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* FindObject(const FECsSkeletalMeshActor& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsSkeletalMeshActor.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* FindObject(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsSkeletalMeshActor or the UClass
	*  associated with the Object have ImplementsInterface(UCsSoundPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* FindObject(const FECsSkeletalMeshActor& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsSkeletalMeshActorPooled* FindSafeObject(const FECsSkeletalMeshActor& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* FindSafeObject(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsSkeletalMeshActor.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsSkeletalMeshActor.
	*/
	const FCsSkeletalMeshActorPooled* FindSafeObject(const FECsSkeletalMeshActor& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsSkeletalMeshActor CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsSkeletalMeshActor& Type);

	void OnUpdate_Object(const FECsSkeletalMeshActor& Type, const FCsSkeletalMeshActorPooled* Object);

	void OnPostUpdate_Pool(const FECsSkeletalMeshActor& Type);

#pragma endregion Update

	// Pause
#pragma region
public:

	/**
	*/
	void Pause(const FECsUpdateGroup& Group, bool bPaused);

	/**
	*/
	void Pause(const FECsSkeletalMeshActor& Type, bool bPaused);

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
	void ConstructPayloads(const FECsSkeletalMeshActor& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual PayloadType* ConstructPayload(const FECsSkeletalMeshActor& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsSkeletalMeshActor::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsSkeletalMeshActor::NPayload::IPayload.
	*/
	PayloadType* AllocatePayload(const FECsSkeletalMeshActor& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsSkeletalMeshActor::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsSkeletalMeshActor::NPayload::IPayload.
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FECsSkeletalMeshActor& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Type);
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
	const FCsSkeletalMeshActorPooled* Spawn(const FECsSkeletalMeshActor& Type, PayloadType* Payload);

	/**
	* Delegate type after a Sound has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsSkeletalMeshActor& /*Type*/, const FCsSkeletalMeshActorPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerSkeletalMeshActor_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsSkeletalMeshActor& Type, ICsSkeletalMeshActor* Object);

	virtual bool Destroy(ICsSkeletalMeshActor* Object);

	/**
	* Delegate type after a Sound has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsSkeletalMeshActor& /*Type*/, const FCsSkeletalMeshActorPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& Str);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsSkeletalMeshActorPooled* Object);

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

	// ICsSkeletalMeshActor
#pragma region
public:

#pragma endregion ICsSkeletalMeshActor

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

#pragma endregion 

#pragma endregion Script

// Class
#pragma region
private:

	UPROPERTY()
	TMap<FECsSkeletalMeshActor, UClass*> ClassMap;

#pragma endregion Class

#undef ManagerType
#undef ManagerParamsType
#undef ConstructParamsType
#undef PayloadType
};