// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
#include "Payload/CsWeaponPayload.h"
#include "CsWeapon.h"
#include "CsWeaponPooled.h"
#include "Managers/Weapon/CsSettings_Manager_Weapon.h"
#include "CsManager_Weapon.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerWeapon_OnSpawn, const FECsWeapon&, Type, TScriptInterface<ICsWeapon>, Weapon);

#pragma endregion Delegates

// Internal
#pragma region

class ICsWeapon;

class CSWP_API FCsManager_Weapon_Internal : public TCsManager_PooledObject_Map<ICsWeapon, FCsWeaponPooled, ICsWeaponPayload, FECsWeapon>
{
private:

	typedef TCsManager_PooledObject_Map<ICsWeapon, FCsWeaponPooled, ICsWeaponPayload, FECsWeapon> Super;

public:

	FCsManager_Weapon_Internal();

	FORCEINLINE virtual const FString& KeyTypeToString(const FECsWeapon& Type) override
	{
		return Type.GetName();
	}
};

#pragma endregion Internal

class ICsGetManagerWeapon;
class UWorld;
class ICsData_Weapon;
struct FCsData_WeaponInterfaceMap;
class UDataTable;
struct FCsWeaponPtr;
struct FCsProjectileWeaponPtr;

UCLASS()
class CSWP_API UCsManager_Weapon : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

// Singleton
#pragma region
public:

	static UCsManager_Weapon* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Weapon> ManagerWeaponClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerWeapon* Get_GetManagerWeapon(UObject* InRoot);
	static ICsGetManagerWeapon* GetSafe_GetManagerWeapon(UObject* Object);

	static UCsManager_Weapon* GetSafe(UObject* Object);

