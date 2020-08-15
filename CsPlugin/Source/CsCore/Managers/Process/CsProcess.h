// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsPooledObjectOld.h"
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Types/CsTypes_String.h"
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "CsProcess.generated.h"

// Enums
#pragma region

	// Process
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsProcess : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsProcess)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsProcess)

struct CSCORE_API EMCsProcess : public TCsEnumStructMap<FECsProcess, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsProcess, FECsProcess, uint8)
};

#pragma endregion Process

	// ProcessRoutine
#pragma region

enum class ECsProcessRoutine : uint8
{
	StartRead_Internal,
	ECsProcessRoutine_MAX,
};

#define ECS_PROCESS_ROUTINE_MAX (uint8)ECsProcessRoutine::ECsProcessRoutine_MAX

struct CSCORE_API EMCsProcessRoutine : public TCsEnumMap<ECsProcessRoutine>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProcessRoutine, ECsProcessRoutine)
};

namespace NCsProcessRoutine
{
	namespace Ref
	{
		typedef ECsProcessRoutine Type;

		extern CSCORE_API const Type StartRead_Internal;
		extern CSCORE_API const Type ECsProcessRoutine_MAX;
	}
}

#pragma endregion ProcessRoutine

#pragma endregion Enums

// Output Event
#pragma region

UENUM(BlueprintType)
enum class ECsProcessMonitorOutputEventPurpose : uint8
{
	FireOnce								UMETA(DisplayName = "FireOnce"),
	Loop									UMETA(DisplayName = "Loop"),
	ECsProcessMonitorOutputEventPurpose_MAX	UMETA(Hidden),
};

#define ECS_PROCESS_MONITOR_OUTPUT_EVENT_PURPOSE (uint8)ECsProcessMonitorOutputEventPurpose::ECsProcessMonitorOutputEventPurpose_MAX

struct CSCORE_API EMCsProcessMonitorOutputEventPurpose : public TCsEnumMap<ECsProcessMonitorOutputEventPurpose>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProcessMonitorOutputEventPurpose, ECsProcessMonitorOutputEventPurpose)
};

namespace NCsProcessMonitorOutputEventPurpose
{
	namespace Ref
	{
		typedef ECsProcessMonitorOutputEventPurpose Type;

		extern CSCORE_API const Type FireOnce;
		extern CSCORE_API const Type Loop;
		extern CSCORE_API const Type ECsProcessMonitorOutputEventPurpose_MAX;
	}
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProcessMonitorOutputEvent_Completed, const FString&, Name);

USTRUCT(BlueprintType)
struct CSCORE_API FCsProcessMonitorOutputEvent
{
	GENERATED_USTRUCT_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FCompleted, const FString&);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	ECsProcessMonitorOutputEventPurpose Purpose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FCsStringParagraph Paragraph;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool Completed;

	FCompleted Event;
	UPROPERTY(BlueprintAssignable, Category = "Process")
	FBindableDynEvent_CsProcessMonitorOutputEvent_Completed ScriptEvent;

