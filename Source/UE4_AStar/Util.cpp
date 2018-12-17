// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_AStar.h"
#include "Util.h"

Util::Util()
{
}

Util::~Util()
{
}

AActor* Util::FindActor(UWorld* World, FString Name)
{
	for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr)
	{
		AActor *Actor = *ActorItr;
		if (Actor->GetName() == Name)
		{
			return Actor;				
		}
	}

	return nullptr;
}