// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "AStar_logic.h"
#include "FMainEvent.h"

UAStar_logic::UAStar_logic()
: BStart(false)
, StartNode(nullptr)
{	
}

UAStar_logic::~UAStar_logic()
{	
}

void UAStar_logic::StartPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("UAStar_logic::StartPlay %d"), GEngine->GetWorld());
	Reset();	
}

void UAStar_logic::Reset()
{
	memset(&MapArray, 0, sizeof(bool) * MAP_SELL_NUM * MAP_SELL_NUM);

	if (StartNode)
	{
		StartNode->ConditionalBeginDestroy();
		StartNode = nullptr;
	}
	
	if (GoalNode)
	{
		GoalNode->ConditionalBeginDestroy();
		GoalNode = nullptr;
	}	

	BStart = false;
}

void UAStar_logic::SetBlock(int ArrayX, int ArrayY)
{
	MapArray[ArrayX][ArrayY] = true;
}

bool UAStar_logic::IsBlock(int ArrayX, int ArrayY)
{
	return MapArray[ArrayX][ArrayY];
}

void UAStar_logic::SetStartPoint(int ArrayX, int ArrayY)
{	
	if (!StartNode)
	{
		StartNode = NewObject<UAStarNode>(this);
	}
	
	StartNode->P.X = ArrayX;
	StartNode->P.Y = ArrayY;	
}

void UAStar_logic::SetGoalPoint(int ArrayX, int ArrayY)
{
	if (!GoalNode)
	{
		GoalNode = NewObject<UAStarNode>(this);
	}

	GoalNode->P.X = ArrayX;
	GoalNode->P.Y = ArrayY;	
}

void UAStar_logic::Play()
{
	UE_LOG(LogTemp, Warning, TEXT("UAStar_logic::Play()"));

	if (!StartNode || !GoalNode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Start or Goal Point is not Setting"));

		return;
	}

	CurNode = StartNode;

	OpenList.Emplace(StartNode);

	BStart = true;
		
	GEngine->GameViewport->GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &UAStar_logic::Update, 0.3f, true);
}

void UAStar_logic::Tick(float DeltaTime)
{
	if (!BStart)
	{
		return;
	}
}

void UAStar_logic::Update()
{
	DeleteOpenNode(CurNode);

	if (AddNearNode(CurNode))
	{
		CloseList.Emplace(CurNode);
	}

	if (OpenList.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Way!!!!"));

		GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(_TimerHandle);

		return;
	}

	CurNode = GetMinNodeF();

	if (CurNode->P == GoalNode->P)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Arrived!!!!"));

		GEngine->GameViewport->GetWorld()->GetTimerManager().ClearTimer(_TimerHandle);
	}
	
	FVector2D Vec2D;
	Vec2D.X = CurNode->P.X;
	Vec2D.Y = CurNode->P.Y;

	FMainEvent::MoveWayEvent.Broadcast(Vec2D);
}

bool UAStar_logic::DeleteOpenNode(const UAStarNode* DeleteNode)
{
	for (auto i : OpenList)
	{
		if (i->P == DeleteNode->P)
		{
			OpenList.Remove(i);

			return true;
		}
	}

	return false;
}

