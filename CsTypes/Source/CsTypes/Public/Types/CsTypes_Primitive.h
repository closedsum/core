// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"

#include "CsTypes_Primitive.generated.h"

// MemberType
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FECsMemberType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsMemberType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsMemberType)

struct CSTYPES_API EMCsMemberType : public TCsEnumStructMap<FECsMemberType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsMemberType, FECsMemberType, uint8)
};

namespace NCsMemberType
{
	typedef FECsMemberType Type;
	typedef EMCsMemberType EnumMapType;

	extern CSTYPES_API const Type Bool;
	extern CSTYPES_API const Type Uint8;
	extern CSTYPES_API const Type Int32;
	extern CSTYPES_API const Type Enum;
	extern CSTYPES_API const Type EnumClass;
	extern CSTYPES_API const Type EnumNamespaced;
	extern CSTYPES_API const Type Float;
	extern CSTYPES_API const Type String;
	extern CSTYPES_API const Type Name;
	extern CSTYPES_API const Type Vector;
	extern CSTYPES_API const Type Rotator;
	extern CSTYPES_API const Type Color;
	extern CSTYPES_API const Type Object;
	extern CSTYPES_API const Type Actor;
	extern CSTYPES_API const Type Pawn;
	extern CSTYPES_API const Type ActorComponent;
	extern CSTYPES_API const Type SceneComponent;
	extern CSTYPES_API const Type PrimitiveComponent;
	extern CSTYPES_API const Type StaticMeshComponent;
	extern CSTYPES_API const Type SkeletalMeshComponent;
}

#pragma endregion MemberType

#define CS_DECLARE_AND_DEFINE_CONST_INTEGRAL_VALUE(Type, Integral, Value) const Type Integral = 1; \
																		  Type* ptr = (Type*)(&Integral); \
																		  *ptr = Value;

// Blueprint Property Types
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsBpProperty_bool
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool DefaultValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool Value;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsTypes|Primitive")
	bool Last_Value;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CsTypes|Primitive")
	bool IsDirty;

public:

	TMulticastDelegate<void(const bool&)> OnChange_Event;

