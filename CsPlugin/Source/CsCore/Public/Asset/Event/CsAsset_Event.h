// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsAsset_Event.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsAsset_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
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

class CSCORE_API ICsAsset_Event
{
	GENERATED_IINTERFACE_BODY()

public:

public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnOpenedInEditor, UObject* /*Asset*/);

	virtual FOnOpenedInEditor& GetAsset_OpenedInEditor_Event() = 0;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUniqueOpenedInEditor, UObject* /*Asset*/);

	virtual FOnUniqueOpenedInEditor& GetAsset_UniqueOpenedInEditor_Event() = 0;

#define ReasonType NCsAsset::NEditor::NClose::EReason
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRequest_Close, UObject* /*Asset*/, const ReasonType& /*Reason*/);
#undef ReasonType

	virtual FOnRequest_Close& GetAssetEditor_OnRequest_Close_Event() = 0;
	virtual FCsAssetEditor_OnRequest_Close& GetAssetEditor_OnRequest_Close_ScriptEvent() = 0;
};