// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "AStarNode.generated.h"

enum Dir_Type
{
	Dir_None = 0,
	Dir_North,
	Dir_East,
	Dir_South,
	Dir_West
};

/**
 * 
 */
UCLASS()
class UE4_ASTAR_API UAStarNode : public UObject
{
	GENERATED_BODY()

public:
	UAStarNode();
	virtual ~UAStarNode();

	UAStarNode(FVector2D P);
	UAStarNode& Copy(const UAStarNode& node);

	FVector2D P;
	double F;
	double G;
	double W;
	UAStarNode* ParentsNode;	
	Dir_Type dirType;
};
