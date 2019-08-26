// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Enum/CsEnumEditorUtils.h"
#include "CsEditor.h"

#include "GameFramework/InputSettings.h"

#include "AssetRegistryModule.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"

#include "Classes/Engine/UserDefinedEnum.h"
#include "UnrealEd/Public/Kismet2/EnumEditorUtils.h"
#include "UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "CoreUObject/Public/UObject/UObjectIterator.h"
#include "Editor/BlueprintGraph/Classes/NodeDependingOnEnumInterface.h"
#include "Editor/BlueprintGraph/Classes/K2Node_Variable.h"

void FCsEnumEditorUtils::SyncInputAction()
{
	// Populate from DefaultInput.ini
	if (UInputSettings* InputSettings = GetMutableDefault<UInputSettings>())
	{
		const FString EnumPrefixName = TEXT("z_ECsInputAction::");
		const FString EnumeratorPrefixName = TEXT("NewEnumerator");

		TArray<FName> Names;
		TArray<FName> EnumeratorNames;
		int32 Value = 0;
		TMap<FName, FText> DisplayNameMap;

		// Add ActionMappings
		for (const FInputActionKeyMapping& Mapping : InputSettings->ActionMappings)
		{
			const FName& Name = Mapping.ActionName;

			if (Names.Find(Name) > INDEX_NONE)
				continue;

			Names.Add(Name);

			const FName& EnumeratorName	= FName(*(EnumeratorPrefixName + FString::FromInt(Value)));

			EnumeratorNames.Add(EnumeratorName);
			++Value;

			DisplayNameMap.Add(EnumeratorName, FText::FromName(Name));
		}
		// Add AxisMappings
		for (const FInputAxisKeyMapping& Mapping : InputSettings->AxisMappings)
		{
			const FName& Name = Mapping.AxisName;

			if (Names.Find(Name) > INDEX_NONE)
				continue;

			Names.Add(Name);

			const FName& EnumeratorName	= FName(*(EnumeratorPrefixName + FString::FromInt(Value)));

			EnumeratorNames.Add(EnumeratorName);
			++Value;

			DisplayNameMap.Add(EnumeratorName, FText::FromName(Name));
		}

		const FName UserDefinedEnumObjectPath;

		UpdateNames(UserDefinedEnumObjectPath, EnumeratorNames, DisplayNameMap);
	}
	else
	{
		UE_LOG(LogCsEditor, Warning, TEXT("FCsEnumEditorUtils::SyncInputAction: Failed to load Default Object for UInputSettings."));
	}
}

void FCsEnumEditorUtils::UpdateNames(const FName& UserDefinedEnumObjectPath, const TArray<FName>& Names, const TMap<FName, FText>& DisplayNameMap)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(FName("AssetRegistry"));
	TArray<FAssetData> OutAssetData;
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FAssetData Asset = AssetRegistry.GetAssetByObjectPath(UserDefinedEnumObjectPath);

	if (UUserDefinedEnum* Enum = Cast<UUserDefinedEnum>(Asset.GetAsset()))
	{
		// Check if Enum has changed. If so, mark dirty

		TArray<TPair<FName, int64>> OldNames;
		CopyEnumeratorsWithoutMax(Enum, OldNames);

		// Check Names to Remove
		TArray<int32> IndicesToRemove;

		const int32 OldCount = OldNames.Num();
		const int32 NewCount = Names.Num();

		for (int32 I = OldCount - 1; I >= 0; --I)
		{
			const FName OldName			  = GetNameFromNamespacedName(OldNames[I].Key);
			const FString OldNameAsString = Enum->DisplayNameMap[OldName].ToString();

			bool Found = false;

			for (int32 J = 0; J < NewCount; ++J)
			{
				const FName NewName			  = Names[J];
				const FString NewNameAsString = DisplayNameMap[NewName].ToString();

				if (OldNameAsString == NewNameAsString)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
			{
				IndicesToRemove.Add(I);
			}
		}

		// Check Names to Add
		TArray<int32> IndicesToAdd;

		for (int32 I = 0; I < NewCount; ++I)
		{
			const FName& NewName		  = Names[I];
			const FString NewNameAsString = DisplayNameMap[NewName].ToString();

			bool Found = false;

			for (int32 J = 0; J < OldCount; ++J)
			{
				const FName& OldName		  = GetNameFromNamespacedName(OldNames[J].Key);
				const FString OldNameAsString = Enum->DisplayNameMap[OldName].ToString();

				if (OldNameAsString == NewNameAsString)
				{
					Found = true;
					break;
				}
			}

			if (!Found)
			{
				IndicesToAdd.Add(I);
			}
		}

		// Handle changes
		if (IndicesToRemove.Num() > 0 ||
			IndicesToAdd.Num() > 0)
		{
			UE_LOG(LogCsEditor, Warning, TEXT("FCsEnumEditorUtils::UpdateNames: UserDefinedEnum at : %s is being repopulated. This may affect blueprints using it."), *(UserDefinedEnumObjectPath.ToString()));

			// Remove Names
			for (const int32& Index : IndicesToRemove)
			{
				const FString EnumeratorName = Enum->GetNameStringByIndex(Index);
				const FString DisplayName    = Enum->GetDisplayNameTextByIndex(Index).ToString();

				UE_LOG(LogCsEditor, Warning, TEXT("FCsEnumEditorUtils::UpdateNames: UserDefinedEnum at : %s. Removing Enumerator: %s. DisplayName: %s. Index: %d."), *(UserDefinedEnumObjectPath.ToString()), *EnumeratorName, *DisplayName, Index);

				FEnumEditorUtils::RemoveEnumeratorFromUserDefinedEnum(Enum, Index);
			}

			// Add Names
			for (const int32& Index : IndicesToAdd)
			{
				FEnumEditorUtils::AddNewEnumeratorForUserDefinedEnum(Enum);

				const FName& NewName  = Names[Index];
				const int32 LastIndex = Enum->NumEnums() - 2;

				FEnumEditorUtils::SetEnumeratorDisplayName(Enum, LastIndex, DisplayNameMap[NewName]);

				const FString EnumeratorName = Enum->GetNameStringByIndex(LastIndex);
				const FString DisplayName	 = Enum->GetDisplayNameTextByIndex(LastIndex).ToString();

				UE_LOG(LogCsEditor, Warning, TEXT("FCsEnumEditorUtils::UpdateNames: UserDefinedEnum at : %s. Adding Enumerator: %s. DisplayName: %s. Index: %d."), *(UserDefinedEnumObjectPath.ToString()), *EnumeratorName, *DisplayName, LastIndex);
			}

			Enum->MarkPackageDirty();
		}
	}
	else
	{
		if (UserDefinedEnumObjectPath == NAME_None)
		{
			UE_LOG(LogCsEditor, Warning, TEXT("FCsEnumEditorUtils::UpdateNames: No valid UserDefinedEnumObjectPath set."));
		}
		else
		{
			UE_LOG(LogCsEditor, Warning, TEXT("FCsEnumEditorUtils::UpdateNames: Failed to find UserDefinedEnum at: %s. It is possible it was deleted or moved."), *(UserDefinedEnumObjectPath.ToString()));
		}
	}
}

