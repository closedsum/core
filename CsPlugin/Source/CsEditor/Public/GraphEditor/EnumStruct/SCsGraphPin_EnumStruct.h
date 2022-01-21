// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "SGraphPin.h"
#include "SGraphPinComboBox.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"
#include "ScopedTransaction.h"

#include "Types/CsTypes_Macro.h"

#pragma region

namespace NCsGraphPinEnumStructCached
{
	namespace Str
	{
		extern CSEDITOR_API const FString INVALID;;
	}

	namespace Txt
	{
		extern CSEDITOR_API const FText INVALID;
	}
}

#pragma endregion Cache

class CSEDITOR_API SCsGraphPin_EnumStruct : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SCsGraphPin_EnumStruct) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);

protected:

	virtual void CustomPopulateEnumMap();

	template<typename EnumMap, typename EnumStruct>
	void Construct_Internal()
	{
		CustomPopulateEnumMap();

		FString CurrentDefaultValue = GraphPinObj->GetDefaultAsString();

		if (CurrentDefaultValue.IsEmpty())
		{
			if (EnumMap::Get().Num() > CS_EMPTY)
			{
				const EnumStruct& Enum = EnumMap::Get().GetEnumAt(CS_FIRST);
				CurrentDefaultValue    = Enum.ToGraphPinString();

				GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, CurrentDefaultValue);
			}
		}
	}

	/**
	*	Function to create class specific widget.
	*
	*	@return Reference to the newly created widget object
	*/
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;

	/**
	*	Function to generate the list of indexes from the enum object
	*
	*	@param OutComboBoxIndexes - Int array reference to store the list of indexes
	*/
	virtual void GenerateComboBoxIndexes(TArray<TSharedPtr<int32>>& OutComboBoxIndexes);

	template<typename EnumMap>
	void GenenerateComboBoxIndexes_Internal(TArray<TSharedPtr<int32>>& OutComboBoxIndexes)
	{
		const int32& Count = EnumMap::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			TSharedPtr<int32> IdxPtr(new int32(I));
			OutComboBoxIndexes.Add(IdxPtr);
		}
	}

	/**
	*	Function to get current string associated with the combo box selection
	*
	*	@return currently selected string
	*/
	virtual FString OnGetText() const;

	template<typename EnumMap, typename EnumStruct>
	FString OnGetText_Internal() const
	{
		FString SelectedString = GraphPinObj->GetDefaultAsString();

		EnumMap& Map		= EnumMap::Get();
		const int32& Count	= Map.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const EnumStruct& Enum		 = Map.GetEnumAt(I);
			const FString GraphPinString = Enum.ToGraphPinString();

			if (SelectedString == GraphPinString)
			{
				return Enum.GetDisplayName();
			}
		}
		return NCsGraphPinEnumStructCached::Str::INVALID;
	}

	/**
	*	Function to set the newly selected index
	*
	* @param NewSelection The newly selected item in the combo box
	* @param SelectInfo Provides context on how the selection changed
	*/
	virtual void ComboBoxSelectionChanged(TSharedPtr<int32> NewSelection, ESelectInfo::Type SelectInfo);

	template<typename EnumMap, typename EnumStruct>
	void ComboBoxSelectionChanged_Internal(TSharedPtr<int32> NewSelection, const ESelectInfo::Type& SelectInfo)
	{
		FString EnumSelectionString;

		if (NewSelection.IsValid())
		{
			const EnumStruct& Enum = EnumMap::Get().GetSafeEnumAt(*NewSelection);
			EnumSelectionString	   = Enum.ToGraphPinString();
		}
		else
		{
			EnumSelectionString = TEXT("(Value=0,Name_Internal=\"None\")");;
		}

		if (GraphPinObj->GetDefaultAsString() != EnumSelectionString)
		{
			const FScopedTransaction Transaction(NSLOCTEXT("GraphEditor", "ChangeEnumStructPinValue", "Change EnumStruct Pin Value"));
			GraphPinObj->Modify();

			// Set new selection
			GraphPinObj->GetSchema()->TrySetDefaultValue(*GraphPinObj, EnumSelectionString);
		}
	}

	/**
	* Returns the friendly name of the enum at index EnumIndex
	*
	* @param EnumIndex	- The index of the enum to return the friendly name for
	*/
	virtual FText OnGetFriendlyName(int32 EnumIndex);

	template<typename EnumMap>
	FText OnGetFriendlyName_Internal(const int32& EnumIndex)
	{
		return FText::FromString(EnumMap::Get().GetSafeEnumAt(EnumIndex).GetDisplayName());
	}

	/**
	* Returns the tooltip of the enum at index EnumIndex
	*
	* @param EnumIndex	- The index of the enum to return the tooltip for
	*/
	virtual FText OnGetTooltip(int32 EnumIndex);

	template<typename EnumMap>
	FText OnGetTooltip_Internal(const int32& EnumIndex)
	{
		return FText::FromString(EnumMap::Get().GetSafeEnumAt(EnumIndex).GetDisplayName());
	}

	TSharedPtr<class SPinComboBox>ComboBox;
};