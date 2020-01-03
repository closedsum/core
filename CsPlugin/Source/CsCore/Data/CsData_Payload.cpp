#include "Data/CsData_Payload.h"
#include "CsCore.h"
#include "Library/CsLibrary_Common.h"

#if WITH_EDITOR
#include "Data/CsDataMapping.h"
#endif WITH_EDITOR

UCsData_Payload::UCsData_Payload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// 98 Editor
#pragma region

#if WITH_EDITOR

bool UCsData_Payload::PerformFindEntry(const FName& InShortCode, TArray<FCsPayload*>& OutPayloads, TArray<FECsLoadAssetsType>& OutLoadAssetsTypes, TArray<int32>& OutIndices)
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

bool UCsData_Payload::PerformAddEntry(const FName& InShortCode, const FECsLoadAssetsType& LoadAssetsType, const TEnumAsByte<ECsLoadFlags_Editor::Type>& LoadFlags, FString& OutMessage, FString& OutOutput)
{
	// Check for VALID ShortCode
	if (InShortCode == NAME_None ||
		InShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput  = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
		}
		return false;
	}
	// Check for VALID LoadAssetsType
	if (!EMCsLoadAssetsType::Get().IsValidEnum(LoadAssetsType))
	{
		OutMessage = TEXT("INVALID LoadAssetsType. See Output Log.");
		OutOutput  = TEXT("ERROR");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
			UCsLibrary_Common::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
		}

		UE_LOG(LogCs, Warning, TEXT("UCsData_Payload::PerformAddEntry: Valid LoadAssetsTypes are:"));

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

			const FString& DataTypeAsString = Payload->DataType;

			OutOutput += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + DataTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[Index]) + TEXT("]");
			OutMessage = TEXT("Already Exists.");

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
			}
			return false;
		}
	}
	// Attempt to ADD it

	// Check ShortCode entry EXISTS in DataMapping
	UCsDataMapping* DataMapping = GetDataMapping();

	TArray<FCsDataMappingEntry*> OutEntries;
	TArray<FECsDataType> OutDataTypes;
	OutIndices.Reset();

	DataMapping->PerformFindEntry(InShortCode, OutEntries, OutDataTypes, OutIndices);

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
				const FString& DataTypeAsString = OutDataTypes[CS_FIRST].Name;

				const FString Output = TEXT("UCsData_Payload::PostEditChangeProperty: Missing LoadFlags: ") + LoadFlagsAsString + TEXT(" in DataMapping: [") + DataTypeAsString + TEXT(",") + InShortCode.ToString() + TEXT(",") + FString::FromInt(OutIndices[CS_FIRST]) + TEXT("]. Manually adding LoadFlag: ") + LoadFlagsAsString + TEXT(".");
					
				if (UCsLibrary_Common::IsDefaultObject(this))
					UCsLibrary_Common::DisplayNotificationInfo(Output, TEXT("Payload"), TEXT("PerformAddEntryLoadFlags"), 1.5f);

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

								const FString& DataTypeAsString = OutDataTypes[CS_FIRST].Name;

								Array.AddDefaulted();
								Array[ArraySize].DataType  = OutDataTypes[CS_FIRST];
								Array[ArraySize].ShortCode	= InShortCode;
								Array[ArraySize].LoadFlags	= LoadFlags;

								const FString& LoadAssetsTypeAsString = LoadAssetsType.Name;
								const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(LoadFlags);

								OutOutput = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + DataTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
								OutMessage = TEXT("SUCCESS.");

								if (UCsLibrary_Common::IsDefaultObject(this))
								{
									UCsLibrary_Common::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
									UCsLibrary_Common::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
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
			bool IsDataTypeMismatch   = false;
			FECsDataType LastDataType = OutDataTypes[CS_FIRST];

			for (int32 I = 0; I < EntryCount; ++I)
			{
				const FString& DataTypeAsString = OutDataTypes[I].Name;

				OutOutput += TEXT("[") + DataTypeAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");

				if (LastDataType != OutDataTypes[I])
					IsDataTypeMismatch |= true;
				LastDataType = OutDataTypes[I];
			}

			OutMessage = TEXT("Can NOT ADD. WARNING, Duplicates. REMOVE extra entries in DataMapping.");

			if (IsDataTypeMismatch)
				OutMessage += TEXT(" ShortCode listed under multiple DataTypes in DataMapping. Should ONLY be ONE.");

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(OutOutput, TEXT("Payload"), TEXT("PerformAddEntryOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(OutMessage, TEXT("Payload"), TEXT("PerformAddEntryMessage"), 5.0f);
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
			OutDataTypes.Reset();
			OutIndices.Reset();

			DataMapping->PerformFindEntry(InShortCode, OutEntries, OutDataTypes, OutIndices);

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

								const FString& DataTypeAsString = OutDataTypes[CS_FIRST].Name;

								Array.AddDefaulted();
								Array[ArraySize].DataType	= OutDataTypes[CS_FIRST];
								Array[ArraySize].ShortCode	= InShortCode;
								Array[ArraySize].LoadFlags	= LoadFlags;

								const FString& LoadAssetsTypeAsString = LoadAssetsType.Name;
								const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(LoadFlags);

								OutOutput  = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + DataTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
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

bool UCsData_Payload::Editor_IsValid(UCsDataMapping* DataMapping)
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
								const FString DataTypeAsString  = Array[J].DataType;
								const FString _ShortCodeAsString = Array[J].ShortCode.ToString();

								TArray<FCsDataMappingEntry*> OutEntries;
								TArray<FECsDataType> OutDataTypes;
								TArray<int32> OutIndices;

								// Search in DataMapping
								if (DataMapping->PerformFindEntry(Array[J].ShortCode, OutEntries, OutDataTypes, OutIndices))
								{
									// Check Multiple Entries in DataMapping
									const int32 EntryCount = OutEntries.Num();

									if (EntryCount > 1)
									{
										UE_LOG(LogCs, Warning, TEXT("UCsData_Payload::Editor_IsValid: [%s, %s, %d] Multiple entries found for ShortCode: %s in DataMapping. Fix DataMapping."), *LoadAssetsTypeAsString, *_ShortCodeAsString, J, *_ShortCodeAsString);

										for (int32 K = 0; K < EntryCount; K++)
										{
											const FString& OutDataTypeAsString = OutDataTypes[K].Name;

											UE_LOG(LogCs, Warning, TEXT("UCsData_Payload::Editor_IsValid: In DataMapping, ShortCode: %s at [%s, %d]."), *_ShortCodeAsString, *OutDataTypeAsString, K);
										}
									}
									else
									{
										// Check DataType Mismatch
										const FString& OutDataTypeAsString = OutDataTypes[CS_FIRST].Name;

										if (DataTypeAsString != OutDataTypeAsString)
										{
											UE_LOG(LogCs, Warning, TEXT("UCsData_Payload::Editor_IsValid: [%s, %s, %d] DataType Mismatch for ShortCode: %s. %s != %s"), *LoadAssetsTypeAsString, *_ShortCodeAsString, J, *_ShortCodeAsString, *DataTypeAsString, *OutDataTypeAsString);
											Pass &= false;
										}
										// Check for LoadFlags
										if (!CS_TEST_BLUEPRINT_BITFLAG(OutEntries[CS_FIRST]->Data_LoadFlags, Array[J].LoadFlags))
										{
											const FString DataLoadFlagsAsString    = EMCsLoadFlags::Get().MaskToString(OutEntries[CS_FIRST]->Data_LoadFlags);
											const FString& PayloadLoadFlagsAsString = EMCsLoadFlags_Editor::Get().ToString(Array[J].LoadFlags);

											UE_LOG(LogCs, Warning, TEXT("UCsData_Payload::Editor_IsValid: [%s, %s, %d] LoadFlags NOT present in DataMapping Entry [%s, %d]. (%s) does NOT containt %s"), *LoadAssetsTypeAsString, *_ShortCodeAsString, J, *OutDataTypeAsString, OutIndices[CS_FIRST], *DataLoadFlagsAsString, *PayloadLoadFlagsAsString);
											Pass &= false;
										}
									}
								}
								else
								{
									UE_LOG(LogCs, Warning, TEXT("UCsData_Payload::Editor_IsValid: [%s, %s, %d] ShortCode: %s NOT Found in DataMapping."), *LoadAssetsTypeAsString, *ShortCodeAsString, J, *ShortCodeAsString);
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

void UCsData_Payload::PostEditChangeProperty(struct FPropertyChangedEvent& e)
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

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(FindEntry.Output, TEXT("Payload"), TEXT("FindEntryOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(FindEntry.Message, TEXT("Payload"), TEXT("FindEntryMessage"), 5.0f);
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
			const FString& DataTypeAsString		  = OutPayloads[I]->DataType;
			const FString& LoadFlagsAsString	  = EMCsLoadFlags_Editor::Get().ToString(OutPayloads[I]->LoadFlags);

			FindEntry.Output += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + DataTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");
		}

		if (PayloadCount == CS_EMPTY)
			FindEntry.Output = TEXT("No Results.");
		FindEntry.Message = TEXT("SUCCESS");

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common::DisplayNotificationInfo(FindEntry.Output, TEXT("Payload"), TEXT("FindEntryOutput"), 5.0f);
			UCsLibrary_Common::DisplayNotificationInfo(FindEntry.Message, TEXT("Payload"), TEXT("FindEntryMessage"), 5.0f);
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

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(RemoveEntry.Output, TEXT("Payload"), TEXT("RemoveEntryOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(RemoveEntry.Message, TEXT("Payload"), TEXT("RemoveEntryMessage"), 5.0f);
			}
			Super::PostEditChangeProperty(e);
			return;
		}
		// Check for VALID DataCollectionType
		const FECsDataCollectionType& DataCollectionType = RemoveEntry.DataCollectionType;

		if (!EMCsDataCollectionType::Get().IsValidEnum(DataCollectionType))
		{
			RemoveEntry.Message = TEXT("INVALID DataCollectionType. See Output Log.");
			RemoveEntry.Output  = TEXT("ERROR");
			RemoveEntry.Remove	= false;

			if (UCsLibrary_Common::IsDefaultObject(this))
			{
				UCsLibrary_Common::DisplayNotificationInfo(RemoveEntry.Output, TEXT("Payload"), TEXT("RemoveEntryOutput"), 5.0f);
				UCsLibrary_Common::DisplayNotificationInfo(RemoveEntry.Message, TEXT("Payload"), TEXT("RemoveEntryMessage"), 5.0f);
			}

			FString Output = TEXT("UCsData_Payload::PostEditChangeProperty: Valid LoadAssetsTypes are:");

			if (UCsLibrary_Common::IsDefaultObject(this))
				UCsLibrary_Common::DisplayNotificationInfo(Output, TEXT("Payload"), TEXT("RemoveEntryAdditionalOutput"), 1.5f);

			UE_LOG(LogCs, Warning, TEXT("%s"), *Output);

			const int32& Count = EMCsDataCollectionType::Get().Num();

			for (int32 I = 0; I < Count; ++I)
			{
				const FECsDataCollectionType& Enum = EMCsDataCollectionType::Get().GetEnumAt(I);
				Output							   = TEXT("DataCollectionType: ") + Enum.Name;

				if (UCsLibrary_Common::IsDefaultObject(this))
				{
					const FString AdditionalOutput = TEXT("RemoveEntryAdditionalOutput") + FString::FromInt(I);

					UCsLibrary_Common::DisplayNotificationInfo(Output, TEXT("Payload"), AdditionalOutput, 1.5f);
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
				// TArrayPayload
				if (StructProperty->Struct == FCsTArrayPayload::StaticStruct())
				{
					const uint8 DataCollectionTypeCount = EMCsDataCollectionType::Get().Num();

					if (StructProperty->ArrayDim == DataCollectionTypeCount)
					{
						CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, DataCollectionTypeCount)

						if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
						{
							// Find LoadAssetsType
							for (int32 I = 0; I < DataCollectionTypeCount; ++I)
							{
								TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;

								const FECsDataCollectionType& CollectionType = EMCsDataCollectionType::Get().GetEnumAt(I);

								if (CollectionType != DataCollectionType)
									continue;

								const FString& DataCollectionTypeAsString = CollectionType.Name;

								bool Found = false;

								const int32 ArraySize = Array.Num();

								for (int32 J = ArraySize - 1; J >= 0; --J)
								{
									FCsPayload& Payload = Array[J];

									if (RemoveEntry.ShortCode == Payload.ShortCode)
									{
										if (Found)
											RemoveEntry.Output += TEXT(", ");

										const FString& DataTypeAsString = Payload.DataType;
										const FString& LoadFlagsAsString = EMCsLoadFlags_Editor::Get().ToString(Payload.LoadFlags);

										RemoveEntry.Output += TEXT("[") + DataCollectionTypeAsString + TEXT(", ") + DataTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(J) + TEXT("]");

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

		if (UCsLibrary_Common::IsDefaultObject(this))
		{
			UCsLibrary_Common::DisplayNotificationInfo(RemoveEntry.Output, TEXT("Payload"), TEXT("RemoveEntryOutput"), 5.0f);
			UCsLibrary_Common::DisplayNotificationInfo(RemoveEntry.Message, TEXT("Payload"), TEXT("RemoveEntryMessage"), 5.0f);
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