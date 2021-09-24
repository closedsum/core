// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;
class UClass;
class UWorld;

namespace NCsValid
{
	namespace NInt
	{
		struct CSCORE_API FLibrary final
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
		};
	}

	namespace NFloat
	{
		struct CSCORE_API FLibrary final
		{
		public:

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
		};

		namespace NCompare
		{
			struct CSCORE_API FLibrary final
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
		struct CSCORE_API FLibrary final
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
		struct CSCORE_API FLibrary final
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

	namespace NEnum
	{
		struct CSCORE_API FLibrary final
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
		};

		namespace NStruct
		{
			struct CSCORE_API FLibrary final
			{
			public:

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
		struct CSCORE_API FLibrary final
		{
		public:

			FORCEINLINE static bool IsZeroChecked(const FString& Context, const FVector& V, const FString& VName)
			{
				checkf(V != FVector::ZeroVector, TEXT("%s: %s == (0.0f, 0.0f, 0.0f) or ZeroVector is NOT Valid."), *Context, *VName);
				return true;
			}

			FORCEINLINE static bool IsZero(const FString& Context, const FVector& V, const FString& VName, void(*Log)(const FString&))
			{
				if (V == FVector::ZeroVector)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s == (0.0f, 0.0f, 0.0f) or ZeroVector is NOT Valid."), *Context, *VName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NArray
	{
		struct CSCORE_API FLibrary final
		{
			template<typename ValueType>
			FORCEINLINE static bool EmptyChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName)
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

			template<typename ValueType>
			FORCEINLINE static bool LessThanOrEqualSizeChecked(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size)
			{
				checkf(Array.Num() <= Size, TEXT("%s: %s.Num() > %d."), *Context, *ArrayName, Size);
				return true;
			}

			template<typename ValueType>
			FORCEINLINE static bool LessThanOrEqualSize(const FString& Context, const TArray<ValueType>& Array, const FString& ArrayName, const int32& Size, void(*Log)(const FString&))
			{
				if (Array.Num() > Size)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s.Num() > %d."), *Context, *ArrayName, Size));
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

			FORCEINLINE static bool IsAnyNoneChecked(const FString& Context, const TArray<FName>& Array, const FString& ArrayName)
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
		};
	}

	namespace NPtr
	{
		struct CSCORE_API FLibrary final
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
		struct CSCORE_API FLibrary final
		{
			template<typename ClassType, typename OtherClassType>
			FORCEINLINE static bool IsClassOf(const FString& Context, const ClassType* A, const FString& AName, void(*Log)(const FString&))
			{
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return false;
				}

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
				checkf(A, TEXT("%s: %s is NULL."), *Context, *AName);

				const OtherClassType* Other = Cast<OtherClassType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName()));
				return true;
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static bool Implements(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName, void(*Log)(const FString&))
			{
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return false;
				}

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
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return nullptr;
				}

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
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return nullptr;
				}

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
				checkf(A, TEXT("%s: %s is NULL."), *Context, *AName);

				OtherClassType* Other = Cast<OtherClassType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does is NOT of type: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *(OtherClassType::StaticClass()->GetName()));

				return Other;
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static InterfaceType* InterfaceCast(const FString& Context, ClassType* A, const FString& AName, const FString& InterfaceName, void(*Log)(const FString&))
			{
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return nullptr;
				}

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
				if (!A)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return nullptr;
				}

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
				checkf(A, TEXT("%s: %s is NULL."), *Context, *AName);

				InterfaceType* Other = Cast<InterfaceType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName);

				return Other;
			}

			template<typename ClassType, typename InterfaceType>
			FORCEINLINE static const InterfaceType* InterfaceCastChecked(const FString& Context, const ClassType* A, const FString& AName, const FString& InterfaceName)
			{
				checkf(A, TEXT("%s: %s is NULL."), *Context, *AName);

				const InterfaceType* Other = Cast<InterfaceType>(A);

				checkf(Other, TEXT("%s: %s: %s with Class: %s does NOT implement the interface: %s."), *Context, *AName, *(A->GetName()), *(A->GetClass()->GetName()), *InterfaceName);

				return Other;
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* NewChecked(const FString& Context, UObject* Outer, const FString& OuterName, UClass* Class, const FString& ClassName)
			{
				checkf(Outer, TEXT("%s: %s is NULL."), *Context, *OuterName);

				checkf(Class, TEXT("%s: %s is NULL."), *Context, *ClassName);

				ObjectType* O = NewObject<ObjectType>(Outer, Class);

				checkf(O, TEXT("%s: Failed to create Object from Class: %s."), *Context, *(Class->GetName()));
				
				return O;
			}

			template<typename ObjectType>
			FORCEINLINE static ObjectType* NewChecked(const FString& Context, UObject* Outer, const FString& OuterName, TSubclassOf<ObjectType>& Class, const FString& ClassName)
			{
				checkf(Outer, TEXT("%s: %s is NULL."), *Context, *OuterName);

				checkf(Class.Get(), TEXT("%s: %s is NULL."), *Context, *ClassName);

				ObjectType* O = NewObject<ObjectType>(Outer, Class);

				checkf(O, TEXT("%s: Failed to create Object from Class: %s."), *Context, *(Class->GetName()));

				return O;
			}
		};
	}

	namespace NWeakObjectPtr
	{
		struct CSCORE_API FLibrary final
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

	namespace NSoftObjectPath
	{
		struct CSCORE_API FLibrary final
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
		struct CSCORE_API FLibrary final
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
						Log(FString::Printf(TEXT("%s: %s is NULL."), *Context, *AName));
					return false;
				}
				return true;
			}
		};
	}

	namespace NActor
	{
		struct CSCORE_API FLibrary final
		{
		public:

			template<typename ActorType>
			FORCEINLINE static ActorType* SpawnChecked(const FString& Context, UWorld* World, UClass* Class, const FString& ClassName)
			{
				checkf(World, TEXT("%s: World is NULL."), *Context);

				checkf(Class, TEXT("%s: %s is NULL."), *Context, *ClassName);

				ActorType* A = World->SpawnActor<ActorType>(Class);

				checkf(A, TEXT("%s: Failed to Spawn Actor of type: %s from %s of type: %s."), *Context, *(ActorType::StaticClass()->GetName()), *ClassName, *(Class->GetName()));

				return A;
			}
		};
	}
}

