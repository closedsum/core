// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
		static void NullAndEmpty(TArray<T*>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				A[I] = nullptr;
			}
			A.Empty();
		}

		template<typename T>
		static void NullAndEmpty(TArray<TWeakObjectPtr<T>>& A)
		{
			const int32 Count = A.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				A[I] = nullptr;
			}
			A.Empty();
		}

		template<typename T>
		static bool IsAnyElementNull(TArray<T*>& A)
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
		static bool IsAnyElementNull(TArray<TWeakObjectPtr<T>>& A)
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
		static bool AreAllElementsNotNull(TArray<T*>& A)
		{
			return !IsAnyElementNull<T>(A);
		}

		template<typename T>
		static bool AreAllElementsNotNull(TArray<TWeakObjectPtr<T>>& A)
		{
			return !IsAnyElementNull<T>(A);
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
		void CopyFixed(T* To, T* From, const int32 &Size)
		{
		}

	#pragma endregion Fixed Array
	};
}