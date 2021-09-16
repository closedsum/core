#include "Beam/CsBeamWeaponComponent.h"
#include "CsWp.h"

// CVar
#include "Beam/CsCVars_BeamWeapon.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Types
#include "Types/CsCached.h"
#include "Types/CsTypes_Math.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Skin/Data/Visual/CsLibrary_Data_Skin_Visual.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Library/CsLibrary_Camera.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsWeaponSettings.h"
// Managers
#include "Managers/Weapon/CsManager_Weapon.h"
// Data
#include "Data/CsData_Weapon.h"
#include "Data/Visual/CsData_Weapon_VisualSkin.h"
#include "Skin/Data/Visual/CsData_Skin_Visual.h"
#include "Beam/Data/CsData_BeamWeapon.h"
// Components
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
// Weapon
#include "Impl/CsBeamWeapon_Impl_Beam.h"
#include "Impl/CsBeamWeapon_Impl_FX.h"
#include "Impl/CsBeamWeapon_Impl_Sound.h"

// Cached 
#pragma region

namespace NCsBeamWeaponComponent
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, SetUpdateGroup);
			CS_DEFINE_CACHED_STRING(Group, "Group");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, SetWeaponType);
			CS_DEFINE_CACHED_STRING(Type, "Type");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, SetBeamType);

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, Init);
			CS_DEFINE_CACHED_STRING(UpdateGroup, "UpdateGroup");
			CS_DEFINE_CACHED_STRING(WeaponType, "WeaponType");
			CS_DEFINE_CACHED_STRING(IdleState, "IdleState");
			CS_DEFINE_CACHED_STRING(FireState, "FireState");

			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, OnUpdate_HandleStates);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, CanFire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, Fire);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent, Fire_Internal);
		}

		namespace Name
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsBeamWeaponComponent, Fire_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsBeamWeaponComponent, Abort_Fire_Internal);
		}

		namespace NTimeBetweenShotsImpl
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsBeamWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(UCsBeamWeaponComponent::FTimeBetweenShotsImpl, OnElapsedTime_Internal);
			}
		}
	}
}

#pragma endregion Cached

UCsBeamWeaponComponent::UCsBeamWeaponComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	// ICsUpdate
	UpdateGroup(),
	// Weapon
	WeaponType(),
	Data(nullptr),
	BeamData(nullptr),
	// Beam
	BeamType(),
	// Owner
	MyOwner(nullptr),
	MyOwnerAsActor(nullptr),
	// State
	CurrentState(),
	IdleState(),
	FireState(),
	// Charge
	CurrentCharge(0.0f),
	// Fire
	bFire(false),
	bFire_Last(false),
	Fire_StartTime(0.0f),
	FireCount(0),
	FireRoutineHandle(),
	// Trace
	BeamImpl(nullptr),
	// Sound
	SoundImpl(nullptr),
	// FX
	FXImpl(nullptr)
{
}

// UObject Interface
#pragma region

void UCsBeamWeaponComponent::BeginDestroy()
{
	Super::BeginDestroy();
	
	CS_SILENT_CLEAR_SCOPED_TIMER_HANDLE(FireScopedHandle.Handle);

	CS_SAFE_DELETE_PTR(BeamImpl)
	CS_SAFE_DELETE_PTR(SoundImpl)
	CS_SAFE_DELETE_PTR(FXImpl)
}

#pragma endregion UObject Interface

// UActorComponent Interface
#pragma region

void UCsBeamWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner		   = GetOwner();
	MyOwnerAsActor = GetOwner();

	TimeBetweenShotsImpl.Outer = this;

	BeamImpl = ConstructBeamImpl();
	BeamImpl->SetOuter(this);

	SoundImpl = ConstructSoundImpl();
	SoundImpl->SetOuter(this);

	FXImpl = ConstructFXImpl();
	FXImpl->SetOuter(this);

	// ScopedHandles
