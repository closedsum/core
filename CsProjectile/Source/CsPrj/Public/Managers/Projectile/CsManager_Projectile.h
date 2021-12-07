// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Managers
#include "Managers/Pool/CsManager_PooledObject_Map.h"
#include "Managers/Resource/CsManager_ResourceValueType.h"
// Types
#include "Types/CsTypes_Projectile.h"
// Projectile
#include "Payload/CsPayload_Projectile.h"
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

namespace NCsProjectile
{
#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsProjectile::NPayload::IPayload

	class CSPRJ_API FManager : public ManagerMapType<ICsProjectile, FCsProjectilePooled, PayloadType, FECsProjectile>
	{
	private:

		typedef ManagerMapType<ICsProjectile, FCsProjectilePooled, PayloadType, FECsProjectile> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsProjectile& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsProjectile& Type) const override
		{
			return EMCsProjectile::Get().IsValidEnum(Type);
		}
	};

#undef PayloadType
}

#pragma endregion Internal

class ICsGetManagerProjectile;
class UDataTable;

// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)
// NCsProjectile::NPayload::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, FInterfaceMap)

// NCsPooledObject::NManager::NHandler::TClass
namespace NCsPooledObject {
	namespace NManager {
		namespace NHandler {
			template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumType>
			class TClass; } } }

// NCsPooledObject::NManager::NHandler::TData
namespace NCsPooledObject {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData; } } }

struct FCsInterfaceMap;

// NCsProjectile::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, FInterfaceMap)

UCLASS()
class CSPRJ_API UCsManager_Projectile : public UObject
{
	GENERATED_UCLASS_BODY()

#define ManagerType NCsProjectile::FManager
#define ManagerParamsType NCsProjectile::FManager::FParams
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define PayloadType NCsProjectile::NPayload::IPayload
#define ClassHandlerType NCsPooledObject::NManager::NHandler::TClass
#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
#define DataType NCsProjectile::NData::IData

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Projectile * Get(UObject * InRoot = nullptr);
#else
FORCEINLINE static UCsManager_Projectile* Get(UObject* InRoot = nullptr)
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
	static bool IsValid(UObject* InRoot = nullptr);
#else
	FORCEINLINE static bool IsValid(UObject* InRoot = nullptr)
	{
		return s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

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

	bool bInitialized;

	virtual void Initialize();

public:

	static bool HasInitialized(UObject* InRoot);

protected:

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

	/** General Idea: Pool Sharing via Mapping of Types.
		Describes the mapping of a Projectile type to underlying Projectile type
		in terms the pool of Projectiles.

		i.e. From -> To
			 TypeMapArray[From] = To.

		i.e. If Type 'A' is mapped to Type 'B' (TypeMapArray[A] = B), then
			 when a Projectile of type 'A' is spawned it will be allocated from
			 the pool of Projectile of type 'B'.

		The idea behind behind this mapping is Projectiles of a different type may
		not have underlying code differences and just be differences in the data
		each respective character type uses. This provides the ability to save on both
		the number of pools created and the number of objects created for a pool. */
	TArray<FECsProjectile> TypeMapArray;

public:

	FORCEINLINE const TArray<FECsProjectile>& GetTypeMapArray() const { return TypeMapArray; }

protected:

	/** Used for faster lookup to see what types (Froms) are mapped to a particular type (To).
		To -> [Froms]
		TypeMapToArray[To] = [Froms] */
	TArray<TArray<FECsProjectile>> TypeMapToArray;

public:

	FORCEINLINE const TArray<TArray<FECsProjectile>>& GetTypeMapToArray() const { return TypeMapToArray; }

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
		check(EMCsProjectile::Get().IsValidEnum(Type));

		return TypeMapArray[Type.GetValue()];
	}

	void SetAndAddTypeMapKeyValue(const FECsProjectile& Key, const FECsProjectile& Value);

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of projectiles. */
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
	virtual void CreatePool(const FECsProjectile& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsProjectilePooled*(const FECsProjectile&)>& GetConstructContainer_Impl();

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
	TMulticastDelegate<void(const FCsProjectilePooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsProjectile& Type);

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
private:

	/** Whether TypesByUpdateGroup is used or not. */
	bool bTypesByUpdateGroup;

	TArray<TArray<FECsProjectile>> TypesByUpdateGroup;

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
	* Update ALL sounds of Type (FECsProjectile) with DeltaTime.
	*
	* @param Type
	* @param DeltaTime
	*/
	void Update(const FECsProjectile& Type, const FCsDeltaTime& DeltaTime);

private:

	FECsProjectile CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsProjectile& Type);

