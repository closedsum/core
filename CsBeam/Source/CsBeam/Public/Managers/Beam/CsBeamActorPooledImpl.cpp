// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Beam/CsBeamActorPooledImpl.h"
#include "CsBeam.h"

// CVar
#include "Managers/Beam/CsCVars_Beam.h"
// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
#include "Managers/Sound/CsLibrary_Manager_Sound.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "Managers/Trace/CsLibrary_Manager_Trace.h"
#include "Managers/Beam/CsLibrary_Manager_Beam.h"
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Data/CsLibrary_Data_Beam.h"
#include "Payload/CsLibrary_Payload_Beam.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Managers/Damage/Modifier/CsLibrary_DamageModifier.h"
#include "Collision/CsTypes_Collision.h"
#include "Library/CsLibrary_Common.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsGetInterfaceMap.h"
// Components
#include "Components/StaticMeshComponent.h"
// Data
#include "Data/CsData_Beam.h"
#include "Data/Collision/CsData_Beam_Collision.h"
#include "Data/Visual/StaticMesh/CsData_Beam_VisualStaticMesh.h"
#include "Data/Visual/Impact/CsData_Beam_VisualImpact.h"
#include "Data/Sound/CsData_Beam_SoundImpact.h"
#include "Data/Damage/CsData_Beam_Damage.h"
#include "Managers/Damage/Data/CsData_Damage.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// Beam
#include "Cache/CsCache_BeamImpl.h"
#include "Payload/Damage/CsPayload_BeamModifierDamage.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Damage
#include "Managers/Damage/Value/Point/CsDamageValuePointImpl.h"
#include "Managers/Damage/Value/Range/CsDamageValueRangeImpl.h"
// Scoped
#include "Managers/ScopedTimer/CsTypes_Manager_ScopedTimer.h"

//#define CS_COLLISION_PROJECTILE	ECC_GameTraceChannel2

// Cached
#pragma region

namespace NCsBeamActorPooledImpl
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, SetType);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, OnCollision);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, Allocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, Deallocate);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, On);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, PrepareOn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, OnPrepareOn_SetModifiers);
		}

		namespace ScopedTimer
		{
			CS_DEFINE_CACHED_STRING(SetCollision, "ACsBeamActorPooledImpl::Launch_SetCollision");
			CS_DEFINE_CACHED_STRING(SetTrailVisual, "ACsBeamActorPooledImpl::Launch_SetTrailVisual");
		}
	}

	namespace NDamageImpl
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl::FDamageImpl, SetValue);
			}
		}
	}
}

#pragma endregion Cached

ACsBeamActorPooledImpl::ACsBeamActorPooledImpl(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	Type(),
	// Collision
	IgnoreActors(),
	IgnoreActorSet(),
	IgnoreComponents(),
	IgnoreComponentSet(),
	bDeallocateOnCollision(true),
	CollisionCount(0),
	CollisionCountdownToDeallocate(0),
	// ICsPooledObject
	Cache(nullptr),
	CacheImpl(nullptr),
	// ICsBeam
	Data(nullptr),
	// Beam
		// On
	bOnOnAllocate(true),
		// Off
	bOnOffDeallocate(true),
	// Damage
	DamageImpl()
{
	// Mesh Component
	MeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MeshComponent"));

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetCastShadow(false);
	MeshComponent->bCastDynamicShadow						  = false;
	MeshComponent->PrimaryComponentTick.bStartWithTickEnabled = false;
	MeshComponent->Deactivate();

	RootComponent = MeshComponent;

	PrimaryActorTick.bCanEverTick		   = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup			   = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_None);
	bReplicates		   = false;
	SetReplicatingMovement(false);
}

// UObject Interface
#pragma region

void ACsBeamActorPooledImpl::BeginDestroy()
{
	Super::BeginDestroy();

	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}
}

#pragma endregion UObject Interface

// AActor Interface
#pragma region

void ACsBeamActorPooledImpl::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetComponentTickEnabled(false);

	SetActorTickEnabled(false);

	ConstructCache();

	DamageImpl.Outer = this;
}

void ACsBeamActorPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Deallocate_Internal();
	SetActorLocation(FVector::ZeroVector);
	Cache->QueueDeallocate();
}

void ACsBeamActorPooledImpl::OutsideWorldBounds()
{
	Deallocate_Internal();
	SetActorLocation(FVector::ZeroVector);
	Cache->QueueDeallocate();
}

#pragma endregion AActor Interface

