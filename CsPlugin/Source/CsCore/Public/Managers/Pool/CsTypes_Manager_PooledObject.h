// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// CVar
#include "CsCVars.h"
// Types
#include "Managers/Pool/CsTypes_Pool.h"
// World
#include "Engine/World.h"

class UWorld;
class UObject;
class UClass;

namespace NCsPooledObject
{
	namespace NManager
	{
		// FConstructParams
		#pragma region

		/**
		*/
		struct CSCORE_API FConstructParams
		{
		public:

			UObject* Outer;

			UClass* Class;

			/** Pass through name of the Type. This additional data is not usually used in
				normal cases. Can be used a additional Type information for a nested object. */
			FName TypeName;

			/** Pass through name of the Class Type. This additional data is not usually used in
				normal cases. Can be used a additional Type information for a nested object. */
			FName ClassTypeName;

			NCsPooledObject::EConstruction ConstructionType;

			FActorSpawnParameters ConstructionInfo;

			/**
			* Custom delegate to construct a UObject (usually UObject is constructed via NewObject).
			*
			* return UObject
			*/
			TDelegate<UObject* /*Object*/(const FConstructParams& /*Params*/)> CustomNewObject_Impl;

			bool bReplicates;

			FConstructParams();
		};

#		pragma endregion FConstructParams

		// FPoolParams
		#pragma region

		/**
		*/
		struct CSCORE_API FPoolParams
		{
		public:

			/** */
			FString Name;

			/** World associated with the Manager. */
			UWorld* World;

			/** */
			FECsCVarLog LogType;

			/** Parameters for describing how to Construct a Pooled Object. */
			FConstructParams ConstructParams;

			/** Whether to Construct the Payloads on Init. */
			bool bConstructPayloads;

			/** Number of Payloads to Construct if bConstructPayloads is true. */
			int32 PayloadSize;

			/** Whether to Create a Pool on Init. */
			bool bCreatePool;

			/** Size of the Pool to create if bCreatePool is true. */
			int32 PoolSize;

			// Scoped Timer

			FECsScopedGroup ScopedGroup;

			/** Scoped Timer for CreatePool */
			FECsCVarLog CreatePoolScopedTimerCVar;
			/** Scoped Timer for Update */
			FECsCVarLog UpdateScopedTimerCVar;
			/** Scoped Timer for Updating a single Object */
			FECsCVarLog UpdateObjectScopedTimerCVar;
			/** Scoped Timer for Allocate */
			FECsCVarLog AllocateScopedTimerCVar;
			/** Scoped Timer for PooledObject->Allocate */
			FECsCVarLog AllocateObjectScopedTimerCVar;
			/** Scoped Timer for Deallocate */
			FECsCVarLog DeallocateScopedTimerCVar;
			/** Scoped Timer for PooledObject->Deallocate */
			FECsCVarLog DeallocateObjectScopedTimerCVar;
			/** Scoped Timer for Spawn */
			FECsCVarLog SpawnScopedTimerCVar;
			/** Scoped Timer for Destroy */
			FECsCVarLog DestroyScopedTimerCVar;

			FPoolParams();
		};

		#pragma endregion FPoolParams
	}
}