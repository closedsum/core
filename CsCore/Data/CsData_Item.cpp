// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Item.h"
#include "CsCore.h"

ACsData_Item::ACsData_Item(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

TCsItemType ACsData_Item::GetBaseItemType() { return BaseItemType; }

// Stats
#pragma region

const bool& ACsData_Item::IsIngredient() { return ECsCachedReferences::Ref::False; }

#pragma endregion Stats

// Members
#pragma region

UScriptStruct* ACsData_Item::GetMembersScriptStruct() { return nullptr; }

TArray<FCsItemMemberDescription>* ACsData_Item::GetMembers() { return nullptr; }

void ACsData_Item::SetMembers(FCsItemHistory& History)
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

const FString& ACsData_Item::GetDisplayName() { return ECsCachedString::Str::INVALID; }
UMaterialInstanceConstant* ACsData_Item::GetMaterial() { return nullptr; }
FCsUint8MatrixDimension* ACsData_Item::GetDimension() { return nullptr; }
const int32& ACsData_Item::GetCapacity() { return ECsCachedReferences::Ref::SInt; }

#pragma endregion UI

// Drop
#pragma region

const bool& ACsData_Item::OnDropSpawnActor() { return ECsCachedReferences::Ref::False; }
const FName& ACsData_Item::GetSpawnedActorDataShortCode() { return ECsCachedName::Name::None; }

#pragma endregion Drop

// Consume
#pragma region

const TArray<FCsItemOnConsumeContentRule>* ACsData_Item::GetOnConsumeContentRules() { return nullptr; }

const bool& ACsData_Item::OnConsumeDropContents() { return ECsCachedReferences::Ref::False; }

#pragma endregion Consume