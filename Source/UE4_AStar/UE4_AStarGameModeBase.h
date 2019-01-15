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
	virtual void Tick(float DeltaTime) override;

	void CameraSetting();
	void InputSetting();
	void EnvSetting();
	void LMouseClick();	
	void LMouseUp();
	void SpawnBlock();
	void ClearBlock();
	void Clear();
	void StartPointSetting();
	void GoalPointSetting();
	void Play();
	void RecvEvent_MoveWay(FVector2D Point);
	void RecvEvent_SpawnPath(FVector2D Point);

	/** Get Piking Point. */
	FVector2D GetHitPoint();

	/** Convert HitPos to ArrayPos */
	FVector2D ConvertArrayPos(const FVector2D& HitPos);

	/** Convert ArrayPos to WorldSpawnPos*/
	FVector2D ConvertWorldSpawnPos(const FVector2D& ArrayPos);

	int MapSize;
	int BlockSize;	
	bool bSpawnBlock = false;

	TArray<class ABlockBox*> BlockBoxArray;
	UPROPERTY()
	class UAStar_logic* AStar;	

	//TWeakObjectPtr<class UAStar_logic> AStar;
};
