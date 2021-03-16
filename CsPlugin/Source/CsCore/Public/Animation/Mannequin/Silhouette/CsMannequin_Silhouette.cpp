// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#include "Animation/Mannequin/Silhouette/CsMannequin_Silhouette.h"
#include "CsCore.h"

// Components
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
// Animation
#include "Animation/Mannequin/Silhouette/CsAnimInstance_Mannequin_Silhouette.h"

#if WITH_EDITOR
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Property.h"
// Containers
#include "Containers/List.h"
#endif // #if WITH_EDITOR


ACsMannequin_Silhouette::ACsMannequin_Silhouette(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	Last_AnimInstance(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
#if WITH_EDITOR
	PrimaryActorTick.bStartWithTickEnabled = true;
#else
	PrimaryActorTick.bStartWithTickEnabled = false;
#endif // #if WITH_EDITOR

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	RootComponent = SkeletalMeshComponent;

	typedef NCsAnimation::NMannequin::NSilhouette::EBone BoneType;

	BoneControlInfos.Reset((uint8)BoneType::EBone_MAX);
	BoneControlInfos.AddDefaulted((uint8)BoneType::EBone_MAX);

	#define CS_TEMP_SET_BONE(__bone) GetBoneControlInfo(BoneType::__bone).SetBone(BoneType::__bone, __bone, FName(#__bone))

	pelvis = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("pelvis")); CS_TEMP_SET_BONE(pelvis);
	thigh_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("thigh_l")); CS_TEMP_SET_BONE(thigh_l);
	thigh_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("thigh_r")); CS_TEMP_SET_BONE(thigh_r);
	calf_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("calf_l")); CS_TEMP_SET_BONE(calf_l);
	calf_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("calf_r")); CS_TEMP_SET_BONE(calf_r);
	foot_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("foot_l")); CS_TEMP_SET_BONE(foot_l);
	foot_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("foot_r")); CS_TEMP_SET_BONE(foot_r);
	spine_01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spine_01")); CS_TEMP_SET_BONE(spine_01);
	spine_02 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spine_02")); CS_TEMP_SET_BONE(spine_02);
	spine_03 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("spine_03")); CS_TEMP_SET_BONE(spine_03);
	clavicle_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("clavicle_l")); CS_TEMP_SET_BONE(clavicle_l);
	clavicle_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("clavicle_r")); CS_TEMP_SET_BONE(clavicle_r);
	upperarm_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("upperarm_l")); CS_TEMP_SET_BONE(upperarm_l);
	upperarm_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("upperarm_r")); CS_TEMP_SET_BONE(upperarm_r);
	lowerarm_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("lowerarm_l")); CS_TEMP_SET_BONE(lowerarm_l);
	lowerarm_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("lowerarm_r")); CS_TEMP_SET_BONE(lowerarm_r);
	hand_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hand_r")); CS_TEMP_SET_BONE(hand_r);
	hand_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("hand_l")); CS_TEMP_SET_BONE(hand_l);
	neck_01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("neck_01")); CS_TEMP_SET_BONE(neck_01);
	head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("head")); CS_TEMP_SET_BONE(head);

	#undef CS_TEMP_SET_BONE

	// Controls
	#define CS_TEMP_SET_CONTROL(__bone) GetBoneControlInfo(BoneType::__bone).SetControl(__bone##_ctrl)

	pelvis_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("pelvis_ctrl")); CS_TEMP_SET_CONTROL(pelvis);
	thigh_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("thigh_l_ctrl")); CS_TEMP_SET_CONTROL(thigh_l);
	thigh_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("thigh_r_ctrl")); CS_TEMP_SET_CONTROL(thigh_r);
	calf_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("calf_l_ctrl")); CS_TEMP_SET_CONTROL(calf_l);
	calf_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("calf_r_ctrl")); CS_TEMP_SET_CONTROL(calf_r);
	foot_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("foot_l_ctrl")); CS_TEMP_SET_CONTROL(foot_l);
	foot_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("foot_r_ctrl")); CS_TEMP_SET_CONTROL(foot_r);
	spine_01_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("spine_01_ctrl")); CS_TEMP_SET_CONTROL(spine_01);
	spine_02_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("spine_02_ctrl")); CS_TEMP_SET_CONTROL(spine_02);
	spine_03_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("spine_03_ctrl")); CS_TEMP_SET_CONTROL(spine_03);
	clavicle_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("clavicle_l_ctrl")); CS_TEMP_SET_CONTROL(clavicle_l);
	clavicle_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("clavicle_r_ctrl")); CS_TEMP_SET_CONTROL(clavicle_r);
	upperarm_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("upperarm_l_ctrl")); CS_TEMP_SET_CONTROL(upperarm_l);
	upperarm_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("upperarm_r_ctrl")); CS_TEMP_SET_CONTROL(upperarm_r);
	lowerarm_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("lowerarm_l_ctrl")); CS_TEMP_SET_CONTROL(lowerarm_l);
	lowerarm_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("lowerarm_r_ctrl")); CS_TEMP_SET_CONTROL(lowerarm_r);
	hand_r_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("hand_r_ctrl")); CS_TEMP_SET_CONTROL(hand_r);
	hand_l_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("hand_l_ctrl"));	CS_TEMP_SET_CONTROL(hand_l);
	neck_01_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("neck_01_ctrl")); CS_TEMP_SET_CONTROL(neck_01);
	head_ctrl = CreateDefaultSubobject<USceneComponent>(TEXT("head_ctrl"));	CS_TEMP_SET_CONTROL(head);

	#undef CS_TEMP_SET_CONTROL

	typedef NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo BoneControlInfoType;

	for (BoneControlInfoType& Info : BoneControlInfos)
	{
		Info.Bone->SetupAttachment(RootComponent, Info.BoneName);
		Info.Control->SetupAttachment(RootComponent, Info.BoneName);
	}
}

