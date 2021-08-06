// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"

#include "CsPlayMode.generated.h"
#pragma once

UENUM(BlueprintType)
enum class ECsPlayMode : uint8
{
	/** Runs from within the editor. */
	InViewPort							UMETA(DisplayName = "In ViewPort"),
	/** Runs in a new window. */
	InEditorFloating					UMETA(DisplayName = "In Editor ViewPort"),
	/** Runs a mobile preview in a new process. */
	InMobilePreview						UMETA(DisplayName = "In Mobile Preview"),
	/** Runs a mobile preview targeted to a particular device in a new process. */
	InTargetedMobilePreview				UMETA(DisplayName = "In Targeted Mobile Preview"),
	/** Runs a vulkan preview in a new process. */
	InVulkanPreview						UMETA(DisplayName = "In Vulkan Preview"),
	/** Runs in a new process. */
	InNewProcess						UMETA(DisplayName = "In New Process"),
	/** Runs in VR. */
	InVR								UMETA(DisplayName = "In VR"),
	/** Simulates in viewport without possessing the player. */
	Simulate							UMETA(DisplayName = "Simulate"),
	/** The number of different Play Modes. */
	Count								UMETA(DisplayName = "Count"),
	/** Simulates a mobile preview from within the level viewport in editor. */
	InMobilePreviewEditorViewport		UMETA(DisplayName = "In Mobile Preview Editor Viewport"),
	/** Simulates a mobile preview in a new window (viewport) in editor. */
	InMobilePreviewEditorFloating		UMETA(DisplayName = "In Mobile Preview Editor Floating"),
	ECsPlayMode_MAX						UMETA(Hidden),
};

struct CSCORE_API EMCsPlayMode : public TCsEnumMap<ECsPlayMode>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsPlayMode, ECsPlayMode)
};

namespace NCsPlayMode
{
	typedef ECsPlayMode Type;

	namespace Ref
	{
		extern CSCORE_API const Type InViewPort;
		extern CSCORE_API const Type InEditorFloating;
		extern CSCORE_API const Type InMobilePreview;
		extern CSCORE_API const Type InTargetedMobilePreview;
		extern CSCORE_API const Type InVulkanPreview;
		extern CSCORE_API const Type InNewProcess;
		extern CSCORE_API const Type InVR;
		extern CSCORE_API const Type Simulate;
		extern CSCORE_API const Type Count;
		extern CSCORE_API const Type InMobilePreviewEditorViewport;
		extern CSCORE_API const Type InMobilePreviewEditorFloating;
		extern CSCORE_API const Type ECsPlayMode_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE bool IsMobilePIE(const Type& InType) { return InType == Type::InMobilePreviewEditorViewport || InType == Type::InMobilePreviewEditorFloating; }

	FORCEINLINE bool IsMobilePreviewEditor(const Type& InType)
	{
#if WITH_EDITOR
		bool bEditor = true;
#else
		bool bEditor = false;
#endif // #if WITH_EDITOR

		return bEditor && (InType == Type::InMobilePreview || IsMobilePIE(InType));
	}
}