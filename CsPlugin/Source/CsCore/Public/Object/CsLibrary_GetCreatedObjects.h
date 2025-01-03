// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
#include "CsMacro_Namespace.h"
// Log
#include "Utility/CsLog.h"

class UObject;
class ICsGetCreatedObjects;

// NCsObject::NCreate::FCreated
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsObject, NCreate, FCreated)

namespace NCsObject
{
	namespace NCreate
	{
		struct CSCORE_API FLibrary
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

			using CreatedObjectsType = NCsObject::NCreate::FCreated;

		// Get
		#pragma region
		public:

			/**
			* Get the interface: ICsGetCreatedObjects from Object.
			* 
			* @param Context	The calling context.
			* @param Object
			* return			Interface of type: ICsGetCreatedObjects.
			*/
			static ICsGetCreatedObjects* GetChecked(const FString& Context, UObject* Object);
			
			/**
			* Get the interface: ICsGetCreatedObjects from GEngine (Usually UUnrealEdEngine).
			* 
			* @param Context	The calling context.
			* return			Interface of type: ICsGetCreatedObjects
			*/
			static ICsGetCreatedObjects* GetChecked(const FString& Context);

		#pragma endregion Get

		// Implements
		#pragma region
		public:

			static bool ImplementsChecked(const FString& Context, const UObject* Object);

			static bool SafeImplements(const FString& Context, const UObject* Object, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Implements

		public:

			/**
			* Get Created Objects from GEngine (usually UUnrealEdEngine).
			*  NOTE: GEngine must implement the interface: ICsGetCreatedObjects.
			* 
			* @param Context	The calling context.
			* return			Created Objects.
			*/
			static CreatedObjectsType* GetCreatedObjectsChecked(const FString& Context);

			static void AddChecked(const FString& Context, UObject* Object, UObject* Owner);

			static void DestroyAndRemoveNullPendingKillOrOrphanedChecked(const FString& Context);
		};
	}
}

using CsCreateObjectLibrary = NCsObject::NCreate::FLibrary;