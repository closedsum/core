// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Level/Types/CsTypes_Level_Streaming.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Level_Streaming)

// FCsLevel_Streaming_LoadParams
#pragma region

bool FCsLevel_Streaming_LoadParams::IsValidChecked(const FString& Context) const 
{
	CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
	return true;
}

bool FCsLevel_Streaming_LoadParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
	return true;
}

bool FCsLevel_Streaming_LoadWithPathParams::IsValidChecked(const FString& Context) const 
{
	CS_IS_STRING_EMPTY_CHECKED(Level)
	return true;
}

bool FCsLevel_Streaming_LoadWithPathParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_STRING_EMPTY(Level)
	return true;
}

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLoad
		{
			bool FParams::IsValidChecked(const FString& Context) const 
			{
				CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
				return true;
			}
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
				bool FParams::IsValidChecked(const FString& Context) const 
				{
					CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
					return true;
				}
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
				bool FParams::IsValidChecked(const FString& Context) const 
				{
					CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsLevel_Streaming_LoadParams

// FCsLevel_Streaming_UnloadParams
#pragma region

bool FCsLevel_Streaming_UnloadParams::IsValidChecked(const FString& Context) const 
{
	CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
	return true;
}

bool FCsLevel_Streaming_UnloadParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
	return true;
}

bool FCsLevel_Streaming_UnloadWithPathParams::IsValidChecked(const FString& Context) const 
{
	CS_IS_STRING_EMPTY_CHECKED(Level)
	return true;
}

bool FCsLevel_Streaming_UnloadWithPathParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_STRING_EMPTY(Level)
	return true;
}

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NUnload
		{
			bool FParams::IsValidChecked(const FString& Context) const 
			{
				CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
			{
				CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
				return true;
			}
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
				bool FParams::IsValidChecked(const FString& Context) const 
				{
					CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
					return true;
				}
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
				bool FParams::IsValidChecked(const FString& Context) const 
				{
					CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
				{
					CS_IS_SOFT_OBJECT_PTR_VALID(Level, UWorld)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsLevel_Streaming_UnloadParams