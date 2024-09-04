// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "ConsoleCommand/CsWidget_ConsoleCommand.h"
#include "CsUI.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Coordinators/ConsoleCommand/CsLibrary_Coordinator_ConsoleCommand.h"
#include "CsLibrary_ConsoleCommand.h"
// Coordinator
#include "Coordinators/ConsoleCommand/CsCoordinator_ConsoleCommand.h"

// UI
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ComboBoxString.h"
#include "Components/SpinBox.h"

// Cached
#pragma region

namespace NCsWidgetConsoleCommand
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_FUNCTION_NAME_AS_STRING(UCsWidget_ConsoleCommand, Open);
			CS_DEFINE_FUNCTION_NAME_AS_STRING(UCsWidget_ConsoleCommand, OnSelectionChanged_Category);
			CS_DEFINE_FUNCTION_NAME_AS_STRING(UCsWidget_ConsoleCommand, OnSelectionChanged_Command);
			CS_DEFINE_FUNCTION_NAME_AS_STRING(UCsWidget_ConsoleCommand, UpdateParams);
		}
	}
}

#pragma endregion Cached

UCsWidget_ConsoleCommand::UCsWidget_ConsoleCommand(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	CurrentCategory(),
	CurrentCommandInfo(nullptr)
{
}

// UUserWidget Interface
#pragma region

void UCsWidget_ConsoleCommand::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
}

#pragma endregion UUserWidget Interface

// ICsMenu
#pragma region

void UCsWidget_ConsoleCommand::Open()
{
	using namespace NCsWidgetConsoleCommand::NCached;

	const FString& Context = Str::Open;

	typedef NCsConsoleCommand::NCoordinator::FLibrary ConsoleCommandCoordinatorLibrary;

	UObject* ContextRoot = ConsoleCommandCoordinatorLibrary::GetContextRootChecked(Context, this);

	UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand = UCsCoordinator_ConsoleCommand::Get(ContextRoot);

	TArray<FString> Categories;
	Coordinator_ConsoleCommand->GetCategories(Categories);

	Category_ComboBox->ClearOptions();

	if (Categories.Num() > CS_EMPTY)
	{
		for (const FString& Category : Categories)
		{
			Category_ComboBox->AddOption(Category);
		}
		Category_ComboBox->SetSelectedOption(Categories[CS_FIRST]);
	}
}

void UCsWidget_ConsoleCommand::Close()
{

}

#pragma endregion ICsMenu

void UCsWidget_ConsoleCommand::Init()
{
	Params.Reset(6);
	Params.AddDefaulted(6);

	for (FParam& Param : Params)
	{
		Param.Outer = this;
	}

	#define CS_TEMP_SET_PARAM_REF(__Param, __Index) \
		__Param.Name			= Param##__Index##_Text; \
		__Param.String_Value	= Param##__Index##_Value_Text; \
		__Param.String_Values	= Param##__Index##_ComboBox; \
		__Param.Min				= Param##__Index##_Min_Text; \
		__Param.Min_Value		= Param##__Index##_Min_Value_Text; \
		__Param.Max				= Param##__Index##_Max_Text; \
		__Param.Max_Value		= Param##__Index##_Max_Value_Text; \
		__Param.Float			= Param##__Index##_Float_SpinBox; \
		__Param.Inc				= Param##__Index##_Int_Inc_Button; \
		__Param.Int				= Param##__Index##_Int_Text; \
		__Param.Dec				= Param##__Index##_Int_Dec_Button;

	CS_TEMP_SET_PARAM_REF(Params[0], 01)
	CS_TEMP_SET_PARAM_REF(Params[1], 02)
	CS_TEMP_SET_PARAM_REF(Params[2], 03)
	CS_TEMP_SET_PARAM_REF(Params[3], 04)
	CS_TEMP_SET_PARAM_REF(Params[4], 05)
	CS_TEMP_SET_PARAM_REF(Params[5], 06)

	#undef CS_TEMP_SET_PARAM_REF

	// Bind delegates

	Execute_Raw_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Execute_Raw);
	Category_ComboBox->OnSelectionChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnSelectionChanged_Category);
	Command_ComboBox->OnSelectionChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnSelectionChanged_Command);
		// 01
	Param01_Int_Inc_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param01_Int_Inc);
	Param01_Int_Text->OnTextChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnChanged_Param01_Int);
	Param01_Int_Text->OnTextCommitted.AddDynamic(this, &UCsWidget_ConsoleCommand::OnCommitted_Param01_Int);
	Param01_Int_Dec_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param01_Int_Dec);
		// 02
	Param02_Int_Inc_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param02_Int_Inc);
	Param02_Int_Text->OnTextChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnChanged_Param02_Int);
	Param02_Int_Text->OnTextCommitted.AddDynamic(this, &UCsWidget_ConsoleCommand::OnCommitted_Param02_Int);
	Param02_Int_Dec_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param02_Int_Dec);
		// 03
	Param03_Int_Inc_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param03_Int_Inc);
	Param03_Int_Text->OnTextChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnChanged_Param03_Int);
	Param03_Int_Text->OnTextCommitted.AddDynamic(this, &UCsWidget_ConsoleCommand::OnCommitted_Param03_Int);
	Param03_Int_Dec_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param03_Int_Dec);
		// 04
	Param04_Int_Inc_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param04_Int_Inc);
	Param04_Int_Text->OnTextChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnChanged_Param04_Int);
	Param04_Int_Text->OnTextCommitted.AddDynamic(this, &UCsWidget_ConsoleCommand::OnCommitted_Param04_Int);
	Param04_Int_Dec_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param04_Int_Dec);
		// 05
	Param05_Int_Inc_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param05_Int_Inc);
	Param05_Int_Text->OnTextChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnChanged_Param05_Int);
	Param05_Int_Text->OnTextCommitted.AddDynamic(this, &UCsWidget_ConsoleCommand::OnCommitted_Param05_Int);
	Param05_Int_Dec_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param05_Int_Dec);
		// 06
	Param06_Int_Inc_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param06_Int_Inc);
	Param06_Int_Text->OnTextChanged.AddDynamic(this, &UCsWidget_ConsoleCommand::OnChanged_Param06_Int);
	Param06_Int_Text->OnTextCommitted.AddDynamic(this, &UCsWidget_ConsoleCommand::OnCommitted_Param06_Int);
	Param06_Int_Dec_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Param06_Int_Dec);

	Execute_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Execute);
	Close_Button->OnPressed.AddDynamic(this, &UCsWidget_ConsoleCommand::OnPressed_Close);
}