#if !UE_BUILD_SHIPPING
	{
		using namespace NCsBeamWeaponComponent::NCached;

		// FireScopedHandle
		{
			const FString& ScopeName		   = Str::Fire_Internal;
			const FECsScopedGroup& ScopedGroup = NCsScopedGroup::WeaponBeam;
			const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogWeaponBeamScopedTimerFire;

			FireScopedHandle.Handle = FCsManager_ScopedTimer::Get().GetHandle(&ScopeName, ScopedGroup, ScopeLog);
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

#pragma endregion UActorComponent Interface

// ICsUpdate
#pragma region

void UCsBeamWeaponComponent::Update(const FCsDeltaTime& DeltaTime)
{ 
	OnUpdate_HandleStates(DeltaTime);
}

#pragma endregion ICsUpdate

// Update
#pragma region

void UCsBeamWeaponComponent::SetUpdateGroup(const FECsUpdateGroup& Group)
{
	using namespace NCsBeamWeaponComponent::NCached;

	const FString& Context = Str::SetUpdateGroup;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::Group, Group));

	UpdateGroup = Group;
}

#pragma endregion Update

// Weapon
#pragma region

void UCsBeamWeaponComponent::SetWeaponType(const FECsWeapon& Type)
{
	using namespace NCsBeamWeaponComponent::NCached;

	const FString& Context = Str::SetWeaponType;

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::Type, Type));

	WeaponType = Type;
}

#pragma endregion Weapon

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

// Beam
#pragma region

void UCsBeamWeaponComponent::SetBeamType(const FECsBeam& Type)
{
	using namespace NCsBeamWeaponComponent::NCached;

	const FString& Context = Str::SetBeamType;

	check(EMCsBeam::Get().IsValidEnumChecked(Context, Str::Type, Type));

	BeamType = Type;
}

#pragma endregion Beam

// ICsBeamWeapon
#pragma region

void UCsBeamWeaponComponent::StartFire()
{
	bFire = true;

	Update(FCsDeltaTime::Zero);
}

void UCsBeamWeaponComponent::StopFire()
{
	bFire = false;

	Update(FCsDeltaTime::Zero);
}

#pragma endregion ICsBeamWeapon

void UCsBeamWeaponComponent::Init()
{
	using namespace NCsBeamWeaponComponent::NCached;

	const FString& Context = Str::Init;

	check(EMCsUpdateGroup::Get().IsValidEnumChecked(Context, Str::UpdateGroup, UpdateGroup));

	check(EMCsWeapon::Get().IsValidEnumChecked(Context, Str::WeaponType, WeaponType));

	// Get Data
	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

	Data = WeaponManagerLibrary::GetDataChecked(Context, this, WeaponType.GetFName());

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

	typedef NCsWeapon::NBeam::NData::IData BeamDataType;

	BeamData = WeaponDataLibrary::GetInterfaceChecked<BeamDataType>(Context, Data);

	CurrentCharge = BeamData->GetMaxCharge();

	BeamImpl->SetOwner(MyOwner);
	BeamImpl->SetFXImpl(FXImpl);
	BeamImpl->SetSoundImpl(SoundImpl);

	check(BeamImpl->IsValidChecked(Context));

	FXImpl->SetOwner(MyOwner);
	SoundImpl->SetOwner(MyOwner);
}

// State
#pragma region

void UCsBeamWeaponComponent::OnUpdate_HandleStates(const FCsDeltaTime& DeltaTime)
{
	using namespace NCsBeamWeaponComponent::NCached;

	const FString& Context = Str::OnUpdate_HandleStates;

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponBeamState))
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
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponBeamStateTransition))
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
			if (CS_CVAR_LOG_IS_SHOWING(LogWeaponBeamStateTransition))
			{
				UE_LOG(LogCsWp, Warning, TEXT("%s: CurrentState: Fire -> Idle."), *Context);
			}
#endif // #if !UE_BUILD_SHIPPING
		}
	}

	bFire_Last = bFire;
}

#pragma endregion State

// Charge
#pragma region

void UCsBeamWeaponComponent::ConsumeCharge()
{
	float PreviousCharge = CurrentCharge;
	// TODO: Decrement properly
	--CurrentCharge;

	OnConsumeCharge_Event.Broadcast(this, PreviousCharge, CurrentCharge);
}

#pragma endregion Charge

// Fire
#pragma region

