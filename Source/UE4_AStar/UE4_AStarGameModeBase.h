// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "EngineUtils.h"
#include "UE4_AStarGameModeBase.generated.h"

//#define MAP_SELL_NUM 10

/**
 * 
 */
UCLASS()
class UE4_ASTAR_API AUE4_AStarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AUE4_AStarGameModeBase(const FObjectInitializer& ObjectInitializer);	

public:
	virtual void StartPlay() override;

	void CameraSetting();
	void InputSetting();
	void EnvSetting();
	void LMouseClick();	
	void SpawnBlock();
	void ClearBlock();
	void StartPointSetting();
	void GoalPointSetting();

	/** Get Piking Point. */
	FVector2D GetHitPoint();

	/** Convert HitPos to ArrayPos */
	FVector2D ConvertArrayPos(const FVector2D& HitPos);

	/** Convert ArrayPos to WorldSpawnPos*/
	FVector2D ConvertWorldSpawnPos(const FVector2D& ArrayPos);

	int MapSize;
	int BlockSize;

	TArray<class ABlockBox*> BlockBoxArray;
	//bool MapArray[MAP_SELL_NUM][MAP_SELL_NUM];

	class UAStar_logic* AStar;	
};
