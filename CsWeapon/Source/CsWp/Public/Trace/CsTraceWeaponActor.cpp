#include "Trace/CsTraceWeaponActor.h"
#include "CsWp.h"

// CVar
#include "Trace/CsCVars_TraceWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
#include "Types/CsTypes_Math.h"
#include "Types/CsTypes_Collision.h"
// Library
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Skin/Data/Visual/CsLibrary_Data_Skin_Visual.h"
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"
#include "Library/CsLibrary_Camera.h"
#include "Library/CsLibrary_Material.h"
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
#include "Data/Visual/CsData_Weapon_VisualSkin.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
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
#include "Trace/Data/Params/CsParams_TraceWeapon_Trace.h"
#include "Trace/Data/Params/CsLibrary_Params_TraceWeapon_Trace.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

		namespace TimeBetweenShotsImpl
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

		namespace TraceImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FTraceImpl, GetStart);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FTraceImpl, GetDirection);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FTraceImpl, GetEnd);
			}
		}

		namespace SoundImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FSoundImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FSoundImpl, SetPayload);
			}
		}

		namespace FXImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FFXImpl, Play);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsTraceWeaponActor::FFXImpl, SetPayload);
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
		CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(TraceScopedHandle);

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
	TraceImpl->Outer = this;

	SoundImpl = ConstructSoundImpl();
	SoundImpl->Weapon = this;

	FXImpl = ConstructFXImpl();
	FXImpl->Weapon = this;

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
		// TraceScopedHandle
		{
			const FString& ScopeName		   = Str::Trace;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTrace;

			TraceScopedHandle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
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
}

// State
#pragma region

void ACsTraceWeaponActor::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsTraceWeaponActor::NCached;

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
	
	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

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

