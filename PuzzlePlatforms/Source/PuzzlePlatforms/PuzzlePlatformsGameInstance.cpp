// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

// Engine Classes
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/MenuWidget.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// A Much better way to do this is to derive a Blueprint class from this class and then set the UMenuClass there
	static ConstructorHelpers::FClassFinder<UMainMenu> MainMenuWidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MainMenuWidgetClass.Class == nullptr) return;
	MenuClass = MainMenuWidgetClass.Class;

	static ConstructorHelpers::FClassFinder<UInGameMenu> InGameMenuWidgetClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (InGameMenuWidgetClass.Class == nullptr) return;
	InGameMenuClass = InGameMenuWidgetClass.Class;

	UE_LOG(LogTemp, Warning, TEXT("In Game Window Class Name: %s"), *InGameMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
	if (MenuClass == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Main Window Name: %s"), *MenuClass->GetName());

}

void UPuzzlePlatformsGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->Destruct();
	}

	UEngine* Engine = GetEngine();
	if (Engine == nullptr) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	// Get the CURRENT World
	UWorld* World = GetWorld();

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IP_Address)
{
	if (Menu != nullptr)
	{
		Menu->Destruct();
	}

	UEngine* Engine = GetEngine();
	if (Engine == nullptr) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *IP_Address));	

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->ClientTravel(IP_Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass == nullptr) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (Menu == nullptr) return;

	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (InGameMenuClass == nullptr) return;

	UMenuWidget* InGameMenuWidget = CreateWidget<UMenuWidget>(this, InGameMenuClass);

	InGameMenuWidget->Setup();
	InGameMenuWidget->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}
