#include "Data/CsData_Payload.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#if WITH_EDITOR
#include "Data/CsDataMapping.h"
#endif WITH_EDITOR

ACsData_Payload::ACsData_Payload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// 98 Editor
#pragma region

#if WITH_EDITOR

bool ACsData_Payload::PerformFindEntry(const FName &InShortCode, TArray<FCsPayload*> &OutPayloads, TArray<FECsLoadAssetsType> &OutLoadAssetsTypes, TArray<int32> &OutIndices)
{
	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{
				const uint8 LoadAssetsTypeCount = EMCsLoadAssetsType::Get().Num();

				if (StructProperty->ArrayDim == LoadAssetsTypeCount)
				{
					CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LoadAssetsTypeCount)

					if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
					{
						// Find LoadAssetsType
						for (int32 I = 0; I < LoadAssetsTypeCount; ++I)
						{
							TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;

							const FECsLoadAssetsType& LoadAssetsType = EMCsLoadAssetsType::Get().GetEnumAt(I);

							bool Found = false;

							const int32 ArraySize = Array.Num();

							for (int32 J = 0; J < ArraySize; J++)
							{
								FCsPayload& Payload = Array[J];

								if (InShortCode == Payload.ShortCode)
								{
									OutPayloads.Add(&Payload);
									OutLoadAssetsTypes.Add(LoadAssetsType);
									OutIndices.Add(J);
								}
							}
						}
					}
				}
			}
		}
	}
	return OutPayloads.Num() > CS_EMPTY;
}

