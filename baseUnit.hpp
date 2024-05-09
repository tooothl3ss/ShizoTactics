// include/unit.hpp
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "attack.hpp"
#include "effect.hpp"

class Unit {
protected:
    std::string name = "Chort";
    std::unique_ptr<Attack> attackType;
    std::vector<StatusEffect> statusEffects; // Эффекты состояния
    int health = 100;
    int attackPower = 10; // depense on 
    int defense = 15;
    int lvl = 0;
    int exp = 0; // будет обнуляться каждый лвл
    int maxlvl = 99;
    int gateExp = 1000; // будет увеличиваться с лвлом
    int criticalHitChance = 25; //%%
    int rang = 0;
    int hitChance = 25; // будет зависить от обзора, высоты, дальности цели и лвла юнита
    bool stunned = false; 
    int accuracy = 1; 
    int attackRange = 2;

public:
    // Конструктор по умолчанию
    Unit() = default;

    // Конструктор с именем и атрибутами
    Unit(const std::string& name, int health, int defense, int accuracy, int attackRange, int attackPower)
        : name(name), baseHealth(health), baseDefense(defense), baseAccuracy(accuracy),
          baseAttackRange(attackRange), baseAttackPower(attackPower),
          health(health), defense(defense), accuracy(accuracy), attackRange(attackRange), attackPower(attackPower) {}

    // Получить имя юнита
    std::string getName() const { return name; }

    // Получить текущее здоровье
    int getHealth() const { return health; }

    // Получить текущую защиту
    int getDefense() const { return defense; }

    // Получить точность юнита
    int getAccuracy() const { return accuracy; }

    // Получить силу атаки юнита
    int getAttackPower() const { return attackPower; }

    // Получить дальность атаки
    int getAttackRange() const { return attackRange; }

    // Метод получения урона с учетом брони
    void takeDamage(int damage);

    // Метод атаки другого юнита
    virtual void attack(Unit& target) const;

    // Установить тип атаки
    void setAttackType(std::unique_ptr<Attack> attack) {
        attackType = std::move(attack);
    }

    // Метод исцеления
    void heal(int amount);

    // Проверка, жив ли юнит
    bool isAlive() const { return health > 0; }

    // Проверка, оглушен ли юнит
    bool isStunned() const {
        return std::any_of(statusEffects.begin(), statusEffects.end(), [](const StatusEffect& effect) {
            return effect.type == StatusEffectType::Stun && effect.isActive();
        });
    }

    // Применить эффект к юниту
    void applyEffect(const StatusEffect& effect) {
        statusEffects.push_back(effect);
        std::cout << name << " получил эффект: " << effect.getName() << " на " << effect.duration << " ходов.\n";
    }

    // Обновить эффекты (уменьшить их продолжительность)
    void updateEffects() {
        for (auto& effect : statusEffects) {
            effect.applyEffect();
        }
        statusEffects.erase(std::remove_if(statusEffects.begin(), statusEffects.end(),
            [](const StatusEffect& effect) { return !effect.isActive(); }), statusEffects.end());
        applyStatusEffects(); // Применить эффекты на характеристики
    }

    // Применить все активные эффекты на характеристики юнита
    void applyStatusEffects() {
        health = baseHealth;
        defense = baseDefense;
        attackPower = baseAttackPower;
        accuracy = baseAccuracy;

        for (const auto& effect : statusEffects) {
            if (effect.isActive()) {
                switch (effect.type) {
                    case StatusEffectType::DecreasedDefense:
                        defense = std::max(0, defense - effect.magnitude);
                        break;
                    case StatusEffectType::DecreasedAttackPower:
                        attackPower = std::max(0, attackPower - effect.magnitude);
                        break;
                    case StatusEffectType::DecreasedAccuracy:
                        accuracy = std::max(0, accuracy - effect.magnitude);
                        break;
                    case StatusEffectType::Poisoned:
                        health = std::max(0, health - effect.magnitude);
                        std::cout << name << " получил урон от отравления: " << effect.magnitude << "\n";
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // Метод отображения текущего состояния юнита
    virtual void displayStatus() const;
};