class FArchiveEnumeratorResolver : public FArchiveUObject
{
public:
	const UEnum* Enum;
	const TArray<TPair<FName, int64>>& OldNames;

	FArchiveEnumeratorResolver(const UEnum* InEnum, const TArray<TPair<FName, int64>>& InOldNames)
		: FArchiveUObject(), Enum(InEnum), OldNames(InOldNames)
	{
	}

	virtual bool UseToResolveEnumerators() const override
	{
		return true;
	}
};

struct FEnumEditorUtilsHelper
{
	static const TCHAR* DisplayName() { return TEXT("DisplayName"); }
	static const TCHAR* InvalidName() { return TEXT("(INVALID)"); }
};

void FCsEnumEditorUtils::PrepareForChange(UUserDefinedEnum* Enum)
{
	FEnumEditorUtils::FEnumEditorManager::Get().PreChange(Enum, FEnumEditorUtils::EEnumEditorChangeInfo::Changed);
	Enum->Modify();
}

void FCsEnumEditorUtils::BroadcastChanges(const UUserDefinedEnum* Enum, const TArray<TPair<FName, int64>>& OldNames, bool bResolveData)
{
	check(NULL != Enum);
	if (bResolveData)
	{
		FArchiveEnumeratorResolver EnumeratorResolver(Enum, OldNames);

		TArray<UClass*> ClassesToCheck;
		for (const UByteProperty* ByteProperty : TObjectRange<UByteProperty>())
		{
			if (ByteProperty && (Enum == ByteProperty->GetIntPropertyEnum()))
			{
				UClass* OwnerClass = ByteProperty->GetOwnerClass();
				if (OwnerClass)
				{
					ClassesToCheck.Add(OwnerClass);
				}
			}
		}
		for (const UEnumProperty* EnumProperty : TObjectRange<UEnumProperty>())
		{
			if (EnumProperty && (Enum == EnumProperty->GetEnum()))
			{
				UClass* OwnerClass = EnumProperty->GetOwnerClass();
				if (OwnerClass)
				{
					ClassesToCheck.Add(OwnerClass);
				}
			}
		}

		for (FObjectIterator ObjIter; ObjIter; ++ObjIter)
		{
			for (UClass* Class : ClassesToCheck)
			{
				if (ObjIter->IsA(Class))
				{
					ObjIter->Serialize(EnumeratorResolver);
					break;
				}
			}
		}
	}

	struct FNodeValidatorHelper
	{
		static bool IsValid(UK2Node* Node)
		{
			return Node
				&& (NULL != Cast<UEdGraph>(Node->GetOuter()))
				&& !Node->HasAnyFlags(RF_Transient) && !Node->IsPendingKill();
		}
	};

	TSet<UBlueprint*> BlueprintsToRefresh;

	{
		//CUSTOM NODES DEPENTENT ON ENUM

		for (TObjectIterator<UK2Node> It(RF_Transient); It; ++It)
		{
			UK2Node* Node = *It;
			INodeDependingOnEnumInterface* NodeDependingOnEnum = Cast<INodeDependingOnEnumInterface>(Node);
			if (FNodeValidatorHelper::IsValid(Node) && NodeDependingOnEnum && (Enum == NodeDependingOnEnum->GetEnum()))
			{
				if (Node->HasValidBlueprint())
				{
					if (NodeDependingOnEnum->ShouldBeReconstructedAfterEnumChanged())
					{
						Node->ReconstructNode();
					}
					BlueprintsToRefresh.Add(Node->GetBlueprint());
				}
			}
		}
	}

	for (TObjectIterator<UEdGraphNode> It(RF_Transient); It; ++It)
	{
		for (UEdGraphPin* Pin : It->Pins)
		{
			if (Pin && (Pin->PinType.PinSubCategory != UEdGraphSchema_K2::PSC_Bitmask) && (Enum == Pin->PinType.PinSubCategoryObject.Get()) && (EEdGraphPinDirection::EGPD_Input == Pin->Direction))
			{
				UK2Node* Node = Cast<UK2Node>(Pin->GetOuter());
				if (FNodeValidatorHelper::IsValid(Node))
				{
					if (UBlueprint* Blueprint = Node->GetBlueprint())
					{
						if (INDEX_NONE == Enum->GetIndexByNameString(Pin->DefaultValue))
						{
							Pin->Modify();
							if (Blueprint->BlueprintType == BPTYPE_Interface)
							{
								Pin->DefaultValue = Enum->GetNameStringByIndex(0);
							}
							else
							{
								Pin->DefaultValue = FEnumEditorUtilsHelper::InvalidName();
							}
							Node->PinDefaultValueChanged(Pin);
							BlueprintsToRefresh.Add(Blueprint);
						}
					}
				}
			}
		}
	}

	// Modify any properties that are using the enum as a bitflags type for bitmask values inside a Blueprint class.
	for (TObjectIterator<UIntProperty> PropertyIter; PropertyIter; ++PropertyIter)
	{
		const UIntProperty* IntProperty = *PropertyIter;
		if (IntProperty && IntProperty->HasMetaData(*FBlueprintMetadata::MD_Bitmask.ToString()))
		{
			UClass* OwnerClass = IntProperty->GetOwnerClass();
			if (OwnerClass)
			{
				// Note: We only need to consider the skeleton class here.
				UBlueprint* Blueprint = Cast<UBlueprint>(OwnerClass->ClassGeneratedBy);
				if (Blueprint && OwnerClass == Blueprint->SkeletonGeneratedClass)
				{
					const FString& BitmaskEnumName = IntProperty->GetMetaData(FBlueprintMetadata::MD_BitmaskEnum);
					if (BitmaskEnumName == Enum->GetName() && !Enum->HasMetaData(*FBlueprintMetadata::MD_Bitflags.ToString()))
					{
						FName VarName = IntProperty->GetFName();

						// This will remove the metadata key from both the skeleton & full class.
						FBlueprintEditorUtils::RemoveBlueprintVariableMetaData(Blueprint, VarName, nullptr, FBlueprintMetadata::MD_BitmaskEnum);

						// Need to reassign the property since the skeleton class will have been regenerated at this point.
						IntProperty = FindFieldChecked<UIntProperty>(Blueprint->SkeletonGeneratedClass, VarName);

						// Reconstruct any nodes that reference the variable that was just modified.
						for (TObjectIterator<UK2Node_Variable> VarNodeIt; VarNodeIt; ++VarNodeIt)
						{
							UK2Node_Variable* VarNode = *VarNodeIt;
							if (VarNode && VarNode->GetPropertyForVariable() == IntProperty)
							{
								VarNode->ReconstructNode();

								BlueprintsToRefresh.Add(VarNode->GetBlueprint());
							}
						}

						BlueprintsToRefresh.Add(Blueprint);
					}
				}
			}
		}
	}

	for (auto It = BlueprintsToRefresh.CreateIterator(); It; ++It)
	{
		FBlueprintEditorUtils::MarkBlueprintAsModified(*It);
		(*It)->BroadcastChanged();
	}

	FEnumEditorUtils::FEnumEditorManager::Get().PostChange(Enum, FEnumEditorUtils::EEnumEditorChangeInfo::Changed);
}

void FCsEnumEditorUtils::CopyEnumeratorsWithoutMax(const UEnum* Enum, TArray<TPair<FName, int64>>& OutEnumNames)
{
	const int32 Count = Enum->NumEnums() - 1;
	for (int32 I = 0; I < Count; ++I)
	{
		OutEnumNames.Emplace(Enum->GetNameByIndex(I), Enum->GetValueByIndex(I));
	}
}

FName FCsEnumEditorUtils::GetNameFromNamespacedName(const FName& Name)
{
	const FString NameAsString = Name.ToString();

	int32 ScopeIndex = NameAsString.Find(TEXT("::"), ESearchCase::CaseSensitive);
	if (ScopeIndex != INDEX_NONE)
	{
		return FName(*NameAsString.Mid(ScopeIndex + 2));
	}
	return Name;
}