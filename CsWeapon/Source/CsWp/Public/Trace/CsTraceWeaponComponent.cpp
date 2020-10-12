#include "Trace/CsTraceWeaponComponent.h"
#include "CsWp.h"

// CVar
#include "Trace/CsCVars_TraceWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Library/CsLibrary_Camera.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/Weapon/CsManager_Weapon.h"
#include "Managers/Trace/CsManager_Trace.h"
#include "Managers/Sound/CsManager_Sound.h"
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
#include "Managers/Trace/CsManager_Trace.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Trace/Data/CsData_TraceWeapon.h"
#include "Trace/Data/Sound/CsData_TraceWeapon_SoundFire.h"
#include "Trace/Data/Visual/CsData_TraceWeapon_VisualFire.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pooled
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Projectile
#include "Payload/CsPayload_ProjectilePooledImpl.h"
#include "Payload/CsPayload_ProjectileImplSlice.h"
#include "Managers/Projectile/CsProjectilePooledImpl.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"
// Params
#include "Trace/Data/Sound/CsParams_TraceWeapon_SoundFire.h"

// Cached 
#pragma region

namespace NCsTraceWeaponComponent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, SetUpdateGroup);
			CS_DEFINE_CACHED_STRING(Group, "Group");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, SetWeaponType);
			CS_DEFINE_CACHED_STRING(Type, "Type");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, Init);
			CS_DEFINE_CACHED_STRING(UpdateGroup, "UpdateGroup");
			CS_DEFINE_CACHED_STRING(WeaponType, "WeaponType");
			CS_DEFINE_CACHED_STRING(IdleState, "IdleState");
			CS_DEFINE_CACHED_STRING(FireState, "FireState");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, Fire_Internal);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsTraceWeaponComponent, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsTraceWeaponComponent, Abort_Fire_Internal);
		}

		namespace TimeBetweenShotsImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsTraceWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}
		}

		namespace TraceImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FTraceImpl, GetLocation);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FTraceImpl, GetDirection);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FTraceImpl, Trace);
			}
		}

		namespace SoundImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FSoundImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FSoundImpl, SetPayload);
			}
		}

		namespace FXImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FFXImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent::FFXImpl, SetPayload);
			}
		}
	}
}

#pragma endregion Cached

UCsTraceWeaponComponent::UCsTraceWeaponComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsUpdate
	UpdateGroup(),
	WeaponType(),
	Data(nullptr),
	MyOwner(nullptr),
	MyOwnerAsActor(nullptr),
	// State
	CurrentState(),
	IdleState(),
	FireState(),
	// Ammo
	CurrentAmmo(0),
	// Fire
	bFire(false),
	bFire_Last(false),
	Fire_StartTime(0.0f),
	FireCount(0),
	FireRoutineHandle(),
	// Trace
	TraceImpl(nullptr),
	// Sound
	SoundImpl(nullptr)
{
}

// UObject Interface
#pragma region

void UCsTraceWeaponComponent::BeginDestroy()
{
	Super::BeginDestroy();
	
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle);

	if (TraceImpl)
	{
		CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(TraceImpl->TraceScopedHandle);

		delete TraceImpl;
		TraceImpl = nullptr;
	}

	if (SoundImpl)
	{
		delete SoundImpl;
		SoundImpl = nullptr;
	}

	if (FXImpl)
	{
		delete FXImpl;
		FXImpl = nullptr;
	}
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsTraceWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner		   = GetOwner();
	MyOwnerAsActor = GetOwner();

	TimeBetweenShotsImpl.Outer = this;

	TraceImpl = ConstructTraceImpl();
	TraceImpl->Outer = this;

	SoundImpl = ConstructSoundImpl();
	SoundImpl->Weapon = this;

	FXImpl = ConstructFXImpl();
	FXImpl->Weapon = this;

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	{
		using namespace NCsTraceWeaponComponent::NCached;

		// FireScopedHandle
		{
			const FString& ScopeName		   = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
		// StartLaunchScopedHandle
		{
			const FString& ScopeName		   = TraceImpl::Str::Trace;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
			//const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTrace;

			//TraceImpl->TraceScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

#pragma endregion UActorComponent Interface

// ICsUpdate
#pragma region

void UCsTraceWeaponComponent::Update(const FCsDeltaTime& DeltaTime)
{ 
	OnUpdate_HandleStates(DeltaTime);
}

#pragma endregion ICsUpdate

void UCsTraceWeaponComponent::SetUpdateGroup(const FECsUpdateGroup& Group)
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::SetUpdateGroup;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::Group, Group));

	UpdateGroup = Group;
}