void ACsBeamActorPooledImpl::SetType(const FECsBeam& InType)
{
	using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::SetType;

	check(EMCsBeam::Get().IsValidEnumChecked(Context, InType));

	if (Type != InType)
	{
		Type = InType;

		typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;

		// Get Data associated with Type
		Data = BeamManagerLibrary::GetDataChecked(Context, this, Type);
	}
}

// Collision
#pragma region

void ACsBeamActorPooledImpl::AddIgnoreActor(AActor* Actor)
{
	IgnoreActors.Add(Actor);
	IgnoreActorSet.Add(Actor);
}

AActor* ACsBeamActorPooledImpl::GetIgnoreActor(const int32& Index)
{
	if (Index >= IgnoreActors.Num())
		return nullptr;
	return IgnoreActors[Index].IsValid() ? IgnoreActors[Index].Get() : nullptr;
}

void ACsBeamActorPooledImpl::AddIgnoreComponent(UPrimitiveComponent* Component)
{
	IgnoreComponents.Add(Component);
	IgnoreComponentSet.Add(Component);
}

UPrimitiveComponent* ACsBeamActorPooledImpl::GetIgnoreComponent(const int32& Index)
{
	if (Index >= IgnoreComponents.Num())
		return nullptr;
	return IgnoreComponents[Index].IsValid() ? IgnoreComponents[Index].Get() : nullptr;
}

bool ACsBeamActorPooledImpl::IsIgnored(AActor* Actor) const
{
	if (!Actor)
		return false;

	return IgnoreActorSet.Find(Actor) != nullptr;
}

bool ACsBeamActorPooledImpl::IsIgnored(UPrimitiveComponent* Component) const
{
	if (!Component)
		return false;

	return IgnoreComponentSet.Find(Component) != nullptr;
}

