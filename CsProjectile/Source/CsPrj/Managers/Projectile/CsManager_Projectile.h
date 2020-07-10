// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
#include "Managers/Projectile/CsTypes_Projectile.h"
#include "Payload/CsProjectilePayload.h"
#include "Managers/Projectile/CsProjectile.h"
#include "Managers/Projectile/CsProjectilePooled.h"
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"
#include "CsManager_Projectile.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerProjectile_OnSpawn, const FECsProjectile&, Type, TScriptInterface<ICsProjectile>, Projectile);

#pragma endregion Delegates

// Internal
#pragma region

class ICsProjectile;

class CSPRJ_API FCsManager_Projectile_Internal : public TCsManager_PooledObject_Map<ICsProjectile, FCsProjectilePooled, ICsProjectilePayload, FECsProjectile>
{
private:

	typedef TCsManager_PooledObject_Map<ICsProjectile, FCsProjectilePooled, ICsProjectilePayload, FECsProjectile> Super;

public:

	FCsManager_Projectile_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsProjectile& Type) override
	{
		return Type.GetName();
	}
};

#pragma endregion Internal

class ICsGetManagerProjectile;
class ICsData_Projectile;
class UDataTable;
struct FCsInterfaceMap;
struct FCsData_ProjectileInterfaceMap;

UCLASS()
class CSPRJ_API UCsManager_Projectile : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

	static UCsManager_Projectile* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Projectile> ManagerProjectileClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerProjectile* Get_GetManagerProjectile(UObject* InRoot);
	static ICsGetManagerProjectile* GetSafe_GetManagerProjectile(UObject* Object);

	static UCsManager_Projectile* GetSafe(UObject* Object);

public:

	static UCsManager_Projectile* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Projectile* s_Instance;
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

	/** */
	FCsSettings_Manager_Projectile Settings;

	/** */
	TArray<FECsProjectile> TypeMapArray;

