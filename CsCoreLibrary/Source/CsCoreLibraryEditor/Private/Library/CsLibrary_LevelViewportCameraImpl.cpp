// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_LevelViewportCameraImpl.h"

// Types
#include "CsMacro_Misc.h"
// Editor
#include "Subsystems/UnrealEditorSubsystem.h"
#include "Editor.h"

namespace NCsViewport
{
	namespace NLevel
	{
		namespace NCamera
		{
			namespace NLibrary
			{
				using LogClassType = NCsCore::NLibrary::FLog;

				CS_DEFINE_STATIC_LOG_LEVEL(FImpl, LogClassType::Warning);

				FImpl::FImpl(){}
				FImpl::~FImpl(){}

				UUnrealEditorSubsystem* FImpl::GetSubsystemChecked(const FString& Context) const
				{
					UUnrealEditorSubsystem* UnrealEditorSubsystem = GEditor->GetEditorSubsystem<UUnrealEditorSubsystem>();

					checkf(UnrealEditorSubsystem, TEXT("%s: Failed to get Editor Subsystem: UUnrealEditorSubsystem from Editor."), *Context);
					return UnrealEditorSubsystem;
				}

				UUnrealEditorSubsystem* FImpl::GetSafeSubsystem(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT) const
				{
					if (UUnrealEditorSubsystem* UnrealEditorSubsystem = GEditor->GetEditorSubsystem<UUnrealEditorSubsystem>())
						return UnrealEditorSubsystem;

					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Editor Subsystem: UUnrealEditorSubsystem from Editor."), *Context))
					return nullptr;			
				}

				void FImpl::GetInfoChecked(const FString& Context, FVector& OutLocation, FRotator& OutRotation) const
				{
					const bool Result = GetSubsystemChecked(Context)->GetLevelViewportCameraInfo(OutLocation, OutRotation);
					checkf(Result, TEXT("%s: Failed to get ANY Perspective Level Viewport."), *Context);
				}

				bool FImpl::GetSafeInfo(const FString& Context, FVector& OutLocation, FRotator& OutRotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT) const
				{
					if (UUnrealEditorSubsystem* UnrealEditorSubsystem = GetSafeSubsystem(Context, Log))
					{
						const bool Result = UnrealEditorSubsystem->GetLevelViewportCameraInfo(OutLocation, OutRotation);

						if (!Result)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get ANY Perspective Level Viewport."), *Context))
							return false;
						}
					}
					return false;
				}

				void FImpl::SafeInfoChecked(const FString& Context, const FVector& Location, const FRotator& Rotation) const
				{
					GetSubsystemChecked(Context)->SetLevelViewportCameraInfo(Location, Rotation);
				}

				bool FImpl::SetSafeInfo(const FString& Context, const FVector& Location, const FRotator& Rotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT) const
				{
					if (UUnrealEditorSubsystem* UnrealEditorSubsystem = GetSafeSubsystem(Context, Log))
					{
						UnrealEditorSubsystem->SetLevelViewportCameraInfo(Location, Rotation);
						return true;
					}
					return false;
				}
			}
		}
	}
}