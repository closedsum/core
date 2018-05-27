// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/CsPooledObject.h"
#include "Types/CsTypes_Pool.h"
#include "Types/CsTypes_String.h"
#include "CsProcess.generated.h"

// Enums
#pragma region

USTRUCT(BlueprintType)
struct FECsProcess : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

public:
	FECsProcess(){}
	FECsProcess(const uint8 &InValue, const FString &InName, const FString &InDisplayName) : FECsEnum_uint8(InValue, InName, InDisplayName) {}
	FECsProcess(const uint8 &InValue, const FString &InName) : FECsEnum_uint8(InValue, InName) {}
	~FECsProcess() {}
};

FORCEINLINE uint32 GetTypeHash(const FECsProcess& b)
{
	return GetTypeHash(b.Name) ^ GetTypeHash(b.Value);
}

struct CSCORE_API EMCsProcess : public TCsEnumMap<FECsProcess, uint8>
{
protected:
	EMCsProcess(){}
	EMCsProcess(const EMCsProcess &) = delete;
	EMCsProcess(EMCsProcess &&) = delete;
public:
	~EMCsProcess(){}
private:
	static EMCsProcess* Instance;

public:
	static EMCsProcess& Get();
};

namespace ECsProcessRoutine
{
	enum Type
	{
		StartRead_Internal,
		ECsProcessRoutine_MAX,
	};
}

namespace ECsProcessRoutine
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString StartRead_Internal;
	}

	namespace Ref
	{
		extern const Type StartRead_Internal;
		extern const Type ECsProcessRoutine_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::StartRead_Internal) { return Str::StartRead_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::StartRead_Internal) { return Ref::StartRead_Internal; }
		return Ref::ECsProcessRoutine_MAX;
	}
}

#define ECS_PROCESS_ROUTINE_MAX (uint8)ECsProcessRoutine::ECsProcessRoutine_MAX
typedef ECsProcessRoutine::Type TCsProcessRoutine;

#pragma endregion Enums

// Output Event
#pragma region

UENUM(BlueprintType)
namespace ECsProcessMonitorOutputEventPurpose
{
	enum Type
	{
		FireOnce								UMETA(DisplayName = "FireOnce"),
		Loop									UMETA(DisplayName = "Loop"),
		ECsProcessMonitorOutputEventPurpose_MAX	UMETA(Hidden),
	};
}

#define ECS_PROCESS_MONITOR_OUTPUT_EVENT_PURPOSE (uint8)ECsProcessMonitorOutputEventPurpose::ECsProcessMonitorOutputEventPurpose_MAX
typedef ECsProcessMonitorOutputEventPurpose::Type TCsProcessMonitorOutputEventPurpose;

namespace ECsProcessMonitorOutputEventPurpose
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString FireOnce;
		extern const TCsString Loop;
	}

	namespace Ref
	{
		extern const Type FireOnce;
		extern const Type Loop;
		extern const Type ECsProcessMonitorOutputEventPurpose_MAX;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::FireOnce) { return Str::FireOnce.Value; }
		if (EType == Type::Loop) { return Str::Loop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::FireOnce) { return Ref::FireOnce; }
		if (String == Str::Loop) { return Ref::Loop; }
		return Ref::ECsProcessMonitorOutputEventPurpose_MAX;
	}
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsProcessMonitorOutputEvent_Completed, const FString&, Name);

USTRUCT(BlueprintType)
struct FCsProcessMonitorOutputEvent
{
	GENERATED_USTRUCT_BODY()

	DECLARE_MULTICAST_DELEGATE_OneParam(FCompleted, const FString&);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	TEnumAsByte<ECsProcessMonitorOutputEventPurpose::Type> Purpose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FCsStringParagraph Paragraph;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool Completed;

	FCompleted Event;
	UPROPERTY(BlueprintAssignable, Category = "Process")
	FBindableDynEvent_CsProcessMonitorOutputEvent_Completed ScriptEvent;

public:
	FCsProcessMonitorOutputEvent() {}

	FCsProcessMonitorOutputEvent(const FString &InName, const FCsStringParagraph &InParagraph, const TCsProcessMonitorOutputEventPurpose &InPurpse) 
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
namespace ECsProcessPriorityModifier
{
	enum Type
	{
		Idle							UMETA(DisplayName = "Idle"),
		Low								UMETA(DisplayName = "Low"),
		Normal							UMETA(DisplayName = "Normal"),
		High							UMETA(DisplayName = "High"),
		Higher							UMETA(DisplayName = "Higher"),
		ECsProcessPriorityModifier_MAX	UMETA(Hidden),
	};
}

#define ECS_PROCESS_PRIORITY_MODIFIER (uint8)ECsProcessPriorityModifier::ECsProcessPriorityModifier_MAX
typedef ECsProcessPriorityModifier::Type TCsProcessPriorityModifier;

namespace ECsProcessPriorityModifier
{
	typedef TCsPrimitiveType_MultiValue_FString_Enum_TwoParams TCsString;

