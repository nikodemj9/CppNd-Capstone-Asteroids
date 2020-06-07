#pragma once
#include "spaceship.h"
#include "rocket.h"

class Command
{
public:
    virtual ~Command() {};
    virtual void execute(Spaceship *spaceship) = 0;
};

class AccelerateCommand : public Command
{
public:
    virtual void execute(Spaceship *spaceship) override;
};

class DecelarateCommand : public Command
{
public:
    virtual void execute(Spaceship *spaceship) override;
};

class RotateLeftCommand : public Command
{
public:
    virtual void execute(Spaceship *spaceship) override;
};

class RotateRightCommand : public Command
{
public:
    virtual void execute(Spaceship *spaceship) override;
};

class ShootCommand : public Command
{
public:
    virtual void execute(Spaceship *spaceship) override;
};