// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Movement.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Math.h"
#include "Actor/CsLibrary_Actor.h"
// Curve
#include "Curves/CurveFloat.h"
// Components
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Mover
#pragma region

namespace NCsMover
{
	namespace Ref
	{
		typedef EMCsMover EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Component);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsMover_MAX, "MAX");
	}
}

namespace NCsMovement
{
	namespace NMover
	{
		namespace Ref
		{
			typedef EMMover EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Component);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMover_MAX, "MAX");
		}
	}
}

#pragma endregion Mover

// MoveDestination
#pragma region

namespace NCsMoveDestination
{
	namespace Ref
	{
		typedef EMCsMoveDestination EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Location);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Component);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Bone);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsMoveDestination_MAX, "MAX");
	}
}

namespace NCsMovement
{
	namespace NDestination
	{
		namespace Ref
		{
			typedef EMDestination EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Location);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Actor);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Component);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Bone);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDestination_MAX, "MAX");
		}
	}
}

#pragma endregion MoveDestination

// FCsMoveByInterp_Params
#pragma region

#define ParamsType NCsMovement::NTo::NInterp::NParams::FParams

void FCsMoveByInterp_Params::CopyParams(ParamsType* Params)
{
	typedef NCsMovement::EMover MoverType;
	typedef NCsMovement::EDestination DestinationType;

	Params->SetEasing(&Easing);
	Params->SetMover(&((MoverType)Mover));
	Params->SetFromLocation(&FromLocation);
	Params->SetMoveObjectName(&MoveObjectName);
	Params->SetMoveActorLabel(&MoveActorLabel);
	Params->SetMoveActor(MoveActor);
	Params->SetMoveComponent(MoveComponent);
	Params->SetDestination(&((DestinationType)Destination));
	Params->SetToLocation(&ToLocation);
	Params->SetToObjectName(&ToObjectName);
	Params->SetToActorLabel(&ToActorLabel);
	Params->SetToBone(&ToBone);
	Params->SetToActor(ToActor);
	Params->SetToComponent(ToComponent);
	Params->SetToMeshComponent(ToMeshComponent);
	Params->SetTime(&Time);
	Params->SetGroup(&Group);
}

void FCsMoveByInterp_Params::CopyParamsAsValue(ParamsType* Params) const
{
	typedef NCsMovement::EMover MoverType;
	typedef NCsMovement::EDestination DestinationType;

	Params->SetEasing(Easing);
	Params->SetMover((MoverType)Mover);
	Params->SetFromLocation(FromLocation);
	Params->SetMoveObjectName(MoveObjectName);
	Params->SetMoveActorLabel(MoveActorLabel);
	Params->SetMoveActor(MoveActor);
	Params->SetMoveComponent(MoveComponent);
	Params->SetDestination((DestinationType)Destination);
	Params->SetToLocation(ToLocation);
	Params->SetToObjectName(ToObjectName);
	Params->SetToActorLabel(ToActorLabel);
	Params->SetToBone(ToBone);
	Params->SetToActor(ToActor);
	Params->SetToComponent(ToComponent);
	Params->SetToMeshComponent(ToMeshComponent);
	Params->SetTime(Time);
	Params->SetGroup(Group);
}

#undef ParamsType

