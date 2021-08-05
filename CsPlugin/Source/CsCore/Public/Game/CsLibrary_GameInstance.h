// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

class UGameInstance;
class UObject;

namespace NCsGameInstance
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				extern CSCORE_API const FString GetSafe;
				extern CSCORE_API const FString GetSafeAsObject;
			}
		}
	}

	class CSCORE_API FLibrary final
	{
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

			checkf(Other, TEXT("%s: %s: with Class: %s is NOT of type: %s."), *Context, *(O->GetName()), *(O->GetClass()->GetName()), *(T::StaticClass()->GetName()));
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
		static UGameInstance* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

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
		static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning)
		{
			UGameInstance* O = GetSafe(Context, ContextObject, Log);

			if (!O)
				return nullptr;

			T* Other = Cast<T>(O);

			if (!Other)
			{
				if (Log)
					Log(FString::Printf(TEXT("%s: %s: with Class: %s is NOT of type: %s."), *Context, *(O->GetName()), *(O->GetClass()->GetName()), *(T::StaticClass()->GetName())));
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
		static UObject* GetSafeAsObject(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

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

	// Editor
	#pragma region
	public:

		/**
		* Check if the instance currently running is PIE.
		* NOTE: Assumes the GameInstance is of type: UCsGameInstance.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is PIE.
		*/
		static bool IsPIEChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Check if the instance currently running is Standalone from Editor.
		* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
		* 
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is Standalone from Editor.
		*/
		static bool IsStandaloneFromEditorChecked(const FString& Context, const UObject* ContextObject);

		/**
		* Check if the instance currently running is Standalone Mobile from Editor.
		* NOTE: Assumes the GameInstnace is of Type: UCsGameInstance.
		*
		* @param Context		The calling context.
		* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
		*						of
		*						A reference to the GameInstance.
		* return				Whether the instance running is Standalone Mobile from Editor.
		*/
		static bool IsStandaloneMobileFromEditorChecked(const FString& Context, const UObject* ContextObject);

	#pragma endregion Editor
	};
}