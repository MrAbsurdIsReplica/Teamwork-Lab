#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
private:
    string name;
    int hp;
    int damage;
    vector<string> inventory;

public:
    Person(string n, int h, int d) {
        name = n;
        hp = h;
        damage = d;
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

    void useItem(int index) {
        if (index < 0 || index >= inventory.size()) {
            cout << "Неверный номер предмета!" << endl;
            return;
        }

        string item = inventory[index];
        cout << name << " использует " << item << endl;

        if (item == "Зелье здоровья") {
            hp += 30;
            cout << name << " восстанавливает 30 HP. Теперь HP: " << hp << endl;
        }
        else if (item == "Зелье силы") {
            damage += 10;
            cout << name << " увеличивает урон на 10. Теперь урон: " << damage << endl;
        }
        else if (item == "Яблоко") {
            hp += 10;
            cout << name << " восстанавливает 10 HP. Теперь HP: " << hp << endl;
        }
        else {
            cout << "Ничего не произошло. Возможно, этот предмет не имеет эффекта." << endl;
        }

        inventory.erase(inventory.begin() + index);
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
        cout << "HP: " << hp << endl;
        cout << "Урон: " << damage << endl;
        cout << "Предметов: " << inventory.size() << endl;
        showInventory();
    }

    string getName() {
        return name;
    }

    bool isAlive() {
        return hp > 0;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Person hero("Герой", 100, 25);
    Person goblin("Гоблин", 60, 15);

    hero.addItem("Зелье здоровья");
    hero.addItem("Меч");
    hero.addItem("Зелье силы");
    hero.addItem("Яблоко");

    hero.showStatus();
    goblin.showStatus();

    cout << "\n=== НАЧАЛО БОЯ ===" << endl;

    while (hero.isAlive() && goblin.isAlive()) {
        hero.attack(goblin);
        if (!goblin.isAlive()) break;

        goblin.attack(hero);
        if (!hero.isAlive()) break;

        hero.showStatus();
        goblin.showStatus();

        char choice;
        cout << "\nИспользовать предмет? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            hero.showInventory();
            int idx;
            cout << "Введите номер предмета: ";
            cin >> idx;
            hero.useItem(idx);
        }

        cout << "----------------------" << endl;
    }

    if (!hero.isAlive()) {
        cout << "\nГоблин победил!" << endl;
    }
    else {
        cout << "\nГерой победил!" << endl;
    }

    return 0;
}