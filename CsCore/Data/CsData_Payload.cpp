#include "Data/CsData_Payload.h"
#include "CsCore.h"
#include "CsCommon.h"

#if WITH_EDITOR
#include "Data/CsDataMapping.h"
#endif WITH_EDITOR

ACsData_Payload::ACsData_Payload(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//Type			  = ECsAssetType::ECsAssetType_MAX;
	//Type_MAX		  = ECsAssetType::ECsAssetType_MAX;
	//AssetTypeToString = &ECsAssetType::ToString;
	//StringToAssetType = &ECsAssetType::ToType;
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
				if (StructProperty->ArrayDim == ECS_LOAD_ASSETS_TYPE_MAX)
				{
					if (FCsTArrayPayload(*Member)[ECS_LOAD_ASSETS_TYPE_MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[ECS_LOAD_ASSETS_TYPE_MAX]>(this))
					{
						// Find LoadAssetsType
						for (int32 I = 0; I < ECS_LOAD_ASSETS_TYPE_MAX; I++)
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

			const FString LoadAssetsTypeAsString = ECsLoadAssetsType::ToString(OutLoadAssetsTypes[I]);
			const FString AssetTypeAsString		 = ECsAssetType::ToString(OutPayloads[I]->AssetType);
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
		AddEntry.Message = TEXT("");
		AddEntry.Output = TEXT("");

		// Check for VALID ShortCode
		if (AddEntry.ShortCode == NAME_None ||
			AddEntry.ShortCode == CS_INVALID_SHORT_CODE)
		{
			AddEntry.Message = TEXT("INVALID ShortCode.");
			AddEntry.Output = TEXT("ERROR");
			AddEntry.Add = false;

			Super::PostEditChangeProperty(e);
			return;
		}

		// Check if ShortCode has ALREADY been ADDED
		TArray<FCsPayload*> OutPayloads;
		TArray<TCsLoadAssetsType> OutLoadAssetsTypes;
		TArray<int32> OutIndices;

		PerformFindEntry(AddEntry.ShortCode, OutPayloads, OutLoadAssetsTypes, OutIndices);

		const int32 PayloadCount = OutPayloads.Num();
		// Entries Found
		if (PayloadCount > CS_EMPTY)
		{
			const FString LoadFlagsAsString = ECsLoadFlags_Editor::ToString(AddEntry.LoadFlags);

			bool IsAssetTypeMismatch = false;

			for (int32 I = 0; I < PayloadCount; I++)
			{
				FCsPayload* Payload = OutPayloads[I];

				const FString LoadAssetsTypeAsString = ECsLoadAssetsType::ToString(OutLoadAssetsTypes[I]);
				const FString AssetTypeAsString		 = ECsAssetType::ToString(Payload->AssetType);

				AddEntry.Output += TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");

				if (AddEntry.AssetType != Payload->AssetType)
					IsAssetTypeMismatch |= true;
			}
			// Duplicates
			if (PayloadCount > 1)
				AddEntry.Message = TEXT("Already Exists. WARNING, Duplicates. REMOVE extra entries.");
			else
				AddEntry.Message = TEXT("Already Exists.");

			if (IsAssetTypeMismatch)
				AddEntry.Message += TEXT(" ShortCode listed under multiple AssetTypes. Should ONLY be ONE.");
		}
		// Attempt to ADD it
		else
		{
			// Check ShortCode entry EXISTS in DataMapping
			ACsDataMapping* DataMapping = GetDataMapping();

			TArray<FCsDataMappingEntry*> OutEntries;
			TArray<TCsAssetType> OutAssetTypes;
			OutIndices.Reset();

			DataMapping->PerformFindEntry(AddEntry.ShortCode, OutEntries, OutAssetTypes, OutIndices);

			const int32 EntryCount = OutEntries.Num();

			// Entries in DataMapping Found
			if (EntryCount > CS_EMPTY)
			{
				// ADD
				if (EntryCount == 1)
				{
					// Check LoadFlags
					const ECsLoadFlags LoadFlags = ECsLoadFlags_Editor::ToBaseType(AddEntry.LoadFlags);

					if (!CS_TEST_BLUEPRINT_BITFLAG(OutEntries[CS_FIRST]->Data_LoadFlags, LoadFlags))
					{
						CS_SET_BLUEPRINT_BITFLAG(OutEntries[CS_FIRST]->Data_LoadFlags, LoadFlags);

						const FString LoadFlagsAsString = ECsLoadFlags_Editor::ToString(AddEntry.LoadFlags);
						const FString AssetTypeAsString = ECsAssetType::ToString(OutAssetTypes[CS_FIRST]);

						UE_LOG(LogCs, Warning, TEXT("ACsData_Payload::PostEditChangeProperty: Missing LoadFlags: %s in DataMapping: [%s, %s, %d]. Manually adding LoadFlag: %s."), *LoadFlagsAsString, *AssetTypeAsString, *(AddEntry.ShortCode.ToString()), *(FString::FromInt(OutIndices[CS_FIRST])), *LoadFlagsAsString);
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
								if (StructProperty->ArrayDim == ECS_LOAD_ASSETS_TYPE_MAX)
								{
									if (FCsTArrayPayload(*Member)[ECS_LOAD_ASSETS_TYPE_MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[ECS_LOAD_ASSETS_TYPE_MAX]>(this))
									{
										TArray<FCsPayload>& Array = ((*Member)[(uint8)AddEntry.LoadAssetsType]).Payloads;

										const int32 ArraySize = Array.Num();

										Array.AddDefaulted();
										Array[ArraySize].AssetType = AddEntry.AssetType;
										Array[ArraySize].ShortCode = AddEntry.ShortCode;
										Array[ArraySize].LoadFlags = AddEntry.LoadFlags;

										const FString LoadAssetsTypeAsString = ECsLoadAssetsType::ToString(AddEntry.LoadAssetsType);
										const FString AssetTypeAsString		 = ECsAssetType::ToString(AddEntry.AssetType);
										const FString LoadFlagsAsString		 = ECsLoadFlags_Editor::ToString(AddEntry.LoadFlags);

										AddEntry.Output = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
										AddEntry.Message = TEXT("SUCCESS.");
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
						const FString AssetTypeAsString = ECsAssetType::ToString(OutAssetTypes[I]);

						AddEntry.Output += TEXT("[") + AssetTypeAsString + TEXT(", ") + FString::FromInt(OutIndices[I]) + TEXT("]");

						if (LastAssetType != OutAssetTypes[I])
							IsAssetTypeMismatch |= true;
						LastAssetType = OutAssetTypes[I];
					}

					AddEntry.Message = TEXT("Can NOT ADD. WARNING, Duplicates. REMOVE extra entries in DataMapping.");

					if (IsAssetTypeMismatch)
						AddEntry.Message += TEXT(" ShortCode listed under multiple AssetTypes in DataMapping. Should ONLY be ONE.");
				}
			}
			// Search for Asset in AssetRegistry, ADD it to DataMapping, and ADD Payload Entry
			else
			{
				bool Successful = DataMapping->PerformAddEntry(AddEntry.ShortCode, (int32)AddEntry.LoadFlags, AddEntry.Message, AddEntry.Output);

				if (Successful)
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
								if (StructProperty->ArrayDim == ECS_LOAD_ASSETS_TYPE_MAX)
								{
									if (FCsTArrayPayload(*Member)[ECS_LOAD_ASSETS_TYPE_MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[ECS_LOAD_ASSETS_TYPE_MAX]>(this))
									{
										TArray<FCsPayload>& Array = ((*Member)[(uint8)AddEntry.LoadAssetsType]).Payloads;

										const int32 ArraySize = Array.Num();

										Array.AddDefaulted();
										Array[ArraySize].AssetType = AddEntry.AssetType;
										Array[ArraySize].ShortCode = AddEntry.ShortCode;
										Array[ArraySize].LoadFlags = AddEntry.LoadFlags;

										const FString LoadAssetsTypeAsString = ECsLoadAssetsType::ToString(AddEntry.LoadAssetsType);
										const FString AssetTypeAsString		 = ECsAssetType::ToString(AddEntry.AssetType);
										const FString LoadFlagsAsString		 = ECsLoadFlags_Editor::ToString(AddEntry.LoadFlags);

										AddEntry.Output = TEXT("[") + LoadAssetsTypeAsString + TEXT(", ") + AssetTypeAsString + TEXT(", ") + LoadFlagsAsString + TEXT(", ") + FString::FromInt(ArraySize) + TEXT("]");
										AddEntry.Message = TEXT("SUCCESS. Check LOG.");
									}
								}
							}
						}
					}
				}
			}
		}
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
					if (StructProperty->ArrayDim == ECS_LOAD_ASSETS_TYPE_MAX)
					{
						if (FCsTArrayPayload(*Member)[ECS_LOAD_ASSETS_TYPE_MAX] = Property->ContainerPtrToValuePtr<FCsTArrayPayload[ECS_LOAD_ASSETS_TYPE_MAX]>(this))
						{
							// Find LoadAssetsType
							for (int32 I = 0; I < ECS_LOAD_ASSETS_TYPE_MAX; I++)
							{
								TArray<FCsPayload>& Array = ((*Member)[I]).Payloads;

								const TCsLoadAssetsType LoadAssetsType = (TCsLoadAssetsType)I;

								if (LoadAssetsType != RemoveEntry.LoadAssetsType)
									continue;

								const FString LoadAssetsTypeAsString = ECsLoadAssetsType::ToString(LoadAssetsType);

								bool Found = false;

								const int32 ArraySize = Array.Num();

								for (int32 J = ArraySize - 1; J >= 0; J--)
								{
									FCsPayload& Payload = Array[J];

									if (RemoveEntry.ShortCode == Payload.ShortCode)
									{
										if (Found)
											RemoveEntry.Output += TEXT(", ");

										const FString AssetTypeAsString = ECsAssetType::ToString(Payload.AssetType);
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