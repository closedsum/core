// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
#include "CsCvars.h"

#include "CsTypes_Debug.generated.h"
#pragma once

// DebugDrawPriority
#pragma region

UENUM(BlueprintType)
enum class ECsDebugDrawPriority : uint8
{
	Any							UMETA(DisplayName = "Any"),
	CVar						UMETA(DisplayName = "CVar"),
	Flag						UMETA(DisplayName = "Flag"),
	ECsDebugDrawPriority_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDebugDrawPriority : public TCsEnumMap<ECsDebugDrawPriority>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDebugDrawPriority, ECsDebugDrawPriority)
};

namespace NCsDebugDrawPriority
{
	typedef ECsDebugDrawPriority Type;

	namespace Ref
	{
		extern CSCORE_API const Type Any;
		extern CSCORE_API const Type CVar;
		extern CSCORE_API const Type Flag;
		extern CSCORE_API const Type ECsDebugDrawPriority_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion DebugDrawPriority

// DebugDrawFrequency
#pragma region

UENUM(BlueprintType)
enum class ECsDebugDrawFrequency : uint8
{
	Once						UMETA(DisplayName = "Once"),
	Update						UMETA(DisplayName = "Update"),
	ECsDebugDrawFrequency_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDebugDrawFrequency : public TCsEnumMap<ECsDebugDrawFrequency>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDebugDrawFrequency, ECsDebugDrawFrequency)
};

namespace NCsDebugDrawFrequency
{
	typedef ECsDebugDrawFrequency Type;

	namespace Ref
	{
		extern CSCORE_API const Type Once;
		extern CSCORE_API const Type Update;
		extern CSCORE_API const Type ECsDebugDrawFrequency_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion DebugDrawFrequency

// DebugDrawRotation
#pragma region

UENUM(BlueprintType)
enum class ECsDebugDrawRotation : uint8
{
	Absolute					UMETA(DisplayName = "Absolute"),
	Offset						UMETA(DisplayName = "Offset"),
	ECsDebugDrawRotation_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDebugDrawRotation : public TCsEnumMap<ECsDebugDrawRotation>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDebugDrawRotation, ECsDebugDrawRotation)
};

namespace NCsDebugDrawRotation
{
	typedef ECsDebugDrawRotation Type;

	namespace Ref
	{
		extern CSCORE_API const Type Absolute;
		extern CSCORE_API const Type Offset;
		extern CSCORE_API const Type ECsDebugDrawRotation_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

#pragma endregion DebugDrawRotation

// FCsDebugDrawCircle
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawCircle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPlay;

	/** Applied as a translation offset to center and / or transform matrix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MinRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness;

	FCsDebugDrawCircle() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Location(FVector::ZeroVector),
		RotationType(ECsDebugDrawRotation::Absolute),
		Rotation(FRotator::ZeroRotator),
		MinRadius(32.0f),
		MaxRadius(32.0f),
		Segments(16),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FTransform& Transform) const;
};

#pragma endregion FCsDebugDrawCircle

// FCsDebugDrawSphere
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawSphere
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPlay;

	/** Applied as a translation offset to center and / or transform matrix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MinRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness;

	FCsDebugDrawSphere() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Location(FVector::ZeroVector),
		RotationType(ECsDebugDrawRotation::Absolute),
		Rotation(FRotator::ZeroRotator),
		MinRadius(32.0f),
		MaxRadius(32.0f),
		Segments(16),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FTransform& Transform) const;
};

#pragma endregion FCsDebugDrawSphere

// FCsDebugDrawPoint
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawPoint
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPlay;

	/** Applied as a translation offset to Location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness;

	FCsDebugDrawPoint() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Offset(FVector::ZeroVector),
		Radius(32.0f),
		Segments(4),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector& Location) const;
};

#pragma endregion FCsDebugDrawPoint

// FCsDebugDrawLine
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawLine
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPlay;

	/** Applied as a translation offset to Start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartOffset;

	/** Applied as a translation offset to End. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness;

	FCsDebugDrawLine() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		StartOffset(FVector::ZeroVector),
		EndOffset(FVector::ZeroVector),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector& Start, const FVector& End) const;
};

#pragma endregion FCsDebugDrawPoint

// FCsDebugDrawLineAndPoint
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawLineAndPoint
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableInPlay;

	/** Applied as a translation offset to Start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartOffset;

	/** Applied as a translation offset to End. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Thickness;

	FCsDebugDrawLineAndPoint() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		StartOffset(FVector::ZeroVector),
		EndOffset(FVector::ZeroVector),
		Radius(32.0f),
		Segments(4),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector& Start, const FVector& End, const float& InLifeTime) const;

	void Draw(UWorld* World, const FVector& Start, const FVector& End) const;

	void DrawOnlyLine(UWorld* World, const FVector& Start, const FVector& End) const;

	void DrawOnlyPoint(UWorld* World, const FVector& Location) const;
};

#pragma endregion FCsDebugDrawLineAndPoint