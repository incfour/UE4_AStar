// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AStarNode.h"
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

	static const int MAP_SELL_NUM = 10;		

	void Reset();
	void SetBlock(int ArrayX, int ArrayY);
	bool IsBlock(int ArrayX, int ArrayY);
	void SetStartPoint(int ArrayX, int ArrayY);
	void SetGoalPoint(int ArrayX, int ArrayY);
	void Play();
	void Tick(float DeltaTime);
	void Update();
	bool DeleteOpenNode(const UAStarNode* DeleteNode);
	bool AddNearNode(UAStarNode* curNode);
	bool IsGoalNodeAndOpenListPush(UAStarNode* curNode, const FVector2D& p, Dir_Type dirType);
	bool IsEmptyPointInMap(const FVector2D& point);
	bool IsCloseNode(const FVector2D& point);
	void AddOpenNode(UAStarNode* curNode, const FVector2D& addPoint, Dir_Type nextDir);
	void MakePath();
	float DirectionWeight(Dir_Type curDir, Dir_Type nextDir);
	UAStarNode* GetMinNodeF();

private:
	FTimerHandle _TimerHandle;	
	bool MapArray[MAP_SELL_NUM][MAP_SELL_NUM];
	UPROPERTY()
	TArray<UAStarNode*> OpenList;
	UPROPERTY()
	TArray<UAStarNode*> CloseList;
	UPROPERTY()
	UAStarNode* StartNode;
	UPROPERTY()
	UAStarNode* GoalNode;	
	UPROPERTY()
	UAStarNode* CurNode;
	bool StartNodeSetting;
	bool GoalNodeSetting;
};
