// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"

// Engine Includes
#include "Components/BoxComponent.h"

#include "MovingPlatform.h"

// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (TriggerVolume == nullptr) return;
	
	SetRootComponent(TriggerVolume);


}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerVolume)
	{
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerVolumeOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerVolumeOverlapEnd);

		TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		TriggerVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	}
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::OnTriggerVolumeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (auto Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APlatformTrigger::OnTriggerVolumeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}


	

