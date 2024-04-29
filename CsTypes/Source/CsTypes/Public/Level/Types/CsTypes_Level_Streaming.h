// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsTypesLog.h"

#include "CsTypes_Level_Streaming.generated.h"

// FCsLevel_Streaming_LoadParams
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsLevel_Streaming_LoadParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	TSoftObjectPtr<UWorld> Level;

	/** Whether the level should be visible if it is loaded	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	bool bMakeVisibleAfterLoad;

	/** Whether we want to force a blocking load */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	bool bShouldBlock;

	FCsLevel_Streaming_LoadParams() :
		Level(nullptr),
		bMakeVisibleAfterLoad(true),
		bShouldBlock(false)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsLevel_Streaming_LoadWithPathParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	FString Level;

	/** Whether the level should be visible if it is loaded	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	bool bMakeVisibleAfterLoad;

	/** Whether we want to force a blocking load */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	bool bShouldBlock;

	FCsLevel_Streaming_LoadWithPathParams() :
		Level(),
		bMakeVisibleAfterLoad(true),
		bShouldBlock(false)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLoad
		{
			struct CSTYPES_API FParams
			{
				TSoftObjectPtr<UWorld> Level;

				/** Whether the level should be visible if it is loaded	*/
				bool bMakeVisibleAfterLoad;

				/** Whether we want to force a blocking load */
				bool bShouldBlock;

				FParams() : 
					Level(nullptr),
					bMakeVisibleAfterLoad(true),
					bShouldBlock(false)
				{
				}

				static FParams Make(const FCsLevel_Streaming_LoadParams& Params)
				{
					FParams P;
					P.Level					= Params.Level;
					P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
					P.bShouldBlock			= Params.bShouldBlock;
					return P;
				}

				static FParams Make(const FCsLevel_Streaming_LoadWithPathParams& Params)
				{
					FParams P;
					P.Level					= TSoftObjectPtr<UWorld>(FSoftObjectPath(Params.Level));
					P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
					P.bShouldBlock			= Params.bShouldBlock;
					return P;
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
			};
		}
	}
}

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLocal
		{
			namespace NLoad
			{
				struct CSTYPES_API FParams
				{
					TSoftObjectPtr<UWorld> Level;

					/** Whether the level should be visible if it is loaded	*/
					bool bMakeVisibleAfterLoad;

					/** Whether we want to force a blocking load */
					bool bShouldBlock;

					FParams() : 
						Level(nullptr),
						bMakeVisibleAfterLoad(true),
						bShouldBlock(false)
					{
					}

					static FParams Make(const FCsLevel_Streaming_LoadParams& Params)
					{
						FParams P;
						P.Level					= Params.Level;
						P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
						P.bShouldBlock			= Params.bShouldBlock;
						return P;
					}

					static FParams Make(const FCsLevel_Streaming_LoadWithPathParams& Params)
					{
						FParams P;
						P.Level					= TSoftObjectPtr<UWorld>(FSoftObjectPath(Params.Level));
						P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
						P.bShouldBlock			= Params.bShouldBlock;
						return P;
					}

				#define LoadParamsType NCsLevel::NStreaming::NLoad::FParams

					static FParams Make(const LoadParamsType& Params)
					{
						FParams P;
						P.Level					= Params.Level;
						P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
						P.bShouldBlock			= Params.bShouldBlock;
						return P;
					}

				#undef LoadParamsType

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
				};
			}
		}
	}
}

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NDynamic
		{
			namespace NLoad
			{
				struct CSTYPES_API FParams
				{
					TSoftObjectPtr<UWorld> Level;

					/** Whether the level should be visible if it is loaded	*/
					bool bMakeVisibleAfterLoad;

					/** Whether we want to force a blocking load */
					bool bShouldBlock;

					FParams() : 
						Level(nullptr),
						bMakeVisibleAfterLoad(true),
						bShouldBlock(false)
					{
					}

					static FParams Make(const FCsLevel_Streaming_LoadParams& Params)
					{
						FParams P;
						P.Level					= Params.Level;
						P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
						P.bShouldBlock			= Params.bShouldBlock;
						return P;
					}

					static FParams Make(const FCsLevel_Streaming_LoadWithPathParams& Params)
					{
						FParams P;
						P.Level					= TSoftObjectPtr<UWorld>(FSoftObjectPath(Params.Level));
						P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
						P.bShouldBlock			= Params.bShouldBlock;
						return P;
					}

				#define LoadParamsType NCsLevel::NStreaming::NLoad::FParams

					static FParams Make(const LoadParamsType& Params)
					{
						FParams P;
						P.Level					= Params.Level;
						P.bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
						P.bShouldBlock			= Params.bShouldBlock;
						return P;
					}

				#undef LoadParamsType

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
				};
			}
		}
	}
}

