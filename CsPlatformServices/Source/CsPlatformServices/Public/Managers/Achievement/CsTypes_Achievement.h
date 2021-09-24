// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
// DataTable
#include "Engine/DataTable.h"

#include "CsTypes_Achievement.generated.h"
#pragma once

// Achievement
#pragma region

USTRUCT(BlueprintType)
struct CSPLATFORMSERVICES_API FECsAchievement : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsAchievement)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsAchievement)

struct CSPLATFORMSERVICES_API EMCsAchievement : public TCsEnumStructMap<FECsAchievement, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsAchievement, FECsAchievement, uint8)
};

namespace NCsAchievement
{
	/**
	* Update the enum map: EMCsAchievement from the settings of type: UCsPlatformServicesSettings
	*
	* @param Context	Calling context / function
	*/
	CSPLATFORMSERVICES_API void PopulateEnumMapFromSettings(const FString& Context);
}
#pragma endregion Achievement

// AchievementState
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementState : uint8
{
	None					UMETA(DisplayName = "None"),
	InProgress				UMETA(DisplayName = "In Progress"),
	Completed				UMETA(DisplayName = "Completed"),
	ECsAchievementState_MAX	UMETA(Hidden),
};

struct CSPLATFORMSERVICES_API EMCsAchievementState final : public TCsEnumMap<ECsAchievementState>
{
	CS_ENUM_MAP_BODY(EMCsAchievementState, ECsAchievementState)
};

