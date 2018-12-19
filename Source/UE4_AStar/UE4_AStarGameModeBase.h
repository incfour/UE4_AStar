// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "EngineUtils.h"
#include "UE4_AStarGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_ASTAR_API AUE4_AStarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	//AUE4_AStarGameModeBase(const FObjectInitializer& ObjectInitializer);	

public:
	virtual void StartPlay() override;

	void CameraSetting();
	void InputSetting();
	void EnvSetting();
	void LMouseClick();	
	void SpawnBlock();
	void ClearBlock();

	int MapSellCount = 10;
	int MapSize;
	int BlockSize;

	TArray<class ABlockBox*> BlockBoxArray;
	bool MapArray[10][10];
};
