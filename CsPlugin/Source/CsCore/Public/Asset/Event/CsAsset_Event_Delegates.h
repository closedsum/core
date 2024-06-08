// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsAsset_Event_Delegates.generated.h"

USTRUCT()
struct CSCORE_API FCsAsset_Event_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsAsset_Event_Delegates_STUB()
	{
	}
};

/** The way that editors were requested to close */
UENUM(BlueprintType)
enum class ECsAssetEditorCloseReason : uint8
{
	CloseAllEditorsForAsset		UMETA(DisplayName = "Close All Editors for Asset"),
	CloseOtherEditors			UMETA(DisplayName = "Close Other Editors"),
	RemoveAssetFromAllEditors	UMETA(DisplayName = "Remove Asset From All Editors"),
	CloseAllAssetEditors		UMETA(DisplayName = "Close All Asset Editors")
};

namespace NCsAsset
{
	namespace NEditor
	{
		namespace NClose
		{
			/** The way that editors were requested to close */
			enum class EReason : uint8
			{
				CloseAllEditorsForAsset,
				CloseOtherEditors,
				RemoveAssetFromAllEditors,
				CloseAllAssetEditors,
			};
		}
	}
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsAssetEditor_OnRequest_Close, UObject*, Asset, const ECsAssetEditorCloseReason&, Reason);

namespace NCsAsset
{
#define ReasonType NCsAsset::NEditor::NClose::EReason

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenedInEditor, UObject* /*Asset*/);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUniqueOpenedInEditor, UObject* /*Asset*/);
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequest_Close, UObject* /*Asset*/, const ReasonType& /*Reason*/);

#undef ReasonType
}