public:

	/**
	*
	*
	* @param InSettings
	*/ 
	FORCEINLINE void SetSettings(const FCsSettings_Manager_Projectile& InSettings)
	{
		Settings = InSettings;
	}

	/**
	* If SET,
	* - Get the type this Projectile has been mapped to for pooling.
	*   i.e. If the projectile is completely data driven, then many projectiles could share
	*   the same class.
	* If NOT set,
	* - Return the same type.
	*
	* @param Type
	* return Projectile Type 
	*/
	FORCEINLINE const FECsProjectile& GetTypeFromTypeMap(const FECsProjectile& Type)
	{
		return TypeMapArray[Type.GetValue()];
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of projectiles. */
	FCsManager_Projectile_Internal Internal;
	
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
	void InitInternal(const FCsManager_Projectile_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsProjectile& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TBaseDelegate<FCsProjectilePooled*, const FECsProjectile&>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsProjectilePooled* ConstructContainer(const FECsProjectile& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void, const FCsProjectilePooled*>& GetOnConstructObject_Event(const FECsProjectile& Type);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsProjectile.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsProjectile.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToPool(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsProjectile.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsProjectile or the UClass
	*  associated with the Object have ImplementsInterface(UCsProjectile::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToPool(const FECsProjectile& Type, UObject* Object);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsProjectile& Type, const FCsProjectilePooled* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsProjectile.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsProjectile.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsProjectile.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToAllocatedObjects(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsProjectile or the UClass
	*  associated with the Object have ImplementsInterface(UCsProjectile::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsProjectile.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsProjectile.
	*/
	const FCsProjectilePooled* AddToAllocatedObjects(const FECsProjectile& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsProjectile.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsProjectilePooled*>& GetPool(const FECsProjectile& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsProjectile.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsProjectilePooled*>& GetAllocatedObjects(const FECsProjectile& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsProjectile& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsProjectile& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsProjectile& Type);

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
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindObject(const FECsProjectile& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsPooledObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindObject(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsPooledObject or the UClass
	*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindObject(const FECsProjectile& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindSafeObject(const FECsProjectile& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindSafeObject(const FECsProjectile& Type, ICsProjectile* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsPooledObject.
	*/
	const FCsProjectilePooled* FindSafeObject(const FECsProjectile& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsProjectile CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsProjectile& Type);

	void OnUpdate_Object(const FECsProjectile& Type, const FCsProjectilePooled* Object);

	void OnPostUpdate_Pool(const FECsProjectile& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsProjectile& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual ICsProjectilePayload* ConstructPayload(const FECsProjectile& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsProjectilePayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsProjectilePayload.
	*/
	ICsProjectilePayload* AllocatePayload(const FECsProjectile& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsProjectilePayload.
	*
	* @param Context	Calling context.
	* @param Type		Type of payload.
	* return			Payload that implements the interface: ICsProjectilePayload.
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FString& Context, const FECsProjectile& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Context, Type);
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsProjectilePayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsProjectilePayload.
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FECsProjectile& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Type);
	}

	virtual ICsProjectilePayload* ScriptAllocatePayload(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload);

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
	const FCsProjectilePooled* Spawn(const FECsProjectile& Type, ICsProjectilePayload* Payload);

	/**
	*
	*/
	virtual const FCsProjectilePooled* ScriptSpawn(const FECsProjectile& Type, const FCsScriptProjectilePayload& ScriptPayload);

	/**
	* Delegate type after a Projectile has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsProjectile& /*Type*/, const FCsProjectilePooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerProjectile_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Projectile
	*/
	virtual bool Destroy(const FECsProjectile& Type, ICsProjectile* Projectile);

	virtual bool Destroy(ICsProjectile* Projectile);

	/**
	* Delegate type after a Projectile has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsProjectile& /*Type*/, const FCsProjectilePooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& Str);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsProjectilePooled* Object);

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

	// ICsProjectile
#pragma region
public:

	/** Delegate for getting the Owner of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectilePooled::FScript_GetOwner Script_GetOwner_Impl;

	/** Delegate for getting the Instigator of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FCsProjectilePooled::FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion ICsProjectile

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

#pragma endregion Script

// Data
#pragma region
public:

	virtual void PopulateDataMapFromSettings();

protected:
	/** <DataName, InterfacePtr> */
	TMap<FName, ICsData_Projectile*> EmulatedDataMap;

	/** <DataName, InterfaceMapPtr> */ 
	TMap<FName, FCsData_ProjectileInterfaceMap*> EmulatedDataInterfaceMap;

	/** <DataName, <InterfaceImplName, InterfaceImplPtr>> */
	TMap<FName, TMap<FName, void*>> EmulatedDataInterfaceImplMap;


	virtual void CreateEmulatedDataFromDataTable(UDataTable* DataTable, const TSet<FECsProjectileData>& EmulatedDataInterfaces);

protected:

	virtual void DeconstructEmulatedData(const FName& InterfaceImplName, void* Data);

public:

	/**
	*/
	template<typename InterfaceType>
	InterfaceType* GetEmulatedData(const FName& Name)
	{
		static_assert(std::is_abstract<InterfaceType>(), "UCsManager_Projectile::GetEmulatedData InterfaceType is NOT abstract.");
		
		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "UCsManager_Projectile::GetEmulatedData: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Name != NAME_None, TEXT("UCsManager_Projectile::GetEmulatedData: Name = None is NOT Valid."));

		FCsData_ProjectileInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap.Find(Name);

		checkf(EmulatedInterfaceMap, TEXT("UCsManager_Projectile::GetEmulatedData: EmulatedInterfaceMap is NULL. Failed to find InterfaceMap associated with %s."), *(Name.ToString()));

		FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("UCsManager_Projectile::GetEmulatedData: InterfaceMap is NULL. Interface failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));

		return InterfaceMap->Get<InterfaceType>();
	}

	/**
	*/
	template<typename InterfaceImplType>
	InterfaceImplType* GetEmulatedDataImpl(const FName& Name)
	{
		static_assert(!std::is_abstract<InterfaceImplType>(), "UCsManager_Projectile::GetEmulatedDataImpl InterfaceImplType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceImplType>(), "UCsManager_Projectile::GetEmulatedDataImpl: InterfaceImplType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Name != NAME_None, TEXT("UCsManager_Projectile::GetEmulatedDataImpl: Name = None is NOT Valid."));

		FCsData_ProjectileInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap.Find(Name);

		checkf(EmulatedInterfaceMap, TEXT("UCsManager_Projectile::GetEmulatedData: EmulatedInterfaceMap is NULL. Failed to find InterfaceMap associated with %s."), *(Name.ToString()));

		FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("UCsManager_Projectile::GetEmulatedData: InterfaceMap is NULL. Interface failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));

		return InterfaceMap->StaticCastChecked<InterfaceImplType>();
	}

protected:

	TMap<FName, ICsData_Projectile*> DataMap;

	void PopulateDataMapFromDataTable(UDataTable* DataTable);

public:

	/**
	*
	*
	* @param Name
	* return
	*/
	ICsData_Projectile* GetData(const FName& Name);

	/**
	*
	*
	* @param Type
	* return
	*/
	ICsData_Projectile* GetData(const FECsProjectile& Type);

private:

	UPROPERTY()
	TMap<FECsProjectile, UClass*> ClassMap;

	UPROPERTY()
	TArray<UDataTable*> DataTables;

	void OnPayloadUnloaded(const FName& Payload);

#pragma endregion Data
};