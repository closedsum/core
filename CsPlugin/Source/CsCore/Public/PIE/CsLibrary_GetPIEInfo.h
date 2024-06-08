// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "PIE/CsGetPIEInfo.h"
// Log
#include "Utility/CsLog.h"

class UObject;

namespace NCsPIE
{
	namespace NGetInfo
	{
		struct CSCORE_API FLibrary
		{
		// Get
		#pragma region
		public:

			/**
			* Get the interface: ICsGetPIEInfo from Object.
			* 
			* @param Context	The calling context.
			* @param Object
			* return			Interface of type: ICsGetPIEInfo.
			*/
			static const ICsGetPIEInfo* GetChecked(const FString& Context, const UObject* Object);
			
			/**
			* Get the interface: ICsGetPIEInfo from GEngine (Usually UUnrealEdEngine).
			* 
			* @param Context	The calling context.
			* return			Interface of type: ICsGetPIEInfo
			*/
			static const ICsGetPIEInfo* GetChecked(const FString& Context);

		#pragma endregion Get

		// Implements
		#pragma region
		public:

			static bool ImplementsChecked(const FString& Context, const UObject* Object);

			static bool SafeImplements(const FString& Context, const UObject* Object, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion Implements

		public:

		#define InfoType NCsPIE::FInfo

			/**
			* Get PIE Info from GEngine (usually UUnrealEdEngine).
			*  NOTE: GEngine must implement the interface: ICsGetPIEInfo.
			* 
			* @param Context	The calling context.
			* return			Info.
			*/
			static const InfoType& GetInfoChecked(const FString& Context);

			FORCEINLINE static bool IsNoneChecked(const FString& Context)
			{
				return GetInfoChecked(Context).IsNone();
			}

		#undef InfoType
		};
	}
}