void ACsTraceWeaponActor::Fire()
{
	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::Fire;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(GetWorld()->GetGameInstance());

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	const FCsDeltaTime& TimeSinceStart = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTimeSinceStart(UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	Payload->CoroutineImpl.BindUObject(this, &ACsTraceWeaponActor::Fire_Internal);
	Payload->StartTime = UCsManager_Time::Get(GetWorld()->GetGameInstance())->GetTime(UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::Fire_Internal);
	Payload->SetFName(Name::Fire_Internal);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &ACsTraceWeaponActor::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

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

			Trace();
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

void ACsTraceWeaponActor::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void ACsTraceWeaponActor::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsTraceWeaponActor::NCached::TimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	UCsCoroutineScheduler* Scheduler = UCsCoroutineScheduler::Get(Outer->GetWorld()->GetGameInstance());

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	Payload->CoroutineImpl.BindRaw(this, &ACsTraceWeaponActor::FTimeBetweenShotsImpl::OnElapsedTime_Internal);
	Payload->StartTime = UCsManager_Time::Get(Outer->GetWorld()->GetGameInstance())->GetTime(Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::OnElapsedTime_Internal);
	Payload->SetFName(Name::OnElapsedTime_Internal);

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

FVector ACsTraceWeaponActor::FTraceImpl::GetStart()
{
	using namespace NCsTraceWeaponActor::NCached::TraceImpl;

	const FString& ScopeName		   = Str::GetStart;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTraceGetLocation;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetStart;

	// Get Data Slice
	typedef NCsWeapon::NTrace::NData::IData WeaponDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());
	
	// Get Trace Params

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	const ITrace* TraceParams = WeaponData->GetTraceParams();

	typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

	check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

	const FLocationInfo& LocationInfo = TraceParams->GetLocationInfo();
	const ELocation& LocationType	  = LocationInfo.GetType();

	// Self
	if (LocationType == ELocation::Self)
	{
		checkf(Outer->RootComponent, TEXT("%s: RootComponent is NULL."));

		return Outer->RootComponent->GetComponentLocation();
	}
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
		checkf(Outer->SkeletalMeshComponent, TEXT("%s:  SkeletalMeshComponent is NULL."), *Context);

		const FName& Bone = LocationInfo.GetBoneOrSocket();

		checkf(Bone != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid in Trace Params."), *Context);

		return Outer->SkeletalMeshComponent->GetBoneLocation(Bone);
	}
	// Socket
	if (LocationType == ELocation::Socket)
	{
		checkf(Outer->SkeletalMeshComponent, TEXT("%s:  SkeletalMeshComponent is NULL."), *Context);

		const FName& Socket = LocationInfo.GetBoneOrSocket();

		checkf(Socket != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid in Trace Params."), *Context);

		checkf(Outer->SkeletalMeshComponent->DoesSocketExist(Socket), TEXT("%s: Socket: %s does NOT exist on SkeletalMesh: %s."), *Context, *(Outer->SkeletalMeshComponent->SkeletalMesh->GetName()));

		const FTransform Transform = Outer->SkeletalMeshComponent->GetSocketTransform(Socket);

		return Transform.GetLocation();
	}
	// Component
	if (LocationType == ELocation::Component)
	{
		checkf(TraceComponentTransform, TEXT("%s: TraceComponentTransform is NULL."), *Context);

		return TraceComponentTransform->GetComponentLocation();
	}
	// Camera
	if (LocationType == ELocation::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			return FCsLibrary_Camera::GetLocationChecked(Context, TheOwner);
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
	}
	// Custom
	if (LocationType == ELocation::Custom)
	{
		checkf(GetStartImpl.IsBound(), TEXT("%s: NOT IMPLEMENTED. GetStartImpl is NOT Bound."));

		return GetStartImpl.Execute();
	}
	return FVector::ZeroVector;
}

FVector ACsTraceWeaponActor::FTraceImpl::GetDirection(const FVector& Start)
{
	using namespace NCsTraceWeaponActor::NCached::TraceImpl;

	const FString& ScopeName		   = Str::GetDirection;
	const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponTrace;
	const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponTraceScopedTimerTraceGetDirection;

	CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

	const FString& Context = Str::GetDirection;

	// Get Data Slice
	typedef NCsWeapon::NTrace::NData::IData WeaponDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());
	
	// Get Trace Params
	using namespace NCsWeapon::NTrace::NParams::NTrace;

	const ITrace* TraceParams = WeaponData->GetTraceParams();

	typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

	check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

	const FDirectionInfo& DirectionInfo = TraceParams->GetDirectionInfo();
	const EDirection& DirectionType		= DirectionInfo.GetType();
	const int32& DirectionRules			= DirectionInfo.GetRules();

	checkf(DirectionRules != NCsRotationRules::None, TEXT("%s: No DirectionRules set in TraceParams for Data."), *Context);

	// Self
	if (DirectionType == EDirection::Self)
	{
		checkf(Outer->RootComponent, TEXT("%s: RootComponent is NULL."), *Context);

		return NCsRotationRules::GetRotation(Outer->RootComponent->GetComponentRotation(), DirectionRules).Vector();
	}
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
		checkf(Outer->SkeletalMeshComponent, TEXT("%s:  SkeletalMeshComponent is NULL."), *Context);

		const FName& Bone = DirectionInfo.GetBoneOrSocket();

		checkf(Bone != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid in Trace Params."), *Context);

		return NCsRotationRules::GetRotation(Outer->SkeletalMeshComponent, Bone, DirectionRules).Vector();
	}
	// Socket
	if (DirectionType == EDirection::Socket)
	{
		checkf(Outer->SkeletalMeshComponent, TEXT("%s:  SkeletalMeshComponent is NULL."), *Context);

		const FName& Socket = DirectionInfo.GetBoneOrSocket();

		checkf(Socket != NAME_None, TEXT("%s: BoneOrSocket: None is NOT Valid in Trace Params."), *Context);

		checkf(Outer->SkeletalMeshComponent->DoesSocketExist(Socket), TEXT("%s: Socket: %s does NOT exist on SkeletalMesh: %s."), *Context, *(Outer->SkeletalMeshComponent->SkeletalMesh->GetName()));

		const FTransform Transform = Outer->SkeletalMeshComponent->GetSocketTransform(Socket);

		return NCsRotationRules::GetRotation(Transform.GetRotation().Rotator(), DirectionRules).Vector();
	}
	// Component
	if (DirectionType == EDirection::Component)
	{
		checkf(TraceComponentTransform, TEXT("%s: TraceComponentTransform is NULL."));
		
		const FRotator Rotation = NCsRotationRules::GetRotation(TraceComponentTransform, DirectionRules);

		return Rotation.Vector();
	}
	// Camera
	if (DirectionType == EDirection::Camera)
	{
		// Try to get camera through the owner
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			return FCsLibrary_Camera::GetDirectionChecked(Context, TheOwner, DirectionRules);
		}
		checkf(0, TEXT("%s: Failed to find Camera / Camera Component from %s."), *Context, *(Outer->PrintNameAndClass()));
	}
	// Trace
	if (DirectionType == EDirection::Trace)
	{
		// Try to get camera through the owner and
		// perform a Trace from the Owner's Camera Location in the
		// direction the Owner's Camera is looking
		if (UObject* TheOwner = Outer->GetMyOwner())
		{
			const FVector CameraStart = FCsLibrary_Camera::GetLocationChecked(Context, TheOwner);
			const FVector Dir		  = FCsLibrary_Camera::GetDirectionChecked(Context, TheOwner, DirectionRules);
			const FVector End		  = CameraStart + TraceParams->GetDistance() * Dir;

			FHitResult Hit;

			Outer->LineTrace(CameraStart, End, Hit);

			if (Hit.bBlockingHit)
			{
				return (Hit.ImpactPoint - Start).GetSafeNormal();
			}
			else
			{
				return (End - Start).GetSafeNormal();
			}
		}
		checkf(0, TEXT("%s: NOT IMPLEMENTED"));
	}
	return FVector::ZeroVector;
}

