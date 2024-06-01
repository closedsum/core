// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Animation/CsTypes_AnimMontage.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class ACharacter;
class UObject;
class UAnimMontage;

namespace NCsCharacter
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORELIBRARY_API const FString GetSafeByTag;
			}
		}
	}

	/**
	* Library of functions related to Character
	*/
	struct CSCORELIBRARY_API FLibrary final
	{
	#define LogWarning void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning
	#define USING_NS_CACHED using namespace NCsCharacter::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsCharacter::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

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
		static ACharacter* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogWarning);
		FORCEINLINE ACharacter* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, bool& OutSuccess, LogWarning)
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
		FORCEINLINE static T* GetSafeByTag(const FString& Context, const UObject* WorldContext, const FName& Tag, LogWarning)
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
			SET_CONTEXT(GetSafeByTag);

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
		static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, LogWarning);
		FORCEINLINE static bool GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, TArray<ACharacter*>& OutCharacters, bool& OutSuccess, LogWarning)
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
		static ACharacter* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, LogWarning);
		FORCEINLINE static ACharacter* GetSafeByTags(const FString& Context, const UObject* WorldContext, const TArray<FName>& Tags, bool& OutSuccess, LogWarning)
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
		static ACharacter* GetSafeByName(const FString& Context, const UObject* WorldContext, const FName& Name, LogWarning);

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
		static ACharacter* GetSafeByLabel(const FString& Context, const UObject* WorldContext, const FString& Label, LogWarning);

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

	// Anim
	#pragma region
	public:

	#define ParamsType NCsAnimMontage::NPlay::FParams

		static float PlayChecked(const FString& Context, const ACharacter* Character, const ParamsType& Params);
		FORCEINLINE static float PlayChecked(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayParams& Params)
		{
			return PlayChecked(Context, Character, ParamsType::Make(Params));
		}

		static float SafePlay(const FString& Context, const ACharacter* Character, const ParamsType& Params, bool& OutSuccess, LogWarning);
		FORCEINLINE static float SafePlay(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayParams& Params, bool& OutSuccess, LogWarning)
		{
			return SafePlay(Context, Character, ParamsType::Make(Params), OutSuccess, Log);
		}
		FORCEINLINE static float SafePlay(const FString& Context, const ACharacter* Character, const ParamsType& Params, LogWarning)
		{
			bool Success = false;
			return SafePlay(Context, Character, Params, Success, Log);
		}
		FORCEINLINE static float SafePlay(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayParams& Params, LogWarning)
		{
			return SafePlay(Context, Character, ParamsType::Make(Params), Log);
		}

		static float SafePlay(const FString& Context, const ACharacter* Character, const FCsAnimMontage_PlayByPathParams& Params, bool& OutSuccess, LogWarning);
		FORCEINLINE static float SafePlay(const FString& Context,  const ACharacter* Character, const FCsAnimMontage_PlayByPathParams& Params, LogWarning)
		{
			bool Success = false;
			return SafePlay(Context, Character, Params, Success, Log);
		}

	#undef ParamsType

	#pragma endregion Anim

	#undef LogWarning
	#undef USING_NS_CACHED
	#undef SET_CONTEXT
	};
}