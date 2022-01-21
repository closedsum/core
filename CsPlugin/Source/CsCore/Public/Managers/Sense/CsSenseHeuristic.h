// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsSenseHeuristic.generated.h"
#pragma once

// SenseHeuristic
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSenseHeuristic : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSenseHeuristic)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSenseHeuristic)

struct CSCORE_API EMCsSenseHeuristic : public TCsEnumStructMap<FECsSenseHeuristic, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSenseHeuristic, FECsSenseHeuristic, uint8)
};

namespace NCsSenseHeuristic
{
	typedef FECsSenseHeuristic Type;
}

#pragma endregion SenseHeuristic

struct ICsSenseInfo;

struct CSCORE_API FCsSenseHeuristicScore
{ 
	ICsSenseInfo* Info;

	float Score;

	FCsSenseHeuristicScore() :
		Info(nullptr),
		Score(0.0f)
	{
	}
};

// SenseHeuristicScoreSortOrder
#pragma region

UENUM(BlueprintType)
enum class ECsSenseHeuristicScoreSortOrder : uint8
{
	Descending							UMETA(DisplayName = "Descending"),
	Ascending							UMETA(DisplayName = "Ascending"),
	Custom								UMETA(DisplayName = "Custom"),
	ECsSenseHeuristicScoreSortOrder_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSenseHeuristicScoreSortOrder : public TCsEnumMap<ECsSenseHeuristicScoreSortOrder>
{
	CS_ENUM_MAP_BODY(EMCsSenseHeuristicScoreSortOrder, ECsSenseHeuristicScoreSortOrder)
};

namespace NCsSenseHeuristicScoreSortOrder
{
	typedef ECsSenseHeuristicScoreSortOrder Type;

	namespace Ref
	{
		extern CSCORE_API const Type Descending;
		extern CSCORE_API const Type Ascending;
		extern CSCORE_API const Type Custom;
		extern CSCORE_API const Type ECsSenseHeuristicScoreSortOrder_MAX;
	}
}

#pragma endregion SenseHeuristicScoreSortOrder

struct ICsSenseInfo;

struct CSCORE_API FCsSenseHeuristic
{
public:

	DECLARE_DELEGATE_RetVal_OneParam(float, FHeuristic, ICsSenseInfo*)

	FHeuristic Heuristic_Impl;

	TArray<FCsSenseHeuristicScore> Scores;

protected:

	ECsSenseHeuristicScoreSortOrder SortOrder;

public:

	// TODO: Store a Linked List for SortOnExecute

	bool bSortOnExecute;

	DECLARE_DELEGATE_RetVal_TwoParams(bool, FSortOnExecuteComparator, const FCsSenseHeuristicScore& /*ScoreToAdd*/, const FCsSenseHeuristicScore& /*Score*/)

	FSortOnExecuteComparator SortOnExecuteComparator_Impl;

	DECLARE_DELEGATE_OneParam(FSort, TArray<FCsSenseHeuristicScore>& /*InScores*/)

	FSort Sort_Impl;

	FCsSenseHeuristic() :
		Heuristic_Impl(),
		Scores(),
		SortOrder(ECsSenseHeuristicScoreSortOrder::Descending),
		bSortOnExecute(true),
		SortOnExecuteComparator_Impl(),
		Sort_Impl()
	{
		Heuristic_Impl.Unbind();
		SortOnExecuteComparator_Impl.Unbind();
		SortOnExecuteComparator_Impl.BindRaw(this, &FCsSenseHeuristic::SortOnExecute_Descending);
		Sort_Impl.Unbind();
		Sort_Impl.BindRaw(this, &FCsSenseHeuristic::Sort_Descending);
	}

	void SetSortOrder(const ECsSenseHeuristicScoreSortOrder& Order)
	{
		// Descending
		if (Order == ECsSenseHeuristicScoreSortOrder::Descending)
		{
			SortOnExecuteComparator_Impl.Unbind();
			SortOnExecuteComparator_Impl.BindRaw(this, &FCsSenseHeuristic::SortOnExecute_Descending);
			Sort_Impl.Unbind();
			Sort_Impl.BindRaw(this, &FCsSenseHeuristic::Sort_Descending);
		}
		// Ascending
		else
		if (Order == ECsSenseHeuristicScoreSortOrder::Ascending)
		{
			SortOnExecuteComparator_Impl.Unbind();
			SortOnExecuteComparator_Impl.BindRaw(this, &FCsSenseHeuristic::SortOnExecute_Ascending);
			Sort_Impl.Unbind();
			Sort_Impl.BindRaw(this, &FCsSenseHeuristic::Sort_Ascending);
		}
	}

	FORCEINLINE bool IsBound()
	{
		return Heuristic_Impl.IsBound();
	}

	void Execute(ICsSenseInfo* Info)
	{
		FCsSenseHeuristicScore Score;
		Score.Info  = Info;
		Score.Score = Heuristic_Impl.Execute(Info);

		if (bSortOnExecute)
		{
			checkf(SortOnExecuteComparator_Impl.IsBound(), TEXT("FCsSenseHeuristic::Execute: SortOnExecuteComparator_Impl must be bound when bSortOnExecute is true."));

			AddAndSortOnExecute(Score);
		}
		else
		{
			Scores.Add(Score);
		}
	}

	void AddAndSortOnExecute(const FCsSenseHeuristicScore& ScoreToAdd)
	{
		const int32 Count = Scores.Num();

		for (int32 I = 0; I < Count; ++I)
		{
			const FCsSenseHeuristicScore& Score = Scores[I];

			if (SortOnExecuteComparator_Impl.Execute(ScoreToAdd, Score))
			{
				Scores.Insert(ScoreToAdd, I);
				return;
			}
		}
		Scores.Add(ScoreToAdd);
	}
	
	bool SortOnExecute_Descending(const FCsSenseHeuristicScore& ScoreToAdd, const FCsSenseHeuristicScore& Score)
	{
		return ScoreToAdd.Score > Score.Score;
	}

	bool SortOnExecute_Ascending(const FCsSenseHeuristicScore& ScoreToAdd, const FCsSenseHeuristicScore& Score)
	{
		return ScoreToAdd.Score < Score.Score;
	}

	void ResetScores()
	{
		Scores.Reset(Scores.Max());
	}

	void Sort()
	{
		if (!bSortOnExecute)
		{
			checkf(Sort_Impl.IsBound(), TEXT("FCsSenseHeuristic::Sort: Sort_Impl must be bound when bSortOnExecute is false."));

			Sort_Impl.Execute(Scores);
		}
	}

	void Sort_Descending(TArray<FCsSenseHeuristicScore>& InScores)
	{
		Scores.Sort([](const FCsSenseHeuristicScore& A, const FCsSenseHeuristicScore& B)
		{
			return A.Score > B.Score;
		});
	}

	void Sort_Ascending(TArray<FCsSenseHeuristicScore>& InScores)
	{
		Scores.Sort([](const FCsSenseHeuristicScore& A, const FCsSenseHeuristicScore& B)
		{
			return A.Score < B.Score;
		});
	}
};