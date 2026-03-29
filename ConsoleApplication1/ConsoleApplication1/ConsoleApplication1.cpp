#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
private:
    string name;
    int hp;
    int maxHp;
    int damage;
    vector<string> inventory;
    bool battleAxeUsed;

public:
    Person(string n, int h, int d) {
        name = n;
        hp = h;
        maxHp = h;
        damage = d;
        battleAxeUsed = false;
    }

    void addItem(string item) {
        inventory.push_back(item);
        cout << item << " добавлен в инвентарь " << name << endl;
    }

    void attack(Person& target) {
        cout << name << " атакует " << target.name << " и наносит " << damage << " урона!" << endl;
        target.takeDamage(damage);
    }

    void takeDamage(int d) {
        hp -= d;
        if (hp < 0) hp = 0;
        cout << "У " << name << " осталось " << hp << " HP." << endl;
        if (hp == 0) {
            cout << name << " повержен!" << endl;
        }
    }

    void battleAxeAttack(Person& target) {
        if (battleAxeUsed) {
            cout << "Боевой топор уже использован в этом бою!" << endl;
            return;
        }

        int halfHp = target.hp / 2;
        cout << name << " использует Боевой топор и наносит " << halfHp << " урона " << target.name << "!" << endl;
        target.takeDamage(halfHp);
        battleAxeUsed = true;
    }

    void useHealthPotion(int index) {
        if (index < 0 || index >= inventory.size()) {
            cout << "Неверный номер предмета!" << endl;
            return;
        }

        string item = inventory[index];
        if (item == "Зелье здоровья") {
            hp += 30;
            if (hp > maxHp) hp = maxHp;
            cout << name << " восстанавливает 30 HP. Теперь HP: " << hp << endl;
            inventory.erase(inventory.begin() + index);
        }
        else if (item == "Яблоко") {
            hp += 10;
            if (hp > maxHp) hp = maxHp;
            cout << name << " восстанавливает 10 HP. Теперь HP: " << hp << endl;
            inventory.erase(inventory.begin() + index);
        }
        else if (item == "Зелье силы") {
            damage += 10;
            cout << name << " увеличивает урон на 10. Теперь урон: " << damage << endl;
            inventory.erase(inventory.begin() + index);
        }
        else {
            cout << "Этот предмет нельзя использовать так!" << endl;
        }
    }

    void useVampirismPotion(int index, Person& target) {
        if (index < 0 || index >= inventory.size()) {
            cout << "Неверный номер предмета!" << endl;
            return;
        }

        string item = inventory[index];
        if (item == "Зелье вампиризма") {
            int vampDamage = damage;
            cout << name << " использует Зелье вампиризма и атакует " << target.name << "!" << endl;
            target.takeDamage(vampDamage);
            int healAmount = vampDamage / 2;
            hp += healAmount;
            if (hp > maxHp) hp = maxHp;
            cout << name << " восстанавливает " << healAmount << " HP. Теперь HP: " << hp << endl;
            inventory.erase(inventory.begin() + index);
        }
        else {
            cout << "Это не зелье вампиризма!" << endl;
        }
    }

    void showInventory() {
        if (inventory.empty()) {
            cout << "Инвентарь " << name << " пуст." << endl;
            return;
        }

        cout << "\n=== Инвентарь " << name << " ===" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            cout << i << ". " << inventory[i] << endl;
        }
        cout << "=========================" << endl;
    }

    void showStatus() {
        cout << "\n--- " << name << " ---" << endl;
        cout << "HP: " << hp << "/" << maxHp << endl;
        cout << "Урон: " << damage << endl;
        cout << "Предметов: " << inventory.size() << endl;
        showInventory();
    }

    string getName() {
        return name;
    }

    int getHp() {
        return hp;
    }

    bool isAlive() {
        return hp > 0;
    }

    bool canUseBattleAxe() {
        for (string item : inventory) {
            if (item == "Боевой топор") return true;
        }
        return false;
    }

    bool isBattleAxeUsed() {
        return battleAxeUsed;
    }

    vector<string> getInventory() {
        return inventory;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Person hero("Герой", 100, 25);
    Person goblin("Гоблин", 80, 15);

    hero.addItem("Зелье здоровья");
    hero.addItem("Боевой топор");
    hero.addItem("Зелье вампиризма");
    hero.addItem("Яблоко");
    hero.addItem("Зелье силы");

    hero.showStatus();
    goblin.showStatus();

    cout << "\n=== НАЧАЛО БОЯ ===" << endl;
    cout << "========================================" << endl;

    while (hero.isAlive() && goblin.isAlive()) {
        cout << "\nТвой ход!" << endl;
        cout << "1. Атаковать" << endl;
        cout << "2. Использовать лечащий предмет (зелье здоровья, яблоко, зелье силы)" << endl;
        cout << "3. Использовать Зелье вампиризма" << endl;

        if (hero.canUseBattleAxe() && !hero.isBattleAxeUsed()) {
            cout << "4. Использовать Боевой топор (отнимает половину HP врага, 1 раз за бой)" << endl;
        }

        cout << "Выбери действие: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            hero.attack(goblin);
        }
        else if (choice == 2) {
            hero.showInventory();
            cout << "Введите номер предмета (зелье здоровья, яблоко или зелье силы): ";
            int itemIndex;
            cin >> itemIndex;
            hero.useHealthPotion(itemIndex);
        }
        else if (choice == 3) {
            hero.showInventory();
            cout << "Введите номер предмета (зелье вампиризма): ";
            int itemIndex;
            cin >> itemIndex;
            hero.useVampirismPotion(itemIndex, goblin);
        }
        else if (choice == 4 && hero.canUseBattleAxe() && !hero.isBattleAxeUsed()) {
            hero.battleAxeAttack(goblin);
        }
        else {
            cout << "Неверный выбор! Пропуск хода." << endl;
        }

        if (!goblin.isAlive()) {
            cout << "\nГоблин повержен! Ты победил!" << endl;
            break;
        }

        cout << "\nХод Гоблина:" << endl;
        goblin.attack(hero);

        if (!hero.isAlive()) {
            cout << "\nГерой повержен! Ты проиграл!" << endl;
            break;
        }

        hero.showStatus();
        goblin.showStatus();
        cout << "----------------------------------------" << endl;
    }

    return 0;
}
// new fitch
