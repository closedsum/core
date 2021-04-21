// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Achievement/CsTypes_Achievement.h"

// Settings
#include "Settings/CsPlatformServicesSettings.h"

// Achievement
#pragma region

namespace NCsAchievement
{
	void PopulateEnumMapFromSettings(const FString& Context)
	{
		if (UCsPlatformServicesSettings* Settings = GetMutableDefault<UCsPlatformServicesSettings>())
		{
			if (UDataTable* DataTable = Settings->Achievements.LoadSynchronous())
			{
				checkf(DataTable->GetRowStruct() == FCsAchievementEntry::StaticStruct(), TEXT("%s: DataTable: %s RowStruct: %s != FCsAchievementEntry."), *Context, *(DataTable->GetName()), *(DataTable->GetRowStruct()->GetName()));

				EMCsAchievement::Get().ClearUserDefinedEnums();

				const TMap<FName, uint8*>& RowMap = DataTable->GetRowMap();

				for (const TPair<FName, uint8*>& Pair : RowMap)
				{
					const FName& Name				 = Pair.Key;
					const FCsAchievementEntry* Entry = (const FCsAchievementEntry*)Pair.Value;

					checkf(Entry->Name.Compare(Name.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != Achievement Name (%s != %s)."), *Context, *(Entry->Name), *(Name.ToString()));

					checkf(!EMCsAchievement::Get().IsValidEnum(Entry->Name), TEXT("%s: Achievement Name: %s already exists (declared in native)."), *Context, *(Entry->Name));

					if (!Entry->DisplayName.IsEmpty())
					{
						checkf(!EMCsAchievement::Get().IsValidEnumByDisplayName(Entry->DisplayName), TEXT("%s: Achievement DisplayName: %s already exists (declared in native)."), *Context, *(Entry->DisplayName));

						EMCsAchievement::Get().Create(Entry->Name, Entry->DisplayName, true);
					}
					else
					{
						EMCsAchievement::Get().Create(Entry->Name, true);
					}
				}
			}
		}
	}
}

#pragma endregion 

// AchievementState
#pragma region

namespace NCsAchievementState
{
	namespace Ref
	{
		typedef EMCsAchievementState EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(None);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(InProgress);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Completed);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAchievementState_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementState_MAX;
}

#pragma endregion AchievementState

// AchievementProgress
#pragma region

namespace NCsAchievementProgress
{
	namespace Ref
	{
		typedef EMCsAchievementProgress EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Normalized);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Standard);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Binary);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Count);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Bitfield);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAchievementProgress_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementProgress_MAX;
}

#pragma endregion AchievementProgress

// FCsAchievement
#pragma region

void FCsAchievement::SetProgressType(const ECsAchievementProgress& InProgressType)
{
	ProgressType = InProgressType;

	// Normalized
	if (ProgressType == ECsAchievementProgress::Normalized)
	{
		MinProgress = 0.0f;
		MaxProgress = 1.0f;
	}
	// Standard | Count | Bitfield
	else
	if (ProgressType == ECsAchievementProgress::Standard ||
		ProgressType == ECsAchievementProgress::Binary ||
		ProgressType == ECsAchievementProgress::Count ||
		ProgressType == ECsAchievementProgress::Bitfield)
	{
		MinProgress = 0.0f;
		MaxProgress = 100.0f;
	}
}

void FCsAchievement::SetProgress(const float& InPercent)
{
	Percent	 = FMath::Clamp(InPercent, 0.0f, 1.0f);
	Progress = (Percent * (MaxProgress - MinProgress)) + MinProgress;

	if (Progress == MaxProgress)
	{
		State = ECsAchievementState::Completed;
	}
	else
	if (Progress > MinProgress)
	{
		State = ECsAchievementState::InProgress;
	}
	else
	{
		State = ECsAchievementState::None;
	}
}

void FCsAchievement::SetCount(const uint64& InCount)
{
	Count = FMath::Min(InCount, MaxCount);

	if (ProgressType == ECsAchievementProgress::Count)
	{
		SetProgress((float)Count / (float)MaxCount);
	}
}

void FCsAchievement::SetMaxCount(const uint64& InCount)
{
	MaxCount = InCount;
	Count    = FMath::Clamp(Count, 0ull, MaxCount);

	if (ProgressType == ECsAchievementProgress::Count)
	{
		SetProgress((float)Count / (float)MaxCount);
	}
}

