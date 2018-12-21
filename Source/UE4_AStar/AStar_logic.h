// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AStar_logic.generated.h"

/**
 * 
 */
UCLASS()
class UE4_ASTAR_API UAStar_logic : public UObject
{
	GENERATED_BODY()

public:
	UAStar_logic();
	virtual ~UAStar_logic();	

	void StartPlay();

	static const int MAP_SELL_NUM2 = 10;		

	void ResetArray();
	void SetBlock(int ArrayX, int ArrayY);
	bool IsBlock(int ArrayX, int ArrayY);
	void SetStartPoint(int ArrayX, int ArrayY);
	void SetGoalPoint(int ArrayX, int ArrayY);

private:
	bool MapArray[MAP_SELL_NUM2][MAP_SELL_NUM2];
	FVector2D Start;
	FVector2D Goal;
};