#pragma endregion FCsLevel_Streaming_LoadParams

// FCsLevel_Streaming_UnloadParams
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsLevel_Streaming_UnloadParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	TSoftObjectPtr<UWorld> Level;

	/** Whether we want to force a blocking unload */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	bool bShouldBlock;

	FCsLevel_Streaming_UnloadParams() :
		Level(nullptr),
		bShouldBlock(false)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsLevel_Streaming_UnloadWithPathParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	FString Level;

	/** Whether we want to force a blocking unload */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Level")
	bool bShouldBlock;

	FCsLevel_Streaming_UnloadWithPathParams() :
		Level(),
		bShouldBlock(false)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
};

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NUnload
		{
			struct CSTYPES_API FParams
			{
				TSoftObjectPtr<UWorld> Level;

				/** Whether we want to force a blocking unload */
				bool bShouldBlock;

				FParams() : 
					Level(nullptr),
					bShouldBlock(false)
				{
				}

				static FParams Make(const FCsLevel_Streaming_UnloadParams& Params)
				{
					FParams P;
					P.Level			= Params.Level;
					P.bShouldBlock	= Params.bShouldBlock;
					return P;
				}

				static FParams Make(const FCsLevel_Streaming_UnloadWithPathParams& Params)
				{
					FParams P;
					P.Level			= TSoftObjectPtr<UWorld>(FSoftObjectPath(Params.Level));
					P.bShouldBlock	= Params.bShouldBlock;
					return P;
				}

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
			};
		}
	}
}

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLocal
		{
			namespace NUnload
			{
				struct CSTYPES_API FParams
				{
					TSoftObjectPtr<UWorld> Level;

					/** Whether we want to force a blocking unload */
					bool bShouldBlock;

					FParams() : 
						Level(nullptr),
						bShouldBlock(false)
					{
					}

					static FParams Make(const FCsLevel_Streaming_UnloadParams& Params)
					{
						FParams P;
						P.Level			= Params.Level;
						P.bShouldBlock	= Params.bShouldBlock;
						return P;
					}

					static FParams Make(const FCsLevel_Streaming_UnloadWithPathParams& Params)
					{
						FParams P;
						P.Level			= TSoftObjectPtr<UWorld>(FSoftObjectPath(Params.Level));
						P.bShouldBlock	= Params.bShouldBlock;
						return P;
					}

				#define UnloadParamsType NCsLevel::NStreaming::NUnload::FParams
					
					static FParams Make(const UnloadParamsType& Params)
					{
						FParams P;
						P.Level			= Params.Level;
						P.bShouldBlock	= Params.bShouldBlock;
						return P;
					}

				#undef UnloadParamsType

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
				};
			}
		}
	}
}

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NDynamic
		{
			namespace NUnload
			{
				struct CSTYPES_API FParams
				{
					TSoftObjectPtr<UWorld> Level;

					/** Whether we want to force a blocking unload */
					bool bShouldBlock;

					FParams() : 
						Level(nullptr),
						bShouldBlock(false)
					{
					}

					static FParams Make(const FCsLevel_Streaming_UnloadParams& Params)
					{
						FParams P;
						P.Level			= Params.Level;
						P.bShouldBlock	= Params.bShouldBlock;
						return P;
					}

					static FParams Make(const FCsLevel_Streaming_UnloadWithPathParams& Params)
					{
						FParams P;
						P.Level			= TSoftObjectPtr<UWorld>(FSoftObjectPath(Params.Level));
						P.bShouldBlock	= Params.bShouldBlock;
						return P;
					}

				#define UnloadParamsType NCsLevel::NStreaming::NUnload::FParams
					
					static FParams Make(const UnloadParamsType& Params)
					{
						FParams P;
						P.Level			= Params.Level;
						P.bShouldBlock	= Params.bShouldBlock;
						return P;
					}

				#undef UnloadParamsType

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsTypes::FLog::Warning) const;
				};
			}
		}
	}
}

#pragma endregion FCsLevel_Streaming_UnloadParams