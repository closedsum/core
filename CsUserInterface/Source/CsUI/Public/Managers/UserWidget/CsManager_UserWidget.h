// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"
// Pool
#include "Managers/Pool/CsManager_PooledObject_Map.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"
// UserWidget
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
#include "Managers/UserWidget/CsUserWidgetPooled.h"
// Settings
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"

#include "CsManager_UserWidget.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerUserWidget_OnSpawn, const FECsUserWidgetPooled&, Type, TScriptInterface<ICsUserWidgetPooled>, UserWidgetPooled);

#pragma endregion Delegates

// Internal
#pragma region

class ICsUserWidgetPooled;

namespace NCsUserWidget
{
#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsUserWidget::NPayload::IPayload

	class CSUI_API FManager : public ManagerMapType<ICsUserWidgetPooled, FCsUserWidgetPooled, PayloadType, FECsUserWidgetPooled>
	{
	private:

		typedef ManagerMapType<ICsUserWidgetPooled, FCsUserWidgetPooled, PayloadType, FECsUserWidgetPooled> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsUserWidgetPooled& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsUserWidgetPooled& Type) const override
		{
			return EMCsUserWidgetPooled::Get().IsValidEnum(Type);
		}
	};

#undef ManagerMapType
#undef PayloadType
}

#pragma endregion Internal

// Managers
#pragma region

#pragma endregion Managers

class ICsGetManagerUserWidget;

// NCsUserWidget::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NData, IData)

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

struct FCsUserWidgetPtr;
struct FCsData_UserWidgetPtr;

// NCsUserWidget::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NData, FInterfaceMap)

// NCsUserWidget::NPayload::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, FInterfaceMap)

class UUserWidget;

UCLASS()
class CSUI_API UCsManager_UserWidget : public UObject
{
	GENERATED_UCLASS_BODY()

#define ManagerType NCsUserWidget::FManager
#define ManagerParamsType NCsUserWidget::FManager::FParams
#define PayloadType NCsUserWidget::NPayload::IPayload
#define ConstructParamsType NCsPooledObject::NManager::FConstructParams
#define ClassHandlerType NCsData::NManager::NHandler::TClass
#define DataHandlerType NCsData::NManager::NHandler::TData
#define DataType NCsUserWidget::NData::IData
#define DataInterfaceMapType NCsUserWidget::NData::FInterfaceMap

public:	

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_UserWidget* Get(UObject* InRoot = nullptr);
#else
	static UCsManager_UserWidget* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_UserWidget* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_UserWidget* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return Cast<T>(GetSafe(Context, InRoot, Log));
	}

#if WITH_EDITOR
	static bool IsValid(UObject* InRoot = nullptr);
