// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Types
#include "Modifier/Types/CsTypes_WeaponModifier.h"
// Pool
#include "Managers/Pool/CsManager_PooledObject_Map.h"
// Settings
 #include "Managers/Weapon/CsSettings_Manager_Weapon.h"
// Weapon
#include "Payload/CsPayload_Weapon.h"
#include "CsWeapon.h"
#include "CsWeaponPooled.h"
#include "CsWeaponClass.h"
#include "Modifier/CsResource_WeaponModifier.h"
#include "Projectile/Params/Spread/CsProjectileWeapon_Spread_Variables.h"

#include "CsManager_Weapon.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerWeapon_OnSpawn, const FECsWeapon&, Type, TScriptInterface<ICsWeapon>, Weapon);

#pragma endregion Delegates

// Internal
#pragma region

class ICsWeapon;

namespace NCsWeapon
{
#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsWeapon::NPayload::IPayload

	class CSWP_API FManager : public ManagerMapType<ICsWeapon, FCsWeaponPooled, PayloadType, FECsWeapon>
	{
	private:

		typedef ManagerMapType<ICsWeapon, FCsWeaponPooled, PayloadType, FECsWeapon> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsWeapon& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsWeapon& Type) const override
		{
			return EMCsWeapon::Get().IsValidEnum(Type);
		}
	};

#undef ManagerMapType
#undef PayloadType
}

#pragma endregion Internal

class ICsGetManagerWeapon;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, FInterfaceMap)

// NCsData::NManager::NHandler::TClass
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumType>
			class TClass;
		}
	}
}

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

struct FCsInterfaceMap;

// NCsWeapon::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, FInterfaceMap)

class UDataTable;
struct FCsWeaponPtr;

class ICsWeapon;
class ICsPointWeapon;
class ICsPointSequenceWeapon;

UCLASS()
class CSWP_API UCsManager_Weapon : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	using ManagerType = NCsWeapon::FManager;
	using ManagerParamsType = NCsWeapon::FManager::FParams;
	using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
	using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
	using PayloadType = NCsWeapon::NPayload::IPayload;
	using ClassHandlerType = NCsData::NManager::NHandler::TClass<FCsWeaponClass, FCsWeaponPtr, FECsWeaponClass>;
	using DataType = NCsWeapon::NData::IData;
	using DataInterfaceMapType = NCsWeapon::NData::FInterfaceMap;
	using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_WeaponPtr, DataInterfaceMapType>;
	using ModifierManagerType = NCsWeapon::NModifier::FManager;
	using ModifierResourceType = NCsWeapon::NModifier::FResource;
	using ModifierType = NCsWeapon::NModifier::IModifier;
	using ModifierImplType = NCsWeapon::NModifier::EImpl;
	using SpreadVariablesManagerType = NCsWeapon::NProjectile::NSpread::NVariables::FManager;
	using SpreadVariablesResourceType = NCsWeapon::NProjectile::NSpread::NVariables::FResource;

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Weapon* Get(const UObject* InRoot = nullptr);
#else
FORCEINLINE static UCsManager_Weapon* Get(const UObject* InRoot = nullptr)
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
	static UCsManager_Weapon* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Weapon* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
	static bool IsValid(const UObject* InRoot = nullptr);
