// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsJsLog.h"

class AActor;
class UObject;

namespace NCsActor
{
	namespace NScriptable
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSJS_API const FString GetSafeByTag;
				}
			}
		}

		/**
		* Library of functions related to an Actor that implements the interface: ICsScriptableActor
		*/
		struct CSJS_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsJs::FLog::Warning

		// Interface
		#pragma region
		public:

			static bool Implements(const AActor* A);
			static bool Implements(const AActor* A, bool& OutIsScript);

			static bool SafeImplements(const FString& Context, const AActor* A, LogLevel);
			static bool SafeImplements(const FString& Context, const AActor* A, bool& OutIsScript, LogLevel);

		#pragma endregion Interface

		// Get
		#pragma region
		public:

			/**
			* Get all Scriptable Actors.
			*  Actors MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutActors		(out)
			* return
			*/
			static void GetChecked(const FString& Context, const UObject* WorldContext, TArray<AActor*>& OutActors);

			/**
			* Safely get all Scriptable Actors.
			*  Actors MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutActors		(out)
			* @param Log			(optional)
			* return				Whether GetSafe was excuted successfully or not.
			*/
			static bool GetSafe(const FString& Context, const UObject* WorldContext, TArray<AActor*>& OutActors, LogLevel);

			/**
			* Get a Scriptable Actor with the given Tag (checks AActor->Tags).
			*  Actor MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return
			*/
			static AActor* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

			/**
			* Get a Scriptable Actor (casted to type T) with the given Tag (checks AActor->Tags).
			*  Actor MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return
			*/
			template<typename T>
			FORCEINLINE static T* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag)
			{
				T* A = Cast<T>(GetByTagChecked(Context, WorldContext, Tag));

				checkf(A, TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName()));

				return A;
			}

			/**
			* Safely get a Scriptable Actor with the given Tag (checks AActor->Tags).
			*  Actor MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* @param Log
			* return				Actor
			*/
			static AActor* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogLevel);

			/**
			* Safely get a Scriptable Actor (casted to type T) with the given Tag (checks AActor->Tags)
			*  Actor MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* @param Log
			* return				Actor
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogLevel)
			{
				T* A = Cast<T>(GetSafeByTag(Context, WorldContext, Tag, Log));

				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Failed to cast Actor to type: %s."), *Context, *(T::StaticClass()->GetName())));
				}
				return A;
			}

			/**
			* Safely get a Scriptable Actor with the given Tag (checks AActor->Tags).
			*  Actor MUST implement the interface: ICsScriptableActor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				Actor
			*/
			FORCEINLINE static AActor* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
			{
				using namespace NCsActor::NScriptable::NLibrary::NCached;

				const FString& Context = Str::GetSafeByTag;

				return GetSafeByTag(Context, WorldContext, Tag, nullptr);
			}

			/**
			* Safely get a Scriptable Actor (casted to type T) with the given Tag (checks AActor->Tags).
			*  Actor MUST implement the interface: ICsScriptableActor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				Actor
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
			{
				using namespace NCsActor::NScriptable::NLibrary::NCached;

				const FString& Context = Str::GetSafeByTag;

				return GetSafeByTag<T>(Context, WorldContext, Tag, nullptr);
			}

			/**
			* Get a list of Scriptable Actors with the given Tag (checks AActor->Tags).
			*  Actors MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* @param OutActors		(out)
			*/
			static void GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors);

			/**
			* Safely get a list of Scriptable Actors with the given Tag (checks AActor->Tags).
			*  Actors MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* @param OutActors		(out)
			* @param Log			(optional)
			* return				Whether any actors were found with Tags.
			*/
			static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<AActor*>& OutActors, LogLevel);

			/**
			* Get a Scriptable Actor with the given Name.
			*  Actor MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static AActor* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Get a Scriptable Actor with the given Name.
			*  Actor MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log
			* return
			*/
			static AActor* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, LogLevel);

			/**
			* Get a Scriptable Actor with the given Name.
			*  Actor MUST implement the interface: ICsScriptableActor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static AActor* GetSafeByName(const UObject* WorldContext, const FName& Name);

			/**
			* Get a Scriptable Actor with the given Label.
			*  Actor MUST implement the interface: ICsScriptableActor.
			* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Level
			* return
			*/
			static AActor* GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label);

			/**
			* Get a Scriptable Actor with the given Label.
			*  Actor MUST implement the interface: ICsScriptableActor.
			* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log
			* return
			*/
			static AActor* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, LogLevel);

			/**
			* Get a Scriptable Actor with the given Label.
			*  Actor MUST implement the interface: ICsScriptableActor.
			* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
			*		  Actor found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static AActor* GetSafeByLabel(const UObject* WorldContext, const FString& Label);

		#pragma endregion Get

		#undef LogLevel
		};
	}
}

using CsScriptableActorLibrary = NCsActor::NScriptable::FLibrary;