void UCsTraceWeaponComponent::SetWeaponType(const FECsWeapon& Type)
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::SetWeaponType;

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::Type, Type));

	WeaponType = Type;
}

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

// ICsProjectileWeapon
#pragma region

void UCsTraceWeaponComponent::StartFire()
{
	bFire = true;

	Update(FCsDeltaTime::Zero);
}

void UCsTraceWeaponComponent::StopFire()
{
	bFire = false;

	Update(FCsDeltaTime::Zero);
}

#pragma endregion ICsProjectileWeapon

void UCsTraceWeaponComponent::Init()
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::Init;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::UpdateGroup, UpdateGroup));

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::WeaponType, WeaponType));

	// Get Data
	Data = UCsManager_Weapon::Get(GetWorld()->GetGameState())->GetData(WeaponType.GetFName());

	checkf(Data, TEXT("%s: Data is NULL. Failed to get Data of type: ICsData_Weapon for Weapon: %s"), *Context, WeaponType.ToChar());

	checkf(FCsLibrary_Data_Weapon::IsValidChecked(Context, Data), TEXT("%s: Data is NOT Valid."), *Context);

	// Set States
	UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

	IdleState = Settings->ProjectileWeaponImpl.IdleState;

	check(EMCsWeaponState::Get().IsValidEnumChecked(Context, Str::IdleState, IdleState));

	FireState = Settings->ProjectileWeaponImpl.FireState;

	check(EMCsWeaponState::Get().IsValidEnumChecked(Context, Str::FireState, FireState));

	CurrentState = IdleState;

	// Ammo
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<TraceDataType>(Context, Data);

	CurrentAmmo = PrjData->GetMaxAmmo();
}

// State
#pragma region

void UCsTraceWeaponComponent::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponTraceState))
	{
		UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: %s."), *Context, CurrentState.ToChar());
	}
#endif // #if !UE_BUILD_SHIPPING

	// Idle
	if (CurrentState == IdleState)
	{
		if (CanFire())
		{
			Fire();

			TimeBetweenShotsImpl.OnElapsedTime();

			CurrentState = FireState;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponTraceStateTransition))
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: Idle -> Fire."), *Context);
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	// Fire
	if (CurrentState == FireState)
	{
		// If can fire, start firing
		if (CanFire())
		{
			Fire();

			TimeBetweenShotsImpl.OnElapsedTime();
		}
		// If no firing is active, go to idle
		else
		if (FireCount == 0)
		{
			CurrentState = IdleState;

#if !UE_BUILD_SHIPPING
			if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponTraceStateTransition))
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: Fire -> Idle."), *Context);
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	bFire_Last = bFire;
}

#pragma endregion State

// Ammo
#pragma region

void UCsTraceWeaponComponent::ConsumeAmmo()
{
	int32 PreviousAmmo = CurrentAmmo;
	--CurrentAmmo;

	OnConsumeAmmo_Event.Broadcast(this, PreviousAmmo, CurrentAmmo);
}

#pragma endregion Ammo

// Fire
#pragma region

bool UCsTraceWeaponComponent::CanFire() const
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::CanFire;
	
	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* PrjData = FCsLibrary_Data_Weapon::GetInterfaceChecked<TraceDataType>(Context, Data);

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = (TimeSinceStart.Time - Fire_StartTime > PrjData->GetTimeBetweenShots());
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !PrjData->DoFireOnRelease() && (PrjData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && PrjData->DoFireOnRelease() && bFire_Last;
	// Check if has ammo to fire.
	const bool Pass_Ammo = PrjData->HasInfiniteAmmo() || CurrentAmmo > 0;

#if !UE_BUILD_SHIPPING
	if (FCsCVarLogMap::Get().IsShowing(NCsCVarLog::LogWeaponTraceCanFire))
	{
		using namespace NCsCached;

		UE_LOG(LogCsWp, Warning, TEXT("%s"), *Context);
		// Pass_Time
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Time (%s): %f - %f > %f"), ToChar(Pass_Time), TimeSinceStart.Time, Fire_StartTime, PrjData->GetTimeBetweenShots());
		// Pass_Fire
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Fire (%s): %s && %s && (%s || %s)"), ToChar(Pass_Fire), ToChar(bFire), ToChar(!PrjData->DoFireOnRelease()), ToChar(PrjData->IsFullAuto()), ToChar(!bFire_Last));
		// Pass_FireOnRelease
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_FireOnRelease (%s): %s && %s && %s"), ToChar(Pass_FireOnRelease), ToChar(!bFire), ToChar(PrjData->DoFireOnRelease()), ToChar(bFire_Last));
		// Pass_Ammo
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Ammo (%s): %s || %s"), ToChar(Pass_Ammo), ToChar(PrjData->HasInfiniteAmmo()), ToChar(CurrentAmmo > 0));

		// Result
		UE_LOG(LogCsWp, Warning, TEXT(" Result (%s): %s && (%s || %s) && %s"), ToChar(Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo), ToChar(Pass_Time), ToChar(Pass_Fire), ToChar(Pass_FireOnRelease), ToChar(Pass_Ammo));
	}
#endif // #if !UE_BUILD_SHIPPING

	return Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Ammo;
}

