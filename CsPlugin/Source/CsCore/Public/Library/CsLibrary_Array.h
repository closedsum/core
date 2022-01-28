// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

namespace NCsArray
{
	struct CSCORE_API FLibrary final
	{
	// TArray
	#pragma region
	public:

		template<typename T>
		static bool AreEqual(TArray<T>& A, TArray<T>& B)
		{
			if (A.Num() != B.Num())
				return false;

			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (A[I] != B[I])
					return false;
			}
			return true;
		}

		template<typename T>
		static bool AreEqual(TArray<T*>& A, TArray<T*>& B)
		{
			if (A.Num() != B.Num())
				return false;

			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (A[I] != B[I])
					return false;
			}
			return true;
		}

		template<typename T>
		static void Copy(TArray<T>& To, const TArray<T>& From, T(*CreateAndCopy)(const T&)=nullptr)
		{
			To.Reset(FMath::Max(To.Max(), From.Num()));
		
			const int32 Count = From.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				To.Add(CreateAndCopy ? (*CreateAndCopy)(From[I]) : From[I]);
			}
		}

		template<typename T>
		static void Copy(TArray<T*>& To, const TArray<T*>& From)
		{
			To.Reset(FMath::Max(To.Max(), From.Num()));

			const int32 Count = From.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				To.Add(From[I]);
			}
		}

		template<typename T>
		static void Copy(TArray<T*>& To, const TArray<T*>* From)
		{
			To.Reset(FMath::Max(To.Max(), From->Num()));

			const int32 Count = From->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				To.Add((*From)[I]);
			}
		}

		template<typename T>
		static void Copy(TArray<TSoftObjectPtr<T>>& To, const TArray<TSoftObjectPtr<T>>& From)
		{
			To.Reset(FMath::Max(To.Max(), From.Num()));

			const int32 Count = From.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				To.Add(From[I]);
			}
		}

		template<typename T>
		FORCEINLINE static void NullAndEmpty(TArray<T*>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				A[I] = nullptr;
			}
			A.Empty();
		}

		template<typename T>
		FORCEINLINE static void NullAndEmpty(TArray<TWeakObjectPtr<T>>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				A[I] = nullptr;
			}
			A.Empty();
		}

		template<typename T>
		FORCEINLINE static bool IsAnyElementNull(TArray<T*>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!A[I])
					return true;
			}
			return false;
		}

		template<typename T>
		FORCEINLINE static bool IsAnyElementNull(TArray<TWeakObjectPtr<T>>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!A[I].IsValid() || !A[I].Get())
					return true;
			}
			return false;
		}

		template<typename T>
		FORCEINLINE static bool IsAnyElementNotValid(TArray<TSoftObjectPtr<T>>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!A[I].IsValid())
					return true;
			}
			return false;
		}

		template<typename T>
		FORCEINLINE static bool AreAllElementsNotNull(TArray<T*>& A)
		{
			return !IsAnyElementNull<T>(A);
		}

		template<typename T>
		FORCEINLINE static bool AreAllElementsNotNull(TArray<TWeakObjectPtr<T>>& A)
		{
			return !IsAnyElementNull<T>(A);
		}

		template<typename T>
		FORCEINLINE static bool AreAllElementsValid(TArray<TSoftObjectPtr<T>>& A)
		{
			return !IsAnyElementNotValid<T>(A);
		}

		template<typename T>
		static bool IsAnyElementTSoftObjectPtrNull(TArray<TSoftObjectPtr<T>>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!A[I].IsValid() || !A[I].Get())
					return true;
			}
			return false;
		}

		template<typename T>
		static bool IsAnyElementTSoftObjectPtrNull(TArray<TSoftObjectPtr<T>>* &A)
		{
			const int32 Count = A->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!(*A)[I].IsValid() || !(*A)[I].Get())
					return true;
			}
			return false;
		}

		template<typename T>
		static bool IsAnyElementTSoftClassPtrNull(TArray<TSoftClassPtr<T>>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!A[I].IsValid() || !A[I].Get())
					return true;
			}
			return false;
		}

		template<typename T>
		static bool IsAnyElementTSoftClassPtrNull(TArray<TSoftClassPtr<T>>* &A)
		{
			const int32 Count = A->Num();

			for (int32 I = 0; I < Count; ++I)
			{
				if (!(*A)[I].IsValid() || !(*A)[I].Get())
					return true;
			}
			return false;
		}

		template<typename T>
		static bool AreAllElementsAssetPtrNotNull(TArray<TSoftObjectPtr<T>>& A)
		{
			return !IsAnyElementTSoftObjectPtrNull<T>(A);
		}

		template<typename T>
		static bool AreAllElementsAssetPtrNotNull(TArray<TSoftObjectPtr<T>>* &A)
		{
			return !IsAnyElementTSoftObjectPtrNull<T>(A);
		}

		template<typename T>
		static bool AreAllElementsAssetSubclassOfNotNull(TArray<TSoftClassPtr<T>>& A)
		{
			return !IsAnyElementTSoftClassPtrNull<T>(A);
		}

		template<typename T>
		static bool AreAllElementsAssetSubclassOfNotNull(TArray<TSoftClassPtr<T>>* &A)
		{
			return !IsAnyElementTSoftClassPtrNull<T>(A);
		}

		template<typename T>
		static void Shuffle(TArray<T>& InArray)
		{
			const int32 Len = InArray.Num();

			for (int32 Index = Len; Index > 1; --Index)
			{
				int32 J = FMath::RandRange(0, Index - 1);

				T Temp			   = InArray[J];
				InArray[J]		   = InArray[Index - 1];
				InArray[Index - 1] = Temp;
			}
		}

		/**
		* Populate Arr with values from [Min, Max] and then perform a random shuffle.
		* 
		* @param Arr
		* @param Min
		* @param Max
		*/
		static void PopulateRangeAndShuffle(TArray<int32>& Arr, const int32& Min, const int32& Max)
		{
			checkf(Max > Min, TEXT("%d is NOT > %d, (Max is NOT > Min)"), Max, Min);

			const int32 UpperBound = Max + 1;

			Arr.Reset(UpperBound - Min);

			for (int32 I = Min; I < UpperBound; ++I)
			{
				Arr.Add(I);
			}

			Shuffle<int32>(Arr);
		}

		template<typename T>
		static void GetIntersecting(const TArray<T*>& A, const TArray<T*>& B, TArray<T*>& Out)
		{
			for (T* _A : A)
			{
				for (T* _B : B)
				{
					if (_A == _B)
						Out.Add(_A);
				}
			}
		}

		template<typename T>
		static void KeepExclusiveToA(TArray<T*>& A, const TArray<T*>& B)
		{
			const int32 Count = A.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				T* _A = A[I];

				for (T* _B : B)
				{
					if (_A == _B)
					{
						A.RemoveAt(I, 1, false);
						break;
					}
				}
			}
		}

		template<typename T>
		FORCEINLINE static void ResetChecked(const FString& Context, TArray<T*>& A, const int32& Count, const int32& Max)
		{
			checkf(Count > 0, TEXT("%s: Count: %d is NOT > 0."), *Context, Count);

			checkf(Max > 0, TEXT("%s: Max: %d is NOT > 0."), *Context, Max);

			checkf(FMath::Max(A.Max(), Count) <= Max, TEXT("%s: A.Max(): %d and Count: %d are NOT <= %d."), *Context, A.Max(), Count, Max);

			A.Reset(FMath::Max(A.Max(), Count));
		}

		template<typename T>
		FORCEINLINE static void ResetChecked(const FString& Context, TArray<T*>& A, const int32& Count)
		{
			checkf(Count > 0, TEXT("%s: Count: %d is NOT > 0."), *Context, Count);

			A.Reset(FMath::Max(A.Max(), Count));
		}

		template<typename T>
		FORCEINLINE static void ResetChecked(TArray<T*>& A, const int32& Count)
		{
			checkf(Count > 0, TEXT("NCsArray::FLibrary::ResetChecked: Count: %d is NOT > 0."), Count);

			A.Reset(FMath::Max(A.Max(), Count));
		}

		template<typename T>
		FORCEINLINE static void ResetChecked(const FString& Context, TArray<T>& A, const int32& Count, const int32& Max)
		{
			checkf(Count > 0, TEXT("%s: Count: %d is NOT > 0."), *Context, Count);

			checkf(Max > 0, TEXT("%s: Max: %d is NOT > 0."), *Context, Max);

			checkf(FMath::Max(A.Max(), Count) <= Max, TEXT("%s: A.Max(): %d and Count: %d are NOT <= %d."), *Context, A.Max(), Count, Max);

			A.Reset(FMath::Max(A.Max(), Count));
		}

		template<typename T>
		FORCEINLINE static void ResetChecked(const FString& Context, TArray<T>& A, const int32& Count)
		{
			checkf(Count > 0, TEXT("%s: Count: %d is NOT > 0."), *Context, Count);

			A.Reset(FMath::Max(A.Max(), Count));
		}

		template<typename T>
		FORCEINLINE static void ResetChecked(TArray<T>& A, const int32& Count)
		{
			checkf(Count > 0, TEXT("NCsArray::FLibrary::ResetChecked: Count: %d is NOT > 0."), Count);

			A.Reset(FMath::Max(A.Max(), Count));
		}

		template<typename T>
		FORCEINLINE static void RemoveLast(TArray<T>& A)
		{
			A.RemoveAt(A.Num() - 1, 1, false);
		}

	#pragma endregion TArray

	// Fixed Array
	#pragma region
	public:

		template<typename T>
		void CopyFixed(T* To, T* From, const int32 &Size)
		{
		}

	#pragma endregion Fixed Array
	};
}

// Assume const FString& Context has been defined
#define CS_RESET_ARRAY_WITH_MAX_CHECKED(__Array, __Type, __Count, __Max) NCsArray::FLibrary::ResetChecked<__Type>(Context, __Array, __Count, __Max)
// Assume const FString& Context has been defined
#define CS_RESET_ARRAY_CHECKED(__Array, __Type, __Count) NCsArray::FLibrary::ResetChecked<__Type>(Context, __Array, __Count)
#define CS_RESET_ARRAY(__Array, __Type, __Count) NCsArray::FLibrary::ResetChecked<__Type>(__Array, __Count)