bool UCsBeamWeaponComponent::CanFire() const
{
	using namespace NCsBeamWeaponComponent::NCached;

	const FString& Context = Str::CanFire;
	
	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	const FCsDeltaTime& TimeSinceStart = TimeManagerLibrary::GetTimeSinceStartChecked(Context, this, UpdateGroup);

	// Check if enough time has elapsed to fire again.
	const bool Pass_Time = (TimeSinceStart.Time - Fire_StartTime > BeamData->GetTimeBetweenShots());
	// Check if bFire is set, its not on release, and its either bFire is just set or FullAuto.
	const bool Pass_Fire = bFire && !BeamData->DoFireOnRelease() && (BeamData->IsFullAuto() || !bFire_Last);
	// Check if bFire has just been unset and on release.
	const bool Pass_FireOnRelease = !bFire && BeamData->DoFireOnRelease() && bFire_Last;
	// Check if has ammo to fire.
	const bool Pass_Charge = BeamData->HasInfiniteCharge() || CurrentCharge > 0.0f;

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogWeaponBeamCanFire))
	{
		using namespace NCsCached;

		UE_LOG(LogCsWp, Warning, TEXT("%s"), *Context);
		// Pass_Time
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Time (%s): %f - %f > %f"), ToChar(Pass_Time), TimeSinceStart.Time, Fire_StartTime, BeamData->GetTimeBetweenShots());
		// Pass_Fire
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Fire (%s): %s && %s && (%s || %s)"), ToChar(Pass_Fire), ToChar(bFire), ToChar(!BeamData->DoFireOnRelease()), ToChar(BeamData->IsFullAuto()), ToChar(!bFire_Last));
		// Pass_FireOnRelease
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_FireOnRelease (%s): %s && %s && %s"), ToChar(Pass_FireOnRelease), ToChar(!bFire), ToChar(BeamData->DoFireOnRelease()), ToChar(bFire_Last));
		// Pass_Ammo
		UE_LOG(LogCsWp, Warning, TEXT("  Pass_Charge (%s): %s || %s"), ToChar(Pass_Charge), ToChar(BeamData->HasInfiniteCharge()), ToChar(CurrentCharge > 0.0f));

		// Result
		UE_LOG(LogCsWp, Warning, TEXT(" Result (%s): %s && (%s || %s) && %s"), ToChar(Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Charge), ToChar(Pass_Time), ToChar(Pass_Fire), ToChar(Pass_FireOnRelease), ToChar(Pass_Charge));
	}
#endif // #if !UE_BUILD_SHIPPING

	return Pass_Time && (Pass_Fire || Pass_FireOnRelease) && Pass_Charge;
}

void UCsBeamWeaponComponent::Fire()
{
	using namespace NCsBeamWeaponComponent::NCached;

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

	Payload->CoroutineImpl.BindUObject(this, &UCsBeamWeaponComponent::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, this, UpdateGroup);
	Payload->Owner.SetObject(this);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);
	Payload->OnEnds.AddDefaulted();
	Payload->OnEnds.Last().BindUObject(this, &UCsBeamWeaponComponent::Fire_Internal_OnEnd);
	Payload->AbortMessages.Add(Name::Abort_Fire_Internal);

	#undef COROUTINE

	Payload->SetValue_Flag(CS_FIRST, BeamData->HasInfiniteCharge());
	Payload->SetValue_Int(CS_FIRST, BeamData->GetBeamsPerShot());
	Payload->SetValue_Float(CS_FIRST, BeamData->GetTimeBetweenBeamsPerShot());

	FireRoutineHandle = Scheduler->Start(Payload);
}

