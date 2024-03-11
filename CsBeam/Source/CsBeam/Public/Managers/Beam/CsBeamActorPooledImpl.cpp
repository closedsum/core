// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/CsBeamActorPooledImpl.h"
#include "CsBeam.h"

// CVar
#include "Managers/Beam/CsCVars_Beam.h"
// Types
#include "Collision/CsTypes_Collision.h"
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
	// Data
#include "Data/CsLibrary_Data_Beam.h"
	// Payload
#include "Payload/CsLibrary_Payload_Beam.h"
#include "Managers/Pool/Payload/CsLibrary_Payload_PooledObject.h"
	// Damage
#include "Value/CsLibrary_DamageValue.h"
#include "Modifier/CsLibrary_DamageModifier.h"
	// Common
#include "Collision/CsLibrary_Collision.h"
#include "Material/CsLibrary_Material.h"
#include "Library/CsLibrary_Math.h"
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
// Trace
#include "Managers/Trace/CsTraceRequest.h"
#include "Managers/Trace/CsTraceResponse.h"
// Beam
#include "Cache/CsCache_BeamImpl.h"
#include "Payload/Damage/CsPayload_BeamModifierDamage.h"
#include "Collision/CsBeam_CollisionShape.h"
#include "CsGetBeamScale.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"
// Damage
#include "Value/Point/CsDamageValuePointImpl.h"
#include "Value/Range/CsDamageValueRangeImpl.h"
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
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, Deallocate_Internal);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, On);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, PrepareOn);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl, OnPrepareOn_SetModifiers);		
		}

		namespace Name
		{
		}

		namespace ScopedTimer
		{
			CS_DEFINE_CACHED_STRING(SetCollision, "ACsBeamActorPooledImpl::Launch_SetCollision");
			CS_DEFINE_CACHED_STRING(SetTrailVisual, "ACsBeamActorPooledImpl::Launch_SetTrailVisual");
		}
	}

	namespace NCollisionImpl
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl::FCollisionImpl, Emit);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl::FCollisionImpl, Emit_Internal);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl::FCollisionImpl, PerformPass);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ACsBeamActorPooledImpl::FCollisionImpl, Shutdown);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ACsBeamActorPooledImpl::FCollisionImpl, Emit_Internal);
			}
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
	// Shutdown
	bShutdown(false),
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
	// Collision
	CollisionImpl(),
	bDeallocateOnCollision(true),
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

	Shutdown();
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

	CollisionImpl.Outer = this;
	DamageImpl.Outer = this;
}

void ACsBeamActorPooledImpl::FellOutOfWorld(const UDamageType& DmgType)
{
	Deallocate_Internal();
	SetActorLocation(FVector3d::ZeroVector);
	Cache->QueueDeallocate();
}