// CHECKED

#if !UE_BUILD_SHIPPING
// Assume const FString& Context has been defined
#define CS_IS_VALID_CHECKED(__Object) __Object.IsValidChecked(Context)

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

#pragma endregion Int

// Float
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_FLOAT_NOT_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::NotEqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::GreaterThanChecked(Context, __A, __temp__str__, __B)); \
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

// Enum
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_ENUM_VALID_CHECKED(__EnumMapType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		check(__EnumMapType::Get().IsValidEnumChecked(Context, __temp__str__, __Enum)); \
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

#pragma endregion EnumStruct

// FVector
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_VECTOR_ZERO_CHECKED(__V) \
	{ \
		static const FString __temp__str__ = #__V; \
		check(NCsValid::NVector::FLibrary::IsZeroChecked(Context, __V, __temp__str__)); \
	}

#pragma endregion FVector

// Array
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_ARRAY_EMPTY_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::EmptyChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::LessThanOrEqualSizeChecked<__ValueType>(Context, __Array, __temp__str__, __Size)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ARRAY_ANY_NULL_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyNullChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context has been defined
#define CS_IS_ARRAY_ANY_NONE_CHECKED(__Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyNoneChecked(Context, __Array, __temp__str__)); \
	}

#pragma endregion Array

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
#define CS_IS_OBJ_CLASS_OF_CHECKED(__Object, __ObjectType, __ClassType) \
	{ \
		static const FString __temp__str__ = #__Object; \
		check((NCsValid::NObject::FLibrary::IsClassOfChecked<__ObjectType, __ClassType>(Context, __Object, __temp__str__))); \
	}
