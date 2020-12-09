// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Speed = 5.f;

}



void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetMobility(EComponentMobility::Movable);

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();

	// Convert TargetLocation which is local to the Actor to its Global Position
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	DistanceBetweenLocations_Sqrd = (GlobalTargetLocation - GlobalStartLocation).SizeSquared();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			MovePlatform(DeltaTime);
		}
	}
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	float DistanceTraveled_Sqrd = (CurrentLocation - GlobalStartLocation).SizeSquared();

	if (DistanceTraveled_Sqrd > DistanceBetweenLocations_Sqrd)
	{
		SwapStartAndEndLocation(GlobalStartLocation, GlobalTargetLocation);
		DistanceBetweenLocations_Sqrd = (GlobalTargetLocation - GlobalStartLocation).SizeSquared();
	}

	FVector TravelThisFrame = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal() * Speed * DeltaTime;
	SetActorLocation(TravelThisFrame + CurrentLocation);
}


void AMovingPlatform::SwapStartAndEndLocation(FVector& StartLocation, FVector& EndLocation)
{
	FVector Temp = StartLocation;
	StartLocation = EndLocation;
	EndLocation = Temp;
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
	
}