void UCsTraceWeaponComponent::Fire()
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::Fire;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetWorld()->GetGameInstance());

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &UCsTraceWeaponComponent::Fire_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::Fire_Internal);
	Payload->SetFName(Name::Fire_Internal);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &UCsTraceWeaponComponent::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	// Cache pointer to TraceDataType (NCsWeapon::NTrace::NData::IData)
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* TraceData = FCsLibrary_Data_Weapon::GetInterfaceChecked<TraceDataType>(Context, Data);

	Payload->SetValue_Flag(CS_FIRST, TraceData->HasInfiniteAmmo());
	Payload->SetValue_Int(CS_FIRST, TraceData->GetTracesPerShot());
	Payload->SetValue_Float(CS_FIRST, TraceData->GetTimeBetweenTracesPerShot());

	FireRoutineHandle = Scheduler->Start(Payload);
}

char UCsTraceWeaponComponent::Fire_Internal(FCsRoutine* R)
{
	using namespace NCsTraceWeaponComponent::NCached;

	const bool& bInfiniteAmmo = R->GetValue_Flag(CS_FIRST);

	static const int32 TRACES_PER_SHOT = 0;
	const int32& TracesPerShot = R->GetValue_Int(TRACES_PER_SHOT);

	const float& TimeBetweenTracesPerShot = R->GetValue_Float(CS_FIRST);

	static const int32 CURRENT_TRACE_PER_SHOT_INDEX = 1;
	int32& CurrentTracePerShotIndex = R->GetValue_Int(CURRENT_TRACE_PER_SHOT_INDEX);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			CS_SET_SCOPED_TIMER_HANDLE(FireScopedHandle);

			ElapsedTime.Reset();

			if (!bInfiniteAmmo)
				ConsumeAmmo();

			TraceImpl->Trace();
			SoundImpl->Play();
			FXImpl->Play();

			// Increment the shot index
			CurrentTracePerShotIndex = FMath::Min(CurrentTracePerShotIndex + 1, TracesPerShot);

			// Check if more projectiles should be fired, if so wait
			if (CurrentTracePerShotIndex < TracesPerShot)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= TimeBetweenTracesPerShot);
			}

			CS_UPDATE_SCOPED_TIMER_HANDLE(FireScopedHandle);
		}
	} while (CurrentTracePerShotIndex < TracesPerShot);

	CS_COROUTINE_END(R);
}

void UCsTraceWeaponComponent::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void UCsTraceWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsTraceWeaponComponent::NCached::TimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(Outer->GetWorld()->GetGameInstance());

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	Payload->CoroutineImpl.BindRaw(this, &UCsTraceWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(Outer->GetWorld()->GetGameInstance())->GetTime(Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::OnElapsedTime_Internal);
	Payload->SetFName(Name::OnElapsedTime_Internal);

	// Get total elapsed time (= TimeBetweenShots)
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* TraceData = FCsLibrary_Data_Weapon::GetInterfaceChecked<TraceDataType>(Context, Outer->GetData());

	Payload->SetValue_Float(CS_FIRST, TraceData->GetTimeBetweenShots());

	Scheduler->Start(Payload);
}

char UCsTraceWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
{
	FCsDeltaTime& ElapsedTime			   = R->GetValue_DeltaTime(CS_FIRST);
	const FCsDeltaTime PreviousElapsedTime = ElapsedTime;

	ElapsedTime += R->DeltaTime;

	const float& TimeBetweenShots = R->GetValue_Float(CS_FIRST);

	// Broadcast ElapsedTime events

		// Time
	const float& PreviousTime = PreviousElapsedTime.Time;
	const float NewTime		  = FMath::Max(ElapsedTime.Time, TimeBetweenShots);

	OnElapsedTime_Event.Broadcast(Outer, PreviousTime, NewTime);
	// Percent
	const float PreviousPercent = PreviousElapsedTime.Time / TimeBetweenShots;
	const float NewPercent		= FMath::Min(ElapsedTime.Time / TimeBetweenShots, 1.0f);

	OnElapsedTimeAsPercent_Event.Broadcast(Outer, PreviousPercent, NewPercent);

	CS_COROUTINE_BEGIN(R);

	ElapsedTime.Reset();

	CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= TimeBetweenShots);

	OnComplete_Event.Broadcast(Outer);

	CS_COROUTINE_END(R);
}

	// Trace
#pragma region

FVector UCsTraceWeaponComponent::FTraceImpl::GetLocation()
{
	using namespace NCsTraceWeaponComponent::NCached::TraceImpl;

	const FString& ScopeName		   = Str::GetLocation;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
	//const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerGetLocation;

	//CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetLocation;

	// Get Data Slice
	typedef NCsWeapon::NTrace::NData::IData WeaponDataType;

	WeaponDataType* WeaponData = FCsLibrary_Data_Weapon::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());
	
	// Get Trace Params
	/*
	using namespace NCsWeapon::NTrace::NParams::NLaunch;

	const ILaunch* LaunchParams = WeaponData->GetLaunchParams();

	checkf(LaunchParams, TEXT("%s: Failed to get LaunchParams from Data."), *Context);

	const ELocation& LocationType = LaunchParams->GetLocationType();

	// Owner
	if (LocationType == ELocation::Owner)
	{
		UObject* TheOwner = Outer->GetMyOwner();

		checkf(TheOwner, TEXT("%s: No Owner found for %s."), *Context, *(Outer->PrintNameAndClass()));

		// Actor
		if (AActor* Actor = Cast<AActor>(TheOwner))
			return Actor->GetActorLocation();
		// Component
		if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
			return Component->GetComponentLocation();

		checkf(0, TEXT("%s: Failed to get Location from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
	}
	// Bone
	if (LocationType == ELocation::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (LocationType == ELocation::Component)
	{
		checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));

		return LaunchComponentTransform->GetComponentLocation();
	}
	*/
	return FVector::ZeroVector;
}

