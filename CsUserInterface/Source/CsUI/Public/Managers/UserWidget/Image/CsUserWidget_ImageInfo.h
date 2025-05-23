// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
#include "Types/CsTypes_Texture.h"
// Log
#include "Utility/CsUILog.h"

#include "CsUserWidget_ImageInfo.generated.h"

struct FCsUserWidget_ImageInfo;

// NCsUserWidget::NImage::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NImage, FInfo)

namespace NCsUserWidget_ImageInfo
{
	using ThisType = FCsUserWidget_ImageInfo;
	using InfoType = NCsUserWidget::NImage::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSUI_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// NCsUserWidget::NImage::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NImage, FInfo)

/**
* Describes any information for a UserWidget Image object.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget_ImageInfo
{
	GENERATED_USTRUCT_BODY()

public:

	/** */
	UPROPERTY(EditAnywhere, Category = "CImpl|User Widget|Text")
	FCsTexture2D Image;

	/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text", meta = (ClampMin = "0.01", UIMin = "0.01"))
	float RenderScale;

	/** The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsUI|User Widget|Text")
	int32 ZOrder;

public:

	FCsUserWidget_ImageInfo() :
		Image(),
		RenderScale(1.0f),
		ZOrder(0)
	{
	}

	using InfoType = NCsUserWidget::NImage::FInfo;
	using _Impl = NCsUserWidget_ImageInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)					{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const	{ _Impl::CopyToInfoAsValue(this, Info); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

class UObject;

namespace NCsUserWidget
{
	namespace NImage
	{
		/**
		* Describes any information for a UserWidget Image object.
		*/
		struct CSUI_API FInfo final
		{
		private:

			/** */
			CS_DECLARE_MEMBER_WITH_PROXY(Image, UTexture2D*)
			/** The scale to apply to Render Transform (set via SetRenderScale(GetScale() * FVector2D::UnitVector)). */
			CS_DECLARE_MEMBER_WITH_PROXY(RenderScale, float)
			/** The order priority this widget is rendered in.  Higher values are rendered last (and so they will appear to be on top). */
			CS_DECLARE_MEMBER_WITH_PROXY(ZOrder, int32)

		public:

			FInfo() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Image, nullptr),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(RenderScale, 1.0f),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(ZOrder, 0)
			{
				CS_CTOR_SET_MEMBER_PROXY(Image);
				CS_CTOR_SET_MEMBER_PROXY(RenderScale);
				CS_CTOR_SET_MEMBER_PROXY(ZOrder);
			}

			FORCEINLINE FInfo(FInfo& B)
			{
				SetImage(B.GetImage());
				SetRenderScale(B.GetRenderScale());
				SetZOrder(B.GetZOrder());
			}

			FORCEINLINE FInfo(const FInfo& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(Image, UTexture2D)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(RenderScale, float)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ZOrder, int32)

			FORCEINLINE void Copy(const FInfo& B)
			{
				SetImage(B.GetImage());
				SetRenderScale(B.GetRenderScale());
				SetZOrder(B.GetZOrder());
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
		};
	}
}