#pragma once

#include <XEngine.h>

// Description:
// Store tile types used at each location (i.e. column, row) as an 1D array of integers.
// The index of each slot can be obtained using the GetIndex(...) helper function.
class TileMap
{
public:
	~TileMap();

	void LoadMap(const char* fileName);
	void SaveMap(const char* fileName);

	void LoadTiles(const char* fileName);

	void Resize(int columns, int rows);

	void Update();
	void Render();
	void ShowDebugUI();

	int GetColumns() const { return mColumns; }
	int GetRows() const { return mRows; }
	int GetTileWidth() const { return mTileWidth; }
	int GetTileHeight() const { return mTileHeight; }

	bool IsBlocked(int column, int row);
	float GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow) const;
	float GetEstimatedDistanceManhattan(int fromColumn, int fromRow, int endColumn, int endRow) const;
	float GetEstimatedDistanceEuclidean(int fromColumn, int fromRow, int endColumn, int endRow) const;
	float GetEstimatedDistanceDiagonal(int fromColumn, int fromRow, int endColumn, int endRow) const;


private:
	int GetIndex(int column, int row, int columnCount) const;

	int* mMap = nullptr;	// Default member initialization
	int mColumns = 0;
	int mRows = 0;

	std::vector<X::TextureId> mTileSet; // Actual textures to use for each location
	int mTileWidth = 0;
	int mTileHeight = 0;
	int mSelectedTile = 0;
};