public:
	FCsProcessMonitorOutputEvent() :
		Name(),
		Purpose(ECsProcessMonitorOutputEventPurpose::ECsProcessMonitorOutputEventPurpose_MAX),
		Paragraph(),
		Completed(false)
	{
	}

	FCsProcessMonitorOutputEvent(const FString &InName, const FCsStringParagraph &InParagraph, const ECsProcessMonitorOutputEventPurpose &InPurpse) 
	{
		Name = InName;
		Paragraph = InParagraph;
		Purpose = InPurpse;
		Completed = false;
	}

	~FCsProcessMonitorOutputEvent() {}

	FCsProcessMonitorOutputEvent& operator=(const FCsProcessMonitorOutputEvent& B)
	{
		Name = B.Name;
		Purpose = B.Purpose;
		Paragraph = B.Paragraph;
		Completed = B.Completed;
		Event = B.Event;
		ScriptEvent = B.ScriptEvent;
		return *this;
	}

	bool operator==(const FCsProcessMonitorOutputEvent& B) const
	{
		if (Name != B.Name)
			return false;
		if (Purpose != B.Purpose)
			return false;
		if (Paragraph != B.Paragraph)
			return false;
		if (Completed != B.Completed)
			return false;
		return true;
	}

	bool operator!=(const FCsProcessMonitorOutputEvent& B) const
	{
		return !(*this == B);
	}

	void ProcessOutput(const FString &Output)
	{
		if (Completed)
			return;

		Paragraph.ProcessInput(Output);

		Completed = Paragraph.HasCompleted();

		if (Completed)
		{
			Event.Broadcast(Name);
#if WITH_EDITOR
			ScriptEvent.Broadcast(Name);
#endif // #if WITH_EDITOR
		}
	}

	void Clear()
	{
		Completed = false;
		Paragraph.Clear();
	}

	void Reset()
	{
		Clear();
		Event.Clear();
		ScriptEvent.Clear();
	}

	bool HasCompleted()
	{
		return Completed;
	}
};

#pragma endregion Output Event

// Payload
#pragma region

UENUM(BlueprintType)
enum class ECsProcessPriorityModifier : uint8
{
	Idle							UMETA(DisplayName = "Idle"),
	Low								UMETA(DisplayName = "Low"),
	Normal							UMETA(DisplayName = "Normal"),
	High							UMETA(DisplayName = "High"),
	Higher							UMETA(DisplayName = "Higher"),
	ECsProcessPriorityModifier_MAX	UMETA(Hidden),
};

#define ECS_PROCESS_PRIORITY_MODIFIER (uint8)ECsProcessPriorityModifier::ECsProcessPriorityModifier_MAX

struct CSCORE_API EMCsProcessPriorityModifier : public TCsEnumMap<ECsProcessPriorityModifier>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProcessPriorityModifier, ECsProcessPriorityModifier)
};

namespace NCsProcessPriorityModifier
{
	typedef ECsProcessPriorityModifier Type;

	namespace Ref
	{
		extern CSCORE_API const Type Idle;
		extern CSCORE_API const Type Low;
		extern CSCORE_API const Type Normal;
		extern CSCORE_API const Type High;
		extern CSCORE_API const Type Higher;
		extern CSCORE_API const Type ECsProcessPriorityModifier_MAX;
	}

	namespace Val
	{
		extern CSCORE_API const int32 Idle;
		extern CSCORE_API const int32 Low;
		extern CSCORE_API const int32 Normal;
		extern CSCORE_API const int32 High;
		extern CSCORE_API const int32 Higher;
	}

	FORCEINLINE const int32& ToInt32(const Type &EType)
	{
		if (EType == Type::Idle) { return Val::Idle; }
		if (EType == Type::Low) { return Val::Low; }
		if (EType == Type::Normal) { return Val::Normal; }
		if (EType == Type::High) { return Val::High; }
		if (EType == Type::Higher) { return Val::Higher; }
		return Val::Normal;
	}
}

struct FCsProcessPayload : public ICsPayload_PooledObject
{
	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	FCsTime Time;

	FString Name;

	/** executable name */
	FString URL;

	/** command line arguments */
	FString Params;

	/** if true, the new process will have its own window */
	bool bLaunchDetached;

	/** if true, the new process will be minimized in the task bar */
	bool bLaunchHidden;

	/** if true, the new process will not have a window or be in the task bar */
	bool bLaunchReallyHidden;

	/** idle, low, normal, high, higher */
	ECsProcessPriorityModifier PriorityModifier;

	/** Directory to start in when running the program, or NULL to use the current working directory */
	bool bOptionalWorkingDirectory;

	FString OptionalWorkingDirectory;

public:
	FCsProcessPayload() 
	{
		Reset();
	}
	~FCsProcessPayload() {}