#else
	static bool IsValid(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? false : s_Instance != nullptr;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_UserWidget> ManagerFXActorClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
	static bool HasShutdown(UObject* InRoot = nullptr);
#else
	static bool HasShutdown(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? true : s_Instance == nullptr;
	}
#endif // #if WITH_EDITOR

#if WITH_EDITOR
protected:

	static ICsGetManagerUserWidget* Get_GetManagerUserWidget(UObject* InRoot);
	static ICsGetManagerUserWidget* GetSafe_GetManagerUserWidget(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);

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
	static UCsManager_UserWidget* s_Instance;
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

	FCsSettings_Manager_UserWidget Settings;

	/** General Idea: Pool Sharing via Mapping of Types.
		Describes the mapping of a UserWidget type to underlying UserWidget type
		in terms the pool of UserWidgets.

		i.e. From -> To
			 TypeMapArray[From] = To.

		i.e. If Type 'A' is mapped to Type 'B' (TypeMapArray[A] = B), then
			 when a UserWidget of type 'A' is spawned it will be allocated from
			 the pool of UserWidget of type 'B'.

		The idea behind behind this mapping is UserWidgets of a different type may
		not have underlying code differences and just be differences in the data
		each respective character type uses. This provides the ability to save on both
		the number of pools created and the number of objects created for a pool. */
	TArray<FECsUserWidgetPooled> TypeMapArray;

public:

	FORCEINLINE const TArray<FECsUserWidgetPooled>& GetTypeMapArray() const { return TypeMapArray; }

protected:

	/** Used for faster lookup to see what types (Froms) are mapped to a particular type (To).
		To -> [Froms]
		TypeMapToArray[To] = [Froms] */
	TArray<TArray<FECsUserWidgetPooled>> TypeMapToArray;

public:

	FORCEINLINE const TArray<TArray<FECsUserWidgetPooled>>& GetTypeMapToArray() const { return TypeMapToArray; }

	FORCEINLINE void SetSettings(const FCsSettings_Manager_UserWidget& InSettings)
	{
		Settings = InSettings;
	}

	/**
	* If SET,
	* - Get the type this UserWidgetPooled has been mapped to for pooling.
	*   i.e. If the widget actor is completely data driven, then many user widget pooled objects could share
	*   the same class.
	* If NOT set,
	* - Return the same type.
	*
	* @param Type
	* return UserWidgetPooled Type 
	*/
	FORCEINLINE const FECsUserWidgetPooled& GetTypeFromTypeMap(const FECsUserWidgetPooled& Type)
	{
		check(EMCsUserWidgetPooled::Get().IsValidEnum(Type));

		return TypeMapArray[Type.GetValue()];
	}

	void SetAndAddTypeMapKeyValue(const FECsUserWidgetPooled& Key, const FECsUserWidgetPooled& Value);

#pragma endregion Settings

// Internal
#pragma region
protected:
	
	/** Reference to the internal manager for handling the pool of fx actors. */
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
	virtual void CreatePool(const FECsUserWidgetPooled& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsUserWidgetPooled*(const FECsUserWidgetPooled&)>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsUserWidgetPooled* ConstructContainer(const FECsUserWidgetPooled& Type);

	/**
	* Custom implementation for constructing a UObject (usually UObject is constructed via NewObject).
	* 
	* @param Params
	* return			UObject.
	*/
	UObject* CustomNewObject(const ConstructParamsType& Params);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void(const FCsUserWidgetPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsUserWidgetPooled& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsUserWidgetPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToPool(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToPool(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsUserWidgetPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToPool(const FECsUserWidgetPooled& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsUserWidgetPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToAllocatedObjects(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToAllocatedObjects(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsUserWidgetPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* AddToAllocatedObjects(const FECsUserWidgetPooled& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsUserWidgetPooled.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsUserWidgetPooled*>& GetPool(const FECsUserWidgetPooled& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsUserWidgetPooled.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsUserWidgetPooled*>& GetAllocatedObjects(const FECsUserWidgetPooled& Type);

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsUserWidgetPooled& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsUserWidgetPooled& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsUserWidgetPooled& Type);

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
	*				Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindObject(const FECsUserWidgetPooled& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsUserWidgetPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindObject(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsUserWidgetPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsUserWidgetPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindObject(const FECsUserWidgetPooled& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindSafeObject(const FECsUserWidgetPooled& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindSafeObject(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsUserWidgetPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsUserWidgetPooled.
	*/
	const FCsUserWidgetPooled* FindSafeObject(const FECsUserWidgetPooled& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsUserWidgetPooled CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsUserWidgetPooled& Type);

	void OnUpdate_Object(const FECsUserWidgetPooled& Type, const FCsUserWidgetPooled* Object);

	void OnPostUpdate_Pool(const FECsUserWidgetPooled& Type);

#pragma endregion Update

	// Payload
#pragma region
protected:

	/** <InterfaceMapPtr> */
	TArray<NCsUserWidget::NPayload::FInterfaceMap*> PayloadInterfaceMaps;

public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsUserWidgetPooled& Type, const int32& Size);

	/**
	*
	*
	* @param Type
	* return
	*/
	virtual PayloadType* ConstructPayload(const FECsUserWidgetPooled& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsUserWidget::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsUserWidget::NPayload::IPayload.
	*/
	PayloadType* AllocatePayload(const FECsUserWidgetPooled& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsUserWidget::NPayload::IPayload).
	*
	* @param Context	The calling context.
	* @param Type		Type of payload.
	* return			Payload that implements the interface: PayloadType (NCsUserWidget::NPayload::IPayload).
	*/
	template<typename PayloadTypeImpl>
	FORCEINLINE PayloadTypeImpl* AllocatePayload(const FString& Context, const FECsUserWidgetPooled& Type)
	{
		return Internal.AllocatePayload<PayloadTypeImpl>(Context, GetTypeFromTypeMap(Type));
	}

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: PayloadType (NCsUserWidget::NPayload::IPayload).
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: PayloadType (NCsUserWidget::NPayload::IPayload).
	*/
	template<typename PayloadTypeImpl>
	PayloadTypeImpl* AllocatePayload(const FECsUserWidgetPooled& Type)
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
	const FCsUserWidgetPooled* Spawn(const FECsUserWidgetPooled& Type, PayloadType* Payload);

	/**
	* Delegate type after an FX Actor object has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsUserWidgetPooled& /*Type*/, const FCsUserWidgetPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerUserWidget_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsUserWidgetPooled& Type, ICsUserWidgetPooled* Object);

	virtual bool Destroy(ICsUserWidgetPooled* Object);

	/**
	* Delegate type after an FX Actor object has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsUserWidgetPooled& /*Type*/, const FCsUserWidgetPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& /*Str*/);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsUserWidgetPooled* Object);

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

	// ICsUserWidgetPooled
#pragma region
public:

#pragma endregion ICsUserWidgetPooled

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
protected:

	ClassHandlerType<FCsUserWidgetPtr, FCsUserWidgetPtr, FECsUserWidgetClass>* ClassHandler;

	virtual void ConstructClassHandler();

public:

	/**
	* Get the UserWidget Pooled container (Interface (ICsUserWidgetPooled), UObject, and / or UClass) associated
	* with the user widget pooled Type.
	*
	* @param Type	Type of the user widget pooled.
	* return		UserWidget Pooled container (Interface (ICsUserWidgetPooled), UObject, and / or UClass).
	*/
	FCsUserWidgetPooled* GetUserWidgetPooled(const FECsUserWidgetPooled& Type);

	/**
	* Get the UserWidget Pooled container (Interface (ICsUserWidgetPooled), UObject, and / or UClass) associated
	* with the user widget pooled class Type.
	*
	* @param Type	Class type of the UserWidget Pooled.
	* return		UserWidget Pooled container (Interface (ICsUserWidgetPooled), UObject, and / or UClass).
	*/
	FCsUserWidgetPooled* GetUserWidgetPooled(const FECsUserWidgetPooledClass& Type);

	/**
	* Get the UserWidget Pooled container (Interface (ICsUserWidgetPooled), UObject, and / or UClass) associated
	* with the user widget class pooled Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the user widget pooled.
	* return			UserWidget Pooled container (Interface (ICsUserWidgetPooled), UObject, and / or UClass).
	*/
	FCsUserWidgetPooled* GetUserWidgetPooledChecked(const FString& Context, const FECsUserWidgetPooledClass& Type);

protected:

	ClassHandlerType<FCsUserWidgetPooled, FCsUserWidgetPooledPtr, FECsUserWidgetPooledClass>* PooledClassHandler;

	virtual void ConstructPooledClassHandler();

public:

	/**
	* Get the UserWidget container (UUserWidget) associated
	* with the user widget Type.
	*
	* @param Type	Type of the user widget.
	* return		UserWidget container (UUserWidget).
	*/
	FCsUserWidgetPtr* GetUserWidget(const FECsUserWidget& Type);

	/**
	* Get the UserWidget container (UUserWidget) associated
	* with the user widget Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Type of the user widget.
	* return			UserWidget container (UUserWidget).
	*/
	FCsUserWidgetPtr* GetUserWidgetChecked(const FString& Context, const FECsUserWidget& Type);

	/**
	* Get the UserWidget container (UUserWidget) associated
	* with the user widget class Type.
	*
	* @param Type	Class type of the UserWidget.
	* return		UserWidget container (UUserWidget).
	*/
	FCsUserWidgetPtr* GetUserWidget(const FECsUserWidgetClass& Type);

	/**
	* Get the UserWidget container (UUserWidget) associated
	* with the user widget class Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		Class type of the user widget.
	* return			UserWidget container (UUserWidget).
	*/
	FCsUserWidgetPtr* GetUserWidgetChecked(const FString& Context, const FECsUserWidgetClass& Type);

#pragma endregion Class

// Data
#pragma region
protected:

	DataHandlerType<DataType, FCsData_UserWidgetPtr, DataInterfaceMapType>* DataHandler;

	virtual void ConstructDataHandler();

public:

	/**
	* Get the Data (implements interface: ICsData_UserWidget) associated with Name of the character type.
	*
	* @param Name	Name of the UserWidget.
	* return		Data that implements the interface: ICsData_UserWidget.
	*/
	DataType* GetData(const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsUserWidget::NData::IData)) associated with Type.
	*
	* @param Type	UserWidget type.
	* return		Data that implements the interface: DataType (NCsUserWidget::NData::IData).
	*/
	DataType* GetData(const FECsUserWidget& Type);

	// TODO: Need to think about / look into mapping of FECsUserWidgetPooled to data
	/**
	* Get the Data (implements interface: DataType (NCsUserWidget::NData::IData)) associated with Type.
	*
	* @param Type	UserWidgetPooled type.
	* return		Data that implements the interface: DataType (NCsUserWidget::NData::IData).
	*/
	DataType* GetData(const FECsUserWidgetPooled& Type);

	/**
	* Get the Data (implements interface: DataType (NCsUserWidget::NData::IData)) associated with Name of the character type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Name		Name of the UserWidget.
	* return			Data that implements the interface: DataType (NCsUserWidget::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FName& Name);

	/**
	* Get the Data (implements interface: DataType (NCsUserWidget::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		UserWidget type.
	* return			Data that implements the interface: DataType (NCsUserWidget::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsUserWidget& Type);

	// TODO: Need to think about / look into mapping of FECsUserWidgetPooled to data
	/**
	* Get the Data (implements interface: DataType (NCsUserWidget::NData::IData)) associated with Type.
	* "Checked" in regards to returning a valid pointer.
	*
	* @param Context	The calling context.
	* @param Type		UserWidgetPooled type.
	* return			Data that implements the interface: DataType (NCsUserWidget::NData::IData).
	*/
	DataType* GetDataChecked(const FString& Context, const FECsUserWidgetPooled& Type);

#pragma endregion Data

public:

	struct FSetPositionInViewports
	{
		friend class UCsManager_UserWidget;

	private:

		UCsManager_UserWidget* Outer;

	private:

	#define IDManagerType NCsResource::NManager::NValue::NFixed::NInt32::FManager

		IDManagerType Manager_ID;

		TArray<int32> AllocatedIDs;

		TArray<UUserWidget*> UserWidgets;

		TArray<FVector> WorldPositions;

		TArray<FVector2D> ScreenPositions;

		TArray<FVector2D> Offsets;

	public:

		FSetPositionInViewports() :
			Outer(nullptr),
			//Manager_ID(),
			AllocatedIDs(),
			UserWidgets(),
			WorldPositions(),
			ScreenPositions(),
			Offsets()
		{
		}

		void SetSize(const int32& InSize);

		int32 Allocate(UUserWidget* Widget);
		
		void Deallocate(const int32& ID);

		void UpdateWorldPositionAndOffset(const int32& ID, const FVector& WorldPosition, const FVector2D& Offset);

		void Update(const FCsDeltaTime& DeltaTime);

	#undef IDManagerType
	};

public:

	FSetPositionInViewports SetPositionInViewports;

#undef ManagerType
#undef ManagerParamsType
#undef PayloadType
#undef ConstructParamsType
#undef ClassHandlerType
#undef DataHandlerType
#undef DataType
#undef DataInterfaceMapType
};