#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<stack>
#include<algorithm>
using namespace std;

//二叉树结构
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//二叉树的前序遍历
vector<int> preorderTraversal(TreeNode* root) { 
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode*> stk;
    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) {//一直向左下走
            res.push_back(root->val);//访问当前节点（相对的根节点）
            stk.push(root);//当前节点入栈
            root = root->left;//将当前节点设置当前节点的左孩子
        }
        //走到了左下的尽头，即当前节点没有左孩子
        root = stk.top(); //取到上一级的节点
        stk.pop();
        root = root->right;//将当前节点设置为当前节点的右孩子，即使为空也没有关系，因为在while循环里判断了
    }
    return res;
}

// 二叉树的中序遍历
// 与前序遍历的区别就在于一直往左下走的时候，中序遍历不会访问该节点，而只是入栈，直到没有左孩子的时候，才会访问该节点
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }

    stack<TreeNode*> stk;
    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) {//一直往左下走
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.push_back(root->val); //访问最左下的节点
        root = root->right;
    }
    return res;
}

//二叉树的后序遍历
vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }

    stack<TreeNode*> stk;
    TreeNode *prev = nullptr;
    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) { //一直往左下走
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        if (root->right == nullptr || root->right == prev) { //只有在当前节点的右孩子为空或者已经被访问过时，才可以访问当前节点
            res.push_back(root->val);
            prev = root;
            root = nullptr;
        } else { //否则，当前节点入栈，并开始访问右孩子
            stk.push(root);
            root = root->right;
        }
    }
    return res;
}

//并查集
class Union {
public:
    Union(int n){
        for(int i=0;i<n;i++){
            fa.push_back(i);
        }
    }
    int find(int x){
        if(fa[x]==x){
            return x;
        }
        else{
            fa[x]=find(fa[x]);
            return fa[x];
        }
    }
    void merge(int i,int j){
        int x=find(i),y=find(j);
        fa[x]=y;
    }
private:
    vector<int> fa;
};