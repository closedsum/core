// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"

#include "CsGetLevelViewportCameraLibrary.generated.h"

UINTERFACE(BlueprintType)
class CSCORELIBRARY_API UCsGetLevelViewportCameraLibrary : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

namespace NCsViewport
{
	namespace NLevel
	{
		namespace NCamera
		{
			/**
			* Interface Library for handling any information with the Level Viewport Camera
			*  (camera associated with FLevelEditorViewportClient).
			*/
			struct CSCORELIBRARY_API ILibrary
			{
			public:

				virtual ~ILibrary(){};

				/**
				* Gets information about the camera position for the primary level editor viewport.  In non-editor builds, these will be zeroed
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context				The Calling Context.
				* @param OutLocation	(out)	Current location of the level editing viewport camera, or zero if none found
				* @param OutRotation	(out)	Current rotation of the level editing viewport camera, or zero if none found
				*/
				virtual void GetInfoChecked(const FString& Context, FVector& OutLocation, FRotator& OutRotation) const = 0;

				/**
				* Safely gets information about the camera position for the primary level editor viewport.  In non-editor builds, these will be zeroed
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context				The Calling Context.
				* @param OutLocation	(out)	Current location of the level editing viewport camera, or zero if none found
				* @param OutRotation	(out)	Current rotation of the level editing viewport camera, or zero if none found
				* @return						Whether or not we were able to get a camera for a level editing viewport
				*/
				virtual bool GetSafeInfo(const FString& Context, FVector& OutLocation, FRotator& OutRotation, void(*Log)(const FString&) = nullptr) const = 0;

				/**
				* Sets information about the camera position for the primary level editor viewport.
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context	The Calling Context.
				* @param Location	Location the camera will be moved to.
				* @param Rotation	Rotation the camera will be set to.
				*/
				virtual void SafeInfoChecked(const FString& Context, const FVector& Location, const FRotator& Rotation) const = 0;

				/**
				* Safely, Sets information about the camera position for the primary level editor viewport.
				* In the UnrealEd module instead of Level Editor as it uses FLevelEditorViewportClient which is in this module
				*
				* @param Context	The Calling Context.
				* @param Location	Location the camera will be moved to.
				* @param Rotation	Rotation the camera will be set to.
				* @return			Whether or not we were able to get a camera for a level editing viewport
				*/
				virtual bool SetSafeInfo(const FString& Context, const FVector& Location, const FRotator& Rotation, void(*Log)(const FString&) = nullptr) const = 0;
			};
		}
	}
}

using ICsLevelViewportCameraLibrary = NCsViewport::NLevel::NCamera::ILibrary;

//			

/**
* Interface for getting the LevelViewportCameraLibrary
*  NOTE: LevelViewportCameraLibrary is EDITOR ONLY.
*  REQUIREMENTS:
*	- Your EditorEngine (i.e. derived from UUnrealEdEngine) should the Interface: ICsGetLevelViewportCameraLibrary.
*   - A "default" implementation class: NCsViewport::NLevel::NCamera::NLibrary::FImpl can be used.
*	  This class is usually created / destroyed by Your EditorEngine.
*/
class CSCORELIBRARY_API ICsGetLevelViewportCameraLibrary
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const ICsLevelViewportCameraLibrary* GetViewportLevelCameraLibrary() const = 0;
};