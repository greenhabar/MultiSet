// MultiSet.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>

using namespace std;

template <class T>
class MultiSet
{
public:
    struct Node
    {
        T value{};
        int count = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };

    MultiSet() : size(0), root(nullptr) {}
    MultiSet(const MultiSet& other) : size(other.size), root(Copy(other.root, nullptr)) {}

    MultiSet(MultiSet&& other) : size(other.size), root(other.root)
    {
        other.root = nullptr;
        other.size = 0;
    }

    MultiSet& operator=(MultiSet&& other)
    {
        if (this != &other)
        {
            Clear();
            size = other.size;
            root = other.root;
            other.root = nullptr;
            other.size = 0;
        }
        return *this;
    }

    bool operator==(const MultiSet& other)
    {
        return size == other.size && Compare(root, other.root);
    }
    bool operator!=(const MultiSet& other)
    {
        return !(*this == other);
    }

    MultiSet& operator=(const MultiSet& other)
    {
        if (this != &other)
        {
            Clear();
            size = other.size;
            root = Copy(other.root, nullptr);
        }
        return *this;
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

    Node* Copy(Node* node, Node* parent)
    {
        if (!node) return node;
        Node* temp = new Node{ node->value, node->count, nullptr, nullptr, parent };
        temp->left = Copy(node->left, temp);
        temp->right = Copy(node->right, temp);
        return temp;
    }

    bool Compare(Node* a, Node* b)
    {
        if (a == nullptr && b == nullptr)
        {
            return true;
        }
        return (a && b) && (a->value == b->value) && (a->count == b->count) && Compare(a->left, b->left) && Compare(a->right, b->right);
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

    Node* Find(const T& val)
    {
        Node* node = root;
        while (node && node->value != val)
        {
            node = node->value > val ? node->left : node->right;
        }
        return node;
    }

    int Count(const T& val)
    {
        return Find(val) == nullptr ? 0 : 1;
    }

    Node* Next(Node* node)
    {
        if (node)
        {
            if (node->right)
            {
                return Min(node->right);
            }
            Node* parent = node->parent;
            while (parent && node->value > parent->value)
            {
                parent = parent->parent;
            }
            return parent;
        }
    }

    Node* Prev(Node* node)
    {
        if (node)
        {
            if (node->left)
            {
                return Max(node->left);
            }
            Node* parent = node->parent;
            while (parent && node->value < parent->value)
            {
                parent = parent->parent;
            }
            return parent;
        }
    }

    void Clear()
    {
        Clear(root);
        root = nullptr;
        size = 0;
    }

    void Clear(Node* node) {
        if (node != nullptr) {
            Clear(node->left);
            Clear(node->right);
            delete node;
        }
    }

    Node* Begin()
    {
        return Min(root);
    }
    Node* End()
    {
        return Max(root);
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

    int Size() {
        return size;
    }

    ~MultiSet()
    {
        Clear();
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
    cout << "\n";

    ms.Print();
    ms.Erase(30);
    ms.Print();
    cout << ms.Begin()->value << "\n";
    cout << ms.End()->value << "\n";

    MultiSet <int> ms2;
    ms2 = move(ms);
    ms2.Print();
    ms.Print();
}