// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"
#include "CoreMinimal.h"

namespace NCsGrid
{
	namespace NUniform
	{
		struct CSCORELIBRARY_API FHelper
		{
		public:

			// Returns the value divided by the divisor rounded up.
			FORCEINLINE static int32 CeilDiv(const float& Value, const float& Divisor)
			{
				const float Resultf = Value / Divisor;
				const int32 Result = (int32)Resultf;
				return Result < Resultf ? Result + 1 : Result;
			}

			FORCEINLINE static int32 MinInt(int32 A, int32 B)
			{
				check(sizeof(int32) == 4);
				A -= B;
				A &= A >> 31;
				return A + B;
			}

			FORCEINLINE static int32 MaxInt(int32 A, int32 B)
			{
				check(sizeof(int32) == 4);
				A -= B;
				A &= (~A) >> 31;
				return A + B;
			}

			FORCEINLINE static int32 ToCellIndex(const float& Value, const float& InverseCellSize, const int32& NumCells)
			{
				const int32 CellPosition = (int)(Value * InverseCellSize);
				return MinInt(MaxInt(CellPosition, 0), NumCells - 1);
			}
		};

		struct CSCORELIBRARY_API FGrid
		{
		#define IDManagerType NCsResource::NManager::NValue::NFixed::NInt32::FManager
		#define ResourceType NCsResource::NManager::NValue::NFixed::NInt32::FResource 

		private:

			IDManagerType Manager_ID;

			/** Width of the grid */
			float Width;
			float WidthBy2;

			int32 NumColumns;
			int32 NumColumnsMinusOne;

			float CellWidth;
			float InverseCellWidth;

			/** The maximum number of elements a Cell can hold. */
			int32 MaxStride;

			/** For a given Cell, the Starting Index to any relevant element data. 
				StartingIndices[Cell ID] = Start of Element Data. */
			TArray<int32> StartingIndices;

			/** For a given Cell, the Number of elements contained. 
				Strides[Cell ID] = Number of Elements. */
			TArray<int32> Strides;

			TArray<ResourceType*> Resources;

			TArray<int32> IDs;

			int32 FreeIndex;

			TArray<int32> DeallocatedIndices;

			TArray<FVector2f> Centers;

			TArray<float> Radii;

		public:

			FGrid();

			FORCEINLINE float GetWidthBy2() const { return WidthBy2; }

			FORCEINLINE int32 AllocateStartingIndex()
			{
				if (DeallocatedIndices.Num() > 0)
				{
					int32 Index = DeallocatedIndices.Last();

					DeallocatedIndices.RemoveAt(DeallocatedIndices.Num() - 1, 1, EAllowShrinking::No);
					return Index;
				}

				int32 Index = FreeIndex;

				FreeIndex += MaxStride;

				check(FreeIndex < IDs.Num());
				return Index;
			}

			void Create(const float& InGridWidth, const float& InCellWidth, const int32& InMaxElements, const int32& InMaxStride);

		private:

			/**
			* Returns the grid cell index for the specified position.
			*
			* @param X	Position along X axis
			* @param Y	Position along Y axis
			* return	Index
			*/
			FORCEINLINE int32 GetCellIndex(const float& X, const float& Y) const
			{
				const int32 CellX = NCsGrid::NUniform::FHelper::ToCellIndex(X, InverseCellWidth, NumColumns);
				const int32 CellY = NCsGrid::NUniform::FHelper::ToCellIndex(Y, InverseCellWidth, NumColumns);
				return CellY * NumColumns + CellX;
			}

			FORCEINLINE FIntVector4 GetCellIndex4(const FVector4f& Rect) const
			{
				FVector4f cell_xyf_vec	   = InverseCellWidth * Rect;
				FIntVector4 cell_xy_vec;
				cell_xy_vec.X			   = FMath::Clamp((int32)cell_xyf_vec.X, 0, NumColumnsMinusOne);
				cell_xy_vec.Y			   = FMath::Clamp((int32)cell_xyf_vec.Y, 0, NumColumnsMinusOne);
				cell_xy_vec.Z			   = FMath::Clamp((int32)cell_xyf_vec.Z, 0, NumColumnsMinusOne);
				cell_xy_vec.W			   = FMath::Clamp((int32)cell_xyf_vec.W, 0, NumColumnsMinusOne);
				return cell_xy_vec;
			}

			void Insert_Internal(const int32& ID, const float& CenterX, const float& CenterY, const float& Radius);

		public:

			/**
			* Inserts an element to the grid.
			*
			* @param ID
			* @param CenterX		X position in World Space of the collision for the object with ID.
			* @param CenterY		Y position in World Space of the collision for the object with ID.
			* @param Radius			Radius of the collision for the object with ID.
			*/
			FORCEINLINE void Insert(const int32& ID, const float& CenterX, const float& CenterY, const float& Radius)
			{
				Insert_Internal(ID, CenterX + GetWidthBy2(), CenterY + GetWidthBy2(), Radius);
			}

		private:

			void Remove_Internal(const int32& ID, const float& CenterX, const float& CenterY);

		public:

			/**
			* Removes an element from the grid.
			*
			* @param ID
			* @param CenterX	X position in World Space of the collision for the object with ID.
			* @param CenterY	Y position in World Space of the collision for the object with ID.
			*/
			FORCEINLINE void Remove(const int32& ID, const float& CenterX, const float& CenterY)
			{
				Remove_Internal(ID, CenterX + GetWidthBy2(), CenterY + GetWidthBy2());
			}

		private:

			void Move_Internal(const int32& ID, const float& PrevCenterX, const float& PrevCenterY, float CenterX, float CenterY);

		public:

			/**
			* Moves an element in the grid from the former position to the new one.
			* 
			* @param ID
			* @param PrevCenterX
			* @param PrevCenterY
			* @param CenterX
			* @param CenterY
			*/
			FORCEINLINE void Move(const int32& ID, const float& PrevCenterX, const float& PrevCenterY, float CenterX, float CenterY)
			{
				Move_Internal(ID, PrevCenterX + GetWidthBy2(), PrevCenterY + GetWidthBy2(), CenterX + GetWidthBy2(), CenterY + GetWidthBy2());
			}

		struct FQuery
		{
		public:

			struct FResult
			{
			public:

				TArray<int32> IDs;

				int32 Count;

				int32 InterationCount;

			// Debug

				UObject* WorldContext;

				bool bDrawCells;
				bool bDrawCellsWithElements;

				FResult() :
					IDs(),
					Count(0),
					InterationCount(0),
					WorldContext(nullptr),
					bDrawCells(false),
					bDrawCellsWithElements(false)
				{
				}
			};
		};

		#define QueryResultType NCsGrid::NUniform::FGrid::FQuery::FResult

		private:

			void Query_Internal(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID, QueryResultType& OutResult) const;

		public:
		
			FORCEINLINE void Query(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID, QueryResultType& OutResult) const
			{
				Query_Internal(CenterX + GetWidthBy2(), CenterY + GetWidthBy2(), HalfWidth, HalfHeight, OmitID, OutResult);
			}

		#undef QueryResultType

			void Reset();

			void Draw(const UObject* WorldContext);

		#undef IDManagerType
		#undef ResourceType
		};
	}
}