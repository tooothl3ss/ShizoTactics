// src/unit.cpp
#include "baseUnit.hpp"

void Unit::takeDamage(int damage) {
    int damageTaken = std::max(0, damage - defense);
    health = std::max(0, health - damageTaken);
    std::cout << name << " получил урон: " << damageTaken << " и теперь у него " << health << " здоровья.\n";
}

void Unit::attack(Unit& target) const {
    if (isStunned()) {
        std::cout << name << " оглушен и не может атаковать!\n";
        return;
    }

    if (attackType) {
        std::cout << name << " атакует " << target.getName() << " используя " << attackType->getName() << "!\n";
        if (attackType->doesHit()) {
            int damage = attackType->calculateDamage(target.getDefense());
            target.takeDamage(damage);
        } else {
            std::cout << name << " промахнулся!\n";
        }
    } else {
        std::cout << name << " не имеет типа атаки!\n";
    }
}

void Unit::heal(int amount) {
    health = std::min(baseHealth, health + amount);
    std::cout << name << " исцелился на " << amount << " и теперь у него " << health << " здоровья.\n";
}

void Unit::displayStatus() const {
    std::cout << "Юнит: " << name << " | Здоровье: " << health << " | Броня: " << defense << " | Точность: " << accuracy << "% | Сила атаки: " << attackPower << '\n';
    if (attackType) {
        std::cout << "Тип атаки: " << attackType->getName() << " | Дальность атаки: " << attackType->getRange() << " | Шанс попадания: " << attackType->getHitChance() << "%\n";
    } else {
        std::cout << "Тип атаки не установлен.\n";
    }

    std::cout << "Состояния: ";
    if (statusEffects.empty()) {
        std::cout << "Нет\n";
    } else {
        for (const auto& effect : statusEffects) {
            std::cout << effect.getName() << " (" << effect.duration << " ходов) ";
        }
        std::cout << '\n';
    }
}
