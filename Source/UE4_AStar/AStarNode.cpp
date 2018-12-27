// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "AStarNode.h"




UAStarNode::UAStarNode()
{
	P = FVector2D::ZeroVector;
	F = 0.0f;
	G = 0.0f;
	W = 0.0f;
	ParentsNode = NULL;
	dirType = Dir_None;
}

UAStarNode::~UAStarNode()
{
	UE_LOG(LogTemp, Warning, TEXT("UAStarNode Destroy"));
}

UAStarNode::UAStarNode(FVector2D P)
{
	this->P = P;
	this->F = 0.0f;
	this->G = 0.0f;
	this->W = 0.0f;
	this->ParentsNode = NULL;
	this->dirType = Dir_None;
}

UAStarNode& UAStarNode::Copy(const UAStarNode& node)
{
	this->P = node.P;
	this->F = node.F;
	this->G = node.G;
	this->W = node.W;
	this->ParentsNode = node.ParentsNode;
	this->dirType = node.dirType;

	return *this;
}