FVector ACsTraceWeaponActor::FTraceImpl::GetEnd(const FVector& Start)
{
	using namespace NCsTraceWeaponActor::NCached::TraceImpl;

	const FString& Context = Str::GetEnd;

	// Get Data Slice
	typedef NCsWeapon::NTrace::NData::IData WeaponDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	WeaponDataType* WeaponData = WeaponDataLibrary::GetInterfaceChecked<WeaponDataType>(Context, Outer->GetData());

	// Get Trace Params
	using namespace NCsWeapon::NTrace::NParams::NTrace;

	const ITrace* TraceParams = WeaponData->GetTraceParams();

	typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

	check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

	return Start + TraceParams->GetDistance() * GetDirection(Start);
}

void ACsTraceWeaponActor::LineTrace(const FVector& Start, const FVector& End, FHitResult& OutHit)
{
	//CS_SCOPED_TIMER(LineTraceScopedHandle);

	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::LineTrace;

	UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(GetWorld()->GetGameState());

	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();
	Request->Start	= Start;
	Request->End	= End;

	// Get collision information related to the trace.
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	TraceDataType* TraceData = WeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

	typedef NCsWeapon::NTrace::NParams::NTrace::ITrace TraceParamsType;

	const TraceParamsType* TraceParams = TraceData->GetTraceParams();

	typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

	check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

	Request->Type   = ECsTraceType::Line;
	Request->Method = ECsTraceMethod::Single;
	Request->Query  = ECsTraceQuery::ObjectType;

	const FCollisionShape& Shape = TraceParams->GetShape();

	// For now assume trace via ObjectType
	const TArray<ECollisionChannel>& ObjectTypes = TraceParams->GetObjectTypes();

	for (const ECollisionChannel& ObjectType : ObjectTypes)
	{
		Request->ObjectParams.AddObjectTypesToQuery(ObjectType);
	}

	FCsTraceResponse* Response = Manager_Trace->Trace(Request);

	OutHit = Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

#if !UE_BUILD_SHIPPING
	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponTraceLineTrace))
	{
		UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

		Settings->TraceWeaponImpl.Debug.DrawLineTrace.Draw(GetWorld(), Start, End, OutHit);
	}
#endif // #if !UE_BUILD_SHIPPING
}

