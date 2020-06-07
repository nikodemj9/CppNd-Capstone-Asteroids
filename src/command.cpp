#include "command.h"

void AccelerateCommand::execute(Spaceship *spaceship)
{
    spaceship->Accelerate(true);
}

void DecelarateCommand::execute(Spaceship *spaceship)
{
    spaceship->Accelerate(false);
}

void RotateLeftCommand::execute(Spaceship *spaceship)
{
    spaceship->Rotate(false);
}

void RotateRightCommand::execute(Spaceship *spaceship)
{
    spaceship->Rotate(true);
}

void ShootCommand::execute(Spaceship *spaceship)
{
    spaceship->Shoot();
}