void FCsAchievement::SetBitfield(const FString& InBitfield)
{
	if (Bitfield.Len() != InBitfield.Len())
	{
		Bitfield = InBitfield;

		NumBitsSet = 0;

		BitfieldLength = Bitfield.Len();

		BitMasks.Reset(FMath::Max((uint32)BitMasks.Max(), BitfieldLength));

		for (uint32 I = 0; I < BitfieldLength; ++I)
		{
			if (Bitfield[I] == '1')
				++NumBitsSet;

			BitMasks.AddDefaulted();
			FString& Mask = BitMasks[I];

			Mask.Reset(BitfieldLength);

			for (uint32 J = 0; J < BitfieldLength; ++J)
			{
				Mask += '0';
			}

			Mask[I] = '1';
		}

		BitMaskNone.Reset(FMath::Max((uint32)BitMaskNone.Len(), BitfieldLength));
		BitMaskComplete.Reset(FMath::Max((uint32)BitMaskComplete.Len(), BitfieldLength));

		for (uint32 I = 0; I < BitfieldLength; ++I)
		{
			BitMaskNone		+= '0';
			BitMaskComplete += '1';
		}
	}
	else
	{
		Bitfield = InBitfield;

		NumBitsSet = 0;

		for (uint32 I = 0; I < BitfieldLength; ++I)
		{
			if (Bitfield[I] == '1')
				++NumBitsSet;
		}
	}

	if (ProgressType == ECsAchievementProgress::Bitfield)
	{
		SetProgress((float)NumBitsSet / (float)UnlockBitfieldLength);
	}
}

void FCsAchievement::OrBitfield(const FString& InBitfield)
{
	if (Bitfield.Len() == InBitfield.Len())
	{
		NumBitsSet = 0;

		for (uint32 I = 0; I < BitfieldLength; ++I)
		{
			if (InBitfield[I] == '1')
				Bitfield[I] = '1';

			if (Bitfield[I] == '1')
				++NumBitsSet;
		}

		if (ProgressType == ECsAchievementProgress::Bitfield)
		{
			SetProgress((float)NumBitsSet / (float)UnlockBitfieldLength);
		}
	}
}

void FCsAchievement::SetBit(const uint32& Index)
{
	if (Index < (uint32)Bitfield.Len())
	{
		const bool HasChanged = Bitfield[Index] == '0';

		Bitfield[Index] = '1';

		if (HasChanged &&
			ProgressType == ECsAchievementProgress::Bitfield)
		{
			++NumBitsSet;
		
			SetProgress((float)NumBitsSet / (float)UnlockBitfieldLength);
		}
	}
}

void FCsAchievement::ClearBit(const uint32& Index)
{
	if (Index < (uint32)Bitfield.Len())
	{
		const bool HasChanged = Bitfield[Index] == '1';

		Bitfield[Index] = '0';

		if (HasChanged &&
			ProgressType == ECsAchievementProgress::Bitfield)
		{
			--NumBitsSet;

			SetProgress((float)NumBitsSet / (float)UnlockBitfieldLength);
		}
	}
}

bool FCsAchievement::IsValidBitfield(const FString& InBitfield)
{
	if (Bitfield.Len() != InBitfield.Len())
		return false;

	for (uint32 I = 0; I < BitfieldLength; ++I)
	{
		if (InBitfield[I] != '0' &&
			InBitfield[I] != '1')
		{
			return false;
		}
	}
	return true;
}

#pragma endregion FCsAchievement

// AchievementAction
#pragma region

namespace NCsAchievementAction
{
	namespace Ref
	{
		typedef EMCsAchievementAction EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(QueryIds, "Query Ids");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(QueryDescriptions, "Query Descriptions");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(UpdateDescriptions, "Update Descriptions");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Create);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Modify);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Remove);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(RemoveAll);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Write);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Complete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(CompleteAll, "Complete All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Reset);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ResetAll, "Reset All");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAchievementAction_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementAction_MAX;
}

#pragma endregion AchievementAction

// AchievementActionState
#pragma region

namespace NCsAchievementActionState
{
	namespace Ref
	{
		typedef EMCsAchievementActionState EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(None);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(InProgress, "In Progress");
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Complete);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAchievementActionState_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementActionState_MAX;
}

#pragma endregion AchievementActionState

// NCsAchievement::NAction::EAllocation
#pragma region

namespace NCsAchievement
{
	namespace NAction
	{
		namespace NAllocation
		{
			namespace Ref
			{
				typedef EMAllocation EnumMapType;

				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterTail, "After Tail");
				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AsHead, "As Head");
				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterHead, "After Head");
				CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EAllocation_MAX, "MAX");
			}

			CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::EAllocation_MAX;
		}
	}
}

#pragma endregion NCsAchievement::NAction::EAllocation

// AchievementWritePolicy
#pragma region

namespace NCsAchievementWritePolicy
{
	namespace Ref
	{
		typedef EMCsAchievementWritePolicy EnumMapType;

		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Client);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP(Server);
		CSPLATFORMSERVICES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsAchievementWritePolicy_MAX, "MAX");
	}

	CSPLATFORMSERVICES_API const uint8 MAX = (uint8)Type::ECsAchievementWritePolicy_MAX;
}

#pragma endregion AchievementWritePolicy