#else
FORCEINLINE static bool IsValid(const UObject* InRoot = nullptr)
{
	return s_Instance != nullptr;
}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Weapon> ManagerWeaponClass, UObject* InOuter = nullptr);
	
	static void Shutdown(const UObject* InRoot = nullptr);
	static bool HasShutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerWeapon* Get_GetManagerWeapon(const UObject* InRoot);
	static ICsGetManagerWeapon* GetSafe_GetManagerWeapon(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

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

public:

	FORCEINLINE const FCsSettings_Manager_Weapon& GetSettings() const { return Settings; }

protected:

	/** General Idea: Pool Sharing via Mapping of Types.
		Describes the mapping of a Weapon type to underlying Weapon type
		in terms the pool of Weapons.

		i.e. From -> To
			 TypeMapArray[From] = To.

		i.e. If Type 'A' is mapped to Type 'B' (TypeMapArray[A] = B), then
			 when a Weapon of type 'A' is spawned it will be allocated from
			 the pool of Weapons of type 'B'.

		The idea behind behind this mapping is Weapons of a different type may
		not have underlying code differences and just be differences in the data
		each respective weapon type uses. This provides the ability to save on both
		the number of pools created and the number of objects created for a pool. */
	TArray<FECsWeapon> TypeMapArray;

public:

	FORCEINLINE const TArray<FECsWeapon>& GetTypeMapArray() const { return TypeMapArray; }

protected:

	/** Used for faster lookup to see what types (Froms) are mapped to a particular type (To).
		To -> [Froms] 
		TypeMapToArray[To] = [Froms] */
	TArray<TArray<FECsWeapon>> TypeMapToArray;

public:

	FORCEINLINE const TArray<TArray<FECsWeapon>>& GetTypeMapToArray() const { return TypeMapToArray; }

	FORCEINLINE bool IsTypeMappedToType(const FECsWeapon& From, const FECsWeapon& To) const { return TypeMapArray[From] == To; }

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

	void SetAndAddTypeMapKeyValue(const FECsWeapon& Key, const FECsWeapon& Value);

	void AddPoolParams(const FECsWeapon& Type, const FCsSettings_Manager_Weapon_PoolParams& InPoolParams);

	FORCEINLINE bool HasPoolParams(const FECsWeapon& Type) const { return Settings.PoolParams.Find(Type) != nullptr; }

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
	virtual void CreatePool(const FECsWeapon& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsWeaponPooled*(const FECsWeapon&)>& GetConstructContainer_Impl();

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
	TMulticastDelegate<void(const FCsWeaponPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsWeapon& Type);

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
	virtual PayloadType* ConstructPayload(const FECsWeapon& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsWeapon::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsWeapon::NPayload::IPayload.
	*/
	PayloadType* AllocatePayload(const FECsWeapon& Type);

		/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsWeapon::NPayload::IPayload.
	*
	* @param Context	Calling context.
	* @param Type		Type of payload.
	* return			Payload that implements the interface: NCsWeapon::NPayload::IPayload.
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FString& Context, const FECsWeapon& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Context, GetTypeFromTypeMap(Type));
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsWeapon::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsWeapon::NPayload::IPayload.
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FECsWeapon& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(GetTypeFromTypeMap(Type));
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
	const FCsWeaponPooled* Spawn(const FECsWeapon& Type, PayloadType* Payload);

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

	/** Delegate for getting the Data of type: NCsWeapon::NData::IData a Weapon is using. 
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

	ClassHandlerType* ClassHandler;

	virtual void ConstructClassHandler();

public:

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon Type.
	*
	* @param Type	Type of the weapon.
	* return		Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeaponClass* GetWeapon(const FECsWeapon& Type);

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Type of the weapon.
	* return			Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeaponClass* GetWeaponChecked(const FString& Context, const FECsWeapon& Type);

	/**
	* Safely get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon Type.
	*
	* @param Context	The calling context.
	* @param Type		Type of the weapon.
	* return			Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeaponClass* GetSafeWeapon(const FString& Context, const FECsWeapon& Type);

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon class Type.
	*
	* @param Type	Class type of the weapon.
	* return		Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeaponClass* GetWeapon(const FECsWeaponClass& Type);

	/**
	* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the weapon.
	* return			Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeaponClass* GetWeaponChecked(const FString& Context, const FECsWeaponClass& Type);

	/**
	* Safely get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
	* with the weapon class Type.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the weapon.
	* return			Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
	*/
	FCsWeaponClass* GetSafeWeapon(const FString& Context, const FECsWeaponClass& Type);

	bool SafeAddClass(const FString& Context, const FECsWeapon& Type, UObject* Class);

	bool SafeAddClass(const FString& Context, const FECsWeaponClass& Type, UObject* Class);

#pragma endregion Class

// Data
#pragma region
protected:

	DataHandlerType* DataHandler;

	virtual void ConstructDataHandler();

public:

	FORCEINLINE DataHandlerType* GetDataHandler() const { return DataHandler; }

public:

	/**
	* Get the Data (implements interface: DataType (NCsWeapon::NData::IData)) associated with Name of the weapon type.
	*
	* @param Name	Name of the Weapon.
	* return		Data that implements the interface: DataType (NCsWeapon::NData::IData).
	*/
	DataType* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsWeapon::NData::IData)) associated with Name of the weapon type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Weapon.
	* return			Data that implements the interface: DataType (NCsWeapon::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Safely get the Data (implements interface: DataType (NCsWeapon::NData::IData)) associated with Name of the weapon type.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Weapon.
	* return			Data that implements the interface: DataType (NCsWeapon::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsWeapon::NData::IData)) associated with Type.
	*
	* @param Type	Weapon type.
	* return		Data that implements the interface: DataType (NCsWeapon::NData::IData).
	*/
	DataType* GetData(const FECsWeapon& Type);

	/**
	* Get the Data (implements interface: DataType (NCsWeapon::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Weapon type.
	* return			Data that implements the interface: DataType (NCsWeapon::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsWeapon& Type);

	/**
	* Get the Data (implements interface: DataType (NCsWeapon::NData::IData)) associated with Type.
	*
	* @param Context	The calling context.
	* @param Type		Weapon type.
	* return			Data that implements the interface: DataType (NCsWeapon::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FECsWeapon& Type);

protected:

	void OnPayloadUnloaded(const FName& Payload);

#pragma endregion Data

// Valid
#pragma region
protected:

	virtual bool IsValidChecked(const FString& Context, const DataType* Data) const;
	virtual bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

#pragma endregion Valid

// Modifier
#pragma region

protected:

	TArray<ModifierManagerType> Manager_Modifiers;

	TArray<ModifierImplType> ImplTypeByModifier;

	FORCEINLINE const ModifierImplType& GetModifierImplType(const FECsWeaponModifier& Type) const
	{
		return ImplTypeByModifier[Type.GetValue()];
	}

	FORCEINLINE ModifierManagerType& GetManagerModifier(const FECsWeaponModifier& Type)
	{
		return Manager_Modifiers[(uint8)GetModifierImplType(Type)];
	}

	void SetupModifiers();

	virtual ModifierType* ConstructModifier(const ModifierImplType& Type);

public:

	ModifierResourceType* AllocateModifier(const FECsWeaponModifier& Type);

	void DeallocateModifier(const FString& Context, const FECsWeaponModifier& Type, ModifierResourceType* Modifier);

	/**
	*
	*
	* @param Context	The calling context.
	* @param Value
	* return
	*/
	virtual const FECsWeaponModifier& GetModifierType(const FString& Context, const ModifierType* Modifier);

	ModifierResourceType* CreateCopyOfModifier(const FString& Context, const ModifierType* Modifier);

	ModifierResourceType* CreateCopyOfModifier(const FString& Context, const ModifierResourceType* Modifier);

