// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Object.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed.h"
// Managers
#include "Managers/Pool/CsManager_PooledObject_Map.h"
// Types
#include "Managers/FX/CsTypes_FX.h"
#include "Managers/Time/CsTypes_Update.h"
// FX
#include "Managers/FX/Payload/CsPayload_FX.h"
#include "Managers/FX/Actor/CsFXActorPooled.h"
#include "Managers/FX/Actor/CsSettings_Manager_FX.h"
#include "Managers/FX/Params/CsParams_FX.h"

#include "CsManager_FX.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerFX_OnSpawn, const FECsFX&, Type, TScriptInterface<ICsFXActorPooled>, FXActor);

#pragma endregion Delegates

// Structs
#pragma region

namespace NCsFX
{
	namespace NParameter
	{
		namespace NInt
		{
			// FIntType (NCsFX::NParamter::NInt::FIntType)

			/**
			* Container for holding a reference to the object FIntType (NCsFX::NParamter::NInt::FIntType).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSFX_API FResource : public TCsResourceContainer<FIntType> {};

			/**
			* A manager handling allocating and deallocating the object FIntType (NCsFX::NParamter::NFloat::FIntType) and
			* are wrapped in the container: NCsFX::NParameter::NInt::FResource.
			*/
			struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FIntType, FResource, 0> {};
		}

		namespace NFloat
		{
			// FFloatType (NCsFX::NParamter::NFloat::FFloatType)

			/**
			* Container for holding a reference to the object FFloatType (NCsFX::NParamter::NFloat::FFloatType).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSFX_API FResource : public TCsResourceContainer<FFloatType> {};

			/**
			* A manager handling allocating and deallocating the object FFloatType (NCsFX::NParamter::NFloat::FFloatType) and
			* are wrapped in the container: NCsFX::NParameter::NFloat::FResource.
			*/
			struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FFloatType, FResource, 0> {};
		}

		namespace NVector
		{
			// FVectorType (NCsFX::NParamter::NVector::FVectorType)

			/**
			* Container for holding a reference to the object FVectorType (NCsFX::NParamter::NVector::FVectorType).
			* This serves as an easy way for a Manager Resource to keep track of the resource.
			*/
			struct CSFX_API FResource : public TCsResourceContainer<FVectorType> {};

			/**
			* A manager handling allocating and deallocating the object FVectorType (NCsFX::NParamter::NVector::FVectorType) and
			* are wrapped in the container: NCsFX::NParameter::NVector::FResource.
			*/
			struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FVectorType, FResource, 0> {};
		}

		namespace NScaled
		{
			namespace NInt
			{
				// FIntType (NCsFX::NParamter::NScaled::NInt::FIntType)

				/**
				* Container for holding a reference to the object FIntType (NCsFX::NParamter::NScaled::NInt::FIntType).
				* This serves as an easy way for a Manager Resource to keep track of the resource.
				*/
				struct CSFX_API FResource : public TCsResourceContainer<FIntType> {};

				/**
				* A manager handling allocating and deallocating the object FIntType (NCsFX::NParamter::NScaled::NInt::FIntType) and
				* are wrapped in the container: NCsFX::NParameter::NScaled::NInt::FResource.
				*/
				struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FIntType, FResource, 0> {};
			}

			namespace NFloat
			{
				// FFloatType (NCsFX::NParamter::NScaled::NFloat::FFloatType)

				/**
				* Container for holding a reference to the object FFloatType (NCsFX::NParamter::NScaled::NFloat::FFloatType).
				* This serves as an easy way for a Manager Resource to keep track of the resource.
				*/
				struct CSFX_API FResource : public TCsResourceContainer<FFloatType> {};

				/**
				* A manager handling allocating and deallocating the object FFloatType (NCsFX::NParamter::NScaled::NFloat::FFloatType) and
				* are wrapped in the container: NCsFX::NParameter::NScaled::NFloat::FResource.
				*/
				struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FFloatType, FResource, 0> {};
			}

			namespace NVector
			{
				// FVectorType (NCsFX::NParamter::NScaled::NVector::FVectorType)

				/**
				* Container for holding a reference to the object FVectorType (NCsFX::NParamter::NScaled::NVector::FVectorType).
				* This serves as an easy way for a Manager Resource to keep track of the resource.
				*/
				struct CSFX_API FResource : public TCsResourceContainer<FVectorType> {};

