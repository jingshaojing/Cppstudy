// 三种二叉树的遍历
// 顺带用两种方式创建二叉树

#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct Treenode
{
    int val;
    Treenode* left;
    Treenode* right;
    Treenode() : val(0),left(nullptr),right(nullptr) {}
    Treenode(int x) : val(x), left(nullptr),right(nullptr) {}
    Treenode(int x, Treenode* left, Treenode* right) : val(x), left(left), right(right) {}
};
class solution
{
public:
    // 中序遍历
    void inorder_traverse(Treenode* cur, vector<int> &vec)
    {
        if (cur == nullptr) return;
        inorder_traverse(cur->left,vec);
        vec.push_back(cur->val);
        inorder_traverse(cur->right, vec);
    }
    // 前序遍历
    void preorder_traverse(Treenode* cur, vector<int>& vec)
    {
        if (cur == nullptr) return;
        vec.push_back(cur->val);
        preorder_traverse(cur->left, vec);
        preorder_traverse(cur->right, vec);
     }
    // 后序遍历
    void postorder_traverse(Treenode* cur, vector<int>& vec)
    {
        if (cur == nullptr) return;
        postorder_traverse(cur->left, vec);
        postorder_traverse(cur->right, vec);
        vec.push_back(cur->val);
    }
    vector<int> preOrderTraverse_iteration(Treenode* root)
    {
        vector<int> result;
        stack<Treenode*> sta;
        if (root != nullptr)
        {
            sta.push(root);
        }
        while (!sta.empty())
        {
            Treenode* temp = sta.top();
            if (temp != NULL)
            {
                sta.pop();
                if (temp->right) sta.push(temp->right);
                if (temp->left)  sta.push(temp->left);
                sta.push(temp);
                sta.push(NULL);
            }
            else
            {
                sta.pop();
                temp = sta.top();
                sta.pop();
                result.push_back(temp->val);
            }
        }
        return result;
    }
    // 迭代法中序遍历
    vector<int> inOrderTraverse_iteration(Treenode* root)
    {
        vector<int> result;
        stack<Treenode*> sta;
        if (root != nullptr)
        {
            sta.push(root);
        }
        while (!sta.empty())
        {
            Treenode* temp = sta.top();
            if (temp != NULL)
            {
                sta.pop();
                if (temp->right) sta.push(temp->right);
                sta.push(temp);
                sta.push(NULL);
                if (temp->left) sta.push(temp->left);
            }
            else
            {
                sta.pop();
                temp = sta.top();
                sta.pop();
                result.push_back(temp->val);
            }
        }
        return result;
    }
    // 迭代法后续遍历
    vector<int> postOrderTraverse(Treenode* root)
    {
        vector<int> result;
        stack<Treenode*> sta;
        if (root != nullptr)
        {
            sta.push(root);
        }
        while (!sta.empty())
        {
            Treenode* temp = sta.top();
            if (temp != NULL)
            {
                sta.pop();
                sta.push(temp);
                sta.push(NULL);
                if (temp->left) sta.push(temp->left);
                if (temp->right) sta.push(temp->right);
            }
            else
            {
                sta.pop();
                temp = sta.top();
                sta.pop();
                result.push_back(temp->val);
            }
        }
        return result;
    }
    vector<int> traverse(Treenode* root)
    {
        vector<int> result;
        inorder_traverse(root, result);
        //preorder_traverse(root, result);
        //postorder_traverse(root, result);
    }
    // 中序遍历和后序遍历构造二叉树
    Treenode* traverse_creatTree(vector<int>& inorder, vector<int>& postorder)
    {
        if (postorder.size() == 0) return NULL;
        int rootvalue = postorder[postorder.size() - 1];
        Treenode* root = new Treenode(rootvalue);
        if (postorder.size() == 1) return root;
        // 该值必须定义在外面，不然出了for循环就失效
        int delimeterIndex;
        for (delimeterIndex = 0; delimeterIndex < inorder.size(); delimeterIndex++)
        {
            if (inorder[delimeterIndex] == rootvalue) break;
        }
        postorder.resize(postorder.size() - 1);
        vector<int> left_inorder(inorder.begin(), inorder.begin() + delimeterIndex);
        vector<int> right_inorder(inorder.begin() + delimeterIndex + 1, inorder.end());
        // 根据中序的左右数组大小决定后序的左右数组
        vector<int> left_postorder(postorder.begin(), postorder.begin() + left_inorder.size());
        vector<int> right_postorder(postorder.begin() + left_inorder.size(), postorder.end());
        // 开始递归调用
        root->left = traverse_creatTree(left_inorder, left_postorder);
        root->right = traverse_creatTree(right_inorder, right_postorder);
        return root;      
    }
    // 中序后序构造二叉树，前序和中序也可以构建
    Treenode* buildTree(vector<int>& inorder, vector<int>& postorder)
    {
        if (inorder.size() == 0 || postorder.size() == 0) return NULL;
        return traverse_creatTree(inorder, postorder);
    }
    // 数组构造
    Treenode* constuct_tree(const vector<int>& nums)
    {
        vector<Treenode*> vecTree(nums.size(), NULL);
        Treenode* root = NULL;
        for (int i = 0; i < nums.size(); i++)
        {
            Treenode* node = NULL;
            if (nums[i] != -1) node = new Treenode(nums[i]);
            vecTree[i] = node;
            if (i == 0) root = node;
        }
        for (int i = 0; i*2 + 2 < nums.size(); i++)
        {
            if (vecTree[i] != NULL)
            {
                vecTree[i]->left = vecTree[i * 2 + 1];
                vecTree[i]->right = vecTree[i * 2 + 2];
            }
        }
        return root;
    }
    bool isvalid_binary_search_tree(Treenode* root)
    {
        inorder_traverse(root);
        for(int i = 1; i < vec.size(); i++)
        {
            if(vec[i] <= vec[i-1]) retutn false; 
        }
        return true;
    }
};
int main()
{
    int number;
    vector<int> result;
    vector<int> inorder, postorder;
    while (cin >> number)
    {
        inorder.push_back(number);
        if (cin.get() == '\n') break;
    }
    //while (cin >> number)
    //{
    //    postorder.push_back(number);
     //   if (cin.get() == '\n') break;
    //}
    //Treenode* root = solution().buildTree(inorder, postorder);
    // 数组构造二叉树之后，构造规则其实是层序遍历
    Treenode* root = solution().constuct_tree(inorder);
    solution().postorder_traverse(root, result);
    for (auto ch : result)
    {
        cout << ch << " ";
    }
    return 0;
}