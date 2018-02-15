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
		IncrementCount_Internal = ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX,
		ECsWidgetCraftingRoutine_MAX,
	};
}

namespace ECsWidgetCraftingRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString IncrementCount_Internal = TCsString(TEXT("IncrementCount_Internal"), TEXT("incrementcount_internal"), TEXT("increment count internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::IncrementCount_Internal) { return Str::IncrementCount_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::IncrementCount_Internal) { return Type::IncrementCount_Internal; }
		return Type::ECsWidgetCraftingRoutine_MAX;
	}
}

#define ECS_WIDGET_CRAFTOMG_ROUTINE_MAX (uint8)ECsWidgetCraftingRoutine::ECsWidgetCraftingRoutine_MAX
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

// Options
#pragma region

	UPROPERTY(meta = (BindWidget))
	UGridPanel* Options_Grid;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Options_ComboBox;

	TCsAssetType RecipeAssetType;
	TCsAssetType ItemAssetType;

	void PopulateRecipes();
	void SetRecipe(const FName &ShortCode);
	UFUNCTION()
	void OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType);

	// Increment
#pragma region

	UPROPERTY(meta = (BindWidget))
	UButton* Increment_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Increment_Text;

	FCsWidget_ButtonAndText Increment;

	UFUNCTION()
	void OnIncrementButtonPressed();
	UFUNCTION()
	void OnIncrementButtonReleased();

	CS_COROUTINE_DECLARE(IncrementCount)

#pragma endregion Increment

	// Count
#pragma region

	UPROPERTY(meta = (BindWidget))
	UBorder* Count_Border;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Count_Spin;

	FCsWidget_SpinIntBox CurrentCount;

	UFUNCTION()
	void OnCountValueChanged(float InValue);
	UFUNCTION()
	void OnCountValueCommitted(float InValue, ETextCommit::Type CommitMethod);

#pragma endregion Count

	// Decrement
#pragma region

	UPROPERTY(meta = (BindWidget))
	UButton* Decrement_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Decrement_Text;

	FCsWidget_ButtonAndText Decrement;

	UFUNCTION()
	void OnDecrementButtonPressed();
	UFUNCTION()
	void OnDecrementButtonReleased();

	CS_COROUTINE_DECLARE(DecrementCount)

#pragma endregion Decrement

	// Start
#pragma region

	UPROPERTY(meta = (BindWidget))
	UButton* Start_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Start_Text;

	FCsWidget_ButtonAndText Start;

	UFUNCTION()
	void OnStartButtonPressed();

#pragma endregion Start

	TWeakObjectPtr<class ACsManager_Inventory> MyManager_Inventory;

	UFUNCTION()
	class ACsManager_Inventory* GetMyManager_Inventory();

	void CraftItem();

#pragma endregion Options

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyProgressBar;

	FCsWidget_Bar ProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UCsWidget_Crafting_Grid* MyGrid;
};