				/**
				* A manager handling allocating and deallocating the object FVectorType (NCsFX::NParamter::NScaled::NVector::FVectorType) and
				* are wrapped in the container: NCsFX::NParameter::NScaled::NVector::FResource.
				*/
				struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FVectorType, FResource, 0> {};
			}
		}

		namespace NDataInterface
		{
			namespace NSkeletalMesh
			{
				// FSkeletalMeshType (NCsFX::NParamter::NDataInterface::NSkeletalMesh::FSkeletalMeshType)

				/**
				* Container for holding a reference to the object FIntType (NCsFX::NParamter::NDataInterface::NSkeletalMesh::FSkeletalMeshType).
				* This serves as an easy way for a Manager Resource to keep track of the resource.
				*/
				struct CSFX_API FResource : public TCsResourceContainer<FSkeletalMeshType> {};

				/**
				* A manager handling allocating and deallocating the object FSkeletalMeshType (NCsFX::NParamter::NDataInterface::NSkeletalMesh::FSkeletalMeshType) and
				* are wrapped in the container: NCsFX::NParameter::NDataInterface::NSkeletalMesh::FResource.
				*/
				struct CSFX_API FManager : public NCsResource::NManager::NValue::TFixed<FSkeletalMeshType, FResource, 0> {};
			}
		}
	}
}

#pragma endregion Structs

// Internal
#pragma region

class ICsFXActorPooled;

namespace NCsFX
{
#define ManagerMapType NCsPooledObject::NManager::TTMap
#define PayloadType NCsFX::NPayload::IPayload

	class CSFX_API FManager : public ManagerMapType<ICsFXActorPooled, FCsFXActorPooled, PayloadType, FECsFX>
	{
	private:

		typedef ManagerMapType<ICsFXActorPooled, FCsFXActorPooled, PayloadType, FECsFX> Super;

	public:

		FManager();

		FORCEINLINE virtual const FString& KeyTypeToString(const FECsFX& Type) const override
		{
			return Type.GetName();
		}

		FORCEINLINE virtual bool IsValidKey(const FECsFX& Type) const override
		{
			return EMCsFX::Get().IsValidEnum(Type);
		}
	};

#undef PayloadType
}

#pragma endregion Internal

class ICsGetManagerFX;
class ICsData_FX;
class UDataTable;

