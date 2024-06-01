// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"

class UObject;
class UClass;
class UWorld;

namespace NCsValid
{
	namespace NInt
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool GreaterThanChecked(const FString& Context, const int32& A, const FString& AName, const int32& B)
			{
				checkf(A > B, TEXT("%s: %s: %d is NOT > %d."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool GreaterThan(const FString& Context, const int32& A, const FString& AName, const int32& B, void(*Log)(const FString&))
			{
				if (A <= B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %d is NOT > %d."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool GreaterThanOrEqualChecked(const FString& Context, const int32& A, const FString& AName, const int32& B)
			{
				checkf(A >= B, TEXT("%s: %s: %d is NOT >= %d."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool GreaterThanOrEqual(const FString& Context, const int32& A, const FString& AName, const int32& B, void(*Log)(const FString&))
			{
				if (A < B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %d is NOT >= %d."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool GreaterThanAndLessThanOrEqualChecked(const FString& Context, const int32& A, const FString& AName, const int32& B, const int32& C)
			{
				checkf(A >= B && A < C, TEXT("%s: %s is NOT in the range: [%d, %d)."), *Context, *AName, B, C);
				return true;
			}

			FORCEINLINE static bool GreaterThanAndLessThanOrEqual(const FString& Context, const int32& A, const FString& AName, const int32& B, const int32& C, void(*Log)(const FString&))
			{
				if (A < B || A >= C)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT in the range: [%d, %d)."), *Context, *AName, B, C));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool LessThanChecked(const FString& Context, const int32& A, const FString& AName, const int32& B)
			{
				checkf(A < B, TEXT("%s: %s: %d is NOT < %d."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool LessThan(const FString& Context, const int32& A, const FString& AName, const int32& B, void(*Log)(const FString&))
			{
				if (A >= B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %d is NOT < %d."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool LessThanOrEqualChecked(const FString& Context, const int32& A, const FString& AName, const int32& B)
			{
				checkf(A <= B, TEXT("%s: %s: %d is NOT <= %d."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool LessThanOrEqual(const FString& Context, const int32& A, const FString& AName, const int32& B, void(*Log)(const FString&))
			{
				if (A > B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %d is NOT <= %d."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

		};
	}

	namespace NFloat
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool EqualChecked(const FString& Context, const float& A, const FString& AName, const float& B)
			{
				checkf(A == B, TEXT("%s: %s: %f != %f is NOT Valid."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool EqualChecked(const FString& Context, const float& A, const FString& AName, const float& B, const FString& BName)
			{
				checkf(A == B, TEXT("%s: %s: %f != %s: %f is NOT Valid."), *Context, *AName, A, *BName, B);
				return true;
			}

			FORCEINLINE static bool Equal(const FString& Context, const float& A, const FString& AName, const float& B, void(*Log)(const FString&))
			{
				if (A != B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f != %f is NOT Valid."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool Equal(const FString& Context, const float& A, const FString& AName, const float& B, const FString& BName, void(*Log)(const FString&))
			{
				if (A != B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f != %s: %f is NOT Valid."), *Context, *AName, A, *BName, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool NotEqualChecked(const FString& Context, const float& A, const FString& AName, const float& B)
			{
				checkf(A != B, TEXT("%s: %s: %f == %f is NOT Valid."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool NotEqual(const FString& Context, const float& A, const FString& AName, const float& B, void(*Log)(const FString&))
			{
				if (A == B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f == %f is NOT Valid."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool GreaterThanChecked(const FString& Context, const float& A, const FString& AName, const float& B)
			{
				checkf(A > B, TEXT("%s: %s: %f is NOT > %f."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool GreaterThanChecked(const FString& Context, const float& A, const FString& AName, const float& B, const FString& BName)
			{
				checkf(A > B, TEXT("%s: %s: %f is NOT > %s: %f."), *Context, *AName, A, *BName, B);
				return true;
			}

			FORCEINLINE static bool GreaterThan(const FString& Context, const float& A, const FString& AName, const float& B, void(*Log)(const FString&))
			{
				if (A <= B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f is NOT > %f."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool GreaterThan(const FString& Context, const float& A, const FString& AName, const float& B, const FString& BName, void(*Log)(const FString&))
			{
				if (A <= B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f is NOT > %s: %f."), *Context, *AName, A, *BName, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool GreaterThanOrEqualChecked(const FString& Context, const float& A, const FString& AName, const float& B)
			{
				checkf(A >= B, TEXT("%s: %s: %f is NOT >= %f."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool GreaterThanOrEqual(const FString& Context, const float& A, const FString& AName, const float& B, void(*Log)(const FString&))
			{
				if (A < B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f is NOT >= %f."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool LessThanChecked(const FString& Context, const float& A, const FString& AName, const float& B)
			{
				checkf(A < B, TEXT("%s: %s: %f is NOT < %f."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool LessThan(const FString& Context, const float& A, const FString& AName, const float& B, void(*Log)(const FString&))
			{
				if (A >= B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f is NOT < %f."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool LessThanOrEqualChecked(const FString& Context, const float& A, const FString& AName, const float& B)
			{
				checkf(A <= B, TEXT("%s: %s: %f is NOT <= %f."), *Context, *AName, A, B);
				return true;
			}

			FORCEINLINE static bool LessThanOrEqual(const FString& Context, const float& A, const FString& AName, const float& B, void(*Log)(const FString&))
			{
				if (A > B)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %f is NOT <= %f."), *Context, *AName, A, B));
					return false;
				}
				return true;
			}
		};

		namespace NCompare
		{
			struct CSVALID_API FLibrary final
			{
			public:

				FORCEINLINE static bool LessThanChecked(const FString& Context, const float& A, const FString& AName, const float& B, const FString& BName)
				{
					checkf(A < B, TEXT("%s: %s: %f is NOT < %s: %f."), *Context, *AName, A, *BName, B);
					return true;
				}

				FORCEINLINE static bool LessThan(const FString& Context, const float& A, const FString& AName, const float& B, const FString& BName, void(*Log)(const FString&))
				{
					if (A >= B)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s: %f is NOT < %s: %f."), *Context, *AName, A,*BName,  B));
						return false;
					}
					return true;
				}
			};
		}
	}

	namespace NName
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool NoneChecked(const FString& Context, const FName& A, const FString& AName)
			{
				checkf(A != NAME_None, TEXT("%s: %s: None is NOT Valid."), *Context, *AName);
				return true;
			}

			FORCEINLINE static bool None(const FString& Context, const FName& A, const FString& AName, void(*Log)(const FString&))
			{
				if (A == NAME_None)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: None is NOT Valid."), *Context, *AName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NString
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool EmptyChecked(const FString& Context, const FString& A, const FString& AName)
			{
				checkf(!A.IsEmpty(), TEXT("%s: %s is EMPTY."), *Context, *AName);
				return true;
			}

			FORCEINLINE static bool Empty(const FString& Context, const FString& A, const FString& AName, void(*Log)(const FString&))
			{
				if (A.IsEmpty())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *AName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NText
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool EmptyChecked(const FString& Context, const FText& A, const FString& AName)
			{
				checkf(!A.IsEmpty(), TEXT("%s: %s is EMPTY."), *Context, *AName);
				return true;
			}

			FORCEINLINE static bool Empty(const FString& Context, const FText& A, const FString& AName, void(*Log)(const FString&))
			{
				if (A.IsEmpty())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *AName));
					return false;
				}
				return true;
			}
		};
	}
		
	namespace NEnum
	{
		struct CSVALID_API FLibrary final
		{
		public:

			template<typename EnumMapType, typename EnumType>
			FORCEINLINE static bool IsValid(const FString& Context, const EnumType& Enum, const FString& EnumName, void(*Log)(const FString&))
			{
				if (!EnumMapType::Get().IsValidEnum(Enum))
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s is NOT Valid."), *Context, *EnumName, EnumMapType::Get().ToChar(Enum)));
					return false;
				}
				return true;
			}

			template<typename EnumMapType, typename EnumType>
			FORCEINLINE static bool IsValidChecked(const FString& Context, const TArray<EnumType>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const EnumType& Enum = Array[I];

					checkf(EnumMapType::Get().IsValidEnum(Enum), TEXT("%s: %s[%d] = %s is NOT Valid."), *Context, *ArrayName, I, EnumMapType::Get().ToChar(Enum));
				}
				return true;
			}

			template<typename EnumMapType, typename EnumType>
			FORCEINLINE static bool IsValid(const FString& Context, const TArray<EnumType>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const EnumType& Enum = Array[I];

					if (!EnumMapType::Get().IsValidEnum(Enum))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] = %s is NOT Valid."), *Context, *ArrayName, I, EnumMapType::Get().ToChar(Enum)));
						return false;
					}
				}
				return true;
			}
		};

		namespace NStruct
		{
			struct CSVALID_API FLibrary final
			{
			public:

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsValidChecked(const FString& Context, const TArray<EnumType>& Array, const FString& ArrayName)
				{
					const int32 Count = Array.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const EnumType& Enum = Array[I];

						checkf(EnumMapType::Get().IsValidEnum(Enum), TEXT("%s: %s[%d] = %s is NOT Valid."), *Context, *ArrayName, I, Enum.ToChar());
					}
					return true;
				}

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsValid(const FString& Context, const TArray<EnumType>& Array, const FString& ArrayName, void(*Log)(const FString&))
				{
					const int32 Count = Array.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						const EnumType& Enum = Array[I];

						if (!EnumMapType::Get().IsValidEnum(Enum))
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: %s[%d] = %s is NOT Valid."), *Context, *ArrayName, I, Enum.ToChar()));
							return false;
						}
					}
					return true;
				}

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsValidChecked(const FString& Context, const TSet<EnumType>& Set, const FString& SetName)
				{
					for (const EnumType& Enum : Set)
					{
						checkf(EnumMapType::Get().IsValidEnum(Enum), TEXT("%s: Element: %s in %s is NOT Valid."), *Context, Enum.ToChar(), *SetName);
					}
					return true;
				}

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsValid(const FString& Context, const TSet<EnumType>& Set, const FString& SetName, void(*Log)(const FString&))
				{
					for (const EnumType& Enum : Set)
					{
						if (!EnumMapType::Get().IsValidEnum(Enum))
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: Element: %s in %s is NOT Valid."), *Context, Enum.ToChar(), *SetName));
							return false;
						}
					}
					return true;
				}

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsUniqueChecked(const FString& Context, const TSet<EnumType>& Set, const FString& SetName)
				{
					static TSet<EnumType> Enums;
					Enums.Reset();

					for (const EnumType& Enum : Set)
					{
						checkf(EnumMapType::Get().IsValidEnum(Enum), TEXT("%s: Element: %s in %s is NOT Valid."), *Context, Enum.ToChar(), *SetName);

						Enums.Add(Enum);
					}
					checkf(Enums.Num() == Set.Num(), TEXT("%s: Not all elments in %s are unique."), *Context, *SetName);
					return true;
				}

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsUnique(const FString& Context, const TSet<EnumType>& Set, const FString& SetName, void(*Log)(const FString&))
				{
					static TSet<EnumType> Enums;
					Enums.Reset();

					for (const EnumType& Enum : Set)
					{
						if (!EnumMapType::Get().IsValidEnum(Enum))
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: Element: %s in %s is NOT Valid."), *Context, Enum.ToChar(), *SetName));
							return false;
						}
						Enums.Add(Enum);
					}

					if (Enums.Num() != Set.Num())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: Not all elments in %s are unique."), *Context, *SetName));
						return false;
					}
					return true;
				}

				template<typename EnumMapType, typename EnumType>
				FORCEINLINE static bool IsValid(const FString& Context, const EnumType& Enum, const FString& EnumName, void(*Log)(const FString&))
				{
					if (!EnumMapType::Get().IsValidEnum(Enum))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s: %s is NOT Valid."), *Context, *EnumName, Enum.ToChar()));
						return false;
					}
					return true;
				}
			};
		}
	}

	namespace NVector
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool IsZeroChecked(const FString& Context, const FVector3f& V, const FString& VName)
			{
				checkf(V != FVector3f::ZeroVector, TEXT("%s: %s == (0.0f, 0.0f, 0.0f) or ZeroVector is NOT Valid."), *Context, *VName);
				return true;
			}

			FORCEINLINE static bool IsZero(const FString& Context, const FVector3f& V, const FString& VName, void(*Log)(const FString&))
			{
				if (V == FVector3f::ZeroVector)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s == (0.0f, 0.0f, 0.0f) or ZeroVector is NOT Valid."), *Context, *VName));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool ComponentsGreaterThanChecked(const FString& Context, const FVector3f& V, const FString& VName, const float& A, const FString& AName)
			{
				checkf(V.X > A, TEXT("%s: %s.X: %f is NOT > %s: %f."), *Context, *VName, V.X, *AName, A);
				checkf(V.Y > A, TEXT("%s: %s.Y: %f is NOT > %s: %f."), *Context, *VName, V.Y, *AName, A);
				checkf(V.Z > A, TEXT("%s: %s.Z: %f is NOT > %s: %f."), *Context, *VName, V.Z, *AName, A);
				return true;
			}

			FORCEINLINE static bool ComponentsGreaterThan(const FString& Context, const FVector3f& V, const FString& VName, const float& A, const FString& AName, void(*Log)(const FString&))
			{
				if (V.X <= A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.X: %f is NOT > %s: %f."), *Context, *VName, V.X, *AName, A));
					return false;
				}
				if (V.Y <= A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Y: %f is NOT > %s: %f."), *Context, *VName, V.Y, *AName, A));
					return false;
				}
				if (V.Z <= A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Z: %f is NOT > %s: %f."), *Context, *VName, V.Z, *AName, A));
					return false;
				}
				return true;
			}

			FORCEINLINE static bool ComponentsGreaterThanOrEqualChecked(const FString& Context, const FVector3f& V, const FString& VName, const float& A, const FString& AName)
			{
				checkf(V.X >= A, TEXT("%s: %s.X: %f is NOT >= %s: %f."), *Context, *VName, V.X, *AName, A);
				checkf(V.Y >= A, TEXT("%s: %s.Y: %f is NOT >= %s: %f."), *Context, *VName, V.Y, *AName, A);
				checkf(V.Z >= A, TEXT("%s: %s.Z: %f is NOT >= %s: %f."), *Context, *VName, V.Z, *AName, A);
				return true;
			}

			FORCEINLINE static bool ComponentsGreaterThanOrEqual(const FString& Context, const FVector3f& V, const FString& VName, const float& A, const FString& AName, void(*Log)(const FString&))
			{
				if (V.X < A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.X: %f is NOT >= %s: %f."), *Context, *VName, V.X, *AName, A));
					return false;
				}
				if (V.Y < A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Y: %f is NOT >= %s: %f."), *Context, *VName, V.Y, *AName, A));
					return false;
				}
				if (V.Z < A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Z: %f is NOT >= %s: %f."), *Context, *VName, V.Z, *AName, A));
					return false;
				}
				return true;
			}
		};
	}

	namespace NArray
	{
		struct CSVALID_API FLibrary final
		{
			template<typename ValueType>
			FORCEINLINE static bool EmptyChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName)
			{
				checkf(Array.Num() > 0, TEXT("%s: %s is EMPTY."), *Context, *ArrayName);
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool EmptyChecked(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				checkf(Array.Num() > 0, TEXT("%s: %s is EMPTY."), *Context, *ArrayName);
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool Empty(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				if (Array.Num() == 0)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *ArrayName));
					return false;
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool Empty(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				if (Array.Num() == 0)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *ArrayName));
					return false;
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool SizeChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() == Size, TEXT("%s: %s.Num(): %d != %d."), *Context, *ArrayName, Array.Num(), Size);
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool SizeChecked(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() == Size, TEXT("%s: %s.Num(): %d != %d."), *Context, *ArrayName, Array.Num(), Size);
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool Size(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() != Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num(): %d != %d."), *Context, *ArrayName, Array.Num(), Size));
					return false;
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool Size(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() != Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num(): %d != %d."), *Context, *ArrayName, Array.Num(), Size));
					return false;
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool GreaterThanOrEqualSizeChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() >= Size, TEXT("%s: %s.Num(): %d < %d."), *Context, *ArrayName, Array.Num(), Size);
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool GreaterThanOrEqualSizeChecked(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() >= Size, TEXT("%s: %s.Num(): %d < %d."), *Context, *ArrayName, Array.Num(), Size);
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool GreaterThanOrEqualSize(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() < Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num(): %d < %d."), *Context, *ArrayName, Array.Num(), Size));
					return false;
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool GreaterThanOrEqualSize(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() < Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num(): %d < %d."), *Context, *ArrayName, Array.Num(), Size));
					return false;
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool LessThanOrEqualSizeChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() <= Size, TEXT("%s: %s.Num(): %d > %d."), *Context, *ArrayName, Array.Num(), Size);
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool LessThanOrEqualSizeChecked(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() <= Size, TEXT("%s: %s.Num(): %d > %d."), *Context, *ArrayName, Array.Num(), Size);
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool LessThanOrEqualSize(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() > Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num(): %d > %d."), *Context, *ArrayName, Array.Num(), Size));
					return false;
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool LessThanOrEqualSize(const FString& Context, const TArray<ValueType, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() > Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num(): %d > %d."), *Context, *ArrayName, Array.Num(), Size));
					return false;
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<ValueType*>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(Array[I], TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<ValueType*, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(Array[I], TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<ValueType*>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (!Array[I])
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<ValueType*, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (!Array[I])
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<TSubclassOf<ValueType>>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<ValueType>& O = Array[I];

					checkf(O.Get(), TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<TSubclassOf<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<ValueType>& O = Array[I];

					checkf(O.Get(), TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<TSubclassOf<ValueType>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<ValueType>& O = Array[I];

					if (!O.Get())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<TSubclassOf<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TSubclassOf<ValueType>& O = Array[I];

					if (!O.Get())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<TWeakObjectPtr<ValueType>>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TWeakObjectPtr<ValueType>& O = Array[I];

					checkf(O.IsValid() && O.Get(), TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<TWeakObjectPtr<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TWeakObjectPtr<ValueType>& O = Array[I];

					checkf(O.IsValid() && O.Get(), TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<TWeakObjectPtr<ValueType>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TWeakObjectPtr<ValueType>& O = Array[I];

					if (!O.IsValid() || !O.Get())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<TWeakObjectPtr<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					const TWeakObjectPtr<ValueType>& O = Array[I];

					if (!O.IsValid() || !O.Get())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyPendingKillChecked(const FString& Context, const TArray<ValueType*>& Array, const FString& ArrayName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(IsValid(Array[I]), TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyPendingKillChecked(const FString& Context, const TArray<ValueType*, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(IsValid(Array[I]), TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyPendingKill(const FString& Context, const TArray<ValueType*>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (!IsValid(Array[I]))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyPendingKill(const FString& Context, const TArray<ValueType*, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (!IsValid(Array[I]))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyPendingKillChecked(const FString& Context, const TArray<TObjectPtr<ValueType>>& Array, const FString& ArrayName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ValueType* V = Array[I].Get();

					checkf(IsValid(V), TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyPendingKillChecked(const FString& Context, const TArray<TObjectPtr<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ValueType* V = Array[I].Get();

					checkf(IsValid(V), TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyPendingKill(const FString& Context, const TArray<TObjectPtr<ValueType>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ValueType* V = Array[I].Get();

					if (!IsValid(V))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyPendingKill(const FString& Context, const TArray<TObjectPtr<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					ValueType* V = Array[I].Get();

					if (!IsValid(V))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NULL or Pending Kill."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNotValidChecked(const FString& Context, const TArray<TSoftObjectPtr<ValueType>>& Array, const FString& ArrayName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(Array[I].ToSoftObjectPath().IsValid(), TEXT("%s: %s[%d] is NOT Valid."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNotValidChecked(const FString& Context, const TArray<TSoftObjectPtr<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyNotValidChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(Array[I].ToSoftObjectPath().IsValid(), TEXT("%s: %s[%d] is NOT Valid."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyNotValid(const FString& Context, const TArray<TSoftObjectPtr<ValueType>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyNotValid: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (!Array[I].ToSoftObjectPath().IsValid())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NOT Valid."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType, uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNotValid(const FString& Context, const TArray<TSoftObjectPtr<ValueType>, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NArray::IsAnyNotValid: ValueType is NOT of type: UObject.");

				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (!Array[I].ToSoftObjectPath().IsValid())
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is NOT Valid."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			FORCEINLINE static bool IsAnyNoneChecked(const FString& Context, const TArray<FName>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(Array[I] != NAME_None, TEXT("%s: %s[%d] is None."), *Context, *ArrayName, I);
				}
				return true;
			}

			template<uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNoneChecked(const FString& Context, const TArray<FName, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName)
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					checkf(Array[I] != NAME_None, TEXT("%s: %s[%d] is None."), *Context, *ArrayName, I);
				}
				return true;
			}

			FORCEINLINE static bool IsAnyNone(const FString& Context, const TArray<FName>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (Array[I] == NAME_None)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is None."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<uint32 AllocatedSize>
			FORCEINLINE static bool IsAnyNone(const FString& Context, const TArray<FName, TFixedAllocator<AllocatedSize>>& Array, const FString& ArrayName, void(*Log)(const FString&))
			{
				const int32 Count = Array.Num();

				for (int32 I = 0; I < Count; ++I)
				{
					if (Array[I] == NAME_None)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s[%d] is None."), *Context, *ArrayName, I));
						return false;
					}
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool ContainsChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const ValueType& Value, const FString& ValueName)
			{
				check(EmptyChecked<ValueType>(Context, Array, ArrayName));

				for (const ValueType& A : Array)
				{
					if (A == Value)
						return true;
				}
				checkf(0, TEXT("%s: %s does NOT contain %s."), *Context, *ArrayName, *ValueName);
				return false;
			}
		};

		namespace N2D
		{
			struct CSVALID_API FLibrary final
			{
				template<typename ValueType>
				FORCEINLINE static bool EmptyChecked(const FString& Context, const TArray<TArray<ValueType>>& Array, const FString& ArrayName)
				{
					checkf(Array.Num() > 0, TEXT("%s: %s is EMPTY."), *Context, *ArrayName);

					int32 Count = Array.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						checkf(Array[I].Num() > 0, TEXT("%s: %s[%d] is EMPTY."), *Context, *ArrayName, I);
					}
					return true;
				}

				template<typename ValueType>
				FORCEINLINE static bool Empty(const FString& Context, const TArray<TArray<ValueType>>& Array, const FString& ArrayName, void(*Log)(const FString&))
				{
					if (Array.Num() == 0)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *ArrayName));
						return false;
					}

					int32 Count = Array.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						if (Array[I].Num() == 0)
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: %s[%d] is EMPTY."), *Context, *ArrayName, I));
							return false;
						}
					}
					return true;
				}

				template<typename ValueType>
				FORCEINLINE static bool EmptyChecked(const FString& Context, const TArray<TArray<ValueType*>>& Array, const FString& ArrayName)
				{
					checkf(Array.Num() > 0, TEXT("%s: %s is EMPTY."), *Context, *ArrayName);

					int32 Count = Array.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						checkf(Array[I].Num() > 0, TEXT("%s: %s[%d] is EMPTY."), *Context, *ArrayName, I);
					}
					return true;
				}

				template<typename ValueType>
				FORCEINLINE static bool Empty(const FString& Context, const TArray<TArray<ValueType*>>& Array, const FString& ArrayName, void(*Log)(const FString&))
				{
					if (Array.Num() == 0)
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *ArrayName));
						return false;
					}

					int32 Count = Array.Num();

					for (int32 I = 0; I < Count; ++I)
					{
						if (Array[I].Num() == 0)
						{
							if (Log)
								Log(FString::Printf(TEXT("%s: %s[%d] is EMPTY."), *Context, *ArrayName, I));
							return false;
						}
					}
					return true;
				}

				template<typename ValueType>
				FORCEINLINE static bool IsAnyNullChecked(const FString& Context, const TArray<TArray<ValueType*>>& Array, const FString& ArrayName)
				{
					const int32 IMax = Array.Num();

					for (int32 I = 0; I < IMax; ++I)
					{
						const TArray<ValueType*>& Arr = Array[I];

						const int32 JMax = Array[I].Num();

						for (int32 J = 0; J < JMax; ++J)
						{
							checkf(Array[I][J], TEXT("%s: %s[%d][%d] is NULL."), *Context, *ArrayName, I, J);
						}
					}
					return true;
				}

				template<typename ValueType>
				FORCEINLINE static bool IsAnyNull(const FString& Context, const TArray<TArray<ValueType*>>& Array, const FString& ArrayName, void(*Log)(const FString&))
				{
					const int32 IMax = Array.Num();

					for (int32 I = 0; I < IMax; ++I)
					{
						const TArray<ValueType*>& Arr = Array[I];

						const int32 JMax = Array[I].Num();

						for (int32 J = 0; J < JMax; ++J)
						{
							if (!Array[I][J])
							{
								if (Log)
									Log(FString::Printf(TEXT("%s: %s[%d][%d] is NULL."), *Context, *ArrayName, I, J));
								return false;
							}
						}
					}
					return true;
				}
			};
		}
	}

	namespace NSet
	{
		struct CSVALID_API FLibrary final
		{
			template<typename ValueType>
			FORCEINLINE static bool EmptyChecked(const FString& Context, const TSet<ValueType>& Set, const FString& SetName)
			{
				checkf(Set.Num() > 0, TEXT("%s: %s is EMPTY."), *Context, *SetName);
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool Empty(const FString& Context, const TSet<ValueType>& Set, const FString& SetName, void(*Log)(const FString&))
			{
				if (Set.Num() == 0)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is EMPTY."), *Context, *SetName));
					return false;
				}
				return true;
			}

						template<typename ValueType>
			FORCEINLINE static bool IsAnyPendingKillChecked(const FString& Context, const TSet<ValueType*>& Set, const FString& SetName)
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NSet::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				for (ValueType* Value : Set)
				{
					checkf(IsValid(Value), TEXT("%s: Value in %s is NULL or Pending Kill."), *Context, *SetName);
				}
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool IsAnyPendingKill(const FString& Context, const TSet<ValueType*>& Set, const FString& SetName, void(*Log)(const FString&))
			{
				static_assert(std::is_base_of<UObject, ValueType>(), "NCsValid::NSet::IsAnyPendingKillChecked: ValueType is NOT of type: UObject.");

				const int32 Count = Set.Num();

				for (ValueType* Value : Set)
				{
					if (!IsValid(Value))
					{
						if (Log)
							Log(FString::Printf(TEXT("%s: Value in %s is NULL or Pending Kill."), *Context, *SetName));
						return false;
					}
				}
				return true;
			}
		};
	}

	namespace NPtr
	{
		struct CSVALID_API FLibrary final
		{
			FORCEINLINE static bool NullChecked(const FString& Context, const void* Ptr, const FString& PtrName)
			{
				checkf(Ptr, TEXT("%s: %s is NULL."), *Context, *PtrName);
				return true;
			}

			FORCEINLINE static bool Null(const FString& Context, const void* Ptr, const FString& PtrName, void(*Log)(const FString&))
			{
				if (!Ptr)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *PtrName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NObject
	{
		struct CSVALID_API FLibrary final
		{
			FORCEINLINE static bool IsPendingKillChecked(const FString& Context, const UObject* A, const FString& AName)
			{
				checkf(A, TEXT("%s: %s is NULL."), *Context, *AName);
				checkf(IsValid(A), TEXT("%s: %s Is Pending Kill."), *Context, *AName);
				return true;
			}

			FORCEINLINE static bool IsPendingKill(const FString& Context, const UObject* A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return false;
				}

				if (!IsValid(A))
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s Is Pending Kill."), *Context, *AName));
					return false;
				}
				return true;
			}

			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static bool IsClassOf(const FString& Context, const ClassType* A, const FString& AName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return false;

				const OtherClassType* Other = Cast<OtherClassType>(A);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName())));
					return false;
				}
				return true;
			}

			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static bool IsClassOfChecked(const FString& Context, const ClassType* A, const FString& AName)
			{
				check(IsPendingKillChecked(Context, A, AName));

				const OtherClassType* Other = Cast<OtherClassType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName()));
				return true;
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static bool Implements(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return false;

				const InterfaceType* Other = Cast<InterfaceType>(A);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName));
					return false;
				}
				return true;
			}
			
			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static OtherClassType* CastTo(const FString& Context, ClassType* A, const FString& AName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return nullptr;

				OtherClassType* Other = Cast<OtherClassType>(A);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName())));
					return nullptr;
				}
				return Other;
			}

			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static const OtherClassType* CastTo(const FString& Context, const ClassType* A, const FString& AName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return nullptr;

				const OtherClassType* Other = Cast<OtherClassType>(A);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName())));
					return nullptr;
				}
				return Other;
			}

			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static OtherClassType* CastToChecked(const FString& Context, ClassType* A, const FString& AName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsPendingKillChecked(Context, A, AName));

				OtherClassType* Other = Cast<OtherClassType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName()));
				return Other;
			#else
				return Cast<OtherClassType>(A);
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static const OtherClassType* CastToChecked(const FString& Context, const ClassType* A, const FString& AName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsPendingKillChecked(Context, A, AName));

				const OtherClassType* Other = Cast<OtherClassType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName()));
				return Other;
			#else
				return Cast<OtherClassType>(A);
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static InterfaceType* InterfaceCast(const FString& Context, ClassType* A, const FString& AName, const FString& InterfaceName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return nullptr;

				InterfaceType* Other = Cast<InterfaceType>(A);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName));
					return nullptr;
				}
				return Other;
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static const InterfaceType* InterfaceCast(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return nullptr;

				const InterfaceType* Other = Cast<InterfaceType>(A);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName));
					return nullptr;
				}
				return Other;
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static InterfaceType* InterfaceCastChecked(const FString& Context, ClassType* A, const FString& AName, const FString& InterfaceName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsPendingKillChecked(Context, A, AName));

				InterfaceType* Other = Cast<InterfaceType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName);
				return Other;
			#else
				return Cast<InterfaceType>(A);
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static const InterfaceType* InterfaceCastChecked(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsPendingKillChecked(Context, A, AName));

				const InterfaceType* Other = Cast<InterfaceType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName);
				return Other;
			#else
				return Cast<InterfaceType>(A);
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* NewChecked(const FString& Context, UObject* Outer, const FString& OuterName, UClass* Class, const FString& ClassName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsPendingKillChecked(Context, Outer, OuterName));
				checkf(Class, TEXT("%s: %s is NULL."), *Context, *ClassName);

				ObjectType* O = NewObject<ObjectType>(Outer, Class);

				checkf(O, TEXT("%s: Failed to create Object from Class: %s."), *Context, *(Class->GetName()));			
				return O;
			#else
				return NewObject<ObjectType>(Outer, Class);
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* NewChecked(const FString& Context, UObject* Outer, const FString& OuterName, TSubclassOf<ObjectType>& Class, const FString& ClassName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsPendingKillChecked(Context, Outer, OuterName));
				checkf(Class.Get(), TEXT("%s: %s is NULL."), *Context, *ClassName);

				ObjectType* O = NewObject<ObjectType>(Outer, Class);

				checkf(O, TEXT("%s: Failed to create Object from Class: %s."), *Context, *(Class->GetName()));
				return O;
			#else
				return NewObject<ObjectType>(Outer, Class);
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ClassType, typename UInterfaceType>
			FORCEINLINE static bool ImplementsInterfaceChecked(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName)
			{
				check(IsPendingKillChecked(Context, A, AName));

				UClass* C = A->GetClass();

				checkf(C, TEXT("%s: %s's Class is NULL."), *Context, *AName);
				checkf(C->ImplementsInterface(UInterfaceType::StaticClass()), TEXT("%s: %s's Class: %s does NOT implement the interface: %s."), *Context, *AName, *(C->GetName()), *InterfaceName);
				return true;
			}

			template<typename ClassType, typename UInterfaceType>
			FORCEINLINE static bool ImplementsInterface(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName, void(*Log)(const FString&))
			{
				if (!IsPendingKill(Context, A, AName, Log))
					return false;

				UClass* C = A->GetClass();

				if (!C)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s's Class is NULL."), *Context, *AName));
					return false;
				}

				if (!C->ImplementsInterface(UInterfaceType::StaticClass()))
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s's Class: %s does NOT implement the interface: %s."), *Context, *AName, *(C->GetName()), *InterfaceName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NWeakObjectPtr
	{
		struct CSVALID_API FLibrary final
		{
			template<typename ObjectType>
			FORCEINLINE static bool NullChecked(const FString& Context, const TWeakObjectPtr<ObjectType>& Ptr, const FString& PtrName)
			{
				checkf(Ptr.IsValid() && Ptr.Get(), TEXT("%s: %s is NULL."), *Context, *PtrName);
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static bool Null(const FString& Context, const TWeakObjectPtr<ObjectType>& Ptr, const FString& PtrName, void(*Log)(const FString&))
			{
				if (!Ptr.IsValid() || !Ptr.Get())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *PtrName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NObjectPtr
	{
		struct CSVALID_API FLibrary final
		{
			template<typename ObjectType>
			FORCEINLINE static bool NullChecked(const FString& Context, const TObjectPtr<ObjectType>& Ptr, const FString& PtrName)
			{
				checkf(Ptr.IsResolved(), TEXT("%s: %s has NOT been resolved."), *Context, *PtrName);
				checkf(IsValid(Ptr.Get()), TEXT("%s: %s is NULL or Pending Kill."), *Context, *PtrName);
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static bool NullChecked(const FString& Context, const TObjectPtr<const ObjectType>& Ptr, const FString& PtrName)
			{
				checkf(Ptr.IsResolved(), TEXT("%s: %s has NOT been resolved."), *Context, *PtrName);
				checkf(IsValid(Ptr.Get()), TEXT("%s: %s is NULL or Pending Kill."), *Context, *PtrName);
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static bool Null(const FString& Context, const TObjectPtr<ObjectType>& Ptr, const FString& PtrName, void(*Log)(const FString&))
			{
				if (!Ptr.IsResolved())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s has NOT been resolved."), *Context, *PtrName));
					return false;
				}

				if (!IsValid(Ptr.Get()))
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL or Pending Kill."), *Context, *PtrName));
					return false;
				}
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static bool Null(const FString& Context, const TObjectPtr<const ObjectType>& Ptr, const FString& PtrName, void(*Log)(const FString&))
			{
				if (!Ptr.IsResolved())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s has NOT been resolved."), *Context, *PtrName));
					return false;
				}

				if (!IsValid(Ptr.Get()))
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL or Pending Kill."), *Context, *PtrName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NSoftObjectPtr
	{
		struct CSVALID_API FLibrary final
		{
		public:

			template<typename ObjectType>
			FORCEINLINE static bool IsValidChecked(const FString& Context, const TSoftObjectPtr<ObjectType>& A, const FString& AName)
			{
				checkf(A.ToSoftObjectPath().IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *AName);
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static bool IsValid(const FString& Context, const TSoftObjectPtr<ObjectType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A.ToSoftObjectPath().IsValid())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *AName));
					return false;
				}
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* GetChecked(const FString& Context, const TSoftObjectPtr<ObjectType>& A, const FString& AName)
			{
				check(IsValidChecked<ObjectType>(Context, A, AName));

				ObjectType* O = A.Get();

				checkf(O, TEXT("%s: %s is NULL. Path @ %s has NOT been Loaded."), *Context, *AName, *(A.ToSoftObjectPath().ToString()));
				return O;
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* Get(const FString& Context, const TSoftObjectPtr<ObjectType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!IsValid<ObjectType>(Context, A, AName, Log))
					return nullptr;

				ObjectType* O = A.Get();

				if (!O)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL. Path @ %s has NOT been Loaded."), *Context, *AName, *(A.ToSoftObjectPath().ToString())));
					return nullptr;
				}
				return O;
			}
		};
	}

	namespace NSoftClassPtr
	{
		struct CSVALID_API FLibrary final
		{
		public:

			template<typename ClassType>
			FORCEINLINE static bool IsValidChecked(const FString& Context, const TSoftClassPtr<ClassType>& A, const FString& AName)
			{
				checkf(A.ToSoftObjectPath().IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *AName);
				return true;
			}

			template<typename ClassType>
			FORCEINLINE static bool IsValid(const FString& Context, const TSoftClassPtr<ClassType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A.ToSoftObjectPath().IsValid())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *AName));
					return false;
				}
				return true;
			}

			template<typename ClassType>
			FORCEINLINE static UClass* GetChecked(const FString& Context, const TSoftClassPtr<ClassType>& A, const FString& AName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsValidChecked<ClassType>(Context, A, AName));

				UClass* O = A.Get();

				checkf(O, TEXT("%s: %s is NULL. Path @ %s has NOT been Loaded."), *Context, *AName, *(A.ToSoftObjectPath().ToString()));
				return O;
			#else
				return A.Get();
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ClassType>
			FORCEINLINE static UClass* Get(const FString& Context, const TSoftClassPtr<ClassType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!IsValid<ClassType>(Context, A, AName, Log))
					return nullptr;

				UClass* O = A.Get();

				if (!O)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL. Path @ %s has NOT been Loaded."), *Context, *AName, *(A.ToSoftObjectPath().ToString())));
					return nullptr;
				}
				return O;
			}

			template<typename ClassType>
			FORCEINLINE static UClass* LoadChecked(const FString& Context, const TSoftClassPtr<ClassType>& A, const FString& AName)
			{
			#if !UE_BUILD_SHIPPING
				check(IsValidChecked<ClassType>(Context, A, AName));

				UClass* O = A.LoadSynchronous();

				checkf(O, TEXT("%s: Failed to Load %s @ %s.."), *Context, *AName, *(A.ToSoftObjectPath().ToString()));
				return O;
			#else
				return A.LoadSynchronous();
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename ClassType>
			FORCEINLINE static UClass* Load(const FString& Context, const TSoftClassPtr<ClassType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!IsValid<ClassType>(Context, A, AName, Log))
					return nullptr;

				UClass* O = A.LoadSynchronous();

				if (!O)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Failed to Load %s @ %s."), *Context, *AName, *(A.ToSoftObjectPath().ToString())));
					return nullptr;
				}
				return O;
			}
		};
	}

	namespace NSoftObjectPath
	{
		struct CSVALID_API FLibrary final
		{
		public:

			FORCEINLINE static bool IsValidChecked(const FString& Context, const FSoftObjectPath& A, const FString& AName)
			{
				checkf(A.IsValid(), TEXT("%s: %s is NOT Valid."), *Context, *AName);
				return true;
			}

			FORCEINLINE static bool IsValid(const FString& Context, const FSoftObjectPath& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A.IsValid())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *AName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NSubclassOf
	{
		struct CSVALID_API FLibrary final
		{
		public:

			template<typename ObjectType>
			FORCEINLINE static bool NullChecked(const FString& Context, const TSubclassOf<ObjectType>& A, const FString& AName)
			{
				checkf(A.Get(), TEXT("%s: %s is NULL."), *Context, *AName);
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static bool Null(const FString& Context, const TSubclassOf<ObjectType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A.Get())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *AName));
					return false;
				}
				return true;
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* GetChecked(const FString& Context, const TSubclassOf<ObjectType>& A, const FString& AName)
			{
				checkf(A.Get(), TEXT("%s: %s is NULL."), *Context, *AName);
				return A.Get();
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* Get(const FString& Context, const TSubclassOf<ObjectType>& A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A.Get())
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT Valid."), *Context, *AName));
					return false;
				}
				return A.Get();
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* GetDefaultObjectChecked(const FString& Context, const TSubclassOf<ObjectType>& A, const FString& AName)
			{
			#if !UE_BUILD_SHIPPING
				checkf(A.Get(), TEXT("%s: %s is NULL."), *Context, *AName);

				UObject* O = A.GetDefaultObject();

				checkf(O, TEXT("%s: Failed to Get DefaultObject from: %s with Class: %s."), *Context, *AName, *(A.Get()->GetName()));

				ObjectType* DOb = Cast<ObjectType>(O);

				checkf(DOb, TEXT("%s: DefaultObject: %s is NOT of type: %s."), *Context, *AName, *(ObjectType::StaticClass()->GetName()));
				return DOb;
			#else
				return Cast<ObjectType>(A.GetDefaultObject());
			#endif // #if !UE_BUILD_SHIPPING
			}
		};
	}

	namespace NActor
	{
		struct CSVALID_API FLibrary final
		{
		public:

			/*template<typename ActorType>
			FORCEINLINE static ActorType* SpawnChecked(const FString& Context, UWorld* World, UClass* Class, const FString& ClassName)
			{
				checkf(World, TEXT("%s: World is NULL."), *Context);
				checkf(Class, TEXT("%s: %s is NULL."), *Context, *ClassName);

				ActorType* A = World->SpawnActor<ActorType>(Class);

				checkf(A, TEXT("%s: Failed to Spawn Actor of type: %s from %s of type: %s."), *Context, *(ActorType::StaticClass()->GetName()), *ClassName, *(Class->GetName()));
				return A;
			}*/
		};
	}

	namespace NInterface
	{
		struct CSVALID_API FLibrary final
		{
		public:

			template<typename InterfaceType>
			FORCEINLINE static UObject* _getUObjectChecked(const FString& Context, const InterfaceType* A, const FString& AName)
			{
			#if !UE_BUILD_SHIPPING
				checkf(A, TEXT("%s: %s is NULL."), *Context, *AName);

				UObject* O = A->_getUObject();

				checkf(IsValid(O), TEXT("%s: %s is NULL, Pending Kill or NOT a UObject."), *Context, *AName);
				return O;
			#else
				return A->_getUObject();
			#endif // #if !UE_BUILD_SHIPPING
			}

			template<typename InterfaceType>
			FORCEINLINE static UObject* _getUObject(const FString& Context, const InterfaceType* A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return nullptr;
				}

				UObject* O = A->_getUObject();

				if (!IsValid(O))
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is Null, Pending Kill or NOT a UObject."), *Context, *AName));
					return nullptr;
				}
				return O;
			}

			/**
			* InterfaceType A to InterfaceType B cast
			*/
			template<typename InterfaceTypeA, typename InterfaceTypeB>
			FORCEINLINE static InterfaceTypeB* InterfaceCastChecked(const FString& Context, InterfaceTypeA* A, const FString& AName, const FString& InterfaceNameA, const FString& InterfaceNameB)
			{
			#if !UE_BUILD_SHIPPING
				UObject* O			  = _getUObjectChecked(Context, A, AName);
				InterfaceTypeB* Other = Cast<InterfaceTypeB>(O);

				checkf(Other, TEXT("%s: %s: %s with Class: %s implementing interface: %s does NOT implement the interface: %s."), *Context, *AName, *(O->GetName()), *(O->GetClass()->GetName()), *InterfaceNameA, *InterfaceNameB);
				return Other;
			#else
				return Cast<InterfaceTypeB>(A->_getUObject());
			#endif // #if !UE_BUILD_SHIPPING
			}

			/**
			* InterfaceType A to InterfaceType B cast
			*/
			template<typename InterfaceTypeA, typename InterfaceTypeB>
			FORCEINLINE static const InterfaceTypeB* InterfaceCastChecked(const FString& Context, const InterfaceTypeA* A, const FString& AName, const FString& InterfaceNameA, const FString& InterfaceNameB)
			{
			#if !UE_BUILD_SHIPPING
				UObject* O			  = _getUObjectChecked(Context, A, AName);
				InterfaceTypeB* Other = Cast<InterfaceTypeB>(O);
			
				checkf(Other, TEXT("%s: %s: %s with Class: %s implementing interface: %s does NOT implement the interface: %s."), *Context, *AName, *(O->GetName()), *(O->GetClass()->GetName()), *InterfaceNameA, *InterfaceNameB);
				return Other;
			#else
				return Cast<InterfaceTypeB>(A->_getUObject());
			#endif // #if !UE_BUILD_SHIPPING
			}

			/**
			* InterfaceType A to InterfaceType B cast
			*/
			template<typename InterfaceTypeA, typename InterfaceTypeB>
			FORCEINLINE static InterfaceTypeB* InterfaceCast(const FString& Context, InterfaceTypeA* A, const FString& AName, const FString& InterfaceNameA, const FString& InterfaceNameB, void(*Log)(const FString&))
			{
				if (UObject* O = _getUObject(Context, A, AName, Log))
				{
					if (InterfaceTypeB* Other = Cast<InterfaceTypeB>(O))
						return Other;

					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s implementing interface: %s does NOT implement the interface: %s."), *Context, *AName, *(O->GetName()), *(O->GetClass()->GetName()), *InterfaceNameA, *InterfaceNameB));
				}
				return nullptr;
			}

			/**
			* InterfaceType A to InterfaceType B cast
			*/
			template<typename InterfaceTypeA, typename InterfaceTypeB>
			FORCEINLINE static const InterfaceTypeB* InterfaceCast(const FString& Context, const InterfaceTypeA* A, const FString& AName, const FString& InterfaceNameA, const FString& InterfaceNameB, void(*Log)(const FString&))
			{
				if (UObject* O = _getUObject(Context, A, AName, Log))
				{
					if (InterfaceTypeB* Other = Cast<InterfaceTypeB>(O))
						return Other;

					if (Log)
						Log(FString::Printf(TEXT("%s: %s: %s with Class: %s implementing interface: %s does NOT implement the interface: %s."), *Context, *AName, *(O->GetName()), *(O->GetClass()->GetName()), *InterfaceNameA, *InterfaceNameB));
				}
				return nullptr;
			}

			/**
			* InterfaceType A to UObject cast
			*/
			template<typename InterfaceType, typename ClassType>
			FORCEINLINE static ClassType* CastChecked(const FString& Context, InterfaceType* A, const FString& AName, const FString& InterfaceName)
			{
			#if !UE_BUILD_SHIPPING
				UObject* O		 = _getUObjectChecked(Context, A, AName);
				ClassType* Other = Cast<ClassType>(O);

				checkf(Other, TEXT("%s: %s: %s with Class: %s implementing interface: %s is NOT of type: %s."), *Context, *AName, *(O->GetName()), *(O->GetClass()->GetName()), *InterfaceName, *(ClassType::StaticClass()->GetName()));
				return Other;
			#else
				return Cast<ClassType>(A->_getUObject());
			#endif // #if !UE_BUILD_SHIPPING
			}

			/**
			* InterfaceType A to UObject cast
			*/
			template<typename InterfaceType, typename ClassType>
			FORCEINLINE static const ClassType* CastChecked(const FString& Context, const InterfaceType* A, const FString& AName, const FString& InterfaceName)
			{
			#if !UE_BUILD_SHIPPING
				UObject* O		 = _getUObjectChecked(Context, A, AName);
				ClassType* Other = Cast<ClassType>(O);

				checkf(Other, TEXT("%s: %s: %s with Class: %s implementing interface: %s is NOT of type: %s."), *Context, *AName, *(O->GetName()), *(O->GetClass()->GetName()), *InterfaceName, *(ClassType::StaticClass()->GetName()));
				return Other;
			#else
				return Cast<ClassType>(A->_getUObject());
			#endif // #if !UE_BUILD_SHIPPING
			}
		};
	}
}

// CHECKED

#if !UE_BUILD_SHIPPING
// Assume const FString& Context has been defined
#define CS_IS_VALID_CHECKED(__Object) __Object.IsValidChecked(Context)
// Assume const FString& Context has been defined
#define CS_IS_TOP_VALID_CHECKED(__Object) __Object.IsTopValidChecked(Context)

// Int
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_INT_GREATER_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::GreaterThanChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::GreaterThanOrEqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_CHECKED(__A, __B, __C) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::GreaterThanAndLessThanOrEqualChecked(Context, __A, __temp__str__, __B, __C)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_INT_LESS_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::LessThanChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::LessThanOrEqualChecked(Context, __A, __temp__str__, __B)); \
	}

#pragma endregion Int

// Float
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_FLOAT_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::EqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_NOT_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::NotEqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_EQUAL_TWO_VALUES_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__a = #__A; \
		static const FString __temp__str__b = #__B; \
		check(NCsValid::NFloat::FLibrary::EqualChecked(Context, __A, __temp__str__a, __B, __temp__str__b)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::GreaterThanChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_GREATER_THAN_TWO_VALUES_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__a = #__A; \
		static const FString __temp__str__b = #__B; \
		check(NCsValid::NFloat::FLibrary::GreaterThanChecked(Context, __A, __temp__str__a, __B, __temp__str__b)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::GreaterThanOrEqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_COMPARE_LESS_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__a__ = #__A; \
		static const FString __temp__str__b__ = #__B; \
		check(NCsValid::NFloat::NCompare::FLibrary::LessThanChecked(Context, __A, __temp__str__a__, __B, __temp__str__b__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_LESS_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::LessThanChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::LessThanOrEqualChecked(Context, __A, __temp__str__, __B)); \
	}

#pragma endregion Float

// FName
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_NAME_NONE_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NName::FLibrary::NoneChecked(Context, __A, __temp__str__)); \
	}

#pragma endregion FName

// FString
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_STRING_EMPTY_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NString::FLibrary::EmptyChecked(Context, __A, __temp__str__)); \
	}

#pragma endregion FString

// FText
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_TEXT_EMPTY_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NText::FLibrary::EmptyChecked(Context, __A, __temp__str__)); \
	}

#pragma endregion FString

// Enum
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_ENUM_VALID_CHECKED(__EnumMapType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		check(__EnumMapType::Get().IsValidEnumChecked(Context, __temp__str__, __Enum)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ENUM_ARRAY_VALID_CHECKED(__EnumMapType, __EnumType, __Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NEnum::FLibrary::IsValidChecked<__EnumMapType, __EnumType>(Context, __Array, __temp__str__))); \
	}

#pragma endregion Enum

// EnumStruct
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_ENUM_STRUCT_VALID_CHECKED(__EnumMapType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		check(__EnumMapType::Get().IsValidEnumChecked(Context, __temp__str__, __Enum)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ENUM_STRUCT_ARRAY_VALID_CHECKED(__EnumMapType, __EnumType, __Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NEnum::NStruct::FLibrary::IsValidChecked<__EnumMapType, __EnumType>(Context, __Array, __temp__str__))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ENUM_STRUCT_SET_VALID_CHECKED(__EnumMapType, __EnumType, __Set) \
	{ \
		static const FString __temp__str__ = #__Set; \
		check((NCsValid::NEnum::NStruct::FLibrary::IsValidChecked<__EnumMapType, __EnumType>(Context, __Set, __temp__str__))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(__EnumMapType, __EnumType, __Set) \
	{ \
		static const FString __temp__str__ = #__Set; \
		check((NCsValid::NEnum::NStruct::FLibrary::IsUniqueChecked<__EnumMapType, __EnumType>(Context, __Set, __temp__str__))); \
	}

#pragma endregion EnumStruct

// FVector3f
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_VECTOR_ZERO_CHECKED(__V) \
	{ \
		static const FString __temp__str__ = #__V; \
		check(NCsValid::NVector::FLibrary::IsZeroChecked(Context, __V, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_VECTOR_COMPONENTS_GREATER_THAN_CHECKED(__V, __A) \
	{ \
		static const FString __temp__str__v = #__V; \
		static const FString __temp__str__a = #__A; \
		check(NCsValid::NVector::FLibrary::ComponentsGreaterThanChecked(Context, __V, __temp__str__v, __A, __temp__str__a)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL_CHECKED(__V, __A) \
	{ \
		static const FString __temp__str__v = #__V; \
		static const FString __temp__str__a = #__A; \
		check(NCsValid::NVector::FLibrary::ComponentsGreaterThanOrEqualChecked(Context, __V, __temp__str__v, __A, __temp__str__a)); \
	}

#pragma endregion FVector3f

// Array
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_TARRAY_EMPTY_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::EmptyChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_SIZE_CHECKED(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::SizeChecked<__ValueType>(Context, __Array, __temp__str__, __Size)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_GREATER_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::GreaterThanOrEqualSizeChecked<__ValueType>(Context, __Array, __temp__str__, __Size)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::LessThanOrEqualSizeChecked<__ValueType>(Context, __Array, __temp__str__, __Size)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_ANY_NULL_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyNullChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyPendingKillChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_ANY_NOT_VALID_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyNotValidChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_ANY_NONE_CHECKED(__Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyNoneChecked(Context, __Array, __temp__str__)); \
	}

	// Fixed
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_TARRAY_FIXED_EMPTY_CHECKED(__Array, __ValueType, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NArray::FLibrary::EmptyChecked<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_FIXED_SIZE_CHECKED(__Array, __ValueType, __AllocatedSize, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NArray::FLibrary::SizeChecked<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, __Size))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_FIXED_GREATER_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __AllocatedSize, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NArray::FLibrary::GreaterThanOrEqualSizeChecked<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, __Size))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_FIXED_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __AllocatedSize, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NArray::FLibrary::LessThanOrEqualSizeChecked<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, __Size))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_FIXED_ANY_NULL_CHECKED(__Array, __ValueType, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NArray::FLibrary::IsAnyNullChecked<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__))); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_FIXED_ANY_NONE_CHECKED(__Array, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check((NCsValid::NArray::FLibrary::IsAnyNoneChecked<__AllocatedSize>(Context, __Array, __temp__str__))); \
	}

#pragma endregion Fixed

	// 2D
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_TARRAY_2D_EMPTY_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::N2D::FLibrary::EmptyChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TARRAY_2D_ANY_NULL_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::N2D::FLibrary::IsAnyNullChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}

#pragma endregion 2D

#pragma endregion Array

// Set
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_TSET_EMPTY_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NSet::FLibrary::EmptyChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_TSET_ANY_PENDING_KILL_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NSet::FLibrary::IsAnyPendingKillChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}

#pragma endregion Set

// Ptr
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_PTR_NULL_CHECKED(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		check(NCsValid::NPtr::FLibrary::NullChecked(Context, __Ptr, __temp__str__)); \
	}

#pragma endregion Ptr

// Object
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_PENDING_KILL_CHECKED(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		check(NCsValid::NObject::FLibrary::IsPendingKillChecked(Context, __Object, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_OBJ_CLASS_OF_CHECKED(__Object, __ObjectType, __ClassType) \
	{ \
		static const FString __temp__str__ = #__Object; \
		check((NCsValid::NObject::FLibrary::IsClassOfChecked<__ObjectType, __ClassType>(Context, __Object, __temp__str__))); \
	}
// Assume const FString& Context has been defined
#define CS_CAST_CHECKED(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastToChecked<__ObjectType, __OtherObjectType>(Context, __In__##__Object, __temp__str__); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_CONST_CAST_CHECKED(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, const __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastToChecked<__ObjectType, __OtherObjectType>(Context, __In__##__Object, __temp__str__); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __In__##__Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, const __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __In__##__Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_NEW_CHECKED(__ObjectType, __Outer, __Class) \
	[] (const FString& Context, UObject* __In__##__Outer, UClass* __In__##__Class) \
	{ \
		static const FString __temp__str__a = #__Outer; \
		static const FString __temp__str__b = #__Class; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __In__##__Outer, __temp__str__a, __In__##__Class, __temp__str__b); \
	}(Context, __Outer, __Class)
// Assume const FString& Context has been defined and this is passed out Outer for NewObject
#define CS_NEW_BY_THIS_AND_SUBCLASS_OF_CHECKED(__ObjectType, __Class) \
	[] (const FString& Context, UObject* __In__##__Outer, TSubclassOf<__ObjectType>& __In__##__Class) \
	{ \
		static const FString __temp__str__a = TEXT("this"); \
		static const FString __temp__str__b = #__Class; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __In__##__Outer, __temp__str__a, __In__##__Class, __temp__str__b); \
	}(Context, this, __Class)
// Assume const FString& Context has been defined
#define CS_IMPLEMENTS_INTERFACE_CHECKED(__Object, __ObjectType, __InterfaceType) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		bool __temp__result = NCsValid::NObject::FLibrary::ImplementsInterfaceChecked<__ObjectType, __InterfaceType::UClassType>(Context, __Object, __temp__str__a, __temp__str__b); \
		check(__temp__result); \
	}

#pragma endregion Object

// WeakObjectPtr
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_WEAK_OBJ_PTR_NULL_CHECKED(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		check(NCsValid::NWeakObjectPtr::FLibrary::NullChecked<__ObjectType>(Context, __Ptr, __temp__str__)); \
	}

#pragma endregion WeakObjectPtr

// TObjectPtr
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_OBJECT_PTR_NULL_CHECKED(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		check(NCsValid::NObjectPtr::FLibrary::NullChecked<__ObjectType>(Context, __Ptr, __temp__str__)); \
	}

#pragma endregion TObjectPtr

// TSoftObjectPtr
#pragma region 

// Assume const FString& Context has been defined
#define CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(__A, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NSoftObjectPtr::FLibrary::IsValidChecked<__ObjectType>(Context, __A, __temp__str__)); \
	}

// Assume const FString& Context has been defined
#define CS_SOFT_OBJECT_PTR_GET_CHECKED(__A, __ObjectType) \
	[] (const FString& Context, const TSoftObjectPtr<__ObjectType>& __In__##__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		return NCsValid::NSoftObjectPtr::FLibrary::GetChecked<__ObjectType>(Context, __In__##__A, __temp__str__); \
	}(Context, __A)

#pragma endregion TSoftObjectPtr

// TSoftClassPtr
#pragma region 

// Assume const FString& Context has been defined
#define CS_IS_SOFT_CLASS_PTR_VALID_CHECKED(__A, __ClassType) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NSoftClassPtr::FLibrary::IsValidChecked<__ClassType>(Context, __A, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_SOFT_CLASS_PTR_GET_CHECKED(__A, __ClassType) \
	[] (const FString& Context, const TSoftClassPtr<__ClassType>& __In__##__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		return NCsValid::NSoftClassPtr::FLibrary::GetChecked<__ClassType>(Context, __In__##__A, __temp__str__); \
	}(Context, __A)
// Assume const FString& Context has been defined
#define CS_SOFT_CLASS_PTR_LOAD_CHECKED(__A, __ClassType) \
	[] (const FString& Context, const TSoftClassPtr<__ClassType>& __In__##__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		return NCsValid::NSoftClassPtr::FLibrary::LoadChecked<__ClassType>(Context, __In__##__A, __temp__str__); \
	}(Context, __A)

#pragma endregion TSoftClassPtr

// FSoftObjectPath
#pragma region 

// Assume const FString& Context has been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NSoftObjectPath::FLibrary::IsValidChecked(Context, __A, __temp__str__)); \
	}

#pragma endregion FSoftObjectPath

// SubclassOf
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_SUBCLASS_OF_NULL_CHECKED(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Class; \
		check(NCsValid::NSubclassOf::FLibrary::NullChecked<__ObjectType>(Context, __Class, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET_CHECKED(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class) \
	{ \
		static const FString __temp__str__ = #__Class; \
		return NCsValid::NSubclassOf::FLibrary::GetChecked<__ObjectType>(Context, __In__##__Class, __temp__str__); \
	}(Context, __Class)
// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET_DEFAULT_OBJ_CHECKED(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class) \
	{ \
		static const FString __temp__str__ = #__Class; \
		return NCsValid::NSubclassOf::FLibrary::GetDefaultObjectChecked<__ObjectType>(Context, __In__##__Class, __temp__str__); \
	}(Context, __Class)

#pragma endregion SubclassOf

// Actor
#pragma region

// Assume const FString& Context has been defined and this->GetWorld() exists
//#define CS_SPAWN_ACTOR_CHECKED(__ActorType, __Class) \
//	[] (const FString& Context, UWorld* __World, UClass* __Class) \
//	{ \
//		static const FString __temp__str__a = #__Class; \
//		return NCsValid::NActor::FLibrary::SpawnChecked<__ActorType>(Context, __World, __Class, __temp__str__a); \
//	}(Context, GetWorld(), __Class)

#pragma endregion Actor

// Interface
#pragma region

// Assume const FString& Context has been defined
#define CS_INTERFACE_GET_UOBJECT_CHECKED(__Interface, __InterfaceType) \
	[](const FString& Context, const __InterfaceType* __In__##__Interface) \
	{ \
		static const FString __temp__str = #__Interface; \
		return NCsValid::NInterface::FLibrary::_getUObjectChecked<__InterfaceType>(Context, __In__##__Interface, __temp__str); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(__Interface, __InterfaceTypeA, __InterfaceTypeB) \
	[] (const FString& Context, __InterfaceTypeA* __In__##__Interface) \
	{ \
		static const FString __temp__str__  = #__Interface; \
		static const FString __temp__str__a = #__InterfaceTypeA; \
		static const FString __temp__str__b = #__InterfaceTypeB; \
		return NCsValid::NInterface::FLibrary::InterfaceCastChecked<__InterfaceTypeA, __InterfaceTypeB>(Context, __In__##__Interface, __temp__str__, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_TO_INTERFACE_CAST_CHECKED(__Interface, __InterfaceTypeA, __InterfaceTypeB) \
	[] (const FString& Context, const __InterfaceTypeA* __In__##__Interface) \
	{ \
		static const FString __temp__str__  = #__Interface; \
		static const FString __temp__str__a = #__InterfaceTypeA; \
		static const FString __temp__str__b = #__InterfaceTypeB; \
		return NCsValid::NInterface::FLibrary::InterfaceCastChecked<__InterfaceTypeA, __InterfaceTypeB>(Context, __In__##__Interface, __temp__str__, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(__Interface, __InterfaceType, __ClassType) \
	[] (const FString& Context, __InterfaceType* __In__##__Interface) \
	{ \
		static const FString __temp__str__a  = #__Interface; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NInterface::FLibrary::CastChecked<__InterfaceType, __ClassType>(Context, __In__##__Interface, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_TO_UOBJECT_CAST_CHECKED(__Interface, __InterfaceType, __ClassType) \
	[] (const FString& Context, const __InterfaceType* __In__##__Interface) \
	{ \
		static const FString __temp__str__a  = #__Interface; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NInterface::FLibrary::CastChecked<__InterfaceType, __ClassType>(Context, __In__##__Interface, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)

#pragma endregion Interface

// Delegate
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_DELEGATE_BOUND_CHECKED(__Delegate) \
	{ \
		static const FString __temp__str__ = #__Delegate; \
		checkf(__Delegate.IsBound(), TEXT("%s: %s is NOT Bound."), *Context, *__temp__str__); \
	}

#pragma endregion Delegate

#else
#define CS_IS_VALID_CHECKED(__Object)
#define CS_IS_TOP_VALID_CHECKED(__Object)
// Int
#define CS_IS_INT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_CHECKED(__A, __B, __C)
#define CS_IS_INT_LESS_THAN_CHECKED(__A, __B)
#define CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(__A, __B)
// Float
#define CS_IS_FLOAT_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_NOT_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_EQUAL_TWO_VALUES_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_TWO_VALUES_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_COMPARE_LESS_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_LESS_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_LESS_THAN_OR_EQUAL_CHECKED(__A, __B)
// FName
#define CS_IS_NAME_NONE_CHECKED(__A)
// FString
#define CS_IS_STRING_EMPTY_CHECKED(__A)
// FText
#define CS_IS_TEXT_EMPTY_CHECKED(__A)
// Enum
#define CS_IS_ENUM_VALID_CHECKED(__EnumMapType, __Enum)
#define CS_IS_ENUM_ARRAY_VALID_CHECKED(__EnumMapType, __EnumType, __Array)
// EnumStruct
#define CS_IS_ENUM_STRUCT_VALID_CHECKED(__EnumMapType, __Enum)
#define CS_IS_ENUM_STRUCT_ARRAY_VALID_CHECKED(__EnumMapType, __EnumType, __Array)
#define CS_IS_ENUM_STRUCT_SET_VALID_CHECKED(__EnumMapType, __EnumType, __Set)
#define CS_IS_ENUM_STRUCT_SET_UNIQUE_CHECKED(__EnumMapType, __EnumType, __Set)
// FVector3f
#define CS_IS_VECTOR_ZERO_CHECKED(__V)
#define CS_IS_VECTOR_COMPONENTS_GREATER_THAN_CHECKED(__V, __A)
#define CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL_CHECKED(__V, __A)
// Array
#define CS_IS_TARRAY_EMPTY_CHECKED(__Array, __ValueType)
#define CS_IS_TARRAY_SIZE_CHECKED(__Array, __ValueType, __Size)
#define CS_IS_TARRAY_GREATER_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size)
#define CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size)
#define CS_IS_TARRAY_ANY_NULL_CHECKED(__Array, __ValueType)
#define CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(__Array, __ValueType)
#define CS_IS_TARRAY_ANY_NOT_VALID_CHECKED(__Array, __ValueType)
#define CS_IS_TARRAY_ANY_NONE_CHECKED(__Array)
	// Fixed
#define CS_IS_TARRAY_FIXED_EMPTY_CHECKED(__Array, __ValueType, __AllocatedSize)
#define CS_IS_TARRAY_FIXED_SIZE_CHECKED(__Array, __ValueType, __AllocatedSize, __Size)
#define CS_IS_TARRAY_FIXED_GREATER_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __AllocatedSize, __Size)
#define CS_IS_TARRAY_FIXED_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __AllocatedSize, __Size)
#define CS_IS_TARRAY_FIXED_ANY_NULL_CHECKED(__Array, __ValueType, __AllocatedSize)
#define CS_IS_TARRAY_FIXED_ANY_NONE_CHECKED(__Array, __AllocatedSize)
	// 2D
#define CS_IS_TARRAY_2D_EMPTY_CHECKED(__Array, __ValueType)
#define CS_IS_TARRAY_2D_ANY_NULL_CHECKED(__Array, __ValueType)
// Set
#define CS_IS_TSET_EMPTY_CHECKED(__Array, __ValueType)
#define CS_IS_TSET_ANY_PENDING_KILL_CHECKED(__Array, __ValueType)
// Ptr
#define CS_IS_PTR_NULL_CHECKED(__Ptr)
// Object
#define CS_IS_PENDING_KILL_CHECKED(__Object)
#define CS_IS_OBJ_CLASS_OF_CHECKED(__Object, __ObjectType, __ClassType)
// Assume const FString& Context has been defined
#define CS_CAST_CHECKED(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NObject::FLibrary::CastToChecked<__ObjectType, __OtherObjectType>(Context,__In__## __Object, __temp__str__); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_CONST_CAST_CHECKED(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, const __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NObject::FLibrary::CastToChecked<__ObjectType, __OtherObjectType>(Context, __In__##__Object, __temp__str__); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __In__##__Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, const __ObjectType* __In__##__Object) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __In__##__Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_NEW_CHECKED(__ObjectType, __Outer, __Class) \
	[] (const FString& Context, UObject* __In__##__Outer, UClass* __In__##__Class) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __In__##__Outer, __temp__str__a, __In__##__Class, __temp__str__b); \
	}(Context, __Outer, __Class)
// Assume const FString& Context has been defined and this is passed out Outer for NewObject
#define CS_NEW_BY_THIS_AND_SUBCLASS_OF_CHECKED(__ObjectType, __Class) \
	[] (const FString& Context, UObject* __In__##__Outer, TSubclassOf<__ObjectType>& __In__##__Class) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __In__##__Outer, __temp__str__a, __In__##__Class, __temp__str__b); \
	}(Context, this, __Class)
// Assume const FString& Context has been defined
#define CS_IMPLEMENTS_INTERFACE_CHECKED(__Object, __ObjectType, __InterfaceType) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		bool __temp__result = NCsValid::NObject::FLibrary::ImplementsInterfaceChecked<__ObjectType, __InterfaceType::UClassType>(Context, __Object, __temp__str__a, __temp__str__b); \
		check(__temp__restul); \
	}
// WeakObjectPtr
#define CS_IS_WEAK_OBJ_PTR_NULL_CHECKED(__Ptr, __ObjectType)
// TObjectPtr
#define CS_IS_OBJECT_PTR_NULL_CHECKED(__Ptr, __ObjectType)
// TSoftObjectPtr
#define CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(__A, __ObjectType)
	// Assume const FString& Context has been defined
#define CS_SOFT_OBJECT_PTR_GET_CHECKED(__A, __ObjectType) \
	[] (const FString& Context, const TSoftObjectPtr<__ObjectType>& __In__##__A) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSoftObjectPtr::FLibrary::GetChecked<__ObjectType>(Context, __In__##__A), __temp__str__); \
	}(Context, __A)
// TSoftClassPtr
#define CS_IS_SOFT_CLASS_PTR_VALID_CHECKED(__A, __ClassType)
	// Assume const FString& Context has been defined
#define CS_SOFT_CLASS_PTR_GET_CHECKED(__A, __ClassType) \
	[] (const FString& Context, const TSoftClassPtr<__ClassType>& __In__##__A) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSoftClassPtr::FLibrary::GetChecked<__ClassType>(Context, __In__##__A, __temp__str__); \
	}(Context, __A)
	// Assume const FString& Context has been defined
#define CS_SOFT_CLASS_PTR_LOAD_CHECKED(__A, __ClassType) \
	[] (const FString& Context, const TSoftClassPtr<__ClassType>& __In__##__A) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSoftClassPtr::FLibrary::LoadChecked<__ClassType>(Context, __In__##__A, __temp__str__); \
	}(Context, __A)
// FSoftObjectPath
#define CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(__A)
// SubclassOf
#define CS_IS_SUBCLASS_OF_NULL_CHECKED(__Class, __ObjectType)
	// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET_CHECKED(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSubclassOf::FLibrary::GetChecked<__ObjectType>(Context, __Class, __temp__str__); \
	}(Context, __Class)
	// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET_DEFAULT_OBJ_CHECKED(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSubclassOf::FLibrary::GetDefaultObjectChecked<__ObjectType>(Context, __In__##__Class, __temp__str__); \
	}(Context, __Class)
// Actor
//#define CS_SPAWN_ACTOR_CHECKED(__ActorType, __Class) \
//	[] (const FString& Context, UWorld* __In__##__World, UClass* __In__##__Class) \
//	{ \
//		static const FString __temp__str__a; \
//		return NCsValid::NActor::FLibrary::SpawnChecked<__ActorType>(Context, __In__##__World, __In__##__Class, __temp__str__a); \
//	}(Context, GetWorld(), __Class)
// Interface
#define CS_INTERFACE_GET_UOBJECT_CHECKED(__Interface, __InterfaceType) \
	[](const FString& Context, const __InterfaceType* __In__##__Interface) \
	{ \
		static const FString __temp__str; \
		return NCsValid::NInterface::FLibrary::_getUObjectChecked<__InterfaceType>(Context, __In__##__Interface, __temp__str); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_INTERFACE_TO_INTERFACE_CAST_CHECKED(__Interface, __InterfaceTypeA, __InterfaceTypeB) \
	[] (const FString& Context, __InterfaceTypeA* __In__##__Interface) \
	{ \
		static const FString __temp__str__; \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NInterface::FLibrary::InterfaceCastChecked<__InterfaceTypeA, __InterfaceTypeB>(Context, __In__##__Interface, __temp__str__, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_TO_INTERFACE_CAST_CHECKED(__Interface, __InterfaceTypeA, __InterfaceTypeB) \
	[] (const FString& Context, const __InterfaceTypeA* __In__##__Interface) \
	{ \
		static const FString __temp__str__; \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NInterface::FLibrary::InterfaceCastChecked<__InterfaceTypeA, __InterfaceTypeB>(Context, __In__##__Interface, __temp__str__, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(__Interface, __InterfaceType, __ClassType) \
	[] (const FString& Context, __InterfaceType* __In__##__Interface) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NInterface::FLibrary::CastChecked<__InterfaceType, __ClassType>(Context, __In__##__Interface, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_TO_UOBJECT_CAST_CHECKED(__Interface, __InterfaceType, __ClassType) \
	[] (const FString& Context, const __InterfaceType* __In__##__Interface) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NInterface::FLibrary::CastChecked<__InterfaceType, __ClassType>(Context, __In__##__Interface, __temp__str__a, __temp__str__b); \
	}(Context, __Interface)
// Delegate
#define CS_IS_DELEGATE_BOUND_CHECKED(__Delegate)
#endif // #if !UE_BUILD_SHIPPING

// SAFE

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VALID(__Object) \
	if (!__Object.IsValid(Context, Log)) \
		return false;
// Assume const FString& Context has been defined
#define CS_IS_VALID_NO_LOG(__Object) \
	if (!__Object.IsValid(Context, nullptr)) \
		return false;
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VALID_EXIT(__Object) \
	if (!__Object.IsValid(Context, Log)) \
		return;
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VALID_RET_NULL(__Object) \
	if (!__Object.IsValid(Context, Log)) \
		return nullptr;
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VALID_RET_VALUE(__Object, __Value) \
	if (!__Object.IsValid(Context, Log)) \
		return __Value;

// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_VALID2(__Object) \
	if (!__Object.IsValid(Ctxt, Log)) \
		return false;
// Assume const FString& Ctxt has been defined
#define CS_IS_VALID_NO_LOG2(__Object) \
	if (!__Object.IsValid(Ctxt, nullptr)) \
		return false;
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_VALID_EXIT2(__Object) \
	if (!__Object.IsValid(Ctxt, Log)) \
		return;
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_VALID_RET_NULL2(__Object) \
	if (!__Object.IsValid(Ctxt, Log)) \
		return nullptr;
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_VALID_RET_VALUE2(__Object, __Value) \
	if (!__Object.IsValid(Ctxt, Log)) \
		return __Value;

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID(__Object) \
	if (!__Object.IsTopValid(Context, Log)) \
		return false;
// Assume const FString& Context has been defined
#define CS_IS_TOP_VALID_NO_LOG(__Object) \
	if (!__Object.IsTopValid(Context, nullptr)) \
		return false;
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID_EXIT(__Object) \
	if (!__Object.IsTopValid(Context, Log)) \
		return;
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID_RET_NULL(__Object) \
	if (!__Object.IsTopValid(Context, Log)) \
		return nullptr;
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID_RET_VALUE(__Object, __Value) \
	if (!__Object.IsTopValid(Context, Log)) \
		return __Value;

// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID2(__Object) \
	if (!__Object.IsTopValid(Ctxt, Log)) \
		return false;
// Assume const FString& Ctxt has been defined
#define CS_IS_TOP_VALID_NO_LOG2(__Object) \
	if (!__Object.IsTopValid(Ctxt, nullptr)) \
		return false;
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID_EXIT2(__Object) \
	if (!__Object.IsTopValid(Ctxt, Log)) \
		return;
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID_RET_NULL2(__Object) \
	if (!__Object.IsTopValid(Ctxt, Log)) \
		return nullptr;
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_TOP_VALID_RET_VALUE2(__Object, __Value) \
	if (!__Object.IsTopValid(Ctxt, Log)) \
		return __Value;

// Int
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_OR_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_NULL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_VALUE(__A, __B, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL(__A, __B, __C) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThanAndLessThanOrEqual(Context, __A, __temp__str__, __B, __C, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_RET_NULL(__A, __B, __C) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::GreaterThanAndLessThanOrEqual(Context, __A, __temp__str__, __B, __C, Log)) { return nullptr; } \
	}
	// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_LESS_THAN(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::LessThan(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_LESS_THAN_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::LessThan(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_LESS_THAN_OR_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::LessThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_LESS_THAN_OR_EQUAL_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::LessThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_LESS_THAN_OR_EQUAL_RET_NULL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::LessThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_INT_LESS_THAN_OR_EQUAL_RET_VALUE(__A, __B, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NInt::FLibrary::LessThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return __Value; } \
	}

#pragma endregion Int

// Float
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::Equal(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_NOT_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::NotEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_EQUAL_TWO_VALUES(__A, __B) \
	{ \
		static const FString __temp__str__a = #__A; \
		static const FString __temp__str__b = #__B; \
		if (!NCsValid::NFloat::FLibrary::Equal(Context, __A, __temp__str__a, __B, __temp__str__b, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_TWO_VALUES(__A, __B) \
	{ \
		static const FString __temp__str__a = #__A; \
		static const FString __temp__str__b = #__B; \
		if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, __temp__str__a, __B, __temp__str__b, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_RET_NULL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_RET_VALUE(__A, __B, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_RET_NULL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_RET_VALUE(__A, __B, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_COMPARE_LESS_THAN(__A, __B) \
	{ \
		static const FString __temp__str__a__ = #__A; \
		static const FString __temp__str__b__ = #__B; \
		if (!NCsValid::NFloat::NCompare::FLibrary::LessThan(Context, __A, __temp__str__a__, __B, __temp__str__b__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_LESS_THAN(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::LessThan(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_LESS_THAN_EXIT(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::LessThan(Context, __A, __temp__str__, __B, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_LESS_THAN_RET_NULL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::LessThan(Context, __A, __temp__str__, __B, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_LESS_THAN_RET_VALUE(__A, __B, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::LessThan(Context, __A, __temp__str__, __B, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_LESS_THAN_OR_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::LessThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}

#pragma endregion Float

// FName
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_NAME_NONE(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NName::FLibrary::None(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_NAME_NONE_RET_NULL(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NName::FLibrary::None(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_NAME_NONE_RET_VALUE(__A, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NName::FLibrary::None(Context, __A, __temp__str__, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_NAME_NONE_EXIT(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NName::FLibrary::None(Context, __A, __temp__str__, Log)) { return; } \
	}

#pragma endregion FName

// FString
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_STRING_EMPTY(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NString::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_STRING_EMPTY_EXIT(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NString::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_STRING_EMPTY_RET_NULL(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NString::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_STRING_EMPTY_RET_VALUE(__A, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NString::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return __Value; } \
	}

#pragma endregion FString

// FText
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TEXT_EMPTY(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NText::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TEXT_EMPTY_EXIT(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NText::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TEXT_EMPTY_RET_NULL(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NText::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TEXT_EMPTY_RET_VALUE(__A, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NText::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return __Value; } \
	}

#pragma endregion FString

// Enum
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_VALID(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_VALID_EXIT(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_VALID_RET_NULL(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_VALID_RET_VALUE(__EnumMapType, __EnumType, __Enum, __Value) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_ARRAY_VALID(__EnumMapType, __EnumType, __Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NEnum::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}

#pragma endregion Enum

// EnumStruct
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_VALID(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_VALID_EXIT(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_VALID_RET_NULL(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_VALID_RET_VALUE(__EnumMapType, __EnumType, __Enum, __Value) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_ARRAY_VALID(__EnumMapType, __EnumType, __Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_SET_VALID(__EnumMapType, __EnumType, __Set) \
	{ \
		static const FString __temp__str__ = #__Set; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Set, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_SET_UNIQUE(__EnumMapType, __EnumType, __Set) \
	{ \
		static const FString __temp__str__ = #__Set; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsUnique<__EnumMapType, __EnumType>(Context, __Set, __temp__str__, Log)) { return false; } \
	}

#pragma endregion EnumStruct

// FVector3f
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VECTOR_ZERO(__V) \
	{ \
		static const FString __temp__str__ = #__V; \
		if (!NCsValid::NVector::FLibrary::IsZero(Context, __V, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VECTOR_COMPONENTS_GREATER_THAN(__V, __A) \
	{ \
		static const FString __temp__str__v = #__V; \
		static const FString __temp__str__a = #__A; \
		if (!NCsValid::NVector::FLibrary::ComponentsGreaterThan(Context, __V, __temp__str__v, __A, __temp__str__a, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VECTOR_COMPONENTS_GREATER_THAN_OR_EQUAL(__V, __A) \
	{ \
		static const FString __temp__str__v = #__V; \
		static const FString __temp__str__a = #__A; \
		if (!NCsValid::NVector::FLibrary::ComponentsGreaterThanOrEqual(Context, __V, __temp__str__v, __A, __temp__str__a, Log)) { return false; } \
	}

#pragma endregion FVector3f

// Array
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_EMPTY(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_EMPTY_EXIT(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_EMPTY_RET_NULL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_SIZE(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Size<__ValueType>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_GREATER_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::GreaterThanOrEqualSize<__ValueType>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::LessThanOrEqualSize<__ValueType>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_ANY_NULL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNull<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_ANY_PENDING_KILL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyPendingKill<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_ANY_NOT_VALID(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNotValid<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_ANY_NONE(__Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNone(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_ANY_NONE_RET_NULL(__Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNone(Context, __Array, __temp__str__, Log)) { return nullptr; } \
	}

	// Fixed
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_EMPTY(__Array, __ValueType, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_EMPTY_EXIT(__Array, __ValueType, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_SIZE(__Array, __ValueType, __AllocatedSize, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Size<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_GREATER_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __AllocatedSize, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::GreaterThanOrEqualSize<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_LESS_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __AllocatedSize, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::LessThanOrEqualSize<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_ANY_NULL(__Array, __ValueType, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNull<__ValueType, __AllocatedSize>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_FIXED_ANY_NONE(__Array, __AllocatedSize) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNone<__AllocatedSize>(Context, __Array, __temp__str__, Log)) { return false; } \
	}

#pragma endregion Fixed

	// 2D
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TARRAY_2D_EMPTY(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::N2D::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}

#pragma endregion 2D

#pragma endregion Array

// Set
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TSET_EMPTY(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NSet::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TSET_EMPTY_EXIT(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NSet::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TSET_EMPTY_RET_NULL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NSet::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_TSET_ANY_PENDING_KILL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NSet::FLibrary::IsAnyPendingKill<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}

#pragma endregion Set

// Ptr
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Context, __Ptr, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL_EXIT(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Context, __Ptr, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL_RET_NULL(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Context, __Ptr, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL_RET_VALUE(__Ptr, __Value) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Context, __Ptr, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL2(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Ctxt, __Ptr, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL_EXIT2(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Ctxt, __Ptr, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL_RET_NULL2(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Ctxt, __Ptr, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PTR_NULL_RET_VALUE2(__Ptr, __Value) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NPtr::FLibrary::Null(Ctxt, __Ptr, __temp__str__, Log)) { return __Value; } \
	}

#pragma endregion Ptr

// Object
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Context, __Object, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL_EXIT(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Context, __Object, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL_RET_NULL(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Context, __Object, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL_RET_VALUE(__Object, __Value) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Context, __Object, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL2(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Ctxt, __Object, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL_EXIT2(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Ctxt, __Object, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL_RET_NULL2(__Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Ctxt, __Object, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Ctxt and void(Log*)(const FString&) have been defined
#define CS_IS_PENDING_KILL_RET_VALUE2(__Object, __Value) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsPendingKill(Ctxt, __Object, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_OBJ_CLASS_OF(__Object, __ObjectType, __ClassType) \
	{ \
		static const FString __temp__str__ = #__Object; \
		if (!NCsValid::NObject::FLibrary::IsClassOf<__ObjectType, __ClassType>(Context, __Object, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_DOES_OBJ_IMPLEMENT(__Object, __ObjectType, __InterfaceType) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		if (!NCsValid::NObject::FLibrary::Implements<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_DOES_OBJ_IMPLEMENT_RET_NULL(__Object, __ObjectType, __InterfaceType) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		if (!NCsValid::NObject::FLibrary::Implements<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_DOES_OBJ_IMPLEMENT_RET_VALUE(__Object, __ObjectType, __InterfaceType, __Value) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		if (!NCsValid::NObject::FLibrary::Implements<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_CAST(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, __ObjectType* __In__##__Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastTo<__ObjectType, __OtherObjectType>(Context, __In__##__Object, __temp__str__, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_CONST_CAST(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, const __ObjectType* __In__##__Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastTo<__ObjectType, __OtherObjectType>(Context, __In__##__Object, __temp__str__, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_INTERFACE_CAST(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, __ObjectType* __In__##__Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCast<__ObjectType, __InterfaceType>(Context, __In__##__Object, __temp__str__a, __temp__str__b, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_CONST_INTERFACE_CAST(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, const __ObjectType* __In__##__Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCast<__ObjectType, __InterfaceType>(Context, __In__##__Object, __temp__str__a, __temp__str__b, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IMPLEMENTS_INTERFACE(__Object, __ObjectType, __InterfaceType) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		if (!NCsValid::NObject::FLibrary::ImplementsInterface<__ObjectType, __InterfaceType::UClassType>(Context, __Object, __temp__str__a, __temp__str__b, Log)) { return false; } \
	}

#pragma endregion Object

// WeakObjectPtr
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_WEAK_OBJ_PTR_NULL(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NWeakObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_WEAK_OBJ_PTR_NULL_EXIT(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NWeakObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_WEAK_OBJ_PTR_NULL_RET_NULL(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NWeakObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_WEAK_OBJ_PTR_NULL_RET_VALUE(__Ptr, __ObjectType, __Value) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NWeakObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return __Value; } \
	}

#pragma endregion WeakObjectPtr

// TObjectPtr
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_OBJECT_PTR_NULL(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_OBJECT_PTR_NULL_EXIT(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_OBJECT_PTR_NULL_RET_NULL(__Ptr, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_OBJECT_PTR_NULL_RET_VALUE(__Ptr, __ObjectType, __Value) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		if (!NCsValid::NObjectPtr::FLibrary::Null<__ObjectType>(Context, __Ptr, __temp__str__, Log)) { return __Value; } \
	}

#pragma endregion TObjectPtr

// TSoftObjectPtr
#pragma region 

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PTR_VALID(__A, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPtr::FLibrary::IsValid<__ObjectType>(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PTR_VALID_EXIT(__A, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPtr::FLibrary::IsValid<__ObjectType>(Context, __A, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PTR_VALID_RET_NULL(__A, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPtr::FLibrary::IsValid<__ObjectType>(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PTR_VALID_RET_VALUE(__A, __ObjectType, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPtr::FLibrary::IsValid<__ObjectType>(Context, __A, __temp__str__, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_SOFT_OBJECT_PTR_GET(__A, __ObjectType) \
	[] (const FString& Context, const TSoftObjectPtr<__ObjectType>& __In__##__A, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__A; \
		return NCsValid::NSoftObjectPtr::FLibrary::Get<__ObjectType>(Context, __In__##__A, __temp__str__, Log); \
	}(Context, __A, Log)

#pragma endregion TSoftObjectPtr

// TSoftClassPtr
#pragma region 

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_CLASS_PTR_VALID(__A, __ClassType) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftClassPtr::FLibrary::IsValid<__ClassType>(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_CLASS_PTR_VALID_EXIT(__A, __ClassType) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftClassPtr::FLibrary::IsValid<__ClassType>(Context, __A, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_CLASS_PTR_VALID_RET_NULL(__A, __ClassType) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftClassPtr::FLibrary::IsValid<__ClassType>(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_CLASS_PTR_VALID_RET_VALUE(__A, __ClassType, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftClassPtr::FLibrary::IsValid<__ClassType>(Context, __A, __temp__str__, Log)) { return __Value; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_SOFT_CLASS_PTR_GET(__A, __ClassType) \
	[] (const FString& Context, const TSoftClassPtr<__ClassType>& __In__##__A, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__A; \
		return NCsValid::NSoftClassPtr::FLibrary::Get<__ClassType>(Context, __In__##__A, __temp__str__, Log); \
	}(Context, __A, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_SOFT_CLASS_PTR_LOAD(__A, __ClassType) \
	[] (const FString& Context, const TSoftClassPtr<__ClassType>& __In__##__A, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__A; \
		return NCsValid::NSoftClassPtr::FLibrary::Load<__ClassType>(Context, __In__##__A, __temp__str__, Log); \
	}(Context, __A, Log)

#pragma endregion TSoftClassPtr

// FSoftObjectPath
#pragma region 

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPath::FLibrary::IsValid(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID_EXIT(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPath::FLibrary::IsValid(Context, __A, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPath::FLibrary::IsValid(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID_RET_VALUE(__A, __Value) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPath::FLibrary::IsValid(Context, __A, __temp__str__, Log)) { return __Value; } \
	}

#pragma endregion FSoftObjectPath

// SubclassOf
#pragma region

#if !UE_BUILD_SHIPPING

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Class; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL_EXIT(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Class; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL_RET_NULL(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__ = #__Class; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL_RET_VALUE(__Class, __ObjectType, __Value) \
	{ \
		static const FString __temp__str__ = #__Class; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__Class; \
		return NCsValid::NSubclassOf::FLibrary::Get<__ObjectType>(Context, __In__##__Class, __temp__str__, Log)); \
	}(Context, __Class, Log)
// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET_DEFAULT_OBJ(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__Class; \
		return NCsValid::NSubclassOf::FLibrary::GetDefaultObject<__ObjectType>(Context, __In__##__Class, __temp__str__, Log)); \
	}(Context, __Class, Log)

#else

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL_EXIT(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL_RET_NULL(__Class, __ObjectType) \
	{ \
		static const FString __temp__str__; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return nullptr; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SUBCLASS_OF_NULL_RET_VALUE(__Class, __ObjectType, __Value) \
	{ \
		static const FString __temp__str__; \
		if (!NCsValid::NSubclassOf::FLibrary::Null<__ObjectType>(Context, __Class, __temp__str__, Log)) { return __Value; } \
	}

// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSubclassOf::FLibrary::Get<__ObjectType>(Context, __In__##__Class, __temp__str__, Log)); \
	}(Context, __Class, Log)
// Assume const FString& Context has been defined
#define CS_SUBCLASS_OF_GET_DEFAULT_OBJ(__Class, __ObjectType) \
	[] (const FString& Context, const TSubclassOf<__ObjectType>& __In__##__Class, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NSubclassOf::FLibrary::GetDefaultObject<__ObjectType>(Context, __In__##__Class, __temp__str__, Log)); \
	}(Context, __Class, Log)

#endif // #if !UE_BUILD_SHIPPING

#pragma endregion SubclassOf

// Interface
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_INTERFACE_GET_UOBJECT(__Interface, __InterfaceType) \
	[](const FString& Context, const __InterfaceType* __In__##__Interface, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str = #__Interface; \
		return NCsValid::NInterface::FLibrary::_getUObject<__InterfaceType>(Context, __In__##__Interface, __temp__str, Log); \
	}(Context, __Interface, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_INTERFACE_TO_INTERFACE_CAST(__Interface, __InterfaceTypeA, __InterfaceTypeB) \
	[] (const FString& Context, __InterfaceTypeA* __In__##__Interface, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__  = #__Interface; \
		static const FString __temp__str__a = #__InterfaceTypeA; \
		static const FString __temp__str__b = #__InterfaceTypeB; \
		return NCsValid::NInterface::FLibrary::InterfaceCast<__InterfaceTypeA, __InterfaceTypeB>(Context, __In__##__Interface, __temp__str__, __temp__str__a, __temp__str__b, Log); \
	}(Context, __Interface, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_CONST_INTERFACE_TO_INTERFACE_CAST(__Interface, __InterfaceTypeA, __InterfaceTypeB) \
	[] (const FString& Context, const __InterfaceTypeA* __In__##__Interface, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__  = #__Interface; \
		static const FString __temp__str__a = #__InterfaceTypeA; \
		static const FString __temp__str__b = #__InterfaceTypeB; \
		return NCsValid::NInterface::FLibrary::InterfaceCast<__InterfaceTypeA, __InterfaceTypeB>(Context, __In__##__Interface, __temp__str__, __temp__str__a, __temp__str__b, Log); \
	}(Context, __Interface, Log)

#pragma endregion Interface

// Delegate
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_DELEGATE_BOUND(__Delegate) \
	{ \
		static const FString __temp__str__ = #__Delegate; \
		if (!__Delegate.IsBound()) \
		{ \
			if (Log) \
				Log(FString::Printf(TEXT("%s: %s is NOT Bound."), *Context, *__temp__str__)); \
			return false; \
		} \
		return true; \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_DELEGATE_BOUND_EXIT(__Delegate) \
	{ \
		static const FString __temp__str__ = #__Delegate; \
		if (!__Delegate.IsBound()) \
		{ \
			if (Log) \
				Log(FString::Printf(TEXT("%s: %s is NOT Bound."), *Context, *__temp__str__)); \
			return; \
		} \
	}

#pragma endregion Delegate

// Editor
#pragma region

#if WITH_EDITOR

	// Ptr
#pragma region

// Assume const FString& Context has been defined
#define CS_EDITOR_IS_PTR_NULL_CHECKED(__Ptr) \
	{ \
		static const FString __temp__str__ = #__Ptr; \
		check(NCsValid::NPtr::FLibrary::NullChecked(Context, __Ptr, __temp__str__)); \
	}

#pragma endregion Ptr

#else

	// Ptr
#define CS_EDITOR_IS_PTR_NULL_CHECKED(__Ptr)

#endif // #if WITH_EDITOR

#pragma endregion Editor