namespace NCsAchievementState
{
	typedef ECsAchievementState Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type None;
		extern CSPLATFORMSERVICES_API const Type InProgress;
		extern CSPLATFORMSERVICES_API const Type Completed;
		extern CSPLATFORMSERVICES_API const Type ECsAchievementState_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsAchievement
{
	enum class EState : uint8
	{
		None,
		InProgress,
		Completed,
		EState_MAX
	};

	struct CSPLATFORMSERVICES_API EMState final : public TCsEnumMap<EState>
	{
		CS_ENUM_MAP_BODY(EMState, EState)
	};

	namespace NState
	{
		namespace Ref
		{
			typedef EState Type;

			extern CSPLATFORMSERVICES_API const Type None;
			extern CSPLATFORMSERVICES_API const Type InProgress;
			extern CSPLATFORMSERVICES_API const Type Completed;
			extern CSPLATFORMSERVICES_API const Type EState_MAX;
		}
	}
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

struct CSPLATFORMSERVICES_API EMCsAchievementProgress final : public TCsEnumMap<ECsAchievementProgress>
{
	CS_ENUM_MAP_BODY(EMCsAchievementProgress, ECsAchievementProgress)
};

namespace NCsAchievementProgress
{
	typedef ECsAchievementProgress Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type Normalized;
		extern CSPLATFORMSERVICES_API const Type Standard;
		extern CSPLATFORMSERVICES_API const Type Binary;
		extern CSPLATFORMSERVICES_API const Type Count;
		extern CSPLATFORMSERVICES_API const Type Bitfield;
		extern CSPLATFORMSERVICES_API const Type ECsAchievementProgress_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsAchievement
{
	enum class EProgress : uint8 
	{
		// [0.0, 1.0] Inclusive.
		Normalized,
		// [0.0, 100.0] Inclusive.
		Standard,
		// [0.0, 100.0] Inclusive. Internally only values supported are 0.0 = Lock and 100.0 = Unlock.
		Binary,
		// [0.0, 100.0] Inclusive. Internally [0, N] Inclusive. X out of N.
		Count,
		// [0.0, 100.0] Inclusive. Internally check against bits set for a mask (i.e. 010010, ... etc).
		Bitfield,
		EProgress_MAX
	};

	struct CSPLATFORMSERVICES_API EMProgress final : public TCsEnumMap<EProgress>
	{
		CS_ENUM_MAP_BODY(EMProgress, EProgress)
	};

	namespace NProgress
	{
		namespace Ref
		{
			typedef EProgress Type;

			extern CSPLATFORMSERVICES_API const Type Normalized;
			extern CSPLATFORMSERVICES_API const Type Standard;
			extern CSPLATFORMSERVICES_API const Type Binary;
			extern CSPLATFORMSERVICES_API const Type Count;
			extern CSPLATFORMSERVICES_API const Type Bitfield;
			extern CSPLATFORMSERVICES_API const Type EProgress_MAX;
		}
	}
}

#pragma endregion AchievementProgress

// NCsAchievement::EValue
#pragma region

namespace NCsAchievement
{
	enum class EValue : uint8
	{
		Float,
		Integer,
		String,
		EValue_MAX
	};

	struct CSPLATFORMSERVICES_API EMValue final : public TCsEnumMap<EValue>
	{
		CS_ENUM_MAP_BODY(EMValue, EValue)
	};

	namespace NValue
	{
		namespace Ref
		{
			typedef EValue Type;

			extern CSPLATFORMSERVICES_API const Type Float;
			extern CSPLATFORMSERVICES_API const Type Integer;
			extern CSPLATFORMSERVICES_API const Type String;
			extern CSPLATFORMSERVICES_API const Type EValue_MAX;
		}
	}
}

#pragma endregion NCsAchievement::EValue

// ICsAchievement
#pragma region

struct CSPLATFORMSERVICES_API ICsAchievement
{
public:

	virtual ~ICsAchievement(){}

#define ProgressType NCsAchievement::EProgress
#define StateType NCsAchievement::EState

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
	*  See ProgressType (NCsAchievement::EProgress (Normalized, Standard, ... etc)).
	*
	* return Progress Type.
	*/
	virtual const ProgressType& GetProgressType() const = 0;

	/**
	* Set the Progress Type.
	*  See ProgressType (NCsAchievement::EProgress (Normalized, Standard, ... etc)).
	*
	* @param InProgressType		New Progress Type.
	*/
	virtual void SetProgressType(const ProgressType& InProgressType) = 0;

	/**
	* Get the current Progress. The value is in the range defined by the Progress Type.
	*  See ProgressType (NCsAchievement::EProgress (Normalized, Standard, ... etc)).
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

	virtual float CalculateProgress(const float& InPercent) = 0;

	/**
	* Get the current Count toward unlocking the Achievement.
	*
	* return	Current Count toward unlocking the Achievement.
	*/
	virtual const uint64& GetCount() const = 0;

	/**
	* Get the maximum Count to unlock the Achievement.
	*  Progress Type must be Count.
	*
	* return	Count to unlock the Achievement.
	*/
	virtual const uint64& GetMaxCount() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FString GetBitfield() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const uint32& GetBitfieldLength() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const uint32& GetUnlockBitfieldLength() const = 0;

	/**
	*
	*
	* @param Index
	* return
	*/
	virtual const FString& GetBitMask(const uint32& Index) const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FString& GetBitMaskNone() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const FString& GetBitMaskComplete() const = 0;

	/**
	*
	*
	* return
	*/
	virtual const uint32& GetNumBitsSet() const = 0;

	/**
	*
	*
	* @param Index
	* return
	*/
	virtual bool IsBitSet(const uint32& Index) const = 0;

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
	virtual const StateType& GetState() const = 0;

	/**
	* Get the Title of the Achievement (i.e. Achievement 1 Title).
	*
	* return Title.
	*/
	virtual const FText& GetTitle() const = 0;

	/**
	* Get the Description of the Achievement (i.e. Locked Achievement 1).
	*
	* return Description.
	*/
	virtual const FText& GetDescription() const = 0;

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

#undef ProgressType
#undef StateType
};

#pragma endregion ICsAchievement

// FCsAchievement
#pragma region

struct CSPLATFORMSERVICES_API FCsAchievement : public ICsAchievement
{
public:

#define StateType NCsAchievement::EState
	/** */
	FString Id;

protected:

	/** */
	bool bValid;

	/** */
	NCsAchievement::EProgress ProgressType;

	/** */
	float Progress;

	/** */
	float MinProgress;
	/** */
	float MaxProgress;

	/** */
	uint64 Count;

	/** */
	uint64 MaxCount;

	/** */
	FString Bitfield;
	/** */
	uint32 BitfieldLength;

	/** */
	uint32 UnlockBitfieldLength;

	/** */
	uint32 NumBitsSet;

	/** */
	TArray<FString> BitMasks;

	/** */
	FString BitMaskNone;

	/** */
	FString BitMaskComplete;

	/** */
	float Percent;

public:

	/** */
	FECsAchievement Type;

protected:

	/** */
	StateType State;

public:

	/** */
	FText Title;

	/** */
	FText Description;

	/** */
	FText UnlockDescription;

	/** */
	bool bHidden;

	/** */
	FDateTime UnlockTime;

	FCsAchievement() :
		Id(),
		bValid(true),
		ProgressType(NCsAchievement::EProgress::Normalized),
		Progress(0.0f),
		MinProgress(0.0f),
		MaxProgress(1.0f),
		Count(0ull),
		MaxCount(0ull),
		Bitfield(),
		BitfieldLength(0),
		UnlockBitfieldLength(0),
		NumBitsSet(0),
		BitMasks(),
		BitMaskNone(),
		BitMaskComplete(),
		Percent(0.0f),
		Type(),
		State(StateType::None),
		Title(),
		Description(),
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

	FORCEINLINE const FString& GetId() const { return Id; }
	FORCEINLINE const bool& IsValid() const { return bValid; }
	FORCEINLINE void SetValid() { bValid = true; }
	FORCEINLINE void SetInvalid() { bValid = false; }
	FORCEINLINE const NCsAchievement::EProgress& GetProgressType() const { return ProgressType; }
	FORCEINLINE const float& GetProgress() const { return Progress; }
	FORCEINLINE const float& GetProgressAsPercent() const { return Percent; }

	float CalculateProgress(const float& InPercent)
	{
		float P = FMath::Clamp(InPercent, 0.0f, 1.0f);
		return (P * (MaxProgress - MinProgress)) + MinProgress;
	}

	FORCEINLINE const uint64& GetCount() const { return Count; }
	FORCEINLINE const uint64& GetMaxCount() const { return MaxCount; }
	FORCEINLINE const FString GetBitfield() const { return Bitfield; }
	FORCEINLINE const uint32& GetBitfieldLength() const { return BitfieldLength; }
	FORCEINLINE const uint32& GetUnlockBitfieldLength() const { return UnlockBitfieldLength; }
	FORCEINLINE const FString& GetBitMask(const uint32& Index) const { return Index < (uint32)BitMasks.Num() ? BitMasks[Index] : BitMaskNone; }
	FORCEINLINE const FString& GetBitMaskNone() const { return BitMaskNone; }
	FORCEINLINE const FString& GetBitMaskComplete() const { return BitMaskComplete; }
	FORCEINLINE const uint32& GetNumBitsSet() const { return NumBitsSet; }
	FORCEINLINE bool IsBitSet(const uint32& Index) const { return Index < (uint32)Bitfield.Len() ? Bitfield[Index] == '1' : false; }
	FORCEINLINE const FECsAchievement& GetType() const { return Type; }
	FORCEINLINE const StateType& GetState() const { return State; }
	FORCEINLINE const FText& GetTitle() const { return Title; }
	FORCEINLINE const FText& GetDescription() const { return Description; }
	FORCEINLINE const FText& GetUnlockedDescription() const { return UnlockDescription; }
	FORCEINLINE const bool& IsHidden() const { return bHidden; }
	FORCEINLINE const FDateTime& GetUnlockTime() const { return UnlockTime; }

	void Complete()
	{
		Progress	   = MaxProgress;
		Count		   = MaxCount;

		// TODO: Set number of bits equal to UnlockBitfieldLength
		//Bitfield	   = UnlockBitfield;
		//BitfieldLength = UnlockBitfieldLength;
		Percent		   = 1.0f;
		State		   = StateType::Completed;
	}

#pragma endregion ICsAchievement

	/**
	* Set the Progress Type.
	*  See ERsAchievementProgress (Normalized, Standard, ... etc).
	*
	* @param InProgressType		New Progress Type.
	*/
	void SetProgressType(const NCsAchievement::EProgress& InProgressType);

	/**
	* Set the Progress. The value is adjusted to range defined by the Progress Type.
	*  See ERsAchievementProgress (Normalized, Standard, ... etc).
	*
	* @param InPercent	Value between [0, 1].
	*/
	void SetProgress(const float& InPercent);

	/**
	*
	*
	* @param InCount
	*/
	void SetCount(const uint64& InCount);

	/**
	* Set the maximum Count to unlock the Achievement.
	*  Progress Type must be Count.
	*
	* @param InCount	New Count to unlock the Achievement.
	*/
	void SetMaxCount(const uint64& InCount);

	/**
	*
	*/
	FORCEINLINE void IncrementCount(){ SetCount(Count + 1); }

	/**
	*
	*
	* @param InCount
	*/
	FORCEINLINE void IncrementCountBy(const uint64& InCount) { SetCount(Count + InCount); }

	/**
	*
	*
	* @param InCount
	* return
	*/
	FORCEINLINE uint64 CalculateCount(const uint64& InCount) { return FMath::Min(InCount, MaxCount); }

	/**
	*
	*
	* @param InBitfield
	*/
	void SetBitfield(const FString& InBitfield);

	/**
	*
	*
	* @param InBitfield
	*/
	void OrBitfield(const FString& InBitfield);

	/**
	*
	*
	* @param Length
	*/
	FORCEINLINE void SetUnlockBitfieldLength(const uint32& Length) { UnlockBitfieldLength = Length; }

	/**
	*
	*
	* @param Index
	*/
	void SetBit(const uint32& Index);

	/**
	*
	*
	* @param Index
	*/
	void ClearBit(const uint32& Index);

	bool IsValidBitfield(const FString& InBitfield);

#undef StateType
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
	Create						UMETA(DisplayName = "Create"),
	Modify						UMETA(DisplayName = "Modify"),
	Remove						UMETA(DisplayName = "Remove"),
	RemoveAll					UMETA(DisplayName = "Remove All"),
	Write						UMETA(DisplayName = "Write"),
	Complete					UMETA(DisplayName = "Complete"),
	CompleteAll					UMETA(DisplayName = "Complete All"),
	Reset						UMETA(DisplayName = "Reset"),
	ResetAll					UMETA(DisplayName = "Reset All"),
	ECsAchievementAction_MAX	UMETA(Hidden),
};

struct CSPLATFORMSERVICES_API EMCsAchievementAction final : public TCsEnumMap<ECsAchievementAction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAchievementAction, ECsAchievementAction)
};

namespace NCsAchievementAction
{
	typedef ECsAchievementAction Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type QueryIds;
		extern CSPLATFORMSERVICES_API const Type QueryDescriptions;
		extern CSPLATFORMSERVICES_API const Type UpdateDescriptions;
		extern CSPLATFORMSERVICES_API const Type Create;
		extern CSPLATFORMSERVICES_API const Type Modify;
		extern CSPLATFORMSERVICES_API const Type Remove;
		extern CSPLATFORMSERVICES_API const Type RemoveAll;
		extern CSPLATFORMSERVICES_API const Type Write;
		extern CSPLATFORMSERVICES_API const Type Complete;
		extern CSPLATFORMSERVICES_API const Type CompleteAll;
		extern CSPLATFORMSERVICES_API const Type Reset;
		extern CSPLATFORMSERVICES_API const Type ResetAll;
		extern CSPLATFORMSERVICES_API const Type ECsAchievementAction_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsAchievement
{
	enum class EAction : uint8
	{
		QueryIds,
		QueryDescriptions,
		UpdateDescriptions,
		Create,
		Modify,
		Remove,
		RemoveAll,
		Write,
		Complete,
		CompleteAll,
		Reset,
		ResetAll,
		EAction_MAX
	};

	struct CSPLATFORMSERVICES_API EMAction final : public TCsEnumMap<EAction>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAction, EAction)
	};