	namespace Str
	{
		extern const TCsString Idle;
		extern const TCsString Low;
		extern const TCsString Normal;
		extern const TCsString High;
		extern const TCsString Higher;
	}

	namespace Ref
	{
		extern const Type Idle;
		extern const Type Low;
		extern const Type Normal;
		extern const Type High;
		extern const Type Higher;
		extern const Type ECsProcessPriorityModifier_MAX;
	}

	namespace Val
	{
		extern const int32 Idle;
		extern const int32 Low;
		extern const int32 Normal;
		extern const int32 High;
		extern const int32 Higher;
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::Idle) { return Str::Idle.Value; }
		if (EType == Type::Low) { return Str::Low.Value; }
		if (EType == Type::Normal) { return Str::Normal.Value; }
		if (EType == Type::High) { return Str::High.Value; }
		if (EType == Type::Higher) { return Str::Higher.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE const Type& ToType(const FString &String)
	{
		if (String == Str::Idle) { return Ref::Idle; }
		if (String == Str::Low) { return Ref::Low; }
		if (String == Str::Normal) { return Ref::Normal; }
		if (String == Str::High) { return Ref::High; }
		if (String == Str::Higher) { return Ref::Higher; }
		return Ref::ECsProcessPriorityModifier_MAX;
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

USTRUCT(BlueprintType)
struct FCsProcessPayload : public FCsPooledObjectPayload
{
	GENERATED_USTRUCT_BODY()

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
	TEnumAsByte<ECsProcessPriorityModifier::Type> PriorityModifier;
	/** Directory to start in when running the program, or NULL to use the current working directory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	bool bOptionalWorkingDirectory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Process")
	FString OptionalWorkingDirectory;

public:
	FCsProcessPayload() {}
	~FCsProcessPayload() {}

	virtual void Reset() override
	{
		FCsPooledObjectPayload::Reset();

		Name = ECsCached::Str::Empty;
		URL = ECsCached::Str::Empty;
		Params = ECsCached::Str::Empty;
		bLaunchDetached = false;
		bLaunchHidden = false;
		bLaunchReallyHidden = false;
		PriorityModifier = ECsProcessPriorityModifier::Normal;
		bOptionalWorkingDirectory = false;
		OptionalWorkingDirectory = ECsCached::Str::Empty;
	}
};

#pragma endregion Payload

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_UCsProcess_OnOutputRecieved, const FString&, Name);

USTRUCT(BlueprintType)
struct FCsProcessCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

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
	TEnumAsByte<ECsProcessPriorityModifier::Type> PriorityModifier;
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

	void Init(const uint16& InActiveIndex, FCsProcessPayload* Payload, const float &InTime, const float &InRealTime, const uint64 &InFrame)
	{
		//Init(InActiveIndex, Payload, InTime, InRealTime, InFrame, nullptr, nullptr);
	}

	virtual void Reset() override
	{
		FCsPooledObjectCache::Reset();

		Name = ECsCached::Str::Empty;
		URL = ECsCached::Str::Empty;
		Params = ECsCached::Str::Empty;
		bLaunchDetached = false;
		bLaunchHidden = false;
		bLaunchReallyHidden = false;
		PriorityModifier = ECsProcessPriorityModifier::Normal;
		bOptionalWorkingDirectory = false;
		OptionalWorkingDirectory = ECsCached::Str::Empty;
	}
};

UCLASS()
class CSCORE_API UCsProcess : public UCsPooledObject
{
	GENERATED_UCLASS_BODY()

public:

	FCsProcessCache Cache;

	void Init(const int32 &Index, const FECsProcess &Type);
	void Allocate(const int32 &Index, FCsProcessPayload* Payload);

// Interface
#pragma region
public:

	void OnCreatePool();
	void DeAllocate();

#pragma endregion Interface

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

	static void RemoveRoutine(UObject* InProcess, struct FCsRoutine* Routine, const uint8 &Type);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &Type);

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
	void RunCommand(const FString &Command);
	
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
	void AddMonitorOutputEvent(const FCsProcessMonitorOutputEvent &Event);
	void ProcessMonitorOuputEvents(const FString &Output);
	void OnOutputRecieved(const FString &Output);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputRecieved, const FString&);

	FOnOutputRecieved OnOutputRecieved_Event;

	UPROPERTY(BlueprintAssignable, Category = "Process")
	FBindableDynEvent_UCsProcess_OnOutputRecieved OnOutputRecieved_ScriptEvent;

#pragma endregion Read / Output
};