void FCsMoveByInterp_Params::ConditionalSetSafeMoveObject(const FString& Context, UObject* WorldContext)
{
	// Actor
	if (Mover == ECsMover::Actor)
	{
		if (MoveActor)
		{
			// Do Nothing, Move Actor already set.
			return;
		}
		else
		{
			typedef NCsActor::FLibrary ActorLibrary;

#if WITH_EDITOR
			// Label
			if (!MoveActorLabel.IsEmpty())
			{
				MoveActor = ActorLibrary::GetByLabelChecked(Context, WorldContext, MoveActorLabel);
				return;
			}
			// Name
			if (MoveObjectName != NAME_None)
			{
				MoveActor = ActorLibrary::GetByNameChecked(Context, WorldContext, MoveObjectName);
				return;
			}

			UE_LOG(LogCs, Warning, TEXT("%s: Failed to set MoveActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
#else
			// Name
			if (MoveObjectName != NAME_None)
			{
				MoveActor = ActorLibrary::GetByNameChecked(Context, WorldContext, MoveObjectName);
				return;
			}

			UE_LOG(LogCs, Warning, TEXT("%s: Failed to set MoveActor. Name: None is NOT Valid."), *Context);
#endif // #if WITH_EDITOR
		}
	}
	// Component
	else
	if (Mover == ECsMover::Component)
	{
		if (MoveComponent)
		{
			// Do Nothing, Move Component already set.
			return;
		}
	}
}

void FCsMoveByInterp_Params::ConditionalSetSafeDestinationObject(const FString& Context, UObject* WorldContext)
{
	// Actor
	if (Destination == ECsMoveDestination::Actor)
	{
		if (ToActor)
		{
			// Do Nothing, Move Actor already set.
			return;
		}
		else
		{
			typedef NCsActor::FLibrary ActorLibrary;

#if WITH_EDITOR
			// Label
			if (!ToActorLabel.IsEmpty())
			{
				ToActor = ActorLibrary::GetByLabelChecked(Context, WorldContext, ToActorLabel);
				return;
			}
			// Name
			if (ToObjectName != NAME_None)
			{
				ToActor = ActorLibrary::GetByNameChecked(Context, WorldContext, ToObjectName);
				return;
			}

			UE_LOG(LogCs, Warning, TEXT("%s: Failed to set ToActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
#else
			// Name
			if (ToObjectName != NAME_None)
			{
				MoveActor = ActorLibrary::GetByNameChecked(Context, WorldContext, ToObjectName);
				return;
			}

			UE_LOG(LogCs, Warning, TEXT("%s: Failed to set ToActor. Name: None is NOT Valid."), *Context);
#endif // #if WITH_EDITOR
		}
	}
	// Component
	else
	if (Destination == ECsMoveDestination::Component)
	{
		if (ToComponent ||
			ToMeshComponent)
		{
			if (!ToComponent && ToMeshComponent)
				ToComponent = ToMeshComponent;
			return;
		}
		else
		{
		}
	}
	// Bone
	else
	if (Destination == ECsMoveDestination::Bone)
	{
		if (ToMeshComponent)
		{
			if (ToBone == NAME_None)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: ToBone: None is NOT Valid."), *Context);
				return;
			}

			const int32 BoneIndex = ToMeshComponent->GetBoneIndex(ToBone);

			if (BoneIndex == INDEX_NONE)
			{
				UE_LOG(LogCs, Warning, TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(ToMeshComponent->GetName()), *(ToBone.ToString()));
				return;
			}
		}
	}
}

bool FCsMoveByInterp_Params::IsValid(const FString& Context) const
{
	// Check Easing is Valid
	if (!EMCsEasingType::Get().IsValidEnum(Easing))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Easing: %s is NOT Valid."), *Context, EMCsEasingType::Get().ToChar(Easing));
		return false;
	}
	// Check Move Object is Valid
	if (!EMCsMover::Get().IsValidEnum(Mover))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Mover: %s is NOT Valid."), *Context, EMCsMover::Get().ToChar(Mover));
		return false;
	}

	if (Mover == ECsMover::Actor)
	{
		if (!MoveActor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: No MoveActor set."), *Context);
			return false;
		}
	}
	else
	if (Mover == ECsMover::Component)
	{
		if (!MoveComponent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: No MoveComponent set."), *Context);
			return false;
		}
	}
	// Check Destination is Valid
	if (!EMCsMoveDestination::Get().IsValidEnum(Destination))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Destination: %s is NOT Valid."), *Context, EMCsMoveDestination::Get().ToChar(Destination));
		return false;
	}

	if (Destination == ECsMoveDestination::Actor)
	{
		if (!ToActor)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: No ToActor set."), *Context);
			return false;
		}
	}
	else
	if (Destination == ECsMoveDestination::Component)
	{
		if (!ToComponent &&
			!ToMeshComponent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: No ToComponent && ToMeshComponent are NOT set."), *Context);
			return false;
		}
	}
	else
	if (Destination == ECsMoveDestination::Bone)
	{
		if (!ToMeshComponent)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: ToMeshComponent is NOT set."), *Context);
			return false;
		}

		if (ToBone == NAME_None)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: ToBone: None is NOT Valid."), *Context);
			return false;
		}

		const int32 BoneIndex = ToMeshComponent->GetBoneIndex(ToBone);

		if (BoneIndex == INDEX_NONE)
		{
			UE_LOG(LogCs, Warning, TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(ToMeshComponent->GetName()), *(ToBone.ToString()));
			return false;
		}
	}
	// Check Time is Valid
	if (Time < 0.0f)
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Time: %f is NOT >= 0.0f."), *Context, Time);
		return false;
	}
	// Check Group is Valid
	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar());
		return false;
	}
	return true;
}

