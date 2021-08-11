// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"
#pragma once

class UObject;

namespace NCsObject
{
	/**
	*/
	class CSCORE_API FLibrary final
	{
	public:

		static FString PrintObjectAndClass(UObject* Object);

		/**
		*
		*
		* @param Object
		* return
		*/
		static FString GetFlagsAsString(UObject* Object);

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

			checkf(Other, TEXT("%s: Object: %s with Class: %s @ %s is NOT of type: %s."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()), *(Path.ToString()), *(T::StaticClass()->GetName()));

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
		static UObject* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely load a Object of type: T at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to type: T to load.
		* @param Log
		* return			Object of type: T.
		*/
		template<typename T>
		static T* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			UObject* Object = SafeLoad(Context, Path, Log);

			if (!Object)
				return nullptr;

			T* Other = Cast<T>(Object);

			if (!Other)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Object: %s with Class: %s @ %s is NOT of type: %s."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()), *(Path.ToString()), *(T::StaticClass()->GetName())));
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

			checkf(Other, TEXT("%s: Object: %s with Class: %s @ %s is NOT of type: %s."), *Context, *(Object->GetName()), *(Object->GetClass()->GetName()), *Path, *(T::StaticClass()->GetName()));

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
		static UObject* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Safely load a Object of type: T at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to type: T to load.
		* @param Log
		* return			Object of type: T.
		*/
		template<typename T>
		static T* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			if (Path.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path is EMPTY."), *Context));
				return nullptr;
			}

			FSoftObjectPath SoftPath(Path);

			return SafeLoad<T>(Context, SoftPath, Log);
		}

	#pragma endregion Load
	};
}