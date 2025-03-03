#include <iostream>
#include <algorithm>
using namespace std;

struct bstnode
{
    int data;
    bstnode *left, *right;
    int ldeep, rdeep;
    bstnode(int val) : data(val), left(NULL), right(NULL), ldeep(0), rdeep(0) {}
};

bstnode *balance_bst(bstnode *root)
{
    if (root == NULL)
        return root;
    if (root->ldeep - root->rdeep == 2 && root->left->ldeep - root->left->rdeep == 1) // LL型，左旋
    {
        bstnode *temp = root;
        root = root->left;
        temp->left = root->right;
        temp->ldeep = temp->left ? max(temp->left->ldeep, temp->left->rdeep) + 1 : 0;
        root->right = temp;
        root->rdeep = root->right ? max(root->right->ldeep, root->right->rdeep) + 1 : 0;
    }
    else if (root->ldeep - root->rdeep == -2 && root->right->ldeep - root->right->rdeep == -1) // RR型，右旋
    {
        bstnode *temp = root;
        root = root->right;
        temp->right = root->left;
        temp->rdeep = temp->right ? max(temp->right->ldeep, temp->right->rdeep) + 1 : 0;
        root->left = temp;
        root->ldeep = root->left ? max(root->left->ldeep, root->left->rdeep) + 1 : 0;
    }
    else if (root->ldeep - root->rdeep == 2 && root->left->ldeep - root->left->rdeep == -1) // LR型，先左旋左孩子再右旋
    {
        bstnode *temp = root->left;
        root->left = temp->right;
        temp->right = temp->right->left;
        root->left->left = temp;
        temp->rdeep = temp->right ? max(temp->right->ldeep, temp->right->rdeep) + 1 : 0;
        root->left->ldeep = root->left->left ? max(root->left->left->ldeep, root->left->left->rdeep) + 1 : 0;
        root->ldeep = root->left ? max(root->left->ldeep, root->left->rdeep) + 1 : 0;
        temp = root;
        root = root->left;
        temp->left = root->right;
        temp->ldeep = temp->left ? max(temp->left->ldeep, temp->left->rdeep) + 1 : 0;
        root->right = temp;
        root->rdeep = root->right ? max(root->right->ldeep, root->right->rdeep) + 1 : 0;
    }
    else if (root->ldeep - root->rdeep == -2 && root->right->ldeep - root->right->rdeep == 1) // RL型，先右旋右孩子再左旋
    {
        bstnode *temp = root->right;
        root->right = temp->left;
        temp->left = root->right->right;
        root->right->right = temp;
        temp->ldeep = temp->left ? max(temp->left->ldeep, temp->left->rdeep) + 1 : 0;
        root->right->rdeep = root->right->right ? max(root->right->right->ldeep, root->right->right->rdeep) + 1 : 0;
        root->rdeep = root->right ? max(root->right->ldeep, root->right->rdeep) + 1 : 0;
        temp = root;
        root = root->right;
        temp->right = root->left;
        temp->rdeep = temp->right ? max(temp->right->ldeep, temp->right->rdeep) + 1 : 0;
        root->left = temp;
        root->ldeep = root->left ? max(root->left->ldeep, root->left->rdeep) + 1 : 0;
    }
    return root;
}

void insert_node(bstnode *&root, bstnode *node)
{
    if (node->data < root->data)
    {
        if (!root->left)
            root->left = node;
        else
            insert_node(root->left, node);
        root->ldeep = max(root->left->ldeep, root->left->rdeep) + 1;
        if (abs(root->ldeep - root->rdeep) > 1)
        {
            root = balance_bst(root);
        }
    }
    else
    {
        if (!root->right)
            root->right = node;
        else
            insert_node(root->right, node);
        root->rdeep = max(root->right->ldeep, root->right->rdeep) + 1;
        if (abs(root->ldeep - root->rdeep) > 1)
        {
            root = balance_bst(root);
        }
    }
}

bstnode *create_bst(int *data, int n)
{
    if (n <= 0)
        return NULL;
    bstnode *res = new bstnode(data[0]);
    for (int i = 1; i < n; i++)
    {
        bstnode *temp = new bstnode(data[i]);
        insert_node(res, temp);
    }
    return res;
}

bstnode *search_bst(bstnode *root, int data)
{
    if (!root)
        return NULL;
    if (data == root->data)
        return root;
    else if (data < root->data)
        return search_bst(root->left, data);
    else
        return search_bst(root->right, data);
}

bstnode *delete_bst(bstnode *root, int data)
{
    if (root->data == data)
    {
        if (!root->left && !root->right)
        {
            delete root;
            return NULL;
        }
        else if (root->left && !root->right)
        {
            bstnode *temp = root->left;
            delete root;
            return temp;
        }
        else if (!root->left && root->right)
        {
            bstnode *temp = root->right;
            delete root;
            return temp;
        }
        else
        {
            bstnode *temp = root->right, *tempp = root;
            while (temp->left)
            {
                tempp = temp;
                temp = temp->left;
            }
            int res = temp->data;
            root = delete_bst(root, res);
            root->data = res;
            return root;
        }
    }
    else if (data < root->data)
    {
        root->left = delete_bst(root->left, data);
        root->ldeep = root->left ? max(root->left->ldeep, root->left->rdeep) + 1 : 0;
        if (abs(root->ldeep - root->rdeep) > 1)
        {
            root = balance_bst(root);
        }
    }
    else
    {
        root->right = delete_bst(root->right, data);
        root->rdeep = root->right ? max(root->right->ldeep, root->right->rdeep) + 1 : 0;
        if (abs(root->ldeep - root->rdeep) > 1)
        {
            root = balance_bst(root);
        }
    }
    return root;
}

void inorder(bstnode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main()
{
    // 创建一个包含一些整数的数组
    int data[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(data) / sizeof(data[0]);

    // 使用数组数据创建平衡二叉搜索树
    bstnode *root = create_bst(data, n);

    // 输出创建后的树
    cout << "Initial tree:" << endl;
    inorder(root); // 调用修改后的中序遍历函数
    cout << endl;

    // 搜索节点
    int search_value = 30;
    bstnode *search_result = search_bst(root, search_value);
    if (search_result)
    {
        cout << "Found node with value " << search_value << endl;
    }
    else
    {
        cout << "Node with value " << search_value << " not found" << endl;
    }

    // 删除节点
    int delete_value = 20;
    root = delete_bst(root, delete_value);
    cout << "Tree after deleting node with value " << delete_value << ":" << endl;
    inorder(root); // 再次输出树的内容以验证删除操作
    cout << endl;

    // 搜索已删除的节点，验证是否成功删除
    search_result = search_bst(root, delete_value);
    if (search_result)
    {
        cout << "Node with value " << delete_value << " still exists!" << endl;
    }
    else
    {
        cout << "Node with value " << delete_value << " successfully deleted" << endl;
    }
    return 0;
}