UCLASS()
class CSFX_API UCsManager_FX : public UObject
{
	GENERATED_UCLASS_BODY()

public:	

using ManagerType = NCsFX::FManager;
using ConstructParamsType = NCsPooledObject::NManager::FConstructParams;
using PayloadType = NCsFX::NPayload::IPayload;

using ParameterType = NCsFX::NParameter::IParameter;
using IntParameterManagerType = NCsFX::NParameter::NInt::FManager;
using IntParameterType = NCsFX::NParameter::NInt::FIntType;
using FloatParameterManagerType = NCsFX::NParameter::NFloat::FManager;
using FloatParameterType = NCsFX::NParameter::NFloat::FFloatType;
using VectorParameterManagerType = NCsFX::NParameter::NVector::FManager;
using VectorParameterType = NCsFX::NParameter::NVector::FVectorType;

using ScaledParameterType = NCsFX::NParameter::NScaled::IScaled;
using ScaledIntParameterManagerType = NCsFX::NParameter::NScaled::NInt::FManager;
using ScaledIntParameterType = NCsFX::NParameter::NScaled::NInt::FIntType;
using ScaledFloatParameterManagerType = NCsFX::NParameter::NScaled::NFloat::FManager;
using ScaledFloatParameterType = NCsFX::NParameter::NScaled::NFloat::FFloatType;
using ScaledVectorParameterManagerType = NCsFX::NParameter::NScaled::NVector::FManager;
using ScaledVectorParameterType = NCsFX::NParameter::NScaled::NVector::FVectorType;

using SkeletalMeshParameterManagerType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::FManager;
using SkeletalMeshParameterType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType;

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_FX* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_FX* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_FX* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_FX* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
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

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_FX> ManagerFXClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerFX* Get_GetManagerFX(const UObject* InRoot);
	static ICsGetManagerFX* GetSafe_GetManagerFX(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

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
	static UCsManager_FX* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot() { return MyRoot; }
	FORCEINLINE const UObject* GetMyRoot() const { return MyRoot; }

#pragma endregion Root

	// State
#pragma region
public:

	enum class EState : uint8
	{
		None,
		Active,
		BeginShutdown
	};

private:

	EState State;

public:


	FORCEINLINE void SetBeginShutdown() { State = EState::BeginShutdown; }

	FORCEINLINE bool IsBeginningShutdown() { return State == EState::BeginShutdown; }

#pragma endregion State

#pragma endregion Singleton

// Settings
#pragma region
protected:

	FCsSettings_Manager_FX Settings;

public:

	FORCEINLINE void SetSettings(const FCsSettings_Manager_FX& InSettings)
	{
		Settings = InSettings;
	}

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
	void InitInternal(const ManagerType::FParams& Params);

	virtual void Clear();

	// Pool
#pragma region
public:

	/**
	* 
	* @param Type
	* @param Size
	*/
	virtual void CreatePool(const FECsFX& Type, const int32& Size);

	/**
	*
	*
	* return
	*/
	TDelegate<FCsFXActorPooled*(const FECsFX&)>& GetConstructContainer_Impl();

	/**
	*
	* @param Type
	* return
	*/
	virtual FCsFXActorPooled* ConstructContainer(const FECsFX& Type);

	/**
	*
	*
	* @param Type
	* return
	*/
	TMulticastDelegate<void(const FCsFXActorPooled*, const ConstructParamsType&)>& GetOnConstructObject_Event(const FECsFX& Type);

	/**
	*
	*
	* @param Type
	* @param Object
	*/
	void OnAddToPool(const FECsFX& Type, const FCsFXActorPooled* Object);

		// Add
#pragma region

			// Pool
#pragma region

public:

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  The Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsFXActorPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToPool(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToPool(const FECsFX& Type, const FCsFXActorPooled* Object);

	/**
	* Adds an Object to the pool for the appropriate Type.
	*  Object must implement the interface: ICsFXActorPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of the pool to add the object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToPool(const FECsFX& Type, UObject* Object);

#pragma endregion Pool

			// Allocated Objects
#pragma region
public:

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type			Type of pool to add the Object to.
	* @param PooledObject	Object that implements the interface: ICsFXActorPooled.
	* @param Object			UObject reference.
	* return				Container holding a reference to a pooled object.
	*						Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* PooledObject, UObject* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToAllocatedObjects(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Adds an Object to the allocated objects for the appropriate Type.
	* If the Object is NOT added to the pool, add it to the pool.
	*  Object must implement the interface: ICsFXActorPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* AddToAllocatedObjects(const FECsFX& Type, UObject* Object);

#pragma endregion Allocated Objects

#pragma endregion Add

public:

	/**
	* Get the pool for the appropriate Type.
	*  Pool is an array of containers holding references to objects that
	*  implement the interface: ICsFXActorPooled.
	*
	* @param Type	Type of pool to get.
	* return		Pool associated with the type.
	*/
	const TArray<FCsFXActorPooled*>& GetPool(const FECsFX& Type);

	/**
	* Get the allocated objects for the appropriate Type.
	*  Allocated Objects are an array of containers holding references to objects that
	*  implement the interface: ICsFXActorPooled.
	*
	* @param Type	Type of allocated objects to get.
	* return		Allocated Objects associated with the Type.
	*/
	const TArray<FCsFXActorPooled*>& GetAllocatedObjects(const FECsFX& Type);

	void LogAllocatedObjects() const;

	/**
	* Get the number of elements in the pool for the appropriate Type.
	*
	*
	* @param Type	Type of pool.
	* return		Number of elements in the pool for the associated Type.
	*/
	const int32& GetPoolSize(const FECsFX& Type);

	/**
	* Get the number of allocated objects for the appropriate Type.
	*
	* @param Type	Type of allocated objects.
	* return		Number of allocated objects for the associated Type.
	*/
	int32 GetAllocatedObjectsSize(const FECsFX& Type);

	/**
	* Get whether all elements in the pool for the appropriate Type
	* have been allocated.
	*
	@ @param Type	Type of pool to check against.
	* return		All elements allocated or not.
	*/
	bool IsExhausted(const FECsFX& Type);

	bool IsAnyAllocated() const;

	bool IsNoneAllocated() const;

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
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindObject(const FECsFX& Type, const int32& Index);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Interface.
	*  Object must implement the interface: ICsFXActorPooled.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object of interface type: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindObject(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by UObject.
	*  Object must implement the interface: ICsFXActorPooled or the UClass
	*  associated with the Object have ImplementsInterface(UCsFXActorPooled::StaticClass()) == true.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindObject(const FECsFX& Type, UObject* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by Index.
	*
	* @param Type	Type of pool to add the Object to.
	* @param Index	Index of the pooled object.
	* return		Container holding a reference to a pooled object.
	*				Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindSafeObject(const FECsFX& Type, const int32& Index);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the Interface.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object implements the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindSafeObject(const FECsFX& Type, ICsFXActorPooled* Object);

	/**
	* Safely, via checks, find the container holding a reference to a pooled object in the pool 
	* for the appropriate Type by the UObject.
	*
	* @param Type		Type of pool to add the Object to.
	* @param Object		Object or Object->GetClass() that implements the interface: ICsFXActorPooled.
	* return			Container holding a reference to a pooled object.
	*					Pooled Object or UClass associated with Pooled Object implements
	*					the interface: ICsFXActorPooled.
	*/
	const FCsFXActorPooled* FindSafeObject(const FECsFX& Type, UObject* Object);

#pragma endregion Find

#pragma endregion Pool

	// Update
#pragma region
public:

	virtual void Update(const FCsDeltaTime& DeltaTime);

private:

	FECsFX CurrentUpdatePoolType;

	int32 CurrentUpdatePoolObjectIndex;

protected:

	void OnPreUpdate_Pool(const FECsFX& Type);

	void OnUpdate_Object(const FECsFX& Type, const FCsFXActorPooled* Object);

	void OnPostUpdate_Pool(const FECsFX& Type);

#pragma endregion Update

	// Pause
#pragma region
public:

	/**
	*/
	virtual void Pause(const FECsUpdateGroup& Group, bool bPaused);

	/**
	*/
	virtual void Pause(const FECsFX& Type, bool bPaused);

private:

	TMap<FECsUpdateGroup, FDelegateHandle> OnPauseHandleByGroupMap;

public:

	void BindToOnPause(const FECsUpdateGroup& Group);

#pragma endregion Pause

	// Allocate / Deallocate
#pragma region
public:

	void QueueDeallocateAll();

#pragma endregion Allocate / Deallocate

	// Payload
#pragma region
public:

	/**
	*
	*
	* @param Size
	*/
	void ConstructPayloads(const FECsFX& Type, const int32& Size);

	/**
	* Constructs a payload object for the appropriate Type.
	*  Payload implements the interface: NCsFX::NPayload::IPayload
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsFX::NPayload::IPayload.
	*/
	virtual PayloadType* ConstructPayload(const FECsFX& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsFX::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsFX::NPayload::IPayload.
	*/
	PayloadType* AllocatePayload(const FECsFX& Type);

	/**
	* Get a payload object from a pool of payload objects for the appropriate Type.
	*  Payload implements the interface: NCsFX::NPayload::IPayload.
	*
	* @param Type	Type of payload.
	* return		Payload that implements the interface: NCsFX::NPayload::IPayload.
	*/
	template<typename PayloadImplType>
	FORCEINLINE PayloadImplType* AllocatePayload(const FECsFX& Type)
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
	* @param Type		Type of FX.
	* @param Payload	Object that implements the interface: NCsFX::NPayload::IPayload.
	*/
	const FCsFXActorPooled* Spawn(const FECsFX& Type, PayloadType* Payload);

	/**
	* Delegate type after an FX Actor object has been Spawned.
	* 
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSpawn, const FECsFX& /*Type*/, const FCsFXActorPooled* /*Object*/);

	/** */
	FOnSpawn OnSpawn_Event;

	/** */
	FCsManagerFX_OnSpawn OnSpawn_ScriptEvent;

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
	virtual bool Destroy(const FECsFX& Type, ICsFXActorPooled* Object);

	virtual bool Destroy(ICsFXActorPooled* Object);

	/**
	* Delegate type after an FX Actor object has been Destroyed.
	*
	* @param Type
	* @param Object
	*/
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDestroy, const FECsFX& /*Type*/, const FCsFXActorPooled* /*Object*/);

	FOnDestroy OnDestroy_Event;

#pragma endregion Destroy

	// Log
#pragma region
protected:

	void Log(const FString& /*Str*/);

	void LogTransaction(const FString& Context, const ECsPoolTransaction& Transaction, const FCsFXActorPooled* Object);

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

	// ICsFXActorPooled
#pragma region
public:

#pragma endregion ICsFXActorPooled

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

	TMap<FName, ICsData_FX*> DataMap;

public:

	virtual void DeconstructData(ICsData_FX* Data);

	ICsData_FX* GetData(const FName& Name);

private:

	UPROPERTY()
	TMap<FECsFX, UClass*> ClassMap;

	UPROPERTY()
	TArray<UDataTable*> DataTables;

#pragma endregion Data

// Params
#pragma region
public:

	template<typename ParameterValueType>
	ParameterValueType* AllocateValue();

	/**
	*
	*
	* @param Value 
	*/
	void DeallocateValue(ParameterType* Value);

	// Int
#pragma region

private:

	IntParameterManagerType Manager_Parameter_Int;

public:

	template<>
	FORCEINLINE IntParameterType* AllocateValue<IntParameterType>() { return Manager_Parameter_Int.AllocateResource(); }

private:

	FORCEINLINE void DeallocateValue(IntParameterType* Value) { Manager_Parameter_Int.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Int

	// Float
#pragma region
private:

	FloatParameterManagerType Manager_Parameter_Float;

public:

	template<>
	FORCEINLINE FloatParameterType* AllocateValue<FloatParameterType>() { return Manager_Parameter_Float.AllocateResource(); }

private:

	FORCEINLINE void DeallocateValue(FloatParameterType* Value) { Manager_Parameter_Float.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Float

	// Vector
#pragma region
private:

	VectorParameterManagerType Manager_Parameter_Vector;

public:

	template<>
	FORCEINLINE VectorParameterType* AllocateValue<VectorParameterType>() { return Manager_Parameter_Vector.AllocateResource(); }

private:

	FORCEINLINE void DeallocateValue(VectorParameterType* Value){ Manager_Parameter_Vector.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Vector

	// Scaled
#pragma region
public:

	/**
	*
	*
	* @param Value 
	*/
	void DeallocateValue(ScaledParameterType* Value);

		// Int
#pragma region
private:

	ScaledIntParameterManagerType Manager_Parameter_Scaled_Int;

public:

	template<>
	FORCEINLINE ScaledIntParameterType* AllocateValue<ScaledIntParameterType>() { return Manager_Parameter_Scaled_Int.AllocateResource(); }

private:

	FORCEINLINE void DeallocateValue(ScaledIntParameterType* Value) { Manager_Parameter_Scaled_Int.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Float

		// Float
#pragma region
private:

	ScaledFloatParameterManagerType Manager_Parameter_Scaled_Float;

public:

	template<>
	FORCEINLINE ScaledFloatParameterType* AllocateValue<ScaledFloatParameterType>() { return Manager_Parameter_Scaled_Float.AllocateResource(); }

private:

	FORCEINLINE void DeallocateValue(ScaledFloatParameterType* Value) { Manager_Parameter_Scaled_Float.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Float

		// Vector
#pragma region
private:

	ScaledVectorParameterManagerType Manager_Parameter_Scaled_Vector;

public:

	template<>
	FORCEINLINE ScaledVectorParameterType* AllocateValue<ScaledVectorParameterType>() { return Manager_Parameter_Scaled_Vector.AllocateResource(); }

private:

	FORCEINLINE void DeallocateValue(ScaledVectorParameterType* Value){ Manager_Parameter_Scaled_Vector.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Vector

#pragma endregion Scaled

	// Data Interface
#pragma region

		// Skeletal Mesh
#pragma region
private:

	SkeletalMeshParameterManagerType Manager_Parameter_DataInterface_SkeletalMesh;

public:

	template<>
	FORCEINLINE SkeletalMeshParameterType* AllocateValue<SkeletalMeshParameterType>() { return Manager_Parameter_DataInterface_SkeletalMesh.AllocateResource(); }
	FORCEINLINE void DeallocateValue(SkeletalMeshParameterType* Value) { Manager_Parameter_DataInterface_SkeletalMesh.DeallocateAt(Value, Value->GetIndex()); }

#pragma endregion Skeletal Mesh

#pragma endregion Data Interface

#pragma endregion Params
};