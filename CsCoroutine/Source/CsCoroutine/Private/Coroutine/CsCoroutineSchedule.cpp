// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsCoroutineSchedule.h"
#include "CsCoroutine.h"

// CVars
#include "Coroutine/CsCVars_Coroutine.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Coroutine/CsSettings_CoroutineScheduler.h"

namespace NCsCoroutine
{
	namespace NSchedule
	{
		namespace NDefault
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FDefault, Start);
					// Routine
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FDefault, GetRoutineContainer);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsCoroutine::NSchedule::NDefault::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsCoroutine::NSchedule::NDefault::NCached; \
			const FString& Context = Str::__FunctionName
		#define RoutineManagerType NCsRoutine::FManager
		#define RoutineResourceType NCsRoutine::FResource
		#define PayloadManagerType NCsCoroutine::NPayload::FManager
		#define PayloadResourceType NCsCoroutine::NPayload::FResource
		#define PayloadType NCsCoroutine::NPayload::FImpl
		#define StateType NCsCoroutine::EState
		#define EndReasonType NCsCoroutine::EEndReason
		#define TransactionType NCsCoroutine::ETransaction
		#define MessageType NCsCoroutine::EMessage

		FDefault::FDefault()
		{
			// Set Index for fast look up

			// Routine
			{
				const TArray<RoutineResourceType*>& Pool = Manager_Routine.GetPool();

				for (RoutineResourceType* Container : Pool)
				{
					FCsRoutine* R	   = Container->Get();
					const int32& Index = Container->GetIndex();
					R->SetIndex(Index);
				}
			}
			// Payload
			{
				const TArray<PayloadResourceType*>& Pool = Manager_Payload.GetPool();

				for (PayloadResourceType* Container : Pool)
				{
					PayloadType* P		= Container->Get();
					const int32& Index	= Container->GetIndex();
					P->SetIndex(Index);
				}
			}
		}

		FDefault::~FDefault()
		{
		}

		// Schedule
		#pragma region

		void FDefault::SetGroup(const FECsUpdateGroup& InGroup)
		{
			Group = InGroup;

			// Update TimeGroup

			// Routine
			{
				const TArray<RoutineResourceType*>& Pool = Manager_Routine.GetPool();

				for (RoutineResourceType* Container : Pool)
				{
					FCsRoutine* R = Container->Get();
					R->SetGroup(Group);
				}
			}
			// Payload
			{
				const TArray<PayloadResourceType*>& Pool = Manager_Payload.GetPool();

				for (PayloadResourceType* Container : Pool)
				{
					PayloadType* P = Container->Get();
					P->Group	   = Group;
				}
			}
		}

		#pragma endregion Schedule

		// Routine
		#pragma region

		RoutineResourceType* FDefault::GetRoutineContainer(const FCsRoutineHandle& Handle) const
		{
			SET_CONTEXT(GetRoutineContainer);

			if (!Handle.IsValid())
				return nullptr;

			const int32& PoolSize = Manager_Routine.GetPoolSize();

			if (Handle.GetIndex() >= PoolSize)
			{
				UE_LOG(LogCsCoroutine, Warning, TEXT("%s: Handle's Index: %d is not associated with any Routine with Group: %s."), *Context, Handle.GetIndex(), Group.ToChar())
				return nullptr;
			}

			RoutineResourceType* Container = Manager_Routine.GetAt(Handle.GetIndex());
			FCsRoutine* R				   = Container->Get();

			if (R->GetHandle() == Handle)
				return Container;
			return nullptr;
		}

		FCsRoutine* FDefault::GetRoutine(const FCsRoutineHandle& Handle) const
		{
			RoutineResourceType* Container = GetRoutineContainer(Handle);

			return Container ? Container->Get() : nullptr;
		}

		#pragma endregion Routine

		// Handle
		#pragma region

		bool FDefault::IsRunning(const FCsRoutineHandle& Handle) const
		{
			if (FCsRoutine* R = GetRoutine(Handle))
				return R->IsRunning();
			return false;
		}

		#pragma endregion Handle

		// Start
		#pragma region

		const FCsRoutineHandle& FDefault::Start(PayloadResourceType* PayloadContainer)
		 {
			SET_CONTEXT(Start);

			PayloadType* Payload = PayloadContainer->Get();

			checkf(Payload, TEXT("%s: PayloadContainer does NOT contain a reference to a Payload."), *Context);
			check(Payload->IsValidChecked(Context));
			checkf(Group == Payload->Group, TEXT("%s: Mismatch between Payload->Group: %s and Group: %s"), *Context, Payload->Group.ToChar(), Group.ToChar());

			FCsRoutine* R = Manager_Routine.AllocateResource();

			R->Init(Payload);

			CS_COROUTINE_INIT(R);

			if (Payload->bPerformFirstUpdate)
			{
				R->StartUpdate();
				R->Update(FCsDeltaTime::Zero);
			}

			//LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

			Payload->Reset();
			Manager_Payload.Deallocate(PayloadContainer);
			return R->HasEnded() ? FCsRoutineHandle::Invalid : R->GetHandle();
		}

		const FCsRoutineHandle& FDefault::Start(PayloadType* Payload)
		{
			return Start(GetPayloadContainer(Payload));
		}

		const FCsRoutineHandle& FDefault::StartChild(PayloadResourceType* PayloadContainer)
		{
			PayloadType* Payload = PayloadContainer->Get();

			checkf(Payload, TEXT("FCsCoroutineSchedule::StartChild: PayloadContainer does NOT contain a reference to a Payload."));
			checkf(Group == Payload->Group, TEXT("FCsCoroutineSchedule::StartChild: Mismatch between Payload->Group: %s and Group: %s"), Payload->Group.ToChar(), Group.ToChar());

			RoutineResourceType* ParentContainer = GetRoutineContainer(Payload->ParentHandle);

			checkf(ParentContainer, TEXT("FCsCoroutineSchedule::StartChild: Failed to find a container for Payload."));

			FCsRoutine* Parent    = ParentContainer->Get();
			FCsRoutine* LastChild = Parent->GetLastChild();

			RoutineResourceType* RoutineContainer = nullptr;

			// Add after Last Child
			if (LastChild)
			{
				RoutineResourceType* LastChildContainer = Manager_Routine.GetAt(LastChild->GetIndex());

				RoutineContainer = Manager_Routine.AllocateAfter(LastChildContainer);
			}
			// Add after Parent
			else
			{
				RoutineContainer = Manager_Routine.AllocateAfter(ParentContainer);
			}

			FCsRoutine* R = RoutineContainer->Get();

			Parent->AddChild(R);

			R->Init(Payload);

			CS_COROUTINE_INIT(R);

			R->StartUpdate();
			R->Update(FCsDeltaTime::Zero);

			Payload->Reset();
			//UE_LOG(LogCsCoroutine, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
			return R->HasEnded() ? FCsRoutineHandle::Invalid : R->GetHandle();
		}

		const FCsRoutineHandle& FDefault::StartChild(PayloadType* Payload)
		{
			return StartChild(GetPayloadContainer(Payload));
		}

		#pragma endregion Start

		// End
		#pragma region

		bool FDefault::End()
		{
			bool Result = false;

			TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
			TCsDoubleLinkedList<RoutineResourceType*>* Next	   = Current;

			while (Next)
			{
				Current								  = Next;
				RoutineResourceType* RoutineContainer = **Current;
				Next								  = Current->GetNextLink();

				FCsRoutine* R = RoutineContainer->Get();

				if (!R->HasEnded())
				{
					R->End(EndReasonType::Shutdown);
				}
				//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

				R->Reset();
				Manager_Routine.Deallocate(RoutineContainer);

				Result = true;
			}
			return Result;
		}

		bool FDefault::End(const FCsRoutineHandle& Handle)
		{
			if (RoutineResourceType* Container = GetRoutineContainer(Handle))
			{
				FCsRoutine* R = Container->Get();

				// If the Routine has already Ended, exit
				if (R->HasEnded() ||
					R->HasJustEnded())
				{
					return false;
				}

				// If the Routine is currently being Updated, queue the End for either the
				// beginning of the next Update or the end of the current Update.
				if (!R->IsUpdateComplete())
				{
					QueueEndHandles.Add(Handle);
					return false;
				}

				R->End(EndReasonType::Manual);

				//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

				R->Reset();
				Manager_Routine.Deallocate(Container);
				return true;
			}
			return false;
		}

		bool FDefault::HasEnded(const FCsRoutineHandle& Handle) const
		{
			if (FCsRoutine* R = GetRoutine(Handle))
				return R->HasEnded();
			return true;
		}

		bool FDefault::HasJustEnded(const FCsRoutineHandle& Handle) const
		{
			if (FCsRoutine* R = GetRoutine(Handle))
				return R->HasJustEnded();
			return true;
		}

		#pragma endregion End

		// Update
		#pragma region

		void FDefault::Update(const FCsDeltaTime& DeltaTime)
		{
			// End any pending Handles requested for End from the previous Update
			for (const FCsRoutineHandle& Handle : QueueEndHandles)
			{
				End(Handle);
			}

			QueueEndHandles.Reset(QueueEndHandles.Max());

			TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
			TCsDoubleLinkedList<RoutineResourceType*>* Next    = Current;

			while (Next)
			{
				Current								  = Next;
				RoutineResourceType* RoutineContainer = **Current;
				Next								  = Current->GetNextLink();

				FCsRoutine* R = RoutineContainer->Get();

				const StateType& State = R->State;

				// Init -> Update
				if (State == StateType::Init)
				{
					R->StartUpdate();
					R->Update(DeltaTime);
				}
				// Update
				else
				if (State == StateType::Update)
				{
					R->Update(DeltaTime);
				}

				// End
				if (State == StateType::End)
				{
					//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

					R->Reset();
					Manager_Routine.Deallocate(RoutineContainer);
				}
			}

			// End any Handles requested for End on the current Update
			for (const FCsRoutineHandle& Handle : QueueEndHandles)
			{
				End(Handle);
			}

			QueueEndHandles.Reset(QueueEndHandles.Max());
		}

		#pragma endregion Update

		// Payload
		#pragma region

		PayloadResourceType* FDefault::GetPayloadContainer(PayloadType* Payload)
		{
			if (Payload->GetIndex() == INDEX_NONE)
			{
				PayloadResourceType* Container = Manager_Payload.Allocate();
				PayloadType* P				   = Container->Get();

				*P = *Payload;

				return Container;
			}
			return Manager_Payload.GetAt(Payload->GetIndex());
		}

		#pragma endregion Payload

		// Message
		#pragma region

		void FDefault::BroadcastMessage(const MessageType& Type, const FName& Message, void* Owner /*=nullptr*/)
		{
			TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
			TCsDoubleLinkedList<RoutineResourceType*>* Next    = Current;

			while (Next)
			{
				Current								  = Next;
				RoutineResourceType* RoutineContainer = **Current;
				Next								  = Current->GetNextLink();

				FCsRoutine* R = RoutineContainer->Get();

				if (Owner)
				{
					if (R->Owner.GetOwner() == Owner)
						R->ReceiveMessage(Type, Message);
				}
				else
				{
					R->ReceiveMessage(Type, Message);
				}
			}
		}

		#pragma endregion Message

		// Log
		#pragma region

		void FDefault::LogTransaction(const FString& FunctionName, const TransactionType& Transaction, FCsRoutine* R)
		{
			/*
			if (CsCVarLogCoroutineTransactions->GetInt() == CS_CVAR_SHOW_LOG)
			{
				FString TransactionAsString = NCsCoroutine::NTransaction::ToActionString(Transaction);
			
				if (Transaction == TransactionType::End)
					TransactionAsString = NCsCoroutine::NTransaction::ToActionString(Transaction) + TEXT("(Reason=") + EMCsCoroutineEndReason::Get().ToString(R->endReason) + TEXT(")");

				const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(R->scheduleType);

				AActor* Actor			= R->GetActor();
				const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
				UObject* Object			= R->GetRObject();
				const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
				UObject* Owner			= R->GetOwner();
				const FString OwnerName	= Owner ? Owner->GetName() : NCsCached::Str::Empty;

				UWorld* World = nullptr;

				if (Actor)
					World = Actor->GetWorld();
				if (Object)
					World = Object->GetWorld();

				const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

				const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->nameAsString;

				FString Elapsed = NCsCached::Str::None;

				if (Transaction == TransactionType::End)
				{
					const float Duration = CurrentTime - R->startTime;
					Elapsed = TEXT("Ran for ") + FString::FromInt(R->tickCount) + TEXT(" Ticks and  ") + UCsLibrary_Common::GetFloatAsStringWithPrecision(Duration, 2) + TEXT(" Seconds.");
				}

				if (Actor && Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Owner: %s using Actor: %s and Object: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *ObjectName, *Elapsed);
				}
				else
				if (Actor)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *Elapsed);
				}
				else
				if (Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ObjectName, *Elapsed);
				}
				else
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *Elapsed);
				}
			}
			*/
		}

		void FDefault::LogRunning()
		{
			/*
			if (CsCVarLogCoroutineRunning->GetInt() != CS_CVAR_SHOW_LOG)
				return;

			const uint8 Schedule = (uint8)ScheduleType;
			const int32 Count    = RoutinesToRun[Schedule].Num();

			if (Count == CS_EMPTY)
				return;

			UWorld* World = nullptr;

			if (UObject* Object = GetMyOwner())
				World = Object->GetWorld();

			float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

			const FString& FunctionName		    = NCsCoroutineCached::Str::Update;
			const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(ScheduleType);

			UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s. Running %d Coroutines at %f."), *FunctionName, *ScheduleTypeAsString, Count, CurrentTime);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				FCsRoutine* R = RoutinesToRun[Schedule][Index];

				AActor* Actor			= R->GetActor();
				const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
				UObject* Object			= R->GetRObject();
				const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
				UObject* Owner			= R->GetOwner();
				const FString OwnerName = Owner ? Owner->GetName() : NCsCached::Str::Empty;

				const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->name.ToString();

				const float Duration = CurrentTime - R->startTime;

				if (Actor && Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Owner: %s using Actor: %s and Object: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, *ObjectName, R->tickCount, Duration);
				}
				else
				if (Actor)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, R->tickCount, Duration);
				}
				else
				if (Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ObjectName, R->tickCount, Duration);
				}
				else
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, R->tickCount, Duration);
				}
			}
			*/
		}

		#pragma endregion Log

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef RoutineManagerType
		#undef RoutineResourceType
		#undef PayloadManagerType
		#undef PayloadResourceType
		#undef PayloadType
		#undef StateType
		#undef EndReasonType
		#undef TransactionType
		#undef MessageType
	}
}

