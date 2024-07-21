// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsJsLog.h"

class ACharacter;
class UObject;

namespace NCsCharacter
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
		// Interface
		#pragma region
		public:

			static bool Implements(const ACharacter* A);

		#pragma endregion Interface

		// Get
		#pragma region
		public:

			/**
			* Get all Scriptable Characters.
			*  Characters MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutCharacters		(out)
			* return
			*/
			static void GetChecked(const FString& Context, const UObject* WorldContext, TArray<ACharacter*>& OutCharacters);

			/**
			* Safely get all Scriptable Characters.
			*  Characters MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutCharacters	(out)
			* @param Log			(optional)
			* return				Whether GetSafe was excuted successfully or not.
			*/
			static bool GetSafe(const FString& Context, const UObject* WorldContext, TArray<ACharacter*>& OutCharacters, void(*Log)(const FString&) = &NCsJs::FLog::Warning);

			/**
			* Get a Scriptable Character with the given Tag (checks AActor->Tags).
			*  Character MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return
			*/
			static ACharacter* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

			/**
			* Get a Scriptable Character (casted to type T) with the given Tag (checks AActor->Tags).
			*  Character MUST implement the interface: ICsScriptableActor.
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

				checkf(A, TEXT("%s: Failed to cast Character to type: %s."), *Context, *(T::StaticClass()->GetName()));

				return A;
			}

			/**
			* Safely get a Scriptable Character with the given Tag (checks AActor->Tags).
			*  Character MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* @param Log
			* return				Character
			*/
			static ACharacter* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &NCsJs::FLog::Warning);

			/**
			* Safely get a Scriptable Character (casted to type T) with the given Tag (checks AActor->Tags)
			*  Character MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* @param Log
			* return				Character
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &NCsJs::FLog::Warning)
			{
				T* A = Cast<T>(GetSafeByTag(Context, WorldContext, Tag, Log));

				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Failed to cast Character to type: %s."), *Context, *(T::StaticClass()->GetName())));
				}
				return A;
			}

			/**
			* Safely get a Scriptable Character with the given Tag (checks AActor->Tags).
			*  Character MUST implement the interface: ICsScriptableActor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				Character
			*/
			FORCEINLINE static ACharacter* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
			{
				using namespace NCsCharacter::NScriptable::NLibrary::NCached;

				const FString& Context = Str::GetSafeByTag;

				return GetSafeByTag(Context, WorldContext, Tag, nullptr);
			}

			/**
			* Safely get a Scriptable Character (casted to type T) with the given Tag (checks AActor->Tags).
			*  Character MUST implement the interface: ICsScriptableActor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tag
			* return				Character
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
			{
				using namespace NCsCharacter::NScriptable::NLibrary::NCached;

				const FString& Context = Str::GetSafeByTag;

				return GetSafeByTag<T>(Context, WorldContext, Tag, nullptr);
			}

			/**
			* Get a list of Scriptable Characters with the given Tag (checks AActor->Tags).
			*  Characters MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* @param OutCharacters	(out)
			*/
			static void GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters);

			/**
			* Safely get a list of Scriptable Characters with the given Tag (checks AActor->Tags).
			*  Characters MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Tags
			* @param OutCharacters	(out)
			* @param Log			(optional)
			* return				Whether any characters were found with Tags.
			*/
			static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, void(*Log)(const FString&) = &NCsJs::FLog::Warning);

			/**
			* Get a Scriptable Character with the given Name.
			*  Character MUST implement the interface: ICsScriptableActor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static ACharacter* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Get a Scriptable Character with the given Name.
			*  Character MUST implement the interface: ICsScriptableActor.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log
			* return
			*/
			static ACharacter* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsJs::FLog::Warning);

			/**
			* Get a Scriptable Character with the given Name.
			*  Character MUST implement the interface: ICsScriptableActor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static ACharacter* GetSafeByName(const UObject* WorldContext, const FName& Name);

			/**
			* Get a Scriptable Character with the given Label.
			*  Character MUST implement the interface: ICsScriptableActor.
			* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
			*		  Character found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Level
			* return
			*/
			static ACharacter* GetByLabelChecked(const FString& Context, const UObject* WorldContext, const FString& Label);

			/**
			* Get a Scriptable Character with the given Label.
			*  Character MUST implement the interface: ICsScriptableActor.
			* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
			*		  Character found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* @param Log
			* return
			*/
			static ACharacter* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &NCsJs::FLog::Warning);

			/**
			* Get a Scriptable Character with the given Label.
			*  Character MUST implement the interface: ICsScriptableActor.
			* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
			*		  Character found in the search will be returned.
			*		- Only valid in Editor.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name
			* return
			*/
			static ACharacter* GetSafeByLabel(const UObject* WorldContext, const FString& Label);

		#pragma endregion Get
		};
	}
}