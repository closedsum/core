// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Coordinators/GameplayTag/CsCoordinator_GameplayTag_Delegates.h"
// Log
#include "Utility/CsGameplayTagsLog.h"

class UObject;
class UCsCoordinator_GameplayTag;

namespace NCsGameplayTag
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSGAMEPLAYTAGS_API const FString GetSafe;
				}
			}
		}

		struct CSGAMEPLAYTAGS_API FLibrary
		{
		#define LogLevel void(*Log)(const FString&) = &NCsGameplayTags::FLog::Warning

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_GameplayTag from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_GameplayTag
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoordinator_GameplayTag from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			Log function for logging conditions that result in NOT getting
			*						the Context Root.
			* return				Context for UCsCoordinator_GameplayTag
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, LogLevel) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @oaram ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_GameplayTag
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoordinator_GameplayTag.
			*/
			static UCsCoordinator_GameplayTag* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoordinator_GameplayTag.
			*/
			template<typename T>
			static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsCoordinator_GameplayTag* O = GetChecked(Context, ContextObject);
				T* Other					  = Cast<T>(O);

				checkf(Other, TEXT("%s: Coordinator_GameplayTag is NOT of type: %s."), *Context, *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				UCsCoordinator_GameplayTag.
			*/
			static UCsCoordinator_GameplayTag* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

			/**
			* Safely get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				UCsCoordinator_GameplayTag.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				UCsCoordinator_GameplayTag* O = GetSafe(Context, ContextObject, Log);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Coordinator_GameplayTag is NOT of type: %s."), *Context, *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				UCsCoordinator_GameplayTag.
			*/
			static UCsCoordinator_GameplayTag* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel);

			/**
			* Safely get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				UCsCoordinator_GameplayTag.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel)
			{
				UCsCoordinator_GameplayTag* O = GetSafe(Context, ContextObject, OutSuccess, Log);

				OutSuccess = false;

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Coordinator_GameplayTag is NOT of type: %s."), *Context, *(T::StaticClass()->GetName())));
				}

				OutSuccess = true;

				return Other;
			}

			/**
			* Safely get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoordinator_GameplayTag.
			*/
			FORCEINLINE static UCsCoordinator_GameplayTag* GetSafe(const UObject* ContextObject)
			{
				using namespace NCsGameplayTag::NCoordinator::NLibrary::NCached;

				const FString& Context = Str::GetSafe;

				return GetSafe(Context, ContextObject, nullptr);
			}

			/**
			* Safely get the reference to UCsCoordinator_GameplayTag from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsCoordinator_GameplayTag.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafe(const UObject* ContextObject)
			{
				using namespace NCsGameplayTag::NCoordinator::NLibrary::NCached;

				const FString& Context = Str::GetSafe;

				return GetSafe<T>(Context, ContextObject, nullptr);
			}

		#pragma endregion Get

		// Active
		#pragma region
		public:

			FORCEINLINE static bool IsActiveChecked(const FString& Context, const UObject* ContextObject)
			{
				return GetChecked(Context, ContextObject) != nullptr;
			}

			FORCEINLINE static bool SafeIsActive(const FString& Context, const UObject* ContextObject, LogLevel)
			{
				return GetSafe(Context, ContextObject, Log) != nullptr;
			}
			FORCEINLINE static bool SafeIsActive(const UObject* ContextObject)
			{
				return GetSafe(ContextObject) != nullptr;
			}

		#pragma endregion Active

		// Class
		#pragma region
		public:

			static TSubclassOf<UCsCoordinator_GameplayTag> GetClassChecked(const FString& Context);

		#pragma endregion Class

		// StartPlay
		#pragma region
		public:

			static void StartPlayChecked(const FString& Context, const UObject* ContextObject);

		#pragma endregion StartPlay

		// Event
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameplayTag Event.
			* @param Event			
			*/
			static void ProcessGameplayTagEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameplayTag Event.
			* @param Event
			* @param Log			(optional)
			* return
			*/
			static bool SafeProcessGameplayTagEvent(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const FCsGameplayTagEvent& Event, LogLevel);

			/**
			* Broadcast a GameplayTag Event routed to the appropriated Group. 
			*  Some values may be optional (i.e. Flag, Value, ... etc).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameplayTag Event.
			* @param Event			GameplayTag Event Info to broadcast.
			*/
			static void BroadcastGameplayTagEventChecked(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const  FCsGameplayTagEvent& Event);

			/**
			* Broadcast a GameplayTag Event routed to the appropriated Group. 
			*  Some values may be optional (i.e. Flag, Value, ... etc).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Group			The route / "group" to direct the GameplayTag Event.
			* @param Event			GameplayTag Event to broadcast.
			* @param Log			Log function for logging conditions that result in NOT processing
			*						the GameplayTag Event.
			* return				Whether the Event was broadcasted or not.
			*/
			static bool SafeBroadcastGameplayTagEvent(const FString& Context, const UObject* ContextObject, const FECsGameplayTagCoordinatorGroup& Group, const  FCsGameplayTagEvent& Event, LogLevel);

		/*#define OnProccessEventGameInfoEventType NCsGameEvent::NCoordinator::FOnProcessGameEventInfo
			static OnProccessEventGameInfoEventType& GetOnProcessGameEventInfo_EventChecked(const FString& Context, const UObject* ContextObject, const FECsGameEventCoordinatorGroup& Group);
		#undef OnProccessEventGameInfoEventType*/

		#pragma endregion Event

		#undef LogLevel
		};
	}
}

using CsGameplayTagCoorindatorLibrary = NCsGameplayTag::NCoordinator::FLibrary;