namespace NCsCoroutine
{
	namespace NSchedule
	{
		namespace NCustom
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FCustom, Ctor);
					// Owner
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FCustom, GetOwnerID);
					// Routine
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FCustom, GetRoutineContainer);
					// Start
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FCustom, Start);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FCustom, StartChild);
					// Update
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsCoroutine::NSchedule::FCustom, Update);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsCoroutine::NSchedule::NCustom::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsCoroutine::NSchedule::NCustom::NCached; \
			const FString& Context = Str::__FunctionName
		#define RoutineManagerType NCsRoutine::FManager
		#define RoutineResourceType NCsRoutine::FResource
		#define PayloadManagerType NCsCoroutine::NPayload::FManager
		#define PayloadResourceType NCsCoroutine::NPayload::FResource
		#define PayloadType NCsCoroutine::NPayload::FImpl
		#define StateType NCsCoroutine::EState
		#define EndReasonType NCsCoroutine::EEndReason
		#define TransactionType NCsCoroutine::ETransaction
		#define MessageType NCsCoroutine::EMessage

		FCustom::FCustom()
		{
			SET_CONTEXT(Ctor);
			
			// Set Index for fast look up

			// Routine
			{
				const TArray<RoutineResourceType*>& Pool = Manager_Routine.GetPool();

				for (RoutineResourceType* Container : Pool)
				{
					FCsRoutine* R	   = Container->Get();
					const int32& Index = Container->GetIndex();
					R->SetIndex(Index);
				}
			}
			// Payload
			{
				const TArray<PayloadResourceType*>& Pool = Manager_Payload.GetPool();

				for (PayloadResourceType* Container : Pool)
				{
					PayloadType* P		= Container->Get();
					const int32& Index	= Container->GetIndex();
					P->SetIndex(Index);
				}
			}

			// Setup Owner tracking
			const FCsSettings_CoroutineScheduler_Custom& Settings = FCsSettings_CoroutineScheduler_Custom::Get();

			CS_IS_VALID_CHECKED(Settings);

			const int32& MaxOwners			 = Settings.MaxOwners;
			const int32& MaxRoutinesPerOwner = Settings.MaxRoutinesPerOwner;
			const int32 RoutineCount		 = MaxOwners * MaxRoutinesPerOwner;
			const int32 PoolSize			 = Manager_Routine.GetPoolSize();

			checkf(RoutineCount <= PoolSize, TEXT("%s: MaxOwners * MaxRoutinesPerOwner > Routine Pool Size: %d (%d * %d) > %d."), *Context, MaxOwners, MaxRoutinesPerOwner, RoutineCount, PoolSize);

			Manager_OwnerID.CreatePool(Settings.MaxOwners);

			OwnerRoutineIDs.Reset(PoolSize);

			for (int32 I = 0; I < PoolSize; ++I)
			{
				OwnerRoutineIDs.Add(INDEX_NONE);
			}

			RoutineStrideByOwnerID.Reset(MaxOwners);

			for (int32 I = 0; I < MaxOwners; ++I)
			{
				RoutineStrideByOwnerID.Add(0);
			}
		}

		FCustom::~FCustom()
		{
		}

		// Owner
		#pragma region

		int32 FCustom::AllocateOwnerID()
		{
			return Manager_OwnerID.AllocateResourceRef();
		}

		void FCustom::DeallocateOwnerID(const int32& OwnerID)
		{
			End(OwnerID);
			Manager_OwnerID.DeallocateAt(OwnerID);
		}

		int32 FCustom::GetOwnerID(const int32& RoutineIndex)
		{
			SET_CONTEXT(GetOwnerID);

			checkf(RoutineIndex >= 0 && RoutineIndex < Manager_Routine.GetPoolSize(), TEXT("%s: RoutineIndex: %d is NOT in the Range: [0, %d]."), *Context, RoutineIndex, Manager_Routine.GetPoolSize());

			const int32& MaxRoutinesPerOwner = FCsSettings_CoroutineScheduler_Custom::Get().MaxRoutinesPerOwner;

			typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceContainerType;

			TCsDoubleLinkedList<ResourceContainerType*>* Current = Manager_OwnerID.GetAllocatedHead();
			TCsDoubleLinkedList<ResourceContainerType*>* Next	 = Current;

			while (Next)
			{
				Current								    = Next;
				ResourceContainerType* RoutineContainer = **Current;
				Next								    = Current->GetNextLink();

				int32* OwnerIdPtr = RoutineContainer->Get();
				const int32& ID	  = *OwnerIdPtr;

				const int32 Start  = ID * MaxRoutinesPerOwner;
				const int32 Stride = RoutineStrideByOwnerID[ID];
					
				for (int32 I = 0; I < Stride; ++I)
				{
					if (OwnerRoutineIDs[I] == RoutineIndex)
					{
						return ID;
					}
				}
			}
			checkf(0, TEXT("%s: Failed to find OwnerID associated with RoutineIndex: %d."), *Context, RoutineIndex);
			return INDEX_NONE;
		}

		int32 FCustom::GetOwnerID(const FCsRoutineHandle& Handle)
		{
			if (RoutineResourceType* Container = GetRoutineContainer(Handle))
				return GetOwnerID(Container->Get());
			return INDEX_NONE;
		}

		#pragma endregion Owner

		// Schedule
		#pragma region

		void FCustom::SetGroup(const FECsUpdateGroup& InGroup)
		{
			Group = InGroup;

			// Update TimeGroup

			// Routine
			{
				const TArray<RoutineResourceType*>& Pool = Manager_Routine.GetPool();

				for (RoutineResourceType* Container : Pool)
				{
					FCsRoutine* R = Container->Get();
					R->SetGroup(Group);
				}
			}
			// Payload
			{
				const TArray<PayloadResourceType*>& Pool = Manager_Payload.GetPool();

				for (PayloadResourceType* Container : Pool)
				{
					PayloadType* P = Container->Get();
					P->Group	   = Group;
				}
			}
		}

		#pragma endregion Schedule

		// Routine
		#pragma region

		RoutineResourceType* FCustom::GetRoutineContainer(const FCsRoutineHandle& Handle) const
		{
			SET_CONTEXT(GetRoutineContainer);

			if (!Handle.IsValid())
				return nullptr;

			const int32& PoolSize = Manager_Routine.GetPoolSize();

			if (Handle.GetIndex() >= PoolSize)
			{
				UE_LOG(LogCsCoroutine, Warning, TEXT("%s: Handle's Index: %d is not associated with any Routine with Group: %s."), *Context, Handle.GetIndex(), Group.ToChar())
				return nullptr;
			}

			RoutineResourceType* Container = Manager_Routine.GetAt(Handle.GetIndex());
			FCsRoutine* R				   = Container->Get();

			if (R->GetHandle() == Handle)
				return Container;
			return nullptr;
		}

		FCsRoutine* FCustom::GetRoutine(const FCsRoutineHandle& Handle) const
		{
			RoutineResourceType* Container = GetRoutineContainer(Handle);

			return Container ? Container->Get() : nullptr;
		}

		#pragma endregion Routine

		// Handle
		#pragma region

		bool FCustom::IsRunning(const FCsRoutineHandle& Handle) const
		{
			if (FCsRoutine* R = GetRoutine(Handle))
				return R->IsRunning();
			return false;
		}

		#pragma endregion Handle

		// Start
		#pragma region

		const FCsRoutineHandle& FCustom::Start(const int32& OwnerID, PayloadResourceType* PayloadContainer)
		{
			SET_CONTEXT(Start);

			check(Manager_OwnerID.IsAllocatedChecked(Context, OwnerID));

			PayloadType* Payload = PayloadContainer->Get();

			checkf(Payload, TEXT("%s: PayloadContainer does NOT contain a reference to a Payload."), *Context);
			check(Payload->IsValidChecked(Context));
			checkf(Group == Payload->Group, TEXT("%s: Mismatch between Payload->Group: %s and Group: %s"), *Context, Payload->Group.ToChar(), Group.ToChar());

			FCsRoutine* R = Manager_Routine.AllocateResource();

			++RoutineStrideByOwnerID[OwnerID];

			const int32& MaxRoutinesPerOwner = FCsSettings_CoroutineScheduler_Custom::Get().MaxRoutinesPerOwner;

			checkf(RoutineStrideByOwnerID[OwnerID] < MaxRoutinesPerOwner, TEXT("%s: Owner ID: %d has ALREADY allocated (%d) Max Routines Per Owner: %d."), *Context, OwnerID, RoutineStrideByOwnerID[OwnerID], MaxRoutinesPerOwner);

			const int32 RoutineIdIndex		= (OwnerID * MaxRoutinesPerOwner) + RoutineStrideByOwnerID[OwnerID];
			OwnerRoutineIDs[RoutineIdIndex] = R->GetIndex();

			R->Init(Payload);

			CS_COROUTINE_INIT(R);

			if (Payload->bPerformFirstUpdate)
			{
				R->StartUpdate();
				R->Update(FCsDeltaTime::Zero);
			}

			//LogTransaction(NCsCoroutineCached::Str::Allocate, (Payload->bDoInit && Payload->bPerformFirstRun) ? TransactionType::Start : TransactionType::Allocate, R);

			Payload->Reset();
			Manager_Payload.Deallocate(PayloadContainer);
			return R->HasEnded() ? FCsRoutineHandle::Invalid : R->GetHandle();
		}

		const FCsRoutineHandle& FCustom::Start(const int32& OwnerID, PayloadType* Payload)
		{
			return Start(OwnerID, GetPayloadContainer(Payload));
		}

		const FCsRoutineHandle& FCustom::StartChild(const int32& OwnerID, PayloadResourceType* PayloadContainer)
		{
			SET_CONTEXT(StartChild);

			PayloadType* Payload = PayloadContainer->Get();

			check(Manager_OwnerID.IsAllocatedChecked(Context, OwnerID));

			checkf(Payload, TEXT("FCsCoroutineSchedule::StartChild: PayloadContainer does NOT contain a reference to a Payload."));
			checkf(Group == Payload->Group, TEXT("FCsCoroutineSchedule::StartChild: Mismatch between Payload->Group: %s and Group: %s"), Payload->Group.ToChar(), Group.ToChar());

			RoutineResourceType* ParentContainer = GetRoutineContainer(Payload->ParentHandle);

			checkf(ParentContainer, TEXT("FCsCoroutineSchedule::StartChild: Failed to find a container for Payload."));

			FCsRoutine* Parent	  = ParentContainer->Get();
			FCsRoutine* LastChild = Parent->GetLastChild();

			RoutineResourceType* RoutineContainer = nullptr;

			// Add after Last Child
			if (LastChild)
			{
				RoutineResourceType* LastChildContainer = Manager_Routine.GetAt(LastChild->GetIndex());

				RoutineContainer = Manager_Routine.AllocateAfter(LastChildContainer);
			}
			// Add after Parent
			else
			{
				RoutineContainer = Manager_Routine.AllocateAfter(ParentContainer);
			}

			FCsRoutine* R = RoutineContainer->Get();

			++RoutineStrideByOwnerID[OwnerID];

			const int32& MaxRoutinesPerOwner = FCsSettings_CoroutineScheduler_Custom::Get().MaxRoutinesPerOwner;

			checkf(RoutineStrideByOwnerID[OwnerID] < MaxRoutinesPerOwner, TEXT("%s: Owner ID: %d has ALREADY allocated (%d) Max Routines Per Owner: %d."), *Context, OwnerID, RoutineStrideByOwnerID[OwnerID], MaxRoutinesPerOwner);

			const int32 RoutineIdIndex		= (OwnerID * MaxRoutinesPerOwner) + RoutineStrideByOwnerID[OwnerID];
			OwnerRoutineIDs[RoutineIdIndex] = R->GetIndex();

			Parent->AddChild(R);

			R->Init(Payload);

			CS_COROUTINE_INIT(R);

			R->StartUpdate();
			R->Update(FCsDeltaTime::Zero);

			Payload->Reset();
			//UE_LOG(LogCsCoroutine, Warning, TEXT("UCsCoroutineScheduler::StartChild: No free Routines. Look for Runaway Coroutines or consider raising the pool size."));
			return R->HasEnded() ? FCsRoutineHandle::Invalid : R->GetHandle();
		}

		const FCsRoutineHandle& FCustom::StartChild(const int32& OwnerID, PayloadType* Payload)
		{
			return StartChild(OwnerID, GetPayloadContainer(Payload));
		}

		#pragma endregion Start

		// End
		#pragma region

		bool FCustom::End()
		{
			bool Result = false;

			TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
			TCsDoubleLinkedList<RoutineResourceType*>* Next	   = Current;

			while (Next)
			{
				Current								  = Next;
				RoutineResourceType* RoutineContainer = **Current;
				Next								  = Current->GetNextLink();

				FCsRoutine* R = RoutineContainer->Get();

				if (!R->HasEnded())
				{
					R->End(EndReasonType::Shutdown);
				}
				//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

				R->Reset();
				Manager_Routine.Deallocate(RoutineContainer);

				Result = true;
			}
			return Result;
		}

		bool FCustom::End(const int32& OwnerID)
		{
			bool Result = false;

			if (!Manager_OwnerID.IsAllocated(OwnerID))
				return false;

			const int32& MaxRoutinesPerOwner = FCsSettings_CoroutineScheduler_Custom::Get().MaxRoutinesPerOwner;
			const int32 Start				 = OwnerID * MaxRoutinesPerOwner;
			const int32 Stride				 = RoutineStrideByOwnerID[OwnerID];
		
			for (int32 I = 0; I < Stride; ++I)
			{
				const int32& RoutineIndex = OwnerRoutineIDs[Start + I];

				RoutineResourceType* RoutineContainer = Manager_Routine.GetAt(RoutineIndex);	
				FCsRoutine* R						  = RoutineContainer->Get();

				if (!R->HasEnded())
				{
					R->End(EndReasonType::Shutdown);
				}
				//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

				R->Reset();
				Manager_Routine.Deallocate(RoutineContainer);

				Result = true;
			}
			return Result;
		}

		bool FCustom::End(const int32& OwnerID, const FCsRoutineHandle& Handle)
		{
			if (RoutineResourceType* Container = GetRoutineContainer(Handle))
			{
				FCsRoutine* R = Container->Get();

				// If the Routine has already Ended, exit
				if (R->HasEnded() ||
					R->HasJustEnded())
				{
					return false;
				}

				const int32& MaxRoutinesPerOwner = FCsSettings_CoroutineScheduler_Custom::Get().MaxRoutinesPerOwner;

				// If the Routine is currently being Updated, queue the End for either the
				// beginning of the next Update or the end of the current Update.
				if (!R->IsUpdateComplete())
				{
					const int32 Stride = QueueEndHandleStrideByOwnerID[OwnerID];
					const int32 Index  = (OwnerID * MaxRoutinesPerOwner) + Stride;
					
					OwnerQueueEndHandles[Index] = Handle;

					++QueueEndHandleStrideByOwnerID[OwnerID];
					return false;
				}

				R->End(EndReasonType::Manual);

				//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

				R->Reset();
				Manager_Routine.Deallocate(Container);

				const int32 Stride = RoutineStrideByOwnerID[OwnerID];
				const int32 Index  = (OwnerID * MaxRoutinesPerOwner) + Stride;

				OwnerRoutineIDs[Index] = INDEX_NONE;

				--RoutineStrideByOwnerID[OwnerID];
				return true;
			}
			return false;
		}

		bool FCustom::HasEnded(const FCsRoutineHandle& Handle) const
		{
			if (FCsRoutine* R = GetRoutine(Handle))
				return R->HasEnded();
			return true;
		}

		bool FCustom::HasJustEnded(const FCsRoutineHandle& Handle) const
		{
			if (FCsRoutine* R = GetRoutine(Handle))
				return R->HasJustEnded();
			return true;
		}

		#pragma endregion End

		// Update
		#pragma region

		void FCustom::Update(const int32& OwnerID, const FCsDeltaTime& DeltaTime)
		{
			SET_CONTEXT(Update);

			check(Manager_OwnerID.IsAllocatedChecked(Context, OwnerID));

			const int32& MaxRoutinesPerOwner = FCsSettings_CoroutineScheduler_Custom::Get().MaxRoutinesPerOwner;

			// End any pending Handles requested for End from the previous Update
			{
				const int32 Stride = QueueEndHandleStrideByOwnerID[OwnerID];
				const int32 Start  = OwnerID * MaxRoutinesPerOwner;
				
				for (int32 I = 0; I < Stride; ++I)
				{
					const int32 Index			   = Start+ I;
					const FCsRoutineHandle& Handle = OwnerQueueEndHandles[Index];

					End(OwnerID, Handle);

					OwnerQueueEndHandles[Index].Invalidate();
				}

				QueueEndHandleStrideByOwnerID[OwnerID] = 0;
			}

			{
				const int32 Start  = OwnerID * MaxRoutinesPerOwner;
				const int32 Stride = RoutineStrideByOwnerID[OwnerID];
		
				static TArray<int32> IndicesToDeallocate;
				IndicesToDeallocate.Reset(IndicesToDeallocate.Max());

				for (int32 I = 0; I < Stride; ++I)
				{
					const int32& RoutineIndex = OwnerRoutineIDs[Start + I];

					RoutineResourceType* RoutineContainer = Manager_Routine.GetAt(RoutineIndex);
					FCsRoutine* R						  = RoutineContainer->Get();

					const StateType& State = R->State;

					// Init -> Update
					if (State == StateType::Init)
					{
						R->StartUpdate();
						R->Update(DeltaTime);
					}
					// Update
					else
					if (State == StateType::Update)
					{
						R->Update(DeltaTime);
					}

					// End
					if (State == StateType::End)
					{
						//LogTransaction(NCsCoroutineCached::ToUpdate(ScheduleType), TransactionType::End, R);

						R->Reset();
						Manager_Routine.Deallocate(RoutineContainer);

						IndicesToDeallocate.Add(I);
					}
				}

				// "Bubble" the Routines that have Ended to the End of the Stride
				for (int32 I = Stride - 1; I >= 0; --I)
				{
					if (IndicesToDeallocate.Find(I))
						continue;

					for (int32 J = I; J < Stride - 1; ++J)
					{
						int32 Temp			   = OwnerRoutineIDs[J + 1];
						OwnerRoutineIDs[J + 1] = OwnerRoutineIDs[J];
						OwnerRoutineIDs[J]	   = Temp;
					}
				}

				RoutineStrideByOwnerID[OwnerID] -= IndicesToDeallocate.Num();
			}

			// End any Handles requested for End on the current Update
			{
				const int32 Stride = QueueEndHandleStrideByOwnerID[OwnerID];
				const int32 Start  = OwnerID * MaxRoutinesPerOwner;
				
				for (int32 I = 0; I < Stride; ++I)
				{
					const int32 Index			   = Start + I;
					const FCsRoutineHandle& Handle = OwnerQueueEndHandles[Index];

					End(OwnerID, Handle);

					OwnerQueueEndHandles[Index].Invalidate();
				}

				QueueEndHandleStrideByOwnerID[OwnerID] = 0;
			}
		}

		#pragma endregion Update

		// Payload
		#pragma region

		PayloadResourceType* FCustom::GetPayloadContainer(PayloadType* Payload)
		{
			if (Payload->GetIndex() == INDEX_NONE)
			{
				PayloadResourceType* Container = Manager_Payload.Allocate();
				PayloadType* P				   = Container->Get();

				*P = *Payload;

				return Container;
			}
			return Manager_Payload.GetAt(Payload->GetIndex());
		}

		#pragma endregion Payload

		// Message
		#pragma region

		void FCustom::BroadcastMessage(const MessageType& Type, const FName& Message, void* Owner /*=nullptr*/)
		{
			TCsDoubleLinkedList<RoutineResourceType*>* Current = Manager_Routine.GetAllocatedHead();
			TCsDoubleLinkedList<RoutineResourceType*>* Next    = Current;

			while (Next)
			{
				Current								  = Next;
				RoutineResourceType* RoutineContainer = **Current;
				Next								  = Current->GetNextLink();

				FCsRoutine* R = RoutineContainer->Get();

				if (Owner)
				{
					if (R->Owner.GetOwner() == Owner)
						R->ReceiveMessage(Type, Message);
				}
				else
				{
					R->ReceiveMessage(Type, Message);
				}
			}
		}

		#pragma endregion Message

		// Log
		#pragma region

		void FCustom::LogTransaction(const FString& FunctionName, const TransactionType& Transaction, FCsRoutine* R)
		{
			/*
			if (CsCVarLogCoroutineTransactions->GetInt() == CS_CVAR_SHOW_LOG)
			{
				FString TransactionAsString = NCsCoroutine::NTransaction::ToActionString(Transaction);
			
				if (Transaction == TransactionType::End)
					TransactionAsString = NCsCoroutine::NTransaction::ToActionString(Transaction) + TEXT("(Reason=") + EMCsCoroutineEndReason::Get().ToString(R->endReason) + TEXT(")");

				const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(R->scheduleType);

				AActor* Actor			= R->GetActor();
				const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
				UObject* Object			= R->GetRObject();
				const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
				UObject* Owner			= R->GetOwner();
				const FString OwnerName	= Owner ? Owner->GetName() : NCsCached::Str::Empty;

				UWorld* World = nullptr;

				if (Actor)
					World = Actor->GetWorld();
				if (Object)
					World = Object->GetWorld();

				const float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

				const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->nameAsString;

				FString Elapsed = NCsCached::Str::None;

				if (Transaction == TransactionType::End)
				{
					const float Duration = CurrentTime - R->startTime;
					Elapsed = TEXT("Ran for ") + FString::FromInt(R->tickCount) + TEXT(" Ticks and  ") + UCsLibrary_Common::GetFloatAsStringWithPrecision(Duration, 2) + TEXT(" Seconds.");
				}

				if (Actor && Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Owner: %s using Actor: %s and Object: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *ObjectName, *Elapsed);
				}
				else
				if (Actor)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ActorName, *Elapsed);
				}
				else
				if (Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. Using Owner: %s. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *ObjectName, *Elapsed);
				}
				else
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s %s Routine with Coroutine: %s at %f. %s"), *FunctionName, *ScheduleTypeAsString, *TransactionAsString, *CoroutineName, CurrentTime, *Elapsed);
				}
			}
			*/
		}

		void FCustom::LogRunning()
		{
			/*
			if (CsCVarLogCoroutineRunning->GetInt() != CS_CVAR_SHOW_LOG)
				return;

			const uint8 Schedule = (uint8)ScheduleType;
			const int32 Count    = RoutinesToRun[Schedule].Num();

			if (Count == CS_EMPTY)
				return;

			UWorld* World = nullptr;

			if (UObject* Object = GetMyOwner())
				World = Object->GetWorld();

			float CurrentTime = World ? World->GetTimeSeconds() : UCsLibrary_Common::GetCurrentDateTimeSeconds();

			const FString& FunctionName		    = NCsCoroutineCached::Str::Update;
			const FString& ScheduleTypeAsString = EMCsCoroutineSchedule::Get().ToString(ScheduleType);

			UE_LOG(LogCsCoroutine, Warning, TEXT("%s: On%s. Running %d Coroutines at %f."), *FunctionName, *ScheduleTypeAsString, Count, CurrentTime);

			for (int32 Index = 0; Index < Count; ++Index)
			{
				FCsRoutine* R = RoutinesToRun[Schedule][Index];

				AActor* Actor			= R->GetActor();
				const FString ActorName = Actor ? Actor->GetName() : NCsCached::Str::Empty;
				UObject* Object			= R->GetRObject();
				const FString ObjectName = Object ? Object->GetName() : NCsCached::Str::Empty;
				UObject* Owner			= R->GetOwner();
				const FString OwnerName = Owner ? Owner->GetName() : NCsCached::Str::Empty;

				const FString CoroutineName = R->name == NAME_None ? NCsCached::Str::None : R->name.ToString();

				const float Duration = CurrentTime - R->startTime;

				if (Actor && Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Owner: %s using Actor: %s and Object: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, *ObjectName, R->tickCount, Duration);
				}
				else
				if (Actor)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ActorName, R->tickCount, Duration);
				}
				else
				if (Object)
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Using Owner: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, *ObjectName, R->tickCount, Duration);
				}
				else
				{
					UE_LOG(LogCsCoroutine, Warning, TEXT("-- Routine with Coroutine: %s. Running for %d Ticks and %f Seconds."), *CoroutineName, R->tickCount, Duration);
				}
			}
			*/
		}

		#pragma endregion Log

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef RoutineManagerType
		#undef RoutineResourceType
		#undef PayloadManagerType
		#undef PayloadResourceType
		#undef PayloadType
		#undef StateType
		#undef EndReasonType
		#undef TransactionType
		#undef MessageType
	}
}