// AActor Interface
#pragma region

void ACsMannequin_Silhouette::PostInitializeComponents()
{
	Super::PostInitializeComponents();

#if WITH_EDITOR
	if (FCsLibrary_World::IsPlayInEditor(GetWorld()) ||
		FCsLibrary_World::IsPlayInEditorPreview(GetWorld()))
	{
		OnObjectModifiedHandle = FCoreUObjectDelegates::OnObjectModified.AddUObject(this, &ACsMannequin_Silhouette::OnObjectModified);

		OnDestroyed.AddDynamic(this, &ACsMannequin_Silhouette::OnDestroy);
	}
#endif // #if WITH_EDITOR
}

void ACsMannequin_Silhouette::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

#if WITH_EDITOR
	if (FCsLibrary_World::IsPlayInEditor(GetWorld()) ||
		FCsLibrary_World::IsPlayInEditorPreview(GetWorld()))
	{
		TickInEditor(DeltaSeconds);
	}
#endif // #if WITH_EDITOR
}

bool ACsMannequin_Silhouette::ShouldTickIfViewportsOnly() const
{
#if WITH_EDITOR
	if (FCsLibrary_World::IsPlayInEditor(GetWorld()) ||
		FCsLibrary_World::IsPlayInEditorPreview(GetWorld()))
	{
		return true;
	}
#endif // #if WITH_EDITOR
	return Super::ShouldTickIfViewportsOnly();
}

#pragma endregion AActor Interface

