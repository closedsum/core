// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Log.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsViewport, NLevel, NCamera, ILibrary)

namespace NCsViewport
{
	namespace NLevel
	{
		namespace NCamera
		{
			class CSCORELIBRARY_API FLibrary final
			{
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

				using InterfaceLibrary = NCsViewport::NLevel::NCamera::ILibrary;

			private:

				static const InterfaceLibrary* GetInterfaceChecked(const FString& Context);

				static const InterfaceLibrary* GetSafeInterface(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			public:

				/**
				* Gets information about the camera position for the primary level editor viewport.  In non-editor builds, these will be zeroed
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context				The Calling Context.
				* @param OutLocation	(out)	Current location of the level editing viewport camera, or zero if none found
				* @param OutRotation	(out)	Current rotation of the level editing viewport camera, or zero if none found
				*/
				static void GetInfoChecked(const FString& Context, FVector& OutLocation, FRotator& OutRotation);

				/**
				* Safely gets information about the camera position for the primary level editor viewport.  In non-editor builds, these will be zeroed
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context				The Calling Context.
				* @param OutLocation	(out)	Current location of the level editing viewport camera, or zero if none found
				* @param OutRotation	(out)	Current rotation of the level editing viewport camera, or zero if none found
				* @return						Whether or not we were able to get a camera for a level editing viewport
				*/
				static bool GetSafeInfo(const FString& Context, FVector& OutLocation, FRotator& OutRotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

				/**
				* Sets information about the camera position for the primary level editor viewport.
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context	The Calling Context.
				* @param Location	Location the camera will be moved to.
				* @param Rotation	Rotation the camera will be set to.
				*/
				static void SafeInfoChecked(const FString& Context, const FVector& Location, const FRotator& Rotation);

				/**
				* Safely, Sets information about the camera position for the primary level editor viewport.
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context	The Calling Context.
				* @param Location	Location the camera will be moved to.
				* @param Rotation	Rotation the camera will be set to.
				* @return			Whether or not we were able to get a camera for a level editing viewport
				*/
				static bool SetSafeInfo(const FString& Context, const FVector& Location, const FRotator& Rotation, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			};
		}
	}
}

using CsLevelViewportCameraLibrary = NCsViewport::NLevel::NCamera::FLibrary;