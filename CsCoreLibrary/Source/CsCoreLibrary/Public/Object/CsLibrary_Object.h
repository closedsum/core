// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "UObject/SoftObjectPath.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UClass;

namespace NCsObject
{
	/**
	*/
	class CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static FString PrintObjectAndClass(const UObject* Object);

		static FString PrintNameAndClass(const UObject* Object);

		static bool IsValidObject(const UObject* Object);

		static bool IsPendingKill(const UObject* Object);

	#if WITH_EDITOR
		static bool IsValidChecked(const FString& Context, const UObject* Object);
	#else
		FORCEINLINE static bool IsValidChecked(const FString& Context, const UObject* Object) { return true; }
	#endif // #if WITH_EDITOR

		static bool SafeIsValid(const FString& Context, const UObject* Object, LogLevel);

		/**
		*
		*
		* @param Object
		* return
		*/
		static FString GetFlagsAsString(const UObject* Object);

		static UObject* ConstructChecked(const FString& Context, UObject* Outer, UClass* Class);
		static UObject* SafeConstruct(const FString& Context, UObject* Outer, UClass* Class, LogLevel);

		static UObject* GetDefaultObjectChecked(const FString& Context, const UObject* Object);
		static UObject* GetSafeDefaultObject(const FString& Context, const UObject* Object, LogLevel);

		static bool IsDefaultObjectChecked(const FString& Context, const UObject* Object);
		static bool SafeIsDefaultObject(const FString& Context, const UObject* Object, LogLevel);
		static bool IsDefaultObject(const UObject* Object);

		static int32 GetUniqueIDChecked(const FString& Context, const UObject* Object);
		static int32 GetSafeUniqueID(const FString& Context, const UObject* Object, LogLevel);

	// Load
	#pragma region
	public:

		/**
		* Load a Object at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Object to load.
		* return			Object.
		*/
		static UObject* LoadChecked(const FString& Context, const FSoftObjectPath& Path);

		/**
		* Load a Object of type: T at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to type: T to load.
		* return			Object of type: T.
		*/
		template<typename T>
		static T* LoadChecked(const FString& Context, const FSoftObjectPath& Path)
		{
			UObject* Object = LoadChecked(Context, Path);

			T* Other = Cast<T>(Object);

			checkf(Other, TEXT("%s: %s @ %s is NOT of type: %s."), *Context, *PrintObjectAndClass(Object), *(Path.ToString()), *(T::StaticClass()->GetName()));
			return Other;
		}

		/**
		* Safely load a Object at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Object to load.
		* @param Log
		* return			Object.
		*/
		static UObject* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

		/**
		* Safely load a Object of type: T at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to type: T to load.
		* @param Log
		* return			Object of type: T.
		*/
		template<typename T>
		static T* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel)
		{
			UObject* Object = SafeLoad(Context, Path, Log);

			if (!Object)
				return nullptr;

			T* Other = Cast<T>(Object);

			if (!Other)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s @ %s is NOT of type: %s."), *Context, *PrintObjectAndClass(Object), *(Path.ToString()), *(T::StaticClass()->GetName())));
				return nullptr;
			}
			return Other;
		}

		/**
		* Load a Object at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Object to load.
		* return			Object.
		*/
		static UObject* LoadChecked(const FString& Context, const FString& Path);

		/**
		* Load a Object of type: T at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to type: T to load.
		* return			Object of type: T.
		*/
		template<typename T>
		static T* LoadChecked(const FString& Context, const FString& Path)
		{
			UObject* Object = LoadChecked(Context, Path);

			T* Other = Cast<T>(Object);

			checkf(Other, TEXT("%s: %s @ %s is NOT of type: %s."), *Context, *PrintObjectAndClass(Object), *Path, *(T::StaticClass()->GetName()));
			return Other;
		}

		/**
		* Safely load a Object at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Object to load.
		* @param Log
		* return			Object.
		*/
		static UObject* SafeLoad(const FString& Context, const FString& Path, LogLevel);

		/**
		* Safely load a Object of type: T at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to type: T to load.
		* @param Log
		* return			Object of type: T.
		*/
		template<typename T>
		static T* SafeLoad(const FString& Context, const FString& Path, LogLevel)
		{
			if (Path.IsEmpty())
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: Path is EMPTY."), *Context));
				return nullptr;
			}

			FSoftObjectPath SoftPath(Path);

			return SafeLoad<T>(Context, SoftPath, Log);
		}

	#pragma endregion Load

		static bool SafeMarkAsGarbage(const FString& Context, UObject* Object, LogLevel);

		static bool SafeMarkAsGarbage(UObject* Object);

	#undef LogLevel
	};
}

using CsObjectLibrary = NCsObject::FLibrary;