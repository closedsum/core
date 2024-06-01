// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Coroutine/CsRoutine.h"
#include "CsCoroutine.h"

// CVar
#include "Coroutine/CsCVars_Coroutine.h"
// Managers
#include "Managers/ScopedTimer/CsManager_ScopedTimer.h"

FCsRoutine::FCsRoutine() :
	RegisterMap()
{
	Parent = nullptr;

	Children.Reset(Children.Max());

	typedef NCsCoroutine::EMMessage MessageMapType;

	for (const MessageType& Type : MessageMapType::Get())
	{
		Messages.AddDefaulted();
		Messages_Recieved.AddDefaulted();
	}

	Reset();
}

FCsRoutine::~FCsRoutine()
{
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(RoutineScopedTimerHandle);
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(CoroutineScopedTimerHandle);
}

// Time
#pragma region

void FCsRoutine::SetGroup(const FECsUpdateGroup& InGroup)
{
	Group = InGroup;
#if !UE_BUILD_SHIPPING
	ScopeName = FString::Printf(TEXT("Routine_%d_%s"), Index, *(Group.GetName()));
#endif // #if !UE_BUILD_SHIPPING
}

#pragma endregion Time

// Index
#pragma region

void FCsRoutine::SetIndex(const int32& InIndex)
{
	Index		 = InIndex;
	Handle.Index = InIndex;
}

#pragma endregion Index

void FCsRoutine::Init(PayloadType* Payload)
{
	State = StateType::Init;

	CoroutineImpl = Payload->CoroutineImpl;
	StartTime	  = Payload->StartTime;
	Owner		  = Payload->Owner;
	
	for (const FName& Message : Payload->AbortMessages)
	{
		Messages[(uint8)MessageType::Abort].Add(Message);
	}

	for (const AbortConditionImplType& AbortImpl : Payload->AbortImpls)
	{
		AbortImpls.AddDefaulted();
		AbortConditionImplType& Last = AbortImpls.Last();
		Last = AbortImpl;
	}

	for (const OnEndType& OnEnd : Payload->OnEnds)
	{
		OnEnds.AddDefaulted();
		OnEndType& Last = OnEnds.Last();
		Last = OnEnd;
	}

	Name_Internal	= Payload->GetFName();
	Name			= const_cast<FString*>(Payload->GetName());

	// Copy Register values over
	typedef NCsCoroutine::NRegister::FInfo InfoType;

	for (const InfoType& Info : Payload->RegisterMap.Infos)
	{
		const ValueType& Type = Info.Type;
		const int32&		I = Info.Index;

		void* From = RegisterMap.Values[(uint8)Type][I];
		void* To   = Payload->RegisterMap.Values[(uint8)Type][I];

		NCsCoroutine::NRegister::NValueType::SetValue(Type, From, To);

		RegisterMap.SetUsedValue(Type, I);
	}
	Handle.New();

	CS_GET_SCOPED_TIMER_HANDLE(RoutineScopedTimerHandle, &ScopeName, NCsScopedGroup::Coroutine, NCsCVarLog::LogRoutineScopedTimer);
	CS_GET_SCOPED_TIMER_HANDLE(CoroutineScopedTimerHandle, Name, NCsScopedGroup::Coroutine, NCsCVarLog::LogCoroutineScopedTimer);
}

// Update
#pragma region

