// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Item.h"
#include "CsCore.h"

UCsData_Item::UCsData_Item(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const FECsItemType& UCsData_Item::GetItemType() { return EMCsItemType::Get().GetMAX(); }

// Stats
#pragma region

const bool& UCsData_Item::IsIngredient() { return NCsCached::Ref::False; }

#pragma endregion Stats

// Members
#pragma region

UScriptStruct* UCsData_Item::GetMembersScriptStruct() { return nullptr; }

TArray<FCsItemMemberDescription>* UCsData_Item::GetMembers() { return nullptr; }

void UCsData_Item::SetMembers(FCsItemHistory& History)
{
	if (TArray<FCsItemMemberDescription>* Members = GetMembers())
	{
		const int32 Count = Members->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			FCsItemMemberDescription& Description = (*Members)[I];

			FCsItemMemberValue Value;
			Value.Type = Description.Type;

			History.Members.Add(Description.Name, Value);
		}
	}
}

#pragma endregion Members

// UI
#pragma region

const FString& UCsData_Item::GetDisplayName() { return NCsCached::Str::INVALID; }
UMaterialInstanceConstant* UCsData_Item::GetMaterial() { return nullptr; }
FCsUint8MatrixDimension* UCsData_Item::GetDimension() { return nullptr; }
const int32& UCsData_Item::GetCapacity() { return NCsCached::Ref::SInt; }

#pragma endregion UI

// Drop
#pragma region

const bool& UCsData_Item::OnDropSpawnActor() { return NCsCached::Ref::False; }
const FName& UCsData_Item::GetSpawnedActorDataShortCode() { return NCsCached::Name::None; }

#pragma endregion Drop

// Consume
#pragma region

const TArray<FCsItemOnConsumeContentRule>* UCsData_Item::GetOnConsumeContentRules() { return nullptr; }

const bool& UCsData_Item::OnConsumeDropContents() { return NCsCached::Ref::False; }

#pragma endregion Consume