	namespace NAction
	{
		namespace Ref
		{
			typedef EAction Type;

			extern CSPLATFORMSERVICES_API const Type QueryIds;
			extern CSPLATFORMSERVICES_API const Type QueryDescriptions;
			extern CSPLATFORMSERVICES_API const Type UpdateDescriptions;
			extern CSPLATFORMSERVICES_API const Type Create;
			extern CSPLATFORMSERVICES_API const Type Modify;
			extern CSPLATFORMSERVICES_API const Type Remove;
			extern CSPLATFORMSERVICES_API const Type RemoveAll;
			extern CSPLATFORMSERVICES_API const Type Write;
			extern CSPLATFORMSERVICES_API const Type Complete;
			extern CSPLATFORMSERVICES_API const Type CompleteAll;
			extern CSPLATFORMSERVICES_API const Type Reset;
			extern CSPLATFORMSERVICES_API const Type ResetAll;
			extern CSPLATFORMSERVICES_API const Type EAction_MAX;
		}
	}
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

struct CSPLATFORMSERVICES_API EMCsAchievementActionState final : public TCsEnumMap<ECsAchievementActionState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAchievementActionState, ECsAchievementActionState)
};

namespace NCsAchievementActionState
{
	typedef ECsAchievementActionState Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type None;
		extern CSPLATFORMSERVICES_API const Type InProgress;
		extern CSPLATFORMSERVICES_API const Type Complete;
		extern CSPLATFORMSERVICES_API const Type ECsAchievementActionState_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsAchievement
{
	namespace NAction
	{
		enum class EState : uint8 
		{
			None,
			InProgress,
			Complete,
			EState_MAX
		};

		struct CSPLATFORMSERVICES_API EMState final : public TCsEnumMap<EState>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMState, EState)
		};

