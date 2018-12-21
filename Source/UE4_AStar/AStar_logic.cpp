// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "AStar_logic.h"

//const int UAStar_logic::MAP_SELL_NUM2 = 10;

UAStar_logic::UAStar_logic()
{	
}

UAStar_logic::~UAStar_logic()
{
}

void UAStar_logic::StartPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("UAStar_logic::StartPlay %d"), GEngine->GetWorld());
	ResetArray();
}

void UAStar_logic::ResetArray()
{
	memset(&MapArray, 0, sizeof(bool) * MAP_SELL_NUM2 * MAP_SELL_NUM2);
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
	Start.X = ArrayX;
	Start.Y = ArrayY;
}

void UAStar_logic::SetGoalPoint(int ArrayX, int ArrayY)
{
	Goal.X = ArrayX;
	Goal.Y = ArrayY;
}