namespace NCsMovement
{
	namespace NTo
	{
		namespace NInterp
		{
			namespace NParams
			{
				#define MoverType NCsMovement::EMover
				#define DestinationType NCsMovement::EDestination

				AActor* FParams::GetMoveActor() const { return MoveActor.IsValid() ? MoveActor.Get() : nullptr; }

				USceneComponent* FParams::GetMoveComponent() const { return MoveComponent.IsValid() ? MoveComponent.Get() : nullptr; }

				AActor* FParams::GetToActor() const { return ToActor.IsValid() ? ToActor.Get() : nullptr; }

				USceneComponent* FParams::GetToComponent() const { return ToComponent.IsValid() ? ToComponent.Get() : nullptr; }

				USkeletalMeshComponent* FParams::GetToMeshComponent() const { return ToMeshComponent.IsValid() ? ToMeshComponent.Get() : nullptr; }

				void FParams::ConditionalSetMoveObjectChecked(const FString& Context, UObject* WorldContext)
				{
					// Check Mover is Valid
					typedef NCsMovement::EMMover MoverMapType;

					check(MoverMapType::Get().IsValidEnumChecked(Context, GetMover()));
					// Actor
					if (GetMover() == MoverType::Actor)
					{
						if (AActor* A = GetMoveActor())
						{
							// Do Nothing, Move Actor already set.
							return;
						}
						else
						{
							typedef NCsActor::FLibrary ActorLibrary;

				#if WITH_EDITOR
							// Label
							if (!GetMoveActorLabel().IsEmpty())
							{
								MoveActor = ActorLibrary::GetByLabelChecked(Context, WorldContext, GetMoveActorLabel());
								return;
							}
							// Name
							if (GetMoveObjectName() != NAME_None)
							{
								MoveActor = ActorLibrary::GetByNameChecked(Context, WorldContext, GetMoveObjectName());
								return;
							}

							checkf(0, TEXT("%s: Failed to set MoveActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
				#else
							// Name
							if (GetMoveObjectName() != NAME_None)
							{
								MoveActor = ActorLibrary::GetByNameChecked(Context, WorldContext, GetMoveObjectName());
								return;
							}

							checkf(0, TEXT("%s: Failed to set MoveActor. Name: None is NOT Valid."), *Context);
				#endif // #if WITH_EDITOR
						}
					}
					// Component
					else
					if (GetMover() == MoverType::Component)
					{
						if (USceneComponent* C = GetMoveComponent())
						{
							// Do Nothing, Move Component already set.
							return;
						}
					}
				}

				void FParams::ConditionalSetDestinationObjectChecked(const FString& Context, UObject* WorldContext)
				{
					// Check Destination is Valid
					typedef NCsMovement::EMDestination DestinationMapType;

					check(DestinationMapType::Get().IsValidEnumChecked(Context, GetDestination()));
					// Actor
					if (GetDestination() == DestinationType::Actor)
					{
						if (AActor* A = GetToActor())
						{
							// Do Nothing, To Actor already set.
							return;
						}
						else
						{
							typedef NCsActor::FLibrary ActorLibrary;

				#if WITH_EDITOR
							// Label
							if (!GetToActorLabel().IsEmpty())
							{
								ToActor = ActorLibrary::GetByLabelChecked(Context, WorldContext, GetToActorLabel());
								return;
							}
							// Name
							if (GetToObjectName() != NAME_None)
							{
								ToActor = ActorLibrary::GetByNameChecked(Context, WorldContext, GetToObjectName());
								return;
							}

							checkf(0, TEXT("%s: Failed to set ToActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
				#else
							// Name
							if (GetToObjectName() != NAME_None)
							{
								ToActor = ActorLibrary::GetByNameChecked(Context, WorldContext, GetToObjectName());
								return;
							}

							checkf(0, TEXT("%s: Failed to set ToActor. Name: None is NOT Valid."), *Context);
				#endif // #if WITH_EDITOR
						}
					}
					// Component
					else
					if (GetDestination() == DestinationType::Component)
					{
						if (USceneComponent* C = GetToComponent())
						{
							// Do Nothing, To Component already set.
							return;
						}
					}
				}

				bool FParams::IsValidChecked(const FString& Context) const
				{
					// Check Easing is Valid
					EMCsEasingType::Get().IsValidEnumChecked(Context, GetEasing());
					// Check Mover is Valid
					typedef NCsMovement::EMMover MoverMapType;

					check(MoverMapType::Get().IsValidEnumChecked(Context, GetMover()));
					// Check Move Object is Valid
					if (GetMover() == MoverType::Actor)
					{
						checkf(GetMoveActor(), TEXT("%s: No MoveActor set."), *Context);
					}
					else
					if (GetMover() == MoverType::Component)
					{
						checkf(GetMoveComponent(), TEXT("%s: No MoveComponent set."), *Context);
					}
					// Check Destination is Valid
					typedef NCsMovement::EMDestination DestinationMapType;

					check(DestinationMapType::Get().IsValidEnumChecked(Context, GetDestination()));
					
					if (GetDestination() == DestinationType::Actor)
					{
						checkf(GetToActor(), TEXT("%s: No ToActor set."), *Context);
					}
					else
					if (GetDestination() == DestinationType::Component)
					{
						checkf(!GetToComponent() && !GetToMeshComponent(), TEXT("%s: No ToComponent && ToMeshComponent are NOT set."), *Context);
					}
					else
					if (GetDestination() == DestinationType::Bone)
					{
						checkf(!GetToMeshComponent(), TEXT("%s: ToMeshComponent is NOT set."), *Context);

						checkf(GetToBone() != NAME_None, TEXT("%s: ToBone: None is NOT Valid."), *Context);

						const int32 BoneIndex = GetToMeshComponent()->GetBoneIndex(ToBone);

						checkf(BoneIndex != INDEX_NONE, TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(GetToMeshComponent()->GetName()), *(GetToBone().ToString()));
					}
					// Check Time is Valid
					checkf(GetTime() >= 0.0f, TEXT("%s: Time: %f is NOT >= 0.0f."), *Context, GetTime());
					// Check Group is Valid
					EMCsUpdateGroup::Get().IsValidEnumChecked(Context, GetGroup());
					return true;
				}

				bool FParams::IsValid(const FString& Context) const
				{
					// Check Easing is Valid
					if (!EMCsEasingType::Get().IsValidEnum(GetEasing()))
					{
						UE_LOG(LogCs, Warning, TEXT("%s: GetEasing(): %s is NOT Valid."), *Context, EMCsEasingType::Get().ToChar(GetEasing()));
						return false;
					}
					// Check Mover is Valid
					typedef NCsMovement::EMMover MoverMapType;

					if (!MoverMapType::Get().IsValidEnum(GetMover()))
					{
						UE_LOG(LogCs, Warning, TEXT("%s: GetMover(): %s is NOT Valid."), *Context, MoverMapType::Get().ToChar(GetMover()));
						return false;
					}
					// Check Move Object is Valid
					if (GetMover() == MoverType::Actor)
					{
						if (!GetMoveActor())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: No MoveActor set."), *Context);
							return false;
						}
					}
					else
					if (GetMover() == MoverType::Component)
					{
						if (!GetMoveComponent())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: No MoveComponent set."), *Context);
							return false;
						}
					}
					// Check Destination is Valid
					typedef NCsMovement::EMDestination DestinationMapType;

					if (!DestinationMapType::Get().IsValidEnum(GetDestination()))
					{
						UE_LOG(LogCs, Warning, TEXT("%s: GetDestination(): %s is NOT Valid."), *Context, DestinationMapType::Get().ToChar(GetDestination()));
						return false;
					}
					
					if (GetDestination() == DestinationType::Actor)
					{
						if (!GetToActor())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: No ToActor set."), *Context);
							return false;
						}
					}
					else
					if (GetDestination() == DestinationType::Component)
					{
						if (!GetToComponent() && 
							!GetToMeshComponent())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: No ToComponent && ToMeshComponent are NOT set."), *Context);
							return false;
						}
					}
					else
					if (GetDestination() == DestinationType::Bone)
					{
						if (!GetToMeshComponent())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: ToMeshComponent is NOT set."), *Context);
							return false;
						}

						if (GetToBone() == NAME_None)
						{
							UE_LOG(LogCs, Warning, TEXT("%s: ToBone: None is NOT Valid."), *Context);
							return false;
						}

						const int32 BoneIndex = GetToMeshComponent()->GetBoneIndex(ToBone);

						if (BoneIndex == INDEX_NONE)
						{
							UE_LOG(LogCs, Warning, TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(GetToMeshComponent()->GetName()), *(GetToBone().ToString()));
							return false;
						}
					}
					// Check Time is Valid
					if (GetTime() < 0.0f)
					{
						UE_LOG(LogCs, Warning, TEXT("%s: GetTime(): %f is NOT >= 0.0f."), *Context, GetTime());
						return false;
					}
					// Check Group is Valid
					if (!EMCsUpdateGroup::Get().IsValidEnum(GetGroup()))
					{
						UE_LOG(LogCs, Warning, TEXT("%s: GetGroup(): %s is NOT Valid."), *Context, GetGroup().ToChar());
						return false;
					}
					return true;
				}

