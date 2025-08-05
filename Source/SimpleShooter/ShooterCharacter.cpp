// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Ensure we have a valid PlayerController
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// Check if the subsystem is valid
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add mapping context with priority 0
			Subsystem->AddMappingContext(ShooterCharacterMappingContext, 0); 
		}
	}
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Ensure PlayerInputComponent is of type UEnhancedInputComponent
	// This is necessary to use the enhanced input system features
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the Move action to the Move function
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move); 
		// Bind the Look action to the Look function
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look); 
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Jump); 


	}

}

void AShooterCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();// Get the 2D vector from the input action value
	
	const FVector Forward = GetActorForwardVector(); // Get the forward vector of the character
	AddMovementInput(Forward, MovementVector.Y); // Add movement input in the forward direction based on the Y component of the input vector

	const FVector Right = GetActorRightVector(); // Get the right vector of the character
	AddMovementInput(Right, MovementVector.X); // Add movement input in the right direction based on the X component of the input vector
}

void AShooterCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>(); // Get the 2D vector from the input action value for looking around
	
	AddControllerYawInput(LookVector.X); // Add yaw input based on the X component of the input vector
	AddControllerPitchInput(LookVector.Y); // Add pitch input based on the Y component of the input vector
}

void AShooterCharacter::Jump(const FInputActionValue& Value)
{
	if (Value.Get<bool>()) // Check if the input action value indicates a jump (true for pressed)
    {
        ACharacter::Jump(); 
    }
}