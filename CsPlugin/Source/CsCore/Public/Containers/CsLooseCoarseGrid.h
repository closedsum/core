// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsLooseCoarseGrid
{
	// Stores a random-access sequence of elements similar to vector, but avoids 
	// heap allocations for small lists. T must be trivially constructible and 
	// destructible.
	template <class T>
	class TSmallList
	{
	public:
		// Creates an empty list.
		TSmallList() {}

		// Creates a copy of the specified list.
		TSmallList(const TSmallList& other)
		{
			if (other.ld.cap == fixed_cap)
			{
				ld = other.ld;
				ld.data = ld.buf;
			}
			else
			{
				reserve(other.ld.num);
				for (int32 j = 0; j < other.size(); ++j)
					ld.data[j] = other.ld.data[j];
				ld.num = other.ld.num;
				ld.cap = other.ld.cap;
			}
		}

		// Copies the specified list.
		FORCEINLINE TSmallList& operator=(const TSmallList& other) 
		{
			TSmallList(other).swap(*this);
			return *this;
		}

		// Destroys the list.
		~TSmallList()
		{
			if (ld.data != ld.buf)
				free(ld.data);
		}

		// Returns the number of agents in the list.
		FORCEINLINE int32 size() const
		{
			return ld.num;
		}

		// Returns the nth element.
		FORCEINLINE T& operator[](int32 n)
		{
			check(n >= 0 && n < ld.num);
			return ld.data[n];
		}

		// Returns the nth element in the list.
		FORCEINLINE const T& operator[](int32 n) const
		{
			check(n >= 0 && n < ld.num);
			return ld.data[n];
		}

		// Returns an index to a matching element in the list or -1
		// if the element is not found.
		FORCEINLINE int32 find_index(const T& element) const
		{
			for (int32 j = 0; j < ld.num; ++j)
			{
				if (ld.data[j] == element)
					return j;
			}
			return -1;
		}

		// Clears the list.
		FORCEINLINE void clear()
		{
			ld.num = 0;
		}

		// Reserves space for n elements.
		FORCEINLINE void reserve(int32 n)
		{
			enum { type_size = sizeof(T) };
			if (n > ld.cap)
			{
				if (ld.cap == fixed_cap)
				{
					ld.data = static_cast<T*>(malloc(n * type_size));
					memcpy(ld.data, ld.buf, sizeof(ld.buf));
				}
				else
					ld.data = static_cast<T*>(realloc(ld.data, n * type_size));
				ld.cap = n;
			}
		}

		// Inserts an element to the back of the list.
		FORCEINLINE void push_back(const T& element)
		{
			if (ld.num >= ld.cap)
				reserve(ld.cap * 2);
			ld.data[ld.num++] = element;
		}

		/// Pops an element off the back of the list.
		FORCEINLINE T pop_back()
		{
			return ld.data[--ld.num];
		}

		// Swaps the contents of this list with the other.
		void swap(TSmallList& other)
		{
			FListData& ld1 = ld;
			FListData& ld2 = other.ld;

			const int32 use_fixed1 = ld1.data == ld1.buf;
			const int32 use_fixed2 = ld2.data == ld2.buf;

			const FListData temp = ld1;
			ld1 = ld2;
			ld2 = temp;

			if (use_fixed1)
				ld2.data = ld2.buf;
			if (use_fixed2)
				ld1.data = ld1.buf;
		}

		// Returns a pointer to the underlying buffer.
		FORCEINLINE T* data()
		{
			return ld.data;
		}

		// Returns a pointer to the underlying buffer.
		FORCEINLINE const T* data() const
		{
			return ld.data;
		}

	private:

		enum { fixed_cap = 256 };

		struct FListData
		{
			T buf[fixed_cap];
			T* data;
			int32 num;
			int32 cap;

			FListData() :
				data(buf), num(0), cap(fixed_cap)
			{
			}
		};
		FListData ld;
	};

	/// Provides an indexed free list with constant-time removals from anywhere
	/// in the list without invalidating indices. T must be trivially constructible 
	/// and destructible.
	template <class T>
	class TFreeList
	{
	public:
		/// Creates a new free list.
		TFreeList() :
			first_free(-1)
		{
		}

		/// Inserts an element to the free list and returns an index to it.
		FORCEINLINE int32 insert(const T& element)
		{
			if (first_free != -1)
			{
				const int32 index = first_free;
				first_free = data[first_free].next;
				data[index].element = element;
				return index;
			}
			else
			{
				FreeElement fe;
				fe.element = element;
				data.push_back(fe);
				return data.size() - 1;
			}
		}

		// Removes the nth element from the free list.
		FORCEINLINE void erase(int32 n)
		{
			check(n >= 0 && n < data.size());
			data[n].next = first_free;
			first_free = n;
		}

		// Removes all elements from the free list.
		FORCEINLINE void clear()
		{
			data.clear();
			first_free = -1;
		}

		// Returns the range of valid indices.
		FORCEINLINE int32 range() const
		{
			return data.size();
		}

		// Returns the nth element.
		FORCEINLINE T& operator[](int32 n)
		{
			return data[n].element;
		}

		// Returns the nth element.
		FORCEINLINE const T& operator[](int32 n) const
		{
			return data[n].element;
		}

		// Reserves space for n elements.
		FORCEINLINE void reserve(int32 n)
		{
			data.reserve(n);
		}

		// Swaps the contents of the two lists.
		FORCEINLINE void swap(TFreeList& other)
		{
			const int temp = first_free;
			data.swap(other.data);
			first_free = other.first_free;
			other.first_free = temp;
		}

	private:
		union FreeElement
		{
			T element;
			int32 next;
		};
		TSmallList<FreeElement> data;
		int32 first_free;
	};

	struct CSCORE_API FHelper
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

		FORCEINLINE static bool DoesRectIntersect(const FVector4& A, const FVector4& B)
		{
			return B.X <= A.Z && B.Z >= A.X && B.Y <= A.W && B.W >= A.Y;
		}
	};

	struct LGridQuery4
	{
		// Stores the resulting elements of the SIMD query.
		NCsLooseCoarseGrid::TSmallList<int32> elements[4];
	};

	struct CSCORE_API FElement
	{
	public:

		// Stores the index to the next element in the loose cell using an indexed SLL.
		int32 Next;

		// Stores the ID of the element. This can be used to associate external
		// data to the element.
		int32 ID;

		// Stores the center of the element.
		float CenterX;
		float CenterY;

		// Stores the half-size of the element relative to the upper-left corner
		// of the grid.
		float HalfWidth;
		float HalfHeight;

		/*
		FElement() :
			next(INDEX_NONE),
			ID(INDEX_NONE),
			CenterX(0.0f),
			CenterY(0.0f),
			HalfWidth(0.0f),
			HalfHeight(0.0f)
		{
		}
		*/
		/*
		FElement(const int32& InNext, const int32& InID, const int32& InCenterX, const int32& InCenterY, const int32& InHalfWidth, const int32& InHalfHeight) :
			next(InNext),
			ID(InID),
			CenterX(InCenterX),
			CenterY(InCenterY),
			HalfWidth(InHalfWidth),
			HalfHeight(InHalfHeight)
		{
		}
		*/

		FORCEINLINE const int32& GetID() const { return ID; }

		FORCEINLINE const int32& GetNext() const { return Next; }
		FORCEINLINE int32* GetNextPtr() { return &Next; }

		FORCEINLINE FVector4 ToRectAsVector4() const
		{
			return FVector4(CenterX - HalfWidth, CenterY - HalfHeight, CenterX + HalfWidth, CenterY + HalfHeight);
		}
	};

	namespace NLoose
	{
		struct CSCORE_API FCell
		{
		public:

			/** Stores the extents of the grid cell relative to the upper-left corner
				of the grid which expands and shrinks with the elements inserted and 
				removed. 
				Rect[0] = Left
				Rect[1] = Top
				Rect[2] = Right
				Rect[3] = Bottom */
			float Rect[4];

			/** Stores the index to the first element using an indexed SLL. */
			int32 Head;

			FCell() :
				Head(INDEX_NONE)
			{
				InvalidateRect();
			}

			FORCEINLINE int32* GetHeadPtr() { return &Head; }

			FORCEINLINE bool HasHead() const { return Head != INDEX_NONE; }

			FORCEINLINE FVector4 RectToVector4() const { return FVector4(Rect[0], Rect[1], Rect[2], Rect[3]); }

			FORCEINLINE void InvalidateRect()
			{
				Rect[0] = FLT_MAX;
				Rect[1] = FLT_MAX;
				Rect[2] = -FLT_MAX;
				Rect[3] = -FLT_MAX;
			}

			FORCEINLINE void Invalidate()
			{
				Head = INDEX_NONE;
				InvalidateRect();
			}
		};

		struct CSCORE_API FGrid
		{
		private:

			typedef NCsLooseCoarseGrid::NLoose::FCell LooseCellType;

		public:

			// Stores all the cells in the loose grid.
			LooseCellType* Cells;

			// Stores the number of columns, rows, and cells in the loose grid.
			int32 NumColumns;
			int32 NumRows;
			int32 NumCells;

			// Stores the inverse size of a loose cell.
			float InverseCellWidth;
			float InverseCellHeight;

			FGrid() :
				Cells(),
				NumColumns(0),
				NumRows(0),
				NumCells(0),
				InverseCellWidth(0.0f),
				InverseCellHeight(0.0f)
			{
			}

			~FGrid()
			{
				delete Cells;
				Cells = nullptr;
			}

			void Init(const int32& InNumColumns, const int32& InNumRows, const float& CellWidth, const float& CellHeight)
			{
				NumColumns		  = InNumColumns;
				NumRows			  = InNumRows;
				NumCells		  = NumColumns * NumRows;
				InverseCellWidth  = 1.0f / InverseCellWidth;
				InverseCellHeight = 1.0f / InverseCellHeight;

				Cells = new LooseCellType[NumCells];

				for (int32 I = 0; I < NumCells; ++I)
				{
					Cells[I].Invalidate();
				}
			}
		};
	}

	namespace NTight
	{
		struct CSCORE_API FCell
		{
		public:

			// Stores the index to the next loose cell in the grid cell.
			int32 Next;

			// Stores the position of the loose cell in the grid.
			int32 Index;

			/*
			FCell() : 
				Next(INDEX_NONE),
				Index(INDEX_NONE)
			{
			}
			*/
			/*
			FCell(const int32& InNext, const int32& InIndex) :
				Index(InNext),
				Index(InIndex)
			{
			}
			*/
		};

		struct CSCORE_API FGrid
		{
		private:

			typedef NCsLooseCoarseGrid::NTight::FCell TightCellType;

		public:

			// Stores all the tight cell nodes in the grid.
			NCsLooseCoarseGrid::TFreeList<TightCellType> Cells;

			// Stores the tight cell heads.
			int32* Heads;

			// Stores the number of columns, rows, and cells in the tight grid.
			int32 NumColumns;
			int32 NumRows;
			int32 NumCells;

			// Stores the inverse size of a tight cell.
			float InverseCellWidth;
			float InverseCellHeight;

			FGrid() :
				Cells(),
				Heads(nullptr),
				NumColumns(0),
				NumRows(0),
				NumCells(0),
				InverseCellWidth(0.0f),
				InverseCellHeight(0.0f)
			{
			}

			~FGrid()
			{
				delete Heads;
				Heads = nullptr;
			}

			void Init(const int32& InNumColumns, const int32& InNumRows, const float& CellWidth, const float& CellHeight)
			{
				NumColumns		  = InNumColumns;
				NumRows			  = InNumRows;
				NumCells		  = InNumColumns * InNumRows;
				InverseCellWidth  = 1.0f / CellWidth;
				InverseCellHeight = 1.0f / CellHeight;

				// Initialize tight cell heads with -1 to indicate empty indexed SLLs.
				Heads = new int32[NumCells];

				for (int32 I = 0; I < NumCells; ++I)
				{
					Heads[I] = INDEX_NONE;
				}
			}
		};
	}

	/** 2D grid comprised of "Tight" and "Loose" grids. */
	struct CSCORE_API FGrid
	{
	private:

		typedef NCsLooseCoarseGrid::FElement ElementType;
		typedef NCsLooseCoarseGrid::NTight::FGrid TightGridType;
		typedef NCsLooseCoarseGrid::NLoose::FGrid LooseGridType;

	private:

		// Stores the tight cell data for the grid.
		TightGridType Tight;

		// Stores the loose cell data for the grid.
		LooseGridType Loose;

		// Stores all the elements in the grid.
		NCsLooseCoarseGrid::TFreeList<ElementType> Elements;

		NCsLooseCoarseGrid::TFreeList<ElementType> TempElements;

		// Stores the number of elements in the grid.
		int32 NumElements;

		// Stores the upper-left corner of the grid.
		float Left;
		float Top;

		/** Width of the grid */
		float Width;
		float WidthBy2;
		
		/** Height of the grid */
		float Height;
		float HeightBy2;

	public:

		FGrid();

		FORCEINLINE float GetWidthBy2() const { return WidthBy2; }
		FORCEINLINE float GetHeightBy2() const { return HeightBy2; }

		/**
		* Creates a loose grid encompassing the specified extents using the specified cell 
		* size. Elements inserted to the loose grid are only inserted in one cell, but the
		* extents of each cell are allowed to expand and shrink. To avoid requiring every
		* loose cell to be checked during a search, a second grid of tight cells referencing
		* the loose cells is stored.
		* 
		* @param LooseCellWidth		Width of a Loose Cell
		*/
		void Create(const float& LooseCellWidth, const float& LooseCellHeight, const float& TightCellWidth, const float& TightCellHeight,
					const float& InLeft, const float& InTop, const float& Right, const float& Bottom);

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
			const int32 CellX = NCsLooseCoarseGrid::FHelper::ToCellIndex(X - Left, Loose.InverseCellWidth, Loose.NumColumns);
			const int32 CellY = NCsLooseCoarseGrid::FHelper::ToCellIndex(Y - Top, Loose.InverseCellHeight, Loose.NumRows);
			return CellY * Loose.NumColumns + CellX;
		}

		FORCEINLINE FIntVector4 GetCellIndex4(const FVector4& Rect) const
		{
			FVector4 inv_cell_size_vec = FVector4(Tight.InverseCellWidth, Tight.InverseCellHeight, Tight.InverseCellWidth, Tight.InverseCellHeight);
			FVector4 cell_xyf_vec	   = Rect * inv_cell_size_vec;
			FIntVector4 clamp_vec	   = FIntVector4(Tight.NumColumns - 1, Tight.NumRows - 1, Tight.NumColumns - 1, Tight.NumRows - 1);
			FIntVector4 cell_xy_vec;
			cell_xy_vec.X			   = FMath::Clamp((int32)cell_xyf_vec.X, 0, clamp_vec.X);
			cell_xy_vec.Y			   = FMath::Clamp((int32)cell_xyf_vec.Y, 0, clamp_vec.Y);
			cell_xy_vec.Z			   = FMath::Clamp((int32)cell_xyf_vec.Z, 0, clamp_vec.Z);
			cell_xy_vec.W			   = FMath::Clamp((int32)cell_xyf_vec.W, 0, clamp_vec.W);
			return cell_xy_vec;
		}

	public:

	private:

		void Insert_Internal(const int32& ID, const float& CenterX, const float& CenterY, const float& HalfWidth, const float& HalfHeight);

	public:

		/**
		* Inserts an element to the grid.
		* 
		* @param ID
		* @param CenterX		X position in World Space of the collision for the object with ID.
		* @param CenterY		Y position in World Space of the collision for the object with ID.
		* @param HalfWidth		Half of the Width (Delta along X-axis) of the collision for the object with ID.
		* @param HalfHeight		Half of the Height (Delta along Y-axis) of the collision for the object with ID.
		*/
		FORCEINLINE void Insert(const int32& ID, const float& CenterX, const float& CenterY, const float& HalfWidth, const float& HalfHeight)
		{
			Insert_Internal(ID, CenterX + GetWidthBy2(), CenterY + GetHeightBy2(), HalfWidth, HalfHeight);
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
			Remove_Internal(ID, CenterX + GetWidthBy2(), CenterY + GetHeightBy2());
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
			Move_Internal(ID, PrevCenterX + GetWidthBy2(), PrevCenterY + GetHeightBy2(), CenterX + GetWidthBy2(), CenterY + GetHeightBy2());
		}

		/**
		* Returns all the element IDs that intersect the specified rectangle excluding elements
		* with the specified ID to omit.
		* 
		* @param CenterX
		* @param CenterY
		* @param HalfWidth
		* @param HalfHeight
		* @param OmitID
		* return
		*/
		TSmallList<int32> Query(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID);

		struct FQuery
		{
		public:

			struct FResult
			{
			public:

				TArray<int32> IDs;

				int32 Count;

				int32 InterationCount;
			};
		};

	#define QueryResultType NCsLooseCoarseGrid::FGrid::FQuery::FResult

	private:

		void Query_Internal(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID, QueryResultType& OutResult) const;

	public:
		
		FORCEINLINE void Query(float CenterX, float CenterY, float HalfWidth, float HalfHeight, const int32& OmitID, QueryResultType& OutResult) const
		{
			Query_Internal(CenterX + GetWidthBy2(), CenterY + GetHeightBy2(), HalfWidth, HalfHeight, OmitID, OutResult);
		}

	#undef QueryResultType

	private:

		/**
		* Check if the specified rectangle is inside the grid boundaries.
		* 
		* @param CenterX
		* @param CenterY
		* @param HalfHeight
		* @param HalfWidth
		* return			Whether the rectangle is in the grid boundaries or not.
		*/
		FORCEINLINE bool IsInBounds(float CenterX, float CenterY, const float& HalfHeight, const float& HalfWidth) const
		{
			CenterX -= Left;
			CenterY -= Top;

			const float x1 = CenterX - HalfWidth;
			const float y1 = CenterY - HalfHeight;
			const float x2 = CenterX + HalfWidth;
			const float y2 = CenterY + HalfHeight;

			return x1 >= 0.0f && x2 < Width && y1 >= 0.0f && y2 < Height;
		}

	public:

		/**
		* Optimizes the grid, shrinking bounding boxes in response to removed elements and
		* rearranging the memory of the grid to allow cache-friendly cell traversal.
		*/
		void Optimize();

	private:

		void OptimizeMemoryLayout();

		void Expand_AABB(const int32& CellIndex, const float& CenterX, const float& CenterY, const float& HalfWidth, const float& HalfHeight);
	};
}