				FVector FParams::GetEndLocation() const
				{
					// TODO: Need to do Relative Location (i.e. check MoveSpace: World or Relative)
					
					// Location
					if (GetDestination() == DestinationType::Location)
						return GetToLocation();
					// Actor
					if (GetDestination() == DestinationType::Actor)
						return GetToActor()->GetActorLocation();
					// Component
					if (GetDestination() == DestinationType::Component)
						return GetToComponent()->GetComponentLocation();
					// Bone
					if (GetDestination() == DestinationType::Bone)
						return GetToMeshComponent()->GetBoneLocation(GetToBone());

					typedef NCsMovement::EMDestination DestinationMapType;

					checkf(0, TEXT("NCsMovement::NTo::NInterp::NParams::FParams::GetEndLocation: GetDestination(): %s is NOT Valid."), DestinationMapType::Get().ToChar(GetDestination()));
					return FVector::ZeroVector;
				}

				void FParams::Reset()
				{

				}

				#undef MoverType
				#undef DestinationType
			}
		}
	}
}

#pragma endregion FCsMoveByInterp_Params

// SpeedFormat
#pragma region

namespace NCsSpeedFormat
{
	namespace Ref
	{
		typedef EMCsSpeedFormat EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(UUpS, "Unreal Units per Second");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MpH, "Miles per Hour");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KpH, "Kilometers per Hour");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedFormat_MAX, "MAX");
	}
}

