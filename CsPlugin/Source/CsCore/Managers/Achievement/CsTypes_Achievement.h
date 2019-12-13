// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

#include "CsTypes_Achievement.generated.h"
#pragma once

// Achievement
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsAchievement : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAchievement)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAchievement)

struct CSCORE_API EMCsAchievement : public TCsEnumStructMap<FECsAchievement, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsAchievement, FECsAchievement, uint8)
};

namespace NCsAchievement
{
	typedef FECsAchievement Type;
}

#pragma endregion Achievement

// AchievementState
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementState : uint8
{
	None						UMETA(DisplayName = "None"),
	InProgress					UMETA(DisplayName = "In Progress"),
	Completed					UMETA(DisplayName = "Completed"),
	ECsAchievementState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAchievementState final : public TCsEnumMap<ECsAchievementState>
{
	CS_ENUM_MAP_BODY(EMCsAchievementState, ECsAchievementState)
};

namespace NCsAchievementState
{
	typedef ECsAchievementState Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type InProgress;
		extern CSCORE_API const Type Completed;
		extern CSCORE_API const Type ECsAchievementState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion AchievementState

// AchievementProgress
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementProgress : uint8
{
	// [0.0, 1.0] Inclusive.
	Normalized					UMETA(DisplayName = "Normalized"),
	// [0.0, 100.0] Inclusive.
	Standard					UMETA(DisplayName = "Standard"),
	// [0.0, 100.0] Inclusive. Internally only values supported are 0.0 = Lock and 100.0 = Unlock.
	Binary						UMETA(DisplayName = "Binary"),
	// [0.0, 100.0] Inclusive. Internally [0, N] Inclusive. X out of N.
	Count						UMETA(DisplayName = "Count"),
	// [0.0, 100.0] Inclusive. Internally check against bits set for a mask (i.e. 010010, ... etc).
	Bitfield					UMETA(DisplayName = "Bitfield"),
	ECsAchievementProgress_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAchievementProgress final : public TCsEnumMap<ECsAchievementProgress>
{
	CS_ENUM_MAP_BODY(EMCsAchievementProgress, ECsAchievementProgress)
};

namespace NCsAchievementProgress
{
	typedef ECsAchievementProgress Type;

	namespace Ref
	{
		extern CSCORE_API const Type Normalized;
		extern CSCORE_API const Type Standard;
		extern CSCORE_API const Type Binary;
		extern CSCORE_API const Type Count;
		extern CSCORE_API const Type Bitfield;
		extern CSCORE_API const Type ECsAchievementProgress_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion AchievementProgress

// ICsAchievement
#pragma region

struct CSCORE_API ICsAchievement
{
public:

	virtual ~ICsAchievement(){}

	/**
	* Get the Id of the Achievement. This is usually the internal name for
	*  the Achievement.
	*
	* return Id.
	*/
	virtual const FString& GetId() const = 0;

	/**
	* Return whether the Achievement is valid. An achievement that is NOT valid
	*  can NOT be updated (Progress, State, ... etc).
	*
	* return Whether Valid or Invalid.
	*/
	virtual const bool& IsValid() const = 0;

	/**
	* Set to Valid.
	*  If Valid, the Achievement can be updated (Progress, State, ... etc).
	*/
	virtual void SetValid() = 0;

	/**
	* Set to Invalid.
	*  If Invalid, the Achievement can NOT be updated (Progress, State, ... etc).
	*/
	virtual void SetInvalid() = 0;

	/**
	* Get the Progress Type. The Progress Type dictates the value range of the Progress.
	*  See ECsAchievementProgress (Normalized, Standard, ... etc).
	*
	* return Progress Type.
	*/
	virtual const ECsAchievementProgress& GetProgressType() const = 0;

	/**
	* Set the Progress Type.
	*  See ECsAchievementProgress (Normalized, Standard, ... etc).
	*
	* @param InProgressType		New Progress Type.
	*/
	virtual void SetProgressType(const ECsAchievementProgress& InProgressType) = 0;

	/**
	* Get the current Progress. The value is in the range defined by the Progress Type.
	*  See ECsAchievementProgress (Normalized, Standard, ... etc).
	*
	* return Progress.
	*/
	virtual const float& GetProgress() const = 0;

	/**
	* Get the current Progress as percent.
	*
	* return Percent. The value is in the range [0, 1].
	*/
	virtual const float& GetProgressAsPercent() const = 0;

	/**
	* Set the Progress. The value is adjusted to range defined by the Progress Type.
	*  See ECsAchievementProgress (Normalized, Standard, ... etc).
	*
	* @param InPercent	Value between [0, 1].
	*/
	virtual void SetProgress(const float& InPercent) = 0;

	virtual float CalculateProgress(const float& InPercent) = 0;

	/**
	* Get the maximum Count to unlock the Achievement.
	*  Progress Type must be Count.
	*
	* return	Count to unlock the Achievement.
	*/
	virtual const int32& GetMaxCount() const = 0;

	/**
	* Set the maximum Count to unlock the Achievement.
	*  Progress Type must be Count.
	*
	* @param InCount	New Count to unlock the Achievement.
	*/
	virtual void SetMaxCount(const int32& InCount) = 0;

	//virtual const uint32& GetUnlockBitfield() = 0;

	//virtual void SetUnlockBitfield(const uint32& InBitfield) = 0;

	//virtual const int32& GetUnlockBitCount() = 0;

	//virtual void SetBitfield(const uint32& InBitfield) = 0;

	//virtual const int32& GetBitCount() = 0;

	/**
	* Get the Type. This is an enum-like (enum struct) representation of the Achievement.
	*  The name will mostly likely be the same as the Id.
	*  See FECsAchievement and NCsAchievement (namespace where enum structs are defined)
	*
	* return Type.
	*/
	virtual const FECsAchievement& GetType() const = 0;

	/**
	*
	*
	* return State.
	*/
	virtual const ECsAchievementState& GetState() const = 0;

	/**
	* Get the Title of the Achievement (i.e. Achievement 1 Title).
	*
	* return Title.
	*/
	virtual const FText& GetTitle() const = 0;

	/**
	* Get the Locked Description of the Achievement (i.e. Locked Achievement 1).
	*
	* return Locked Description.
	*/
	virtual const FText& GetLockedDescription() const = 0;

	/**
	* 
	*
	* return Unlocked Description.
	*/
	virtual const FText& GetUnlockedDescription() const = 0;

	/**
	*
	*
	* return Whether the achievement is hidden.
	*/
	virtual const bool& IsHidden() const = 0;

	/**
	*
	*
	* return Unlock Time.
	*/
	virtual const FDateTime& GetUnlockTime() const = 0;

	/**
	*
	*/
	virtual void Complete() = 0;
};

#pragma endregion ICsAchievement

// FCsAchievement
#pragma region

struct CSCORE_API FCsAchievement : public ICsAchievement
{
public:

	/** */
	FString Id;

protected:

	/** */
	bool bValid;

	/** */
	ECsAchievementProgress ProgressType;

	/** */
	float Progress;

	/** */
	float MinProgress;
	/** */
	float MaxProgress;

	/** */
	int32 Count;

	/** */
	int32 MaxCount;

	/** */
	uint32 Bitfield;
	/** */
	int32 BitCount;

	/** */
	uint32 UnlockBitfield;
	/** */
	int32 UnlockBitCount;

	/** */
	float Percent;

public:

	/** */
	FECsAchievement Type;
	
protected:

	/** */
	ECsAchievementState State;

public:

	/** */
	FText Title;

	/** */
	FText LockedDescription;

	/** */
	FText UnlockDescription;

	/** */
	bool bHidden;

	/** */
	FDateTime UnlockTime;

	FCsAchievement() :
		Id(),
		bValid(true),
		ProgressType(ECsAchievementProgress::Normalized),
		Progress(0.0f),
		MinProgress(0.0f),
		MaxProgress(1.0f),
		Count(0),
		MaxCount(0),
		Bitfield(0),
		BitCount(0),
		UnlockBitfield(0),
		UnlockBitCount(0),
		Percent(0.0f),
		Type(),
		State(ECsAchievementState::None),
		Title(),
		LockedDescription(),
		UnlockDescription(),
		bHidden(false),
		UnlockTime()
	{
	}

	virtual ~FCsAchievement()
	{
	}

// ICsAchievement
#pragma region
public:

	FORCEINLINE const FString& GetId() const
	{
		return Id;
	}

	FORCEINLINE const bool& IsValid() const
	{
		return bValid;
	}

	FORCEINLINE void SetValid()
	{
		bValid = true;
	}

	FORCEINLINE void SetInvalid()
	{
		bValid = false;
	}

	FORCEINLINE const ECsAchievementProgress& GetProgressType() const
	{
		return ProgressType;
	}

	void SetProgressType(const ECsAchievementProgress& InProgressType)
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
			ProgressType == ECsAchievementProgress::Count ||
			ProgressType == ECsAchievementProgress::Bitfield)
		{
			MinProgress = 0.0f;
			MaxProgress = 100.0f;
		}

		const float NewProgress = (Percent * (MaxProgress - MinProgress)) + MinProgress;

		SetProgress(NewProgress);
	}

	FORCEINLINE const float& GetProgress() const
	{
		return Progress;
	}

	FORCEINLINE const float& GetProgressAsPercent() const
	{
		return Percent;
	}

	void SetProgress(const float& InPercent)
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

	float CalculateProgress(const float& InPercent)
	{
		float P = FMath::Clamp(InPercent, 0.0f, 1.0f);
		return (P * (MaxProgress - MinProgress)) + MinProgress;
	}

	FORCEINLINE const int32& GetMaxCount() const
	{
		return MaxCount;
	}

	void SetMaxCount(const int32& InCount)
	{
		MaxCount = InCount;
		Count    = FMath::Clamp(Count, 0, MaxCount);

		if (ProgressType == ECsAchievementProgress::Count)
		{
			SetProgress((float)Count / (float)MaxCount);
		}
	}

	FORCEINLINE const FECsAchievement& GetType() const
	{
		return Type;
	}

	FORCEINLINE const ECsAchievementState& GetState() const
	{
		return State;
	}

	FORCEINLINE const FText& GetTitle() const
	{
		return Title;
	}

	FORCEINLINE const FText& GetLockedDescription() const
	{
		return LockedDescription;
	}

	FORCEINLINE const FText& GetUnlockedDescription() const
	{
		return UnlockDescription;
	}

	FORCEINLINE const bool& IsHidden() const
	{
		return bHidden;
	}

	FORCEINLINE const FDateTime& GetUnlockTime() const
	{
		return UnlockTime;
	}

	void Complete()
	{
		Progress = MaxProgress;
		Count	 = MaxCount;
		Bitfield = UnlockBitfield;
		Percent  = 1.0f;
		State	 = ECsAchievementState::Completed;
	}

#pragma endregion ICsAchievement
};

#pragma endregion FCsAchievement

// AchievementAction
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementAction : uint8
{
	QueryIds					UMETA(DisplayName = "Query Ids"),
	QueryDescriptions			UMETA(DisplayName = "Query Descriptions"),
	UpdateDescriptions			UMETA(DisplayName = "Update Descriptions"),
	Write						UMETA(DisplayName = "Write"),
	Complete					UMETA(DisplayName = "Complete"),
	CompleteAll					UMETA(DisplayName = "Complete All"),
	Reset						UMETA(DisplayName = "Reset"),
	ResetAll					UMETA(DisplayName = "Reset All"),
	ECsAchievementAction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAchievementAction final : public TCsEnumMap<ECsAchievementAction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAchievementAction, ECsAchievementAction)
};

namespace NCsAchievementAction
{
	typedef ECsAchievementAction Type;

	namespace Ref
	{
		extern CSCORE_API const Type QueryIds;
		extern CSCORE_API const Type QueryDescriptions;
		extern CSCORE_API const Type UpdateDescriptions;
		extern CSCORE_API const Type Write;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type CompleteAll;
		extern CSCORE_API const Type Reset;
		extern CSCORE_API const Type ResetAll;
		extern CSCORE_API const Type ECsAchievementAction_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion AchievementAction

// AchievementActionState
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementActionState : uint8
{
	None							UMETA(DisplayName = "None"),
	InProgress						UMETA(DisplayName = "In Progress"),
	Complete						UMETA(DisplayName = "Complete"),
	ECsAchievementActionState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAchievementActionState final : public TCsEnumMap<ECsAchievementActionState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAchievementActionState, ECsAchievementActionState)
};

namespace NCsAchievementActionState
{
	typedef ECsAchievementActionState Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type InProgress;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsAchievementActionState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion AchievementActionState

// FCsAchievementActionInfo
#pragma region

struct CSCORE_API FCsAchievementActionInfo
{
public:

	/** Achievement to perform Action on. */
	FECsAchievement Achievement;

	/** Action to processed. See ECsAchievementAction. */
	ECsAchievementAction Action;

	/** If Action == Write, the progress as a percent [0.0, 1.0] inclusive. */
	float Percent;

private:

	/** Current state of the action (i.e. In Progress, Complete, ... etc). */
	ECsAchievementActionState State;

	/** Whether the action completed successfully. */
	bool bSuccess;

public:

	FCsAchievementActionInfo() :
		Achievement(),
		Action(ECsAchievementAction::ECsAchievementAction_MAX),
		Percent(0.0f),
		State(ECsAchievementActionState::None),
		bSuccess(false)
	{

	}

	FORCEINLINE bool IsReadyToProcess() const
	{
		return State == ECsAchievementActionState::None;
	}

	FORCEINLINE void StartProgress()
	{
		State = ECsAchievementActionState::InProgress;
	}

	FORCEINLINE bool InProgress() const
	{
		return State == ECsAchievementActionState::InProgress;
	}

	FORCEINLINE void Complete()
	{
		State = ECsAchievementActionState::Complete;
	}

	FORCEINLINE bool IsComplete() const
	{
		return State == ECsAchievementActionState::Complete;
	}

	FORCEINLINE void Success()
	{
		bSuccess = true;
	}

	FORCEINLINE bool WasSuccessful() const
	{
		return bSuccess;
	}

	void Reset()
	{
		Achievement = EMCsAchievement::Get().GetMAX();
		Action = ECsAchievementAction::ECsAchievementAction_MAX;
		Percent = 0.0f;
		State = ECsAchievementActionState::None;
		bSuccess = false;
	}
};

#pragma endregion FCsAchievementActionInfo

struct CSCORE_API FCsAchievementWriteState
{
private: 

	bool bLocked;

public:

	bool bComplete;

	bool bSuccess;

	FCsAchievementWriteState() :
		bLocked(false),
		bComplete(false),
		bSuccess(false)
	{
	}

	bool IsLocked() const
	{
		return bLocked;
	}

	void Lock()
	{
		bLocked = true;
	}

	void Unlock()
	{
		bLocked = false;
	}

	bool CanUnlock() const
	{
		return bLocked && bComplete;
	}

	void Complete()
	{
		bComplete = true;
	}

	void Reset()
	{
		bLocked = false;
		bComplete = false;
		bSuccess = false;
	}
};

struct CSCORE_API FCsAchievementToWrite
{
public:

	FECsAchievement Achievement;

	float Percent;

	FCsAchievementToWrite() :
		Achievement(),
		Percent(0.0f)
	{
	}
};

struct CSCORE_API FCsAchievementResetState
{
private:

	bool bLocked;
	bool bProcessing;

public:

	bool bSuccess;

	FCsAchievementResetState() :
		bLocked(false),
		bProcessing(false),
		bSuccess(false)
	{
	}

	bool IsLocked() const
	{
		return bLocked;
	}

	void Unlock()
	{
		bLocked = false;
	}

	bool CanUnlock() const
	{
		return bLocked && !bProcessing;
	}

	void StartProcessing()
	{
		bLocked = true;
		bProcessing = true;
	}

	void StopProcessing()
	{
		bProcessing = false;
	}

	void Reset()
	{
		bLocked = false;
		bProcessing = false;
		bSuccess = false;
	}
};

struct CSCORE_API FCsAchievementToReset
{
public:

	FECsAchievement Achievement;

	float Percent;

	FCsAchievementToReset() :
		Achievement(),
		Percent(0.0f)
	{
	}
};

// AchievementQueryOrder
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementQueryOrder : uint8
{
	IdsFirst						UMETA(DisplayName = "Ids First"),
	DescriptionsFirst				UMETA(DisplayName = "Descriptions First"),
	ECsAchievementQueryOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAchievementQueryOrder final : public TCsEnumMap<ECsAchievementQueryOrder>
{
	CS_ENUM_MAP_BODY(EMCsAchievementQueryOrder, ECsAchievementQueryOrder)
};

namespace NCsAchievementQueryOrder
{
	typedef ECsAchievementQueryOrder Type;

	namespace Ref
	{
		extern CSCORE_API const Type IdsFirst;
		extern CSCORE_API const Type DescriptionsFirst;
		extern CSCORE_API const Type ECsAchievementQueryOrder_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion AchievementQueryOrder

// FCsAchievementQueryIdsState
#pragma region

struct CSCORE_API FCsAchievementQueryIdsState
{
private:

	bool bComplete;
	bool bProcessing;
	bool bQueue;

public:

	bool bSuccess;

	FCsAchievementQueryIdsState() :
		bComplete(false),
		bProcessing(false),
		bQueue(false),
		bSuccess(false)
	{
	}

	FORCEINLINE bool IsQueued() const
	{
		return bQueue;
	}

	FORCEINLINE void Queue()
	{
		bQueue = true;
	}

	FORCEINLINE bool IsProcessing() const
	{
		return bProcessing;
	}

	FORCEINLINE void StartProcessing()
	{
		bProcessing = true;
		bQueue = false;
	}

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

	FORCEINLINE void Complete()
	{
		bComplete = true;
		bProcessing = false;
	}

	FORCEINLINE bool IsSuccessful() const
	{
		return bSuccess;
	}

	FORCEINLINE void Success()
	{
		bSuccess = true;
	}

	void Reset()
	{
		bComplete = false;
		bProcessing = false;
		bQueue = false;
		bSuccess = false;
	}
};

#pragma endregion FCsAchievementQueryIdsState

// FCsAchievementQueryDescriptionsState
#pragma region

struct CSCORE_API FCsAchievementQueryDescriptionsState
{
private:

	bool bComplete;
	bool bProcessing;
	bool bQueue;

public:

	bool bSuccess;

	FCsAchievementQueryDescriptionsState() :
		bComplete(false),
		bProcessing(false),
		bQueue(false),
		bSuccess(false)
	{
	}

	FORCEINLINE bool IsQueued() const
	{
		return bQueue;
	}

	FORCEINLINE void Queue()
	{
		bQueue = true;
	}

	FORCEINLINE bool IsProcessing() const
	{
		return bProcessing;
	}

	FORCEINLINE void StartProcessing()
	{
		bProcessing = true;
		bQueue = false;
	}

	FORCEINLINE bool IsComplete() const
	{
		return bComplete;
	}

	FORCEINLINE void Complete()
	{
		bComplete = true;
		bProcessing = false;
	}

	FORCEINLINE bool IsSuccessful() const
	{
		return bSuccess;
	}

	FORCEINLINE void Success()
	{
		bSuccess = true;
	}

	void Reset()
	{
		bComplete = false;
		bProcessing = false;
		bQueue = false;
		bSuccess = false;
	}
};

#pragma endregion FCsAchievementQueryDescriptionsState

// FCsAchievementQueryState
#pragma region

struct CSCORE_API FCsAchievementQueryState
{
public:

	FCsAchievementQueryIdsState Ids;

	FCsAchievementQueryDescriptionsState Descriptions;

	FCsAchievementQueryState() :
		Ids(),
		Descriptions()
	{
	}

	FORCEINLINE bool IsProcessing() const
	{
		return Ids.IsProcessing() || Descriptions.IsProcessing();
	}

	FORCEINLINE bool IsComplete() const
	{
		return Ids.IsComplete() && Descriptions.IsComplete();
	}

	FORCEINLINE bool IsSuccessful() const
	{
		return Ids.IsSuccessful() && Descriptions.IsSuccessful();
	}

	void Reset()
	{
		Ids.Reset();
		Descriptions.Reset();
	}
};

#pragma endregion FCsAchievementQueryState