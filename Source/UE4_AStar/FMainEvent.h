// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/**
 * 
 */
struct UE4_ASTAR_API FMainEvent
{

	DECLARE_MULTICAST_DELEGATE_OneParam(FMoveWayEvent, FVector2D);
	DECLARE_MULTICAST_DELEGATE_OneParam(FSpawnPathEvent, FVector2D);

	static FMoveWayEvent MoveWayEvent;
	static FSpawnPathEvent SpawnPathEvent;
};
