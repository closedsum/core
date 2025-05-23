// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"
#include "Coroutine/CsRoutine.h"

#define CS_ROUTINE_POOL_SIZE 2048
#define CS_COROUTINE_PAYLOAD_SIZE 64

// Structs
#pragma region

	// Routine
	
namespace NCsRoutine
{
	struct CSCOROUTINE_API FResource : public TCsResourceContainer<FCsRoutine>
	{
		~FResource(){}
	};

	struct CSCOROUTINE_API FManager : public NCsResource::NManager::NValue::TFixed<FCsRoutine, FResource, CS_ROUTINE_POOL_SIZE>
	{
		~FManager(){}
	};
}

	// Payload

namespace NCsCoroutine
{
	namespace NPayload
	{
		struct CSCOROUTINE_API FResource : public TCsResourceContainer<FImpl>
		{
			~FResource(){}
		};

		struct CSCOROUTINE_API FManager : public NCsResource::NManager::NValue::TFixed<FImpl, FResource, CS_COROUTINE_PAYLOAD_SIZE>
		{
			~FManager(){}
		};
	}
}

#pragma endregion Structs

namespace NCsCoroutine
{
	namespace NSchedule
	{
		class CSCOROUTINE_API FDefault
		{
		public:

			FDefault();

			virtual ~FDefault();

		private:

			using PayloadManagerType = NCsCoroutine::NPayload::FManager;
			using PayloadResourceType = NCsCoroutine::NPayload::FResource;
			using PayloadType = NCsCoroutine::NPayload::FImpl;
			using RoutineManagerType = NCsRoutine::FManager;
			using RoutineResourceType = NCsRoutine::FResource;
			using MessageType = NCsCoroutine::EMessage;
			using TransactionType = NCsCoroutine::ETransaction;

		// Schedule
		#pragma region
		protected:

			/** */
			FECsUpdateGroup Group;

		public:

			/**
			*
			*
			* @param InGroup
			*/
			void SetGroup(const FECsUpdateGroup& InGroup);

		#pragma endregion Schedule

		// Routine
		#pragma region
		protected:		

			/** */
			RoutineManagerType Manager_Routine;

		public:

			/**
			*
			*
			* @param Handle
			* return
			*/
			RoutineResourceType* GetRoutineContainer(const FCsRoutineHandle& Handle) const;

			/**
			*
			*
			* @param Handle
			* return
			*/
			FCsRoutine* GetRoutine(const FCsRoutineHandle& Handle) const;

		#pragma endregion Routine

		// Handle
		#pragma region
		public:

			FORCEINLINE bool IsHandleValid(const FCsRoutineHandle& Handle) const
			{
				return GetRoutineContainer(Handle) != nullptr;
			}

			bool IsRunning(const FCsRoutineHandle& Handle) const;

		#pragma endregion Handle

		// Start
		#pragma region
		public:

			/**
			*
			*
			* @param PayloadContainer
			* return
			*/
			const FCsRoutineHandle& Start(PayloadResourceType* PayloadContainer);

			/**
			*
			*
			* @param Payload
			* return
			*/
			const FCsRoutineHandle& Start(PayloadType* Payload);

			/**
			*
			*
			* @param PayloadContainer
			* return
			*/
			const FCsRoutineHandle& StartChild(PayloadResourceType* PayloadContainer);

			/**
			*
			*
			* @param Payload
			* return
			*/
			const FCsRoutineHandle& StartChild(PayloadType* Payload);

		#pragma endregion Start

		// End
		#pragma region
		public:

			/**
			* End all routines.
			*/
			bool End();

			/**
			* End the routine associated with the Handle.
			*
			* @param Handle		Handle to a routine.
			* return			Whether the routine has successful ended.
			*					NOTE: If the routine has already ended or send to queued to end, 
			*						  this will return false.
			*/
			bool End(const FCsRoutineHandle& Handle);

			/**
			* Check if a routine associated with the Handle has already ended.
			* NOTE: This returns True if Handle is NOT Valid.
			* 
			* @param Handle		Handle to a routine.
			* return			Whether the routine has already ended.
			*/
			bool HasEnded(const FCsRoutineHandle& Handle) const;

