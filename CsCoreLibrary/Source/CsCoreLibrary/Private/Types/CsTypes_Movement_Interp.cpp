// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Movement_Interp.h"
#include "CsCoreLibrary.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Actor/CsLibrary_Actor.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Curve
#include "Curves/CurveFloat.h"
// Component
#include "Components/SkeletalMeshComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Movement_Interp)

// FCsMoveByInterp_Params
#pragma region

namespace NCsMoveByInterp_Params
{
	using MoverType = NCsMovement::EMover;
	using DestinationType = NCsMovement::EDestination;

	void FImpl::CopyToParams(FCsMoveByInterp_Params* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Easing);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Mover, MoverType);
		CS_THIS_COPY_TO_PROXY(Params, FromLocation);
		CS_THIS_COPY_TO_PROXY(Params, MoveObjectName);
		CS_THIS_COPY_TO_PROXY(Params, MoveActorLabel);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, MoveActor);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, MoveComponent);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Destination, DestinationType);
		CS_THIS_COPY_TO_PROXY(Params, ToLocation);
		CS_THIS_COPY_TO_PROXY(Params, ToObjectName);
		CS_THIS_COPY_TO_PROXY(Params, ToActorLabel);
		CS_THIS_COPY_TO_PROXY(Params, ToBone);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToActor);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToComponent);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToMeshComponent);
		CS_THIS_COPY_TO_PROXY(Params, Time);
		CS_THIS_COPY_TO_PROXY(Params, Group);
	}

	void FImpl::CopyToParamsAsValue(const FCsMoveByInterp_Params* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Easing);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Mover, MoverType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, FromLocation);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, MoveObjectName);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, MoveActorLabel);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, MoveActor);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, MoveComponent);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Destination, DestinationType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToLocation);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToObjectName);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToActorLabel);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToBone);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToActor);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToComponent);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, ToMeshComponent);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Time);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Group);
	}
}

void FCsMoveByInterp_Params::ConditionalSetSafeMoveObject(const FString& Context, const UObject* WorldContext)
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
		#if WITH_EDITOR
			// Label
			if (!MoveActorLabel.IsEmpty())
			{
				MoveActor = CsActorLibrary::GetByLabelChecked(Context, WorldContext, MoveActorLabel);
				return;
			}
			// Name
			if (MoveObjectName != NAME_None)
			{
				MoveActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, MoveObjectName);
				return;
			}

			UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to set MoveActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
		#else
			// Name
			if (MoveObjectName != NAME_None)
			{
				MoveActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, MoveObjectName);
				return;
			}

			UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to set MoveActor. Name: None is NOT Valid."), *Context);
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

void FCsMoveByInterp_Params::ConditionalSetSafeDestinationObject(const FString& Context, const UObject* WorldContext)
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
		#if WITH_EDITOR
			// Label
			if (!ToActorLabel.IsEmpty())
			{
				ToActor = CsActorLibrary::GetByLabelChecked(Context, WorldContext, ToActorLabel);
				return;
			}
			// Name
			if (ToObjectName != NAME_None)
			{
				ToActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, ToObjectName);
				return;
			}

			UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to set ToActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
		#else
			// Name
			if (ToObjectName != NAME_None)
			{
				MoveActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, ToObjectName);
				return;
			}

			UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: Failed to set ToActor. Name: None is NOT Valid."), *Context);
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
				UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: ToBone: None is NOT Valid."), *Context);
				return;
			}

			const int32 BoneIndex = ToMeshComponent->GetBoneIndex(ToBone);

			if (BoneIndex == INDEX_NONE)
			{
				UE_LOG(LogCsCoreLibrary, Warning, TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(ToMeshComponent->GetName()), *(ToBone.ToString()));
				return;
			}
		}
	}
}

