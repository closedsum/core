// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Material/CsTypes_Material.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUserWidget_ProgressBarInfo.generated.h"

struct FCsUserWidget_ProgressBarInfo;

// NCsUserWidget::NProgressBar::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NProgressBar, FInfo)

namespace NCsUserWidget_ProgressBarInfo
{
	using ThisType = FCsUserWidget_ProgressBarInfo;
	using InfoType = NCsUserWidget::NProgressBar::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSUI_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

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

	using InfoType = NCsUserWidget::NProgressBar::FInfo;
	using _Impl = NCsUserWidget_ProgressBarInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)					{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const	{ _Impl::CopyToInfoAsValue(this, Info); }

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

			FORCEINLINE FInfo(FInfo& B)
			{
				SetFillColorAndOpacity(B.GetFillColorAndOpacity());
			}

			FORCEINLINE FInfo(const FInfo& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FillColorAndOpacity, FLinearColor)

			FORCEINLINE void Copy(const FInfo& B)
			{
				SetFillColorAndOpacity(B.GetFillColorAndOpacity());
			}
			
			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}