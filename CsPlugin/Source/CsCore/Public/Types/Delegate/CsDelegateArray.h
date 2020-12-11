// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

template<typename DelegateType>
struct TCsDelegateArray
{
public:

	TArray<DelegateType> Delegates;

	TArray<FDelegateHandle> Handles;

	TArray<bool> IsBoundFlags;
	TArray<bool> IsExplicitClearFlags;

	TArray<int32> IndexByOrder;

	TCsDelegateArray() :
		Delegates(),
		Handles(),
		IsBoundFlags(),
		IsExplicitClearFlags(),
		IndexByOrder(),
		EndPosition(0)
	{
	}
	
private:
	int32 EndPosition;
public:
	
	// Range-based for loop
	class ConstIterator
	{
		TCsDelegateArray<DelegateType>* Array;
		int32 Position;
	public:
		ConstIterator(TCsDelegateArray<DelegateType>* _Array, int32 _Position) :Array(_Array), Position(_Position) {}

		const DelegateType& operator*() const { return Array->GetAtPosition(Position); }
		ConstIterator& operator++() { ++Position; return *this; }
		bool operator!=(const ConstIterator& It) const { return Position != It.Position; }
	};

public:

	ConstIterator const begin() { return { this, 0 }; }
	ConstIterator const end() { return { this, EndPosition }; }
	
	const FDelegateHandle& Add(const DelegateType& InDelegate, bool IsExplicitClear = false)
	{
		checkf(InDelegate.IsBound(), TEXT("TCsDelegateArray::Add: InDelegate is NOT Bound."));

		if (Delegates.Num() == EndPosition)
		{
			Delegates.AddDefaulted();
			Handles.AddDefaulted();
			IsBoundFlags.AddDefaulted();
			IsBoundFlags[EndPosition] = false;
			IsExplicitClearFlags.AddDefaulted();
			IsExplicitClearFlags[EndPosition] = false;
			IndexByOrder.AddDefaulted();
			IndexByOrder[EndPosition] = INDEX_NONE;
		}

		++EndPosition;

		// Get First Unbound Index
		int32 FirstUnboundIndex = INDEX_NONE;

		for (int32 I = 0; I < EndPosition; ++I)
		{
			if (!IsBoundFlags[I])
			{
				FirstUnboundIndex = I;
				break;
			}
		}

		// Get First Free Position in Index By Order
		int32 FreePositionIndex = INDEX_NONE;

		for (int32 I = 0; I < EndPosition; ++I)
		{
			if (IndexByOrder[I] == INDEX_NONE)
			{
				FreePositionIndex = I;
				break;
			}
		}

		IndexByOrder[FreePositionIndex] = FirstUnboundIndex;

		DelegateType& Delegate = Delegates[FirstUnboundIndex];
		// TODO: May need to look at the platform agnostic way?
		//Delegate = std::move(InDelegate);
		Delegate = InDelegate;

		IsExplicitClearFlags[FirstUnboundIndex] = IsExplicitClear;

		Handles[FirstUnboundIndex] = Delegate.GetHandle();

		return Handles[FirstUnboundIndex];
	}

	FORCEINLINE const DelegateType& GetAtPosition(const int32& Index)
	{
		return Delegates[IndexByOrder[Index]];
	}

	// TODO: Broadcast

	void Clear(const FDelegateHandle& Handle)
	{
		bool Success = false;
		int32 Count  = 0;

		for (int32 I = 0; I < EndPosition; ++I)
		{
			if (Handle == Handles[I])
			{
				Delegates[I].Unbind();
				Handles[I].Reset();
				IsBoundFlags[I] = false;
				IndexByOrder[I] = INDEX_NONE;

				Success = true;
			}
			else
			{
				IndexByOrder[Count] = I;
				++Count;
			}
		}

		if (Success)
			--EndPosition;
	}

	void Clear()
	{
		int32 Count = 0;

		for (int32 I = 0; I < EndPosition; ++I)
		{
			// If Explicit, Move towards the front
			if (IsExplicitClearFlags[I])
			{
				IndexByOrder[Count] = I;
				++Count;
			}
			// Else unbind
			else
			{
				Delegates[I].Unbind();
				Handles[I].Reset();
				IsBoundFlags[I] = false;
				IndexByOrder[I] = INDEX_NONE;
			}
		}
		EndPosition = 0;
	}
};