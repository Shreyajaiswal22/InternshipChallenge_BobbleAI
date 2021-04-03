#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root)
            return "[]";
        
        queue<TreeNode*> q;
        TreeNode* curr_node = root;
        q.push(curr_node);
        stringstream serialTree;
        serialTree << "[" << curr_node->val << ",";
        
        while(!q.empty()){
            int elements_per_level = q.size();
            vector<TreeNode*> childs;
            bool all_childs_null = true;
            for(int k = 0 ; k < elements_per_level; k++){
                curr_node = q.front();
                q.pop();
                
                // iterate through and populate children
                if(curr_node->left) {
                    q.push(curr_node->left);
                    all_childs_null = false;
                }
                if(curr_node->right){
                    q.push(curr_node->right);
                    all_childs_null = false;
                }
                childs.push_back(curr_node->left);
                childs.push_back(curr_node->right);
            }
            
            // serialize the children
            if(!all_childs_null)
                for(int k = 0; k < childs.size(); k++)
                    if(childs[k])
                        serialTree << childs[k]->val << ",";
                    else
                        serialTree << "null,";
            
        }
        serialTree << "]";
        
        return serialTree.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        list<TreeNode*> lst;
        std::string element;
        string serialTreeInput = data;
        char f1 = serialTreeInput.front();
        char f2 = serialTreeInput.back();
        if(f1 == '[')
            serialTreeInput.erase(serialTreeInput.begin());
        if(f2 == ']')
            serialTreeInput.erase(serialTreeInput.end()-1);
        istringstream serialTree(serialTreeInput);
        
        // push elements to a queue
        while(getline(serialTree,element,',')){
            if(element != "null")
                lst.push_back(new TreeNode(atoi(element.c_str())));
            else
                lst.push_back(NULL);
            //std::cout << element << std::endl;
        }
        
        auto it = lst.begin();
        auto it_child = lst.begin();
        it_child++;
        TreeNode* root = *it;
        
        while(it_child != lst.end()){
            while(*it == NULL)
                it++;
            
            TreeNode* curr_node = *it;
            curr_node->left = *(it_child); 
            it_child++;
            curr_node->right = *(it_child); 
            it++; it_child++; // for next parent node
        }
        
        return root;
    }
};
