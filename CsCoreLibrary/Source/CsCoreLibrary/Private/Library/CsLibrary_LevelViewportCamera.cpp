// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_LevelViewportCamera.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Library/CsGetLevelViewportCameraLibrary.h"
// Engine
#include "Engine/Engine.h"

namespace NCsViewport
{
	namespace NLevel
	{
		namespace NCamera
		{
			using LogClassType = NCsCore::NLibrary::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);
			
			using InterfaceLibrary = NCsViewport::NLevel::NCamera::ILibrary;

			const InterfaceLibrary* FLibrary::GetInterfaceChecked(const FString& Context)
			{
			#if !UE_BUILD_SHIPPING
				const InterfaceLibrary* Interface = CS_CONST_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetLevelViewportCameraLibrary)->GetViewportLevelCameraLibrary();

				CS_IS_PTR_NULL_CHECKED(Interface)
				return Interface;
			#else
				return CS_CONST_INTERFACE_CAST_CHECKED(GEngine, UEngine, ICsGetLevelViewportCameraLibrary)->GetViewportLevelCameraLibrary();
			#endif // !UE_BUILD_SHIPPING
			}

			const InterfaceLibrary* FLibrary::GetSafeInterface(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (ICsGetLevelViewportCameraLibrary* GetLevelViewportCameraLibrary = CS_INTERFACE_CAST(GEngine, UEngine, ICsGetLevelViewportCameraLibrary))
				{
					if (const InterfaceLibrary* Interface = GetLevelViewportCameraLibrary->GetViewportLevelCameraLibrary())
						return Interface;
					CS_CONDITIONAL_LOG(FString(TEXT("%s: ViewportLevelCameraLibrary is NULL.")))
				}
				return nullptr;
			}

			void FLibrary::GetInfoChecked(const FString& Context, FVector& OutLocation, FRotator& OutRotation)
			{
				GetInterfaceChecked(Context)->GetInfoChecked(Context, OutLocation, OutRotation);
			}

			bool FLibrary::GetSafeInfo(const FString& Context, FVector& OutLocation, FRotator& OutRotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (const InterfaceLibrary* Interface = GetSafeInterface(Context, Log))
					return Interface->GetSafeInfo(Context, OutLocation, OutRotation, Log);
				return false;
			}

			void FLibrary::SafeInfoChecked(const FString& Context, const FVector& Location, const FRotator& Rotation)
			{
				GetInterfaceChecked(Context)->SafeInfoChecked(Context, Location, Rotation);
			}

			bool FLibrary::SetSafeInfo(const FString& Context, const FVector& Location, const FRotator& Rotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)\
			{
				if (const InterfaceLibrary* Interface = GetSafeInterface(Context, Log))
					return Interface->SetSafeInfo(Context, Location, Rotation, Log);
				return false;
			}
		}
	}
}