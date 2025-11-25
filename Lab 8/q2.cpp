#include <iostream>
#include <string>
using namespace std;

class Combatant
{
public:
    string name;
    int hp;
    int attack;
    Combatant() {}
    Combatant(string n, int h, int a)
    {
        name = n;
        hp = h;
        attack = a;
    }
};

class Node
{
public:
    Combatant data;
    Node *left;
    Node *right;
    Node(Combatant c)
    {
        data = c;
        left = right = NULL;
    }
};

class BST
{
public:
    Node *root;
    BST() { root = NULL; }

    Node *insert(Node *node, Combatant c)
    {
        if (!node)
            return new Node(c);
        if (c.name < node->data.name)
            node->left = insert(node->left, c);
        else
            node->right = insert(node->right, c);
        return node;
    }

    void insert(Combatant c)
    {
        root = insert(root, c);
    }

    Node *minNode(Node *node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node *deleteNode(Node *node, string name)
    {
        if (!node)
            return node;
        if (name < node->data.name)
            node->left = deleteNode(node->left, name);
        else if (name > node->data.name)
            node->right = deleteNode(node->right, name);
        else
        {
            if (!node->left)
            {
                Node *t = node->right;
                delete node;
                return t;
            }
            if (!node->right)
            {
                Node *t = node->left;
                delete node;
                return t;
            }
            Node *t = minNode(node->right);
            node->data = t->data;
            node->right = deleteNode(node->right, t->data.name);
        }
        return node;
    }

    void remove(string name)
    {
        root = deleteNode(root, name);
    }

    Node *frontline()
    {
        return minNode(root);
    }

    void show(Node *node)
    {
        if (!node)
            return;
        show(node->left);
        cout << node->data.name << " (HP: " << node->data.hp << ")  ";
        show(node->right);
    }

    bool empty()
    {
        return root == NULL;
    }
};

int main()
{
    BST heroes, enemies;

    heroes.insert(Combatant("Aiden", 30, 6));
    heroes.insert(Combatant("Blaze", 32, 5));
    heroes.insert(Combatant("Cyra", 28, 7));
    heroes.insert(Combatant("Drake", 35, 4));
    heroes.insert(Combatant("Elara", 26, 8));

    enemies.insert(Combatant("Goblin", 25, 5));
    enemies.insert(Combatant("Orc", 33, 6));
    enemies.insert(Combatant("Viper", 22, 7));
    enemies.insert(Combatant("Troll", 38, 4));
    enemies.insert(Combatant("Specter", 30, 6));

    int round = 1;

    while (!heroes.empty() && !enemies.empty())
    {

        cout << "\nRound " << round << "\n";

        cout << "\nHeroes: ";
        heroes.show(heroes.root);

        cout << "\nEnemies: ";
        enemies.show(enemies.root);

        Node *h = heroes.frontline();
        Node *e = enemies.frontline();

        cout << "\n\nPlayer's turn\n";
        int dmg = h->data.attack + 2;
        cout << h->data.name << " attacks " << e->data.name << " and deals " << dmg << ".\n";
        e->data.hp -= dmg;

        if (e->data.hp <= 0)
        {
            cout << e->data.name << " has been defeated.\n";
            enemies.remove(e->data.name);
            if (enemies.empty())
                break;
            e = enemies.frontline();
        }

        cout << "\nEnemy's turn\n";
        dmg = e->data.attack + 2;
        cout << e->data.name << " attacks " << h->data.name << " and deals " << dmg << ".\n";
        h->data.hp -= dmg;

        if (h->data.hp <= 0)
        {
            cout << h->data.name << " has been defeated.\n";
            heroes.remove(h->data.name);
            if (heroes.empty())
                break;
        }

        round++;
    }

    if (heroes.empty())
    {
        cout << "\nEnemies won." << endl;
    }
    else
    {
        cout << "\nHeroes won." << endl;
    }

    return 0;
}
