// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "EngineUtils.h"
#include "UE4_AStarGameModeBase.generated.h"

//#define MAP_SELL_NUM 10

UENUM()
enum class SettingState : uint8
{
	SpawnBlock			UMETA(DisplayName = "SpawnBlock"),
	StartPointSetting   UMETA(DisplayName = "StartPointSetting"),
	GoalPointSetting    UMETA(DisplayName = "GoalPointSetting"),
};

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

	//UFUNCTION(BlueprintCallable)
	void StartPointSetting();

	//UFUNCTION(BlueprintCallable)
	void GoalPointSetting();

	UFUNCTION(BlueprintCallable)
	void Play();

	UFUNCTION(BlueprintCallable)
	void Clear();

	UFUNCTION(BlueprintCallable)
	bool IsEnablePlay();

	UFUNCTION(BlueprintCallable)
	void SetSettingState(SettingState InputState);

	void RecvEvent_MoveWay(FVector2D Point);
	void RecvEvent_SpawnPath(FVector2D Point);

	/** Get Piking Point. */
	FVector2D GetHitPoint();

	/** Convert HitPos to ArrayPos */
	FVector2D ConvertArrayPos(const FVector2D& HitPos);

	/** Convert ArrayPos to WorldSpawnPos*/
	FVector2D ConvertWorldSpawnPos(const FVector2D& ArrayPos);	

private:
	int MapSize;
	int BlockSize;
	bool bSpawnBlock = false;
	bool bStartPointSetting = false;	
	bool bGoalPointSetting = false;

	TArray<class ABlockBox*> BlockBoxArray;

	UPROPERTY()
	SettingState State;

	UPROPERTY()
	class UAStar_logic* AStar;

	//TWeakObjectPtr<class UAStar_logic> AStar;
};
