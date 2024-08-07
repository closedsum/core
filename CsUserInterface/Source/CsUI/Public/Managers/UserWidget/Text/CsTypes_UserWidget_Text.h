// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Proxy.h"
// Log
#include "Utility/CsUILog.h"

#include "CsTypes_UserWidget_Text.generated.h"

// FCsUserWidget_Text_OutlineSettings
#pragma region

// NCsUserWidget::NText::FOutline
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NText, FOutline)

/**
* Describes any Outline Settings for Damage Text.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget_Text_OutlineSettings
{
	GENERATED_USTRUCT_BODY()

public:

	/** Size of an outline in slate units (at 1.0 font scale this unit is a pixel). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI", meta = (UIMin = "0", ClampMin = "0"))
	int32 Size;

	/** When enabled the outline will be applied to any drop shadow that uses this font. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI")
	bool bApplyOutlineToDropShadow;

	/** The color of the outline for any character int this font. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI")
	FLinearColor Color;

	FCsUserWidget_Text_OutlineSettings() :
		Size(0),
		bApplyOutlineToDropShadow(false),
		Color(FLinearColor::Black)
	{
	}

#define SettingsType NCsUserWidget::NText::FOutline
	void CopyToSettings(SettingsType* Settings);
	void CopyToSettingsAsValue(SettingsType* Settings) const;
#undef SettingsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

namespace NCsUserWidget
{
	namespace NText
	{
		/**
		* Describes any Outline Settings for Damage Text.
		*/
		struct CSUI_API FOutline
		{
		private:

			/** Size of an outline in slate units (at 1.0 font scale this unit is a pixel). */
			CS_DECLARE_MEMBER_WITH_PROXY(Size, int32)

			/** When enabled the outline will be applied to any drop shadow that uses this font. */
			CS_DECLARE_MEMBER_WITH_PROXY(bApplyOutlineToDropShadow, bool)

			/** The color of the outline for any character int this font. */
			CS_DECLARE_MEMBER_WITH_PROXY(Color, FLinearColor)

		public:

			FOutline() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Size, 0),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(bApplyOutlineToDropShadow, false),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Color, FLinearColor::Black)
			{
				CS_CTOR_SET_MEMBER_PROXY(Size);
				CS_CTOR_SET_MEMBER_PROXY(bApplyOutlineToDropShadow);
				CS_CTOR_SET_MEMBER_PROXY(Color);
			}

			FORCEINLINE FOutline(FOutline& B)
			{
				Copy(B);
			}

			FORCEINLINE FOutline(const FOutline& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Size, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bApplyOutlineToDropShadow, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)

			FORCEINLINE void Copy(const FOutline& B)
			{
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Size);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, bApplyOutlineToDropShadow);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Color);
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Size, 0)
				CS_RESET_MEMBER_WITH_PROXY(bApplyOutlineToDropShadow, false)
				CS_RESET_MEMBER_WITH_PROXY(Color, FLinearColor::Black)
			}
		};
	}
}

#pragma endregion FCsUserWidget_Text_OutlineSettings

// FCsUserWidget_Text_ShadowSettings
#pragma region

// NCsUserWidget::NText::FShadow
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NText, FShadow)

/**
* Describes any Shadow Settings for Damage Text.
*/
USTRUCT(BlueprintType)
struct CSUI_API FCsUserWidget_Text_ShadowSettings
{
	GENERATED_USTRUCT_BODY()

public:

	/** The direction the shadow is cast. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI", meta = (UIMin = "0", ClampMin = "0"))
	FVector2D Offset;

	/** The color of the shadow */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsUI")
	FLinearColor Color;
	
	FCsUserWidget_Text_ShadowSettings() :
		Offset(1.0f),
		Color(FLinearColor::Transparent)
	{
	}

#define SettingsType NCsUserWidget::NText::FShadow
	void CopyToSettings(SettingsType* Settings);
	void CopyToSettingsAsValue(SettingsType* Settings) const;
#undef SettingsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;
};

namespace NCsUserWidget
{
	namespace NText
	{
		/**
		* Describes any Shadow Settings for Damage Text.
		*/
		struct CSUI_API FShadow
		{
		private:

			/** The direction the shadow is cast. */
			CS_DECLARE_MEMBER_WITH_PROXY(Offset, FVector2D)

			/** The color of the shadow */
			CS_DECLARE_MEMBER_WITH_PROXY(Color, FLinearColor)

		public:

			FShadow() :
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Offset, FVector2D::UnitVector),
				CS_CTOR_INIT_MEMBER_WITH_PROXY(Color, FLinearColor::Transparent)
			{
				CS_CTOR_SET_MEMBER_PROXY(Offset);
				CS_CTOR_SET_MEMBER_PROXY(Color);
			}

			FORCEINLINE FShadow(FShadow& B)
			{
				Copy(B);
			}

			FORCEINLINE FShadow(const FShadow& B)
			{
				Copy(B);
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector2D)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)

			FORCEINLINE void Copy(const FShadow& B)
			{
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Offset);
				CS_COPY_PROXY_TO_PROXY_AS_VALUE(B, Color);
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Offset, FVector2D::UnitVector)
				CS_RESET_MEMBER_WITH_PROXY(Color, FLinearColor::Transparent)
			}
		};
	}
}

#pragma endregion FCsUserWidget_Text_ShadowSettings