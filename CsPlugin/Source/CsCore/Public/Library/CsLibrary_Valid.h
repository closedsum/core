// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

namespace NCsValid
{
	namespace NFloat
	{
		struct CIMPL_API FLibrary final
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
		};
	}

	namespace NName
	{
		struct CIMPL_API FLibrary final 
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
}

#if !UE_BUILD_SHIPPING
// Float

// Assume const FString& Context has been defined
#define CS_FLOAT_GREATER_THAN_CHECKED(__A, __B) check(NCsValid::NFloat::FLibrary::GreaterThanChecked(Context, __A, #__A, __B))
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_FLOAT_GREATER_THAN(__A, __B) if (!NCsValid::NFloat::FLibrary::GreaterThan(Context, __A, #__A, __B, Log)) { return false; }

// FName

// Assume const FString& Context has been defined
#define CS_NAME_NONE_CHECKED(__A) check(NCsValid::NName::FLibrary::NoneChecked(Context, __A, #__A))
// Assume const FString& Context and void(Log*)(const FString&) have been defined
#define CS_NAME_NONE(__A) if (!NCsValid::NName::FLibrary::None(Context, __A, #__A, Log)) { return false; }
#else
// Float
#define CS_FLOAT_GREATER_THAN_CHECKED(__A, __B)
#define CS_FLOAT_GREATER_THAN(__A, __B)
// FName
#define CS_NAME_NONE_CHECKED(__A)
#define CS_NAME_NONE(__A)
#endif // #if !UE_BUILD_SHIPPING
