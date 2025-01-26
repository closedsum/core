#include "Trace/CsTraceWeaponComponent.h"
#include "CsWp.h"

// CVar
#include "Trace/CsCVars_TraceWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsTypes_Math.h"
// Library
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
	// Pool
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
	// Data
#include "Data/CsLibrary_Data_Weapon.h"
#include "Data/Visual/CsLibrary_Data_Skin_Visual.h"
	// Common
#include "Camera/CsLibrary_Camera.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_DataType.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Weapon/CsManager_Weapon.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/Visual/CsData_Weapon_VisualSkin.h"
#include "Data/Visual/CsData_Skin_Visual.h"
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
#include "Trace/Impl/CsTraceWeapon_Impl_Trace.h"
#include "Trace/Impl/CsTraceWeapon_Impl_FX.h"
#include "Trace/Impl/CsTraceWeapon_Impl_Sound.h"
// Game
#include "GameFramework/GameStateBase.h" // TODO: Move usage through a library

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTraceWeaponComponent)

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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, LineTrace);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsTraceWeaponComponent, Trace);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsTraceWeaponComponent, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsTraceWeaponComponent, Abort_Fire_Internal);
		}

		namespace NTimeBetweenShotsImpl
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
	TraceImpl->SetOuter(this);

	SoundImpl = ConstructSoundImpl();
	SoundImpl->SetOuter(this);

	FXImpl = ConstructFXImpl();
	FXImpl->SetOuter(this);

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

// ICsTraceWeapon
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

#pragma endregion ICsTraceWeapon

void UCsTraceWeaponComponent::Init()
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::Init;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, UpdateGroup);
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeapon, WeaponType);

	// Get Data
	Data = UCsManager_Weapon::Get(GetWorld()->GetGameState())->GetDataChecked(Context, WeaponType.GetFName());

	check(CsWeaponDataLibrary::IsValidChecked(Context, Data));

	// Set Skin
	{
		if (CsWeaponSkinDataType* WeaponSkin = CsWeaponDataLibrary::GetSafeInterfaceChecked<CsWeaponSkinDataType>(Context, Data))
		{
			CsSkinDataType* Skin = WeaponSkin->GetSkin();

			checkf(Skin, TEXT("%s: Failed to get Skin of type: %s from Data."), *Context, *(CsSkinDataType::Name.ToString()));

			// Static Mesh
			CsSkinDataLibrary::SetSafeStaticMeshAndMaterials(Context, Skin, GetStaticMeshComponent());
			// Skeletal Mesh
			CsSkinDataLibrary::SetSafeSkeletalMeshAndMaterials(Context, Skin, GetSkeletalMeshComponent());
		}
	}

	// Set States
	UCsWeaponSettings* Settings = GetMutableDefault<UCsWeaponSettings>();

	IdleState = Settings->ProjectileWeaponImpl.IdleState;
	FireState = Settings->ProjectileWeaponImpl.FireState;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, IdleState);
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponState, FireState);

	CurrentState = IdleState;

	// Ammo
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* PrjData = CsWeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

	CurrentAmmo = PrjData->GetMaxAmmo();

	TraceImpl->SetOwner(MyOwner);
	TraceImpl->SetFXImpl(FXImpl);
	TraceImpl->SetSoundImpl(SoundImpl);

	check(TraceImpl->IsValidChecked(Context));

	FXImpl->SetOwner(MyOwner);
	SoundImpl->SetOwner(MyOwner);
}

// State
#pragma region

void UCsTraceWeaponComponent::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsTraceWeaponComponent::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

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
	
	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* PrjData = CsWeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

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
		const TCHAR*(*ToChar)(const bool& Value) = &CsDataTypeLibrary::ToChar;

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

	UCsCoroutineScheduler* Scheduler = CsCoroutineSchedulerLibrary::GetChecked(Context, this);

	// End previous Fire Routine
	Scheduler->End(UpdateGroup, FireRoutineHandle);

	const FCsDeltaTime& TimeSinceStart = CsTimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	Fire_StartTime = TimeSinceStart.Time;

	// Setup Fire Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

	#define COROUTINE Fire_Internal

	Payload->CoroutineImpl.BindUObject(this, &UCsTraceWeaponComponent::COROUTINE);
	Payload->StartTime = CsTimeManagerLibrary::GetTimeChecked(Context, this, UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &UCsTraceWeaponComponent::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	#undef COROUTINE

	// Cache pointer to TraceDataType (NCsWeapon::NTrace::NData::IData)
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* TraceData = CsWeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Data);

	check(CsWeaponDataLibrary::IsValidChecked(Context, Data));

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

	ElapsedTime += R->GetDeltaTime();
	
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

void UCsTraceWeaponComponent::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void UCsTraceWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsTraceWeaponComponent::NCached::NTimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	UCsCoroutineScheduler* Scheduler = CsCoroutineSchedulerLibrary::GetChecked(Context, Outer);

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	#define COROUTINE OnElapsedTime_Internal

	Payload->CoroutineImpl.BindRaw(this, &UCsTraceWeaponComponent::FTimeBetweenShotsImpl::COROUTINE);
	Payload->StartTime = CsTimeManagerLibrary::GetTimeChecked(Context, Outer, Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	// Get total elapsed time (= TimeBetweenShots)
	typedef NCsWeapon::NTrace::NData::IData TraceDataType;

	TraceDataType* TraceData = CsWeaponDataLibrary::GetInterfaceChecked<TraceDataType>(Context, Outer->GetData());

	Payload->SetValue_Float(CS_FIRST, TraceData->GetTimeBetweenShots());

	Scheduler->Start(Payload);
}

char UCsTraceWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
{
	FCsDeltaTime& ElapsedTime			   = R->GetValue_DeltaTime(CS_FIRST);
	const FCsDeltaTime PreviousElapsedTime = ElapsedTime;

	ElapsedTime += R->GetDeltaTime();

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
TraceImplType* UCsTraceWeaponComponent::ConstructTraceImpl()
{
	return new TraceImplType();
}
#undef TraceImplType

#pragma endregion Projectile

	// Sound
#pragma region

#define SoundImplType NCsWeapon::NTrace::NImpl::NSound::FImpl
SoundImplType* UCsTraceWeaponComponent::ConstructSoundImpl()
{
	return new SoundImplType();
}
#undef SoundImplType

#pragma endregion Sound

	// FX
#pragma region

#define FXImplType NCsWeapon::NTrace::NImpl::NFX::FImpl
FXImplType* UCsTraceWeaponComponent::ConstructFXImpl()
{
	return new FXImplType();
}
#undef FXImplType

#pragma endregion FX

#pragma endregion Fire

// Visual
#pragma region

void UCsTraceWeaponComponent::ConstructSkeletalMeshComponent()
{
	checkf(!SkeletalMeshComponent, TEXT("UCsTraceWeaponComponent::ConstructSkeletalMeshComponent: SkeletalMeshComponent has already been constructed."));

	SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, FName("SkeletalMeshComponent"));
	SkeletalMeshComponent->RegisterComponent();
}

#pragma endregion Visual

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