FVector UCsTraceWeaponComponent::FTraceImpl::GetDirection()
{
	using namespace NCsTraceWeaponComponent::NCached::TraceImpl;

	const FString& ScopeName		   = Str::GetDirection;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
	//const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerGetDirection;

	//CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetDirection;

	// Get Data Slice
	typedef NCsWeapon::NTrace::NData::IData WeaponDataType;

	WeaponDataType* WeaponData = FCsLibrary_Data_Weapon::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());
	
	// Get Trace Params
	/*
	using namespace NCsWeapon::NTrace::NParams::NLaunch;

	const ILaunch* LaunchParams = WeaponData->GetLaunchParams();

	checkf(LaunchParams, TEXT("%s: Failed to get LaunchParams from Data."), *Context);

	const ELocation& LocationType   = LaunchParams->GetLocationType();
	const EDirection& DirectionType = LaunchParams->GetDirectionType();
	const int32& DirectionRules		= LaunchParams->GetDirectionRules();

	checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in Launchparams for Data."), *Context);

	// Owner
	if (DirectionType == EDirection::Owner)
	{
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			// AActor
			if (AActor* Actor = Cast<AActor>(TheOwner))
				return NCsRotationRules::GetRotation(Actor, DirectionRules).Vector();
			// USceneComponent
			if (USceneComponent* Component = Cast<USceneComponent>(TheOwner))
				return NCsRotationRules::GetRotation(Component, DirectionRules).Vector();
			checkf(0, TEXT("%s: Failed to get Direction from %s."), *Context, *(Outer->PrintNameClassAndOwner()));
		}
	}
	// Bone
	if (DirectionType == EDirection::Bone)
	{
		checkf(0, TEXT("NOT IMPLEMENTED"));
	}
	// Component
	if (DirectionType == EDirection::Component)
	{
		checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));
		
		const FRotator Rotation = NCsRotationRules::GetRotation(LaunchComponentTransform, DirectionRules);

		return Rotation.Vector();
	}
	// Camera
	if (DirectionType == EDirection::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			return FCsLibrary_Camera::GetDirectionChecked(Context, TheOwner);
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
	}
	// ITrace | Get Launch Trace Params
	if (DirectionType == EDirection::Trace)
	{
		const ITrace* LaunchTraceParams = FLibrary::GetInterfaceChecked<ITrace>(Context, LaunchParams);
		
		// Start
		const ETraceStart& TraceStart = LaunchTraceParams->GetTraceStartType();

		FVector Start = FVector::ZeroVector;

		// LaunchLocation
		if (TraceStart == ETraceStart::LaunchLocation)
		{
			Start = GetLaunchLocation();
		}
		// Owner
		else
		if (TraceStart == ETraceStart::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceStart == ETraceStart::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceStart == ETraceStart::Component)
		{
			checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));

			Start = LaunchComponentTransform->GetComponentLocation();
		}
		// Camera
		else
		if (TraceStart == ETraceStart::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Outer->GetMyOwner())
			{
				Start = FCsLibrary_Camera::GetLocationChecked(Context, TheOwner);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
			}
		}

		// Direction
		const ETraceDirection& TraceDirection  = LaunchTraceParams->GetTraceDirectionType();

		FVector Dir = FVector::ZeroVector;

		// Owner
		if (TraceDirection == ETraceDirection::Owner)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Bone
		else
		if (TraceDirection == ETraceDirection::Bone)
		{
			checkf(0, TEXT("NOT IMPLEMENTED"));
		}
		// Component
		else
		if (TraceDirection == ETraceDirection::Component)
		{
			checkf(LaunchComponentTransform, TEXT("%s: LaunchComponentTransform is NULL."));

			const FRotator Rotation = NCsRotationRules::GetRotation(LaunchComponentTransform->GetComponentRotation(), DirectionRules);

			Dir = Rotation.Vector();
		}
		else
		// Camera
		if (TraceDirection == ETraceDirection::Camera)
		{
			// Try to get camera through the owner
			if (UObject* TheOwner = Outer->GetMyOwner())
			{
				Dir = FCsLibrary_Camera::GetDirectionChecked(Context, TheOwner, DirectionRules);
			}
			// TODO: For now assert
			else
			{
				checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
			}
		}

		const float& Distance = LaunchTraceParams->GetTraceDistance();

		const FVector End = Start + Distance * Dir;

		// Perform Trace
		UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(Outer->GetWorld()->GetGameState());

		FCsTraceRequest* Request = Manager_Trace->AllocateRequest();
		Request->Start = Start;
		Request->End = End;

		// Get collision information related to the projectile to be used in the trace.
		ICsData_Projectile* PrjData					  = UCsManager_Projectile::Get(Outer->GetWorld()->GetGameState())->GetDataChecked(Context, Outer->GetProjectileType());
		ICsData_ProjectileCollision* PrjCollisionData = FCsLibrary_Data_Projectile::GetInterfaceChecked<ICsData_ProjectileCollision>(Context, PrjData);

		const FCsCollisionPreset& CollisionPreset		 = PrjCollisionData->GetCollisionPreset();
		const TEnumAsByte<ECollisionChannel>& ObjectType = CollisionPreset.ObjectType;

		Request->ObjectParams.AddObjectTypesToQuery(ObjectType);

		Request->Type = LaunchTraceParams->GetTraceType();

		if (Request->Type == ECsTraceType::Sweep)
		{
			//Request->Shape = 
		}
		
		FCsTraceResponse* Response = Manager_Trace->Trace(Request);

		FVector LookAtLocation = FVector::ZeroVector;

		if (Response &&
			Response->bResult)
		{
			LookAtLocation = Start + Response->OutHits[CS_FIRST].Distance * Dir;
		}
		else
		{
			LookAtLocation = Start + Distance * Dir;
		}

		const FVector LaunchLocation  = GetLaunchLocation();
		const FVector LaunchDirection = (LookAtLocation - LaunchLocation).GetSafeNormal();

		// Check the direction is in FRONT of the Start. The trace could produce a result BEHIND the start

		if (Start == LaunchDirection ||
			FVector::DotProduct(Dir, LaunchDirection) > 0)
		{
			return LaunchDirection;
		}
		return Dir;
	}
	*/
	return FVector::ZeroVector;
}

