// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Material/CsTypes_Material.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUserWidget_ProgressBarInfo.generated.h"

// NCsUserWidget::NProgressBar::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NProgressBar, FInfo)

/**
* Describes any information for a UserWidget ProgressBar object.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget_ProgressBarInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** Fill Color and Opacity */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI|User Widget|Progress Bar")
	FLinearColor FillColorAndOpacity;

	FCsUserWidget_ProgressBarInfo() :
		FillColorAndOpacity(FLinearColor::Red)
	{
	}

#define InfoType NCsUserWidget::NProgressBar::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

class UObject;

namespace NCsUserWidget
{
	namespace NProgressBar
	{
		/**
		* Describes any information for a UserWidget ProgressBar object.
		*/
		struct CSUI_API FInfo final
		{
		private:

			CS_DECLARE_MEMBER_WITH_PROXY(FillColorAndOpacity, FLinearColor)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(FillColorAndOpacity, FLinearColor::Red)
			{
				CS_CTOR_SET_MEMBER_PROXY(FillColorAndOpacity);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FillColorAndOpacity, FLinearColor)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}