void UCsWidget_ConsoleCommand::OnPressed_Execute_Raw()
{
	typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

	ConsoleCommandLibrary::Exec(this, Execute_Raw_Value_Text->GetText().ToString());
}

void UCsWidget_ConsoleCommand::OnSelectionChanged_Category(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	using namespace NCsWidgetConsoleCommand::NCached;

	const FString& Context = Str::OnSelectionChanged_Category;

	// Update Commands
	CurrentCommandInfo = nullptr;

	typedef NCsConsoleCommand::NCoordinator::FLibrary ConsoleCommandCoordinatorLibrary;
	typedef NCsConsoleCommand::FInfo CommandInfoType;

	UObject* ContextRoot = ConsoleCommandCoordinatorLibrary::GetContextRootChecked(Context, this);
	
	UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand = UCsCoordinator_ConsoleCommand::Get(ContextRoot);

	if (const TArray<CommandInfoType>* InfosPtr = Coordinator_ConsoleCommand->GetConsoleCommandInfos(SelectedItem))
	{
		CurrentCategory = SelectedItem;

		Command_ComboBox->ClearOptions();

		const TArray<CommandInfoType>& Infos = *InfosPtr;

		for (const CommandInfoType& Info : Infos)
		{
			Command_ComboBox->AddOption(Info.GetPrimaryDefintion());
		}

		CurrentCommandInfo = const_cast<CommandInfoType*>(&(Infos[CS_FIRST]));

		Command_ComboBox->SetSelectedOption(CurrentCommandInfo->GetPrimaryDefintion());

		Description_Text->SetText(FText::FromString(CurrentCommandInfo->Description));
		UpdateParams();
	}
	else
	{
		CurrentCategory.Empty();

		Command_ComboBox->ClearOptions();

		Description_Text->SetText(FText::FromString(TEXT("")));

		// Hide Params
		for (FParam& Param : Params)
		{
			Param.Hide();
		}
	}
}

