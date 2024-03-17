// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"
#include "Types/CsCached.h"

#include "CsTypes_Save.generated.h"

// SaveStorage
#pragma region

UENUM(BlueprintType)
enum class ECsSaveStorage : uint8
{
	Local				UMETA(DisplayName = "Local"),
	Cloud				UMETA(DisplayName = "Cloud"),
	ECsSaveStorage_MAX	UMETA(Hidden),
};

struct CSPLATFORMSERVICES_API EMCsSaveStorage final : public TCsEnumMap<ECsSaveStorage>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSaveStorage, ECsSaveStorage)
};

namespace NCsSaveStorage
{
	typedef ECsSaveStorage Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type Local;
		extern CSPLATFORMSERVICES_API const Type Cloud;
		extern CSPLATFORMSERVICES_API const Type ECsSaveStorage_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

#pragma endregion SaveStorage

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

struct CSPLATFORMSERVICES_API EMCsSave final : public TCsEnumMap<ECsSave>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSave, ECsSave)
};

namespace NCsSave
{
	typedef ECsSave Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type Save1;
		extern CSPLATFORMSERVICES_API const Type Save2;
		extern CSPLATFORMSERVICES_API const Type Save3;
		extern CSPLATFORMSERVICES_API const Type Save4;
		extern CSPLATFORMSERVICES_API const Type Save5;
		extern CSPLATFORMSERVICES_API const Type Save6;
		extern CSPLATFORMSERVICES_API const Type Save7;
		extern CSPLATFORMSERVICES_API const Type Save8;
		extern CSPLATFORMSERVICES_API const Type ECsSave_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

#pragma endregion Save

// FCsSaveFileInfo
#pragma region

namespace NCsSave
{
	namespace NFile
	{
		struct CSPLATFORMSERVICES_API FInfo
		{
		public:

			static const FInfo Invalid;

		public:

			FString FileName;
			FString FileNameWithExt;

			bool bValid;

		// Read

			bool bRead;

			FDateTime ReadTime;

			FString ReadContents;

			int32 ReadCount;

		// Write

			bool bWrite;

			FDateTime WriteTime;

			FString WriteContents;

			int32 WriteCount;

		// Delete

			bool bDelete;

			FDateTime DeleteTime;

			int32 DeleteCount;

			FInfo() :
				FileName(),
				FileNameWithExt(),
				bValid(false),
				bRead(false),
				ReadTime(),
				ReadContents(),
				ReadCount(0),
				bWrite(false),
				WriteTime(),
				WriteContents(),
				WriteCount(0),
				bDelete(false),
				DeleteTime(),
				DeleteCount(0)
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
				ReadCount = 0;
				bWrite = false;
				WriteTime = FDateTime::Now();
				WriteContents.Empty();
				WriteCount = 0;
				bDelete = false;
				DeleteTime = FDateTime::Now();
				DeleteCount = 0;
			}
		};
	}
}

#pragma endregion NCsSave::NFile::FInfo

namespace NCsSave
{
	namespace NData
	{
		struct CSPLATFORMSERVICES_API FInfo
		{
		public:

			int32 SetCount;

			FInfo() :
				SetCount(0)
			{

			}
		};
	}
}

// NCsSave::FEnumerateUserFilesState
#pragma region

namespace NCsSave
{
	struct CSPLATFORMSERVICES_API FEnumerateUserFilesState
	{
	private:

		/** Is complete. */
		bool bComplete;

		/** Is queued. */
		bool bQueued;

		/** Is processing (currently in async call / process). */
		bool bProcessing;

	public:

		/** Is Successful. */
		bool bSuccess;

		FEnumerateUserFilesState() :
			bComplete(false),
			bQueued(false),
			bProcessing(false),
			bSuccess(false)
		{
		}

		void Complete()
		{
			bComplete = true;
			bQueued = false;
		}

		FORCEINLINE bool IsComplete() const { return bComplete; }

		FORCEINLINE void Queue() { bQueued = true; }

		FORCEINLINE bool IsQueued() const { return bQueued; }

		FORCEINLINE void StartProcessing() { bProcessing = true; }

		FORCEINLINE bool IsProcessing() const { return bProcessing; }

		FORCEINLINE void EndProcessing() { bProcessing = false; }

