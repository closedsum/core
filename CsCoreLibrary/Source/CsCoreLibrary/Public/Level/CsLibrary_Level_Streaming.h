// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Level/Types/CsTypes_Level_Streaming.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UWorld;
class ULevelStreaming;
class ALevelScriptActor;

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLocal
		{
			struct CSCORELIBRARY_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

			// Is
			#pragma region
			public:

				static bool SafeIs(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UWorld>& Level, LogLevel);

			#pragma endregion Is

			public:

				static FName GetNameChecked(const FString& Context, const TSoftObjectPtr<UWorld>& Level);

				static FName GetSafeName(const FString& Context, const TSoftObjectPtr<UWorld>& Level, bool& OutSuccess, LogLevel);
				FORCEINLINE static FName GetSafeName(const FString& Context, const TSoftObjectPtr<UWorld>& Level, LogLevel)
				{
					bool OutSuccess = false;
					return GetSafeName(Context, Level, OutSuccess, Log);
				}

				static FString MakeSafeLevelNameChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName);

				static FString SafeMakeSafeLevelName(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, LogLevel);
				FORCEINLINE static FString SafeMakeSafeLevelName(const FString& Context, const UObject* WorldContext, const FName& LevelName, LogLevel)
				{
					bool OutSuccess = false;
					return SafeMakeSafeLevelName(Context, WorldContext, LevelName, OutSuccess, Log);
				}

				static FString GetSearchPackageNameChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName);

				static FString GetSafeSearchPackageName(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, LogLevel);
				FORCEINLINE static FString GetSafeSearchPackageName(const FString& Context, const UObject* WorldContext, const FName& LevelName, LogLevel)
				{
					bool OutSuccess = false;
					return GetSafeSearchPackageName(Context, WorldContext, LevelName, OutSuccess, Log);
				}

				static ULevelStreaming* FindAndCacheObjectChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName);

				static ULevelStreaming* SafeFindAndCacheObject(const FString& Context, const UObject* WorldContext, const FName& LevelName, LogLevel);
				FORCEINLINE static ULevelStreaming* SafeFindAndCacheObject(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, LogLevel)
				{
					ULevelStreaming* Level = SafeFindAndCacheObject(Context, WorldContext, LevelName, Log);
					OutSuccess			   = Level != nullptr;
					return Level;
				}

			// Load
			#pragma region
			public:

			#define LoadParamsType NCsLevel::NStreaming::NLocal::NLoad::FParams

				static void LoadChecked(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params);
				FORCEINLINE static void LoadChecked(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}
				FORCEINLINE static void LoadChecked(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}
				FORCEINLINE static void LoadChecked(const FString& Context, const UObject* WorldContext, const NCsLevel::NStreaming::NLoad::FParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}

				static bool SafeLoad(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params, LogLevel);
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params, bool& OutSuccess, LogLevel)
				{
					OutSuccess = SafeLoad(Context, WorldContext, Params, Log);
					return OutSuccess;
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params, bool& OutSuccess, LogLevel)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params, LogLevel)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), Log);
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params, bool& OutSuccess, LogLevel)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params, LogLevel)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), Log);
				}

			#undef LoadParamsType

			#pragma endregion Load

			// Unload
			#pragma region
			public:

			#define UnloadParamsType NCsLevel::NStreaming::NLocal::NUnload::FParams

				static void UnloadChecked(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params);
				FORCEINLINE static void UnloadChecked(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}
				FORCEINLINE static void UnloadChecked(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}
				FORCEINLINE static void UnloadChecked(const FString& Context, const UObject* WorldContext, const NCsLevel::NStreaming::NUnload::FParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}

				static bool SafeUnload(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params, LogLevel);
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params, bool& OutSuccess, LogLevel)
				{
					OutSuccess = SafeUnload(Context, WorldContext, Params, Log);
					return OutSuccess;
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params, bool& OutSuccess, LogLevel)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params, LogLevel)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), Log);
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params, bool& OutSuccess, LogLevel)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params, LogLevel)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), Log);
				}

			#undef UnloadParamsType

			#pragma endregion Unload

			#undef LogLevel
			};
		}	
	}

	namespace NStreaming
	{
		namespace NDynamic
		{
			struct CSCORELIBRARY_API FLibrary final
			{
			#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

			private:
				
				typedef NCsLevel::NStreaming::NLocal::FLibrary LocalLibrary;

			// Is
			#pragma region
			public:

				FORCEINLINE static bool SafeIs(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UWorld>& Level, LogLevel)
				{
					return !LocalLibrary::SafeIs(Context, WorldContext, Level, Log);
				}

			#pragma endregion Is

			// Load
			#pragma region
			public:

			#define LoadParamsType NCsLevel::NStreaming::NDynamic::NLoad::FParams

				static void LoadChecked(const FString& Context, UObject* WorldContext, const LoadParamsType& Params);
				FORCEINLINE static void LoadChecked(const FString& Context, UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}
				FORCEINLINE static void LoadChecked(const FString& Context, UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}
				FORCEINLINE static void LoadChecked(const FString& Context, UObject* WorldContext, const NCsLevel::NStreaming::NLoad::FParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}

			#undef LoadParamsType

			#pragma endregion Load

			// Unload
			#pragma region
			public:

			#define UnloadParamsType NCsLevel::NStreaming::NDynamic::NUnload::FParams

				static void UnloadChecked(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params);
				FORCEINLINE static void UnloadChecked(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}
				FORCEINLINE static void UnloadChecked(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}
				FORCEINLINE static void UnloadChecked(const FString& Context, const UObject* WorldContext, const NCsLevel::NStreaming::NUnload::FParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}

			#undef UnloadParamsType

			#pragma endregion Unload

			#undef LogLevel
			};
		}
	}

	namespace NStreaming
	{
		struct CSCORELIBRARY_API FLibrary final
		{
		private:

			typedef NCsLevel::NStreaming::NLocal::FLibrary LocalLibrary;
			typedef NCsLevel::NStreaming::NDynamic::FLibrary DynamicLibrary;

			// Load
			#pragma region
			public:

			#define LoadParamsType NCsLevel::NStreaming::NLoad::FParams

				FORCEINLINE static void LoadChecked(const FString& Context, UObject* WorldContext, const LoadParamsType& Params)
				{
					if (LocalLibrary::SafeIs(Context, WorldContext, Params.Level, nullptr))
						LocalLibrary::LoadChecked(Context, WorldContext, Params);
					else
						DynamicLibrary::LoadChecked(Context, WorldContext, Params);
				}
				FORCEINLINE static void LoadChecked(const FString& Context, UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}
				FORCEINLINE static void LoadChecked(const FString& Context, UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params)
				{
					LoadChecked(Context, WorldContext, LoadParamsType::Make(Params));
				}

			#undef LoadParamsType

			#pragma endregion Load

			// Unload
			#pragma region
			public:

			#define UnloadParamsType NCsLevel::NStreaming::NUnload::FParams

				FORCEINLINE static void UnloadChecked(const FString& Context, UObject* WorldContext, const UnloadParamsType& Params)
				{
					LocalLibrary::UnloadChecked(Context, WorldContext, Params);
				}
				FORCEINLINE static void UnloadChecked(const FString& Context, UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}
				FORCEINLINE static void UnloadChecked(const FString& Context, UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params)
				{
					UnloadChecked(Context, WorldContext, UnloadParamsType::Make(Params));
				}

			#undef UnloadParamsType

			#pragma endregion Unload

			// LevelScriptActor
			#pragma region
			public:

			static ALevelScriptActor* GetLevelScriptActorChecked(const FString& Context, ULevelStreaming* LevelStreaming);

			#pragma endregion LevelScriptActor

			public:

				static const FName& GetPackageNameToLoadChecked(const FString& Context, ULevelStreaming* LevelStreaming);

				static const TArray<AActor*>& GetActorsChecked(const FString& Context, ULevelStreaming* LevelStreaming);
		};
	}
}

using CsLevelStreamingLibrary = NCsLevel::NStreaming::FLibrary;
using CsLocalLevelStreamingLibrary = NCsLevel::NStreaming::NLocal::FLibrary;
using CsLevelDyanmicStreamingLibrary = NCsLevel::NStreaming::NDynamic::FLibrary;