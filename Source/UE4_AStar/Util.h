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

	template <typename ActorType>
	static ActorType* FindActor(UWorld* World, FString Name)
	{
		for (TActorIterator<ActorType> ActorItr(World); ActorItr; ++ActorItr)
		{
			ActorType *Actor = *ActorItr;
			if (Actor->GetName() == Name)
			{
				return Actor;
			}
		}

		return nullptr;
	}

	template <typename ObjectType>
	static ObjectType* FindObject(FString Name)
	{
		for (TObjectIterator<ObjectType> Itr; Itr; ++Itr)
		{
			if (Itr->GetName() == Name)
			{
				return *Itr;
			}
		}

		return nullptr;
	}
};