		namespace NState
		{
			namespace Ref
			{
				typedef EState Type;

				extern CSPLATFORMSERVICES_API const Type None;
				extern CSPLATFORMSERVICES_API const Type InProgress;
				extern CSPLATFORMSERVICES_API const Type Complete;
				extern CSPLATFORMSERVICES_API const Type EState_MAX;
			}
		}
	}
}

#pragma endregion AchievementActionState

// NCsAchievement::NAction::EAllocation
#pragma region

namespace NCsAchievement
{
	namespace NAction
	{
		enum class EAllocation : uint8
		{
			AfterTail,
			AsHead,
			AfterHead,
			EAllocation_MAX
		};

		struct CSPLATFORMSERVICES_API EMAllocation final : public TCsEnumMap<EAllocation>
		{
			CS_ENUM_MAP_BODY(EMAllocation, EAllocation)
		};

		namespace NAllocation
		{
			typedef EAllocation Type;

			namespace Ref
			{
				extern CSPLATFORMSERVICES_API const Type AfterTail;
				extern CSPLATFORMSERVICES_API const Type AsHead;
				extern CSPLATFORMSERVICES_API const Type AfterHead;
				extern CSPLATFORMSERVICES_API const Type EAllocation_MAX;
			}

			extern CSPLATFORMSERVICES_API const uint8 MAX;
		}
	}
}

