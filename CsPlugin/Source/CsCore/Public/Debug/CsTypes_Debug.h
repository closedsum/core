// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
#include "Engine/HitResult.h"
// CVars
#include "CsCVars_Core.h"

#include "CsTypes_Debug.generated.h"

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

// FCsDebugDrawBox
#pragma region

class UWorld;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawBox
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to center and / or transform matrix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FRotator3f Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Extent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bSolid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawBox() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Location(FVector3f::ZeroVector),
		RotationType(ECsDebugDrawRotation::Absolute),
		Rotation(FRotator3f::ZeroRotator),
		Extent(FVector3f::ZeroVector),
		Color(FColor::Red),
		LifeTime(0.1f),
		bSolid(false),
		Thickness(1.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;

	void Draw(const UObject* WorldContext, const FTransform3f& Transform) const;

	void Draw(const UObject* WorldContext, const FTransform3f& Transform, const FVector3f& InExtent) const;

private:

	void Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform, const FVector3f& InExtent) const;
};

#pragma endregion FCsDebugDrawBox

// FCsDebugDrawCircle
#pragma region

class UObject;
class AActor;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawCircle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	/** Whether to enable drawing in Editor Preview or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	/** The priority for which flag / method to enable drawing in Editor,
		CVar, bEnableInPreview or bEnableinPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	/** Whether to enable drawing during Play in Editor (PIE) or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to center and / or transform matrix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FRotator3f Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MinRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawCircle() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Location(FVector3f::ZeroVector),
		RotationType(ECsDebugDrawRotation::Absolute),
		Rotation(FRotator3f::ZeroRotator),
		MinRadius(32.0f),
		MaxRadius(32.0f),
		Segments(16),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;
	bool CanDraw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar) const;

	void Draw(const UObject* WorldContext, const FTransform3f& Transform) const;
	void Draw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar, const FVector3f& InLocation, const float& InMinRadius, const float& InMaxRadius) const;
	void Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& InMinRadius, const float& InMaxRadius) const;

	void DrawAtLocation(AActor* Actor, const FECsCVarDraw& OtherCVar, const float& InMinRadius, const float& InMaxRadius) const;
	void DrawAtLocation(AActor* Actor, const float& InMinRadius, const float& InMaxRadius) const;
	void DrawAtLocation(AActor* Actor, const float& Radius) const;

private:

	void Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform) const;
	void Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform, const float& InMinRadius, const float& InMaxRadius) const;
};

#pragma endregion FCsDebugDrawCircle

// FCsDebugDrawSphere
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawSphere
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to center and / or transform matrix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FRotator3f Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MinRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "1.0", ClampMin = "1.0"))
	float MaxRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawSphere() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Location(FVector3f::ZeroVector),
		RotationType(ECsDebugDrawRotation::Absolute),
		Rotation(FRotator3f::ZeroRotator),
		MinRadius(32.0f),
		MaxRadius(32.0f),
		Segments(16),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;

	void Draw(const UObject* WorldContext, const FTransform3f& Transform) const;
	void Draw(const UObject* WorldContext, const FTransform3f& Transform, const float& InMinRadius, const float& InMaxRadius) const;
	void Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& InMinRadius, const float& InMaxRadius) const;
	void Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& Radius) const;

private:

	void Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform) const;
	void Draw_Internal(const UObject* WorldContext, const FTransform3f& Transform, const float& InMinRadius, const float& InMaxRadius) const;
};

#pragma endregion FCsDebugDrawSphere

// FCsDebugDrawPie
#pragma region

class UObject;
class AActor;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawPie
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to center and / or transform matrix. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FRotator3f Rotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "1.0", ClampMin = "1.0"))
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "1.0", ClampMin = "1.0"))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawPie() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Location(FVector3f::ZeroVector),
		RotationType(ECsDebugDrawRotation::Absolute),
		Rotation(FRotator3f::ZeroRotator),
		Angle(45.0f),
		Radius(32.0f),
		Segments(16),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;
	bool CanDraw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar) const;

	void Draw(const UObject* WorldContext, const FTransform3f& Transform) const;
	void Draw(const UObject* WorldContext, const float& InAngle, const FTransform3f& Transform, const float& InRadius) const;
	void Draw(const UObject* WorldContext, const FECsCVarDraw& OtherCVar, const float& InAngle, const FVector3f& InLocation, const float& InRadius) const;
	void Draw(const UObject* WorldContext, const FVector3f& InLocation, const float& InRadius) const;

	void DrawAtLocation(AActor* Actor, const FECsCVarDraw& OtherCVar, const float& InRadius) const;
	void DrawAtLocation(AActor* Actor, const float& InRadius) const;

private:

	void Draw_Internal(const UObject* WorldContext, const float& InAngle, const FTransform3f& Transform) const;
	void Draw_Internal(const UObject* WorldContext, const float& InAngle, const FTransform3f& Transform, const float& InRadius) const;
};

#pragma endregion FCsDebugDrawPie

// FCsDebugDrawPoint
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawPoint
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to Location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawPoint() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Offset(FVector3f::ZeroVector),
		Radius(32.0f),
		Segments(4),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector3f& Location) const;
};

#pragma endregion FCsDebugDrawPoint

// FCsDebugDrawLine
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawLine
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	/** Whether to enable drawing in Editor Preview or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	/** The priority for which flag / method to enable drawing in Editor,
		CVar, bEnableInPreview or bEnableinPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	/** Whether to enable drawing during Play in Editor (PIE) or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to Start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f StartOffset;

	/** Applied as a translation offset to End. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f EndOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawLine() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		StartOffset(FVector3f::ZeroVector),
		EndOffset(FVector3f::ZeroVector),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;

	void Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& End) const;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to Start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f StartOffset;

	/** Applied as a translation offset to End. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f EndOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	int32 Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawLineAndPoint() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		StartOffset(FVector3f::ZeroVector),
		EndOffset(FVector3f::ZeroVector),
		Radius(32.0f),
		Segments(4),
		Color(FColor::Red),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& InLifeTime) const;

	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End) const;

	void DrawOnlyLine(UWorld* World, const FVector3f& Start, const FVector3f& End) const;

	void DrawOnlyPoint(UWorld* World, const FVector3f& Location) const;
};

#pragma endregion FCsDebugDrawLineAndPoint

// FCsDebugDrawDirectionArrow
#pragma region

class UObject;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawDirectionArrow
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	/** Whether to enable drawing in Editor Preview or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	/** The priority for which flag / method to enable drawing in Editor,
		CVar, bEnableInPreview or bEnableinPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	/** Whether to enable drawing during Play in Editor (PIE) or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to Start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f StartOffset;

	/** Applied as a translation offset to End. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f EndOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawRotation RotationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FRotator3f Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	/** Size of the Arrow. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Length;

	FCsDebugDrawDirectionArrow() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		StartOffset(FVector3f::ZeroVector),
		EndOffset(FVector3f::ZeroVector),
		RotationType(ECsDebugDrawRotation::Offset),
		Rotation(FRotator3f::ZeroRotator),
		Color(FColor::Red),
		LifeTime(0.1f),
		Size(1.0f),
		Thickness(1.0f),
		Length(100.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;

	void Draw(const UObject* WorldContext, const FVector3f& Start, const FRotator3f& InRotation) const;
	void Draw(const UObject* WorldContext, const FVector3f& Start, const FRotator3f& InRotation, const float& InLength) const;
	void Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& Direction, const float& InLength) const;
	void Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& Direction) const;
};

#pragma endregion FCsDebugDrawDirectionArrow

// FCsDebugDrawString
#pragma region

class UWorld;

USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawString
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	/** Applied as a translation offset to Location. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FVector3f Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bDrawShadow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float FontScale;

	FCsDebugDrawString() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Offset(FVector3f::ZeroVector),
		Color(FColor::Red),
		LifeTime(0.1f),
		bDrawShadow(false),
		FontScale(1.0f)
	{
	}

	bool CanDraw(const UObject* WorldContext) const;

	void Draw(const UObject* WorldContext, const FVector3f& Location, const FString& Text) const;
};

#pragma endregion FCsDebugDrawString

// FCsDebugDrawTraceLine
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawTraceLine
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FColor HitColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float HitSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Thickness;

	FCsDebugDrawTraceLine() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Color(FColor::Red),
		HitColor(FColor::Green),
		HitSize(16.0f),
		LifeTime(0.1f),
		Thickness(1.0f)
	{
		
	}

	bool CanDraw(const UObject* WorldContext) const;

	void Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& End, const FHitResult& Hit) const;

	void Draw(const UObject* WorldContext, const FVector3f& Start, const FVector3f& End, const bool& BlockingHit, const FVector3f& ImpactPoint) const;
};

#pragma endregion FCsDebugDrawTraceLine

// FCsDebugDrawTraceBox
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawTraceBox
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor HitColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	FCsDebugDrawTraceBox() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Color(FLinearColor::Red),
		HitColor(FLinearColor::Green),
		LifeTime(0.1f)
	{
		
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f& HalfSize, const FRotator3f& Rotation, const FHitResult& Hit) const;
};

#pragma endregion FCsDebugDrawTraceBox

// FCsDebugDrawTraceSphere
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawTraceSphere
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor HitColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	FCsDebugDrawTraceSphere() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Color(FLinearColor::Red),
		HitColor(FLinearColor::Green),
		LifeTime(0.1f)
	{
		
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const FHitResult& Hit) const;
};

#pragma endregion FCsDebugDrawTraceSphere

// FCsDebugDrawTraceCapsule
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawTraceCapsule
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor HitColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	FCsDebugDrawTraceCapsule() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Color(FLinearColor::Red),
		HitColor(FLinearColor::Green),
		LifeTime(0.1f)
	{
		
	}

	bool CanDraw(UWorld* World) const;

	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const float& HalfHeight, const FHitResult& Hit) const;
};

#pragma endregion FCsDebugDrawTraceCapsule

// FCsDebugDrawTraceShape
#pragma region

struct FCollisionShape;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsDebugDrawTraceShape
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FECsCVarDraw CVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPreview;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	ECsDebugDrawPriority PriorityInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	bool bEnableInPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug")
	FLinearColor HitColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Debug", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float LifeTime;

	FCsDebugDrawTraceShape() :
		CVar(),
		bEnableInPreview(false),
		PriorityInPlay(ECsDebugDrawPriority::Any),
		bEnableInPlay(false),
		Color(FLinearColor::Red),
		HitColor(FLinearColor::Green),
		LifeTime(0.1f)
	{
		
	}

	bool CanDraw(UWorld* World) const;

	/**
	* Draw a Line Trace from Start to End with the given FHitResult (Hit) information.
	*
	* @param World	World context.
	* @param Start	Start location of the trace.
	* @param End	End location of the trace.
	* @param Hit	FHitResult information of the trace.
	*/
	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FHitResult& Hit) const;

	/**
	* Draw a Box Trace from Start to End with the given FHitResult (Hit) information.
	*
	* @param World		World context.
	* @param Start		Start location of the trace.
	* @param End		End location of the trace.
	* @param HalfSize	Extents of the box.
	* @param Rotation	Orientation of the box. 
	* @param Hit		FHitResult information of the trace.
	*/
	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FVector3f& HalfSize, const FRotator3f& Rotation, const FHitResult& Hit) const;

	/**
	* Draw a Sphere Trace from Start to End with the given FHitResult (Hit) information.
	*
	* @param World	World context.
	* @param Start	Start location of the trace.
	* @param End	End location of the trace.
	* @param Radius Radius of the sphere. 
	* @param Hit	FHitResult information of the trace.
	*/
	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const FHitResult& Hit) const;
	
	/**
	* Draw a Capsule Trace from Start to End with the given FHitResult (Hit) information.
	*
	* @param World		World context.
	* @param Start		Start location of the trace.
	* @param End		End location of the trace.
	* @param Radius		Radius of the capsule.
	* @param HalfHeight Half height of the capsule.
	* @param Hit		FHitResult information of the trace.
	*/
	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const float& Radius, const float& HalfHeight, const FHitResult& Hit) const;

	/**
	* Draw a Trace's shape (Line, Box, Sphere, or Capsule) from Start to End with the given FHitResult (Hit) information.
	*
	* @param World	World context.
	* @param Start	Start location of the trace.
	* @param End	End location of the trace.
	* @param Shape	Shape of the trace (Line, Box, Sphere, or Capsule). 
	* @param Hit	FHitResult information of the trace.
	*/
	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FCollisionShape* Shape, const FHitResult& Hit) const;

	/**
	* Draw a Trace's shape (Line, Box, Sphere, or Capsule) from Start to End.
	*
	* @param World	World context.
	* @param Start	Start location of the trace.
	* @param End	End location of the trace.
	* @param Shape	Shape of the trace (Line, Box, Sphere, or Capsule). 
	*/
	void Draw(UWorld* World, const FVector3f& Start, const FVector3f& End, const FCollisionShape* Shape) const;
};

#pragma endregion FCsDebugDrawTraceShape