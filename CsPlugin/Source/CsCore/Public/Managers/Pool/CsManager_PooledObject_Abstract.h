// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Containers/CsInterfaceMap.h"
#include "Types/CsCached.h"
// PooledObject
#include "Managers/Pool/CsPooledObject.h"
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/Pool/CsTypes_Manager_PooledObject.h"
// Actor
#include "GameFramework/Actor.h"
// Utility
#include "Utility/CsAllocationOrder.h"
// Timer
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"

class UWorld;
class UObject;
class UClass;

namespace NCsPooledObject
{
	namespace NManager
	{
		// IManager
		#pragma region

		class IManager
		{
		public:

			virtual ~IManager() {}

			virtual const FGuid& GetId() const = 0;

			virtual void Init(const FPoolParams& Params) = 0;

			virtual void Clear() = 0;
			virtual void Shutdown() = 0;

			virtual UWorld* GetCurrentWorld() = 0;

			virtual float GetCurrentTimeSeconds() = 0;

		// Pool
		#pragma region
		public:

			virtual void CreatePool(const int32& Size) = 0;

			virtual const int32& GetPoolSize() const = 0;
			virtual int32 GetAllocatedObjectsSize() const = 0;

			virtual bool IsExhausted() const = 0;

		#pragma endregion Pool

		// Update
		#pragma region
		public:

			virtual void Update(const FCsDeltaTime& DeltaTime) = 0;

			//virtual FCsManagerPooledObject_OnUpdate_Object& GetOnUpdate_Object_Event() = 0;

		#pragma endregion Update

		// Payload
		#pragma region
		public:

			virtual void ConstructPayloads(const int32& Size) = 0;

			virtual void DeconstructPayloads() = 0;

		#pragma endregion Payload

		// Allocate / Deallocate
		#pragma region
		public:

			virtual void QueueDeallocateAll() = 0;

		#pragma endregion Allocate / Deallocate

		// Destroy
		#pragma region
		public:

			virtual bool Destroy(const int32& Index) = 0;
			virtual bool Destroy(UObject* Object) = 0;

		#pragma endregion Destroy

		// Script
		#pragma region
		public:

			virtual FCsPooledObject::FScript_GetCache& GetScript_GetCache_Impl() = 0;

			virtual FCsPooledObject::FScript_Allocate& GetScript_Allocate_Impl() = 0;

			virtual FCsPooledObject::FScript_Deallocate& GetScript_Deallocate_Impl() = 0;

			virtual FCsPooledObject::FScript_Update& GetScript_Update_Impl() = 0;

			virtual FCsPooledObject::FScript_OnConstructObject& GetScript_OnConstructObject_Impl() = 0;

		#pragma endregion Script
		};

		#pragma endregion IManager

		enum class EFunctionNames : uint8
		{
			Update,
			Allocate,
			Deallocate,
			DeallocateAll,
			ConstructPayloads,
			AllocatePayload,
			DeallocatePayload,
			Spawn,
			EFunctionNames_MAX,
		};

		enum class EScopedTimerNames : uint8
		{
			CreatePool,
			Update,
			UpdateObject,
			Allocate,
			AllocateObject,
			Deallocate,
			DeallocateObject,
			Spawn,
			Destroy,
			EScopedTimerNames_MAX,
		};

		/**
		*/
		template<typename InterfaceType, typename InterfaceContainerType, typename PayloadType>
		class TAbstract
		{
			static_assert(std::is_abstract<InterfaceType>(), "NCsPooledObject::NManager::TAbstract: InterfaceType MUST be abstract.");

			// TODO: Check InterfaceType implements _getUObject
 
			static_assert(std::is_base_of<FCsPooledObject, InterfaceContainerType>(), "NCsPooledObject::NManager::TAbstract: InterfaceContainerType is NOT a child of: FCsPooledObject.");

			static_assert(std::is_abstract<PayloadType>(), "NCsPooledObject::NManager::TAbstract: PayloadType MUST be abstract.");

			static_assert(std::is_base_of<ICsGetInterfaceMap, PayloadType>(), "NCsPooledObject::NManager::TAbstract: PayloadType does NOT implement the interface: ICsGetInterfaceMap.");

		private:

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsPooledObject::NCache::ICache CacheType;

		public:

			TAbstract() :
				Name(),
				Id(),
				CurrentWorld(nullptr),
				ConstructContainer_Impl(),
				ConstructObject_Impl(),
				OnConstructObject_Event(),
				ConstructParams(),
				Pool(),
				Links(),
				PoolSize(0),
				PoolIndex(0),
				AdvancePoolIndex(nullptr),
				AllocatedObjects(),
				AllocatedHead(nullptr),
				AllocatedTail(nullptr),
				AllocatedObjectsSize(0),
				AllocationOrder(),
				OnAddToPool_Event(),
				OnAddToPool_UpdateScriptDelegates_Impl(),
				OnUpdate_Object_Event(),
				OnDeallocate_Event(),
				Payloads(),
				PooledObjectPayloads(),
				PayloadSize(0),
				PayloadIndex(0),
				ConstructPayload_Impl(),
				Log_Impl(),
				LogTransaction_Impl(),
				LogType(),
				OnSpawn_Event(),
				Script_GetCache_Impl(),
				Script_Allocate_Impl(),
				Script_Deallocate_Impl(),
				Script_Update_Impl(),
				Script_OnConstructObject_Impl()
			{
				Name = TEXT("NCsPooledObject::NManager::TAbstract");

				Id = FGuid::NewGuid();

				OnAddToPool_Event.Clear();
				OnDeallocate_Event.Clear();

				Pool.Reset();

				AdvancePoolIndex = &TAbstract<InterfaceType, InterfaceContainerType, PayloadType>::AdvancePoolIndexByOrder;

				ConstructContainer_Impl.BindRaw(this, &TAbstract<InterfaceType, InterfaceContainerType, PayloadType>::ConstructContainer);
				ConstructObject_Impl.BindRaw(this, &TAbstract<InterfaceType, InterfaceContainerType, PayloadType>::ConstructObject);

				AllocatedObjects.Reset();

				Payloads.Reset();

				OnSpawn_Event.Clear();
			}

			virtual ~TAbstract()
			{
				Shutdown();
			}

		protected:

			/** */
			FString Name;

		private:

			FGuid Id;

		public:

			FORCEINLINE const FGuid& GetId() const { return Id; }