bool FCsMoveByInterp_Params::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/) const
{
	// Check Easing is Valid
	if (!EMCsEasingType::Get().IsValidEnum(Easing))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Easing: %s is NOT Valid."), *Context, EMCsEasingType::Get().ToChar(Easing)));
		return false;
	}
	// Check Move Object is Valid
	if (!EMCsMover::Get().IsValidEnum(Mover))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mover: %s is NOT Valid."), *Context, EMCsMover::Get().ToChar(Mover)));
		return false;
	}

	if (Mover == ECsMover::Actor)
	{
		if (!MoveActor)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mover == ECsMover::Actor and MoveActor is NULL."), *Context));
			return false;
		}

		USceneComponent* RootComponent = MoveActor->GetRootComponent();

		if (!RootComponent)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: MoveActor: %s has NO RootComponent."), *Context, *(MoveActor->GetName())));
			return false;
		}

		if (RootComponent->Mobility != EComponentMobility::Movable)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: MoveActor: %s Mobility is NOT Movable."), *Context, *(MoveActor->GetName())));
			return false;
		}
	}
	else
	if (Mover == ECsMover::Component)
	{
		if (!MoveComponent)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Mover == ECsMover::Component and MoveComponent is NULL."), *Context));
			return false;
		}

		if (MoveComponent->Mobility != EComponentMobility::Movable)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: MoveComponent: %s Mobility is NOT Movable."), *Context, *(MoveComponent->GetName())));
			return false;
		}
	}
	// Check Destination is Valid
	if (!EMCsMoveDestination::Get().IsValidEnum(Destination))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Destination: %s is NOT Valid."), *Context, EMCsMoveDestination::Get().ToChar(Destination)));
		return false;
	}

	if (Destination == ECsMoveDestination::Actor)
	{
		if (!ToActor)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Destination == ECsMoveDestination::Actor and ToActor is NULL."), *Context));
			return false;
		}
	}
	else
	if (Destination == ECsMoveDestination::Component)
	{
		if (!ToComponent &&
			!ToMeshComponent)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Destination == ECsMoveDestination::Component and ToComponent && ToMeshComponent are NULL."), *Context));
			return false;
		}
	}
	else
	if (Destination == ECsMoveDestination::Bone)
	{
		if (!ToMeshComponent)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Destination == ECsMoveDestination::Bone and ToMeshComponent is NULL."), *Context));
			return false;
		}

		if (ToBone == NAME_None)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Destination == ECsMoveDestination::Bone and ToBone: None is NOT Valid."), *Context));
			return false;
		}

		const int32 BoneIndex = ToMeshComponent->GetBoneIndex(ToBone);

		if (BoneIndex == INDEX_NONE)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(ToMeshComponent->GetName()), *(ToBone.ToString())));
			return false;
		}
	}
	// Check Time is Valid
	if (Time < 0.0f)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Time: %f is NOT >= 0.0f."), *Context, Time));
		return false;
	}
	// Check Group is Valid
	if (!EMCsUpdateGroup::Get().IsValidEnum(Group))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Group: %s is NOT Valid."), *Context, Group.ToChar()));
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
				using MoverMapType = NCsMovement::EMMover;
				using DestinationMapType = NCsMovement::EMDestination;

				void FParams::SetMoveActor(AActor* Value) { MoveActor = Value; }

				void FParams::SetMoveComponent(USceneComponent* Value) { MoveComponent = Value; }

				void FParams::SetToActor(AActor* Value) { ToActor = Value; }

				void FParams::SetToComponent(USceneComponent* Value) { ToComponent = Value; }

				void FParams::SetToMeshComponent(USkeletalMeshComponent* Value) { ToMeshComponent = Value; }

				AActor* FParams::GetMoveActor() const { return MoveActor.IsValid() ? MoveActor.Get() : nullptr; }

				USceneComponent* FParams::GetMoveComponent() const { return MoveComponent.IsValid() ? MoveComponent.Get() : nullptr; }

				AActor* FParams::GetToActor() const { return ToActor.IsValid() ? ToActor.Get() : nullptr; }

				USceneComponent* FParams::GetToComponent() const { return ToComponent.IsValid() ? ToComponent.Get() : nullptr; }

				USkeletalMeshComponent* FParams::GetToMeshComponent() const { return ToMeshComponent.IsValid() ? ToMeshComponent.Get() : nullptr; }

				void FParams::ConditionalSetMoveObjectChecked(const FString& Context, UObject* WorldContext)
				{
					CS_IS_ENUM_VALID_CHECKED(MoverMapType, GetMover())

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
						#if WITH_EDITOR
							// Label
							if (!GetMoveActorLabel().IsEmpty())
							{
								MoveActor = CsActorLibrary::GetByLabelChecked(Context, WorldContext, GetMoveActorLabel());
								return;
							}
							// Name
							if (GetMoveObjectName() != NAME_None)
							{
								MoveActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, GetMoveObjectName());
								return;
							}

							checkf(0, TEXT("%s: Failed to set MoveActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
						#else
							// Name
							if (GetMoveObjectName() != NAME_None)
							{
								MoveActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, GetMoveObjectName());
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
					CS_IS_ENUM_VALID_CHECKED(DestinationMapType, GetDestination())
					
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
						#if WITH_EDITOR
							// Label
							if (!GetToActorLabel().IsEmpty())
							{
								ToActor = CsActorLibrary::GetByLabelChecked(Context, WorldContext, GetToActorLabel());
								return;
							}
							// Name
							if (GetToObjectName() != NAME_None)
							{
								ToActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, GetToObjectName());
								return;
							}

							checkf(0, TEXT("%s: Failed to set ToActor. Label is EMPTY. Name: None is NOT Valid."), *Context);
						#else
							// Name
							if (GetToObjectName() != NAME_None)
							{
								ToActor = CsActorLibrary::GetByNameChecked(Context, WorldContext, GetToObjectName());
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
					CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, GetEasing())
					CS_IS_ENUM_VALID_CHECKED(MoverMapType, GetMover())
					// Check Move Object is Valid
					if (GetMover() == MoverType::Actor)
					{
						checkf(GetMoveActor(), TEXT("%s: GetMover() == NCsMovement::EMover::Actor and GetMoveActor() is NULL."), *Context);
						// Check RootComponent is Valid
						USceneComponent* RootComponent = MoveActor->GetRootComponent();

						checkf(RootComponent, TEXT("%s: GetMoveActor(): %s has NO RootComponent."), *Context, *(GetMoveActor()->GetName()));
						// Check RootComponent is Movable
						checkf(RootComponent->Mobility == EComponentMobility::Movable, TEXT("%s: GetMoveActor(): %s Mobility is NOT Movable."), *Context, *(GetMoveActor()->GetName()));
					}
					else
					if (GetMover() == MoverType::Component)
					{
						checkf(GetMoveComponent(), TEXT("%s: GetMover() == NCsMovement::EMover::Component and GetMoveComponent() is NULL."), *Context);
						// Check GetMoveComponent() is Movable
						checkf(GetMoveComponent()->Mobility == EComponentMobility::Movable, TEXT("%s: GetMoveComponent(): %s Mobility is NOT Movable."), *Context, *(GetMoveComponent()->GetName()));
					}
					
					CS_IS_ENUM_VALID_CHECKED(DestinationMapType, GetDestination())

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

						CS_IS_NAME_NONE_CHECKED(GetToBone());

						const int32 BoneIndex = GetToMeshComponent()->GetBoneIndex(ToBone);

						checkf(BoneIndex != INDEX_NONE, TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(GetToMeshComponent()->GetName()), *(GetToBone().ToString()));
					}
					// Check Time is Valid
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(GetTime(), 0.0f)
					// Check Group is Valid
					CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUpdateGroup, GetGroup())
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/) const
				{
					CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, GetEasing())
					CS_IS_ENUM_VALID(MoverMapType, MoverType, GetMover())

					// Check Move Object is Valid
					if (GetMover() == MoverType::Actor)
					{
						if (!GetMoveActor())
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No MoveActor set."), *Context));
							return false;
						}
					}
					else
					if (GetMover() == MoverType::Component)
					{
						if (!GetMoveComponent())
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No MoveComponent set."), *Context));
							return false;
						}
					}

					CS_IS_ENUM_VALID(DestinationMapType, DestinationType, GetDestination())
					
					if (GetDestination() == DestinationType::Actor)
					{
						if (!GetToActor())
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No ToActor set."), *Context));
							return false;
						}
					}
					else
					if (GetDestination() == DestinationType::Component)
					{
						if (!GetToComponent() && 
							!GetToMeshComponent())
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No ToComponent && ToMeshComponent are NOT set."), *Context));
							return false;
						}
					}
					else
					if (GetDestination() == DestinationType::Bone)
					{
						if (!GetToMeshComponent())
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ToMeshComponent is NOT set."), *Context));
							return false;
						}

						CS_IS_NAME_NONE(GetToBone())

						const int32 BoneIndex = GetToMeshComponent()->GetBoneIndex(ToBone);

						if (BoneIndex == INDEX_NONE)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ToMeshComponent: %s does NOT contain ToBone: %s."), *Context, *(GetToMeshComponent()->GetName()), *(GetToBone().ToString())));
							return false;
						}
					}
					// Check Time is Valid
					CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GetTime(), 0.0f)
					// Check Group is Valid
					CS_IS_ENUM_STRUCT_VALID(EMCsUpdateGroup, FECsUpdateGroup, GetGroup())
					return true;
				}

				FVector3f FParams::GetEndLocation() const
				{
					// TODO: Need to do Relative Location (i.e. check MoveSpace: World or Relative)
					
					// Location
					if (GetDestination() == DestinationType::Location)
						return GetToLocation();
					// Actor
					if (GetDestination() == DestinationType::Actor)
						return CsMathLibrary::Convert(GetToActor()->GetActorLocation()) + GetToLocation();
					// Component
					if (GetDestination() == DestinationType::Component)
						return CsMathLibrary::Convert(GetToComponent()->GetComponentLocation()) + GetToLocation();
					// Bone
					if (GetDestination() == DestinationType::Bone)
						return CsMathLibrary::Convert(GetToMeshComponent()->GetBoneLocation(GetToBone())) + GetToLocation();

					checkf(0, TEXT("NCsMovement::NTo::NInterp::NParams::FParams::GetEndLocation: GetDestination(): %s is NOT Valid."), DestinationMapType::Get().ToChar(GetDestination()));
					return FVector3f::ZeroVector;
				}

				void FParams::Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Easing, ECsEasingType::Linear)
					CS_RESET_MEMBER_WITH_PROXY(Mover, MoverType::Actor)
					CS_RESET_MEMBER_WITH_PROXY(FromLocation, FVector3f::ZeroVector)
					CS_RESET_MEMBER_WITH_PROXY(MoveObjectName, NAME_None)
					CS_RESET_MEMBER_WITH_PROXY(MoveActorLabel, TEXT(""))
					MoveActor = nullptr;
					MoveComponent = nullptr;
					CS_RESET_MEMBER_WITH_PROXY(Destination, DestinationType::Location)
					CS_RESET_MEMBER_WITH_PROXY(ToLocation, FVector3f::ZeroVector)
					CS_RESET_MEMBER_WITH_PROXY(ToObjectName, NAME_None)
					CS_RESET_MEMBER_WITH_PROXY(ToActorLabel, TEXT(""))
					CS_RESET_MEMBER_WITH_PROXY(ToBone, NAME_None)
					ToActor = nullptr;
					ToComponent = nullptr;
					ToMeshComponent = nullptr;
					CS_RESET_MEMBER_WITH_PROXY(Time, 0.0f)
					CS_RESET_MEMBER_WITH_PROXY(Group, EMCsUpdateGroup::Get().GetMAX())
				}
			}
		}
	}
}

