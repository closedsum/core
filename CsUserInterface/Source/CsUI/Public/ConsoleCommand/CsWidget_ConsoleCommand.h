// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"
// Interfaces
//#include "ICsMenu.h"
// Types
#include "ConsoleCommand/CsTypes_ConsoleCommand.h"

#include "CsWidget_ConsoleCommand.generated.h"

class UButton;
class UTextBlock;
class UEditableTextBox;
class UComboBoxString;
class USpinBox;

UCLASS(Blueprintable)
class CSUI_API UCsWidget_ConsoleCommand : public UUserWidget
{
	GENERATED_UCLASS_BODY()

// UUserWidget Interface
#pragma region
protected:

	virtual void NativeConstruct() override;

#pragma endregion UUserWidget Interface

// ICsMenu
#pragma region
public:

	void Open();

	void Close();

#pragma endregion ICsMenu

public:

	void Init();

	FString CurrentCategory;

#define CommandInfoType NCsConsoleCommand::FInfo

	CommandInfoType* CurrentCommandInfo;

#undef CommandInfoType

	UPROPERTY(meta = (BindWidget))
	UButton* Execute_Raw_Button;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Execute_Raw_Value_Text;

	UFUNCTION()
	void OnPressed_Execute_Raw();

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Category_ComboBox;

	UFUNCTION()
	void OnSelectionChanged_Category(FString SelectedItem, ESelectInfo::Type SelectionType);

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Command_ComboBox;

	UFUNCTION()
	void OnSelectionChanged_Command(FString SelectedItem, ESelectInfo::Type SelectionType);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description_Text;

	struct FParam
	{
		friend class UCsWidget_ConsoleCommand;

	#define ParamInfoType NCsConsoleCommand::NParam::FInfo

	private:

		UCsWidget_ConsoleCommand* Outer;

		ParamInfoType* Info;

	public:

		UTextBlock* Name;

		UEditableTextBox* String_Value;

		UComboBoxString* String_Values;

		UTextBlock* Min;

		UTextBlock* Min_Value;

		UTextBlock* Max;

		UTextBlock* Max_Value;

		USpinBox* Float;

		UButton* Inc;

		UEditableTextBox* Int;

		UButton* Dec;

		FParam() :
			Outer(nullptr),
			Info(nullptr),
			Name(nullptr),
			String_Value(nullptr),
			String_Values(nullptr),
			Min(nullptr),
			Min_Value(nullptr),
			Max(nullptr),
			Max_Value(nullptr),
			Float(nullptr),
			Inc(nullptr),
			Int(nullptr),
			Dec(nullptr)
		{
		}

		void Init(const ParamInfoType& ParamInfo);

		void Hide();

		void OnPressed_Inc();
		void OnChanged_Int(const FText& Text);
		void OnCommitted_Int(const FText& Text, ETextCommit::Type CommitMethod);
		void OnPressed_Dec();

		FString ToString() const;

	#undef ParamInfoType
	};

	TArray<FParam> Params;

	void UpdateParams();

	// Param01
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param01_Text;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param01_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Param01_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param01_Min_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param01_Min_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param01_Max_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param01_Max_Value_Text;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Param01_Float_SpinBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Param01_Int_Inc_Button;

	UFUNCTION()
	void OnPressed_Param01_Int_Inc();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param01_Int_Text;

	UFUNCTION()
	void OnChanged_Param01_Int(const FText& Text);

	UFUNCTION()
	void OnCommitted_Param01_Int(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	UButton* Param01_Int_Dec_Button;

	UFUNCTION()
	void OnPressed_Param01_Int_Dec();

#pragma endregion Param01

	// Param02
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param02_Text;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param02_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Param02_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param02_Min_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param02_Min_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param02_Max_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param02_Max_Value_Text;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Param02_Float_SpinBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Param02_Int_Inc_Button;

	UFUNCTION()
	void OnPressed_Param02_Int_Inc();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param02_Int_Text;

	UFUNCTION()
	void OnChanged_Param02_Int(const FText& Text);

	UFUNCTION()
	void OnCommitted_Param02_Int(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	UButton* Param02_Int_Dec_Button;

	UFUNCTION()
	void OnPressed_Param02_Int_Dec();

#pragma endregion Param02

	// Param03
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param03_Text;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param03_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Param03_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param03_Min_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param03_Min_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param03_Max_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param03_Max_Value_Text;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Param03_Float_SpinBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Param03_Int_Inc_Button;

	UFUNCTION()
	void OnPressed_Param03_Int_Inc();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param03_Int_Text;

	UFUNCTION()
	void OnChanged_Param03_Int(const FText& Text);

	UFUNCTION()
	void OnCommitted_Param03_Int(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	UButton* Param03_Int_Dec_Button;

	UFUNCTION()
	void OnPressed_Param03_Int_Dec();

#pragma endregion Param03

	// Param04
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param04_Text;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param04_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Param04_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param04_Min_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param04_Min_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param04_Max_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param04_Max_Value_Text;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Param04_Float_SpinBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Param04_Int_Inc_Button;

	UFUNCTION()
	void OnPressed_Param04_Int_Inc();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param04_Int_Text;

	UFUNCTION()
	void OnChanged_Param04_Int(const FText& Text);

	UFUNCTION()
	void OnCommitted_Param04_Int(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	UButton* Param04_Int_Dec_Button;

	UFUNCTION()
	void OnPressed_Param04_Int_Dec();

#pragma endregion Param04

	// Param05
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param05_Text;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param05_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Param05_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param05_Min_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param05_Min_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param05_Max_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param05_Max_Value_Text;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Param05_Float_SpinBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Param05_Int_Inc_Button;

	UFUNCTION()
	void OnPressed_Param05_Int_Inc();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param05_Int_Text;

	UFUNCTION()
	void OnChanged_Param05_Int(const FText& Text);

	UFUNCTION()
	void OnCommitted_Param05_Int(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	UButton* Param05_Int_Dec_Button;

	UFUNCTION()
	void OnPressed_Param05_Int_Dec();

#pragma endregion Param05

	// Param06
#pragma region
public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param06_Text;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param06_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Param06_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param06_Min_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param06_Min_Value_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param06_Max_Text;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Param06_Max_Value_Text;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Param06_Float_SpinBox;

	UPROPERTY(meta = (BindWidget))
	UButton* Param06_Int_Inc_Button;

	UFUNCTION()
	void OnPressed_Param06_Int_Inc();

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Param06_Int_Text;

	UFUNCTION()
	void OnChanged_Param06_Int(const FText& Text);

	UFUNCTION()
	void OnCommitted_Param06_Int(const FText& Text, ETextCommit::Type CommitMethod);

	UPROPERTY(meta = (BindWidget))
	UButton* Param06_Int_Dec_Button;

	UFUNCTION()
	void OnPressed_Param06_Int_Dec();

#pragma endregion Param06

	UPROPERTY(meta = (BindWidget))
	UButton* Execute_Button;

	UFUNCTION()
	void OnPressed_Execute();

	UPROPERTY(meta = (BindWidget))
	UButton* Close_Button;

	UFUNCTION()
	void OnPressed_Close();

	DECLARE_MULTICAST_DELEGATE(FOnPressed_Close);

	FOnPressed_Close OnPressed_Close_Event;
};