		FORCEINLINE bool IsCompleteAndNotProcessing() const { return bComplete && !bProcessing; }

		void Reset()
		{
			bComplete = false;
			bQueued = false;
			bProcessing = false;
			bSuccess = false;
		}
	};
}

#pragma endregion NCsSave::FEnumerateUserFilesState

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

struct CSPLATFORMSERVICES_API EMCsSaveAction final : public TCsEnumMap<ECsSaveAction>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSaveAction, ECsSaveAction)
};

namespace NCsSaveAction
{
	typedef ECsSaveAction Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type Enumerate;
		extern CSPLATFORMSERVICES_API const Type Read;
		extern CSPLATFORMSERVICES_API const Type ReadAll;
		extern CSPLATFORMSERVICES_API const Type Write;
		extern CSPLATFORMSERVICES_API const Type WriteAll;
		extern CSPLATFORMSERVICES_API const Type Delete;
		extern CSPLATFORMSERVICES_API const Type DeleteAll;
		extern CSPLATFORMSERVICES_API const Type ECsSaveAction_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsSave
{
	enum class EAction : uint8
	{
		Enumerate,
		Read,
		ReadAll,
		Write,
		WriteAll,
		Delete,
		DeleteAll,
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

			extern CSPLATFORMSERVICES_API const Type Enumerate;
			extern CSPLATFORMSERVICES_API const Type Read;
			extern CSPLATFORMSERVICES_API const Type ReadAll;
			extern CSPLATFORMSERVICES_API const Type Write;
			extern CSPLATFORMSERVICES_API const Type WriteAll;
			extern CSPLATFORMSERVICES_API const Type Delete;
			extern CSPLATFORMSERVICES_API const Type DeleteAll;
			extern CSPLATFORMSERVICES_API const Type EAction_MAX;
		}
	}
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

struct CSPLATFORMSERVICES_API EMCsSaveActionState final : public TCsEnumMap<ECsSaveActionState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSaveActionState, ECsSaveActionState)
};

namespace NCsSaveActionState
{
	typedef ECsSaveActionState Type;

	namespace Ref
	{
		extern CSPLATFORMSERVICES_API const Type None;
		extern CSPLATFORMSERVICES_API const Type InProgress;
		extern CSPLATFORMSERVICES_API const Type Complete;
		extern CSPLATFORMSERVICES_API const Type ECsSaveActionState_MAX;
	}

	extern CSPLATFORMSERVICES_API const uint8 MAX;
}

namespace NCsSave
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

#pragma endregion SaveActionState

// NCsSave::NAction::FInfo
#pragma region

namespace NCsSave
{
	namespace NAction
	{
		namespace NInfo
		{
			struct CSPLATFORMSERVICES_API FInfo
			{
			public:

			#define ActionType NCsSave::EAction
			#define ActionStateType NCsSave::NAction::EState

				/** Profile to perform the action on.
					If Profile == ECsPlayerProfile_MAX, then perform action on ALL Profiles. */
				ECsPlayerProfile Profile;

				/** Index of File in SaveFileInfos in UCsManager_Save. */
				int32 FileIndex;

				/** Action to processed. See ECsSaveAction. */
				ActionType Action;

				/** Data to be used in the action. */
				FString Data;

			private:

				/** Current state of the action (i.e. In Progress, Complete, ... etc). */
				ActionStateType State;

				/** Whether the action completed successfully. */
				bool bSuccess;

			public:

				FInfo() :
					Profile(ECsPlayerProfile::ECsPlayerProfile_MAX),
					FileIndex(INDEX_NONE),
					Action(ActionType::EAction_MAX),
					Data(),
					State(ActionStateType::None),
					bSuccess(false)
				{

				}

				FORCEINLINE bool IsAllProfiles() const
				{
					return Profile == ECsPlayerProfile::ECsPlayerProfile_MAX;
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
					Profile = ECsPlayerProfile::ECsPlayerProfile_MAX;
					FileIndex = INDEX_NONE;
					Action = ActionType::EAction_MAX;
					Data.Empty();
					State = ActionStateType::None;
					bSuccess = false;
				}

			#undef ActionType
			#undef ActionStateType
			};
		}
	}
}

#pragma endregion FCsSaveActionInfo