	void OnUpdate_Object(const FECsProjectile& Type, const FCsProjectilePooled* Object);

	void OnPostUpdate_Pool(const FECsProjectile& Type);

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
	* Set th pause flag for ALL sounds associated with Type: (FECsProjectile).
	*
	* @param Type
	* @param bPaused	True = pause. False = un-pause.
	*/
	void Pause(const FECsProjectile& Type, bool bPaused);

private:

	TMap<FECsUpdateGroup, FDelegateHandle> OnPauseHandleByGroupMap;

public:

	void BindToOnPause(const FECsUpdateGroup& Group);

#pragma endregion Pause

	// Payload
#pragma region
protected:

	/** <InterfaceMapPtr> */
	TArray<NCsProjectile::NPayload::FInterfaceMap*> PayloadInterfaceMaps;

	/** <InterfaceImpName, <InterfaceImplPtr>> 
		 stores all interface "slices" related to payload and projectile but 
		 NOT the interface stored in Internal (i.e. NCsProjectile::NPayload::FImplSlice) 
		 as Internal handles the deconstruction of that interface. */
	TMap<FName, TArray<void*>> PayloadInterfaceImplMap;

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
	virtual PayloadType* ConstructPayload(const FECsProjectile& Type);

protected:

	virtual void DeconstructPayloadSlice(const FName& InterfaceImplName, void* Data);

public:

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsProjectile::NPayload::IPayload).
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: PayloadType (NCsProjectile::NPayload::IPayload).
	*/
	PayloadType* AllocatePayload(const FECsProjectile& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsProjectile::NPayload::IPayload).
	*
	* @param Context	Calling context.
	* @param Type		Type of payload.
	* return			Payload that implements the interface: PayloadType (NCsProjectile::NPayload::IPayload).
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FString& Context, const FECsProjectile& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Context, Type);
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsProjectile::NPayload::IPayload).
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: PayloadType (NCsProjectile::NPayload::IPayload).
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FECsProjectile& Type)
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
	const FCsProjectilePooled* Spawn(const FECsProjectile& Type, PayloadType* Payload);

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

// Class
#pragma region
protected:

	ClassHandlerType<FCsProjectilePooled, FCsProjectilePtr, FECsProjectileClass>* ClassHandler;

	virtual void ConstructClassHandler();

public:

	/**
	* Get the Projectile container (Interface (ICsProjectile), UObject, and / or UClass) associated
	* with the projectile Type.
	*
	* @param Type	Type of the projectile.
	* return		Projectile container (Interface (ICsProjectile), UObject, and / or UClass).
	*/
	FCsProjectilePooled* GetProjectile(const FECsProjectile& Type);

	/**
	* Get the Projectile container (Interface (ICsProjectile), UObject, and / or UClass) associated
	* with the projectile class Type.
	*
	* @param Type	Class type of the projectile.
	* return		Projectile container (Interface (ICsProjectile), UObject, and / or UClass).
	*/
	FCsProjectilePooled* GetProjectile(const FECsProjectileClass& Type);

	/**
	* Get the Projectile container (Interface (ICsProjectile), UObject, and / or UClass) associated
	* with the projectile class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the projectile.
	* return			Projectile container (Interface (ICsProjectile), UObject, and / or UClass).
	*/
	FCsProjectilePooled* GetProjectileChecked(const FString& Context, const FECsProjectileClass& Type);

#pragma endregion Class

// Data
#pragma region
protected:

#define DataInterfaceMapType NCsProjectile::NData::FInterfaceMap

	DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* DataHandler;

	virtual void ConstructDataHandler();

public:

	FORCEINLINE DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* GetDataHandler() const { return DataHandler; }

#undef DataInterfaceMapType

	/**
	* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Name of the projectile type.
	*
	* @param Name	Name of the Projectile.
	* return		Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	DataType* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Name of the projectile type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Projectile.
	* return			Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Safely get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Name of the weapon type.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Weapon.
	* return			Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Type.
	*
	* @param Type	Projectile type.
	* return		Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	DataType* GetData(const FECsProjectile& Type);

	/**
	* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Projectile type.
	* return			Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsProjectile& Type);

	/**
	* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Type.
	*
	* @param Context	The calling context.
	* @param Type		Weapon type.
	* return			Data that implements the interface: DataType (NCsProjectile::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FECsProjectile& Type);

	void OnPayloadUnloaded(const FName& Payload);

#pragma endregion Data

#undef ManagerType
#undef ManagerParamsType
#undef ConstructParamsType
#undef PayloadType
#undef ClassHandlerType
#undef DataHandlerType
#undef DataType
};