void ACsBeamActorPooledImpl::OutsideWorldBounds()
{
	Deallocate_Internal();
	SetActorLocation(FVector3d::ZeroVector);
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

// ICsUpdate
#pragma region

void ACsBeamActorPooledImpl::Update(const FCsDeltaTime& DeltaTime)
{
	CacheImpl->Update(DeltaTime);
}

#pragma endregion ICsUpdate

// ICsShutdown
#pragma region

void ACsBeamActorPooledImpl::Shutdown()
{
	if (Cache)
	{
		delete Cache;
		Cache = nullptr;
		CacheImpl = nullptr;
	}
	bShutdown = true;
}

#pragma endregion ICsShutdown

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

	// Cache collision related data
	typedef NCsBeam::NData::FLibrary BeamDataLibrary;
	typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

	CollisionDataType* CollisionData = BeamDataLibrary::GetSafeInterfaceChecked<CollisionDataType>(Context, Data);

	if (CollisionData)
	{
		typedef NCsBeam::NCollision::NParams::FFrequency CollisionFrequencyParamsType;
		typedef NCsBeam::NCollision::NShape::FShape CollisionShapeType;

		CollisionImpl.FrequencyParams = const_cast<CollisionFrequencyParamsType*>(&CollisionData->GetCollisionFrequencyParams());
		CollisionImpl.Shape			  = const_cast<CollisionShapeType*>(CollisionData->GetCollisionShape());
	}
	CollisionImpl.CollisionData = CollisionData;

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

	const FString& Context = Str::Deallocate_Internal;

	// Collision
	CollisionImpl.Shutdown();

	// Mesh
	typedef NCsMaterial::FLibrary MaterialLibrary;

	MaterialLibrary::ClearOverrideChecked(Context, MeshComponent);
	MeshComponent->SetStaticMesh(nullptr);
	MeshComponent->SetVisibility(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetComponentTickEnabled(false);
	MeshComponent->Deactivate();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	// Modifiers
	DamageImpl.Modifiers.Reset(DamageImpl.Modifiers.Max());

	Data = nullptr;

	Cache->Reset();
}

#pragma endregion PooledObject

// ICsBeam
#pragma region

void ACsBeamActorPooledImpl::On()
{
	CollisionImpl.ConditionalEmit();
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
	
	typedef NCsBeam::NPayload::FLibrary BeamPayloadLibrary;
	typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;

	PooledPayloadType* PooledPayload = BeamPayloadLibrary::GetInterfaceChecked<PooledPayloadType>(Context, Payload);

	typedef NCsMath::FLibrary MathLibrary;

	// Handle Orientation
	{
		// Check Parent is set
		USceneComponent* Parent = nullptr;

		UObject* Object = PooledPayload->GetParent();

		// SceneComponent
		if (USceneComponent* Component = Cast<USceneComponent>(Object))
			Parent = Component;
		// Actor -> Get RootComponent
		else
		if (AActor* Actor = Cast<AActor>(Object))
			Parent = Actor->GetRootComponent();

		// Attach to Parent
		if (Parent)
		{
			const FCsAttachmentTransformRules Rule = FCsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			const FName Bone					   = NAME_None;

			const FVector3d Scale = GetActorScale3D();

			MeshComponent->AttachToComponent(Parent, Rule.ToRule(), Bone);
			MeshComponent->SetWorldScale3D(Scale * MathLibrary::Convert(Payload->GetScale()));
		}
		// Teleport / Set Orientation
		else
		{
			const FVector3f& Direction = Payload->GetDirection();
			FRotator3f Rotation		   = Direction.Rotation();

			TeleportTo(MathLibrary::Convert(Payload->GetLocation()), MathLibrary::Convert(Rotation), false, true);

			const FVector3d Scale = GetActorScale3D();
			SetActorScale3D(Scale * MathLibrary::Convert(Payload->GetScale()));
		}
	}
	// CollisionDataType (NCsBeam::NData::NCollision::ICollision)
	{
		// TODO: Move Into CollisionImpl

		const FString& ScopeName		   = ScopedTimer::SetCollision;
		const FECsScopedGroup& ScopedGroup = NCsScopedGroup::Beam;
		const FECsCVarLog& ScopeLog		   = NCsCVarLog::LogBeamScopedTimerPrepareOnSetCollision;

		CS_SCOPED_TIMER_ONE_SHOT(&ScopeName, ScopedGroup, ScopeLog);

		typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

		if (CollisionDataType* CollisionData = CollisionImpl.CollisionData)
		{
			const FCsCollisionPreset& CollisionPreset = CollisionData->GetCollisionPreset();

			if (CollisionPreset.CollisionEnabled != ECollisionEnabled::NoCollision)
			{
				// Instigator
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetInstigator()))
					CollisionImpl.AddIgnoreActor(Actor);
				// Owner
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetOwner()))
					CollisionImpl.AddIgnoreActor(Actor);
				// Parent
				if (AActor* Actor = Cast<AActor>(PooledPayload->GetParent()))
					CollisionImpl.AddIgnoreActor(Actor);

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

			CollisionImpl.CountdownToDeallocate = CollisionData->GetCollisionCount();
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
			typedef NCsDamage::NManager::NModifier::FLibrary DamageModifierLibrary;

			DamageModifierLibrary::CopyChecked(Context, this, DmgModifierPayload->GetDamageModifiers(), DamageImpl.Modifiers);
		}
	}
}

#undef PayloadType

#pragma endregion On

#pragma endregion Beam

// Collision
#pragma region

void ACsBeamActorPooledImpl::FCollisionImpl::AddIgnoreActor(AActor* Actor)
{
	IgnoreActors.Add(Actor);
	IgnoreActorSet.Add(Actor);
}

const AActor* ACsBeamActorPooledImpl::FCollisionImpl::GetIgnoreActor(const int32& Index)
{
	if (Index >= IgnoreActors.Num())
		return nullptr;
	return IgnoreActors[Index].IsValid() ? IgnoreActors[Index].Get() : nullptr;
}

void ACsBeamActorPooledImpl::FCollisionImpl::AddIgnoreComponent(UPrimitiveComponent* Component)
{
	IgnoreComponents.Add(Component);
	IgnoreComponentSet.Add(Component);
}

UPrimitiveComponent* ACsBeamActorPooledImpl::FCollisionImpl::GetIgnoreComponent(const int32& Index)
{
	if (Index >= IgnoreComponents.Num())
		return nullptr;
	return IgnoreComponents[Index].IsValid() ? IgnoreComponents[Index].Get() : nullptr;
}