public:
	FCsBpProperty_bool() :
		DefaultValue(false),
		Value(false),
		Last_Value(false),
		IsDirty(false)
	{
	}
	~FCsBpProperty_bool() {}

	void SetDefaultValue(const bool& inDefaultValue)
	{
		DefaultValue = inDefaultValue;
	}

	FORCEINLINE void UpdateIsDirty()
	{
		IsDirty = Value != Last_Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE FCsBpProperty_bool& operator=(const bool& B)
	{
		Value = B;
		UpdateIsDirty();
		return *this;
	}

	FORCEINLINE bool operator==(const bool& B) const
	{
		return Value == B;
	}

	FORCEINLINE bool operator!=(const bool& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const bool& inValue)
	{
		Value = inValue;
		UpdateIsDirty();
	}

	FORCEINLINE const bool& Get() { return Value; }

	FORCEINLINE void Clear()
	{
		Last_Value = Value;
		IsDirty = false;
	}

	void ResetValue()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;
	}

	void Reset()
	{
		ResetValue();

		OnChange_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE void MarkDirty() { IsDirty = true; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

#pragma endregion Blueprint Property Types

// Vector Types
#pragma region

// TODO: Look at FIntPoint, FVector ... etc for proper setup

USTRUCT(BlueprintType)
struct CSTYPES_API FCsUint8Point
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	uint8 X; // 8 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	uint8 Y; // 8 bits

	FCsUint8Point()
	{
		Reset();
	}
	~FCsUint8Point(){}

	FORCEINLINE FCsUint8Point& operator=(const FCsUint8Point& B)
	{
		X = B.X;
		Y = B.Y;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8Point& B) const
	{
		return X == B.X && Y == B.Y;
	}

	FORCEINLINE bool operator!=(const FCsUint8Point& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		X = 0;
		Y = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("X=%d Y=%d"), X, Y);
	}

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = 0;

		// The initialization is only successful if the X and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("X="), X) & FParse::Value(*InSourceString, TEXT("Y="), Y);

		return bSuccessful;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // X
			 + 8;// Y
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsUint8MatrixDimension
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	uint8 RowSpan; // 8 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	uint8 ColumnSpan; // 8 bits

	FCsUint8MatrixDimension()
	{
		Reset();
	}

	FCsUint8MatrixDimension(const uint8& InRowSpan, const uint8& InColumnSpan)
	{
		RowSpan	   = InRowSpan;
		ColumnSpan = InColumnSpan;
	}
	~FCsUint8MatrixDimension() {}

	FORCEINLINE FCsUint8MatrixDimension& operator=(const FCsUint8MatrixDimension& B)
	{
		RowSpan	   = B.RowSpan;
		ColumnSpan = B.ColumnSpan;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8MatrixDimension& B) const
	{
		return RowSpan == B.RowSpan && ColumnSpan == B.ColumnSpan;
	}

	FORCEINLINE bool operator!=(const FCsUint8MatrixDimension& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		RowSpan	   = 0;
		ColumnSpan = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("RowSpan=%d ColumnSpan=%d"), RowSpan, ColumnSpan);
	}

	bool InitFromString(const FString& InSourceString)
	{
		RowSpan = ColumnSpan = 0;

		// The initialization is only successful if the RowSpan and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("RowSpan="), RowSpan) & FParse::Value(*InSourceString, TEXT("ColumnSpan="), ColumnSpan);

		return bSuccessful;
	}

	FORCEINLINE void Set(const uint8& InRowSpan, const uint8& InColumnSpan)
	{
		RowSpan    = InRowSpan;
		ColumnSpan = InColumnSpan;
	}

	FORCEINLINE uint8 GetRow(const int32& Index)
	{
		return (Index / RowSpan) % RowSpan;
	}

	FORCEINLINE uint8 GetColumn(const int32& Index)
	{
		return Index % RowSpan;
	}

	FORCEINLINE uint16 GetSize()
	{
		return RowSpan * ColumnSpan;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // RowSpan
			 + 8;// ColumnSpan
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsUint8MatrixCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	uint8 Row; // 8 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	uint8 Column; // 8 bits

	FCsUint8MatrixCoordinate()
	{
		Reset();
	}
	~FCsUint8MatrixCoordinate() {}

	FORCEINLINE FCsUint8MatrixCoordinate& operator=(const FCsUint8MatrixCoordinate& B)
	{
		Row    = B.Row;
		Column = B.Column;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsUint8MatrixCoordinate& B) const
	{
		return Row == B.Row && Column == B.Column;
	}

	FORCEINLINE bool operator!=(const FCsUint8MatrixCoordinate& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Row	   = 0;
		Column = 0;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("Row=%d Column=%d"), Row, Column);
	}

	bool InitFromString(const FString& InSourceString)
	{
		Row = Column = 0;

		// The initialization is only successful if the RowSpan and Y values can all be parsed from the string
		const bool bSuccessful = FParse::Value(*InSourceString, TEXT("Row="), Row) & FParse::Value(*InSourceString, TEXT("Column="), Column);

		return bSuccessful;
	}

	FORCEINLINE void Set(const uint8& InRow, const uint8& InColumn)
	{
		Row    = InRow;
		Column = InColumn;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 8 // Row
			 + 8;// Column
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsVectorFlag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool X; // 1 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool Y; // 1 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool Z; // 1 bits

	FCsVectorFlag()
	{
		Reset();
	}
	~FCsVectorFlag() {}

	FORCEINLINE FCsVectorFlag& operator=(const FCsVectorFlag& B)
	{
		X = B.X;
		Y = B.Y;
		Z = B.Z;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsVectorFlag& B) const
	{
		return X == B.X && Y == B.Y && Z == B.Z;
	}

	FORCEINLINE bool operator!=(const FCsVectorFlag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		X = false;
		Y = false;
		Z = false;
	}
	
	FString ToString() const
	{
		return FString::Printf(TEXT("X=%s Y=%s Z=%s"), (*ToString_Internal(X)), (*ToString_Internal(Y)), (*ToString_Internal(Z)));
	}
	
private:

	const FString& ToString_Internal(const bool& Value) const 
	{
		static const FString True = TEXT("True");
		static const FString False = TEXT("False");
		return Value ? True : False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		X = Y = Z = false;

		// The initialization is only successful if the X, Y and Z values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, TEXT("X="), X) &
								 InitFromString_Internal(InSourceString, TEXT("Y="), Y) &
								 InitFromString_Internal(InSourceString, TEXT("Z="), Z);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool& Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == TEXT("true") || Bool == TEXT("1"))
		{
			Value = true;
			return true;
		}
		if (Bool == TEXT("false") || Bool == TEXT("0"))
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	FORCEINLINE void Set(const bool& InX, const bool& InY, const bool& InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	FORCEINLINE void ApplyLock(FVector3f& V)
	{
		V.X = X ? 0.0f : V.X;
		V.Y = Y ? 0.0f : V.Y;
		V.Z = Z ? 0.0f : V.Z;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 1 // X
			 + 1 // Y
			 + 1;// Z
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

USTRUCT(BlueprintType)
struct CSTYPES_API FCsRotatorFlag
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool Roll; // 1 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool Pitch; // 1 bits

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsTypes|Primitive")
	bool Yaw; // 1 bits

	FCsRotatorFlag()
	{
		Reset();
	}
	~FCsRotatorFlag() {}

	FCsRotatorFlag& operator=(const FCsRotatorFlag& B)
	{
		Roll  = B.Roll;
		Pitch = B.Pitch;
		Yaw   = B.Yaw;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsRotatorFlag& B) const
	{
		return Roll == B.Roll && Pitch == B.Pitch && Yaw == B.Yaw;
	}

	FORCEINLINE bool operator!=(const FCsRotatorFlag& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Reset()
	{
		Roll = false;
		Pitch = false;
		Yaw = false;
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("R=%s P=%s Y=%s"), (*ToString_Internal(Roll)), (*ToString_Internal(Pitch)), (*ToString_Internal(Yaw)));
	}

private:

	const FString& ToString_Internal(const bool& Value) const
	{
		static const FString True = TEXT("True");
		static const FString False = TEXT("False");
		return Value ? True : False;
	}

public:

	bool InitFromString(const FString& InSourceString)
	{
		Roll = Pitch = Yaw = false;

		// The initialization is only successful if the Roll, Pitch and Yaw values can all be parsed from the string
		const bool bSuccessful = InitFromString_Internal(InSourceString, TEXT("R="), Roll) &
								 InitFromString_Internal(InSourceString, TEXT("P="), Pitch) &
								 InitFromString_Internal(InSourceString, TEXT("Y="), Yaw);

		return bSuccessful;
	}

private:

	bool InitFromString_Internal(const FString& InSourceString, const FString& SearchString, bool& Value)
	{
		FString Bool;
		FParse::Value(*InSourceString, *SearchString, Bool);

		Bool = Bool.ToLower();

		if (Bool == TEXT("true") || Bool == TEXT("1"))
		{
			Value = true;
			return true;
		}
		if (Bool == TEXT("false") || Bool == TEXT("0"))
		{
			Value = false;
			return true;
		}
		return false;
	}

public:

	FORCEINLINE void Set(const bool& InRoll, const bool& InPitch, const bool& InYaw)
	{
		Roll = InRoll;
		Pitch = InPitch;
		Yaw = InYaw;
	}

	FORCEINLINE void ApplyLock(FRotator& R)
	{
		R.Roll = Roll ? 0.0f : R.Roll;
		R.Pitch = Pitch ? 0.0f : R.Pitch;
		R.Yaw = Yaw ? 0.0f : R.Yaw;
	}

	FORCEINLINE uint32 GetBits() const
	{
		return 1 // Roll
			 + 1 // Pitch
			 + 1;// Yaw
	}

	FORCEINLINE float GetBytes() const
	{
		return (float)GetBits() / 8.0f;
	}
};

#pragma endregion Vector Types

// FCsBool_Array
#pragma region

USTRUCT(BlueprintType)
struct CSTYPES_API FCsBool_Array
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Primitive")
	TArray<bool> Flags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Primitive")
	bool bAnyTrue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTypes|Primitive")
	bool bAnyFalse;

	FCsBool_Array() :
		Flags(),
		bAnyTrue(false),
		bAnyFalse(false)
	{
	}
};

#pragma endregion FCsBool_Array