			/**
			* Check if a routine associated with the Handle has just ended.
			*
			* @param Handle		Handle to a routine.
			* return			Whether the routine has just ended.
			*/
			bool HasJustEnded(const FCsRoutineHandle& Handle) const;

		private:

			/** Handles to End either beginning of the next Update or the end of the
				current Update.
				NOTE: This list is populated when a Routine is currently being Executed and
					  requested to End. */
			TArray<FCsRoutineHandle> QueueEndHandles;

		#pragma endregion End

		// Update
		#pragma region
		public:

			/**
			*
			*
			* @param DeltaTime
			*/
			void Update(const FCsDeltaTime& DeltaTime);

		#pragma endregion Update

		// Payload
		#pragma region
		protected:

			/** */
			PayloadManagerType Manager_Payload;

		public:

			/**
			*
			*
			* return
			*/
			FORCEINLINE PayloadResourceType* AllocatePayloadContainer()
			{
				return Manager_Payload.Allocate();
			}

			/**
			*
			*
			* return
			*/
			FORCEINLINE PayloadType* AllocatePayload()
			{
				return Manager_Payload.AllocateResource();
			}

		protected:

			/**
			*
			*
			* @param Payload
			* return
			*/
			PayloadResourceType* GetPayloadContainer(PayloadType* Payload);

		#pragma endregion Payload

		// Message
		#pragma region
		public:		

			/**
			*
			*
			* @param Type
			* @param Message
			* @param Owner
			*/
			void BroadcastMessage(const MessageType& Type, const FName& Message, void* Owner = nullptr);

		#pragma endregion Message

		// Log
		#pragma region
		public:

			/**
			*
			*
			* @param FunctionName
			* @param Transaction
			* @param R
			*/
			void LogTransaction(const FString& FunctionName, const TransactionType& Transaction, FCsRoutine* R);

			/**
			*
			*/
			void LogRunning();

		#pragma endregion Log
		};
	}
}

namespace NCsCoroutine
{
	namespace NSchedule
	{
		class CSCOROUTINE_API FCustom
		{
		public:

			FCustom();

			virtual ~FCustom();
		
		private:

			using IDManagerType = NCsResource::NManager::NValue::NFixed::NInt32::FManager;
			using PayloadManagerType = NCsCoroutine::NPayload::FManager;
			using PayloadResourceType = NCsCoroutine::NPayload::FResource;
			using PayloadType = NCsCoroutine::NPayload::FImpl;
			using RoutineManagerType = NCsRoutine::FManager;
			using RoutineResourceType = NCsRoutine::FResource;
			using MessageType = NCsCoroutine::EMessage;
			using TransactionType = NCsCoroutine::ETransaction;

		// Owner
		#pragma region
		private:

			IDManagerType Manager_OwnerID;

			// Max Owners * Max Allocated Routines (Stride)
			TArray<int32> OwnerRoutineIDs;
			TArray<int32> RoutineStrideByOwnerID;

		public:

			int32 AllocateOwnerID();

			void DeallocateOwnerID(const int32& OwnerID);

			bool HasFreeOwnerID() const { return !Manager_OwnerID.IsExhausted(); }

		private:

			int32 GetOwnerID(const int32& RoutineIndex);
			FORCEINLINE int32 GetOwnerID(FCsRoutine* R)
			{
				checkf(R, TEXT("NCsCoroutine::NSchedule::FCustom::GetOwnerID: R is NULL."));
				return GetOwnerID(R->GetIndex());
			}
			int32 GetOwnerID(const FCsRoutineHandle& Handle);

		#pragma endregion Owner

		// Schedule
		#pragma region
		protected:

			/** */
			FECsUpdateGroup Group;

		public:

			/**
			*
			*
			* @param InGroup
			*/
			void SetGroup(const FECsUpdateGroup& InGroup);

		#pragma endregion Schedule

		// Routine
		#pragma region
		protected:

			/** */
			RoutineManagerType Manager_Routine;

		public:

			/**
			*
			*
			* @param Handle
			* return
			*/
			RoutineResourceType* GetRoutineContainer(const FCsRoutineHandle& Handle) const;

			/**
			*
			*
			* @param Handle
			* return
			*/
			FCsRoutine* GetRoutine(const FCsRoutineHandle& Handle) const;

		#pragma endregion Routine

		// Handle
		#pragma region
		public:

			FORCEINLINE bool IsHandleValid(const FCsRoutineHandle& Handle) const
			{
				return GetRoutineContainer(Handle) != nullptr;
			}

			bool IsRunning(const FCsRoutineHandle& Handle) const;

		#pragma endregion Handle

		// Start
		#pragma region
		public:

			/**
			*
			*
			* @param PayloadContainer
			* return
			*/
			const FCsRoutineHandle& Start(const int32& OwnerID, PayloadResourceType* PayloadContainer);

			/**
			*
			*
			* @param Payload
			* return
			*/
			const FCsRoutineHandle& Start(const int32& OwnerID, PayloadType* Payload);

			/**
			*
			*
			* @param PayloadContainer
			* return
			*/
			const FCsRoutineHandle& StartChild(const int32& OwnerID, PayloadResourceType* PayloadContainer);

			/**
			*
			*
			* @param Payload
			* return
			*/
			const FCsRoutineHandle& StartChild(const int32& OwnerID, PayloadType* Payload);

		#pragma endregion Start

		// End
		#pragma region
		public:

			/**
			* End all routines.
			*/
			bool End();

			/**
			* End all routines associated with Owner ID.
			* 
			* @param Owner ID
			*/
			bool End(const int32& OwnerID);

			/**
			* End the routine associated with the Handle.
			*
			* @param Handle		Handle to a routine.
			* return			Whether the routine has successful ended.
			*					NOTE: If the routine has already ended or send to queued to end, 
			*						  this will return false.
			*/
			bool End(const int32& OwnerID, const FCsRoutineHandle& Handle);

			/**
			* End the routine associated with the Handle.
			*
			* @param Handle		Handle to a routine.
			* return			Whether the routine has successful ended.
			*					NOTE: If the routine has already ended or send to queued to end, 
			*						  this will return false.
			*/
			FORCEINLINE bool End(const FCsRoutineHandle& Handle) 
			{
				return End(GetOwnerID(Handle), Handle);
			}

			/**
			* Check if a routine associated with the Handle has already ended.
			* NOTE: This returns True if Handle is NOT Valid.
			* 
			* @param Handle		Handle to a routine.
			* return			Whether the routine has already ended.
			*/
			bool HasEnded(const FCsRoutineHandle& Handle) const;

			/**
			* Check if a routine associated with the Handle has just ended.
			*
			* @param Handle		Handle to a routine.
			* return			Whether the routine has just ended.
			*/
			bool HasJustEnded(const FCsRoutineHandle& Handle) const;

		private:

			/** Handles to End either beginning of the next Update or the end of the
				current Update.
				NOTE: This list is populated when a Routine is currently being Executed and
					  requested to End. */
			TArray<FCsRoutineHandle> OwnerQueueEndHandles;
			TArray<int32> QueueEndHandleStrideByOwnerID;

		#pragma endregion End

		// Update
		#pragma region
		public:

			/**
			*
			*
			* @param DeltaTime
			*/
			void Update(const int32& OwnerID, const FCsDeltaTime& DeltaTime);

		#pragma endregion Update

		// Payload
		#pragma region
		protected:

			/** */
			PayloadManagerType Manager_Payload;

		public:

			/**
			*
			*
			* return
			*/
			FORCEINLINE PayloadResourceType* AllocatePayloadContainer()
			{
				return Manager_Payload.Allocate();
			}

			/**
			*
			*
			* return
			*/
			FORCEINLINE PayloadType* AllocatePayload()
			{
				return Manager_Payload.AllocateResource();
			}

		protected:

			/**
			*
			*
			* @param Payload
			* return
			*/
			PayloadResourceType* GetPayloadContainer(PayloadType* Payload);

		#pragma endregion Payload

		// Message
		#pragma region
		public:

			/**
			*
			*
			* @param Type
			* @param Message
			* @param Owner
			*/
			void BroadcastMessage(const MessageType& Type, const FName& Message, void* Owner = nullptr);

		#pragma endregion Message

		// Log
		#pragma region
		public:

			/**
			*
			*
			* @param FunctionName
			* @param Transaction
			* @param R
			*/
			void LogTransaction(const FString& FunctionName, const TransactionType& Transaction, FCsRoutine* R);

			/**
			*
			*/
			void LogRunning();

		#pragma endregion Log
		};
	}
}