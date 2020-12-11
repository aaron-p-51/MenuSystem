// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"

#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (PauseCancelButton == nullptr) return false;
	PauseCancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CloseInGameMenu);

	if (PauseMainMenuButton == nullptr) return false;
	PauseMainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitToMainMenu);

	return true;
}

void UInGameMenu::CloseInGameMenu()
{
	TearDown();
}

void UInGameMenu::QuitToMainMenu()
{
	if (MenuInterface != nullptr)
	{
		TearDown();
		MenuInterface->LoadMainMenu();
	}
}