char UCsBeamWeaponComponent::Fire_Internal(FCsRoutine* R)
{
	using namespace NCsBeamWeaponComponent::NCached;

	const bool& bInfiniteCharge = R->GetValue_Flag(CS_FIRST);

	static const int32 BEAMS_PER_SHOT = 0;
	const int32& BeamsPerShot = R->GetValue_Int(BEAMS_PER_SHOT);

	const float& TimeBetweenBeamsPerShot = R->GetValue_Float(CS_FIRST);

	static const int32 CURRENT_BEAM_PER_SHOT_INDEX = 1;
	int32& CurrentBeamPerShotIndex = R->GetValue_Int(CURRENT_BEAM_PER_SHOT_INDEX);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);

	ElapsedTime += R->DeltaTime;
	
	CS_COROUTINE_BEGIN(R);

	++FireCount;

	do 
	{
		{
			CS_SET_SCOPED_TIMER_HANDLE(FireScopedHandle);

			ElapsedTime.Reset();

			if (!bInfiniteCharge)
				ConsumeCharge();

			BeamImpl->Emit(Data);
			SoundImpl->TryFire(Data);
			FXImpl->TryFire(Data);

			// Increment the shot index
			CurrentBeamPerShotIndex = FMath::Min(CurrentBeamPerShotIndex + 1, BeamsPerShot);

			// Check if more projectiles should be fired, if so wait
			if (CurrentBeamPerShotIndex < BeamsPerShot)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= TimeBetweenBeamsPerShot);
			}

			CS_UPDATE_SCOPED_TIMER_HANDLE(FireScopedHandle);
		}
	} while (CurrentBeamPerShotIndex < BeamsPerShot);

	CS_COROUTINE_END(R);
}

void UCsBeamWeaponComponent::Fire_Internal_OnEnd(FCsRoutine* R)
{
	--FireCount;
}

void UCsBeamWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime()
{
	using namespace NCsBeamWeaponComponent::NCached::NTimeBetweenShotsImpl;

	const FString& Context = Str::OnElapsedTime;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	UCsCoroutineScheduler* Scheduler = CoroutineSchedulerLibrary::GetChecked(Context, Outer);

	// Setup Routine
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	PayloadType* Payload = Scheduler->AllocatePayload(Outer->GetUpdateGroup());

	#define COROUTINE OnElapsedTime_Internal

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	Payload->CoroutineImpl.BindRaw(this, &UCsBeamWeaponComponent::FTimeBetweenShotsImpl::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, Outer, Outer->GetUpdateGroup());
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	// Get total elapsed time (= TimeBetweenShots)
	Payload->SetValue_Float(CS_FIRST, Outer->GetBeamData()->GetTimeBetweenShots());

	Scheduler->Start(Payload);
}

char UCsBeamWeaponComponent::FTimeBetweenShotsImpl::OnElapsedTime_Internal(FCsRoutine* R)
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

	// Beam
#pragma region

#define BeamImplType NCsWeapon::NBeam::NImpl::NBeam::FImpl
BeamImplType* UCsBeamWeaponComponent::ConstructBeamImpl()
{
	return new BeamImplType();
}
#undef BeamImplType

#pragma endregion Beam

	// Sound
#pragma region

#define SoundImplType NCsWeapon::NBeam::NImpl::NSound::FImpl
SoundImplType* UCsBeamWeaponComponent::ConstructSoundImpl()
{
	return new SoundImplType();
}
#undef SoundImplType

#pragma endregion Sound

	// FX
#pragma region

#define FXImplType NCsWeapon::NBeam::NImpl::NFX::FImpl
FXImplType* UCsBeamWeaponComponent::ConstructFXImpl()
{
	return new FXImplType();
}
#undef FXImplType

#pragma endregion FX

#pragma endregion Fire

// Visual
#pragma region

void UCsBeamWeaponComponent::ConstructSkeletalMeshComponent()
{
	checkf(!SkeletalMeshComponent, TEXT("UCsBeamWeaponComponent::ConstructSkeletalMeshComponent: SkeletalMeshComponent has already been constructed."));

	SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, FName("SkeletalMeshComponent"));
	SkeletalMeshComponent->RegisterComponent();
}

#pragma endregion Visual

// Print
#pragma region

FString UCsBeamWeaponComponent::PrintNameAndClass()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s"), *(GetName()), *(GetClass()->GetName()));
}

FString UCsBeamWeaponComponent::PrintNameClassAndOwner()
{
	return FString::Printf(TEXT("Weapon: %s with Class: %s with MyOwner: %s"), *(GetName()), *(GetClass()->GetName()), *(MyOwner->GetName()));
}

#pragma endregion Print