// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsDataLog.h"

class ULevel;
class UWorld;
class UObject;
class ALevelScriptActor;
struct FCsPayload;

namespace NCsLevel
{
	namespace NPersistent
	{
		namespace NData
		{
			struct CSDATA_API FLibrary final
			{
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

			// SetupData
			#pragma region
			public:

				/**
				* Get the Level Setup Data as a UObject from the current Persistent Level.
				*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
				* 
				* @param Context		The calling context.
				* @param WorldContext
				* return				UObject.
				*/
				static UObject* GetSetupDataAsObjectChecked(const FString& Context, const UObject* WorldContext);

				/**
				* Safely get the Level Setup Data as a UObject from the current Persistent Level.
				*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
				*
				* @param Context		The calling context.
				* @param WorldContext
				* @param Log			(optional)
				* return				UObject.
				*/
				static UObject* GetSafeSetupDataAsObject(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Safely get the Level Setup Data as a UObject from the current Persistent Level.
				*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
				*
				* @param WorldContext
				* return				UObject.
				*/
				static UObject* GetSafeSetupDataAsObject(const UObject* WorldContext);

				/**
				* Get the Level Setup Data of type: T from current Persistent Level.
				*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
				*
				* @param Context		The calling context.
				* @param WorldContext
				* return				Level Setup Data of type: T.
				*/
				template<typename T>
				FORCEINLINE static T* GetSetupDataChecked(const FString& Context, const UObject* WorldContext)
				{
					T* Slice = Cast<T>(GetSetupDataAsObjectChecked(Context, WorldContext));

					checkf(Slice, TEXT("%s: Failed to cast Level Setup Data to type: T."), *Context);

					return Slice;
				}

				/**
				* Safely get the Level Setup Data of type: T from current Persistent Level.
				*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
				*
				* @param Context		The calling context.
				* @param WorldContext
				* @param Log			(optional)
				* return				Level Setup Data of type: T.
				*/
				template<typename T>
				FORCEINLINE static T* GetSafeSetupData(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
				{
					T* Slice = Cast<T>(GetSafeSetupDataAsObject(Context, WorldContext, Log));

					if (!Slice)
					{
						if (Log)
						{
							Log(FString::Printf(TEXT("%s: Failed to cast Level Setup Data to type: T."), *Context));
						}
						return nullptr;
					}
					return Slice;
				}

				/**
				* Safely get the Level Setup Data of type: T from current Persistent Level.
				*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
				*
				* @param WorldContext
				* return				Level Setup Data of type: T.
				*/
				template<typename T>
				FORCEINLINE static T* GetSafeSetupData(const UObject* WorldContext)
				{
					return Cast<T>(GetSafeSetupDataAsObject(WorldContext));
				}

			#pragma endregion SetupData

			// ICsGetLevelPayload
			#pragma region
			public:

				static void GetPayloadAndLevelNameChecked(const FString& Context, const UObject* WorldContext, FCsPayload*& OutPayload, FName& OutLevelName);

				static bool GetSafePayloadAndLevelName(const FString& Context, const UObject* WorldContext, FCsPayload*& OutPayload, FName& OutLevelName, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			#pragma endregion ICsGetLevelPayload
			};
		}
	}
}

using CsLevelDataLibrary = NCsLevel::NPersistent::NData::FLibrary;