bool UAStar_logic::AddNearNode(UAStarNode* curNode)
{
	bool retAdd = false;
	FVector2D searchPoint;

	// ��
	if (curNode->P.X < MAP_SELL_NUM - 1)
	{
		searchPoint.X = curNode->P.X + 1;
		searchPoint.Y = curNode->P.Y;

		if (IsGoalNodeAndOpenListPush(curNode, searchPoint, Dir_North))
			return true;

		if (IsEmptyPointInMap(searchPoint) && IsCloseNode(searchPoint) == false)
		{
			AddOpenNode(curNode, searchPoint, Dir_North);

			retAdd = true;
		}
	}

	// ��
	if (curNode->P.Y > 0)
	{
		searchPoint.X = curNode->P.X;
		searchPoint.Y = curNode->P.Y - 1;

		if (IsGoalNodeAndOpenListPush(curNode, searchPoint, Dir_West))
			return true;

		if (IsEmptyPointInMap(searchPoint) && IsCloseNode(searchPoint) == false)
		{
			AddOpenNode(curNode, searchPoint, Dir_West);

			retAdd = true;
		}
	}

	// ��
	if (curNode->P.Y < MAP_SELL_NUM - 1)
	{
		searchPoint.X = curNode->P.X;
		searchPoint.Y = curNode->P.Y + 1;

		if (IsGoalNodeAndOpenListPush(curNode, searchPoint, Dir_East))
			return true;

		if (IsEmptyPointInMap(searchPoint) && IsCloseNode(searchPoint) == false)
		{
			AddOpenNode(curNode, searchPoint, Dir_East);

			retAdd = true;
		}
	}

	// ��
	if (curNode->P.X > 0)
	{
		searchPoint.X = curNode->P.X - 1;
		searchPoint.Y = curNode->P.Y;

		if (IsGoalNodeAndOpenListPush(curNode, searchPoint, Dir_South))
			return true;

		if (IsEmptyPointInMap(searchPoint) && IsCloseNode(searchPoint) == false)
		{
			AddOpenNode(curNode, searchPoint, Dir_South);

			retAdd = true;
		}
	}

	return retAdd;
}

bool UAStar_logic::IsGoalNodeAndOpenListPush(UAStarNode* curNode, const FVector2D& p, Dir_Type dirType)
{
	if(p == GoalNode->P)
	{
		GoalNode->ParentsNode = curNode;
		GoalNode->dirType = dirType;

		OpenList.Emplace(GoalNode);

		return true;
	}

	return false;
}

bool UAStar_logic::IsEmptyPointInMap(const FVector2D& point)
{
	return MapArray[(int)point.X][(int)point.Y] == false ? true : false;
}

bool UAStar_logic::IsCloseNode(const FVector2D& point)
{
	for (auto i : CloseList)
	{
		if (i->P == point)
		{
			return true;
		}
	}

	return false;
}

void UAStar_logic::AddOpenNode(UAStarNode* curNode, const FVector2D& addPoint, Dir_Type nextDir)
{
	double F, G, H, W;

	// A* ���� G
	// �����忡�� �߰� �� ��� �Ÿ� + ���� �Ÿ�
	G = FVector2D::Distance(curNode->P, addPoint) + curNode->G;// GetDistance(curNode->p, addPoint) + curNode->g;

	// A* ���� H
	// �߰� �� ���� ��ǥ���� �Ÿ�
	H = FMath::Abs(addPoint.X - GoalNode->P.X) + FMath::Abs(addPoint.Y - GoalNode->P.Y);

	// ���� ���� ���� ����ġ
	W = DirectionWeight(curNode->dirType, nextDir) + curNode->W;

	F = G + H + W;

	for (auto i : OpenList)
	{
		if (i->P == addPoint)
		{
			if (i->F >= F)
			{
				OpenList.Remove(i);

				i->ConditionalBeginDestroy();
				i = nullptr;

				break;
			}
		}
	}	

	// ���¸���Ʈ�� ������ �־��ش�.
	UAStarNode* addNode = NewObject<UAStarNode>(this);	
	addNode->P = addPoint;
	addNode->F = F;
	addNode->G = G;
	addNode->W = W;
	addNode->ParentsNode = curNode;
	addNode->dirType = nextDir;

	OpenList.Emplace(addNode);
}

float UAStar_logic::DirectionWeight(Dir_Type curDir, Dir_Type nextDir)
{
	int dirWeight = FMath::Abs(nextDir - curDir);

	// ���� ����
	if (dirWeight == 0)
		return 0.0f;
	else if (dirWeight == 1)
		return 1.0f;
	else if (dirWeight == 2)
		return 2.0f;
	else if (dirWeight == 3)	// 3�� ���� �ٷ� �� �ݴ���� ��.
		return 1.0f;

	return 0.0f;
}

UAStarNode* UAStar_logic::GetMinNodeF()
{
	UAStarNode* retNode = NULL;

	double minf = 100000.0f;

	for (auto i : OpenList)
	{
		if (i->F <= minf)
		{
			retNode = i;
			minf = i->F;
		}
	}

	return retNode;
}