// Assume const FString& Context has been defined
#define CS_CAST_CHECKED(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, __ObjectType* __Object) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastToChecked<__ObjectType, __OtherObjectType>(Context, __Object, __temp__str__); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, __ObjectType* __Object) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, const __ObjectType* __Object) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_NEW_CHECKED(__ObjectType, __Outer, __Class) \
	[] (const FString& Context, UObject* __Outer, UClass* __Class) \
	{ \
		static const FString __temp__str__a = #__Outer; \
		static const FString __temp__str__b = #__Class; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __Outer, __temp__str__a, __Class, __temp__str__b); \
	}(Context, __Outer, __Class)
// Assume const FString& Context has been defined and this is passed out Outer for NewObject
#define CS_NEW_BY_THIS_AND_SUBCLASS_OF_CHECKED(__ObjectType, __Class) \
	[] (const FString& Context, UObject* __Outer, TSubclassOf<__ObjectType>& __Class) \
	{ \
		static const FString __temp__str__a = TEXT("this"); \
		static const FString __temp__str__b = #__Class; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __Outer, __temp__str__a, __Class, __temp__str__b); \
	}(Context, this, __Class)

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

#pragma endregion WeakObjectPtr

// Actor
#pragma region

// Assume const FString& Context has been defined and this->GetWorld() exists
#define CS_SPAWN_ACTOR_CHECKED(__ActorType, __Class) \
	[] (const FString& Context, UWorld* __World, UClass* __Class) \
	{ \
		static const FString __temp__str__a = #__Class; \
		return NCsValid::NActor::FLibrary::SpawnChecked<__ActorType>(Context, __World, __Class, __temp__str__a); \
	}(Context, GetWorld(), __Class)

#pragma endregion Actor

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
// Int
#define CS_IS_INT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_CHECKED(__A, __B, __C)
// Float
#define CS_IS_FLOAT_NOT_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_COMPARE_LESS_THAN_CHECKED(__A, __B)
// FName
#define CS_IS_NAME_NONE_CHECKED(__A)
// FString
#define CS_IS_STRING_EMPTY_CHECKED(__A)
// Enum
#define CS_IS_ENUM_VALID_CHECKED(__EnumMapType, __Enum)
// EnumStruct
#define CS_IS_ENUM_STRUCT_VALID_CHECKED(__EnumMapType, __Enum)
// FVector
#define CS_IS_VECTOR_ZERO_CHECKED(__V)
// Array
#define CS_IS_ARRAY_EMPTY_CHECKED(__Array, __ValueType)
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size)
#define CS_IS_ARRAY_ANY_NULL_CHECKED(__Array, __ValueType)
#define CS_IS_ARRAY_ANY_NONE_CHECKED(__Array)
// Ptr
#define CS_IS_PTR_NULL_CHECKED(__Ptr)
// Object
#define CS_IS_OBJ_CLASS_OF_CHECKED(__Object, __ObjectType, __ClassType)
// Assume const FString& Context has been defined
#define CS_CAST_CHECKED(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, __ObjectType* __Object) \
	{ \
		static const FString __temp__str__; \
		return NCsValid::NObject::FLibrary::CastToChecked<__ObjectType, __OtherObjectType>(Context, __Object, __temp__str__); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, __ObjectType* __Object) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_CONST_INTERFACE_CAST_CHECKED(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, const __ObjectType* __Object) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::InterfaceCastChecked<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b); \
	}(Context, __Object)
// Assume const FString& Context has been defined
#define CS_NEW_CHECKED(__ObjectType, __Outer, __Class) \
	[] (const FString& Context, UObject* __Outer, UClass* __Class) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __Outer, __temp__str__a, __Class, __temp__str__b); \
	}(Context, __Outer, __Class)
// Assume const FString& Context has been defined and this is passed out Outer for NewObject
#define CS_NEW_BY_THIS_AND_SUBCLASS_OF_CHECKED(__ObjectType, __Class) \
	[] (const FString& Context, UObject* __Outer, TSubclassOf<__ObjectType>& __Class) \
	{ \
		static const FString __temp__str__a; \
		static const FString __temp__str__b; \
		return NCsValid::NObject::FLibrary::NewChecked<__ObjectType>(Context, __Outer, __temp__str__a, __Class, __temp__str__b); \
	}(Context, this, __Class)