namespace NCsSpeed
{
	namespace NFormat
	{
		typedef EMFormat EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(UUpS, "Unreal Units per Second");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(MpH, "Miles per Hour");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KpH, "Kilometers per Hour");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFormat_MAX, "MAX");
	}
}

#pragma endregion SpeedFormat

// FCsSpeed
#pragma region

#if WITH_EDITOR

void FCsSpeed::OnPostEditChange(const FName& PropertyName)
{
	// UUpS
	if (PropertyName == FName("UUpS"))
		FromUUpS();
	// MpH
	else
	if (PropertyName == FName("MpH"))
		FromMpH();
	// KpH
	else
	if (PropertyName == FName("KpH"))
		FromKpH();
}

#endif // #if WITH_EDITOR

#pragma endregion FCsSpeed

// FCsAcceleration
#pragma region

#if WITH_EDITOR

void FCsAcceleration::OnPostEditChange(const FName& PropertyName)
{
	// UUpSS
	if (PropertyName == FName("UUpSS"))
		FromUUpSS();
	// MpHS
	else
	if (PropertyName == FName("MpHS"))
		FromMpHS();
	// KpHS
	else
	if (PropertyName == FName("KpHS"))
		FromKpHS();
}

#endif // #if WITH_EDITOR

#pragma endregion FCsAcceleration

// SpeedInterpMethod
#pragma region

namespace NCsSpeedInterpMethod
{
	namespace Ref
	{
		typedef EMCsSpeedInterpMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Acceleration);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Easing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Curve);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedInterpMethod_MAX, "MAX");
	}
}

namespace NCsSpeed
{
	namespace NInterp
	{
		namespace NMethod
		{
			typedef EMMethod EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Acceleration);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Easing);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Curve);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
		}
	}
}

#pragma endregion SpeedInterpMethod

// SpeedInterpDirection
#pragma region

namespace NCsSpeedInterpDirection
{
	namespace Ref
	{
		typedef EMCsSpeedInterpDirection EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Increasing);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Decreasing);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedInterpDirection_MAX, "MAX");
	}
}

