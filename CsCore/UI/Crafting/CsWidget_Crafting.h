// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "Types/CsTypes_Coroutine.h"
#include "Types/CsTypes_Input.h"
#include "CsWidget_Crafting.generated.h"

// Enums
#pragma region

namespace ECsWidgetCraftingRoutine
{
	enum Type
	{
		IncrementCount_Internal = ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX,
		DecrementCount_Internal,
		UpdateProgress_Internal,
		ECsWidgetCraftingRoutine_MAX,
	};
}

namespace ECsWidgetCraftingRoutine
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString IncrementCount_Internal = TCsString(TEXT("IncrementCount_Internal"), TEXT("incrementcount_internal"), TEXT("increment count internal"));
		const TCsString DecrementCount_Internal = TCsString(TEXT("DecrementCount_Internal"), TEXT("decrementcount_internal"), TEXT("decrement count internal"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::IncrementCount_Internal) { return Str::IncrementCount_Internal.Value; }
		if (EType == Type::DecrementCount_Internal) { return Str::IncrementCount_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::IncrementCount_Internal) { return Type::IncrementCount_Internal; }
		if (String == Str::DecrementCount_Internal) { return Type::IncrementCount_Internal; }
		return Type::ECsWidgetCraftingRoutine_MAX;
	}
}

#define ECS_WIDGET_CRAFTING_ROUTINE_MAX (uint8)ECsWidgetCraftingRoutine::ECsWidgetCraftingRoutine_MAX
typedef ECsWidgetCraftingRoutine::Type TCsWidgetCraftingRoutine;

UENUM(BlueprintType)
namespace ECsWidgetCraftingProcessState
{
	enum Type
	{
		None								UMETA(DisplayName = "None"),
		InProgress							UMETA(DisplayName = "InProgress"),
		Finished							UMETA(DisplayName = "Finished"),
		ECsWidgetCraftingProcessState_MAX	UMETA(Hidden),
	};
}

namespace ECsWidgetCraftingProcessState
{
	typedef TCsProperty_Multi_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"));
		const TCsString InProgress = TCsString(TEXT("InProgress"), TEXT("inprogress"));
		const TCsString Finished = TCsString(TEXT("Finished"), TEXT("finished"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::InProgress) { return Str::InProgress.Value; }
		if (EType == Type::Finished) { return Str::Finished.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::InProgress) { return Type::InProgress; }
		if (String == Str::Finished) { return Type::Finished; }
		return Type::ECsWidgetCraftingProcessState_MAX;
	}
}

#define ECS_WIDGET_CRAFTING_PROCESS_STATE_MAX (uint8)ECsWidgetCraftingProcessState::ECsWidgetCraftingProcessState_MAX
typedef ECsWidgetCraftingProcessState::Type TCsWidgetCraftingProcessState;

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsWidget_Crafting : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void OnNativeConstruct() override;
	virtual void Init() override;
	virtual void OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime) override;

	virtual void Hide() override;

// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;

#pragma endregion Routines

// Game Event
#pragma region

	virtual bool ProcessGameEvent(const TCsGameEvent &GameEvent) override;

#pragma endregion Game Event

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

	UPROPERTY(BlueprintReadOnly, Category ="Crafting")
	int32 CurrentSelectedOptionIndex;

	TArray<FName> SelectedOptionShortCodes;

	FECsAssetType RecipeAssetType;
	FECsAssetType ItemAssetType;

	UPROPERTY(BlueprintReadWrite, Category = "Crafting")
	uint8 Bag;

	void PopulateRecipes();
	void SetRecipe(const FName &ShortCode);
	void UpdateRecipeWithSelectedOption();
	UFUNCTION()
	void OnRecipeSelectionChanged(FString SelectedItem, ESelectInfo::Type  SelectionType);

	bool CanCompleteRecipe(const uint32& Count);

	// Increment
#pragma region

	UPROPERTY(meta = (BindWidget))
	UButton* Increment_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Increment_Text;

	FCsWidget_ButtonAndText Increment;

	TCsGameEvent IncrementStartGameEvent;
	TCsGameEvent IncrementEndGameEvent;

	UFUNCTION()
	void OnIncrementButtonPressed();
	UFUNCTION()
	void OnIncrementButtonReleased();

	UPROPERTY()
	float AutoIncrementTime;

	bool CanIncrement();

	CS_COROUTINE_DECLARE(IncrementCount)

	FECsInputAction IncrementInputAction;

	void PerformIncrementCount();
	void StopIncrementCount();

#pragma endregion Increment

	// Count
#pragma region

	UPROPERTY(meta = (BindWidget))
	UBorder* Count_Border;

	UPROPERTY(meta = (BindWidget))
	class UCsSpinBox_Int32* Count_Spin;

	FCsWidget_SpinBox_uint32 CurrentCount;

	UFUNCTION()
	void OnCountValueChanged(int32 InValue);
	UFUNCTION()
	void OnCountValueCommitted(int32 InValue, ETextCommit::Type CommitMethod);

#pragma endregion Count

	// Decrement
#pragma region

	UPROPERTY(meta = (BindWidget))
	UButton* Decrement_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Decrement_Text;

	FCsWidget_ButtonAndText Decrement;

	TCsGameEvent DecrementStartGameEvent;
	TCsGameEvent DecrementEndGameEvent;

	UFUNCTION()
	void OnDecrementButtonPressed();
	UFUNCTION()
	void OnDecrementButtonReleased();

	UPROPERTY()
	float AutoDecrementTime;

	bool CanDecrement();

	CS_COROUTINE_DECLARE(DecrementCount)

	FECsInputAction DecrementInputAction;

	void PerformDecrementCount();
	void StopDecrementCount();

#pragma endregion Decrement

	// Start
#pragma region

	UPROPERTY(meta = (BindWidget))
	UButton* Start_Button;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Start_Text;

	FCsWidget_ButtonAndText Start;

	TCsGameEvent StartGameEvent;

	FECsInputAction StartInputAction;

	UFUNCTION()
	void OnStartButtonPressed();

	TWeakObjectPtr<class ACsManager_Inventory> MyManager_Inventory;

	UFUNCTION()
	class ACsManager_Inventory* GetMyManager_Inventory();

	bool CanCraftItems();
	void CraftItems();

	void CancelCurrentCraftingProcess();

	UPROPERTY(BlueprintReadWrite, Category = "Crafting")
	TEnumAsByte<ECsWidgetCraftingProcessState::Type> CraftingProcessState;

	virtual void OnBeginCraftingProcess(const uint64 &ProcessId, const uint64& PayloadId);
	virtual void OnCraftItem_Event(const uint64 &ProcessId, const uint64 &PayloadId);
	virtual void OnFinishCraftingProcess(const uint64 &ProcessId, const uint64 &PayloadId);

#pragma endregion Start

#pragma endregion Options

// Progress
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyProgressBar;

	FCsWidget_Bar ProgressBar;

	void UpdateProgress(const uint64 &PayloadId);
	static char UpdateProgress_Internal(struct FCsRoutine* r);
	struct FCsRoutine* UpdateProgress_Internal_Routine;

	void StopUpdateProgress();

#pragma endregion Progress

	UPROPERTY(meta = (BindWidget))
	class UCsWidget_Crafting_Grid* MyGrid;
};