public:

	static UCsManager_Weapon* GetFromWorldContextObject(const UObject* WorldContextObject);

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
	static UCsManager_Weapon* s_Instance;
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

	FCsSettings_Manager_Weapon Settings;

	/** */
	TArray<FECsWeapon> TypeMapArray;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_Weapon& InSettings)
	{
		Settings = InSettings;
	}

		/**
	* If SET,
	* - Get the type this Weapon has been mapped to for pooling.
	*   i.e. If the weapon is completely data driven, then many weapons could share
	*   the same class.
	* If NOT set,
	* - Return the same type.
	*
	* @param Type
	* return Weapon Type 
	*/
	FORCEINLINE const FECsWeapon& GetTypeFromTypeMap(const FECsWeapon& Type)
	{
		return TypeMapArray[Type.GetValue()];
	}

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of projectiles. */
	FCsManager_Weapon_Internal Internal;
	
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
	void InitInternal(const FCsManager_Weapon_Internal::FCsManagerPooledObjectMapParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsWeapon& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TBaseDelegate<FCsWeaponPooled*, const FECsWeapon&>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsWeaponPooled* ConstructContainer(const FECsWeapon& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void, const FCsWeaponPooled*, const FCsManagerPooledObjectConstructParams&>& GetOnConstructObject_Event(const FECsWeapon& Type);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsWeapon.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsWeapon.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* AddToPool(const FECsWeapon& Type, ICsWeapon* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsWeapon.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* AddToPool(const FECsWeapon& Type, const FCsWeaponPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsWeapon or the UClass
	*  associated with the Object have ImplementsInterface(UCsWeapon::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* AddToPool(const FECsWeapon& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsWeapon.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsWeapon.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* AddToAllocatedObjects(const FECsWeapon& Type, ICsWeapon* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsWeapon.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* AddToAllocatedObjects(const FECsWeapon& Type, ICsWeapon* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsWeapon or the UClass
	*  associated with the Object have ImplementsInterface(UCsWeapon::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* AddToAllocatedObjects(const FECsWeapon& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsWeapon.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsWeaponPooled*>& GetPool(const FECsWeapon& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsWeapon.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsWeaponPooled*>& GetAllocatedObjects(const FECsWeapon& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsWeapon& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsWeapon& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsWeapon& Type);

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
	*				Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* FindObject(const FECsWeapon& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsWeapon.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* FindObject(const FECsWeapon& Type, ICsWeapon* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsWeapon or the UClass
	*  associated with the Object have ImplementsInterface(UCsWeapon::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* FindObject(const FECsWeapon& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* FindSafeObject(const FECsWeapon& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* FindSafeObject(const FECsWeapon& Type, ICsWeapon* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsWeapon.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsWeapon.
	*/
	const FCsWeaponPooled* FindSafeObject(const FECsWeapon& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsWeapon CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsWeapon& Type);

	void OnUpdate_Object(const FECsWeapon& Type, const FCsWeaponPooled* Object);

	void OnPostUpdate_Pool(const FECsWeapon& Type);

#pragma endregion Update

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsWeapon& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual ICsWeaponPayload* ConstructPayload(const FECsWeapon& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: ICsWeaponPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: ICsWeaponPayload.
	*/
	ICsWeaponPayload* AllocatePayload(const FECsWeapon& Type);

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
	const FCsWeaponPooled* Spawn(const FECsWeapon& Type, ICsWeaponPayload* Payload);

	/**
	* Delegate type after a Weapon has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsWeapon& /*Type*/, const FCsWeaponPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerWeapon_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Weapon
	* return
	*/
	virtual bool Destroy(const FECsWeapon& Type, ICsWeapon* Weapon);

	virtual bool Destroy(ICsWeapon* Weapon);

	/**
	* Delegate type after a Weapon has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsWeapon& /*Type*/, const FCsWeaponPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& Str);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsWeaponPooled* Object);

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

	// ICsWeapon
#pragma region
public:

	/** Delegate for getting the Data of type: ICsData_Weapon a Weapon is using. 
		 The Projectile implements a script interface of type: ICsWeapon. */
	FCsWeaponPooled::FScript_GetData Script_GetData_Impl;

	/** Delegate for getting the current state of a Weapon. 
		 The Weapon implements a script interface of type: ICsWeapon. */
	FCsWeaponPooled::FScript_GetCurrentState Script_GetCurrentState_Impl;

#pragma endregion ICsWeapon

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

// Class
#pragma region
protected:

	// <Weapon (type), Weapon Class>
	TMap<FName, FCsWeapon> WeaponClassByTypeMap;

	void GetWeaponClassesDataTableChecked(const FString& Context, UDataTable*& OutDataTable, TSoftObjectPtr<UDataTable>& OutDataTableSoftObject);

	void PopulateClassMapFromSettings();

	// <Weapon Class (type), Weapon Class>
	TMap<FName, FCsWeapon> WeaponClassByClassTypeMap;

public:

/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon Type.
	*
	* @param Type	Type of the weapon.
	* return		Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeapon* GetWeapon(const FECsWeapon& Type);

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Type of the weapon.
	* return			Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeapon* GetWeaponChecked(const FString& Context, const FECsWeapon& Type);

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon class Type.
	*
	* @param Type	Class type of the weapon.
	* return		Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeapon* GetWeapon(const FECsWeaponClass& Type);

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the weapon.
	* return			Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeapon* GetWeaponChecked(const FString& Context, const FECsWeaponClass& Type);

protected:

	void ResetClassContainers();

#pragma endregion Class

// Data
#pragma region
protected:

	/** <DataName, InterfacePtr> */
	TMap<FName, ICsData_Weapon*> EmulatedDataMap;

	/** <DataName, InterfaceMapPtr> */
	TMap<FName, FCsData_WeaponInterfaceMap*> EmulatedDataInterfaceMap;

	/** <DataName, <InterfaceImplName, InterfaceImplPtr>> */
	TMap<FName, TMap<FName, void*>> EmulatedDataInterfaceImplMap;

public:

	void PopulateDataMapFromSettings();

protected:

	virtual void CreateEmulatedDataFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject, const TSet<FECsWeaponData>& EmulatedDataInterfaces);

	virtual void DeconstructEmulatedData(const FName& InterfaceImplName, void* Data);

public:

	/**
	*/
	template<typename InterfaceType>
	InterfaceType* GetEmulatedData(const FName& Name)
	{
		static_assert(std::is_abstract<InterfaceType>(), "UCsManager_Weapon::GetEmulatedData InterfaceType is NOT abstract.");
		
		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceType>(), "UCsManager_Weapon::GetEmulatedData: InterfaceType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Name != NAME_None, TEXT("UCsManager_Weapon::GetEmulatedData: Name = None is NOT Valid."));

		FCsData_ProjectileInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap.Find(Name);

		checkf(EmulatedInterfaceMap, TEXT("UCsManager_Weapon::GetEmulatedData: EmulatedInterfaceMap is NULL. Failed to find InterfaceMap associated with %s."), *(Name.ToString()));

		FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("UCsManager_Weapon::GetEmulatedData: InterfaceMap is NULL. Interface failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));

		return InterfaceMap->Get<InterfaceType>();
	}

	/**
	*/
	template<typename InterfaceImplType>
	InterfaceImplType* GetEmulatedDataImpl(const FName& Name)
	{
		static_assert(!std::is_abstract<InterfaceImplType>(), "UCsManager_Weapon::GetEmulatedDataImpl InterfaceImplType is NOT abstract.");

		static_assert(std::is_base_of<ICsGetInterfaceMap, InterfaceImplType>(), "UCsManager_Weapon::GetEmulatedDataImpl: InterfaceImplType is NOT a child of: ICsGetInterfaceMap.");

		checkf(Name != NAME_None, TEXT("UCsManager_Weapon::GetEmulatedDataImpl: Name = None is NOT Valid."));

		FCsData_ProjectileInterfaceMap* EmulatedInterfaceMap = EmulatedDataInterfaceMap.Find(Name);

		checkf(EmulatedInterfaceMap, TEXT("UCsManager_Weapon::GetEmulatedData: EmulatedInterfaceMap is NULL. Failed to find InterfaceMap associated with %s."), *(Name.ToString()));

		FCsInterfaceMap* InterfaceMap = EmulatedInterfaceMap->GetInterfaceMap();

		checkf(InterfaceMap, TEXT("UCsManager_Weapon::GetEmulatedData: InterfaceMap is NULL. Interface failed to propertly implement method: GetInterfaceMap for interface: ICsGetInterfaceMap."));

		return InterfaceMap->StaticCastChecked<InterfaceImplType>();
	}

protected:

	// <EntryName, Data>
	TMap<FName, ICsData_Weapon*> DataMap;

	TArray<UDataTable*> DataTables;

	// <Path, <RowName, RowPtr>>
	TMap<FSoftObjectPath, TMap<FName, uint8*>> DataTableRowByPathMap;

	void PopulateDataMapFromDataTable(UDataTable* DataTable, const TSoftObjectPtr<UDataTable>& DataTableSoftObject);

public:

	/**
	* Get the Data (implements interface: ICsData_Weapon) associated with Name of the weapon type.
	*
	* @param Name	Name of the Weapon.
	* return		Data that implements the interface: ICsData_Weapon.
	*/
	ICsData_Weapon* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: ICsData_Weapon) associated with Type.
	*
	* @param Type	Weapon type.
	* return		Data that implements the interface: ICsData_Weapon.
	*/
	ICsData_Weapon* GetData(const FECsWeapon& Type);

	/**
	* Get the Data (implements interface: ICsData_Weapon) associated with Name of the weapon type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Weapon.
	* return			Data that implements the interface: ICsData_Weapon.
	*/
	ICsData_Weapon* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: ICsData_Weapon) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Weapon type.
	* return			Data that implements the interface: ICsData_Weapon.
	*/
	ICsData_Weapon* GetDataChecked(const FString& Context, const FECsWeapon& Type);

protected:

	void ResetDataContainers();

	void OnPayloadUnloaded(const FName& Payload);

#pragma endregion Data
};