void FCsRoutine::Update(const FCsDeltaTime& InDeltaTime)
{
	CS_SCOPED_TIMER(RoutineScopedTimerHandle);

	bUpdateComplete = false;

	// Check for Abort Messages
	const int32 AbortIndex = (int32)MessageType::Abort;

	TSet<FName>& AbortMessages		    = Messages[AbortIndex];
	TSet<FName>& AbortMessages_Recieved = Messages_Recieved[AbortIndex];

	if (AbortMessages.Num() > CS_EMPTY)
	{
		bool MatchFound = false;

		for (const FName& Recieved : AbortMessages_Recieved)
		{
			if (AbortMessages.Find(Recieved))
			{
				AbortMessages.Reset();
				End(EndReasonType::AbortMessage);

				MatchFound = true;
			}

			if (MatchFound)
				break;
		}
	}
	AbortMessages_Recieved.Reset();

	// If the Coroutine has been ended by a Abort Message, EXIT
	if (State == StateType::End &&
		EndReason == EndReasonType::AbortMessage)
	{
		bUpdateComplete = true;
		return;
	}
	// If the Owner of the Coroutine is a UObject, check if that object
	// is still valid
	if (Owner.IsObject())
	{
		UObject* O = Owner.GetSafeObject();

		if (!IsValid(O))
		{
			End(EndReasonType::OwnerIsInvalid);

			bUpdateComplete = true;
			return;
		}
	}
	// Check if Coroutine should be aborted
	for (AbortConditionImplType& AbortImpl : AbortImpls)
	{
		if (AbortImpl.Execute(this))
		{
			for (OnAbortType& OnAbort : OnAborts)
			{
				OnAbort.Execute(this);
			}
			End(EndReasonType::AbortCondition);

			bUpdateComplete = true;
			return;
		}
	}
	// Check if the Coroutine has been ended
	if (State == StateType::End)
	{
		if (EndReason == EndReasonType::EEndReason_MAX)
			End(EndReasonType::EndOfExecution);

		bUpdateComplete = true;
		return;
	}

	DeltaTime    = InDeltaTime;
	ElapsedTime += DeltaTime;

	++TickCount;

	// Run the Coroutine
	{
		CS_SCOPED_TIMER(CoroutineScopedTimerHandle);

		bExecuteComplete = false;
		
		CoroutineImpl.Execute(this);

		bExecuteComplete = true;
	}
	// Check if the Coroutine has ended naturally after
	// the function has completed execution / reached end of scope.
	if (State == StateType::End)
	{
		if (EndReason == EndReasonType::EEndReason_MAX &&
			TickCount > 0)
		{
			End(EndReasonType::EndOfExecution);
		}
	};

	bUpdateComplete = true;
}

#pragma endregion Update

// End
#pragma region

void FCsRoutine::End(const EndReasonType& InEndReason)
{
	EndChildren();

	State	  = StateType::End;
	EndReason = InEndReason;

	for (OnEndType& OnEnd : OnEnds)
	{
		OnEnd.Execute(this);
	}

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogRoutineEnd))
	{
		UE_LOG(LogCsCoroutine, Warning, TEXT("Routine (%s %d): %s: End Reason: %s."), Group.ToChar(), Index, ToChar(), EndReasonMapType::Get().ToChar(EndReason));
	}
#endif // #if !UE_BUILD_SHIPPING

	CS_CLEAR_SCOPED_TIMER_HANDLE(RoutineScopedTimerHandle);
	CS_CLEAR_SCOPED_TIMER_HANDLE(CoroutineScopedTimerHandle);
}

#pragma endregion End

void FCsRoutine::Reset()
{
	if (Parent)
	{
		Parent->Children.Remove(this);
	}

	Parent = nullptr;

	EndChildren();

	CoroutineImpl.Unbind();

	// Time
	StartTime.Reset();
	ElapsedTime.Reset();
	DeltaTime.Reset();
	TickCount = 0;
	Delay = 0.0f;

	RoutineScopedTimerHandle.Reset();
	CoroutineScopedTimerHandle.Reset();

	Handle.Reset();
	AbortImpls.Reset(AbortImpls.Max());
	OnAborts.Reset(OnAborts.Max());

	State = StateType::Free;

	Name = nullptr;
	Name_Internal = NAME_None;

	bUpdateComplete = false;
	bExecuteComplete = false;

	EndReason = EndReasonType::EEndReason_MAX;
	OnEnds.Reset(OnEnds.Max());

	Owner.Reset();
	
	RegisterMap.Reset();

	// Messages
	typedef NCsCoroutine::EMMessage MessageMapType;

	for (const MessageType& Type : MessageMapType::Get())
	{
		const int32 I = (int32)Type;

		Messages[I].Reset();
		Messages_Recieved[I].Reset();
	}

	pt.lc = 0;
}

// Children
#pragma region

void FCsRoutine::AddChild(FCsRoutine* Child)
{
	Child->Parent = this;
	Children.Add(Child);
}

void FCsRoutine::EndChildren()
{
	for (FCsRoutine* Child : Children)
	{
		Child->End(EndReasonType::Parent);
	}
	Children.Reset(Children.Max());
}

void FCsRoutine::EndChild(FCsRoutine* Child)
{
	const int32 Count = Children.Num();

	for (int32 I = Count - 1; I >= 0; --I)
	{
		if (Child == Children[I])
		{
			Child->End(EndReasonType::Parent);
			Children.RemoveAt(I, 1, false);
			break;
		}
	}
}

#pragma endregion Children