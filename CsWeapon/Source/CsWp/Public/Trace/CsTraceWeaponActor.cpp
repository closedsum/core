#include "Trace/CsTraceWeaponActor.h"
#include "CsWp.h"

// CVar
#include "Trace/CsCVars_TraceWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Skin/Data/Visual/CsLibrary_Data_Skin_Visual.h"
#include "Library/CsLibrary_Camera.h"
#include "Material/CsLibrary_Material.h"
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Weapon/CsManager_Weapon.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/Visual/CsData_Weapon_VisualSkin.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Trace/Data/CsData_TraceWeapon.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pooled
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Params
#include "Trace/Data/Params/CsParams_TraceWeapon_Trace.h"
#include "Trace/Data/Params/CsLibrary_Params_TraceWeapon_Trace.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Weapon
#include "Impl/CsTraceWeapon_Impl_Trace.h"
#include "Impl/CsTraceWeapon_Impl_FX.h"
#include "Impl/CsTraceWeapon_Impl_Sound.h"

// Cached 
#pragma region

namespace NCsTraceWeaponActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, SetUpdateGroup);
			CS_DEFINE_CACHED_STRING(Group, "Group");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, SetWeaponType);
			CS_DEFINE_CACHED_STRING(Type, "Type");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, Init);
			CS_DEFINE_CACHED_STRING(UpdateGroup, "UpdateGroup");
			CS_DEFINE_CACHED_STRING(WeaponType, "WeaponType");
			CS_DEFINE_CACHED_STRING(IdleState, "IdleState");
			CS_DEFINE_CACHED_STRING(FireState, "FireState");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, LineTrace);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor, Trace);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsTraceWeaponActor, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsTraceWeaponActor, Abort_Fire_Internal);
		}

		namespace NTimeBetweenShotsImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FTimeBetweenShotsImpl, OnElapsedTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsTraceWeaponActor::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}
		}
	}
}

#pragma endregion Cached

ACsTraceWeaponActor::ACsTraceWeaponActor(const FObjectInitializer& ObjectInitializer)
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

void ACsTraceWeaponActor::BeginDestroy()
{
	Super::BeginDestroy();
	
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle);

	if (TraceImpl)
	{
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

void ACsTraceWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	MyOwner		   = GetOwner();
	MyOwnerAsActor = GetOwner();

	TimeBetweenShotsImpl.Outer = this;

	TraceImpl = ConstructTraceImpl();
	TraceImpl->SetOuter(this);

	SoundImpl = ConstructSoundImpl();
	SoundImpl->SetOuter(this);

	FXImpl = ConstructFXImpl();
	FXImpl->SetOuter(this);

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	{
		using namespace NCsTraceWeaponActor::NCached;

		// FireScopedHandle
		{
			const FString& ScopeName		   = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

#pragma endregion UActorComponent Interface

// ICsUpdate
#pragma region

void ACsTraceWeaponActor::Update(const FCsDeltaTime& DeltaTime)
{ 
	OnUpdate_HandleStates(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsTraceWeaponActor::SetUpdateGroup(const FECsUpdateGroup& Group)
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::SetUpdateGroup;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::Group, Group));

	UpdateGroup = Group;
}

void ACsTraceWeaponActor::SetWeaponType(const FECsWeapon& Type)
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::SetWeaponType;

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::Type, Type));

	WeaponType = Type;
}

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

// ICsProjectileWeapon
#pragma region

void ACsTraceWeaponActor::StartFire()
{
	bFire = true;

	Update(FCsDeltaTime::Zero);
}

void ACsTraceWeaponActor::StopFire()
{
	bFire = false;

	Update(FCsDeltaTime::Zero);
}

#pragma endregion ICsProjectileWeapon

void ACsTraceWeaponActor::Init()
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::Init;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::UpdateGroup, UpdateGroup));

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::WeaponType, WeaponType));

	// Get Data
	Data = UCsManager_Weapon::Get(GetWorld()->GetGameState())->GetDataChecked(Context, WeaponType.GetFName());

	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	check(WeaponDataLibrary::IsValidChecked(Context, Data));

	// Set States
	UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

	IdleState = Settings->ProjectileWeaponImpl.IdleState;

	check(EMCsWeaponState::Get().IsValidEnumChecked(Context, Str::IdleState, IdleState));

	FireState = Settings->ProjectileWeaponImpl.FireState;

	check(EMCsWeaponState::Get().IsValidEnumChecked(Context, Str::FireState, FireState));

	CurrentState = IdleState;

	// Ammo
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* PrjData = WeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

	CurrentAmmo = PrjData->GetMaxAmmo();

	// Set Skin
	{
		typedef NCsWeapon::NData::NVisual::NSkin::ISkin WeaponSkinType;

		if (WeaponSkinType* WeaponSkin = WeaponDataLibrary::GetSafeInterfaceChecked<WeaponSkinType>(Context, Data))
		{
			typedef NCsSkin::NData::NVisual::IVisual SkinType;

			SkinType* Skin = WeaponSkin->GetSkin();

			checkf(Skin, TEXT("%s: Failed to get Skin of type: %s from Data."), *Context, *(SkinType::Name.ToString()));

			typedef NCsSkin::NData::NVisual::FLibrary SkinLibrary;

			// Static Mesh
			SkinLibrary::SetSafeStaticMeshAndMaterials(Context, Skin, GetStaticMeshComponent());
			// Skeletal Mesh
			SkinLibrary::SetSafeSkeletalMeshAndMaterials(Context, Skin, GetSkeletalMeshComponent());
		}
	}

	TraceImpl->SetOwner(MyOwner);
	TraceImpl->SetFXImpl(FXImpl);
	TraceImpl->SetSoundImpl(SoundImpl);

	check(TraceImpl->IsValidChecked(Context));

	FXImpl->SetOwner(MyOwner);
	SoundImpl->SetOwner(MyOwner);
}