#pragma endregion NCsAchievement::NAction::EAllocation

// NCsAchievement::FValue
#pragma region

namespace NCsAchievement
{
	struct CSPLATFORMSERVICES_API FValue
	{
	public:

		NCsAchievement::EValue ValueType;

		float Percent;

		uint64 Count;

		FString Bitfield;

		FValue() :
			ValueType(NCsAchievement::EValue::EValue_MAX),
			Percent(0.0f),
			Count(0ull),
			Bitfield()
		{
		}

		void Reset()
		{
			ValueType = NCsAchievement::EValue::EValue_MAX;
			Percent = 0.0f;
			Count = 0ull;
			Bitfield.Empty();
		}

		void SetPercent(const float& Value)
		{
			ValueType = NCsAchievement::EValue::Float;
			Percent   = Value;
		}

		void SetCount(const uint64& Value)
		{
			ValueType = NCsAchievement::EValue::Integer;
			Count	  = Value;
		}

		void SetBitfield(const FString& Value)
		{
			ValueType = NCsAchievement::EValue::String;
			Bitfield  = Value;
		}
	};
}

#pragma endregion FRsAchievementValue

// AchievementWritePolicy
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementWritePolicy : uint8
{
	Client							UMETA(DisplayName = "Client"),
	Server							UMETA(DisplayName = "Server"),
	ECsAchievementWritePolicy_MAX	UMETA(Hidden),
};

struct CSPLATFORMSERVICES_API EMCsAchievementWritePolicy final : public TCsEnumMap<ECsAchievementWritePolicy>
{
	CS_ENUM_MAP_BODY(EMCsAchievementWritePolicy, ECsAchievementWritePolicy)
};

namespace NCsAchievementWritePolicy
{
	typedef ECsAchievementWritePolicy Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type Client;
		extern CSPLATFORMSERVICES_API const Type Server;
		extern CSPLATFORMSERVICES_API const Type ECsAchievementProgress_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

#pragma endregion AchievementWritePolicy

// FCsAchievementEntry
#pragma region

USTRUCT(BlueprintType)
struct CSPLATFORMSERVICES_API FCsAchievementEntry : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	/** Name used as the API Name on most platforms.
		Name used to reference the achievement internally. 
	    Should be UNIQUE and the SAME name as the Row Name. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	/** Name displayed to the user in script (i.e. blueprint).
		Should be UNIQUE. If Empty, Name will be used as the DisplayName. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString DisplayName;

	/** Whether this achievement is currently valid.
	     Can be completed by the user.
		 Is Visible.
		 Can be updated. 
		 
		Platform Equivalents:
		 Oculus: is_archived */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bValid;