			/**
			*
			*
			* @param Params
			*/
			virtual void Init(const FPoolParams& Params)
			{
				Name		 = Params.Name;
				CurrentWorld = Params.World;
				LogType		 = Params.LogType;

				ConstructParams = Params.ConstructParams;

				FunctionNames[(uint8)EFunctionNames::Update]			= Name + TEXT("::Update");
				FunctionNames[(uint8)EFunctionNames::Allocate]			= Name + TEXT("::Allocate");
				FunctionNames[(uint8)EFunctionNames::Deallocate]		= Name + TEXT("::Deallocate");
				FunctionNames[(uint8)EFunctionNames::DeallocateAll]		= Name + TEXT("::DeallocateAll");
				FunctionNames[(uint8)EFunctionNames::ConstructPayloads] = Name + TEXT("::ConstructPayloads");
				FunctionNames[(uint8)EFunctionNames::AllocatePayload]	= Name + TEXT("::AllocatePayload");
				FunctionNames[(uint8)EFunctionNames::DeallocatePayload] = Name + TEXT("::DeallocatePayload");
				FunctionNames[(uint8)EFunctionNames::Spawn]				= Name + TEXT("::Spawn");

				// Set Scoped Timer CVars
				ScopedGroup = Params.ScopedGroup;

				ScopedTimerNames[(uint8)EScopedTimerNames::CreatePool]		= Name + TEXT("_CreatePool");
				ScopedTimerNames[(uint8)EScopedTimerNames::Update]			= Name + TEXT("_Update");
				ScopedTimerNames[(uint8)EScopedTimerNames::UpdateObject]	= Name + TEXT("_UpdateObject");
				ScopedTimerNames[(uint8)EScopedTimerNames::Allocate]		= Name + TEXT("_Allocate");
				ScopedTimerNames[(uint8)EScopedTimerNames::AllocateObject]	= Name + TEXT("_AllocateObject");
				ScopedTimerNames[(uint8)EScopedTimerNames::Deallocate]		= Name + TEXT("_Deallocate");
				ScopedTimerNames[(uint8)EScopedTimerNames::DeallocateObject] = Name + TEXT("_DeallocateObject");
				ScopedTimerNames[(uint8)EScopedTimerNames::Spawn]			= Name + TEXT("_Spawn");
				ScopedTimerNames[(uint8)EScopedTimerNames::Destroy]			= Name + TEXT("_Destroy");

				CreatePoolScopedTimerCVar		= Params.CreatePoolScopedTimerCVar;
				UpdateScopedTimerCVar			= Params.UpdateScopedTimerCVar;
				UpdateObjectScopedTimerCVar		= Params.UpdateObjectScopedTimerCVar;
				AllocateScopedTimerCVar			= Params.AllocateScopedTimerCVar;
				AllocateObjectScopedTimerCVar	= Params.AllocateObjectScopedTimerCVar;
				DeallocateScopedTimerCVar		= Params.DeallocateScopedTimerCVar;
				DeallocateObjectScopedTimerCVar = Params.DeallocateObjectScopedTimerCVar;
				DeallocateObjectScopedTimerCVar = Params.DeallocateObjectScopedTimerCVar;
				SpawnScopedTimerCVar			= Params.SpawnScopedTimerCVar;
				DestroyScopedTimerCVar			= Params.DestroyScopedTimerCVar;

				// Scoped Timers
				CS_GET_SCOPED_TIMER_HANDLE(CreatePoolScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::CreatePool]), ScopedGroup, CreatePoolScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(UpdateScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::Update]), ScopedGroup, UpdateScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(UpdateObjectScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::UpdateObject]), ScopedGroup, UpdateObjectScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(AllocateScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::Allocate]), ScopedGroup, AllocateScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(AllocateObjectScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::AllocateObject]), ScopedGroup, AllocateObjectScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(DeallocateScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::Deallocate]), ScopedGroup, DeallocateScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(DeallocateObjectScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::DeallocateObject]), ScopedGroup, DeallocateObjectScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(SpawnScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::Spawn]), ScopedGroup, SpawnScopedTimerCVar);
				CS_GET_SCOPED_TIMER_HANDLE(DestroyScopedTimerHandle, &(ScopedTimerNames[(uint8)EScopedTimerNames::Destroy]), ScopedGroup, DestroyScopedTimerCVar);

				// Check to Construct Payloads
				if (Params.bConstructPayloads)
				{
					checkf(Params.PayloadSize > 0, TEXT("%s::Init: PayloadSize must be GREATER THAN 0."), *Name);

					ConstructPayloads(Params.PayloadSize);
				}
				// Check to Create Pool
				if (Params.bCreatePool)
				{
					checkf(Params.PoolSize > 0, TEXT("%s::Init: PoolSize must be GREATER THAN 0."), *Name);

					CreatePool(Params.PoolSize);
				}
			}

			/**
			*
			*/
			virtual void Clear()
			{
				for (InterfaceContainerType* O : Pool)
				{
					if (O->IsObject())
					{
						if (UObject* Object = O->GetSafeObject())
						{
							if (IsValid(Object))
							{
								O->Deallocate();
								O->Shutdown();
								DeconstructObject(O);
							}
						}
					}
					else
					{
						O->Deallocate();
						O->Shutdown();
						DeconstructObject(O);
					}
					delete O;
				}

				Pool.Reset();
				PoolSize = 0;
				AllocatedObjects.Reset();
				AllocationOrder.Shutdown();

				for (PooledPayloadType* P : PooledObjectPayloads)
				{
					P->Reset();
				}
				OnAddToPool_Event.Clear();
				OnDeallocate_Event.Clear();
			}

			/**
			*
			*/
			virtual void Shutdown()
			{
				Clear();

				// Links
				{
					const int32 Count = Links.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						TCsDoubleLinkedList<InterfaceContainerType*>* L = Links[I];
						delete L;
						Links[I] = nullptr;
					}
					Links.Reset();
				}
				// Payloads
				{
					const int32 Count = Payloads.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						PayloadType* P = Payloads[I];
						delete P;
						Payloads[I] = nullptr;
					}
					Payloads.Reset();
					PooledObjectPayloads.Reset();
				}

				OnUpdate_Object_Event.Clear();

				// Scoped Timer
				CS_CLEAR_SCOPED_TIMER_HANDLE(CreatePoolScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(UpdateScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(UpdateObjectScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(AllocateScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(AllocateObjectScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(DeallocateScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(DeallocateObjectScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(SpawnScopedTimerHandle);
				CS_CLEAR_SCOPED_TIMER_HANDLE(DestroyScopedTimerHandle);
			}

			/** */
			TWeakObjectPtr<UWorld> CurrentWorld;

			/**
			*
			*
			* return	World associated with the pool.
			*/
			UWorld* GetCurrentWorld()
			{
				return CurrentWorld.IsValid() ? CurrentWorld.Get() : nullptr;
			}

			/**
			* Get the current time in seconds.
			*
			* return	Current time in seconds.
			*/
			virtual float GetCurrentTimeSeconds()
			{
				return GetCurrentWorld() ? GetCurrentWorld()->GetTimeSeconds() : 0.0f;
			}

			/**
			*
			* return Container
			*/
			TDelegate<InterfaceContainerType*()> ConstructContainer_Impl;

		protected:

			FORCEINLINE InterfaceContainerType* ConstructContainer()
			{
				return new InterfaceContainerType();
			}

		// Object
		#pragma region
		public:

			/**
			* Creates a pooled object of type ICsPooledObject.
			*
			* return
			*/
			InterfaceContainerType* ConstructObject(const FConstructParams& Params)
			{
				UClass* Class = Params.Class;

				checkf(Class, TEXT("%s::ConstructObject: No Class set."), *Name);

				UObject* Object = nullptr;

				// Actor
				if (Params.ConstructionType == NCsPooledObject::EConstruction::Actor)
				{
					AActor* Actor = GetCurrentWorld()->template SpawnActor<AActor>(Class, Params.ConstructionInfo);

					checkf(IsValid(Actor), TEXT("%s::ConstructObject: Actor is NULL. Class: %s. Actor did NOT spawn."), *Name, *(Class->GetName()));

					if (!Params.bReplicates)
					{
						Actor->SetReplicates(false);
						Actor->SetRole(ROLE_None);
						GetCurrentWorld()->RemoveNetworkActor(Actor);
					}

					Object = Actor;
				}
				// Object
				else
				if (Params.ConstructionType == NCsPooledObject::EConstruction::Object)
				{
					checkf(Params.Outer, TEXT("%s::ConstructObject: Params.Outer is NULL. This should be Valid if Params.ConstructionType == NCsPooledObject::EConstruction::Object."), *Name)

					Object = NewObject<UObject>(Params.Outer, Class);

					checkf(Object, TEXT("%s::ConstructObject: Object is NULL. Class: %s. Object did NOT get constructed."), *Name, *(Class->GetName()));
				}
				// Custom Object
				else
				if (Params.ConstructionType == NCsPooledObject::EConstruction::CustomObject)
				{
					checkf(Params.CustomNewObject_Impl.IsBound(), TEXT("%s::ConstructObject: Params.CustomNewObject_Impl is NOT Bound. This should be Bound if Params.ConstructionType == NCsPooledObject::EConstruction::CustomObject."), *Name);

					Object = Params.CustomNewObject_Impl.Execute(Params);

					checkf(Object, TEXT("%s::ConstructObject: Object is NULL. Class: %s. Object did NOT get constructed."), *Name, *(Class->GetName()));
				}

				if (Object)
				{
					InterfaceContainerType* O = ConstructContainer_Impl.Execute();

					O->SetObject(Object);

					// Bind the appropriate Script delegates.
					O->Script_GetCache_Impl			 = Script_GetCache_Impl;
					O->Script_Allocate_Impl			 = Script_Allocate_Impl;
					O->Script_Deallocate_Impl		 = Script_Deallocate_Impl;
					O->Script_Update_Impl			 = Script_Update_Impl;
					O->Script_OnConstructObject_Impl = Script_OnConstructObject_Impl;

		#if WITH_EDITOR

					const FString ObjectName = Object->GetName();
					const FString ClassName  = Class->GetName();

					// ICsPooledObject Script Interface
					if (O->IsScript())
					{
						checkf(O->Script_GetCache_Impl.IsBound(), TEXT("%s::ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Update_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

						checkf(O->Script_Allocate_Impl.IsBound(), TEXT("%s::ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Allocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

						checkf(O->Script_Deallocate_Impl.IsBound(), TEXT("%s::ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Deallocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
					}
					// ICsUpdate Script Interface
					if (O->IsScriptUpdate())
					{
						checkf(O->Script_Update_Impl.IsBound(), TEXT("%s::ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsUpdate. Script_Update_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
					}
					// ICsOnConstructObject Script Interface
					if (O->IsScriptOnConstructObject())
					{
						checkf(O->Script_OnConstructObject_Impl.IsBound(), TEXT("%s::ConstructObject: Object: %s with Class: %s implements a script interface of type: ICsOnConstructObject. Script_OnConstructObject_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
					}
		#endif // #if WITH_EDITOR

					if (O->Implements_ICsOnConstructObject())
					{
						O->OnConstructObject(Params);
					}
					OnConstructObject_Event.Broadcast(O, Params);

					return O;
				}
				checkf(0, TEXT("%s:ConstructObject: Failed to Construct Object with Class: %s."), *Name, *(Class->GetName()));
				return nullptr;
			}

			/**
			*
			*
			* return Object
			*/
			TDelegate<InterfaceContainerType* /*Object*/(const FConstructParams& /*Params*/)> ConstructObject_Impl;

			/**
			*
			*
			* @param Object
			*/
			TMulticastDelegate<void(const InterfaceContainerType* /*Object*/, const FConstructParams& /*Params*/)> OnConstructObject_Event;

			/**
			* Delete (or mark for deconstruction) a pooled object.
			*
			* @param Object		Container holding a pooled object.
			*/
			virtual void DeconstructObject(InterfaceContainerType* Object)
			{
				// For Actors, Do Nothing. Let the World handle destruction
				//if (AActor* A = Object->template GetSafeObject<AActor>())
				//	return;
				if (UObject* O = Object->GetSafeObject())
					O->MarkAsGarbage();
			}

			/**
			* Get the name of a pooled object.
			*
			* @param Object		Container holding a pooled object.
			* return			Name of the pooled object.
			*/
			virtual FString GetObjectName(const InterfaceContainerType* Object)
			{
				if (Object->IsObject())
					return Object->GetObject()->GetName();
				return NCsCached::Str::Empty;
			}

		#pragma endregion Object

		// Pool
		#pragma region
		protected:

			/** */
			FString FunctionNames[(uint8)EFunctionNames::EFunctionNames_MAX];

			/** */
			FConstructParams ConstructParams;

			/** */
			TArray<InterfaceContainerType*> Pool;
			/** */
			TArray<TCsDoubleLinkedList<InterfaceContainerType*>*> Links;
			/** */
			int32 PoolSize;
			/** */
			int32 PoolIndex;

			void (TAbstract<InterfaceType, InterfaceContainerType, PayloadType>::*AdvancePoolIndex)();

			/** */
			TArray<InterfaceContainerType*> AllocatedObjects;
			/** */
			TCsDoubleLinkedList<InterfaceContainerType*>* AllocatedHead;
			/** */
			TCsDoubleLinkedList<InterfaceContainerType*>* AllocatedTail;
			/** */
			int32 AllocatedObjectsSize;

			FCsAllocationOrder AllocationOrder;

		public:

			/**
			*
			*
			* @param Size
			*/
			void CreatePool(const int32& Size)
			{
				CS_SCOPED_TIMER(CreatePoolScopedTimerHandle);

				checkf(Size > 0, TEXT("%s::CreatePool: Size must be GREATER THAN 0."), *Name);

				PoolSize = Size;

				Pool.Reset(PoolSize);
				Links.Reset(PoolSize);
				AllocatedObjects.Reset(PoolSize);
				AllocationOrder.Create(PoolSize);

				for (int32 I = 0; I < Size; ++I)
				{
					InterfaceContainerType* O = ConstructObject_Impl.Execute(ConstructParams);

					checkf(O, TEXT("%s::CreatePool: Failed to ConstructObject of type: InterfaceContainerType."), *Name);

					UObject* Object	= O->GetObject();

		#if WITH_EDITOR
					const FString ObjectName = Object->GetName();
					UClass* Class			 = Object->GetClass();
					const FString ClassName  = Class->GetName();

					// ICsPooledObject Script Interface
					if (O->IsScript())
					{
						checkf(O->Script_GetCache_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_GetCache_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

						checkf(O->Script_Allocate_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Allocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

						checkf(O->Script_Deallocate_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Deallocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
					}
					// ICsUpdate Script Interface
					if (O->IsScriptUpdate())
					{
						checkf(O->Script_Update_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsUpdate. Script_Update_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
					}
					// ICsOnConstructObject Script Interface
					if (O->IsScriptOnConstructObject())
					{
						checkf(O->Script_OnConstructObject_Impl.IsBound(), TEXT("%s:CreatePool: Object: %s with Class: %s implements a script interface of type: ICsOnConstructObject. Script_OnConstructObject_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
					}
		#endif // #if WTIH_EDITOR

					CacheType* Cache = O->GetCache();

					checkf(Cache, TEXT("%s::CreatePool: Failed to get Cache of type: NCsPooledObject::NCache::ICache."), *Name);

					Cache->Init(I);
					O->Deallocate();

					Pool.Add(O);

					// Add Link
					Links.Add(new TCsDoubleLinkedList<InterfaceContainerType*>());
					// Set Element for Link
					TCsDoubleLinkedList<InterfaceContainerType*>* Link = Links.Last();
					(**Link)										   = O;

					OnAddToPool_Event.Broadcast(O);
				}
			}

			// Add
		#pragma region
		public:

				// Pool
		#pragma region
		public:

			/**
			* Adds an Object to the pool.
			*  The Object must implement the interface: ICsPooledObject.
			*
			* @param InterfaceObject	Object that implements the interface: ICsPooledObject.
			* @param Object				UObject reference.
			* @param DeallocateOnAdd
			* return					Container holding a reference to a pooled object.
			*							Pooled Object implements the interface: ICsPooledObject.
			*/
			const InterfaceContainerType* AddToPool(InterfaceType* InterfaceObject, UObject* Object, bool DeallocateOnAdd = true)
			{
				checkf(Object, TEXT("%s::AddToPool: Object is NULL."), *Name);

				InterfaceContainerType* O = ConstructContainer_Impl.Execute();

				checkf(O, TEXT("%s::AddToPool: Failed to Construct Container of type: InterfaceContainerType."), *Name);

				Pool.Add(O);

				O->SetObject(Object);

				O->Script_GetCache_Impl   = Script_GetCache_Impl;
				O->Script_Allocate_Impl   = Script_Allocate_Impl;
				O->Script_Deallocate_Impl = Script_Deallocate_Impl;
				O->Script_Update_Impl	 = Script_Update_Impl;

				CacheType* Cache = O->GetCache();

				checkf(Cache, TEXT("%s::AddToPool: Cache is NULL."), *Name);

				const int32& Index = Cache->GetIndex();

				checkf(Index == INDEX_NONE, TEXT("%s::AddToPool: PooledObject is already a part of an existing pool."), *Name);

		#if WITH_EDITOR
				const FString ObjectName = Object->GetName();
				UClass* Class			 = Object->GetClass();
				const FString ClassName  = Class->GetName();

				// ICsPooledObject Script Interface
				if (O->IsScript())
				{
					checkf(O->Script_GetCache_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_GetCache_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

					checkf(O->Script_Allocate_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Allocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);

					checkf(O->Script_Deallocate_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsPooledObject. Script_Deallocate_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
				}
				// ICsUpdate Script Interface
				if (O->IsScriptUpdate())
				{
					checkf(O->Script_Update_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsUpdate. Script_Update_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
				}
				// ICsOnConstructObject Script Interface
				if (O->IsScriptOnConstructObject())
				{
					checkf(O->Script_OnConstructObject_Impl.IsBound(), TEXT("%s:AddToPool: Object: %s with Class: %s implements a script interface of type: ICsOnConstructObject. Script_OnConstructObject_Impl is NOT bound to any function."), *Name, *ObjectName, *ClassName);
				}
		#endif // #if WITH_EDITOR

				Cache->Init(PoolSize);

				if (DeallocateOnAdd)
					O->Deallocate();

				// Add Link
				Links.Add(new TCsDoubleLinkedList<InterfaceContainerType*>());
				// Set Element for Link
				TCsDoubleLinkedList<InterfaceContainerType*>* Link = Links.Last();
				(**Link) = O;

				AllocationOrder.Add();

				++PoolSize;

				OnAddToPool_UpdateScriptDelegates_Impl.ExecuteIfBound(O);
				OnAddToPool_Event.Broadcast(O);

				return O;
			}

			/**
			* Adds an Object to the pool.
			*  Object must implement the interface: ICsPooledObject.
			*
			* @param Type				Type of pool to add the Object to.
			* @param Object				Object that implements the interface: ICsPooledObject.
			* @param DeallocateOnAdd
			* return					Container holding a reference to a pooled object.
			*							Pooled Object implements the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* AddToPool(InterfaceType* Object, bool DeallocateOnAdd = true)
			{
				return AddToPool(Object, Object->_getUObject(), DeallocateOnAdd);
			}

			template<typename OtherInterfaceType, typename ContainerType>
			FORCEINLINE const ContainerType* AddToPool(OtherInterfaceType* Object, bool DeallocateOnAdd = true)
			{
				static_assert(std::is_abstract<OtherInterfaceType>(), "NCsPooledObject::NManager::TAbstract::AddToPool: OtherInterfaceType is NOT an abstract class.");

				static_assert(std::is_base_of<InterfaceContainerType, ContainerType>(), "NCsPooledObject::NManager::TAbstract::AddToPool: ContainerType is NOT a child of InterfaceContainerType.");

		#if WITH_EDITOR
				const ContainerType* Ptr = dynamic_cast<const ContainerType*>(AddToPool(Object, DeallocateOnAdd));

				checkf(Ptr, TEXT("%s::AddToPool: Failed to cast to ContainerType."), *Name);

				return Ptr;
		#else
				return static_cast<ContainerType*>(AddToPool(Object->_getUObject(), DeallocateOnAdd));
		#endif // #if WITH_EDITOR
			}

			/**
			* Adds an Object to the pool.
			*  Object must implement the interface: ICsPooledObject or the UClass
			*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
			*
			* @param Object				Object or Object->GetClass() that implements the interface: ICsPooledObject.
			* @param DeallocateOnAdd
			* return					Container holding a reference to a pooled object.
			*							Pooled Object or UClass associated with Pooled Object implements
			*							the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* AddToPool(UObject* Object, bool DeallocateOnAdd = true)
			{
				return AddToPool(nullptr, Object, DeallocateOnAdd);
			}

			template<typename ContainerType>
			FORCEINLINE const ContainerType* AddToPool(UObject* Object, bool DeallocateOnAdd = true)
			{
				static_assert(std::is_base_of<InterfaceContainerType, ContainerType>(), "NCsPooledObject::NManager::TAbstract::AddToPool ContainerType is NOT a child of InterfaceContainerType.");
		
		#if WITH_EDITOR
				const ContainerType* Ptr = dynamic_cast<const ContainerType*>(AddToPool(Object, DeallocateOnAdd));

				checkf(Ptr, TEXT("%s::AddToPool: Failed to cast to ContainerType."), *Name);

				return Ptr;
		#else
				return static_cast<const ContainerType*>(AddToPool(Object, DeallocateOnAdd));
		#endif // #if WITH_EDITOR
			}

			/** Delegate called after Adding an Object to the pool.
			*
			* @param Object
			*/
			TMulticastDelegate<void(const InterfaceContainerType* /*Object*/)> OnAddToPool_Event;

			/**
			* 
			*
			* @param Object
			*/
			TDelegate<void(InterfaceContainerType* /*Object*/)> OnAddToPool_UpdateScriptDelegates_Impl;

		#pragma endregion Pool

				// Allocated Objects
		#pragma region

			/**
			* Adds an Object to the allocated objects. 
			* If the Object is NOT added to the pool, add it to the pool.
			*  Object must implement the interface: ICsPooledObject.
			*
			* @param InterfaceObject	Object that implements the interface: ICsPooledObject.
			* @param Object				UObject reference.
			* return					Container holding a reference to a pooled object.
			*							Pooled Object implements the interface: ICsPooledObject.
			*/
			const InterfaceContainerType* AddToAllocatedObjects(InterfaceType* InterfaceObject, UObject* Object)
			{
				checkf(Object, TEXT("%s:AddToAllocatedObjects: Object is NULL."), *Name);

				int32 Index   = INDEX_NONE;
				UClass* Class = Object->GetClass();

				// Interface
				if (ICsPooledObject* P = Cast<ICsPooledObject>(Object))
				{
					CacheType* Cache = P->GetCache();

					checkf(Cache, TEXT("%s::AddToAllocatedObjects: Cache is NULL."), *Name);

					Index = Cache->GetIndex();
				}
				// Script Interface
				else
				if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
				{
					checkf(Script_GetCache_Impl.IsBound(), TEXT("%s:AddToAllocatedObjects: Script_GetCache_Impl is NOT bound to any function."), *Name);

					Index = Script_GetCache_Impl.Execute(Object)->GetIndex();
				}
				else
				{
					checkf(0, TEXT("%s:AddToAllocatedObjects: Object: %s with Class: %s does NOT implement the interface: ICsPooledObject."), *Name, *(Object->GetName()), *(Class->GetName()));
				}

				// Add to pool
				if (Index == INDEX_NONE)
				{
					const InterfaceContainerType* O = AddToPool(InterfaceObject, Object, false);

					AddToAllocatedObjects_Internal(const_cast<InterfaceContainerType*>(O));

					return O;
				}
				// Already exists in pool
				else
				{
					checkf(PoolSize > 0, TEXT("%s:AddToAllocatedObjects: No pool created. Call CreatePool."), *Name);

					checkf(Index >= 0 && Index < PoolSize, TEXT("%s:AddToAllocatedObjects: Index: %d is NOT Valid for this pool."), *Name, Index);

					InterfaceContainerType* O = Pool[Index];

					CacheType* Cache = O->GetCache();

					checkf(Cache, TEXT("%s::AddToAllocatedObjects: Cache is NULL."), *Name);

					if (Cache->IsAllocated())
						return O;

					AddToAllocatedObjects_Internal(O);

					return O;
				}
			}

			/**
			* Adds an Object to the Allocated Objects.
			* If the Object is NOT added to the pool, add it to the pool.
			*  Object must implement the interface: ICsPooledObject.
			*
			* @param Type		Type of pool to add the Object to.
			* @param Object		Object that implements the interface: ICsPooledObject.
			* return			Container holding a reference to a pooled object.
			*					Pooled Object implements the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* AddToAllocatedObjects(InterfaceType* Object)
			{
				checkf(Object, TEXT("%s::AddToAllocatedObjects: Object is NULL."));

				return AddToAllocatedObjects(Object, Object->_getUObject());
			}

			/**
			* Adds an Object to the allocated objects.
			* If the Object is NOT added to the pool, add it to the pool.
			*  Object must implement the interface: ICsPooledObject or the UClass
			*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
			*
			* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
			* return			Container holding a reference to a pooled object.
			*					Pooled Object or UClass associated with Pooled Object implements
			*					the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* AddToAllocatedObjects(UObject* Object)
			{
				return AddToAllocatedObjects(nullptr, Object);
			}

		protected:

			/**
			*
			*
			* @param Object
			*/
			virtual void AddToAllocatedObjects_Internal(InterfaceContainerType* Object)
			{
				const int32& Index = Object->GetCache()->GetIndex();

				TCsDoubleLinkedList<InterfaceContainerType*>* Link = Links[Index];

				AddAllocatedLink(Link);
				AllocatedObjects.Add(Object);

				AllocatedObjectsSize = AllocatedObjects.Num();
			}

		#pragma endregion Allocated Objects

		#pragma endregion Add

			// Linked List
		#pragma region
		public:

			/**
			* Get the current head (first object) of the allocated linked list.
			*
			* return Allocated Head.
			*/
			FORCEINLINE const TCsDoubleLinkedList<InterfaceContainerType*>* GetAllocatedHead()
			{
				return AllocatedHead;
			}

			/**
			* Get the current head (first object) of the allocated linked list.
			*
			* return Allocated Head.
			*/
			FORCEINLINE const InterfaceContainerType* GetAllocatedHeadObject()
			{
				return AllocatedHead ? **AllocatedHead : nullptr;
			}

			/**
			* Get the current tail (last object) of the allocated linked list.
			*
			* return Allocated Tail.
			*/
			FORCEINLINE const TCsDoubleLinkedList<InterfaceContainerType*>* GetAllocatedTail()
			{
				return AllocatedTail;
			}

		protected:

			/**
			*
			*
			* @param Link
			*/
			FORCEINLINE void AddAllocatedLink(TCsDoubleLinkedList<InterfaceContainerType*>* Link)
			{
				if (AllocatedTail)
				{
					Link->LinkAfter(AllocatedTail);
					AllocatedTail = Link;
				}
				else
				{
					AllocatedHead = Link;
					AllocatedTail = AllocatedHead;
				}
			}

			/**
			*
			*
			* @param Link
			*/
			FORCEINLINE void RemoveAllocatedLink(TCsDoubleLinkedList<InterfaceContainerType*>* Link)
			{
				// Check to Update HEAD
				if (Link == AllocatedHead)
				{
					AllocatedHead = Link->GetNextLink();

					if (!AllocatedHead)
					{
						checkf(Link == AllocatedTail, TEXT("%s::RemoveAllocatedLink: Link == AllocatedHead == AllocatedTail."), *Name);

						AllocatedTail = nullptr;
					}
				}
				// Check to Update TAIL
				else
				if (Link == AllocatedTail)
				{
					AllocatedTail = Link->GetPrevLink();
				}
				Link->Unlink();
			}

		#pragma endregion Linked List

		public:

			/**
			* Get the pool.
			*  Pool is an array of containers holding references to objects that
			*  implement the interface: ICsPooledObject.
			*
			* return	Pool
			*/
			FORCEINLINE const TArray<InterfaceContainerType*>& GetPool() const
			{
				return Pool;
			}

			/**
			* Get the allocated objects.
			*  Allocated Objects are an array of containers holding references to objects that
			*  implement the interface: ICsPooledObject.
			*
			* return	Allocated Objects
			*/
			FORCEINLINE const TArray<InterfaceContainerType*>& GetAllocatedObjects() const
			{
				return AllocatedObjects;
			}

			/**
			* Get the number of elements in the pool.
			*
			* return	Number of elements in the pool.
			*/
			FORCEINLINE const int32& GetPoolSize() const
			{
				return PoolSize;
			}

			/**
			* Get the number of allocated objects.
			*
			* return	Number of allocated objects.
			*/
			FORCEINLINE int32 GetAllocatedObjectsSize() const
			{
				return AllocatedObjectsSize;
			}

			/**
			* Get whether all elements in the pool have been allocated.
			*
			* return	All elements allocated or not.
			*/
			FORCEINLINE bool IsExhausted() const
			{
				return AllocatedObjectsSize == PoolSize;
			}

			FORCEINLINE void AdvancePoolIndexByIncrement() { PoolIndex = (PoolIndex + 1) % PoolSize; }

			FORCEINLINE void AdvancePoolIndexByOrder() { PoolIndex = AllocationOrder.Advance(); }

			// Find
		#pragma region
		public:

			/**
			* Find the container holding a reference to a pooled object in the pool by Index.
			*
			* @param Index	Index of the pooled object.
			* return		Container holding a reference to a pooled object.
			*				Pooled Object implements the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* FindObject(const int32& Index)
			{
				checkf(Index > INDEX_NONE && Index < PoolSize, TEXT("FCsManager_PooledObject::FindObject: Index: %d is NOT valid for pool."), Index);

				return Pool[Index];
			}

			/**
			* Find the container holding a reference to a pooled object in the pool by Interface.
			*  Object must implement the interface: ICsPooledObject.
			*
			* @param Object		Object of interface type: ICsPooledObject.
			* return			Container holding a reference to a pooled object.
			*					Pooled Object implements the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* FindObject(InterfaceType* Object)
			{
				checkf(Object, TEXT("%s::FindObject: Object is NULL."), *Name);

				return FindObject(Object->_getUObject());
			}

			/**
			* Find the container holding a reference to a pooled object in the pool by UObject.
			*  Object must implement the interface: ICsPooledObject or the UClass
			*  associated with the Object have ImplementsInterface(UCsPooledObject::StaticClass()) == true.
			*
			* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
			* return			Container holding a reference to a pooled object.
			*					Pooled Object or UClass associated with Pooled Object implements
			*					the interface: ICsPooledObject.
			*/
			const InterfaceContainerType* FindObject(UObject* Object)
			{
				checkf(Object, TEXT("%s::FindObject: Object is NULL."), *Name);

				UClass* Class = Object->GetClass();
				int32 Index   = INDEX_NONE;

				// Interface
				if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
				{
					CacheType* Cache = Interface->GetCache();

					checkf(Cache, TEXT("%s::FindObject: Cache is NULL."), *Name);

					Index = Cache->GetIndex();
				}
				// Script Interface
				else
				if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
				{
					checkf(Script_GetCache_Impl.IsBound(), TEXT("%s::FindObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl Bound to any function."), *Name, *(Object->GetName()), *(Class->GetName()));

					Index = Script_GetCache_Impl.Execute(Object)->GetIndex();
				}
				// INVALID
				else
				{
					checkf(false, TEXT("%s::FindObject: Object: %s with Class: %s does NOT implement interface: ICsPooledObject."), *Name, *(Object->GetName()), *(Class->GetName()));

					return nullptr;
				}
	
				checkf(Index > INDEX_NONE && Index < PoolSize, TEXT("%s::FindObject: Object: %s with Class: %s is already in a pool."), *Name, *(Object->GetName()), *(Class->GetName()));

				InterfaceContainerType* O = Pool[Index];

				checkf(O->GetObject() == Object, TEXT("%s::FindObject: Object: %s with Class: %s is NOT this pool."), *Name, *(Object->GetName()), *(Class->GetName()));

				return O;
			}

			/**
			* Safely, via checks, find the container holding a reference to a pooled object in the pool by Index.
			*
			* @param Index	Index of the pooled object.
			* return		Container holding a reference to a pooled object.
			*				Pooled Object implements the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* FindSafeObject(const int32& Index)
			{
				if (Index < 0 || Index >= PoolSize)
					return nullptr;
				return Pool[Index];
			}

			/**
			* Safely, via checks, find the container holding a reference to a pooled object in the pool by the Interface.
			*
			* @param Object		Object that implements the interface: ICsPooledObject.
			* return			Container holding a reference to a pooled object.
			*					Pooled Object implements the interface: ICsPooledObject.
			*/
			FORCEINLINE const InterfaceContainerType* FindSafeObject(InterfaceType* Object)
			{
				if (!Object)
					return nullptr;

				return FindSafeObject(Object->_getUObject());
			}

			/**
			* Safely, via checks, find the container holding a reference to a pooled object in the pool by the UObject.
			*
			* @param Object		Object or Object->GetClass() that implements the interface: ICsPooledObject.
			* return			Container holding a reference to a pooled object.
			*					Pooled Object or UClass associated with Pooled Object implements
			*					the interface: ICsPooledObject.
			*/
			const InterfaceContainerType* FindSafeObject(UObject* Object)
			{
				if (!Object)
					return nullptr;

				UClass* Class = Object->GetClass();
				int32 Index   = INDEX_NONE;

				// Interface
				if (ICsPooledObject* Interface = Cast<ICsPooledObject>(Object))
				{
					CacheType* Cache = Interface->GetCache();

					checkf(Cache, TEXT("%s::FindSafeObject: Cache is NULL."), *Name);

					Index = Cache->GetIndex();
				}
				// Script Interface
				else
				if (Class->ImplementsInterface(UCsPooledObject::StaticClass()))
				{
					if (!Script_GetCache_Impl.IsBound())
						return nullptr;

					Index = Script_GetCache_Impl.Execute(Object)->GetIndex();
				}
				// INVALID
				else
				{
					return nullptr;
				}
	
				if (Index == INDEX_NONE && Index >= PoolSize)
					return nullptr;

				InterfaceContainerType* O = Pool[Index];

				if (O->GetObject() != Object)
					return nullptr;

				return O;
			}

		#pragma endregion Find
	 
		#pragma endregion Pool

		// Update
		#pragma region
		public:

			/**
			*
			*
			* @param DeltaTime
			*/
			void Update(const FCsDeltaTime& DeltaTime)
			{
				CS_SCOPED_TIMER(UpdateScopedTimerHandle);

				const FString& Context = FunctionNames[(uint8)EFunctionNames::Update];

				TCsDoubleLinkedList<InterfaceContainerType*>* Current = AllocatedHead;
				TCsDoubleLinkedList<InterfaceContainerType*>* Next	  = Current;

				int32 NewSize = 0;

				while (Next)
				{
					CS_SCOPED_TIMER(UpdateObjectScopedTimerHandle);

					Current					  = Next;
					InterfaceContainerType* O = **Current;
					Next					  = Current->GetNextLink();

					CacheType* Cache = O->GetCache();

					checkf(Cache, TEXT("%s::Update: Cache is NULL."), *Name);

					if (Cache->GetUpdateType() == NCsPooledObject::EUpdate::Manager)
					{
						O->Update(DeltaTime);
					}

					// Check if PooledObject is queued for Deallocation
					if (Cache->ShouldDeallocate())
					{
						CS_NON_SHIPPING_EXPR(LogTransaction_Impl.Execute(Context, ECsPoolTransaction::DeallocateByQueue, O));
						O->Deallocate();

						checkf(!Cache->IsAllocated(), TEXT("%s: Failed to deallocate object."), *Context);

						RemoveAllocatedLink(Current);
						AllocationOrder.Promote(Cache->GetIndex());

						OnDeallocate_Event.Broadcast(O);
						continue;
					}

					// Check if PooledObject was Deallocated NOT in a normal way (i.e. Out of Bounds)
					if (!Cache->IsAllocated())
					{
						CS_NON_SHIPPING_EXPR(LogTransaction_Impl.Execute(Context, ECsPoolTransaction::DeallocateByUnknown, O));
						RemoveAllocatedLink(Current);
						AllocationOrder.Promote(Cache->GetIndex());
						continue;
					}

					// Check if PooledObject LifeTime has expired.
					if (Cache->HasLifeTimeExpired())
					{
						CS_NON_SHIPPING_EXPR(LogTransaction_Impl.Execute(Context, ECsPoolTransaction::DeallocateByLifeTime, O));
						O->Deallocate();

						checkf(!Cache->IsAllocated(), TEXT("%s: Failed to deallocate object."), *Context);

						RemoveAllocatedLink(Current);
						AllocationOrder.Promote(Cache->GetIndex());

						OnDeallocate_Event.Broadcast(O);
						continue;
					}

					if (NewSize < AllocatedObjectsSize)
					{
						AllocatedObjects[NewSize] = O;
					}

					OnUpdate_Object_Event.Broadcast(O);
					++NewSize;
				}

				for (int32 I = AllocatedObjectsSize - 1; I >= NewSize; --I)
				{
					AllocatedObjects.RemoveAt(I, 1, false);
				}
				AllocatedObjectsSize = AllocatedObjects.Num();
			}

			/**
			*
			* @param Object
			*/
			TMulticastDelegate<void(const InterfaceContainerType* /*Object*/)> OnUpdate_Object_Event;

		#pragma endregion Update

		// Pause
		#pragma region
		public:

			/**
			* 
			* 
			* @param bPaused	Whether to pause or un-pause
			*/
			void Pause(bool bPaused)
			{
				TCsDoubleLinkedList<InterfaceContainerType*>* Current = AllocatedHead;
				TCsDoubleLinkedList<InterfaceContainerType*>* Next    = Current;

				while (Next)
				{
					Current					  = Next;
					InterfaceContainerType* O = **Current;
					Next					  = Current->GetNextLink();

					O->Pause(bPaused);
				}
			}

		#pragma endregion Pause

		// Allocate / Deallocate
		#pragma region
		public:

			FORCEINLINE void QueueDeallocateAll()
			{
				for (InterfaceContainerType* O : AllocatedObjects)
				{
					O->GetCache()->QueueDeallocate();
				}
			}

		protected:

			/**
			*
			*
			* @param Payload
			* return
			*/
			InterfaceContainerType* Allocate(PayloadType* Payload)
			{
				CS_SCOPED_TIMER(AllocateScopedTimerHandle);

				const FString& Context = FunctionNames[(uint8)EFunctionNames::Allocate];

				if (IsExhausted())
				{
					checkf(0, TEXT("%s: Pool is exhausted. Pool Size is %d."), *Context, PoolSize);
					return nullptr;
				}

				for (int32 I = 0; I < PoolSize; ++I)
				{
					//PoolIndex				  = (PoolIndex + 1) % PoolSize;
					((*this).*AdvancePoolIndex)();

					InterfaceContainerType* O = Pool[PoolIndex];

					CacheType* Cache = O->GetCache();

					checkf(Cache, TEXT("%s: Cache is NULL."), *Context);

					if (!Cache->IsAllocated())
					{
						// Get Pooled Object Payload
						PooledPayloadType* P = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType, PayloadType>(Context, Payload);

						CS_SCOPED_TIMER(AllocateObjectScopedTimerHandle);

						O->Allocate(P);
						return O;
					}
				}
				checkf(0, TEXT("%s: Pool is exhausted. Pool Size is %d."), *Context, PoolSize);
				return nullptr;
			}

			/**
			* Deallocate an object at specified Index.
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* @param Index	Index of the object.
			* return		Whether the object at Index was successfully deallocated or not.	
			*/
			bool Deallocate(const int32& Index)
			{
				CS_SCOPED_TIMER(DeallocateScopedTimerHandle);

				const FString& Context = FunctionNames[(uint8)EFunctionNames::Deallocate];

				// Check if Index is valid
				if (Index <= INDEX_NONE)
				{
					CS_NON_SHIPPING_EXPR(Log_Impl.ExecuteIfBound(FString::Printf(TEXT("%s::DeAllocate: %s with PoolIndex: %d is NOT in the Pool. Call AddToPool."), *Name, *(ConstructParams.Class->GetName()), Index)));
					return false;
				}
				// Check if Index is valid
				if (Index >= PoolSize)
				{
					CS_NON_SHIPPING_EXPR(Log_Impl.ExecuteIfBound(FString::Printf(TEXT("%s::DeAllocate: %s with PoolIndex: %d is NOT in the Pool. Call AddToPool."), *Name, *(ConstructParams.Class->GetName()), Index)));
					return false;
				}
				// Check if object is already deallocated
				if (Links[Index] != AllocatedHead &&
					!Links[Index]->IsLinked())
				{
					CS_NON_SHIPPING_EXPR(Log_Impl.ExecuteIfBound(FString::Printf(TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *(ConstructParams.Class->GetName()), Index)));
					return false;
				}
				// Check if object is already deallocated
				if (AllocatedObjectsSize == CS_EMPTY)
				{
					CS_NON_SHIPPING_EXPR(Log_Impl.ExecuteIfBound(FString::Printf(TEXT("%s::DeAllocate: %s at PoolIndex: %d is already deallocated or not in the Pool."), *Name, *(ConstructParams.Class->GetName()), Index)));
					return false;
				}

				TCsDoubleLinkedList<InterfaceContainerType*>* Link = Links[Index];
				InterfaceContainerType* O						   = **Link;

				CS_NON_SHIPPING_EXPR(LogTransaction_Impl.Execute(Context, ECsPoolTransaction::Deallocate, O));

				// Deallocate Object
				{
					CS_SCOPED_TIMER(DeallocateObjectScopedTimerHandle);
					O->Deallocate();
				}
				RemoveAllocatedLink(Link);
				AllocationOrder.Promote(Index);

				// Update AllocatedObjects
				TCsDoubleLinkedList<InterfaceContainerType*>* Current = AllocatedHead;
				TCsDoubleLinkedList<InterfaceContainerType*>* Next    = Current;

				int32 NewSize = 0;

				while (Next)
				{
					Current = Next;
					O		= **Current;
					Next	= Current->GetNextLink();

					if (NewSize < AllocatedObjectsSize)
					{
						AllocatedObjects[NewSize] = O;
					}

					++NewSize;
				}

				for (int32 I = AllocatedObjectsSize - 1; I >= NewSize; --I)
				{
					AllocatedObjects.RemoveAt(I, 1, false);
				}
				AllocatedObjectsSize = AllocatedObjects.Num();

				OnDeallocate_Event.Broadcast(O);
				return true;
			}

		public:

			/** Delegate type when deallocating a pooled object.
			*
			* @param Object
			*/
			TMulticastDelegate<void(const InterfaceContainerType* /*Object*/)> OnDeallocate_Event;

		protected:

			/**
			* Deallocate an Object.
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* @param Object		Object to deallocate.
			* return			Whether the Object was successfully deallocated or not.	
			*/
			FORCEINLINE bool Deallocate(InterfaceContainerType* Object)
			{
				return Deallocate(Object->GetCache()->GetIndex());
			}

			/**
			* Deallocate the FIRST object in the allocated list.
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* return	Whether the Object was successfully deallocated or not.
			*/
			const InterfaceContainerType* DeallocateHead()
			{
				if (!AllocatedHead)
					return nullptr;
				if (Deallocate(**AllocatedHead))
					return **AllocatedHead;
				return nullptr;
			}

			/**
			*
			*/
			void DeallocateAll()
			{
				const FString& Context = FunctionNames[(uint8)EFunctionNames::DeallocateAll];

				for (InterfaceContainerType* O : AllocatedObjects)
				{
					CS_NON_SHIPPING_EXPR(LogTransaction_Impl.Execute(Context, ECsPoolTransaction::Deallocate, O));
					O->Deallocate();
					OnDeallocate_Event.Broadcast(O);
				}

				AllocatedObjects.Reset(PoolSize);

				TCsDoubleLinkedList<InterfaceContainerType>* Current = AllocatedHead;
				TCsDoubleLinkedList<InterfaceContainerType>* Next	 = Current;

				while (Next)
				{
					Current = Next;
					Next	= Current->GetNextLink();

					Current->Unlink();
				}

				AllocatedHead = nullptr;
				AllocatedTail = nullptr;

				AllocationOrder.Reset();
			}

		#pragma endregion Allocate / Deallocate

		// Payload
		#pragma region
		protected:

			/** */
			TArray<PayloadType*> Payloads;
			/** */
			TArray<PooledPayloadType*> PooledObjectPayloads;
			/** */
			int32 PayloadSize;
			/** */
			int32 PayloadIndex;

		public:

			/**
			*
			*
			* @param Size
			*/
			void ConstructPayloads(const int32& Size)
			{
				const FString& Context = FunctionNames[(uint8)EFunctionNames::ConstructPayloads];

				checkf(Size > 0, TEXT("%s: Size must be GREATER THAN 0."), *Context);

				checkf(ConstructPayload_Impl.IsBound(), TEXT("%s: ConstructPayload_Impl is NOT bound."), *Context);

				PayloadSize = Size;

				Payloads.Reset(PayloadSize);
				PooledObjectPayloads.Reset(PayloadSize);

				for (int32 I = 0; I < Size; ++I)
				{
					Payloads.Add(ConstructPayload_Impl.Execute());

					checkf(Payloads[I], TEXT("%s: Failed to construct payload of type: PayloadType."), *Context);

					// Get Pooled Object Payload
					PooledPayloadType* P = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType, PayloadType>(Context, Payloads[I]);

					PooledObjectPayloads.Add(P);
				}
			}

			/**
			*
			* @param Size
			*/
			TDelegate<PayloadType*()> ConstructPayload_Impl;

			/**
			*
			*/
			void DeconstructPayloads()
			{
				for (int32 I = 0; I < PayloadSize; ++I)
				{
					PayloadType* P = Payloads[I];
					delete P;
					Payloads[I] = nullptr;
				}
				Payloads.Reset(PayloadSize);
				PooledObjectPayloads.Reset(PayloadSize);
				PayloadSize = 0;
			}

			/**
			* Get a payload object from a pool of payload objects.
			*  Payload implements the interface: NCsPooledObject::NPayload::IPayload and PayloadType.
			*
			* return	Payload that implements the interface: NCsPooledObject::NPayload::IPayload
						and PayloadType.
			*/
			PayloadType* AllocatePayload()
			{
				for (int32 I = 0; I < PayloadSize; ++I)
				{
					PayloadIndex			= (PayloadIndex + 1) % PayloadSize;
					PayloadType* Payload	= Payloads[PayloadIndex];
					PooledPayloadType* P	= PooledObjectPayloads[PayloadIndex];

					if (!P->IsAllocated())
					{
						P->Allocate();
						return Payload;
					}
				}
				checkf(0, TEXT("%s::AllocatePayload: Pool is exhausted. Pool Size = %d."), *Name, PayloadSize);
				return nullptr;
			}

			/**
			* Get a payload object from a pool of payload objects.
			*  Payload implements the interface: NCsPooledObject::NPayload::IPayload and PayloadType.
			*
			* @param Context	Calling context
			* return			PayloadTypeImpl that implements the interface: NCsPooledObject::NPayload::IPayload
								and PayloadType.
			*/
			template<typename PayloadImplType>
			FORCEINLINE PayloadImplType* AllocatePayload(const FString& Context)
			{
				return NCsInterfaceMap::StaticCastChecked<PayloadImplType, PayloadType>(Context, AllocatePayload());
			}

			/**
			* Get a payload object from a pool of payload objects.
			*  Payload implements the interface: NCsPooledObject::NPayload::IPayload and PayloadType.
			*
			* return	PayloadTypeImpl that implements the interface: NCsPooledObject::NPayload::IPayload
						and PayloadType.
			*/
			template<typename PayloadImplType>
			FORCEINLINE PayloadImplType* AllocatePayload()
			{
				const FString& Context = FunctionNames[(uint8)EFunctionNames::AllocatePayload];

				return AllocatePayload<PayloadImplType>(Context);
			}

			FORCEINLINE void DeallocatePayload(const FString& Context, PayloadType* Payload) 
			{ 
				PooledPayloadType* P = NCsInterfaceMap::GetInterfaceChecked<PooledPayloadType, PayloadType>(Context, Payload);

				P->Reset();
			}

			FORCEINLINE void DeallocatePayload(PayloadType* Payload)
			{
				const FString& Context = FunctionNames[(uint8)EFunctionNames::DeallocatePayload];

				DeallocatePayload(Context, Payload);
			}

			/**
			*
			*
			* return
			*/
			FORCEINLINE const int32& GetPayloadSize()
			{
				return PayloadSize;
			}

		#pragma endregion Payload

		// Log
		#pragma region
		public:

			TDelegate<void(const FString& /*Str*/)> Log_Impl;

			TDelegate<void(const FString& /*Context*/, const ECsPoolTransaction& /*Transaction*/, const InterfaceContainerType* /*Object*/)> LogTransaction_Impl;

		protected:

			FECsCVarLog LogType;

		#pragma endregion Log

		// Spawn
		#pragma region
		public:

			/**
			*
			*
			* @param Payload
			* return
			*/
			const InterfaceContainerType* Spawn(PayloadType* Payload)
			{
				CS_SCOPED_TIMER(SpawnScopedTimerHandle);

				const FString& Context = FunctionNames[(uint8)EFunctionNames::Spawn];

				checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

				InterfaceContainerType* O = Allocate(Payload);

				checkf(O->GetCache()->IsAllocated(), TEXT("%s: Object was NOT allocated properly (GetCache()->IsAllocated() == false)."), *Context);

		#if !UE_BUILD_SHIPPING
				LogTransaction_Impl.Execute(Context, ECsPoolTransaction::Allocate, O);
		#endif // #if !UE_BUILD_SHIPPING

				DeallocatePayload(Context, Payload);
				AddToAllocatedObjects_Internal(O);
				OnSpawn_Event.Broadcast(O);
				return O;
			}

			template<typename OtherContainerType, typename OtherPayloadType>
			const OtherContainerType* Spawn(OtherPayloadType* Payload)
			{
				static_assert(std::is_base_of<InterfaceContainerType, OtherContainerType>(), "NCsPooledObject::NManager::TAbstract: InterfaceContainerType:");

				static_assert(std::is_abstract<OtherPayloadType>(), "NCsPooledObject::NManager::TAbstract: InterfaceContainerType:");

				CS_SCOPED_TIMER(SpawnScopedTimerHandle);

				const FString& Context = FunctionNames[(uint8)EFunctionNames::Spawn];

				checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

				// Get PayloadType
				PayloadType* P = NCsInterfaceMap::GetInterfaceChecked<PayloadType, OtherPayloadType>(Context, Payload);

				InterfaceContainerType* O = Allocate(P);

		#if !UE_BUILD_SHIPPING
				LogTransaction_Impl.Execute(Context, ECsPoolTransaction::Spawn, O);
		#endif // #if !UE_BUILD_SHIPPING

				DeallocatePayload(Context, P);
				AddToAllocatedObjects_Internal(O);
				OnSpawn_Event.Broadcast(O);
				return static_cast<OtherContainerType*>(O);
			}

			/**
			*
			* @param Object
			*/
			TMulticastDelegate<void(const InterfaceContainerType* /*Object*/)> OnSpawn_Event;

		#pragma endregion Spawn

		// Destroy
		#pragma region
		public:

			/**
			*
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* @param Index
			* return		Whether the Object was successfully "destroyed" / deallocated
			*/
			FORCEINLINE bool Destroy(const int32& Index)
			{
				CS_SCOPED_TIMER(DestroyScopedTimerHandle);

				return Deallocate(Index);
			}

			/**
			*
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* @param Object
			* return			Whether the Object was successfully "destroyed" / deallocated
			*/
			FORCEINLINE bool Destroy(const InterfaceContainerType* Object)
			{
				checkf(Object, TEXT("%s::Destroy: Object is NULL."), *Name);

				return Destroy(Object->GetCache()->GetIndex());
			}

			/**
			*
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* @param Object
			* return			Whether the Object was successfully "destroyed" / deallocated
			*/
			FORCEINLINE bool Destroy(InterfaceType* Object)
			{
				checkf(Object, TEXT("%s::Destroy: Object is NULL."), *Name);

				return Destroy(Object->_getUObject());
			}

			/**
			*
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* @param Object
			* return			Whether the Object was successfully "destroyed" / deallocated
			*/
			FORCEINLINE bool Destroy(UObject* Object)
			{
				const InterfaceContainerType* O = FindObject(Object);
				return Destroy(O);
			}

			/**
			*
			*  NOTE: This process is O(n). Consider queuing the deallocate.
			*
			* return	If successful return the FIRST object in the allocated list was successfully "destroyed" / deallocated
			*/
			FORCEINLINE const InterfaceContainerType* DestroyHead()
			{
				return DeallocateHead();
			}

		#pragma endregion Destroy

		// Script
		#pragma region
		public:

			// ICsPooledObject

			FCsPooledObject::FScript_GetCache Script_GetCache_Impl;

			FCsPooledObject::FScript_Allocate Script_Allocate_Impl;

			FCsPooledObject::FScript_Deallocate Script_Deallocate_Impl;

			// ICsUpdate

			FCsPooledObject::FScript_Update Script_Update_Impl;

			// ICsOnConstructObject

			FCsPooledObject::FScript_OnConstructObject Script_OnConstructObject_Impl;

		#pragma endregion Script

		// Scoped Timer
		#pragma region
		protected:

			FECsScopedGroup ScopedGroup;

			/** */
			FString ScopedTimerNames[(uint8)EScopedTimerNames::EScopedTimerNames_MAX];

			FCsScopedTimerHandle CreatePoolScopedTimerHandle;
			FECsCVarLog CreatePoolScopedTimerCVar;

			FCsScopedTimerHandle UpdateScopedTimerHandle;
			FECsCVarLog UpdateScopedTimerCVar;

			FCsScopedTimerHandle UpdateObjectScopedTimerHandle;
			FECsCVarLog UpdateObjectScopedTimerCVar;

			FCsScopedTimerHandle AllocateScopedTimerHandle;
			FECsCVarLog AllocateScopedTimerCVar;

			FCsScopedTimerHandle AllocateObjectScopedTimerHandle;
			FECsCVarLog AllocateObjectScopedTimerCVar;

			FCsScopedTimerHandle DeallocateScopedTimerHandle;
			FECsCVarLog DeallocateScopedTimerCVar;

			FCsScopedTimerHandle DeallocateObjectScopedTimerHandle;
			FECsCVarLog DeallocateObjectScopedTimerCVar;

			FCsScopedTimerHandle SpawnScopedTimerHandle;
			FECsCVarLog SpawnScopedTimerCVar;

			FCsScopedTimerHandle DestroyScopedTimerHandle;
			FECsCVarLog DestroyScopedTimerCVar;

		#pragma endregion Scoped Timer
		};
	}
}