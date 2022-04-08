// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
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

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Size, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bApplyOutlineToDropShadow, bool)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

			void Copy(const FOutline& From)
			{
				SetSize(From.GetSize());
				SetbApplyOutlineToDropShadow(From.GetbApplyOutlineToDropShadow());
				SetColor(From.GetColor());
			}

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

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Offset, FVector2D)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Color, FLinearColor)

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsUI::FLog::Warning) const;

			void Copy(const FShadow& From)
			{
				SetOffset(From.GetOffset());
				SetColor(From.GetColor());
			}

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Offset, FVector2D::UnitVector)
				CS_RESET_MEMBER_WITH_PROXY(Color, FLinearColor::Transparent)
			}
		};
	}
}

#pragma endregion FCsUserWidget_Text_ShadowSettings