// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "ManagECs/PlayerProfile/CsTypes_PlayerProfile.h"

#include "CsTypes_Save.generated.h"
#pragma once

// Save
#pragma region

UENUM(BlueprintType)
enum class ECsSave : uint8
{
	Save1		UMETA(DisplayName = "Save 1"),
	Save2		UMETA(DisplayName = "Save 2"),
	Save3		UMETA(DisplayName = "Save 3"),
	Save4		UMETA(DisplayName = "Save 4"),
	Save5		UMETA(DisplayName = "Save 5"),
	Save6		UMETA(DisplayName = "Save 6"),
	Save7		UMETA(DisplayName = "Save 7"),
	Save8		UMETA(DisplayName = "Save 8"),
	ECsSave_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSave final : public TCsEnumMap<ECsSave>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSave, ECsSave)
};

namespace NCsSave
{
	typedef ECsSave Type;

	namespace Ref
	{
		extern CSCORE_API const Type Save1;
		extern CSCORE_API const Type Save2;
		extern CSCORE_API const Type Save3;
		extern CSCORE_API const Type Save4;
		extern CSCORE_API const Type Save5;
		extern CSCORE_API const Type Save6;
		extern CSCORE_API const Type Save7;
		extern CSCORE_API const Type Save8;
		extern CSCORE_API const Type ECsSave_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion Save

struct CSCORE_API FCsSaveFileInfo
{
public:

	static const FCsSaveFileInfo Invalid;

public:

	FString FileName;
	FString FileNameWithExt;

	bool bValid;

	// Read

	bool bRead;

	FDateTime ReadTime;

	FString ReadContents;

	// Write

	bool bWrite;

	FDateTime WriteTime;

	FString WriteContents;

	// Delete

	bool bDelete;

	FDateTime DeleteTime;

	FCsSaveFileInfo() :
		FileName(),
		FileNameWithExt(),
		bValid(false),
		bRead(false),
		ReadTime(),
		ReadContents(),
		bWrite(false),
		WriteTime(),
		WriteContents(),
		bDelete(false),
		DeleteTime()
	{
	}

	void Reset()
	{
		FileName = NCsCached::Str::Empty;
		FileNameWithExt = NCsCached::Str::Empty;
		bValid = false;
		bRead = false;
		ReadTime = FDateTime::Now();
		ReadContents.Empty();
		bWrite = false;
		WriteTime = FDateTime::Now();
		WriteContents.Empty();
		bDelete = false;
		DeleteTime = FDateTime::Now();
	}
};

struct CSCORE_API FCsSaveEnumerateUserFilesState
{
private:

	/** Is complete. */
	bool bComplete;

	/** Is queued. */
	bool bQueued;

public:

	/** Is Successful. */
	bool bSuccess;

	FCsSaveEnumerateUserFilesState() :
		bComplete(false),
		bQueued(false),
		bSuccess(false)
	{
	}

	void Queue()
	{
		bQueued = true;
	}

	bool IsQueued() const
	{
		return bQueued;
	}

	void Complete()
	{
		bComplete = true;
		bQueued = false;
	}

	bool IsComplete() const
	{
		return bComplete;
	}

	void Reset()
	{
		bComplete = false;
		bQueued = false;
		bSuccess = false;
	}
};

// SaveAction
#pragma region

UENUM(BlueprintType)
enum class ECsSaveAction : uint8
{
	Enumerate			UMETA(DisplayName = "Enumerate"),
	Read				UMETA(DisplayName = "Read"),
	ReadAll				UMETA(DisplayName = "Read All"),
	Write				UMETA(DisplayName = "Write"),
	WriteAll			UMETA(DisplayName = "Write All"),
	Delete				UMETA(DisplayName = "Delete"),
	DeleteAll			UMETA(DisplayName = "Delete All"),
	ECsSaveAction_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSaveAction final : public TCsEnumMap<ECsSaveAction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSaveAction, ECsSaveAction)
};

namespace NCsSaveAction
{
	typedef ECsSaveAction Type;

	namespace Ref
	{
		extern CSCORE_API const Type Enumerate;
		extern CSCORE_API const Type Read;
		extern CSCORE_API const Type ReadAll;
		extern CSCORE_API const Type Write;
		extern CSCORE_API const Type WriteAll;
		extern CSCORE_API const Type Delete;
		extern CSCORE_API const Type DeleteAll;
		extern CSCORE_API const Type ECsSaveAction_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion SaveAction

// SaveActionState
#pragma region

UENUM(BlueprintType)
enum class ECsSaveActionState : uint8
{
	None					UMETA(DisplayName = "None"),
	InProgress				UMETA(DisplayName = "In Progress"),
	Complete				UMETA(DisplayName = "Complete"),
	ECsSaveActionState_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSaveActionState final : public TCsEnumMap<ECsSaveActionState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSaveActionState, ECsSaveActionState)
};

namespace NCsSaveActionState
{
	typedef ECsSaveActionState Type;

	namespace Ref
	{
		extern CSCORE_API const Type None;
		extern CSCORE_API const Type InProgress;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsSaveActionState_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion SaveActionState

struct CSCORE_API FCsSaveActionInfo
{
public:

	/** Profile to perform the action on.
		If Profile == ECsPlayerProfile_MAX, then perform action on ALL Profiles. */
	ECsPlayerProfile Profile;

	/** Index of File in SaveFileInfos in UCsManager_Save. */
	int32 FileIndex;

	/** Action to processed. See ECsSaveAction. */
	ECsSaveAction Action;

	/** Whether to preform the Action on all contents vECsus a subset (i.e. Profile).
		This should primarily used as a debug option (Deleting All Saves, ... etc). */
	bool bAllContent;

private:

	/** Current state of the action (i.e. In Progress, Complete, ... etc). */
	ECsSaveActionState State;

	/** Whether the action completed successfully. */
	bool bSuccess;

public:

	FCsSaveActionInfo() :
		Profile(ECsPlayerProfile::ECsPlayerProfile_MAX),
		FileIndex(INDEX_NONE),
		Action(ECsSaveAction::ECsSaveAction_MAX),
		bAllContent(false),
		State(ECsSaveActionState::None),
		bSuccess(false)
	{

	}

	FORCEINLINE bool IsAllProfiles() const
	{
		return Profile == ECsPlayerProfile::ECsPlayerProfile_MAX;
	}

	FORCEINLINE bool IsReadyToProcess() const
	{
		return State == ECsSaveActionState::None;
	}

	FORCEINLINE void StartProgress()
	{
		State = ECsSaveActionState::InProgress;
	}

	FORCEINLINE bool InProgress() const
	{
		return State == ECsSaveActionState::InProgress;
	}

	FORCEINLINE void Complete()
	{
		State = ECsSaveActionState::Complete;
	}

	FORCEINLINE bool IsComplete() const
	{
		return State == ECsSaveActionState::Complete;
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
		Profile = ECsPlayerProfile::ECsPlayerProfile_MAX;
		FileIndex = INDEX_NONE;
		Action = ECsSaveAction::ECsSaveAction_MAX;
		bAllContent = false;
		State = ECsSaveActionState::None;
		bSuccess = false;
	}
};