#pragma endregion Modifier

// Events
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FWeapon_OnAllocate, const ICsWeapon* /*Weapon*/, PooledPayloadType* /*Payload*/);

	FWeapon_OnAllocate Weapon_OnAllocate_Event;

private:

	FORCEINLINE void Weapon_OnAllocate(const ICsWeapon* Weapon, PooledPayloadType* Payload)
	{
		Weapon_OnAllocate_Event.Broadcast(Weapon, Payload);
	}

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FWeapon_OnDeallocate_Start, const ICsWeapon* /*Weapon*/);

	FWeapon_OnDeallocate_Start Weapon_OnDeallocate_Start_Event;

private:

	FORCEINLINE void Weapon_OnDeallocate_Start(const ICsWeapon* Weapon)
	{
		Weapon_OnDeallocate_Start_Event.Broadcast(Weapon);
	}

	// Point
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FPointWeapon_OnHit, const ICsPointWeapon* /*Weapon*/, const FHitResult& /*Hit*/);

	FPointWeapon_OnHit PointWeapon_OnHit_Event;

private:

	FORCEINLINE void PointWeapon_OnHit(const ICsPointWeapon* Weapon, const FHitResult& Hit)
	{
		PointWeapon_OnHit_Event.Broadcast(Weapon, Hit);
	}

	// Sequence
#pragma region
public:

	DECLARE_MULTICAST_DELEGATE_ThreeParams(FPointSequenceWeapon_OnHit, const ICsPointSequenceWeapon* /*Weapon*/, const int32& Index /*Index*/, const FHitResult& /*Hit*/);

	FPointSequenceWeapon_OnHit PointSequenceWeapon_OnHit_Event;

private:

	FORCEINLINE void PointSequenceWeapon_OnHit(const ICsPointSequenceWeapon* Weapon, const int32& Index, const FHitResult& Hit)
	{
		PointSequenceWeapon_OnHit_Event.Broadcast(Weapon, Index, Hit);
	}

#pragma endregion Sequence

#pragma endregion Point

#pragma endregion Events

// Spread
#pragma region
private:

	SpreadVariablesManagerType SpreadVariablesManager;

	void SetupSpreadVariables();

public:
	
	FORCEINLINE SpreadVariablesResourceType* AllocateSpreadVariables() { return SpreadVariablesManager.Allocate(); }

	FORCEINLINE void DeallocateSpreadVariables(SpreadVariablesResourceType* Resource) { SpreadVariablesManager.Deallocate(Resource); }
	FORCEINLINE void DeallocateSpreadVariables(const int32& Index) { SpreadVariablesManager.DeallocateAt(Index); }

#pragma endregion Spread
};