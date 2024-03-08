// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class ACharacter;
class UObject;

namespace NCsCharacter
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetSafeByTag;
			}
		}
	}

	/**
	* Library of functions related to Character
	*/
	struct CSCORE_API FLibrary final
	{
	// Get
	#pragma region
	public:

		/**
		* Get an Character with the given Tag (checks ACharacter->Tags)
		*  NOTE: Find the FIRST Character the given Tag.
		*  NOTE: There should be only ONE Character with given Tag.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return
		*/
		static ACharacter* GetByTagChecked(const FString& Context, const UObject* WorldContext, const FName& Tag);

		/**
		* Get an Character (casted to type T) with the given Tag (checks ACharacter->Tags)
		*  NOTE: Find the FIRST Character the given Tag.
		*  NOTE: There should be only ONE Character with given Tag.
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
		* Safely get an Character with the given Tag (checks ACharacter->Tags)
		*  NOTE: Find the FIRST Character the given Tag.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* @param Log
		* return				Character
		*/
		static ACharacter* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &FCsLog::Warning);
		FORCEINLINE ACharacter* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			ACharacter* C = GetSafeByTag(Context, WorldContext, Tag, Log);
			OutSuccess    = C != nullptr;
			return C;
		}

		/**
		* Safely get an Character (casted to type T) with the given Tag (checks ACharacter->Tags)
		*  NOTE: Find the FIRST Character the given Tag.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* @param Log
		* return				Character
		*/
		template<typename T>
		FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, void(*Log)(const FString&) = &FCsLog::Warning)
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
		* Safely get an Character with the given Tag (checks ACharacter->Tags)
		*  NOTE: Find the FIRST Character the given Tag.
		* 
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return				Character
		*/
		FORCEINLINE static ACharacter* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
		{
			using namespace NCsCharacter::NLibrary::NCached;

			const FString& Context = Str::GetSafeByTag;

			return GetSafeByTag(Context, WorldContext, Tag, nullptr);
		}

		/**
		* Safely get an Character (casted to type T) with the given Tag (checks ACharacter->Tags)
		*  NOTE: Find the FIRST Character the given Tag.
		* 
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tag
		* return				Character
		*/
		template<typename T>
		FORCEINLINE static T* GetSafeByTag(const UObject* WorldContext, const FName& Tag)
		{
			using namespace NCsCharacter::NLibrary::NCached;

			const FString& Context = Str::GetSafeByTag;

			return GetSafeByTag<T>(Context, WorldContext, Tag, nullptr);
		}

		/**
		* Get a list of Characters with the given Tags (checks ACharacter->Tags).
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param OutCharacters		(out)
		*/
		static void GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters);

		/**
		* Get a Character with the given Tags (checks ACharacter->Tags).
		*  NOTE: Find the FIRST Character the given Tag.
		*  NOTE: There should be only ONE Character with given Tag.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* return				Character
		*/
		static ACharacter* GetByTagsChecked(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags);

		/**
		* Safely get a list of Characters with the given Tag (checks ACharacter->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param OutCharacters	(out)
		* @param Log			(optional)
		* return				Whether any Characters were found with Tags.
		*/
		static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, void(*Log)(const FString&) = &FCsLog::Warning);
		FORCEINLINE static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			OutSuccess = GetSafeByTags(Context, WorldContext, Tags, OutCharacters, Log);
			return OutSuccess;
		}

		/**
		* Safely get a Character with the given Tags (checks ACharacter->Tags).
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Tags
		* @param Log			(optional)
		* return				Character.
		*/
		static ACharacter* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, void(*Log)(const FString&) = &FCsLog::Warning);
		FORCEINLINE static ACharacter* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			ACharacter* C = GetSafeByTags(Context, WorldContext, Tags, Log);
			OutSuccess    = C != nullptr;
			return C;
		}

		/**
		* Get an Character with the given Name.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static ACharacter* GetByNameChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

		/**
		* Get an Character with the given Name.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static ACharacter* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Character with the given Name.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* return
		*/
		static ACharacter* GetSafeByName(const UObject* WorldContext, const FName& Name);

		/**
		* Get an Character with the given Label.
		* NOTE: - More than 1 Actor can have the SAME Label in Editor. In this case, the FIRST
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
		* Get an Character with the given Label.
		* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
		*		- Only valid in Editor.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Name
		* @param Log
		* return
		*/
		static ACharacter* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get an Character with the given Label.
		* NOTE: - More than 1 Character can have the SAME Label in Editor. In this case, the FIRST
		*		  Actor found in the search will be returned.
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