void UCsWidget_ConsoleCommand::OnSelectionChanged_Command(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	using namespace NCsWidgetConsoleCommand::NCached;

	const FString& Context = Str::OnSelectionChanged_Command;

	// Hide Params
	for (FParam& Param : Params)
	{
		Param.Hide();
	}

	CurrentCommandInfo = nullptr;

	// Find Command
	typedef NCsConsoleCommand::NCoordinator::FLibrary ConsoleCommandCoordinatorLibrary;
	typedef NCsConsoleCommand::FInfo CommandInfoType;

	UObject* ContextRoot = ConsoleCommandCoordinatorLibrary::GetContextRootChecked(Context, this);

	UCsCoordinator_ConsoleCommand* Coordinator_ConsoleCommand = UCsCoordinator_ConsoleCommand::Get(ContextRoot);

	if (const TArray<CommandInfoType>* InfosPtr = Coordinator_ConsoleCommand->GetConsoleCommandInfos(CurrentCategory))
	{
		const TArray<CommandInfoType>& Infos = *InfosPtr;

		const int32 Count = Infos.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const CommandInfoType& Info = Infos[I];

			if (SelectedItem == Info.GetPrimaryDefintion())
			{
				CurrentCommandInfo = const_cast<CommandInfoType*>(&Info);

				Description_Text->SetText(FText::FromString(CurrentCommandInfo->Description));
				UpdateParams();
				break;
			}
		}
	}
}

#define ParamInfoType NCsConsoleCommand::NParam::FInfo
void UCsWidget_ConsoleCommand::FParam::Init(const ParamInfoType& ParamInfo)
{
	Info = const_cast<ParamInfoType*>(&ParamInfo);

	// Set the Name
	Name->SetVisibility(ESlateVisibility::HitTestInvisible);
	Name->SetText(FText::FromString(FString::Printf(TEXT("%s"), *ParamInfo.Name)));

	typedef NCsConsoleCommand::NParam::EValue ParamValueType;

	// Check if the values should be chosen from a drop down
	const TArray<FString>& Values = Info->Values;

	if (Values.Num() > CS_EMPTY)
	{
		String_Values->SetVisibility(ESlateVisibility::Visible);
		String_Values->ClearOptions();

		for (int32 I = 0; I < Values.Num(); ++I)
		{
			String_Values->AddOption(Values[I]);
		}

		String_Values->SetSelectedOption(Values[CS_FIRST]);
	}
	else
	{
		const ParamValueType& ValueType = Info->ValueType;

		// String | Enum (Enum should have ParamInfo.Values populated)
		if (ValueType == ParamValueType::String ||
			ValueType == ParamValueType::Enum)
		{
			String_Value->SetVisibility(ESlateVisibility::Visible);
		}
		// Integer | Float
		else
		if (ValueType == ParamValueType::Integer ||
			ValueType == ParamValueType::Float)
		{
			Min->SetVisibility(ESlateVisibility::HitTestInvisible);
			Min_Value->SetVisibility(ESlateVisibility::HitTestInvisible);
			Max->SetVisibility(ESlateVisibility::HitTestInvisible);
			Max_Value->SetVisibility(ESlateVisibility::HitTestInvisible);

			if (Info->bMinValue)
				Min_Value->SetText(FText::FromString(FString::Printf(TEXT("%f"), Info->MinValue)));
			else
				Min_Value->SetText(FText::FromString(TEXT("-inf")));

			if (Info->bMaxValue)
				Max_Value->SetText(FText::FromString(FString::Printf(TEXT("%f"), Info->MaxValue)));
			else
				Max_Value->SetText(FText::FromString(TEXT("inf")));

			// Integer
			if (ValueType == ParamValueType::Integer)
			{
				if (Info->bMinValue)
					Min_Value->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::FloorToInt(Info->MinValue))));
				else
					Min_Value->SetText(FText::FromString(TEXT("-inf")));

				if (Info->bMaxValue)
					Max_Value->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::FloorToInt(Info->MaxValue))));
				else
					Max_Value->SetText(FText::FromString(TEXT("inf")));

				Inc->SetVisibility(ESlateVisibility::Visible);
				Int->SetVisibility(ESlateVisibility::Visible);
				Dec->SetVisibility(ESlateVisibility::Visible);

				Int->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::FloorToInt(Info->DefaultValue))));
			}
			// Float
			else
			{
				if (Info->bMinValue)
					Min_Value->SetText(FText::FromString(FString::Printf(TEXT("%3.3f"), Info->MinValue)));
				else
					Min_Value->SetText(FText::FromString(TEXT("-inf")));

				if (Info->bMaxValue)
					Max_Value->SetText(FText::FromString(FString::Printf(TEXT("%3.3f"), Info->MaxValue)));
				else
					Max_Value->SetText(FText::FromString(TEXT("inf")));

				Float->SetVisibility(ESlateVisibility::Visible);

				Float->ClearMinValue();
				Float->ClearMaxValue();
				Float->ClearMinSliderValue();
				Float->ClearMaxSliderValue();

				if (Info->bMinValue)
				{
					Float->SetMinValue(Info->MinValue);
					Float->SetMinSliderValue(Info->MinValue);
				}

				if (Info->bMaxValue)
				{
					Float->SetMaxValue(Info->MaxValue);
					Float->SetMaxSliderValue(Info->MaxValue);
				}

				Float->SetValue(Info->DefaultValue);
			}
		}
	}
}
#undef ParamInfoType