	/** Determines who is allowed to write the achievement
	    progress. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECsAchievementWritePolicy WritePolicy;

	/** How progress of the achievement is tracked. 
		 Normalized	[0.0, 1.0] Inclusive.
		 Standard	[0.0, 100.0] Inclusive.
		 Binary		[0.0, 100.0] Inclusive. Internally only values supported are 0.0 = Lock and 100.0 = Unlock.
		 Count		[0.0, 100.0] Inclusive. Internally [0, N] Inclusive. X out of N.
		 Bitfield	[0.0, 100.0] Inclusive. Internally check against bits set for a mask (i.e. 010010, ... etc).

		For some platforms Normalized, Standard, and Binary are the same. 
		
		Platform Equivalents:
		 Oculus: (Normalized | Standard | Binary) = Simple */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ECsAchievementProgress ProgressType;

	/** ProgressType MUST be Count or Bitfield to use this property.
		The number to reach before the achievement is unlocked. 
		
		Platform Equivalents:
		 Oculus: Target */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int64 Count;

	/** ProgressType MUST be Bitfield to use this property.
		The size of the bitfield. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 BitfieldLength;

	/** Name of the achievement the user sees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Title;

	/** The text description the user sees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;

	/** Optional. Might not be supported on some platforms. 
	    The text description that the user sees when the 
		achievement is unlocked. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString UnlockedDescription;

	/** Optional. Might not be supported on some platforms. 
	    Indicates whether the achievement is hidden until 
		earned. 
		
		Platform Equivalents:
		 Oculus: is_secret */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bHidden;

	FCsAchievementEntry() :
		Name(),
		DisplayName(),
		bValid(true),
		WritePolicy(ECsAchievementWritePolicy::Client),
		ProgressType(ECsAchievementProgress::Standard),
		Count(0ull),
		BitfieldLength(0),
		Title(),
		Description(),
		UnlockedDescription(),
		bHidden(false)
	{
	}

	FORCEINLINE bool operator==(const FCsAchievementEntry& B) const
	{
		return Name == B.Name &&
			   bValid == B.bValid &&
			   WritePolicy == B.WritePolicy &&
			   ProgressType == B.ProgressType &&
			   Count == B.Count &&
			   BitfieldLength == B.BitfieldLength &&
			   bHidden == B.bHidden &&
			   DisplayName == B.DisplayName &&
			   Title == B.Title &&
			   Description == B.Description &&
			   UnlockedDescription == B.UnlockedDescription;
	}

	FORCEINLINE bool operator!=(const FCsAchievementEntry& B) const
	{
		return !(*this == B);
	}

	void Reset()
	{
		Name.Empty();
		DisplayName.Empty();
		WritePolicy = ECsAchievementWritePolicy::Client;
		ProgressType = ECsAchievementProgress::Standard;
		Count = 0ull;
		BitfieldLength = 0;
		Title.Empty();
		Description.Empty();
		UnlockedDescription.Empty();
		bHidden = false;
	}
};

#pragma endregion FCsAchievementEntry

// NCsAchievement::NAction::NInfo::FInfo
#pragma region

namespace NCsAchievement
{
	namespace NAction
	{
		namespace NInfo
		{
			struct CSPLATFORMSERVICES_API FInfo
			{
			public:

			#define ActionType NCsAchievement::EAction
			#define ValueType NCsAchievement::FValue
			#define ActionStateType NCsAchievement::NAction::EState

				/** Action to processed. See ActionType (NCsAchievement::EAction). */
				ActionType Action;

				/** Achievement to perform Action on. */
				FECsAchievement Achievement;

				/** If Action == Remove, this will be the name of the
					achievement removed. */
				FString Name;

				/** If Action == Write, value type to write. */
				ValueType Value;

				/** If Action == Create | Modify, the appropriate data to update. */
				FCsAchievementEntry Entry;

			private:

				/** Current state of the action (i.e. In Progress, Complete, ... etc). */
				ActionStateType State;

				/** Whether the action completed successfully. */
				bool bSuccess;

			public:

				FInfo() :
					Action(ActionType::EAction_MAX),
					Achievement(),
					Name(),
					Value(),
					Entry(),
					State(ActionStateType::None),
					bSuccess(false)
				{

				}

