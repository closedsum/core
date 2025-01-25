// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Interface
#include "Library/CsGetLevelViewportCameraLibrary.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UUnrealEditorSubsystem;

namespace NCsViewport
{
	namespace NLevel
	{
		namespace NCamera
		{
			namespace NLibrary
			{
				class CSCORELIBRARYEDITOR_API FImpl : public ICsLevelViewportCameraLibrary
				{
				private:
					FImpl();

					FImpl(const FImpl&) = delete;
					FImpl(FImpl&&) = delete;
				public:
					~FImpl();

					FORCEINLINE static FImpl& Get()
					{
						static FImpl Instance;
						return Instance;
					}

					FORCEINLINE static FImpl* GetPtr() { return &Get(); }

				private:

					CS_DECLARE_STATIC_LOG_LEVEL

				public:
					
					UUnrealEditorSubsystem* GetSubsystemChecked(const FString& Context) const;

					UUnrealEditorSubsystem* GetSafeSubsystem(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_LEVEL) const;

					void GetInfoChecked(const FString& Context, FVector& OutLocation, FRotator& OutRotation) const;

					bool GetSafeInfo(const FString& Context, FVector& OutLocation, FRotator& OutRotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL) const;

					void SafeInfoChecked(const FString& Context, const FVector& Location, const FRotator& Rotation) const;

					bool SetSafeInfo(const FString& Context, const FVector& Location, const FRotator& Rotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL) const;
				};
			}
		}
	}
}