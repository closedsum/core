// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Movement.h"

// Library
#include "Library/CsLibrary_Math.h"
// Curve
#include "Curves/CurveFloat.h"

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