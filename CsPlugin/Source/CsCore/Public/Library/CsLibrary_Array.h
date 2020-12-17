// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class CSCORE_API FCsLibrary_Array
{
// TArray
#pragma region
public:

	template<typename T>
	static bool AreTArraysEqual(TArray<T>& A, TArray<T>& B)
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
	static bool AreTArraysEqual(TArray<T*>& A, TArray<T*>& B)
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
	static void CopyTArrays(TArray<T>& To, TArray<T>& From, T(*CreateAndCopy)(const T&)=nullptr)
	{
		To.Reset();
		
		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add(CreateAndCopy ? (*CreateAndCopy)(From[I]) : From[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<T*>& To, TArray<T*>& From)
	{
		To.Reset();

		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add(From[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<T*>& To, TArray<T*>* From)
	{
		To.Reset();

		const int32 Count = From->Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add((*From)[I]);
		}
	}

	template<typename T>
	static void CopyTArrays(TArray<TSoftObjectPtr<T>>& To, TArray<TSoftObjectPtr<T>>& From)
	{
		To.Reset();

		const int32 Count = From.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			To.Add(From[I]);
		}
	}

	template<typename T>
	static void NullAndEmptyTArray(TArray<T*>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			A[I] = nullptr;
		}
		A.Empty();
	}

	template<typename T>
	static void NullAndEmptyTArray(TArray<TWeakObjectPtr<T>>& A)
	{
		const int32 Count = A.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			A[I] = nullptr;
		}
		A.Empty();
	}

	template<typename T>
	static bool IsAnyElementInTArrayNull(TArray<T*>& A)
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
	static bool IsAnyElementInTArrayNull(TArray<TWeakObjectPtr<T>>& A)
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
	static bool AreAllElementsInTArrayNotNull(TArray<T*>& A)
	{
		return !IsAnyElementInTArrayNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayNotNull(TArray<TWeakObjectPtr<T>>& A)
	{
		return !IsAnyElementInTArrayNull<T>(A);
	}

	template<typename T>
	static bool IsAnyElementInTArrayTSoftObjectPtrNull(TArray<TSoftObjectPtr<T>>& A)
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
	static bool IsAnyElementInTArrayTSoftObjectPtrNull(TArray<TSoftObjectPtr<T>>* &A)
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
	static bool IsAnyElementInTArrayTSoftClassPtrNull(TArray<TSoftClassPtr<T>>& A)
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
	static bool IsAnyElementInTArrayTSoftClassPtrNull(TArray<TSoftClassPtr<T>>* &A)
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
	static bool AreAllElementsInTArrayAssetPtrNotNull(TArray<TSoftObjectPtr<T>>& A)
	{
		return !IsAnyElementInTArrayTSoftObjectPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetPtrNotNull(TArray<TSoftObjectPtr<T>>* &A)
	{
		return !IsAnyElementInTArrayTSoftObjectPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetSubclassOfNotNull(TArray<TSoftClassPtr<T>>& A)
	{
		return !IsAnyElementInTArrayTSoftClassPtrNull<T>(A);
	}

	template<typename T>
	static bool AreAllElementsInTArrayAssetSubclassOfNotNull(TArray<TSoftClassPtr<T>>* &A)
	{
		return !IsAnyElementInTArrayTSoftClassPtrNull<T>(A);
	}

	template<typename T>
	static void ShuffleTArray(TArray<T>& InArray)
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

#pragma endregion TArray

// Fixed Array
#pragma region
public:

	template<typename T>
	void CopyFixedArrays(T* To, T* From, const int32 &Size)
	{
	}

#pragma endregion Fixed Array
};