// include/attack.hpp
#pragma once

#include <string>
#include <iostream>

// Перечисление возможных типов атак
enum class DamageType {
    Physical,
    Magical,
    Fire,
    Ice
};

// Базовый класс для типов атак
class Attack {
protected:
    std::string name;
    int power;
    DamageType damageType;
    int range; // Дальность атаки
    int hitChance; // Шанс попадания (в процентах)

public:
    // Конструктор атаки
    Attack(const std::string& name, int power, DamageType damageType, int range, int hitChance)
        : name(name), power(power), damageType(damageType), range(range), hitChance(hitChance) {}

    // Получить название атаки
    std::string getName() const { return name; }

    // Получить силу атаки
    int getPower() const { return power; }

    // Получить тип урона
    DamageType getDamageType() const { return damageType; }

    // Получить дальность атаки
    int getRange() const { return range; }

    // Получить шанс попадания
    int getHitChance() const { return hitChance; }

    // Проверить, попадает ли атака по цели
    bool doesHit() const {
        return (rand() % 100) < hitChance;
    }

    // Виртуальный метод для вычисления итогового урона с учетом брони
    virtual int calculateDamage(int targetDefense) const = 0;
};

// Физическая атака
class PhysicalAttack : public Attack {
public:
    PhysicalAttack(int power, int range = 1, int hitChance = 80)
        : Attack("Физическая атака", power, DamageType::Physical, range, hitChance) {}

    int calculateDamage(int targetDefense) const override {
        int effectiveDamage = std::max(0, power - targetDefense);
        return effectiveDamage;
    }
};

// Магическая атака
class MagicalAttack : public Attack {
public:
    MagicalAttack(int power, int range = 3, int hitChance = 70)
        : Attack("Магическая атака", power, DamageType::Magical, range, hitChance) {}

    int calculateDamage(int targetDefense) const override {
        int effectiveDamage = power - targetDefense / 2; // Магия игнорирует половину брони
        return std::max(0, effectiveDamage);
    }
};

// Огненная атака
class FireAttack : public Attack {
public:
    FireAttack(int power, int range = 2, int hitChance = 75)
        : Attack("Огненная атака", power, DamageType::Fire, range, hitChance) {}

    int calculateDamage(int targetDefense) const override {
        int effectiveDamage = power - targetDefense / 4; // Огненная атака игнорирует четверть брони
        return std::max(0, effectiveDamage);
    }
};

// Ледяная атака
class IceAttack : public Attack {
public:
    IceAttack(int power, int range = 2, int hitChance = 65)
        : Attack("Ледяная атака", power, DamageType::Ice, range, hitChance) {}

    int calculateDamage(int targetDefense) const override {
        int effectiveDamage = power - targetDefense / 3; // Ледяная атака игнорирует треть брони
        return std::max(0, effectiveDamage);
    }
};