// WeakObjectPtr
#define CS_IS_WEAK_OBJ_PTR_NULL_CHECKED(__Ptr, __ObjectType)
// FSoftObjectPath
#define CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(__A)
// SubclassOf
#define CS_IS_SUBCLASS_OF_NULL_CHECKED(__Class, __ObjectType)
// Actor
// Assume const FString& Context has been defined and this->GetWorld() exists
#define CS_SPAWN_ACTOR_CHECKED(__ActorType, __Class) \
	[] (const FString& Context, UWorld* __World, UClass* __Class) \
	{ \
		static const FString __temp__str__a; \
		return NCsValid::NActor::FLibrary::SpawnChecked<__ActorType>(Context, __World, __Class, __temp__str__a); \
	}(Context, GetWorld(), __Class)
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

#pragma endregion Int

// Float
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_NOT_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::NotEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, __temp__str__, __B, Log)) { return false; } \
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
#define CS_IS_FLOAT_COMPARE_LESS_THAN(__A, __B) \
	{ \
		static const FString __temp__str__a__ = #__A; \
		static const FString __temp__str__b__ = #__B; \
		if (!NCsValid::NFloat::NCompare::FLibrary::LessThan(Context, __A, __temp__str__a__, __B, __temp__str__b__, Log)) { return false; } \
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
#define CS_IS_STRING_EMPTY_RET_NULL(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NString::FLibrary::Empty(Context, __A, __temp__str__, Log)) { return nullptr; } \
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

#pragma endregion EnumStruct

// FVector
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_VECTOR_ZERO(__V) \
	{ \
		static const FString __temp__str__ = #__V; \
		if (!NCsValid::NVector::FLibrary::IsZero(Context, __V, __temp__str__, Log)) { return false; } \
	}

#pragma endregion FVector

// Array
#pragma region

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_EMPTY(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_EMPTY_EXIT(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::Empty<__ValueType>(Context, __Array, __temp__str__, Log)) { return; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::LessThanOrEqualSize<__ValueType>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_ANY_NULL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNull<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_ANY_NONE(__Array) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNone(Context, __Array, __temp__str__, Log)) { return false; } \
	}

#pragma endregion Array

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

#pragma endregion Ptr

// Object
#pragma region

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
	[] (const FString& Context, __ObjectType* __Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastTo<__ObjectType, __OtherObjectType>(Context, __Object, __temp__str__, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_CONST_CAST(__Object, __ObjectType, __OtherObjectType) \
	[] (const FString& Context, const __ObjectType* __Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__ = #__Object; \
		return NCsValid::NObject::FLibrary::CastTo<__ObjectType, __OtherObjectType>(Context, __Object, __temp__str__, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_INTERFACE_CAST(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, __ObjectType* __Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCast<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b, Log); \
	}(Context, __Object, Log)
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_CONST_INTERFACE_CAST(__Object, __ObjectType, __InterfaceType) \
	[] (const FString& Context, const __ObjectType* __Object, void(*Log)(const FString&)) \
	{ \
		static const FString __temp__str__a = #__Object; \
		static const FString __temp__str__b = #__InterfaceType; \
		return NCsValid::NObject::FLibrary::InterfaceCast<__ObjectType, __InterfaceType>(Context, __Object, __temp__str__a, __temp__str__b, Log); \
	}(Context, __Object, Log)

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

#pragma endregion WeakObjectPtr

// FSoftObjectPath
#pragma region 

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPath::FLibrary::IsValid(Context, __A, __temp__str__, Log)) { return false; } \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NSoftObjectPath::FLibrary::IsValid(Context, __A, __temp__str__, Log)) { return nullptr; } \
	}

#pragma endregion FSoftObjectPath

// SubclassOf
#pragma region

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

#pragma endregion SubclassOf

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