// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Spawner/Modifier/Types/CsTypes_SpawnerModifier.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class UCsManager_Spawner;
class UClass;

// NCsSpawner::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, FResource)
// NCsSpawner::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, IModifier)

namespace NCsSpawner
{
	namespace NManager
	{
		/**
		*/
		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Spawner from a WorldContext.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Spawner.
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Spawner from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Spawner.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Spawner from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Spawner.
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Spawner from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Spawner.
			*/
			static UCsManager_Spawner* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_Spawner from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Spawner.
			*/
			static UCsManager_Spawner* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Spawner from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Spawner.
			*/
			static UCsManager_Spawner* GetSafe(const UObject* WorldContext);

		#pragma endregion Get
		};

		namespace NModifier
		{
			struct CSCORE_API FLibrary final
			{
			public:

			#define ModifierResourceType NCsSpawner::NModifier::FResource
			#define ModifierType NCsSpawner::NModifier::IModifier

				static ModifierResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsSpawnerModifier& Type);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsSpawnerModifier& Type, ModifierResourceType* Modifier);

				static const FECsSpawnerModifier& GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier);

			#undef ModifierResourceType
			#undef ModifierType
			};
		}
	}
}