namespace NCsSpeed
{
	namespace NInterp
	{
		namespace NDirection
		{
			typedef EMDirection EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(Increasing);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Decreasing);
			CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
		}
	}
}

#pragma endregion SpeedInterpDirection

// FCsSpeedInterpInfo
#pragma region

bool FCsSpeedInterpInfo::IsValidChecked() const
{
	return true;
}

#define InfoType NCsSpeed::NInterp::FInfo
void FCsSpeedInterpInfo::SetInfo(InfoType* Info)
{
#undef InfoType

	typedef NCsSpeed::NInterp::EMethod MethodType;

	Info->SetMethod((MethodType*)(&Method));

	typedef NCsSpeed::NInterp::EDirection DirectionType;

	Info->SetDirection((DirectionType*)(&Direction));
	Info->SetEasing(&Easing);
	Info->SetCurve(&Curve);
	Info->SetTime(&Time);
	Info->SetAcceleration(&Acceleration);
}

FString FCsSpeedInterpInfo::PrintSummary(const int32& IndentSpaces /*=0*/)
{
	FString Spaces = TEXT("");

	int32 Count = 0;

	while (Count < IndentSpaces)
	{
		Spaces += TEXT(" ");
		++Count;
	}

	FString Summary;
	// Method

		// Acceleration
	if (Method == ECsSpeedInterpMethod::Acceleration)
	{
		Summary += FString::Printf(TEXT("%sMethod: %s"), *Spaces, EMCsSpeedInterpMethod::Get().ToChar(Method));
	}
		// Easing
	else
	if (Method == ECsSpeedInterpMethod::Easing)
	{
		Summary += FString::Printf(TEXT("%sMethod: %s - %s"), *Spaces, EMCsSpeedInterpMethod::Get().ToChar(Method), EMCsEasingType::Get().ToChar(Easing));
	}
		// Curve
	else
	if (Method == ECsSpeedInterpMethod::Curve)
	{
		FString Path = TEXT("None");

		if (Curve)
		{
			TSoftObjectPtr<UCurveFloat> SoftObject = TSoftObjectPtr<UCurveFloat>(Curve);
			Path								   = SoftObject.ToSoftObjectPath().ToString();
		}

		Summary += FString::Printf(TEXT("%sCurve: %s - %s"), *Spaces, EMCsSpeedInterpMethod::Get().ToChar(Method), *Path);
	}

	Summary += TEXT("\n");
	// Direction
	Summary += FString::Printf(TEXT("%sDirection: %s"), *Spaces, EMCsSpeedInterpDirection::Get().ToChar(Direction));
	Summary += TEXT("\n");
	// Time
	Summary += FString::Printf(TEXT("%sTime: %f"), *Spaces, Time);
	Summary += TEXT("\n");
	// Acceleration
	Summary += FString::Printf(TEXT("%sAcceleration: %s"), *Spaces, *(Acceleration.ToString()));

	return Summary;
}

#if WITH_EDITOR

void FCsSpeedInterpInfo::OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName)
{
	// Acceleration
	if (PropertyNames.Find(TEXT("Acceleration")))
		Acceleration.OnPostEditChange(PropertyName);
}

#endif // #if WITH_EDITOR

#pragma endregion FCsSpeedInterpInfo

// NCsSpeed::NInterp::FInterp
#pragma region