void UCsTraceWeaponComponent::FTraceImpl::Trace()
{
	using namespace NCsTraceWeaponComponent::NCached::TraceImpl;

	const FString& Context = Str::Trace;

	const FVector Start = GetLocation();
	const FVector Dir = GetDirection();
	const FVector End = Start + 10000.0f * Dir;

	UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(Outer->GetWorld()->GetGameState());

	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();
	Request->Start = Start;
	Request->End = End;

	FCsTraceResponse* Response = Manager_Trace->Trace(Request);
}

UCsTraceWeaponComponent::FTraceImpl* UCsTraceWeaponComponent::ConstructTraceImpl()
{
	return new UCsTraceWeaponComponent::FTraceImpl();
}

#pragma endregion Projectile

	// Sound
#pragma region

void UCsTraceWeaponComponent::FSoundImpl::Play()
{
	using namespace NCsTraceWeaponComponent::NCached::SoundImpl;

	const FString& Context = Str::Play;

	// NCsWeapon::NTrace::NData::NSound::NFire::IFire | ICsData_ProjectileWeapon_SoundFire
	typedef NCsWeapon::NTrace::NData::NSound::NFire::IFire SoundDataType;

	if (SoundDataType* SoundData = FCsLibrary_Data_Weapon::GetSafeInterfaceChecked<SoundDataType>(Context, Weapon->GetData()))
	{
		typedef NCsWeapon::NTrace::NData::NSound::NFire::NParams::IParams ParamsType;

		ParamsType* Params	  = SoundData->GetFireSoundParams();
		const FCsSound& Sound = Params->GetSound();

		USoundBase* SoundAsset = Sound.GetChecked(Context);

		// Get Manager
		UCsManager_Sound* Manager_Sound = UCsManager_Sound::Get(Weapon->GetWorld()->GetGameState());
		// Allocate payload
		typedef NCsSound::NPayload::IPayload PayloadType;

		PayloadType* Payload = Manager_Sound->AllocatePayload(Sound.Type);
		// Set appropriate values on payload
		SetPayload(Payload, Sound);

		Manager_Sound->Spawn(Sound.Type, Payload);
	}
}

#define SoundPayloadType NCsSound::NPayload::IPayload
void UCsTraceWeaponComponent::FSoundImpl::SetPayload(SoundPayloadType* Payload, const FCsSound& Sound)
{
#undef SoundPayloadType

	using namespace NCsTraceWeaponComponent::NCached::SoundImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsSound::NPayload::FImpl PayloadImplType;

	PayloadImplType* PayloadImpl = FCsLibrary_Payload_Sound::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Weapon;
	PayloadImpl->Owner						= Weapon->GetMyOwner();
	PayloadImpl->Sound						= Sound.GetChecked(Context);
	PayloadImpl->SoundAttenuation			= Sound.GetAttenuation();
	PayloadImpl->DeallocateMethod			= Sound.GetDeallocateMethod();
	PayloadImpl->LifeTime					= Sound.LifeTime;
	PayloadImpl->AttachmentTransformRules	= Sound.AttachmentTransformRules;
	PayloadImpl->Bone						= Sound.Bone;
	PayloadImpl->TransformRules				= Sound.TransformRules;
	PayloadImpl->Transform					= Sound.Transform;
}

UCsTraceWeaponComponent::FSoundImpl* UCsTraceWeaponComponent::ConstructSoundImpl()
{
	return new UCsTraceWeaponComponent::FSoundImpl();
}

#pragma endregion Sound

	// FX
#pragma region

void UCsTraceWeaponComponent::FFXImpl::Play()
{
	using namespace NCsTraceWeaponComponent::NCached::FXImpl;

	const FString& Context = Str::Play;

	// NCsWeapon::NTrace::NData::NVisual::NFire::IFire | ICsData_ProjectileWeapon_VisualFire
	typedef NCsWeapon::NTrace::NData::NVisual::NFire::IFire FXDataType;

	if (FXDataType* FXData = FCsLibrary_Data_Weapon::GetSafeInterfaceChecked<FXDataType>(Context, Weapon->GetData()))
	{
		typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams ParamsType;

		const ParamsType* Params = FXData->GetFireFXParams();
		const FCsFX& FX			 = Params->GetFX();

		UNiagaraSystem* FXAsset = FX.GetChecked(Context);

		// Get Manager
		UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(Weapon->GetWorld()->GetGameState());
		// Allocate payload
		typedef NCsFX::NPayload::IPayload PayloadType;

		PayloadType* Payload = Manager_FX->AllocatePayload(FX.Type);
		// Set appropriate values on payload
		SetPayload(Payload, FX);
		SetPayload(Payload, FXData);

		Manager_FX->Spawn(FX.Type, Payload);
	}
}