void ACsTraceWeaponActor::Trace()
{
	CS_SCOPED_TIMER(TraceScopedHandle);

	using namespace NCsTraceWeaponActor::NCached;

	const FString& Context = Str::Trace;

	const FVector Start = TraceImpl->GetStart();
	const FVector End	= TraceImpl->GetEnd(Start);

	UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(GetWorld()->GetGameState());
	
	FCsTraceRequest* Request = Manager_Trace->AllocateRequest();
	Request->Start = Start;
	Request->End   = End;

	// Get collision information related to the trace.
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	TraceDataType* TraceData = WeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);
	
	typedef NCsWeapon::NTrace::NParams::NTrace::ITrace TraceParamsType;

	const TraceParamsType* TraceParams = TraceData->GetTraceParams();

	typedef NCsWeapon::NTrace::NParams::NTrace::FLibrary TraceParamsLibrary;

	check(TraceParamsLibrary::IsValidChecked(Context, TraceParams));

	const FCollisionShape& Shape = TraceParams->GetShape();

	// Line
	if (Shape.IsLine())
	{
		Request->Type = ECsTraceType::Line;
	}
	else
	{
		Request->Type = ECsTraceType::Sweep;
	}

	Request->Method = ECsTraceMethod::Single;
	Request->Query  = ECsTraceQuery::ObjectType;

	Request->Shape = Shape;

	// For now assume trace via ObjectType
	const TArray<ECollisionChannel>& ObjectTypes = TraceParams->GetObjectTypes();

	for (const ECollisionChannel& ObjectType : ObjectTypes)
	{
		Request->ObjectParams.AddObjectTypesToQuery(ObjectType);
	}

	FCsTraceResponse* Response = Manager_Trace->Trace(Request);
	
#if !UE_BUILD_SHIPPING
	if (FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::DrawWeaponTraceTrace))
	{
		UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();
		const FHitResult& Hit		= Response->bResult ? Response->OutHits[CS_FIRST] : NCsCollision::NHit::Default;

		Settings->TraceWeaponImpl.Debug.DrawTrace.Draw(GetWorld(), Start, End, &Shape, Hit);
	}
#endif // #if !UE_BUILD_SHIPPING

	// TODO: OnHit
}

ACsTraceWeaponActor::FTraceImpl* ACsTraceWeaponActor::ConstructTraceImpl()
{
	return new ACsTraceWeaponActor::FTraceImpl();
}

#pragma endregion Projectile

	// Sound
#pragma region

void ACsTraceWeaponActor::FSoundImpl::Play()
{
	using namespace NCsTraceWeaponActor::NCached::SoundImpl;

	const FString& Context = Str::Play;

	// SoundDataType (NCsWeapon::NTrace::NData::NSound::NFire::IFire)
	typedef NCsWeapon::NTrace::NData::NSound::NFire::IFire SoundDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	if (SoundDataType* SoundData = WeaponDataLibrary::GetSafeInterfaceChecked<SoundDataType>(Context, Weapon->GetData()))
	{
		typedef NCsWeapon::NTrace::NData::NSound::NFire::NParams::IParams ParamsType;

		const ParamsType* Params = SoundData->GetFireSoundParams();
		const FCsSound& Sound	 = Params->GetSound();

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
void ACsTraceWeaponActor::FSoundImpl::SetPayload(SoundPayloadType* Payload, const FCsSound& Sound)
{
#undef SoundPayloadType

	using namespace NCsTraceWeaponActor::NCached::SoundImpl;

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

ACsTraceWeaponActor::FSoundImpl* ACsTraceWeaponActor::ConstructSoundImpl()
{
	return new ACsTraceWeaponActor::FSoundImpl();
}

#pragma endregion Sound

	// FX
#pragma region

void ACsTraceWeaponActor::FFXImpl::Play()
{
	using namespace NCsTraceWeaponActor::NCached::FXImpl;

	const FString& Context = Str::Play;

	// FXDataType (NCsWeapon::NTrace::NData::NVisual::NFire::IFire)
	typedef NCsWeapon::NTrace::NData::NVisual::NFire::IFire FXDataType;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	if (FXDataType* FXData = WeaponDataLibrary::GetSafeInterfaceChecked<FXDataType>(Context, Weapon->GetData()))
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
void ACsTraceWeaponActor::FFXImpl::SetPayload(FXPayloadType* Payload, const FCsFX& FX)
{
#undef FXPayloadType

	using namespace NCsTraceWeaponActor::NCached::FXImpl;

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
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	FXDataType* FXData = WeaponDataLibrary::GetInterfaceChecked<FXDataType>(Context, Weapon->GetData());

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
void ACsTraceWeaponActor::FFXImpl::SetPayload(FXPayloadType* Payload, FXDataType* FXData)
{
#undef FXPayloadType
#undef FXDataType

	using namespace NCsTraceWeaponActor::NCached::FXImpl;

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

ACsTraceWeaponActor::FFXImpl* ACsTraceWeaponActor::ConstructFXImpl()
{
	return new ACsTraceWeaponActor::FFXImpl();
}

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