#pragma endregion FCsMoveByInterp_Params

// FCsSpeedInterpInfo
#pragma region

namespace NCsSpeedInterpInfo
{
	using MethodType = NCsSpeed::NInterp::EMethod;
	using DirectionType = NCsSpeed::NInterp::EDirection;

	void FImpl::CopyToInfo(FCsSpeedInterpInfo* This, InfoType* Info)
	{
		CS_THIS_COPY_TYPE_TO_PROXY(Info, Method, MethodType);
		CS_THIS_COPY_TYPE_TO_PROXY(Info, Direction, DirectionType);
		CS_THIS_COPY_TO_PROXY(Info, Easing);
		CS_THIS_COPY_TO_PROXY(Info, Curve);
		CS_THIS_COPY_TO_PROXY(Info, Time);
		CS_THIS_COPY_TO_PROXY(Info, Acceleration);
	}

	void FImpl::CopyToInfoAsValue(const FCsSpeedInterpInfo* This, InfoType* Info)
	{
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Info, Method, MethodType);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Info, Direction, DirectionType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, Easing);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, Curve);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, Time);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, Acceleration);
	}
}

#if WITH_EDITOR

void FCsSpeedInterpInfo::OnPostEditChange(const TSet<FString>& PropertyNames, const FName& PropertyName)
{
	// Acceleration
	if (PropertyNames.Find(TEXT("Acceleration")))
		Acceleration.OnPostEditChange(PropertyName);
}

#endif // #if WITH_EDITOR

bool FCsSpeedInterpInfo::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsSpeedInterpInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsCore::NLibrary::FLog::Warning*/) const
{
	return true;
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

		using InfoType = NCsSpeed::NInterp::FInfo;

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

		void FInterp::SetInfo(InfoType* InInfo)
		{
			using namespace NCached;

			const FString& Context = Str::SetInfo;

			CS_IS_PTR_NULL_CHECKED(InInfo);

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
				const float Percent		    = CsMathLibrary::Ease(Info->GetEasing(), CurrentAlpha, 0.0f, 1.0f, 1.0f);
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