bool ACsBeamActorPooledImpl::FCollisionImpl::IsIgnored(AActor* Actor) const
{
	if (!Actor)
		return false;

	return IgnoreActorSet.Find(Actor) != nullptr;
}

bool ACsBeamActorPooledImpl::FCollisionImpl::IsIgnored(UPrimitiveComponent* Component) const
{
	if (!Component)
		return false;

	return IgnoreComponentSet.Find(Component) != nullptr;
}

void ACsBeamActorPooledImpl::FCollisionImpl::ConditionalEmit()
{
	if (CollisionData)
		Emit();
}

void ACsBeamActorPooledImpl::FCollisionImpl::Emit()
{
	using namespace NCsBeamActorPooledImpl::NCollisionImpl::NCached;	

	const FString& Context = Str::Emit;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;
	typedef NCsCoroutine::NPayload::FImpl PayloadType;

	UCsCoroutineScheduler* Scheduler  = CoroutineSchedulerLibrary::GetChecked(Context, Outer);
	const FECsUpdateGroup& Group	  = Outer->GetUpdateGroup();
	PayloadType* Payload			  = Scheduler->AllocatePayload(Group);

	typedef NCsTime::NManager::FLibrary TimeManagerLibrary;

	#define COROUTINE Emit_Internal

	Payload->CoroutineImpl.BindRaw(this, &ACsBeamActorPooledImpl::FCollisionImpl::COROUTINE);
	Payload->StartTime = TimeManagerLibrary::GetTimeChecked(Context, Outer, Group);
	Payload->Owner.SetObject(Outer);
	Payload->SetName(Str::COROUTINE);
	Payload->SetFName(Name::COROUTINE);

	#undef COROUTINE

	static const int32 LIFETIME = 0;
	Payload->SetValue_Float(LIFETIME, Outer->GetData()->GetLifeTime());

	Scheduler->Start(Payload);
}

char ACsBeamActorPooledImpl::FCollisionImpl::Emit_Internal(FCsRoutine* R)
{
	static const int32 LIFETIME = 0;
	const float& LifeTime = R->GetValue_Float(LIFETIME);

	static const int32 CAN_EMIT = 0;
	bool& CanEmit = R->GetValue_Flag(CAN_EMIT);

	static const int32 HAS_INTERVAL = 1;
	bool& HasInterval = R->GetValue_Flag(HAS_INTERVAL);

	static const int32 SHOULD_YIELD = 2;
	bool& ShouldYield = R->GetValue_Flag(SHOULD_YIELD);

	static const int32 CURRENT_PASS_COUNT = 0;
	int32& CurrentPassCount = R->GetValue_Int(CURRENT_PASS_COUNT);

	FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
	ElapsedTime += R->DeltaTime;

	typedef NCsBeam::NCollision::EFrequency FrequencyType;

	const FrequencyType& Frequency = FrequencyParams->GetType();

	CS_COROUTINE_BEGIN(R)

	do 
	{
		{

			ElapsedTime.Reset();

			PerformPass();

			// Once
			if (Frequency == FrequencyType::Once)
			{
				CanEmit = false;
			}
			// Count | TimeCount | TimeInterval
			else
			if (Frequency == FrequencyType::Count ||
				Frequency == FrequencyType::TimeCount ||
				Frequency == FrequencyType::TimeInterval)
			{
				CanEmit		= CurrentPassCount < FrequencyParams->GetCount();
				HasInterval = CanEmit && FrequencyParams->GetInterval() > 0.0f;
			}
			// Infinite
			else
			if (Frequency == FrequencyType::Infinite)
			{
				CanEmit		= LifeTime == 0.0f || ElapsedTime.Time < LifeTime;
				HasInterval = CanEmit && FrequencyParams->GetInterval() > 0.0f;
				ShouldYield = !HasInterval;
			}

			if (HasInterval)
			{
				CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams->GetInterval());
			}
			else
			if (ShouldYield)
			{
				CS_COROUTINE_YIELD(R);
			}
		}
	} while(CanEmit);

	CS_COROUTINE_END(R)
}

