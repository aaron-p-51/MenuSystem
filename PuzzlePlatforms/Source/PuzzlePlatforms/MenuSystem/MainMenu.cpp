// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;


	if (MainMenuHostButton == nullptr) return false;
	MainMenuHostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (MainMenuJoinButton == nullptr) return false;
	MainMenuJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (JoinMenuCancelButton == nullptr) return false;
	JoinMenuCancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (JoinMenuJoinButton == nullptr) return false;
	JoinMenuJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (QuitGameButton == nullptr) return false;
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);


	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr && IPAddressField != nullptr)
	{
		const FString& IP = IPAddressField->GetText().ToString();
		MenuInterface->Join(IP);
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher != nullptr && JoinMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(JoinMenu);
	}
}

void UMainMenu::OpenMainMenu()
{
	if (MenuSwitcher != nullptr && MainMenu != nullptr)
	{
		MenuSwitcher->SetActiveWidget(MainMenu);
	}
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->ConsoleCommand(TEXT("quit"), false);
}