void ACsMannequin_Silhouette::OnDestroy(AActor* Actor)
{
#if WITH_EDITOR
	if (FCsLibrary_World::IsPlayInEditor(GetWorld()) ||
		FCsLibrary_World::IsPlayInEditorPreview(GetWorld()))
	{
		FCoreUObjectDelegates::OnObjectModified.Remove(OnObjectModifiedHandle);
	}
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

void ACsMannequin_Silhouette::TickInEditor(const float& DeltaSeconds)
{
	//using namespace NCCursorImpl::NCached;

	//const FString& Context = Str::TickInEditor;

	UCsAnimInstance_Mannequin_Silhouette* AnimInstance = Cast<UCsAnimInstance_Mannequin_Silhouette>(SkeletalMeshComponent->GetAnimInstance());

	if (!AnimInstance)
		return;

	if (AnimInstance != Last_AnimInstance)
	{
		SetupAttachements();

		Last_AnimInstance = AnimInstance;
	}

	ACsMannequin_Silhouette* DOb = GetClass()->GetDefaultObject<ACsMannequin_Silhouette>();

	typedef NCsAnimation::NMannequin::NSilhouette::EBoneControlApplication BoneControlApplicationType;
	typedef NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo BoneControlInfoType;
	typedef NCsAnimation::NMannequin::NSilhouette::EBone BoneType;

	// Component
	if (BoneControlApplication == BoneControlApplicationType::Component)
	{
		// Pelvis (pelvis)
		{
			BoneControlInfoType& Pelvis	= GetBoneControlInfo(BoneType::pelvis);

			PelvisControl.OnUpdateByComponent(DOb->PelvisControl, Pelvis);
		}
		// Thigh (thigh_l | thigh_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::thigh_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::thigh_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::thigh_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::thigh_r);

			ThighControl.OnUpdateByComponent(DOb->ThighControl, LeftDOb, Left, RightDOb, Right);
		}
		// Calf (calf_l | calf_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::calf_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::calf_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::calf_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::calf_r);

			CalfControl.OnUpdateByComponent(DOb->CalfControl, LeftDOb, Left, RightDOb, Right);
		}
		// Foot (foot_l | foot_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::foot_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::foot_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::foot_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::foot_r);

			FootControl.OnUpdateByComponent(DOb->FootControl, LeftDOb, Left, RightDOb, Right);
		}
		// Lower Torso (spine_01)
		{
			BoneControlInfoType& LowerTorso = GetBoneControlInfo(BoneType::spine_01);

			LowerTorsoControl.OnUpdateByComponent(DOb->LowerTorsoControl, LowerTorso);
		}
		// Upper Torso (spine_02)
		{
			BoneControlInfoType& UpperTorso = GetBoneControlInfo(BoneType::spine_02);

			UpperTorsoControl.OnUpdateByComponent(DOb->UpperTorsoControl, UpperTorso);
		}
		// Chest (spine_03)
		{
			BoneControlInfoType& Chest = GetBoneControlInfo(BoneType::spine_03);

			ChestControl.OnUpdateByComponent(DOb->ChestControl, Chest);
		}
		// Lats (clavicle_l | clavicle_r)
		{
			FTransform Transform_L = clavicle_l_ctrl->GetRelativeTransform();
			FTransform Transform_R = clavicle_r_ctrl->GetRelativeTransform();

			clavicle_l_ctrl_info.Transform = Transform_L;
			clavicle_r_ctrl_info.Transform = Transform_R;

			// Left (clavicle_l) Changed
			if (clavicle_l_ctrl_info.HasChanged())
			{
				const FVector Scale = Transform_L.GetScale3D();

				LatSize = FMath::Max3(Scale.X, Scale.Y, Scale.Z);

				Transform_L.SetScale3D(LatSize* FVector::OneVector);

				const FVector Location = Transform_L.GetLocation();

				LatHeightOffset = Location.Z;

				clavicle_l_ctrl_info.Transform = Transform_L;
				clavicle_r_ctrl_info.Transform = Transform_L;

				clavicle_l_ctrl->SetRelativeTransform(Transform_L);
				clavicle_r_ctrl->SetRelativeTransform(Transform_L);
			}
			// Right (clavicle_r) Changed
			if (clavicle_r_ctrl_info.HasChanged())
			{
				const FVector Scale = Transform_R.GetScale3D();

				LatSize = FMath::Max3(Scale.X, Scale.Y, Scale.Z);

				Transform_R.SetScale3D(LatSize* FVector::OneVector);

				const FVector Location = Transform_R.GetLocation();

				LatHeightOffset = Location.X;

				clavicle_l_ctrl_info.Transform = Transform_R;
				clavicle_r_ctrl_info.Transform = Transform_R;

				clavicle_l_ctrl->SetRelativeTransform(Transform_R);
				clavicle_r_ctrl->SetRelativeTransform(Transform_R);
			}
			clavicle_l_ctrl_info.Resolve();
			clavicle_r_ctrl_info.Resolve();
		}
		// Upper Arm (upperarm_l | upperarm_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::upperarm_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::upperarm_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::upperarm_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::upperarm_r);

			UpperarmControl.OnUpdateByComponent(DOb->UpperarmControl, LeftDOb, Left, RightDOb, Right);
		}
		// Lower Arm (lowerarm_l | lowerarm_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::lowerarm_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::lowerarm_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::lowerarm_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::lowerarm_r);

			LowerarmControl.OnUpdateByComponent(DOb->LowerarmControl, LeftDOb, Left, RightDOb, Right);
		}
		// Hand (hand_l | hand_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::hand_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::hand_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::hand_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::hand_r);

			HandControl.OnUpdateByComponent(DOb->HandControl, LeftDOb, Left, RightDOb, Right);
		}
		// Neck (neck_01)
		{
			
		}
		// Head (head)
		{
			BoneControlInfoType& Head = GetBoneControlInfo(BoneType::head);

			HeadControl.OnUpdateByComponent(DOb->HeadControl, Head);
		}
	}
	// Member
	else
	if (BoneControlApplication == BoneControlApplicationType::Member)
	{
		// Pelvis (pelvis)
		{
			BoneControlInfoType& PelvisDOb = DOb->GetBoneControlInfo(BoneType::pelvis);
			BoneControlInfoType& Pelvis	   = GetBoneControlInfo(BoneType::pelvis);
			
			PelvisControl.OnUpdateByMember(PelvisDOb, Pelvis);
		}
		// Thigh (thigh_l | thigh_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::thigh_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::thigh_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::thigh_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::thigh_r);

			ThighControl.OnUpdateByMember(LeftDOb, Left, RightDOb, Right);
		}
		// Calf (calf_l | calf_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::calf_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::calf_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::calf_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::calf_r);

			CalfControl.OnUpdateByMember(LeftDOb, Left, RightDOb, Right);
		}
		// Foot (foot_l | foot_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::foot_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::foot_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::foot_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::foot_r);

			FootControl.OnUpdateByMember(LeftDOb, Left, RightDOb, Right);
		}
		// Lower Torso (spine_01)
		{
			BoneControlInfoType& LowerTorsoDOb = DOb->GetBoneControlInfo(BoneType::spine_01);
			BoneControlInfoType& LowerTorso    = GetBoneControlInfo(BoneType::spine_01);

			LowerTorsoControl.OnUpdateByMember(LowerTorsoDOb, LowerTorso);
		}
		// Upper Torso (spine_02)
		{
			BoneControlInfoType& UpperTorsoDOb = DOb->GetBoneControlInfo(BoneType::spine_02);
			BoneControlInfoType& UpperTorso    = GetBoneControlInfo(BoneType::spine_02);

			UpperTorsoControl.OnUpdateByMember(UpperTorsoDOb, UpperTorso);
		}
		// Chest (spine_03)
		{
			BoneControlInfoType& ChestDOb = DOb->GetBoneControlInfo(BoneType::spine_03);
			BoneControlInfoType& Chest	  = GetBoneControlInfo(BoneType::spine_03);

			ChestControl.OnUpdateByMember(ChestDOb, Chest);
		}
		// Lats (clavicle_l | clavicle_r)
		{
			const FVector Scale = LatSize * FVector::OneVector;

			clavicle_l_ctrl->SetRelativeScale3D(Scale);
			clavicle_r_ctrl->SetRelativeScale3D(Scale);

			FVector Location = FVector::ZeroVector;

			Location.Z = LatHeightOffset;

			clavicle_l_ctrl->SetRelativeLocation(Location);
			clavicle_r_ctrl->SetRelativeLocation(Location);

			clavicle_l_ctrl_info.Transform = clavicle_l_ctrl->GetRelativeTransform();
			clavicle_r_ctrl_info.Transform = clavicle_r_ctrl->GetRelativeTransform();

			clavicle_l_ctrl_info.Resolve();
			clavicle_r_ctrl_info.Resolve();
		}
		// Upper Arm (upperarm_l | upperarm_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::upperarm_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::upperarm_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::upperarm_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::upperarm_r);

			UpperarmControl.OnUpdateByMember(LeftDOb, Left, RightDOb, Right);
		}
		// Lower Arm (lowerarm_l | lowerarm_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::lowerarm_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::lowerarm_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::lowerarm_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::lowerarm_r);

			LowerarmControl.OnUpdateByMember(LeftDOb, Left, RightDOb, Right);
		}
		// Hand (hand_l | hand_r)
		{
			BoneControlInfoType& LeftDOb  = DOb->GetBoneControlInfo(BoneType::hand_l);
			BoneControlInfoType& Left	  = GetBoneControlInfo(BoneType::hand_l);
			BoneControlInfoType& RightDOb = DOb->GetBoneControlInfo(BoneType::hand_r);
			BoneControlInfoType& Right	  = GetBoneControlInfo(BoneType::hand_r);

			HandControl.OnUpdateByMember(LeftDOb, Left, RightDOb, Right);
		}
		// Neck (neck_01)
		{

		}
		// Head (head)
		{
			BoneControlInfoType& HeadDOb = DOb->GetBoneControlInfo(BoneType::head);
			BoneControlInfoType& Head	   = GetBoneControlInfo(BoneType::head);
			
			HeadControl.OnUpdateByMember(HeadDOb, Head);
		}
	}
}