void ACsBeamActorPooledImpl::FCollisionImpl::PerformPass()
{
	using namespace NCsBeamActorPooledImpl::NCollisionImpl::NCached;

	const FString& Context = Str::PerformPass;

	void(*Log)(const FString&) = NCsBeam::FLog::Warning;

	typedef NCsTrace::NManager::FLibrary TraceManagerLibrary;
	typedef NCsTrace::NRequest::FRequest RequestType;

	RequestType* Request = TraceManagerLibrary::AllocateRequestChecked(Context, Outer);

	typedef NCsMath::FLibrary MathLibrary;

	Request->Start = MathLibrary::Convert(Outer->GetActorLocation());
	
	const FVector3f Dir = MathLibrary::Convert(Outer->GetActorRotation().Vector());
	FVector3f Scale	    = FVector3f::OneVector;

	if (UObject* MyOwner = Outer->GetCache()->GetOwner())
	{
		ICsGetBeamScale* GetBeamScale = CS_INTERFACE_CAST(MyOwner, UObject, ICsGetBeamScale);
		Scale						  = GetBeamScale->GetBeamScale();
	}

	Request->Method = ECsTraceMethod::Multi;
	Request->Query = ECsTraceQuery::ObjectType;

	Request->Params.AddIgnoredActors(IgnoreActors);
	Request->Params.AddIgnoredComponents(IgnoreComponents);

	const FCsCollisionPreset& Preset = CollisionData->GetCollisionPreset();

	Request->ObjectParams.AddObjectTypesToQuery(Preset.ObjectType);
	Request->ResponseParams.CollisionResponse = Preset.CollisionResponses;

	Shape->TraceChecked(Context, Outer, Request, Dir, Scale);
}

void ACsBeamActorPooledImpl::FCollisionImpl::Shutdown()
{
	using namespace NCsBeamActorPooledImpl::NCollisionImpl::NCached;

	const FString& Context = Str::Shutdown;

	typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

	CoroutineSchedulerLibrary::SafeEnd(Outer, Outer->GetUpdateGroup(), EmitInternalHandle);

	CollisionData = nullptr;
	FrequencyParams = nullptr;
	Shape = nullptr;
	CurrentCount = 0;
	CountdownToDeallocate = 0;
	IgnoreActors.Reset(IgnoreActors.Max());
	IgnoreActorSet.Reset();
	IgnoreComponents.Reset(IgnoreComponents.Max());
	IgnoreComponentSet.Reset();
	EmitInternalHandle.Reset();
}

void ACsBeamActorPooledImpl::OnCollision(UPrimitiveComponent* CollidingComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector3d NormalImpulse, const FHitResult& Hit)
{
	using namespace NCsBeamActorPooledImpl::NCached;

	const FString& Context = Str::OnCollision;

	if (CollisionImpl.IsIgnored(OtherActor))
		return;

	if (CollisionImpl.IsIgnored(OtherComp))
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
		UE_LOG(LogCsBeam, Warning, TEXT("-- Actor: %s"), Hit.HasValidHitObjectHandle() ? *(Hit.GetActor()->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- Component: %s"), Hit.Component.IsValid() ? *(Hit.Component->GetName()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- BoneName: %s"), Hit.BoneName.IsValid() ? *(Hit.BoneName.ToString()) : TEXT("None"));
		UE_LOG(LogCsBeam, Warning, TEXT("-- FaceIndex: %d"), Hit.FaceIndex);
	}
#endif // #if !UE_BUILD_SHIPPING

	// Get Physics Surface
	EPhysicalSurface SurfaceType	= NCsHitResult::GetPhysSurfaceType(Hit);

	typedef NCsBeam::NData::FLibrary BeamDataLibrary;
	typedef NCsMath::FLibrary MathLibrary;
	typedef NCsCollision::FLibrary CollisionLibrary;

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

			FTransform3f Transform = FTransform3f::Identity;
			Transform.SetLocation(CollisionLibrary::GetLocation(Hit));
			Transform.SetRotation(CollisionLibrary::GetImpactQuat(Hit));

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

			FTransform3f Transform = FTransform3f::Identity;
			Transform.SetLocation(CollisionLibrary::GetLocation(Hit));
			Transform.SetRotation(CollisionLibrary::GetImpactQuat(Hit));

			SoundManagerLibrary::SpawnChecked(Context, this, &Payload, ImpactSound, Transform);
		}
	}
	// DamageDataType (NCsBeam::NData::NDamage::IDamage)
	{
		/*
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
		*/
	}

	// CollisionDataType (NCsBeam::NData::NCollision::ICollision)
	typedef NCsBeam::NData::NCollision::ICollision CollisionDataType;

	CollisionDataType* CollisionData = CollisionImpl.CollisionData;
	{
		if (CollisionData->IgnoreCollidingObjectAfterCollision())
		{
			// Actor
			if (OtherActor)
			{
				CollisionImpl.AddIgnoreActor(OtherActor);
			}
			// Component
			if (OtherComp)
			{
				CollisionImpl.AddIgnoreComponent(OtherComp);
			}
		}
	}

	++CollisionImpl.CurrentCount;
	--CollisionImpl.CountdownToDeallocate;

	if (bDeallocateOnCollision && CollisionImpl.CountdownToDeallocate <= 0)
		Cache->QueueDeallocate();
}

#pragma endregion Collision

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