namespace NCsSpeed
{
	namespace NInterp
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpeed::NInterp::FInterp, SetMaxSpeed);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpeed::NInterp::FInterp, SetPercentOfMaxSpeed);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpeed::NInterp::FInterp, SetMinSpeed);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpeed::NInterp::FInterp, SetInfo);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpeed::NInterp::FInterp, SetTargetSpeed);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpeed::NInterp::FInterp, SetTargetSpeedAsPercent);
			}
		}

		void FInterp::SetMaxSpeed(const float& Speed)
		{
			using namespace NCached;

			const FString& Context = Str::SetMaxSpeed;

			checkf(Speed > 0.0f, TEXT("%s: Speed: %f is NOT > 0.0f."), *Context, Speed);

			if (Speed != MaxSpeed)
			{
				MaxSpeed		  = Speed;
				MinSpeedAsPercent = MinSpeed / MaxSpeed;
				PercentOfMaxSpeed = 1.0f;
			}
		}

		void FInterp::SetPercentOfMaxSpeed(const float& Percent)
		{
			using namespace NCached;

			const FString& Context = Str::SetPercentOfMaxSpeed;

			checkf(Percent > 0.0f && Percent <= 1.0f, TEXT("%s: Percent: %f is NOT in the range (0.0f, 1.0f]."), *Context, Percent);

			checkf(MaxSpeed > 0.0f, TEXT("%s: MaxSpeed: %f is NOT > 0.0f"), *Context, MaxSpeed);

			if (Percent != PercentOfMaxSpeed)
			{
				PercentOfMaxSpeed = Percent;
				MaxBound		  = PercentOfMaxSpeed;
			}
		}

		void FInterp::SetMinSpeed(const float& Speed)
		{
			using namespace NCached;

			const FString& Context = Str::SetMinSpeed;

			checkf(MaxSpeed > 0.0f, TEXT("%s: MaxSpeed: %f is NOT > 0.0f"), *Context, MaxSpeed);

			checkf(Speed <= MaxSpeed, TEXT("%s: Speed is NOT <= MaxSpeed (%f > %f)."), *Context, Speed, MaxSpeed);

			if (Speed != MinSpeed)
			{
				MinSpeed		  = Speed;
				MinSpeedAsPercent = MinSpeed / MaxSpeed;
				MinBound		  = MinSpeedAsPercent;
			}
		}

		#define InfoType NCsSpeed::NInterp::FInfo
		void FInterp::SetInfo(InfoType* InInfo)
		{
		#undef InfoType

			using namespace NCached;

			const FString& Context = Str::SetInfo;

			checkf(InInfo, TEXT("%s: InInfo is NULL."), *Context);

			Info = InInfo;

			checkf(Info->IsValidChecked(Context), TEXT("%s: Info is NOT Valid."), *Context);

			typedef NCsSpeed::NInterp::EDirection DirectionType;

			DirectionSign = Info->GetDirection() == DirectionType::Increasing ? 1.0f : -1.0f;

			// Acceleration
			typedef NCsSpeed::NInterp::EMethod MethodType;

			if (Info->GetMethod() == MethodType::Acceleration)
			{
				checkf(MaxSpeed > 0.0f, TEXT("%s: MaxSpeed (%f) <= 0.0f"), *Context, MaxSpeed);

				AccelerationAsPercent = Info->GetAcceleration().UUpSS / MaxSpeed;
			}
		}

		void FInterp::SetTargetSpeed(const float& Speed)
		{
			using namespace NCached;

			const FString& Context = Str::SetTargetSpeed;

			checkf(MaxSpeed > 0.0f, TEXT("%s: MaxSpeed (%f) <= 0.0f"), *Context, MaxSpeed);

			checkf(Speed <= MaxSpeed, TEXT("%s: Speed > MaxSpeed (%f > %f)."), *Context, Speed, MaxSpeed);

			if (Speed != TargetSpeed)
			{
				TargetSpeed			 = Speed;
				TargetSpeedAsPercent = TargetSpeed / MaxSpeed;
			}
		}

		void FInterp::SetTargetSpeedAsPercent(const float& Percent)
		{
			using namespace NCached;

			const FString& Context = Str::SetTargetSpeedAsPercent;

			checkf(MaxSpeed > 0.0f, TEXT("%s: MaxSpeed (%f) <= 0.0f"), *Context, MaxSpeed);

			checkf(Percent >= -1.0f && Percent <= 1.0f, TEXT("%s: Percent: %f should be between [-1.0f, 1.0f] inclusive."), *Context, Percent);

			if (Percent != TargetSpeedAsPercent)
			{
				TargetSpeedAsPercent = Percent;
				TargetSpeed			 = FMath::Abs(TargetSpeedAsPercent) * MaxSpeed;
			}
		}

		void FInterp::SetCurrentSpeedAsPercent(const float& Percent)
		{
			typedef NCsSpeed::NInterp::EMethod MethodType;

			const MethodType& Method = Info->GetMethod();

			// Acceleration
			if (Method == MethodType::Acceleration)
			{
				CurrentSpeedAsPercent = Percent;
			}
			// Easing
			else
			if (Method == MethodType::Easing)
			{
				// Remap Percent from [0.0f, 1.0f] to be percent of [MinSpeedAsPercent, 1.0f]
				float RemappedPercent = (FMath::Max(Percent, MinSpeedAsPercent) - MinSpeedAsPercent) / (1.0f - MinSpeedAsPercent);

				// TODO: Get the Alpha that corresponds to the Percent
				CurrentAlpha = RemappedPercent;
			}
			// Curve
			else
			if (Method == MethodType::Curve)
			{
				// Remap Percent from [0.0f, 1.0f] to be percent of [MinSpeedAsPercent, 1.0f]
				float RemappedPercent = (FMath::Max(Percent, MinSpeedAsPercent) - MinSpeedAsPercent) / (1.0f - MinSpeedAsPercent);

				// TODO: Get the Alpha that corresponds to the Percent
				// TODO: Use Curve Lookup Table
				CurrentAlpha = RemappedPercent;
			}
		}

		void FInterp::Update(const float& DeltaTime)
		{
			if (TargetSpeedAsPercent == CurrentSpeedAsPercent)
				return;

			typedef NCsSpeed::NInterp::EMethod MethodType;
			typedef NCsSpeed::NInterp::EDirection DirectionType;

			const MethodType& Method = Info->GetMethod();

			// Acceleration
			if (Method == MethodType::Acceleration)
			{
				// Increasing to TargetSpeedAsPercent
				if (DirectionSign > 0)
				{
					if (bMinBound)
						CurrentSpeedAsPercent = FMath::Clamp(CurrentSpeedAsPercent + (DeltaTime * AccelerationAsPercent), MinBound, TargetSpeedAsPercent);
					else
						CurrentSpeedAsPercent =  FMath::Min(CurrentSpeedAsPercent + (DeltaTime * AccelerationAsPercent), TargetSpeedAsPercent);
				}
				// Decreasing to TargetSpeedAsPercent
				else
				{
					if (bMaxBound)
						CurrentSpeedAsPercent = FMath::Clamp(CurrentSpeedAsPercent - (DeltaTime * AccelerationAsPercent), TargetSpeedAsPercent, MaxBound);
					else
						CurrentSpeedAsPercent = FMath::Max(TargetSpeedAsPercent, CurrentSpeedAsPercent - (DeltaTime * AccelerationAsPercent));
				}
			}
			// Easing
			else
			if (Method == MethodType::Easing)
			{
				const float AdjustedDeltaTime = DeltaTime / Info->GetTime();

				CurrentAlpha				= FMath::Clamp(CurrentAlpha + AdjustedDeltaTime, 0.0f, 1.0f);
				const float Percent		    = FCsLibrary_Math::Ease(Info->GetEasing(), CurrentAlpha, 0.0f, 1.0f, 1.0f);
				const float AdjustedPercent = Info->GetDirection() == DirectionType::Increasing ? Percent : 1.0f - Percent;

				// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, 1.0f]

				// Increasing
				if (Info->GetDirection() == DirectionType::Increasing)
					CurrentSpeedAsPercent = FMath::Clamp(Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent, 0.0f, TargetSpeedAsPercent);
				// Decreasing
				else
					CurrentSpeedAsPercent = FMath::Max(TargetSpeedAsPercent, Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent);
			}
			// Curve
			else
			if (Method == MethodType::Curve)
			{
				const float AdjustedDeltaTime = DeltaTime / Info->GetTime();

				CurrentAlpha				= FMath::Clamp(CurrentAlpha + AdjustedDeltaTime, 0.0f, 1.0f);
				const float Percent			= Info->GetCurve()->GetFloatValue(CurrentAlpha);
				const float AdjustedPercent = Info->GetDirection() == DirectionType::Increasing ? Percent : 1.0f - Percent;

				// Remap Percent from [0.0f, 1.0f] to [MinSpeedAsPercent, 1.0f]

				// Increasing
				if (Info->GetDirection() == DirectionType::Increasing)
					CurrentSpeedAsPercent = FMath::Clamp(Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent, 0.0f, TargetSpeedAsPercent);
				// Decreasing
				else
					CurrentSpeedAsPercent = FMath::Max(TargetSpeedAsPercent, Percent * (1.0f - MinSpeedAsPercent) + MinSpeedAsPercent);
			}
		}

		float FInterp::RemapValue(const float& Value) const
		{
			return (Value * (MaxBound - MinBound)) + MinBound;
		}
	}
}

#pragma endregion NCsSpeed::NInterp::FInterp