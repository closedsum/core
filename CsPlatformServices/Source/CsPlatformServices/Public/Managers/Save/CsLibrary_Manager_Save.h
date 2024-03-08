// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Save/CsTypes_Save.h"
// Log
#include "Utility/CsPlatformServicesLog.h"

class UObject;
class UCsManager_Save;

namespace NCsSave
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSPLATFORMSERVICES_API const FString GetSafe;
				}
			}
		}

		/**
		*/
		struct CSPLATFORMSERVICES_API FLibrary final
		{

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Save from a ContextObject.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Save.
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Save.
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Save from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Save.
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject)
			{
				return nullptr;
			}
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Save.
			*/
			static UCsManager_Save* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Get the reference to UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Save.
			*/
			template<typename T>
			FORCEINLINE static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsManager_Save* O = GetChecked(Context, ContextObject);
				T* Other		   = Cast<T>(O);

				checkf(Other, TEXT("%s: Manager_Save is NOT of type: %s."), *Context, *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Save.
			*/
			static UCsManager_Save* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Save.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				UCsManager_Save* O = GetChecked(Context, ContextObject);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					Log(FString::Printf(TEXT("%s: Manager_Save is NOT of type: %s."), *Context, *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Save.
			*/
			static UCsManager_Save* GetSafe(const UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Save from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				UCsManager_Save.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafe(const UObject* ContextObject)
			{
				using namespace NCsSave::NManager::NLibrary::NCached;

				const FString& Context = Str::GetSafe;

				return GetSafe<T>(Context, ContextObject, nullptr);
			}

		#pragma endregion Get

		// FileName
		#pragma region
		public:
			
			/**
			* Set the current save (slot).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Save			Save (slot) to set as the current save.
			*/
			static void SetCurrentSaveChecked(const FString& Context, const UObject* ContextObject, const ECsSave& Save);

			/**
			* Set the current save (slot).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Save			Save (slot) to set as the current save.
			* @param Log			(optional)
			* return
			*/
			static bool SetSafeCurrentSave(const FString& Context, const UObject* ContextObject, const ECsSave& Save, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SetSafeCurrentSave(const FString& Context, const UObject* ContextObject, const ECsSave& Save, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SetSafeCurrentSave(Context, ContextObject, Save, Log);
				return OutSuccess;
			}

		#pragma endregion FileName

		// Enumerate
		#pragma region
		public:

			/**
			* Get a list of all save filenames for specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			*/
			static void EnumerateChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get a list of all save filenames for specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			*/
			static bool SafeEnumerate(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeEnumerate(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeEnumerate(Context, ContextObject, Log);
				return OutSuccess;
			}

			#pragma endregion Enumerate

		// Read
		#pragma region
		public:

			/**
			* Read a save for a specified profile and Save (slot)
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to read save from.
			* @param Save			Save (slot) to read from.
			*/
			static void ReadChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

			/**
			* Safely read a save for a specified profile and Save (slot)
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to read save from.
			* @param Save			Save (slot) to read from.
			* @param Log			(optional)
			* return
			*/
			static bool SafeRead(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeRead(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeRead(Context, ContextObject, Profile, Save, Log);
				return OutSuccess;
			}

			/**
			* Read all saves for a specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to read all saves from.
			*/
			static void ReadAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile);

			/**
			* Safely read all saves for a specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to read all saves from.
			* @param Log			(optional)
			* return
			*/
			static bool SafeReadAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeReadAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeReadAll(Context, ContextObject, Profile, Log);
				return OutSuccess;
			}

		#pragma endregion Read

		// Write
		#pragma region
		public:

			/**
			* Write a save for a specified profile and Save (slot).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to write save to.
			* @param Save			Save (slot) to write to.
			*/
			static void WriteChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

			/**
			* Safely write a save for a specified profile and Save (slot). 
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to write save to.
			* @param Save			Save (slot) to write to.
			* @param Log			(optional)
			* return
			*/
			static bool SafeWrite(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeWrite(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeWrite(Context, ContextObject, Profile, Save, Log);
				return OutSuccess;
			}

			/**
			* Write all saves for a specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to write all saves to.
			*/
			static void WriteAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile);

			/**
			* Safely write all saves for a specified profile.
			* 
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Profile		Profile to write all saves to.
			* @param Log			(optional)
			* return
			*/
			static bool SafeWriteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeWriteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeWriteAll(Context, ContextObject, Profile, Log);
				return OutSuccess;
			}

		#pragma endregion Write

		// Delete
		#pragma region
		public:

			/**
			* Delete a save for a specified profile and Save (slot).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Profile		Profile to delete save from.
			* @param Save			Save (slot) to delete.
			*/
			static void DeleteChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save);

			/**
			* Safely delete a save for a specified profile and Save (slot).
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Profile		Profile to delete save from.
			* @param Save			Save (slot) to delete.
			* @param Log			(optional)
			* return
			*/
			static bool SafeDelete(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeDelete(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeDelete(Context, ContextObject, Profile, Save, Log);
				return OutSuccess;
			}

			/**
			* Delete all saves for a specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Profile		Profile to delete all saves from.
			*/
			static void DeleteAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile);

			/**
			* Safely delete all saves for a specified profile.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Profile		Profile to delete all saves from.
			* @param Log			(optional)
			* return
			*/
			static bool SafeDeleteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeDeleteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeDeleteAll(Context, ContextObject, Profile, Log);
				return OutSuccess;
			}

			/**
			* Delete all saves for all profiles.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*/
			static void DeleteAllContentChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely delete all saves for all profiles.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return
			*/
			static bool SafeDeleteAllContent(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning);
			FORCEINLINE static bool SafeDeleteAllContent(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) = &NCsPlatformServices::FLog::Warning)
			{
				OutSuccess = SafeDeleteAllContent(Context, ContextObject, Log);
				return OutSuccess;
			}

		#pragma endregion Delete
		};
	}
} 