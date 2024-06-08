// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Level/CsLibrary_LevelImpl.h"

// Library
#include "Level/CsLibrary_Level.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Level/Data/Setup/CsData_Level_Setup.h"
// Level
#include "Engine/Level.h"
#include "Engine/LevelScriptActor.h"
#include "Level/Data/Setup/CsGetLevelSetupData.h"
#include "Level/CsGetLevelPayload.h"

namespace NCsLevel
{
	namespace NPersistent
	{
		namespace NImpl
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						// SetupData
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::NImpl::FLibrary, GetSafeSetupDataAsObject);
					}
				}
			}

			#define USING_NS_CACHED using namespace NCsLevel::NPersistent::NImpl::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsLevel::NPersistent::NImpl::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName
			#define LogLevel void(*Log)(const FString& Context) /*=&FCsLog::Warning*/
			#define LevelLibrary NCsLevel::NPersistent::FLibrary

			// SetupData
			#pragma region

			UObject* FLibrary::GetSetupDataAsObjectChecked(const FString& Context, const UObject* WorldContext)
			{
				ICsGetLevelSetupData* GetLevelSetupData = LevelLibrary::GetScriptActorChecked<ICsGetLevelSetupData>(Context, WorldContext);
				ICsData_Level_Setup* SetupData			= GetLevelSetupData->GetLevelSetupData();

				CS_IS_PTR_NULL_CHECKED(SetupData)

				UObject* O = CS_INTERFACE_GET_UOBJECT_CHECKED(SetupData, ICsData_Level_Setup);
				return O;
			}

			UObject* FLibrary::GetSafeSetupDataAsObject(const FString& Context, const UObject* WorldContext, LogLevel)
			{
				if (ICsGetLevelSetupData* GetLevelSetupData = LevelLibrary::GetSafeScriptActor<ICsGetLevelSetupData>(Context, WorldContext, Log))
				{
					ICsData_Level_Setup* SetupData = GetLevelSetupData->GetLevelSetupData();

					CS_IS_PTR_NULL_RET_NULL(SetupData)

					UObject* O = CS_INTERFACE_GET_UOBJECT(SetupData, ICsData_Level_Setup);
					return O;
				}
				return nullptr;
			}

			UObject* FLibrary::GetSafeSetupDataAsObject(const UObject* WorldContext)
			{
				SET_CONTEXT(GetSafeSetupDataAsObject);

				return GetSafeSetupDataAsObject(Context, WorldContext, nullptr);
			}

			#pragma endregion SetupData

			// ICsGetLevelPayload
			#pragma region

			void FLibrary::GetPayloadAndLevelNameChecked(const FString& Context, const UObject* WorldContext, FCsPayload*& OutPayload, FName& OutLevelName)
			{
				OutPayload	  = nullptr;
				OutLevelName  = NAME_None;

				ICsGetLevelPayload* GetLevelPayload = GetSetupDataChecked<ICsGetLevelPayload>(Context, WorldContext);
				const FCsPayload& Payload			= GetLevelPayload->GetLevelPayload();
				OutPayload							= const_cast<FCsPayload*>(&Payload);
				OutLevelName						= LevelLibrary::GetFNameChecked(Context, WorldContext);
			}

			bool FLibrary::GetSafePayloadAndLevelName(const FString& Context, const UObject* WorldContext, FCsPayload*& OutPayload, FName& OutLevelName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				OutPayload	  = nullptr;
				OutLevelName  = NAME_None;

				ICsGetLevelPayload* GetLevelPayload = GetSafeSetupData<ICsGetLevelPayload>(Context, WorldContext, Log);

				if (!GetLevelPayload)
					return false;

				const FCsPayload& Payload = GetLevelPayload->GetLevelPayload();
				OutPayload				  = const_cast<FCsPayload*>(&Payload);
				OutLevelName			  = LevelLibrary::GetSafeFName(Context, WorldContext, Log);

				if (OutLevelName == NAME_None)
					return false;
				return true;
			}

			#pragma endregion ICsGetLevelPayload

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
			#undef LogLevel
			#undef LevelLibrary
		}
	}
}