				FORCEINLINE bool IsReadyToProcess() const
				{
					return State == ActionStateType::None;
				}

				FORCEINLINE void StartProgress()
				{
					State = ActionStateType::InProgress;
				}

				FORCEINLINE bool InProgress() const
				{
					return State == ActionStateType::InProgress;
				}

				FORCEINLINE void Complete()
				{
					State = ActionStateType::Complete;
				}

				FORCEINLINE bool IsComplete() const
				{
					return State == ActionStateType::Complete;
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
					Action = ActionType::EAction_MAX;
					Achievement = EMCsAchievement::Get().GetMAX();
					Value.Reset();
					Entry.Reset();
					State = ActionStateType::None;
					bSuccess = false;
				}

			#undef ActionType
			#undef ValueType
			#undef ActionStateType
			};
		}
	}
}

#pragma endregion NCsAchievement::NAction::NInfo::FInfo

// NCsAchievement::NWrite::FState
#pragma region

namespace NCsAchievement
{
	namespace NWrite
	{
		struct CSPLATFORMSERVICES_API FState
		{
		private: 

			bool bLocked;

		public:

			bool bComplete;

			bool bSuccess;

			FState() :
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
	}
}

#pragma endregion NCsAchievement::NWrite::FState

// FCsAchievementToWrite
#pragma region

struct CSPLATFORMSERVICES_API FCsAchievementToWrite
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

#pragma endregion FCsAchievementToWrite

// AchievementQueryOrder
#pragma region

UENUM(BlueprintType)
enum class ECsAchievementQueryOrder : uint8
{
	IdsFirst						UMETA(DisplayName = "Ids First"),
	DescriptionsFirst				UMETA(DisplayName = "Descriptions First"),
	ECsAchievementQueryOrder_MAX	UMETA(Hidden),
};

struct CSPLATFORMSERVICES_API EMCsAchievementQueryOrder final : public TCsEnumMap<ECsAchievementQueryOrder>
{
	CS_ENUM_MAP_BODY(EMCsAchievementQueryOrder, ECsAchievementQueryOrder)
};

namespace NCsAchievementQueryOrder
{
	typedef ECsAchievementQueryOrder Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type IdsFirst;
		extern CSPLATFORMSERVICES_API const Type DescriptionsFirst;
		extern CSPLATFORMSERVICES_API const Type ECsAchievementQueryOrder_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsAchievement
{
	namespace NQuery
	{
		enum class EOrder : uint8 
		{
			IdsFirst,
			DescriptionsFirst,
			EOrder_MAX
		};

		struct CSPLATFORMSERVICES_API EMOrder final : public TCsEnumMap<EOrder>
		{
			CS_ENUM_MAP_BODY(EMOrder, EOrder)
		};

		namespace NOrder
		{
			namespace Ref
			{
				typedef EOrder Type;

				extern CSPLATFORMSERVICES_API const Type IdsFirst;
				extern CSPLATFORMSERVICES_API const Type DescriptionsFirst;
				extern CSPLATFORMSERVICES_API const Type EOrder_MAX;
			}
		}
	}
}

#pragma endregion AchievementQueryOrder

// NCsAchievement::NQuery::FIdsState
#pragma region

namespace NCsAchievement
{
	namespace NQuery
	{
		struct CSPLATFORMSERVICES_API FIdsState
		{
		private:

			bool bComplete;
			bool bProcessing;
			bool bQueue;

		public:

			bool bSuccess;

			FIdsState() :
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
	}
}

#pragma endregion NCsAchievement::NQuery::FIdsState

// NCsAchievement::NQuery::FDescriptionsState
#pragma region

namespace NCsAchievement
{
	namespace NQuery
	{
		struct CSPLATFORMSERVICES_API FDescriptionsState
		{
		private:

			bool bComplete;
			bool bProcessing;
			bool bQueue;

		public:

			bool bSuccess;

			FDescriptionsState() :
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
	}
}

#pragma endregion NCsAchievement::NQuery::FDescriptionsState

// NCsAchievement::NQuery::FState
#pragma region

namespace NCsAchievement
{
	namespace NQuery
	{
		struct CSPLATFORMSERVICES_API FState
		{
		public:

			NCsAchievement::NQuery::FIdsState Ids;

			NCsAchievement::NQuery::FDescriptionsState Descriptions;

			FState() :
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
	}
}

#pragma endregion NCsAchievement::NQuery::FState