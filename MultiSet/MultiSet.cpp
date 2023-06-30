// MultiSet.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;

template <class T>
class MultiSet
{
    struct Node
    {
        T value{};
        int count = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };

    MultiSet() : size(0), root(nullptr) {}

    void Insert(const T& val)
    {
        if (root == nullptr)
        {
            root = new Node{ val,1, nullptr, nullptr, nullptr };
            size++;
            return;
        }
        Node* parent = nullptr;
        Node* node = root;
        while (node != nullptr && node->value != val) {
            parent = node;
            node = node->value > val ? node->left : node->right;
        }
        if (node == nullptr) {
            Node* temp = new Node{ val,1, nullptr, nullptr, parent };

            parent->value > val ? parent->left = temp : parent->right = temp;
        }
        else
        {
            node->count++;
        }
        size++;
    }
    void Erase(const T& val)
    {
        if (size > 0)
        {
            Node* node = root;
            Node* parent = nullptr;
            while (node->value != val && node != nullptr)
            {
                parent = node;
                node = node->value > val ? node->left : node->right;
            }
            if (node != nullptr)
            {
                if (node->left == nullptr && node->right == nullptr)
                {
                    if (node == root)
                    {
                        root = nullptr;
                    }
                    else
                    {
                        node == parent->right ? parent->right = nullptr : parent->left = nullptr;
                    }
                    delete node;
                }
                else if (node->left == nullptr)
                {
                    node->right->parent = node->parent;
                    if (node == root)
                    {
                        root = node->right;
                    }
                    else
                    {
                        node == parent->right ? parent->right = node->right : parent->left = node->right;
                    }
                    delete node;
                }
                else if (node->right == nullptr)
                {
                    node->left->parent = node->parent;
                    if (node == root)
                    {
                        root = node->left;
                    }
                    else
                    {
                        node == parent->left ? parent->left = node->left : parent->right = node->left;
                    }
                    delete node;
                }
                else
                {
                    Node* temp = Min(node->right);
                    if (temp->right)
                    {
                        temp->right->parent = temp->parent;
                    }
                    temp == temp->parent->right ? temp->parent->right = temp->right : temp->parent->right = temp->right;
                    node->value = temp->value;
                    node->count = temp->count;
                    delete temp;
                }
                size-=node->count;
            }

        }
    }
    void Print() {
        Print(root);
        cout << endl;
    }

    void Print(Node* node) {
        if (node != nullptr) {
            Print(node->left);
            for (int i = 0; i < node->count; i++)
            {
                cout << node->value << " ";
            }
            Print(node->right);
        }
    }

    Node* Min(Node* node)
    {
        if (node != nullptr)
        {
            while (node->left != nullptr)
            {
                node = node->left;
            }
        }
        return node;
    }

    Node* Max(Node* node)
    {
        if (node != nullptr)
        {
            while (node->right != nullptr)
            {
                node = node->right;
            }
        }
        return node;
    }

    int Size() {
        return size;
    }
private:
    int size = 0;
    Node* root = nullptr;
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    MultiSet <int> ms;
    int arr[]{ 45, 30, 50, 27, 39, 90, 30, 15, 70, 93 };
    for (int i = 0; i < 10; i++) {
        int val = arr[i];
        cout << val << " ";
        ms.Insert(val);
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
