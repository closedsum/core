// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
// Managers
#include "Managers/Pool/CsManager_PooledObject_Map.h"
// Types
#include "Types/CsTypes_Beam.h"
// Beam
#include "Payload/CsPayload_Beam.h"
#include "Managers/Beam/ICsBeam.h"
#include "Managers/Beam/CsBeamPooled.h"
#include "Managers/Beam/CsSettings_Manager_Beam.h"

#include "CsManager_Beam.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerBeam_OnSpawn, const FECsBeam&, Type, TScriptInterface<ICsBeam>, Beam);

#pragma endregion Delegates

// Internal
#pragma region

class ICsBeam;

namespace NCsBeam
{
#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsBeam::NPayload::IPayload

	class CSBEAM_API FManager : public ManagerMapType<ICsBeam, FCsBeamPooled, PayloadType, FECsBeam>
	{
	private:

		typedef ManagerMapType<ICsBeam, FCsBeamPooled, PayloadType, FECsBeam> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsBeam& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsBeam& Type) const override
		{
			return EMCsBeam::Get().IsValidEnum(Type);
		}
	};

#undef PayloadType
}

#pragma endregion Internal

class ICsGetManagerBeam;
class UDataTable;

// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)
// NCsBeam::NPayload::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NPayload, FInterfaceMap)

// NCsData::NManager::NHandler::TClass
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfacePooledContainerType, typename InterfaceUStructContainerType, typename EnumType>
			class TClass; } } }

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData; } } }

struct FCsInterfaceMap;

// NCsBeam::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, FInterfaceMap)

UCLASS()
class CSBEAM_API UCsManager_Beam : public UObject
{
	GENERATED_UCLASS_BODY()

#define ManagerType NCsBeam::FManager
#define ManagerParamsType NCsBeam::FManager::FParams
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define PayloadType NCsBeam::NPayload::IPayload
#define ClassHandlerType NCsData::NManager::NHandler::TClass
#define DataHandlerType NCsData::NManager::NHandler::TData
#define DataType NCsBeam::NData::IData

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Beam * Get(UObject * InRoot = nullptr);
#else
FORCEINLINE static UCsManager_Beam* Get(UObject* InRoot = nullptr)
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

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Beam> ManagerBeamClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerBeam* Get_GetManagerBeam(UObject* InRoot);
	static ICsGetManagerBeam* GetSafe_GetManagerBeam(UObject* Object);

	static UCsManager_Beam* GetSafe(UObject* Object);

public:

	static UCsManager_Beam* GetFromWorldContextObject(const UObject* WorldContextObject);

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
	static UCsManager_Beam* s_Instance;
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
	FCsSettings_Manager_Beam Settings;

	/** */
	TArray<FECsBeam> TypeMapArray;

public:

	/**
	*
	*
	* @param InSettings
	*/ 
	FORCEINLINE void SetSettings(const FCsSettings_Manager_Beam& InSettings)
	{
		Settings = InSettings;
	}

	/**
	* If SET,
	* - Get the type this Beam has been mapped to for pooling.
	*   i.e. If the beam is completely data driven, then many beams could share
	*   the same class.
	* If NOT set,
	* - Return the same type.
	*
	* @param Type
	* return Beam Type 
	*/
	FORCEINLINE const FECsBeam& GetTypeFromTypeMap(const FECsBeam& Type)
	{
		check(EMCsBeam::Get().IsValidEnum(Type));

		return TypeMapArray[Type.GetValue()];
	}

	void SetAndAddTypeMapKeyValue(const FECsBeam& Key, const FECsBeam& Value);

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of beams. */
	ManagerType Internal;

