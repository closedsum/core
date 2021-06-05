// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

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
}

#if !UE_BUILD_SHIPPING
// Int
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_INT_GREATER_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::GreaterThanChecked(Context, __A, __temp__str__, __B)); \
	}
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
// Assume const FString& Context has been defined
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::GreaterThanOrEqualChecked(Context, __A, __temp__str__, __B)); \
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
// Assume const FString& Context has been defined
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_CHECKED(__A, __B, __C) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NInt::FLibrary::GreaterThanAndLessThanOrEqualChecked(Context, __A, __temp__str__, __B, __C)); \
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

// Assume const FString& Context has been defined
#define CS_IS_FLOAT_NOT_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::NotEqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_NOT_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::NotEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::GreaterThanChecked(Context, __A, __temp__str__, __B)); \
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
// Assume const FString& Context has been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NFloat::FLibrary::GreaterThanOrEqualChecked(Context, __A, __temp__str__, __B)); \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(__A, __B) \
	{ \
		static const FString __temp__str__ = #__A; \
		if (!NCsValid::NFloat::FLibrary::GreaterThanOrEqual(Context, __A, __temp__str__, __B, Log)) { return false; } \
	}

// Assume const FString& Context has been defined
#define CS_IS_FLOAT_COMPARE_LESS_THAN_CHECKED(__A, __B) \
	{ \
		static const FString __temp__str__a__ = #__A; \
		static const FString __temp__str__b__ = #__B; \
		check(NCsValid::NFloat::NCompare::FLibrary::LessThanChecked(Context, __A, __temp__str__a__, __B, __temp__str__b__)); \
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

// Assume const FString& Context has been defined
#define CS_IS_NAME_NONE_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NName::FLibrary::NoneChecked(Context, __A, __temp__str__)); \
	}
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

// Assume const FString& Context has been defined
#define CS_IS_STRING_EMPTY_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NString::FLibrary::EmptyChecked(Context, __A, __temp__str__)); \
	}
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

#pragma endregion EnumStruct

// Array
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_ARRAY_EMPTY_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::EmptyChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
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
// Assume const FString& Context has been defined
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::LessThanOrEqualSizeChecked<__ValueType>(Context, __Array, __temp__str__, __Size)); \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __Size) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::LessThanOrEqualSize<__ValueType>(Context, __Array, __temp__str__, __Size, Log)) { return false; } \
	}
// Assume const FString& Context has been defined
#define CS_IS_ARRAY_ANY_NULL_CHECKED(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		check(NCsValid::NArray::FLibrary::IsAnyNullChecked<__ValueType>(Context, __Array, __temp__str__)); \
	}
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ARRAY_ANY_NULL(__Array, __ValueType) \
	{ \
		static const FString __temp__str__ = #__Array; \
		if (!NCsValid::NArray::FLibrary::IsAnyNull<__ValueType>(Context, __Array, __temp__str__, Log)) { return false; } \
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

#pragma endregion Ptr

// FSoftObjectPath
#pragma region 

// Assume const FString& Context has been defined
#define CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(__A) \
	{ \
		static const FString __temp__str__ = #__A; \
		check(NCsValid::NSoftObjectPath::FLibrary::IsValidChecked(Context, __A, __temp__str__)); \
	}
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

// Delegate
#pragma region

// Assume const FString& Context has been defined
#define CS_IS_DELEGATE_BOUND_CHECKED(__Delegate) \
	{ \
		static const FString __temp__str__ = #__Delegate; \
		checkf(__Delegate.IsBound(), TEXT("%s: %s is NOT Bound."), *Context, *__temp__str__); \
	}
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

#else
// Int
#define CS_IS_INT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN(__A, __B)
#define CS_IS_INT_GREATER_THAN_EXIT(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_EXIT(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_RET_NULL(__A, __B)
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_CHECKED(__A, __B, __C)
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL(__A, __B, __C)
#define CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_RET_NULL(__A, __B, __C)
// Float
#define CS_IS_FLOAT_NOT_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_NOT_EQUAL(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_RET_NULL(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(__A, __B)
#define CS_IS_FLOAT_COMPARE_LESS_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_COMPARE_LESS_THAN(__A, __B)
// FName
#define CS_IS_NAME_NONE_CHECKED(__A)
#define CS_IS_NAME_NONE(__A)
#define CS_IS_NAME_NONE_RET_NULL(__A)
#define CS_IS_NAME_NONE_EXIT(__A)
// FString
#define CS_IS_STRING_EMPTY_CHECKED(__A)
#define CS_IS_STRING_EMPTY(__A)
#define CS_IS_STRING_EMPTY_RET_NULL(__A)
// EnumStruct
#define CS_IS_ENUM_STRUCT_VALID(__EnumMapType, __EnumType, __Enum)
#define CS_IS_ENUM_STRUCT_VALID_EXIT(__EnumMapType, __EnumType, __Enum)
#define CS_IS_ENUM_STRUCT_VALID_RET_NULL(__EnumMapType, __EnumType, __Enum)
// Array
#define CS_IS_ARRAY_EMPTY_CHECKED(__Array, __ValueType)
#define CS_IS_ARRAY_EMPTY(__Array, __ValueType)
#define CS_IS_ARRAY_EMPTY_EXIT(__Array, __ValueType)
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(__Array, __ValueType, __Size)
#define CS_IS_ARRAY_LESS_THAN_OR_EQUAL_SIZE(__Array, __ValueType, __Size)
#define CS_IS_ARRAY_ANY_NULL_CHECKED(__Array, __ValueType)
#define CS_IS_ARRAY_ANY_NULL(__Array, __ValueType)
// Ptr
#define CS_IS_PTR_NULL_CHECKED(__Ptr)
#define CS_IS_PTR_NULL(__Ptr)
#define CS_IS_PTR_NULL_EXIT(__Ptr)
#define CS_IS_PTR_NULL_RET_NULL(__Ptr)
// FSoftObjectPath
#define CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(__A)
#define CS_IS_SOFT_OBJECT_PATH_VALID(__A)
#define CS_IS_SOFT_OBJECT_PATH_VALID_RET_NULL(__A)
// Delegate
#define CS_IS_DELEGATE_BOUND_CHECKED(__Delegate)
#define CS_IS_DELEGATE_BOUND(__Delegate)
#define CS_IS_DELEGATE_BOUND_EXIT(__Delegate)
#endif // #if !UE_BUILD_SHIPPING
