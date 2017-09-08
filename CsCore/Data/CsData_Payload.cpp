#include "Data/CsData_Payload.h"
#include "CsCore.h"
#include "CsCommon.h"

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

bool ACsData_Payload::PerformFindEntry(const FName &InShortCode, TArray<FCsPayload*> &OutPayloads, TArray<TCsLoadAssetsType> &OutLoadAssetsTypes, TArray<int32> &OutIndices)
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
				if (StructProperty->ArrayDim == LOAD_ASSETS_TYPE_MAX)
				{
					CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LOAD_ASSETS_TYPE_MAX)

					if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
					{
						// Find LoadAssetsType
						for (int32 I = 0; I < LOAD_ASSETS_TYPE_MAX; I++)
						{
							TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;

							const TCsLoadAssetsType LoadAssetsType = (TCsLoadAssetsType)I;

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

bool ACsData_Payload::PerformAddEntry(const FName &ShortCode, const TCsLoadAssetsType &LoadAssetsType, const TEnumAsByte<ECsLoadFlags_Editor::Type> &LoadFlags, FString &OutMessage, FString &OutOutput)
{
	// Check for VALID ShortCode
	if (ShortCode == NAME_None ||
		ShortCode == CS_INVALID_SHORT_CODE)
	{
		OutMessage = TEXT("INVALID ShortCode.");
		OutOutput  = TEXT("ERROR");
	}
	// Check for VALID LoadAssetsType
	if (LoadAssetsType == LoadAssetType_MAX)
	{
		OutMessage = TEXT("INVALID LoadAssetType. See Output Log.");
		OutOutput  = TEXT("ERROR");

		UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::PerformAddEntry: Valid LoadAssetsTypes are:"));

		for (int32 I = 0; I < LOAD_ASSETS_TYPE_MAX; I++)
		{
			UE_LOG(LogCs, Warning, TEXT("LoadAssetType: %s"), *((*LoadAssetsTypeToString)((TCsLoadAssetsType)I)));
		}
		return false;
	}

	// Check if ShortCode has ALREADY been ADDED
	TArray<FCsPayload*> OutPayloads;
	TArray<TCsLoadAssetsType> OutLoadAssetsTypes;
	TArray<int32> OutIndices;

	PerformFindEntry(ShortCode, OutPayloads, OutLoadAssetsTypes, OutIndices);

	const int32 PayloadCount = OutPayloads.Num();
	// Entries Found
	if (PayloadCount > CS_EMPTY)
	{
		const FString LoadFlagsAsString = ECsLoadFlags_Editor::ToString(LoadFlags);

		for (int32 I = 0; I < PayloadCount; I++)
		{
			FCsPayload* Payload = OutPayloads[I];

			const FString LoadAssetsTypeAsString = (*LoadAssetsTypeToString)(OutLoadAssetsTypes[I]);
			const FString AssetTypeAsString		 = Payload->AssetType;

			OutOutput += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");
		}
		// Duplicates
		if (PayloadCount > 1)
			OutMessage = TEXT("Already Exists. WARNING, Duplicates. REMOVE extra entries.");
		else
			OutMessage = TEXT("Already Exists.");
		return false;
	}
	// Attempt to ADD it
	else
	{
		// Check ShortCode entry EXISTS in DataMapping
		ACsDataMapping* DataMapping = GetDataMapping();

		TArray<FCsDataMappingEntry*> OutEntries;
		TArray<TCsAssetType> OutAssetTypes;
		OutIndices.Reset();

		DataMapping->PerformFindEntry(ShortCode, OutEntries, OutAssetTypes, OutIndices);

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

					const FString LoadFlagsAsString = ECsLoadFlags_Editor::ToString(LoadFlags);
					const FString AssetTypeAsString = (*AssetTypeToString)(OutAssetTypes[CS_FIRST]);

					UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::PostEditChangeProperty: Missing LoadFlags: %s in DataMapping: [%s, %s, %d]. Manually adding LoadFlag: %s."), *LoadFlagsAsString, *AssetTypeAsString, *(ShortCode.ToString()), *(FString::FromInt(OutIndices[CS_FIRST])), *LoadFlagsAsString);
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
							if (StructProperty->ArrayDim == LOAD_ASSETS_TYPE_MAX)
							{
								CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LOAD_ASSETS_TYPE_MAX)

								if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
								{
									TArray<FCsPayload>& Array = ((*Member)[(uint8)LoadAssetsType]).Payloads;

									const int32 ArraySize = Array.Num();

									const FString AssetTypeAsString = (*AssetTypeToString)(OutAssetTypes[CS_FIRST]);

									Array.AddDefaulted();
									Array[ArraySize].AssetType		  = AssetTypeAsString;
									Array[ArraySize].AssetType_Script = (uint8)OutAssetTypes[CS_FIRST];
									Array[ArraySize].ShortCode		  = ShortCode;
									Array[ArraySize].LoadFlags		  = LoadFlags;

									const FString LoadAssetsTypeAsString = (*LoadAssetsTypeToString)(LoadAssetsType);
									const FString LoadFlagsAsString		 = ECsLoadFlags_Editor::ToString(LoadFlags);

									OutOutput = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
									OutMessage = TEXT("SUCCESS.");
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
				TCsAssetType LastAssetType = OutAssetTypes[CS_FIRST];

				for (int32 I = 0; I < EntryCount; I++)
				{
					const FString AssetTypeAsString = (*AssetTypeToString)(OutAssetTypes[I]);

					OutOutput += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");

					if (LastAssetType != OutAssetTypes[I])
						IsAssetTypeMismatch |= true;
					LastAssetType = OutAssetTypes[I];
				}

				OutMessage = TEXT("Can NOT ADD. WARNING, Duplicates. REMOVE extra entries in DataMapping.");

				if (IsAssetTypeMismatch)
					OutMessage += TEXT(" ShortCode listed under multiple AssetTypes in DataMapping. Should ONLY be ONE.");
				return false;
			}
		}
		// Search for Asset in AssetRegistry, ADD it to DataMapping, and ADD Payload Entry
		else
		{
			bool Successful = DataMapping->PerformAddEntry(ShortCode, (int32)LoadFlags, OutMessage, OutOutput);

			if (Successful)
			{
				OutEntries.Reset();
				OutAssetTypes.Reset();
				OutIndices.Reset();

				DataMapping->PerformFindEntry(ShortCode, OutEntries, OutAssetTypes, OutIndices);

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
							if (StructProperty->ArrayDim == LOAD_ASSETS_TYPE_MAX)
							{
								CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LOAD_ASSETS_TYPE_MAX)

								if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
								{
									TArray<FCsPayload>& Array = ((*Member)[(uint8)LoadAssetsType]).Payloads;

									const int32 ArraySize = Array.Num();

									const FString AssetTypeAsString = (*AssetTypeToString)(OutAssetTypes[CS_FIRST]);

									Array.AddDefaulted();
									Array[ArraySize].AssetType		  = AssetTypeAsString;
									Array[ArraySize].AssetType_Script = (uint8)OutAssetTypes[CS_FIRST];
									Array[ArraySize].ShortCode		  = ShortCode;
									Array[ArraySize].LoadFlags		  = LoadFlags;

									const FString LoadAssetsTypeAsString = (*LoadAssetsTypeToString)(LoadAssetsType);
									const FString LoadFlagsAsString		 = ECsLoadFlags_Editor::ToString(LoadFlags);

									OutOutput  = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
									OutMessage = TEXT("SUCCESS. Check LOG.");
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

void ACsData_Payload::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	// Find Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadFindEntry, Find))
	{
		FindEntry.Message = TEXT("");
		FindEntry.Output = TEXT("");

		// Check for VALID ShortCode
		if (FindEntry.ShortCode == NAME_None ||
			FindEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			FindEntry.Message = TEXT("INVALID ShortCode.");
			FindEntry.Output = TEXT("ERROR");
			FindEntry.Find = false;

			Super::PostEditChangeProperty(e);
			return;
		}

		TArray<FCsPayload*> OutPayloads;
		TArray<TCsLoadAssetsType> OutLoadAssetsTypes;
		TArray<int32> OutIndices;

		PerformFindEntry(FindEntry.ShortCode, OutPayloads, OutLoadAssetsTypes, OutIndices);

		const int32 PayloadCount = OutPayloads.Num();

		for (int32 I = 0; I < PayloadCount; I++)
		{
			if (I > 0)
				FindEntry.Output += TEXT(", ");

			const FString LoadAssetsTypeAsString = (*LoadAssetsTypeToString)(OutLoadAssetsTypes[I]);
			const FString AssetTypeAsString		 = OutPayloads[I]->AssetType;
			const FString LoadFlagsAsString		 = ECsLoadFlags_Editor::ToString(OutPayloads[I]->LoadFlags);

			FindEntry.Output += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");
		}

		if (PayloadCount == CS_EMPTY)
			FindEntry.Output = TEXT("No Results.");
		FindEntry.Message = TEXT("SUCCESS");
		FindEntry.Find = false;
	}
	// Add Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadAddEntry, Add))
	{
		const TCsLoadAssetsType LoadAssetsType = (*StringToLoadAssetsType)(AddEntry.LoadAssetsType);

		PerformAddEntry(AddEntry.ShortCode, LoadAssetsType, AddEntry.LoadFlags, AddEntry.Message, AddEntry.Output);
		AddEntry.Add = false;
	}
	// Remove Entry
	if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsPayloadRemoveEntry, Remove))
	{
		RemoveEntry.Message = TEXT("");
		RemoveEntry.Output = TEXT("");

		// Check for VALID ShortCode
		if (RemoveEntry.ShortCode == NAME_None ||
			RemoveEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			RemoveEntry.Message = TEXT("INVALID ShortCode.");
			RemoveEntry.Output = TEXT("ERROR");
			RemoveEntry.Remove = false;

			Super::PostEditChangeProperty(e);
			return;
		}
		// Check for VALID LoadAssetsType
		const TCsLoadAssetsType LoadAssetsType = (*StringToLoadAssetsType)(RemoveEntry.LoadAssetsType);

		if (LoadAssetsType == LoadAssetType_MAX)
		{
			RemoveEntry.Message = TEXT("INVALID LoadAssetType. See Output Log.");
			RemoveEntry.Output  = TEXT("ERROR");
			RemoveEntry.Remove	= false;

			UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::PostEditChangeProperty: Valid LoadAssetsTypes are:"))

				for (int32 I = 0; I < LOAD_ASSETS_TYPE_MAX; I++)
				{
					UE_LOG(LogCs, Warning, TEXT("LoadAssetType: %s"), *((*LoadAssetsTypeToString)((TCsLoadAssetsType)I)));
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
					if (StructProperty->ArrayDim == LOAD_ASSETS_TYPE_MAX)
					{
						CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(uint8, MAX, LOAD_ASSETS_TYPE_MAX)

						if (FCsTArrayPayload(*Member)[MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[MAX]>(this))
						{
							// Find LoadAssetsType
							for (int32 I = 0; I < LOAD_ASSETS_TYPE_MAX; I++)
							{
								TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;

								const TCsLoadAssetsType AssetsType = (TCsLoadAssetsType)I;

								if (AssetsType != LoadAssetsType)
									continue;

								const FString LoadAssetsTypeAsString = (*LoadAssetsTypeToString)(LoadAssetsType);

								bool Found = false;

								const int32 ArraySize = Array.Num();

								for (int32 J = ArraySize - 1; J >= 0; J--)
								{
									FCsPayload& Payload = Array[J];

									if (RemoveEntry.ShortCode == Payload.ShortCode)
									{
										if (Found)
											RemoveEntry.Output += TEXT(", ");

										const FString AssetTypeAsString = Payload.AssetType;
										const FString LoadFlagsAsString = ECsLoadFlags_Editor::ToString(Payload.LoadFlags);

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