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
		};
	}

	namespace NFloat
	{
		struct CSCORE_API FLibrary final
		{
		public:

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

	namespace NEnum
	{
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
		};
	}

	namespace NPtr
	{
		struct CSCORE_API FLibrary final
		{
			FORCEINLINE static bool NullChecked(const FString& Context, void* Ptr, const FString& PtrName)
			{
				checkf(Ptr, TEXT("%s: %s is NULL."), *Context, *PtrName);
				return true;
			}

			FORCEINLINE static bool Null(const FString& Context, void* Ptr, const FString& PtrName, void(*Log)(const FString&))
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
}

#if !UE_BUILD_SHIPPING
// Int

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

// Float

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

// FName

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

// EnumStruct

// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_IS_ENUM_STRUCT_IS_VALID(__EnumMapType, __EnumType, __Enum) \
	{ \
		static const FString __temp__str__ = #__Enum; \
		if (!NCsValid::NEnum::NStruct::FLibrary::IsValid<__EnumMapType, __EnumType>(Context, __Enum, __temp__str__, Log)) { return false; } \
	}

// Array

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

// Ptr

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
#else
// Int
#define CS_IS_INT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL(__A, __B)
#define CS_IS_INT_GREATER_THAN_OR_EQUAL_EXIT(__A, __B)
// Float
#define CS_IS_FLOAT_GREATER_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(__A, __B)
#define CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(__A, __B)
#define CS_IS_FLOAT_COMPARE_LESS_THAN_CHECKED(__A, __B)
#define CS_IS_FLOAT_COMPARE_LESS_THAN(__A, __B)
// FName
#define CS_IS_NAME_NONE_CHECKED(__A)
#define CS_IS_NAME_NONE(__A)
// EnumStruct
#define CS_IS_ENUM_STRUCT_IS_VALID(__EnumMapType, __EnumType, __Enum)
// Array
#define CS_IS_ARRAY_EMPTY_CHECKED(__Array, __ValueType)
#define CS_IS_ARRAY_EMPTY(__Array, __ValueType)
#define CS_IS_ARRAY_EMPTY_EXIT(__Array, __ValueType)
// Ptr
#define CS_IS_PTR_NULL_CHECKED(__Ptr)
#define CS_IS_PTR_NULL(__Ptr)
#define CS_IS_PTR_NULL_EXIT(__Ptr)
#endif // #if !UE_BUILD_SHIPPING