#define FXPayloadType NCsFX::NPayload::IPayload
void UCsTraceWeaponComponent::FFXImpl::SetPayload(FXPayloadType* Payload, const FCsFX& FX)
{
#undef FXPayloadType

	using namespace NCsTraceWeaponComponent::NCached::FXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsFX::NPayload::FImpl PayloadImplType;

	PayloadImplType* PayloadImpl = FCsLibrary_Payload_FX::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	PayloadImpl->Instigator					= Weapon;
	PayloadImpl->Owner						= Weapon->GetMyOwner();
	PayloadImpl->FXSystem					= FX.GetChecked(Context);
	PayloadImpl->DeallocateMethod			= FX.DeallocateMethod;
	PayloadImpl->LifeTime					= FX.LifeTime;
	PayloadImpl->AttachmentTransformRules	= FX.AttachmentTransformRules;
	PayloadImpl->Bone						= FX.Bone;
	PayloadImpl->TransformRules				= FX.TransformRules;
	PayloadImpl->Transform					= FX.Transform;

	typedef NCsWeapon::NTrace::NData::NVisual::NFire::IFire FXDataType;

	FXDataType* FXData = FCsLibrary_Data_Weapon::GetInterfaceChecked<FXDataType>(Context, Weapon->GetData());

	typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams ParamsType;

	const ParamsType* Params = FXData->GetFireFXParams();

	typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::EAttach AttachType;

	const AttachType& Type = Params->GetAttachType();

	// None
	if (Type == AttachType::None)
	{
		// Do Nothing
	}
	// Owner
	else
	if (Type == AttachType::Owner)
	{
		PayloadImpl->Parent = Weapon->GetMyOwner();
	}
	// Component
	else
	if (Type == AttachType::Component)
	{
		PayloadImpl->Parent = Component;
	}
	// Custom
	else
	{
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."));
	}
}

#define FXPayloadType NCsFX::NPayload::IPayload
#define FXDataType NCsWeapon::NTrace::NData::NVisual::NFire::IFire
void UCsTraceWeaponComponent::FFXImpl::SetPayload(FXPayloadType* Payload, FXDataType* FXData)
{
#undef FXPayloadType
#undef FXDataType

	using namespace NCsTraceWeaponComponent::NCached::FXImpl;

	const FString& Context = Str::SetPayload;

	typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::IParams ParamsType;

	const ParamsType* Params = FXData->GetFireFXParams();

	typedef NCsWeapon::NTrace::NData::NVisual::NFire::NParams::EAttach AttachType;

	const AttachType& Type = Params->GetAttachType();

	typedef NCsFX::NPayload::FImpl PayloadImplType;

	PayloadImplType* PayloadImpl = FCsLibrary_Payload_FX::PureStaticCastChecked<PayloadImplType>(Context, Payload);

	// None
	if (Type == AttachType::None)
	{
		// Do Nothing
	}
	// Owner
	else
	if (Type == AttachType::Owner)
	{
		PayloadImpl->Parent = Weapon->GetMyOwner();
	}
	// Component
	else
	if (Type == AttachType::Component)
	{
		PayloadImpl->Parent = Component;
	}
	// Custom
	else
	{
		checkf(0, TEXT("%s: AttachType::Custom is NOT implemented."));
	}
}

UCsTraceWeaponComponent::FFXImpl* UCsTraceWeaponComponent::ConstructFXImpl()
{
	return new UCsTraceWeaponComponent::FFXImpl();
}

#pragma endregion FX

#pragma endregion Fire

// Print
#pragma region

FString UCsTraceWeaponComponent::PrintNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(GetName()), *(GetClass()->GetName()));
}

FString UCsTraceWeaponComponent::PrintNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(GetName()), *(GetClass()->GetName()), *(MyOwner->GetName()));
}

#pragma endregion Print