void ACsBeamActorPooledImpl::OnCollision(UPrimitiveComponent* CollidingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::OnCollision;

	if (IsIgnored(OtherActor))
		return;

	if (IsIgnored(OtherComp))
		return;

#if !UE_BUILD_SHIPPING
	if (CS_CVAR_LOG_IS_SHOWING(LogBeamCollision))
	{
		UE_LOG(LogCsBeam, Warning, TEXT("%s (%s):"), *Context, *(GetName()));

		UE_LOG(LogCsBeam, Warning, TEXT("- CollidingComponent: %s"), CollidingComponent ? *(CollidingComponent->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("- OtherActor: %s"), OtherActor ? *(OtherActor->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("- OtherComp: %s"), OtherComp ? *(OtherComp->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("- NormalImpulse: %s"), *(NormalImpulse.ToString()));
		// HitResult
		UE_LOG(LogCsBeam, Warning, TEXT("- Hit"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- bBlockingHit: %s"), Hit.bBlockingHit ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- bStartPenetrating"), Hit.bStartPenetrating ? TEXT("True") : TEXT("False"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- Time: %f"), Hit.Time);
		UE_LOG(LogCsBeam, Warning, TEXT("-- Location: %s"), *(Hit.Location.ToString()));
		UE_LOG(LogCsBeam, Warning, TEXT("-- ImpactPoint: %s"), *(Hit.ImpactPoint.ToString()));
		UE_LOG(LogCsBeam, Warning, TEXT("-- Normal: %s"), *(Hit.Normal.ToString()));
		UE_LOG(LogCsBeam, Warning, TEXT("-- ImpactNormal: %s"), *(Hit.ImpactNormal.ToString()));
		UE_LOG(LogCsBeam, Warning, TEXT("-- TraceStart: %s"), *(Hit.TraceStart.ToString()));
		UE_LOG(LogCsBeam, Warning, TEXT("-- TraceEnd: %s"), *(Hit.TraceEnd.ToString()));
		UE_LOG(LogCsBeam, Warning, TEXT("-- PenetrationDepth: %f"), Hit.PenetrationDepth);
		UE_LOG(LogCsBeam, Warning, TEXT("-- Item: %d"), Hit.Item);
		UE_LOG(LogCsBeam, Warning, TEXT("-- PhysMaterial: %s"), Hit.PhysMaterial.IsValid() ? *(Hit.PhysMaterial->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- Actor: %s"), Hit.Actor.IsValid() ? *(Hit.Actor->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- Component: %s"), Hit.Component.IsValid() ? *(Hit.Component->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- BoneName: %s"), Hit.BoneName.IsValid() ? *(Hit.BoneName.ToString()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- FaceIndex: %d"), Hit.FaceIndex);
	}
#endif // #if !UE_BUILD_SHIPPING

	// Get Physics Surface
	EPhysicalSurface SurfaceType	= NCsHitResult::GetPhysSurfaceType(Hit);

	typedef NCsBeam::NData::FLibrary BeamDataLibrary;

	// ImpactVisualDataType (NCsBeam::NData::NVisual::NImpact::IImpact)
	{
		typedef NCsBeam::NData::NVisual::NImpact::IImpact ImpactVisualDataType;

		if (ImpactVisualDataType* ImpactVisualData = BeamDataLibrary::GetSafeInterfaceChecked<ImpactVisualDataType>(Context, Data))
		{
			typedef NCsFX::NManager::FLibrary FXManagerLibrary;
			typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

			PayloadImplType Payload;
			Payload.Instigator = Cache->GetInstigator();

			const FCsFX& ImpactFX = ImpactVisualData->GetImpactFX(SurfaceType);

			FTransform Transform = FTransform::Identity;
			Transform.SetLocation(Hit.Location);
			Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

			FXManagerLibrary::SpawnChecked(Context, this, &Payload, ImpactFX, Transform);
		}
	}
	// ImpactSoundDataType (NCsBeam::NData::NSound::NImpact::IImpact)
	{
		typedef NCsBeam::NData::NSound::NImpact::IImpact ImpactSoundDataType;

		if (ImpactSoundDataType* ImpactSoundData = BeamDataLibrary::GetSafeInterfaceChecked<ImpactSoundDataType>(Context, Data))
		{
			typedef NCsSound::NManager::FLibrary SoundManagerLibrary;
			typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

			PayloadImplType Payload;
			Payload.Instigator = Cache->GetInstigator();

			const FCsSound& ImpactSound = ImpactSoundData->GetImpactSound(SurfaceType);

			FTransform Transform = FTransform::Identity;
			Transform.SetLocation(Hit.Location);
			Transform.SetRotation(Hit.ImpactNormal.Rotation().Quaternion());

			SoundManagerLibrary::SpawnChecked(Context, this, &Payload, ImpactSound, Transform);
		}
	}
	// DamageDataType (NCsBeam::NData::NDamage::IDamage)
	{
		typedef NCsBeam::NData::NDamage::IDamage DamageDataType;

		if (DamageDataType* DamageData = BeamDataLibrary::GetSafeInterfaceChecked<DamageDataType>(Context, Data))
		{
			// NOTE: For now reset and apply the modifiers on each hit.
			// FUTURE: Look into having additional rules on how the modifiers are applied
			
			// Apply Modifiers
			DamageImpl.SetValue(DamageData->GetDamageData());

			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;

			DamageModifierLibrary::ModifyChecked(Context, DamageImpl.Modifiers, DamageData->GetDamageData(), DamageImpl.GetValue());

			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			DamageManagerLibrary::ProcessDataChecked(Context, this, DamageImpl.GetValue(), DamageData->GetDamageData(), GetCache()->GetInstigator(), this, Hit);
		}
	}

	// CollisionDataType (NCsBeam::NData::NCollision::ICollision)
	typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

	if (CollisionDataType* CollisionData = BeamDataLibrary::GetInterfaceChecked<CollisionDataType>(Context, Data))
	{
		if (CollisionData->IgnoreHitObjectAfterHit())
		{
			// Actor
			if (OtherActor)
			{
				AddIgnoreActor(OtherActor);
			}
			// Component
			if (OtherComp)
			{
				AddIgnoreComponent(OtherComp);
			}
		}
	}

	++CollisionCount;
	--CollisionCountdownToDeallocate;

	if (bDeallocateOnCollision && CollisionCountdownToDeallocate <= 0)
		Cache->QueueDeallocate();
}

#pragma endregion Collision

// ICsUpdate
#pragma region

void ACsBeamActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

void ACsBeamActorPooledImpl::ConstructCache()
{
	typedef NCsBeam::NCache::FImpl CacheImplType;

	CacheImpl = new CacheImplType();
	Cache	  = CacheImpl;
}

// ICsPooledObject
#pragma region

#define PooledPayloadType NCsPooledObject::NPayload::IPayload
void ACsBeamActorPooledImpl::Allocate(PooledPayloadType* Payload)
{
#undef PooledPayloadType

	using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::Allocate;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set Type
	typedef NCsBeam::NPayload::IPayload PayloadType;
	typedef NCsPooledObject::NPayload::FLibrary PooledPayloadLibrary;

	PayloadType* BeamPayload = PooledPayloadLibrary::GetInterfaceChecked<PayloadType>(Context, Payload);

	Type = BeamPayload->GetType();

	check(EMCsBeam::Get().IsValidEnumChecked(Context, Type));

	// Get Data associated with Type
	// TODO: FUTURE: Add to list of preserved changes
	typedef NCsBeam::NManager::FLibrary BeamManagerLibrary;

	Data = BeamManagerLibrary::GetDataChecked(Context, this, Type);

	// TODO: Need to determine best place to set LifeTime from Data

	// Set Data on Cache
	CacheImpl->Allocate(Payload);
	CacheImpl->SetData(Data);

	if (bOnOnAllocate)
	{
		PrepareOn(BeamPayload);
		On();
	}
}

void ACsBeamActorPooledImpl::Deallocate()
{
	Deallocate_Internal();
	Cache->Deallocate();
}

#pragma endregion ICsPooledObject

// PooledObject
#pragma region

void ACsBeamActorPooledImpl::Deallocate_Internal()
{
	using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::Deallocate;

	// Collision
	IgnoreActors.Reset(IgnoreActors.Max());
	IgnoreComponents.Reset(IgnoreComponents.Max());

	CollisionCount = 0;
	CollisionCountdownToDeallocate = 0;

	// Mesh
	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::ClearOverride(MeshComponent);
	MeshComponent->SetStaticMesh(nullptr);
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	// Modifiers
	DamageImpl.Modifiers.Reset(DamageImpl.Modifiers.Max());
}

#pragma endregion PooledObject

// ICsBeam
#pragma region

void ACsBeamActorPooledImpl::On()
{
}

void ACsBeamActorPooledImpl::Off()
{
	if (bOnOffDeallocate)
		Cache->QueueDeallocate();
}

UObject* ACsBeamActorPooledImpl::GetOwner() const
{
	return Cache->GetOwner();
}

UObject* ACsBeamActorPooledImpl::GetInstigator() const
{
	return Cache->GetInstigator();
}

#pragma endregion ICsBeam

// Beam
#pragma region

	// On
#pragma region

#define PayloadType NCsBeam::NPayload::IPayload

void ACsBeamActorPooledImpl::PrepareOn(PayloadType* Payload)
{
using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::PrepareOn;

	CS_IS_PTR_NULL_CHECKED(Payload)

	// Set Damage Value if the projectile supports damage
	OnPrepareOn_SetModifiers(Payload);

	SetActorHiddenInGame(false);

	typedef NCsBeam::NData::FLibrary BeamDataLibrary;

	// VisualDataType (NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh)
	{
		typedef NCsBeam::NData::NVisual::NStaticMesh::IStaticMesh VisualDataType;

		if (VisualDataType* VisualData = BeamDataLibrary::GetSafeInterfaceChecked<VisualDataType>(Context, Data))
		{
			// TODO: MAYBE? Allocate Static Mesh Actor and get Static Mesh Component

			//MeshComponent->AttachToComponent(CollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

			UStaticMesh* Mesh = VisualData->GetStaticMesh();

			CS_IS_PTR_NULL_CHECKED(Mesh)

			MeshComponent->SetStaticMesh(Mesh);
			//MeshComponent->SetWorldScale3D(VisualData->GetStaticMesh().Scale);
			MeshComponent->Activate();
			MeshComponent->SetVisibility(true);
			MeshComponent->SetHiddenInGame(false);
			MeshComponent->SetComponentTickEnabled(true);
		}
	}
	
	// TODO: Handle Attach and / or orientation
	{
		const FVector& Direction = Payload->GetDirection();
		FRotator Rotation		 = Direction.Rotation();

		TeleportTo(Payload->GetLocation(), Rotation, false, true);
	}
	// CollisionDataType (NCsBeam::NData::NCollision::ICollision)
	{
		const FString& ScopeName		   = ScopedTimer::SetCollision;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Beam;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogBeamScopedTimerPrepareOnSetCollision;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

		if (CollisionDataType* CollisionData = BeamDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data))
		{
			const FCsCollisionPreset& CollisionPreset = CollisionData->GetCollisionPreset();

			if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
			{
				typedef NCsBeam::NPayload::FLibrary BeamPayloadLibrary;
				typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

				PooledPayloadType* PooledPayload = BeamPayloadLibrary::GetInterfaceChecked<PooledPayloadType>(Context, Payload);

				// Instigator
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetInstigator()))
					AddIgnoreActor(Actor);
				// Owner
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetOwner()))
					AddIgnoreActor(Actor);
				// Parent
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetParent()))
					AddIgnoreActor(Actor);

				/*
				const int32 Count = IgnoreActors.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					AActor* Actor = IgnoreActors[I].IsValid() ? IgnoreActors[I].Get() : nullptr;

					if (!Actor)
						continue;

					CollisionComponent->MoveIgnoreActors.Add(Actor);
				}
				*/

				// TODO: FUTURE: Allow Mesh to be a colliding component?
				/*
				CollisionComponent->SetCollisionObjectType(CollisionPreset.ObjectType);
				CollisionComponent->SetSphereRadius(CollisionData->GetCollisionRadius());
				CollisionComponent->SetCollisionResponseToChannels(CollisionPreset.CollisionResponses);

				CollisionComponent->SetNotifyRigidBodyCollision(CollisionPreset.bSimulationGeneratesHitEvents);
				CollisionComponent->SetGenerateOverlapEvents(CollisionPreset.bGenerateOverlapEvents);

				CollisionComponent->Activate();
				CollisionComponent->SetComponentTickEnabled(true);

				CollisionComponent->SetCollisionEnabled(CollisionPreset.CollisionEnabled);
				*/
			}

			CollisionCountdownToDeallocate = CollisionData->GetHitCount();
		}
	}
	SetActorTickEnabled(true);
}