void UCsWidget_ConsoleCommand::FParam::Hide()
{
	Name->SetVisibility(ESlateVisibility::Collapsed);
	String_Value->SetVisibility(ESlateVisibility::Collapsed);
	String_Values->SetVisibility(ESlateVisibility::Collapsed);
	Min->SetVisibility(ESlateVisibility::Collapsed);
	Min_Value->SetVisibility(ESlateVisibility::Collapsed);
	Max->SetVisibility(ESlateVisibility::Collapsed);
	Max_Value->SetVisibility(ESlateVisibility::Collapsed);
	Float->SetVisibility(ESlateVisibility::Collapsed);
	Inc->SetVisibility(ESlateVisibility::Collapsed);
	Int->SetVisibility(ESlateVisibility::Collapsed);
	Dec->SetVisibility(ESlateVisibility::Collapsed);
}

void UCsWidget_ConsoleCommand::FParam::OnPressed_Inc()
{
	int32 Value = FCString::Atoi(*(Int->GetText().ToString()));

	Value = Info->bMaxValue ? FMath::Min(Value + 1, (int32)Info->MaxValue) : Value + 1;

	Int->SetText(FText::FromString(FString::Printf(TEXT("%d"), Value)));
}

void UCsWidget_ConsoleCommand::FParam::OnChanged_Int(const FText& Text)
{
	int32 Value = FCString::Atoi(*(Text.ToString()));

	if (Info->bMinValue)
		Value = FMath::Max(Value, (int32)Info->MinValue);

	if (Info->bMaxValue)
		Value = FMath::Min(Value, (int32)Info->MaxValue);

	Int->SetText(FText::FromString(FString::Printf(TEXT("%d"), Value)));
}

void UCsWidget_ConsoleCommand::FParam::OnCommitted_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	int32 Value = FCString::Atoi(*(Text.ToString()));

	if (Info->bMinValue)
		Value = FMath::Max(Value, (int32)Info->MinValue);

	if (Info->bMaxValue)
		Value = FMath::Min(Value, (int32)Info->MaxValue);

	Int->SetText(FText::FromString(FString::Printf(TEXT("%d"), Value)));
}

void UCsWidget_ConsoleCommand::FParam::OnPressed_Dec()
{
	int32 Value = FCString::Atoi(*(Int->GetText().ToString()));

	Value = Info->bMinValue ? FMath::Max(Value - 1, (int32)Info->MinValue) : Value - 1;

	Int->SetText(FText::FromString(FString::Printf(TEXT("%d"), Value)));
}

FString UCsWidget_ConsoleCommand::FParam::ToString() const
{
	typedef NCsConsoleCommand::NParam::EValue ParamValueType;

	const ParamValueType& ValueType = Info->ValueType;

	const TArray<FString>& Values = Info->Values;

	if (Values.Num() > CS_EMPTY)
	{
		return String_Values->GetSelectedOption();
	}
	else
	{
		// String | Enum
		if (ValueType == ParamValueType::String ||
			ValueType == ParamValueType::Enum)
		{
			return String_Value->GetText().ToString();
		}
		// Integer
		else
		if (ValueType == ParamValueType::Integer)
		{
			return Int->GetText().ToString();
		}
		// Float
		else
		if (ValueType == ParamValueType::Float)
		{
			return FString::Printf(TEXT("%f"), Float->GetValue());
		}
	}
	return FString();
}

void UCsWidget_ConsoleCommand::UpdateParams()
{
	using namespace NCsWidgetConsoleCommand::NCached;

	const FString& Context = Str::UpdateParams;

	for (FParam& Param : Params)
	{
		Param.Hide();
	}

	if (!CurrentCategory.IsEmpty())
	{
		if (CurrentCommandInfo)
		{
			typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;

			const TArray<ParamInfoType>& ParamInfos = CurrentCommandInfo->ParamInfos;

			const int32 Count = ParamInfos.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const ParamInfoType& ParamInfo = ParamInfos[I];
				FParam& Param				   = Params[I];

				Param.Init(ParamInfo);
			}
		}
	}
}

// Param01
#pragma region

void UCsWidget_ConsoleCommand::OnPressed_Param01_Int_Inc()
{
	Params[0].OnPressed_Inc();
}