#endif // #if WITH_EDITOR

void ACsMannequin_Silhouette::SetupAttachements()
{
	const FAttachmentTransformRules& Rules = FAttachmentTransformRules::SnapToTargetIncludingScale;

	typedef NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo BoneControlInfoType;

	for (BoneControlInfoType& Info : BoneControlInfos)
	{
		{
			UStaticMeshComponent* Bone = Info.Bone;

			FTransform Transform = Bone->GetAttachParent() ? Bone->GetRelativeTransform() : Bone->GetComponentTransform();
			Bone->AttachToComponent(RootComponent, Rules, Info.BoneName);
			Bone->SetRelativeTransform(Transform);
		}
		{
			USceneComponent* Control = Info.Control;

			FTransform Transform = Control->GetAttachParent() ? Control->GetRelativeTransform() : Control->GetComponentTransform();
			Control->AttachToComponent(RootComponent, Rules, Info.BoneName);
			Control->SetRelativeTransform(Transform);
		}
	}
}

#if WITH_EDITOR

void ACsMannequin_Silhouette::PreEditChange(FEditPropertyChain& e)
{
	TSet<FString> PropertyNames;

	for (FProperty* N : e)
	{
		PropertyNames.Add(N->GetFName().ToString());
	}

	// "Lock" BoneControlApplication value
	ACsMannequin_Silhouette* DOb = GetClass()->GetDefaultObject<ACsMannequin_Silhouette>();

	bBoneControlApplication		 = true;
	DOb->bBoneControlApplication = true;

	typedef NCsAnimation::NMannequin::NSilhouette::EBoneControlApplication BoneControlApplicationType;

	#define CS_TEMP_CHECK_IS_MODIFIED(__ctrl) \
		if (__ctrl.IsModified(#__ctrl, PropertyNames)) \
		{ \
			DOb->BoneControlApplication = BoneControlApplicationType::Member; \
			BoneControlApplication		= BoneControlApplicationType::Member; \
		}

	CS_TEMP_CHECK_IS_MODIFIED(PelvisControl)
	CS_TEMP_CHECK_IS_MODIFIED(ThighControl)
	CS_TEMP_CHECK_IS_MODIFIED(CalfControl)
	CS_TEMP_CHECK_IS_MODIFIED(FootControl)
	CS_TEMP_CHECK_IS_MODIFIED(LowerTorsoControl)
	CS_TEMP_CHECK_IS_MODIFIED(UpperTorsoControl)
	CS_TEMP_CHECK_IS_MODIFIED(ChestControl)
	CS_TEMP_CHECK_IS_MODIFIED(UpperarmControl)
	CS_TEMP_CHECK_IS_MODIFIED(LowerarmControl)
	CS_TEMP_CHECK_IS_MODIFIED(HandControl)
	CS_TEMP_CHECK_IS_MODIFIED(HeadControl)

	#undef CS_TEMP_CHECK_IS_MODIFIED

	UObject::PreEditChange(e);
}

void ACsMannequin_Silhouette::PostEditChangeChainProperty(FPropertyChangedChainEvent& e)
{
	const FName PropertyName	   = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	const FName MemberPropertyName = (e.MemberProperty != NULL) ? e.MemberProperty->GetFName() : NAME_None;

	//int32 Index;

	typedef NCsProperty::FLibrary PropertyLibrary;

	TSet<FString> PropertyNames;
	PropertyLibrary::GetPropertyNamesInChain(e, PropertyNames);

	ACsMannequin_Silhouette* DOb = GetClass()->GetDefaultObject<ACsMannequin_Silhouette>();

	typedef NCsAnimation::NMannequin::NSilhouette::EBoneControlApplication BoneControlApplicationType;

	#define CS_TEMP_CHECK_IS_MODIFIED(__ctrl) \
		if (__ctrl.IsModified(#__ctrl, PropertyNames)) \
		{ \
			DOb->BoneControlApplication = BoneControlApplicationType::Member; \
			BoneControlApplication		= BoneControlApplicationType::Member; \
		}

	CS_TEMP_CHECK_IS_MODIFIED(PelvisControl)
	CS_TEMP_CHECK_IS_MODIFIED(ThighControl)
	CS_TEMP_CHECK_IS_MODIFIED(CalfControl)
	CS_TEMP_CHECK_IS_MODIFIED(FootControl)
	CS_TEMP_CHECK_IS_MODIFIED(LowerTorsoControl)
	CS_TEMP_CHECK_IS_MODIFIED(UpperTorsoControl)
	CS_TEMP_CHECK_IS_MODIFIED(ChestControl)
	CS_TEMP_CHECK_IS_MODIFIED(UpperarmControl)
	CS_TEMP_CHECK_IS_MODIFIED(LowerarmControl)
	CS_TEMP_CHECK_IS_MODIFIED(HandControl)
	CS_TEMP_CHECK_IS_MODIFIED(HeadControl)

	#undef CS_TEMP_CHECK_IS_MODIFIED

	Super::PostEditChangeChainProperty(e);

	// "Unlock" BoneControlApplication value
	bBoneControlApplication		 = false;
	DOb->bBoneControlApplication = false;
}

void ACsMannequin_Silhouette::OnObjectModified(UObject* Object)
{
	typedef NCsAnimation::NMannequin::NSilhouette::EBoneControlApplication BoneControlApplicationType;

	if (BoneControlApplication == BoneControlApplicationType::Component)
		return;

	if (bBoneControlApplication)
		return;

	typedef NCsAnimation::NMannequin::NSilhouette::FBoneControlInfo BoneControlInfoType;
	typedef NCsAnimation::NMannequin::NSilhouette::EBone BoneType;

	for (BoneControlInfoType& Info : BoneControlInfos)
	{
		if (Object == Info.Control)
		{
			ACsMannequin_Silhouette* DOb = GetClass()->GetDefaultObject<ACsMannequin_Silhouette>();

			DOb->BoneControlApplication = BoneControlApplicationType::Component;
			BoneControlApplication		= BoneControlApplicationType::Component;
			
			Info.OnModify(DOb->GetBoneControlInfo(Info.Type));
			break;
		}
	}
}

#endif // #if WITH_EDITOR