void ACsBeamActorPooledImpl::OnPrepareOn_SetModifiers(PayloadType* Payload)
{
	using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::OnPrepareOn_SetModifiers;

	// NCsBeam::NPayload::NModifier::NDamage::IDamage
	{
		typedef NCsBeam::NPayload::FLibrary PayloadLibrary;
		typedef NCsBeam::NPayload::NModifier::NDamage::IDamage ModDamagePayloadType;

		if (ModDamagePayloadType* DmgModifierPayload = PayloadLibrary::GetSafeInterfaceChecked<ModDamagePayloadType>(Context, Payload))
		{
			typedef NCsDamage::NManager::FLibrary DamageManagerLibrary;

			DamageManagerLibrary::CreateCopyOfModifiersChecked(Context, this, DmgModifierPayload->GetDamageModifiers(), DamageImpl.Modifiers);
		}
	}
}

#undef PayloadType

#pragma endregion On

	// Emit
#pragma region

void ACsBeamActorPooledImpl::Emit()
{

}

char ACsBeamActorPooledImpl::Emit_Internal(FCsRoutine* R)
{
	CS_COROUTINE_BEGIN(R)

	CS_COROUTINE_END(R)
}

#pragma endregion Emit

#pragma endregion Beam

// Damage
#pragma region

