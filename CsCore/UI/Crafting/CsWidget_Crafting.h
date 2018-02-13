// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "Types/CsTypes_Coroutine.h"
#include "CsWidget_Crafting.generated.h"

// Enums
#pragma region

namespace ECsWidgetCraftingRoutine
{
	enum Type
	{
		CraftItem_Internal = ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX,
		ECsWidgetCraftingRoutine_MAX,
	};
}

namespace ECsWidgetCraftingRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString CraftItem_Internal = TCsString(TEXT("CraftItem_Internal"), TEXT("craftitem_internal"), TEXT("craft item internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::CraftItem_Internal) { return Str::CraftItem_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::CraftItem_Internal) { return Type::CraftItem_Internal; }
		return Type::ECsWidgetCraftingRoutine_MAX;
	}
}

#define ECS_WIDGET_CRAFTING_ROUTINE_MAX (uint8)ECsWidgetCraftingRoutine::ECsWidgetCraftingRoutine_MAX
typedef ECsWidgetCraftingRoutine::Type TCsWidgetCraftingRoutine;

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsWidget_Crafting : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void Init() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MyVerticalBox;

	TCsFVector2D Position;
	TCsFVector2D Size;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Header_Text;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* Options_Grid;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Options_ComboBox;

	TCsAssetType RecipeAssetType;
	TCsAssetType ItemAssetType;

	void PopulateRecipes();
	void OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType);

	UPROPERTY(meta = (BindWidget))
	UBorder* Count_Border;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Count_Spin;

	FCsWidget_SpinIntBox CurrentCount;

	UPROPERTY(meta = (BindWidget))
	UButton* Start_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Start_Text;

	FCsWidget_ButtonAndText Start;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyProgressBar;

	FCsWidget_Bar ProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UCsWidget_Crafting_Grid* MyGrid;

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type) override;

#pragma endregion Routines
	
	CS_COROUTINE_DECLARE(CraftItem)
};