void UCsWidget_ConsoleCommand::OnChanged_Param01_Int(const FText& Text)
{
	Params[0].OnChanged_Int(Text);
}

void UCsWidget_ConsoleCommand::OnCommitted_Param01_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	Params[0].OnCommitted_Int(Text, CommitMethod);
}

void UCsWidget_ConsoleCommand::OnPressed_Param01_Int_Dec()
{
	Params[0].OnPressed_Dec();
}

#pragma endregion Param01

// Param02
#pragma region

void UCsWidget_ConsoleCommand::OnPressed_Param02_Int_Inc()
{
	Params[1].OnPressed_Inc();
}

void UCsWidget_ConsoleCommand::OnChanged_Param02_Int(const FText& Text)
{
	Params[1].OnChanged_Int(Text);
}

void UCsWidget_ConsoleCommand::OnCommitted_Param02_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	Params[1].OnCommitted_Int(Text, CommitMethod);
}

void UCsWidget_ConsoleCommand::OnPressed_Param02_Int_Dec()
{
	Params[1].OnPressed_Dec();
}

#pragma endregion Param02

// Param03
#pragma region

void UCsWidget_ConsoleCommand::OnPressed_Param03_Int_Inc()
{
	Params[2].OnPressed_Inc();
}

void UCsWidget_ConsoleCommand::OnChanged_Param03_Int(const FText& Text)
{
	Params[2].OnChanged_Int(Text);
}

void UCsWidget_ConsoleCommand::OnCommitted_Param03_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	Params[2].OnCommitted_Int(Text, CommitMethod);
}

void UCsWidget_ConsoleCommand::OnPressed_Param03_Int_Dec()
{
	Params[2].OnPressed_Dec();
}

#pragma endregion Param03

// Param04
#pragma region

void UCsWidget_ConsoleCommand::OnPressed_Param04_Int_Inc()
{
	Params[3].OnPressed_Inc();
}

void UCsWidget_ConsoleCommand::OnChanged_Param04_Int(const FText& Text)
{
	Params[3].OnChanged_Int(Text);
}

void UCsWidget_ConsoleCommand::OnCommitted_Param04_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	Params[3].OnCommitted_Int(Text, CommitMethod);
}

void UCsWidget_ConsoleCommand::OnPressed_Param04_Int_Dec()
{
	Params[3].OnPressed_Dec();
}

#pragma endregion Param04

// Param05
#pragma region

void UCsWidget_ConsoleCommand::OnPressed_Param05_Int_Inc()
{
	Params[4].OnPressed_Inc();
}

void UCsWidget_ConsoleCommand::OnChanged_Param05_Int(const FText& Text)
{
	Params[4].OnChanged_Int(Text);
}

void UCsWidget_ConsoleCommand::OnCommitted_Param05_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	Params[4].OnCommitted_Int(Text, CommitMethod);
}

void UCsWidget_ConsoleCommand::OnPressed_Param05_Int_Dec()
{
	Params[4].OnPressed_Dec();
}

#pragma endregion Param05

// Param06
#pragma region

void UCsWidget_ConsoleCommand::OnPressed_Param06_Int_Inc()
{
	Params[5].OnPressed_Inc();
}

void UCsWidget_ConsoleCommand::OnChanged_Param06_Int(const FText& Text)
{
	Params[5].OnChanged_Int(Text);
}

void UCsWidget_ConsoleCommand::OnCommitted_Param06_Int(const FText& Text, ETextCommit::Type CommitMethod)
{
	Params[5].OnCommitted_Int(Text, CommitMethod);
}

void UCsWidget_ConsoleCommand::OnPressed_Param06_Int_Dec()
{
	Params[5].OnPressed_Dec();
}

#pragma endregion Param06

void UCsWidget_ConsoleCommand::OnPressed_Execute()
{
	// Build Command from Params
	if (CurrentCommandInfo)
	{
		FString Command = CurrentCommandInfo->GetPrimaryCommand();

		typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;

		const TArray<ParamInfoType>& ParamInfos = CurrentCommandInfo->ParamInfos;

		const int32 Count = ParamInfos.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const ParamInfoType& ParamInfo = ParamInfos[I];
			FParam& Param				   = Params[I];

			Command += TEXT(" ") + Param.ToString();
		}

		typedef NCsConsoleCommand::NLibrary::FLibrary ConsoleCommandLibrary;

		ConsoleCommandLibrary::Exec(this, Command);
	}
}

void UCsWidget_ConsoleCommand::OnPressed_Close()
{
	OnPressed_Close_Event.Broadcast();
}