ACsBeamActorPooledImpl::FDamageImpl::FDamageImpl() :
	Outer(nullptr),
	Type(),
	ValuePoint(nullptr),
	ValueRange(nullptr),
	Modifiers()
{
	typedef NCsDamage::NValue::NPoint::FImpl PointType;
	typedef NCsDamage::NValue::NRange::FImpl RangeType;

	ValuePoint = new PointType();
	ValueRange = new RangeType();
}

ACsBeamActorPooledImpl::FDamageImpl::~FDamageImpl()
{
	delete ValuePoint;
	ValuePoint = nullptr;

	delete ValueRange;
	ValueRange = nullptr;

	Modifiers.Reset();
}

#define DamageDataType NCsDamage::NData::IData
void ACsBeamActorPooledImpl::FDamageImpl::SetValue(DamageDataType* InData)
{
#undef DamageDataType

	using namespace NCsBeamActorPooledImpl::NDamageImpl::NCached;

	const FString& Context = Str::SetValue;

	typedef NCsDamage::NValue::FLibrary DamageValueLibrary;
	typedef NCsDamage::NValue::IValue ValueType;

	const ValueType* Value = InData->GetValue();
	Type				   = DamageValueLibrary::GetTypeChecked(Context, Value);

	ResetValue();
	DamageValueLibrary::CopyChecked(Context, Value, GetValue());
}

#define ValueType NCsDamage::NValue::IValue
ValueType* ACsBeamActorPooledImpl::FDamageImpl::GetValue()
{
#undef ValueType

	// Point
	if (Type == NCsDamageValue::Point)
		return ValuePoint;
	// Range
	if (Type == NCsDamageValue::Range)
		return ValueRange;

	checkf(0, TEXT("ACsBeamActorPooledImpl::FDamageImpl::GetValue: No Value associated with Type: %s."), Type.ToChar());
	return nullptr;
}

void ACsBeamActorPooledImpl::FDamageImpl::ResetValue()
{
	ValuePoint->Reset();
	ValueRange->Reset();
}

void ACsBeamActorPooledImpl::FDamageImpl::Reset()
{
	ResetValue();

	Modifiers.Reset(Modifiers.Max());
}

#pragma endregion Damage