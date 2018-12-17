// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class UE4_ASTAR_API Util
{
public:
	Util();
	~Util();

	static AActor* FindActor(UWorld* World, FString Name);
};