	// ICsPayload_PooledObject
#pragma region

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	UObject* GetInstigator() const
	{
		return Instigator;
	}

	UObject* GetOwner() const
	{
		return Owner;
	}

	UObject* GetParent() const
	{
		return Parent;
	}

	FORCEINLINE const FCsTime& GetTime() const 
	{
		return Time;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;

		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;

		Time.Reset();

		Name = NCsCached::Str::Empty;
		URL = NCsCached::Str::Empty;
		Params = NCsCached::Str::Empty;
		bLaunchDetached = false;
		bLaunchHidden = false;
		bLaunchReallyHidden = false;
		PriorityModifier = ECsProcessPriorityModifier::Normal;
		bOptionalWorkingDirectory = false;
		OptionalWorkingDirectory = NCsCached::Str::Empty;
	}

#pragma endregion ICsPayload_PooledObject
};

#pragma endregion Payload

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_UCsProcess_OnOutputRecieved, const FString&, Name);

USTRUCT(BlueprintType)
struct FCsProcessCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FECsProcess Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString Name;
	/** executable name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString URL;
	/** command line arguments */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString Params;
	/** if true, the new process will have its own window */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool bLaunchDetached;
	/** if true, the new process will be minimized in the task bar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool bLaunchHidden;
	/** if true, the new process will not have a window or be in the task bar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool bLaunchReallyHidden;
	/** idle, low, normal, high, higher */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	ECsProcessPriorityModifier PriorityModifier;
	/** Directory to start in when running the program, or NULL to use the current working directory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool bOptionalWorkingDirectory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString OptionalWorkingDirectory;

	FCsProcessCache()
	{
		Reset();
	}

	~FCsProcessCache() {}

	void Init(FCsProcessPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		//Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Name = NCsCached::Str::Empty;
		URL = NCsCached::Str::Empty;
		Params = NCsCached::Str::Empty;
		bLaunchDetached = false;
		bLaunchHidden = false;
		bLaunchReallyHidden = false;
		PriorityModifier = ECsProcessPriorityModifier::Normal;
		bOptionalWorkingDirectory = false;
		OptionalWorkingDirectory = NCsCached::Str::Empty;
	}
};

UCLASS()
class CSCORE_API UCsProcess : public UCsPooledObjectOld
{
	GENERATED_UCLASS_BODY()

public:

	FCsProcessCache Cache;

	void Init(const int32 &Index, const FECsProcess &Type);
	void Allocate(FCsProcessPayload* Payload);

// Interface
#pragma region
public:

	void OnCreatePool();
	void DeAllocate();

#pragma endregion Interface

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8& Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type);

	static void RemoveRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8& Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8& Type);

#pragma endregion Routines

public:

	FProcHandle ProcessHandle;
	uint32 ProcessID;
	void* ReadPipeChild;
	void* WritePipeChild;
	void* ReadPipeParent;
	void* WritePipeParent;

	bool ReadFlag;

	UFUNCTION(BlueprintCallable, Category = "Process")
	void RunCommand(const FString& Command);
	
// Read / Output
#pragma region

	void StartRead();
	static char StartRead_Internal(FCsRoutine* r);
	FCsRoutine* StartRead_Internal_Routine;
	
	UFUNCTION(BlueprintCallable, Category = "Process")
	void StopRead();

private:

	TArray<FCsProcessMonitorOutputEvent> MonitorOutputEvents;

public:

	UFUNCTION(BlueprintCallable, Category = "Process")
	void AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent& Event);
	void ProcessMonitorOuputEvents(const FString& Output);
	void OnOutputRecieved(const FString& Output);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputRecieved, const FString&);

	FOnOutputRecieved OnOutputRecieved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Process")
	FBindableDynEvent_UCsProcess_OnOutputRecieved OnOutputRecieved_ScriptEvent;

#pragma endregion Read / Output
};