	/**
	* Setup the internal manager for handling the pool of beams.
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
	virtual void CreatePool(const FECsBeam& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsBeamPooled*(const FECsBeam&)>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsBeamPooled* ConstructContainer(const FECsBeam& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void(const FCsBeamPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsBeam& Type);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsBeam.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsBeam.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsBeam.
	*/
	const FCsBeamPooled* AddToPool(const FECsBeam& Type, ICsBeam* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsBeam.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsBeam.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsBeam.
	*/
	const FCsBeamPooled* AddToPool(const FECsBeam& Type, const FCsBeamPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsBeam or the UClass
	*  associated with the Object have ImplementsInterface(UCsBeam::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsBeam.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsBeam.
	*/
	const FCsBeamPooled* AddToPool(const FECsBeam& Type, UObject* Object);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsBeam& Type, const FCsBeamPooled* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsBeam.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsBeam.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsBeam.
	*/
	const FCsBeamPooled* AddToAllocatedObjects(const FECsBeam& Type, ICsBeam* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsBeam.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsBeam.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsBeam.
	*/
	const FCsBeamPooled* AddToAllocatedObjects(const FECsBeam& Type, ICsBeam* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsBeam or the UClass
	*  associated with the Object have ImplementsInterface(UCsBeam::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsBeam.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsBeam.
	*/
	const FCsBeamPooled* AddToAllocatedObjects(const FECsBeam& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsBeam.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsBeamPooled*>& GetPool(const FECsBeam& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsBeam.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsBeamPooled*>& GetAllocatedObjects(const FECsBeam& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsBeam& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsBeam& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsBeam& Type);

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
	const FCsBeamPooled* FindObject(const FECsBeam& Type, const int32& Index);

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
	const FCsBeamPooled* FindObject(const FECsBeam& Type, ICsBeam* Object);

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
	const FCsBeamPooled* FindObject(const FECsBeam& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsBeamPooled* FindSafeObject(const FECsBeam& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsPooledObject.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsPooledObject.
	*/
	const FCsBeamPooled* FindSafeObject(const FECsBeam& Type, ICsBeam* Object);

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
	const FCsBeamPooled* FindSafeObject(const FECsBeam& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
private:

	/** Whether TypesByUpdateGroup is used or not. */
	bool bTypesByUpdateGroup;

	TArray<TArray<FECsBeam>> TypesByUpdateGroup;

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
	* Update ALL sounds of Type (FECsBeam) with DeltaTime.
	*
	* @param Type
	* @param DeltaTime
	*/
	void Update(const FECsBeam& Type, const FCsDeltaTime& DeltaTime);

private:

	FECsBeam CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsBeam& Type);

	void OnUpdate_Object(const FECsBeam& Type, const FCsBeamPooled* Object);

	void OnPostUpdate_Pool(const FECsBeam& Type);

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
	* Set th pause flag for ALL sounds associated with Type: (FECsBeam).
	*
	* @param Type
	* @param bPaused	True = pause. False = un-pause.
	*/
	void Pause(const FECsBeam& Type, bool bPaused);

private:

	TMap<FECsUpdateGroup, FDelegateHandle> OnPauseHandleByGroupMap;

public:

	void BindToOnPause(const FECsUpdateGroup& Group);

#pragma endregion Pause

	// Payload
#pragma region
protected:

	/** <InterfaceMapPtr> */
	TArray<NCsBeam::NPayload::FInterfaceMap*> PayloadInterfaceMaps;

	/** <InterfaceImpName, <InterfaceImplPtr>> 
		 stores all interface "slices" related to payload and beam but 
		 NOT the interface stored in Internal (i.e. NCsBeam::NPayload::FImplSlice) 
		 as Internal handles the deconstruction of that interface. */
	TMap<FName, TArray<void*>> PayloadInterfaceImplMap;

public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsBeam& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual PayloadType* ConstructPayload(const FECsBeam& Type);

protected:

	virtual void DeconstructPayloadSlice(const FName& InterfaceImplName, void* Data);

public:

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsBeam::NPayload::IPayload).
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: PayloadType (NCsBeam::NPayload::IPayload).
	*/
	PayloadType* AllocatePayload(const FECsBeam& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsBeam::NPayload::IPayload).
	*
	* @param Context	Calling context.
	* @param Type		Type of payload.
	* return			Payload that implements the interface: PayloadType (NCsBeam::NPayload::IPayload).
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FString& Context, const FECsBeam& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Context, Type);
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsBeam::NPayload::IPayload).
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: PayloadType (NCsBeam::NPayload::IPayload).
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FECsBeam& Type)
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
	const FCsBeamPooled* Spawn(const FECsBeam& Type, PayloadType* Payload);

	/**
	* Delegate type after a Beam has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsBeam& /*Type*/, const FCsBeamPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerBeam_OnSpawn OnSpawn_ScriptEvent;

#pragma endregion Spawn

	// Destroy
#pragma region
public:

	/**
	*
	*
	* @param Type
	* @param Beam
	*/
	virtual bool Destroy(const FECsBeam& Type, ICsBeam* Beam);

	virtual bool Destroy(ICsBeam* Beam);

	/**
	* Delegate type after a Beam has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsBeam& /*Type*/, const FCsBeamPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& Str);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsBeamPooled* Object);

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

	// ICsBeam
#pragma region
public:

	/** Delegate for getting the Owner of a Beam. 
		 The Beam implements a script interface of type: ICsBeam. */
	FCsBeamPooled::FScript_GetOwner Script_GetOwner_Impl;

	/** Delegate for getting the Instigator of a Beam. 
		 The Beam implements a script interface of type: ICsBeam. */
	FCsBeamPooled::FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion ICsBeam

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

	ClassHandlerType<FCsBeamPooled, FCsBeamPtr, FECsBeamClass>* ClassHandler;

	virtual void ConstructClassHandler();

public:

	/**
	* Get the Beam container (Interface (ICsBeam), UObject, and / or UClass) associated
	* with the beam Type.
	*
	* @param Type	Type of the beam.
	* return		Beam container (Interface (ICsBeam), UObject, and / or UClass).
	*/
	FCsBeamPooled* GetBeam(const FECsBeam& Type);

	/**
	* Get the Beam container (Interface (ICsBeam), UObject, and / or UClass) associated
	* with the beam class Type.
	*
	* @param Type	Class type of the beam.
	* return		Beam container (Interface (ICsBeam), UObject, and / or UClass).
	*/
	FCsBeamPooled* GetBeam(const FECsBeamClass& Type);

	/**
	* Get the Beam container (Interface (ICsBeam), UObject, and / or UClass) associated
	* with the beam class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the beam.
	* return			Beam container (Interface (ICsBeam), UObject, and / or UClass).
	*/
	FCsBeamPooled* GetBeamChecked(const FString& Context, const FECsBeamClass& Type);

#pragma endregion Class

// Data
#pragma region
protected:

#define DataInterfaceMapType NCsBeam::NData::FInterfaceMap

	DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* DataHandler;

	virtual void ConstructDataHandler();

public:

	FORCEINLINE DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* GetDataHandler() const { return DataHandler; }

#undef DataInterfaceMapType

	/**
	* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Name of the beam type.
	*
	* @param Name	Name of the Beam.
	* return		Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	DataType* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Name of the beam type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Beam.
	* return			Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Safely get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Name of the weapon type.
	*
	* @param Context	The calling context.
	* @param Name		Name of the Weapon.
	* return			Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Type.
	*
	* @param Type	Beam type.
	* return		Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	DataType* GetData(const FECsBeam& Type);

	/**
	* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Beam type.
	* return			Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsBeam& Type);

	/**
	* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Type.
	*
	* @param Context	The calling context.
	* @param Type		Weapon type.
	* return			Data that implements the interface: DataType (NCsBeam::NData::IData).
	*/
	DataType* GetSafeData(const FString& Context, const FECsBeam& Type);

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