// State
#pragma region

void ACsTraceWeaponActor::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponTraceState))
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
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponTraceStateTransition))
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
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponTraceStateTransition))
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

void ACsTraceWeaponActor::ConsumeAmmo()
{
	int32 PreviousAmmo = CurrentAmmo;
	--CurrentAmmo;

	OnConsumeAmmo_Event.Broadcast(this, PreviousAmmo, CurrentAmmo);
}

#pragma endregion Ammo

// Fire
#pragma region

bool ACsTraceWeaponActor::CanFire() const
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::CanFire;
	
	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	typedef NCsWeapon::NTrace::NData::IData TraceDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	TraceDataType* PrjData = WeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = (TimeSinceStart.Time - Fire_StartTime > PrjData->GetTimeBetweenShots());
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !PrjData->DoFireOnRelease() && (PrjData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && PrjData->DoFireOnRelease() && bFire_Last;
	// Check if has ammo to fire.
	const bool Pass_Ammo = PrjData->HasInfiniteAmmo() || CurrentAmmo > 0;

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponTraceCanFire))
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

void ACsTraceWeaponActor::Fire()
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::Fire;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, this);

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Fire_Internal

	Payload->CoroutineImpl.BindUObject(this, &ACsTraceWeaponActor::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, this, UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsTraceWeaponActor::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	#undef COROUTINE

	// Cache pointer to TraceDataType (NCsWeapon::NTrace::NData::IData)
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	TraceDataType* TraceData = WeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

	//check(WeaponDataLibrary::IsValidChecked(Context, Data));

	Payload->SetValue_Flag(CS_FIRST, TraceData->HasInfiniteAmmo());
	Payload->SetValue_Int(CS_FIRST, TraceData->GetTracesPerShot());
	Payload->SetValue_Float(CS_FIRST, TraceData->GetTimeBetweenTracesPerShot());

	FireRoutineHandle = Scheduler->Start(Payload);
}

char ACsTraceWeaponActor::Fire_Internal(FCsRoutine* R)
{
	using namespace NCsTraceWeaponActor::NCached;

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

			TraceImpl->Trace(Data);
			SoundImpl->TryFire(Data);
			FXImpl->TryFire(Data);

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

void ACsTraceWeaponActor::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void ACsTraceWeaponActor::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsTraceWeaponActor::NCached::NTimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, Outer);

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	#define COROUTINE OnElapsedTime_Internal

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	Payload->CoroutineImpl.BindRaw(this, &ACsTraceWeaponActor::FTimeBetweenShotsImpl::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, Outer, Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	// Get total elapsed time (= TimeBetweenShots)
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	TraceDataType* TraceData = WeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Outer->GetData());

	Payload->SetValue_Float(CS_FIRST, TraceData->GetTimeBetweenShots());

	Scheduler->Start(Payload);
}

char ACsTraceWeaponActor::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
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

#define TraceImplType NCsWeapon::NTrace::NImpl::NTrace::FImpl
TraceImplType* ACsTraceWeaponActor::ConstructTraceImpl()
{
	return new TraceImplType();
}
#undef TraceImplType

#pragma endregion Projectile

	// Sound
#pragma region

#define SoundImplType NCsWeapon::NTrace::NImpl::NSound::FImpl
SoundImplType* ACsTraceWeaponActor::ConstructSoundImpl()
{
	return new SoundImplType();
}
#undef SoundImplType

#pragma endregion Sound

	// FX
#pragma region

#define FXImplType NCsWeapon::NTrace::NImpl::NFX::FImpl
FXImplType* ACsTraceWeaponActor::ConstructFXImpl()
{
	return new FXImplType();
}
#undef FXImplType

#pragma endregion FX

#pragma endregion Fire

// Visual
#pragma region

void ACsTraceWeaponActor::ConstructSkeletalMeshComponent()
{
	checkf(!SkeletalMeshComponent, TEXT("ACsTraceWeaponActor::ConstructSkeletalMeshComponent: SkeletalMeshComponent has already been constructed."));

	SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, FName("SkeletalMeshComponent"));
	SkeletalMeshComponent->RegisterComponent();
	SetRootComponent(SkeletalMeshComponent);
}

#pragma endregion Visual

// Print
#pragma region

FString ACsTraceWeaponActor::PrintNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(GetName()), *(GetClass()->GetName()));
}

FString ACsTraceWeaponActor::PrintNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(GetName()), *(GetClass()->GetName()), *(MyOwner->GetName()));
}

#pragma endregion Print