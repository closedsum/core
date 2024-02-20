// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Level/Types/CsTypes_Level_Streaming.h"

class UObject;
class UWorld;
class ULevelStreaming;

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLocal
		{
			struct CSCORE_API FLibrary final
			{
			// Is
			#pragma region
			public:

				static bool SafeIs(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UWorld>& Level, void(*Log)(const FString&) = &FCsLog::Warning);

			#pragma endregion Is

			public:

				static FName GetNameChecked(const FString& Context, const TSoftObjectPtr<UWorld>& Level);

				static FName GetSafeName(const FString& Context, const TSoftObjectPtr<UWorld>& Level, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
				FORCEINLINE static FName GetSafeName(const FString& Context, const TSoftObjectPtr<UWorld>& Level, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					bool OutSuccess = false;
					return GetSafeName(Context, Level, OutSuccess, Log);
				}

				static FString MakeSafeLevelNameChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName);

				static FString SafeMakeSafeLevelName(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
				FORCEINLINE static FString SafeMakeSafeLevelName(const FString& Context, const UObject* WorldContext, const FName& LevelName, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					bool OutSuccess = false;
					return SafeMakeSafeLevelName(Context, WorldContext, LevelName, OutSuccess, Log);
				}

				static FString GetSearchPackageNameChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName);

				static FString GetSafeSearchPackageName(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);
				FORCEINLINE static FString GetSafeSearchPackageName(const FString& Context, const UObject* WorldContext, const FName& LevelName, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					bool OutSuccess = false;
					return GetSafeSearchPackageName(Context, WorldContext, LevelName, OutSuccess, Log);
				}

				static ULevelStreaming* FindAndCacheObjectChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName);

				static ULevelStreaming* SafeFindAndCacheObject(const FString& Context, const UObject* WorldContext, const FName& LevelName, void(*Log)(const FString&) = &FCsLog::Warning);
				FORCEINLINE static ULevelStreaming* SafeFindAndCacheObject(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
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

				static bool SafeLoad(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params, void(*Log)(const FString&) = &FCsLog::Warning);
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					OutSuccess = SafeLoad(Context, WorldContext, Params, Log);
					return OutSuccess;
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadParams& Params, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), Log);
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeLoad(Context, WorldContext, LoadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeLoad(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_LoadWithPathParams& Params, void(*Log)(const FString&) = &FCsLog::Warning)
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

				static bool SafeUnload(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params, void(*Log)(const FString&) = &FCsLog::Warning);
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					OutSuccess = SafeUnload(Context, WorldContext, Params, Log);
					return OutSuccess;
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadParams& Params, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), Log);
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), OutSuccess, Log);
				}
				FORCEINLINE static bool SafeUnload(const FString& Context, const UObject* WorldContext, const FCsLevel_Streaming_UnloadWithPathParams& Params, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return SafeUnload(Context, WorldContext, UnloadParamsType::Make(Params), Log);
				}

			#undef UnloadParamsType

			#pragma endregion Unload
			};
		}	
	}

	namespace NStreaming
	{
		namespace NDynamic
		{
			struct CSCORE_API FLibrary final
			{
			// Is
			#pragma region
			public:

				FORCEINLINE static bool SafeIs(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UWorld>& Level, void(*Log)(const FString&) = &FCsLog::Warning)
				{
					return !NCsLevel::NStreaming::NLocal::FLibrary::SafeIs(Context, WorldContext, Level, Log);
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
			};
		}
	}

	namespace NStreaming
	{
		struct CSCORE_API FLibrary final
		{
			#define LocalLibrary NCsLevel::NStreaming::NLocal::FLibrary
			#define DynamicLibrary NCsLevel::NStreaming::NDynamic::FLibrary

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

			#undef LocalLibrary
			#undef DynamicLibrary
		};
	}
}