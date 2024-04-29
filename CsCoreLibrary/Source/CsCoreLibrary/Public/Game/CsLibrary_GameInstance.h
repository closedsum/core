// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UEngine;
class UGameInstance;

namespace NCsGameInstance
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORELIBRARY_API const FString GetSafe;
				extern CSCORELIBRARY_API const FString GetSafeAsObject;
				extern CSCORELIBRARY_API const FString IsSafe;
			}
		}
	}

	class CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static FString PrintObjectAndClass(const UGameInstance* Object);

		static FString PrintNameAndClass(const UGameInstance* Object);

	// Get
	#pragma region
	public:

		/**
		* Get GameInstance from ContextObject.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UGameInstance* GetChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Get GameInstance from ContextObject.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		template<typename T>
		static T* GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UGameInstance* O = GetChecked(Context, ContextObject);
			T* Other		 = Cast<T>(O);

			checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintNameAndClass(O), *(T::StaticClass()->GetName()));
			return Other;
		}

		/**
		* Safely get GameInstance from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		static UGameInstance* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely get GameInstance from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		template<typename T>
		static T* GetSafe(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			UGameInstance* O = GetSafe(Context, ContextObject, Log);

			if (!O)
				return nullptr;

			T* Other = Cast<T>(O);

			if (!Other)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintNameAndClass(O), *(T::StaticClass()->GetName())));
			}
			return Other;
		}

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UGameInstance* GetSafe(const UObject* ContextObject);

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		template<typename T>
		static T* GetSafe(const UObject* ContextObject)
		{
			using namespace NCsGameInstance::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe<T>(Context, ContextObject, nullptr);
		}

		/**
		* Get GameInstance from ContextObject.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UObject* GetAsObjectChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely get GameInstance from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log
		* return				GameInstance
		*/
		static UObject* GetSafeAsObject(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely get GameInstance from ContextObject.
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				GameInstance
		*/
		static UObject* GetSafeAsObject(const UObject* ContextObject);

	#pragma endregion Get

	// Is
	#pragma region
	public:

		/**
		* Check if the ContextObject is of type: UGameInstance
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return
		*/
		static bool IsChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Safely check if the ContextObject is of type: UGameInstance
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* @param Log			(optional)
		* return
		*/
		static bool IsSafe(const FString& Context, const UObject* ContextObject, LogLevel);

		/**
		* Safely check if the ContextObject is of type: UGameInstance
		*
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return
		*/
		static bool IsSafe(const UObject* ContextObject);

		FORCEINLINE static bool SafeIsReachable(const UObject* ContextObject)
		{
			return GetSafe(ContextObject) != nullptr;
		}

	#pragma endregion Is

	// Engine
	#pragma region
	public:

		static UEngine* GetEngineChecked(const FString& Context, const UObject* ContextObject);

		static UEngine* GetSafeEngine(const FString& Context, const UObject* ContextObject, LogLevel);

	#pragma endregion Engine

	#undef LogLevel
	};
}