bool ACsData_Payload::PerformAddEntry(const FName &InShortCode, const FECsLoadAssetsType &LoadAssetsType, const TEnumAsByte<ECsLoadFlags_Editor::Type> &LoadFlags, FString &OutMessage, FString &OutOutput)
{
	// Check for VALID ShortCode
	if (InShortCode == NAME_None ||
		InShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput  = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}
	// Check for VALID LoadAssetsType
	if (!EMCsLoadAssetsType::Get().IsValidEnum(LoadAssetsType))
	{
		OutMessage = TEXT("INVALID LoadAssetsType. See Output Log.");
		OutOutput  = TEXT("ERROR");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
		}

		UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::PerformAddEntry: Valid LoadAssetsTypes are:"));

		const int32& Count = EMCsLoadAssetsType::Get().Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FECsLoadAssetsType& Enum = EMCsLoadAssetsType::Get().GetEnumAt(I);

			UE_LOG(LogCs, Warning, TEXT("LoadAssetsType: %s"), *(Enum.Name));
		}
		return false;
	}

	// Check if ShortCode has ALREADY been ADDED
	TArray<FCsPayload*> OutPayloads;
	TArray<FECsLoadAssetsType> OutLoadAssetsTypes;
	TArray<int32> OutIndices;

	PerformFindEntry(InShortCode, OutPayloads, OutLoadAssetsTypes, OutIndices);

	const int32 PayloadCount = OutPayloads.Num();
	// Entries Found
	if (PayloadCount > CS_EMPTY)
	{
		const int32 Index = OutLoadAssetsTypes.Find(LoadAssetsType);

		if (Index != INDEX_NONE)
		{
			const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(LoadFlags);
			const FString& LoadAssetsTypeAsString = OutLoadAssetsTypes[Index].Name;

			FCsPayload* Payload = OutPayloads[Index];

			const FString AssetTypeAsString = Payload->AssetType;

			OutOutput += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[Index]) + TEXT("]");
			OutMessage = TEXT("Already Exists.");

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
			}
			return false;
		}
	}
	// Attempt to ADD it

	// Check ShortCode entry EXISTS in DataMapping
	ACsDataMapping* DataMapping = GetDataMapping();

	TArray<FCsDataMappingEntry*> OutEntries;
	TArray<FECsAssetType> OutAssetTypes;
	OutIndices.Reset();

	DataMapping->PerformFindEntry(InShortCode, OutEntries, OutAssetTypes, OutIndices);

	const int32 EntryCount = OutEntries.Num();

	// Entries in DataMapping Found
	if (EntryCount > CS_EMPTY)
	{
		// ADD
		if (EntryCount == 1)
		{
			// Check LoadFlags
			const ECsLoadFlags Flags = ECsLoadFlags_Editor::ToBaseType(LoadFlags);

			if (!CS_TEST_BLUEPRINT_BITFLAG(OutEntries[CS_FIRST]->Data_LoadFlags, Flags))
			{
				CS_SET_BLUEPRINT_BITFLAG(OutEntries[CS_FIRST]->Data_LoadFlags, Flags);

				const FString& LoadFlagsAsString = EMCsLoadFlags_Editor::Get().ToString(LoadFlags);
				const FString& AssetTypeAsString = OutAssetTypes[CS_FIRST].Name;

				const FString Output = TEXT("ACsData_Payload::PostEditChangeProperty: Missing LoadFlags: ") + LoadFlagsAsString + TEXT(" in DataMapping: [") + AssetTypeAsString + TEXT(",") + InShortCode.ToString() + TEXT(",") + FString::FromInt(OutIndices[CS_FIRST]) + TEXT("]. Manually adding LoadFlag: ") + LoadFlagsAsString + TEXT(".");
					
				if (UCsCommon::IsDefaultObject(this))
					UCsCommon::DisplayNotificationInfo(Output, TEXT("Payload"), TEXT("PerformAddEntryLoadFlags"), 1.5f);

				UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
			}

			UClass* Class = GetClass();

			for (TFieldIterator<UProperty> It(Class); It; ++It)
			{
				UProperty* Property = Cast<UProperty>(*It);

				const FString MemberName = Property->GetName();

				// Struct
				if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
				{
					// FCsTArrayPayload
					if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
					{
						const uint8 LoadAssetsTypeCount = EMCsLoadAssetsType::Get().Num();

						if (StructProperty->ArrayDim == LoadAssetsTypeCount)
						{
							CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LoadAssetsTypeCount)

							if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
							{
								TArray<FCsPayload>& Array = ((*Member)[(uint8)LoadAssetsType]).Payloads;

								const int32 ArraySize = Array.Num();

								const FString& AssetTypeAsString = OutAssetTypes[CS_FIRST].Name;

								Array.AddDefaulted();
								Array[ArraySize].AssetType  = OutAssetTypes[CS_FIRST];
								Array[ArraySize].ShortCode	= InShortCode;
								Array[ArraySize].LoadFlags	= LoadFlags;

								const FString& LoadAssetsTypeAsString = LoadAssetsType.Name;
								const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(LoadFlags);

								OutOutput = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
								OutMessage = TEXT("SUCCESS.");

								if (UCsCommon::IsDefaultObject(this))
								{
									UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
									UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
								}
								MarkPackageDirty();
							}
						}
					}
				}
			}
		}
		// Multiple in DataMapping
		else
		{
			bool IsAssetTypeMismatch   = false;
			FECsAssetType LastAssetType = OutAssetTypes[CS_FIRST];

			for (int32 I = 0; I < EntryCount; ++I)
			{
				const FString& AssetTypeAsString = OutAssetTypes[I].Name;

				OutOutput += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");

				if (LastAssetType != OutAssetTypes[I])
					IsAssetTypeMismatch |= true;
				LastAssetType = OutAssetTypes[I];
			}

			OutMessage = TEXT("Can NOT ADD. WARNING, Duplicates. REMOVE extra entries in DataMapping.");

			if (IsAssetTypeMismatch)
				OutMessage += TEXT(" ShortCode listed under multiple AssetTypes in DataMapping. Should ONLY be ONE.");

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
			}
			return false;
		}
	}
	// Search for Asset in AssetRegistry, ADD it to DataMapping, and ADD Payload Entry
	else
	{
		int32 Flags = 0;
		CS_SET_BLUEPRINT_BITFLAG(Flags, LoadFlags);

		bool Successful = DataMapping->PerformAddEntry(InShortCode, Flags, OutMessage, OutOutput);

		if (Successful)
		{
			DataMapping->GenerateMaps();

			OutEntries.Reset();
			OutAssetTypes.Reset();
			OutIndices.Reset();

			DataMapping->PerformFindEntry(InShortCode, OutEntries, OutAssetTypes, OutIndices);

			UClass* Class = GetClass();

			for (TFieldIterator<UProperty> It(Class); It; ++It)
			{
				UProperty* Property = Cast<UProperty>(*It);

				const FString MemberName = Property->GetName();

				// Struct
				if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
				{
					// FCsTArrayPayload
					if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
					{
						const uint8 LoadAssetsTypeCount = EMCsLoadAssetsType::Get().Num();

						if (StructProperty->ArrayDim == LoadAssetsTypeCount)
						{
							CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LoadAssetsTypeCount)

							if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
							{
								TArray<FCsPayload>& Array = ((*Member)[(uint8)LoadAssetsType]).Payloads;

								const int32 ArraySize = Array.Num();

								const FString& AssetTypeAsString = OutAssetTypes[CS_FIRST].Name;

								Array.AddDefaulted();
								Array[ArraySize].AssetType	= OutAssetTypes[CS_FIRST];
								Array[ArraySize].ShortCode	= InShortCode;
								Array[ArraySize].LoadFlags	= LoadFlags;

								const FString& LoadAssetsTypeAsString = LoadAssetsType.Name;
								const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(LoadFlags);

								OutOutput  = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
								OutMessage = TEXT("SUCCESS. Check LOG.");

								MarkPackageDirty();
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool ACsData_Payload::Editor_IsValid(ACsDataMapping* DataMapping)
{
	bool Pass = true;

	UClass* Class = GetClass();

	for (TFieldIterator<UProperty> It(Class); It; ++It)
	{
		UProperty* Property = Cast<UProperty>(*It);

		const FString MemberName = Property->GetName();

		// Struct
		if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
		{
			// FCsTArrayPayload
			if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
			{
				const uint8 LoadAssetsTypeCount = EMCsLoadAssetsType::Get().Num();

				if (StructProperty->ArrayDim == LoadAssetsTypeCount)
				{
					CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LoadAssetsTypeCount)

					if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
					{
						// TArray<FCsPayload>
						for (int32 I = 0; I < MAX; ++I)
						{
							TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;
							const int32 ArraySize	  = Array.Num();

							const FECsLoadAssetsType& LoadAssetsType = EMCsLoadAssetsType::Get().GetEnumAt(I);
							const FString LoadAssetsTypeAsString	 = LoadAssetsType.Name;

							// FCsPayload
							for (int32 J = 0; J < ArraySize; J++)
							{
								const FString AssetTypeAsString = Array[J].AssetType;
								const FString _ShortCodeAsString = Array[J].ShortCode.ToString();

								TArray<FCsDataMappingEntry*> OutEntries;
								TArray<FECsAssetType> OutAssetTypes;
								TArray<int32> OutIndices;

								// Search in DataMapping
								if (DataMapping->PerformFindEntry(Array[J].ShortCode, OutEntries, OutAssetTypes, OutIndices))
								{
									// Check Multiple Entries in DataMapping
									const int32 EntryCount = OutEntries.Num();

									if (EntryCount > 1)
									{
										UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::Editor_IsValid: [%s, %s, %d] Multiple entries found for ShortCode: %s in DataMapping. Fix DataMapping."), *LoadAssetsTypeAsString, *_ShortCodeAsString, J, *_ShortCodeAsString);

										for (int32 K = 0; K < EntryCount; K++)
										{
											const FString& OutAssetTypeAsString = OutAssetTypes[K].Name;

											UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::Editor_IsValid: In DataMapping, ShortCode: %s at [%s, %d]."), *_ShortCodeAsString, *OutAssetTypeAsString, K);
										}
									}
									else
									{
										// Check AssetType Mismatch
										const FString& OutAssetTypeAsString = OutAssetTypes[CS_FIRST].Name;

										if (AssetTypeAsString != OutAssetTypeAsString)
										{
											UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::Editor_IsValid: [%s, %s, %d] AssetType Mismatch for ShortCode: %s. %s != %s"), *LoadAssetsTypeAsString, *_ShortCodeAsString, J, *_ShortCodeAsString, *AssetTypeAsString, *OutAssetTypeAsString);
											Pass &= false;
										}
										// Check for LoadFlags
										if (!CS_TEST_BLUEPRINT_BITFLAG(OutEntries[CS_FIRST]->Data_LoadFlags, Array[J].LoadFlags))
										{
											const FString DataLoadFlagsAsString    = EMCsLoadFlags::Get().MaskToString(OutEntries[CS_FIRST]->Data_LoadFlags);
											const FString& PayloadLoadFlagsAsString = EMCsLoadFlags_Editor::Get().ToString(Array[J].LoadFlags);

											UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::Editor_IsValid: [%s, %s, %d] LoadFlags NOT present in DataMapping Entry [%s, %d]. (%s) does NOT containt %s"), *LoadAssetsTypeAsString, *_ShortCodeAsString, J, *OutAssetTypeAsString, OutIndices[CS_FIRST], *DataLoadFlagsAsString, *PayloadLoadFlagsAsString);
											Pass &= false;
										}
									}
								}
								else
								{
									UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::Editor_IsValid: [%s, %s, %d] ShortCode: %s NOT Found in DataMapping."), *LoadAssetsTypeAsString, *ShortCodeAsString, J, *ShortCodeAsString);
									Pass &= false;
								}
							}
						}
					}
				}
			}
		}
	}
	return Pass;
}

void ACsData_Payload::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Find Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadFindEntry, Find))
	{
		if (!FindEntry.Find)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		FindEntry.Message = TEXT("");
		FindEntry.Output  = TEXT("");

		// Check for VALID ShortCode
		if (FindEntry.ShortCode == NAME_None ||
			FindEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			FindEntry.Message = TEXT("INVALID ShortCode.");
			FindEntry.Output = TEXT("ERROR");
			FindEntry.Find = false;

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(FindEntry.Output, TEXT("Payload"), TEXT("FindEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(FindEntry.Message, TEXT("Payload"), TEXT("FindEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}

		TArray<FCsPayload*> OutPayloads;
		TArray<FECsLoadAssetsType> OutLoadAssetsTypes;
		TArray<int32> OutIndices;

		PerformFindEntry(FindEntry.ShortCode, OutPayloads, OutLoadAssetsTypes, OutIndices);

		const int32 PayloadCount = OutPayloads.Num();

		for (int32 I = 0; I < PayloadCount; ++I)
		{
			if (I > 0)
				FindEntry.Output += TEXT(", ");

			const FString& LoadAssetsTypeAsString = OutLoadAssetsTypes[I].Name;
			const FString& AssetTypeAsString	  = OutPayloads[I]->AssetType;
			const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(OutPayloads[I]->LoadFlags);

			FindEntry.Output += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");
		}

		if (PayloadCount == CS_EMPTY)
			FindEntry.Output = TEXT("No Results.");
		FindEntry.Message = TEXT("SUCCESS");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(FindEntry.Output, TEXT("Payload"), TEXT("FindEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(FindEntry.Message, TEXT("Payload"), TEXT("FindEntryMessage"), 5.0f);
		}
		FindEntry.Find = false;
	}
	// Add Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadAddEntry, Add))
	{
		if (!AddEntry.Add)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		AddEntry.Message = TEXT("");
		AddEntry.Output  = TEXT("");

		const FECsLoadAssetsType& LoadAssetsType = AddEntry.LoadAssetsType;

		PerformAddEntry(AddEntry.ShortCode, LoadAssetsType, AddEntry.LoadFlags, AddEntry.Message, AddEntry.Output);
		AddEntry.Add = false;
	}
	// Remove Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadRemoveEntry, Remove))
	{
		if (!RemoveEntry.Remove)
		{
			Super::PostEditChangeProperty(e);
			return;
		}

		RemoveEntry.Message = TEXT("");
		RemoveEntry.Output  = TEXT("");

		// Check for VALID ShortCode
		if (RemoveEntry.ShortCode == NAME_None ||
			RemoveEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			RemoveEntry.Message = TEXT("INVALID ShortCode.");
			RemoveEntry.Output = TEXT("ERROR");
			RemoveEntry.Remove = false;

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(RemoveEntry.Output, TEXT("Payload"), TEXT("RemoveEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(RemoveEntry.Message, TEXT("Payload"), TEXT("RemoveEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}
		// Check for VALID LoadAssetsType
		const FECsLoadAssetsType& LoadAssetsType = RemoveEntry.LoadAssetsType;

		if (!EMCsLoadAssetsType::Get().IsValidEnum(LoadAssetsType))
		{
			RemoveEntry.Message = TEXT("INVALID LoadAssetsType. See Output Log.");
			RemoveEntry.Output  = TEXT("ERROR");
			RemoveEntry.Remove	= false;

			if (UCsCommon::IsDefaultObject(this))
			{
				UCsCommon::DisplayNotificationInfo(RemoveEntry.Output, TEXT("Payload"), TEXT("RemoveEntryOutput"), 5.0f);
				UCsCommon::DisplayNotificationInfo(RemoveEntry.Message, TEXT("Payload"), TEXT("RemoveEntryMessage"), 5.0f);
			}

			FString Output = TEXT("ACsData_Payload::PostEditChangeProperty: Valid LoadAssetsTypes are:");

			if (UCsCommon::IsDefaultObject(this))
				UCsCommon::DisplayNotificationInfo(Output, TEXT("Payload"), TEXT("RemoveEntryAdditionalOutput"), 1.5f);

			UE_LOG(LogCs, Warning, TEXT("%s"), *Output);

			const int32& Count = EMCsLoadAssetsType::Get().Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FECsLoadAssetsType& Enum = EMCsLoadAssetsType::Get().GetEnumAt(I);
				Output						   = TEXT("LoadAssetsType: ") + Enum.Name;

				if (UCsCommon::IsDefaultObject(this))
				{
					const FString AdditionalOutput = TEXT("RemoveEntryAdditionalOutput") + FString::FromInt(I);

					UCsCommon::DisplayNotificationInfo(Output, TEXT("Payload"), AdditionalOutput, 1.5f);
				}
				UE_LOG(LogCs, Warning, TEXT("%s"), *Output);
			}

			Super::PostEditChangeProperty(e);
			return;
		}

		UClass* Class = GetClass();

		for (TFieldIterator<UProperty> It(Class); It; ++It)
		{
			UProperty* Property = Cast<UProperty>(*It);

			const FString MemberName = Property->GetName();

			// Struct
			if (UStructProperty* StructProperty = Cast<UStructProperty>(*It))
			{
				// FCorgiTArrayPayload
				if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
				{
					const uint8 LoadAssetTypeCount = EMCsLoadAssetsType::Get().Num();

					if (StructProperty->ArrayDim == LoadAssetTypeCount)
					{
						CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LoadAssetTypeCount)

						if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
						{
							// Find LoadAssetsType
							for (int32 I = 0; I < LoadAssetTypeCount; ++I)
							{
								TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;

								const FECsLoadAssetsType& AssetsType = EMCsLoadAssetsType::Get().GetEnumAt(I);

								if (AssetsType != LoadAssetsType)
									continue;

								const FString& LoadAssetsTypeAsString = LoadAssetsType.Name;

								bool Found = false;

								const int32 ArraySize = Array.Num();

								for (int32 J = ArraySize - 1; J >= 0; --J)
								{
									FCsPayload& Payload = Array[J];

									if (RemoveEntry.ShortCode == Payload.ShortCode)
									{
										if (Found)
											RemoveEntry.Output += TEXT(", ");

										const FString& AssetTypeAsString = Payload.AssetType;
										const FString& LoadFlagsAsString = EMCsLoadFlags_Editor::Get().ToString(Payload.LoadFlags);

										RemoveEntry.Output += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(J) + TEXT("]");

										Found = true;

										Array.RemoveAt(J);
									}
								}
							}
						}
					}
				}
			}
		}

		if (RemoveEntry.Output == TEXT(""))
			RemoveEntry.Output = TEXT("Nothing Removed.");
		RemoveEntry.Message = TEXT("SUCCESS");

		if (UCsCommon::IsDefaultObject(this))
		{
			UCsCommon::DisplayNotificationInfo(RemoveEntry.Output, TEXT("Payload"), TEXT("RemoveEntryOutput"), 5.0f);
			UCsCommon::DisplayNotificationInfo(RemoveEntry.Message, TEXT("Payload"), TEXT("RemoveEntryMessage"), 5.0f);
		}
		RemoveEntry.Remove = false;
	}
	// Validate
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadValidate, Validate))
	{
	}
	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR

#pragma endregion 98 Editor