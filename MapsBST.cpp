/*
    Name: Joshua Tan
    Student: 301624402
    CompID: jta241
*/

#include "MapsBST.hpp"
using namespace std;

// PRIVATE:
/*
    recursively insert map nodes into BST
    allows duplicates (maps with the same numberOfInternalWalls) and inserts it to the right
*/
MapBSTNode* MapsBST::insert(MapBSTNode* node, MapAsHex* valuePtr){
    // if valuePtr walls < node walls, check left of node
    if (valuePtr->getNumberOfInternalWalls() < node->mahPtr->getNumberOfInternalWalls()) {
        if (node->left != nullptr) {
            insert(node->left, valuePtr);
        }
        else {
            MapBSTNode* newNode = new MapBSTNode;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->parent = node;
            newNode->mahPtr = valuePtr;

            node->left = newNode;
            size++;
        }
    }

    // if valuePtr walls >= node walls, check right of node
    else {
        if (node->right != nullptr) {
            insert(node->right, valuePtr);
        }
        else {
            MapBSTNode* newNode = new MapBSTNode;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->parent = node;
            newNode->mahPtr = valuePtr;

            node->right = newNode;
            size++;
        }
    }
};

/*
    Recursively searches the BST for all maps with a number of internal walls equal to 'key'.
    Appends matching map pointers to the result vector.
    Traverses left if key < node's value, right otherwise (even when matched, to find duplicates).
*/
void MapsBST::search(MapBSTNode* node, const int key, vector<MapAsHex*> &result) const{
    // if key < node walls, check left of node
    if (key < node->mahPtr->getNumberOfInternalWalls()) {
        if (node->left != nullptr) {
            search(node->left, key, result);
        }
    }
    // if key >= node walls, check right of node
    else {
        // store matches
        if (key == node->mahPtr->getNumberOfInternalWalls()) {
            result.push_back(node->mahPtr);  
        }
        if (node->right != nullptr) {
            search(node->right, key, result);
        }
    }
};

/*
    Recursively prints the BST using in-order traversal.
    Outputs all maps in ascending order of internal walls.
*/
void MapsBST::print(MapBSTNode* node, ostream& os) const{
    // left
    if (node->left != nullptr) {
        print(node->left, os);
    }

    // print
    os << *node->mahPtr << endl;
    
    // right
    if (node->right != nullptr) {
        print(node->right, os);
    }

};

/*
    Recursively performs in-order traversal to rank maps from least to most internal walls.
    Appends map pointers to the result vector during traversal.
*/
void MapsBST::rank(MapBSTNode* node, vector<MapAsHex*> &result) const{
    // traverse left
    if (node->left != nullptr) {
        rank(node->left, result);
    }

    // add to rankedList (ascending)
    result.push_back(node->mahPtr);
    
    // traverse right
    if (node->right != nullptr) {
        rank(node->right, result);
    }
};

/*
    Recursively destroys the BST using post-order traversal.
    Frees memory for each node (but not the MapAsHex objects themselves).
*/
void MapsBST::destroy(MapBSTNode* node){
    if (node == nullptr) return;

    // traverse left
    if (node->left != nullptr) {
        destroy(node->left);
    }

    // traverse right
    if (node->right != nullptr) {
        destroy(node->right);
    }

    // destroy node
    delete node;
};

// PUBLIC:
/*
    Default constructor.
    Initializes the BST as an empty tree with root set to nullptr and size set to 0.
*/
MapsBST::MapsBST() {
    root = nullptr;
    size = 0;
};

/*
    Wrapper method for inserting a map into the BST.
    Creates the root node if the tree is empty; otherwise, calls the private recursive insert.
*/
void MapsBST::insert(MapAsHex* valuePtr) {
    if (size == 0) {     
        root = new MapBSTNode;
        root->left = nullptr;
        root->right = nullptr;
        root -> parent = nullptr;
        root->mahPtr = valuePtr;
        size++;
    }
    else {
        insert(root, valuePtr);
    }  
};

/*
    Wrapper method for searching the BST for maps with numberOfInternalWalls == key.
    Returns a vector of matching MapAsHex* pointers (empty if not found).
*/
vector<MapAsHex*> MapsBST::search(const int key) const{
    vector<MapAsHex*> matchList;
    search(root, key, matchList);
    return matchList;
};

/*
    Returns the number of nodes (maps) currently stored in the BST.
*/
int MapsBST::getSize() const {
    return size;
};

/*
    Wrapper method for printing all maps stored in the BST.
    Uses in-order traversal to print maps in ascending order by internal wall count.
    If the tree is empty, prints "Empty tree".
*/
void MapsBST::print(ostream& os) const {
    if (size == 0) {
        os << "Empty tree" << endl;
    }
    else {
        print(root, os);
    }
};

/*
    Wrapper method that returns a vector of all map pointers ranked from smallest to largest
    by number of internal walls using in-order traversal.
*/
vector<MapAsHex*> MapsBST::rank() const{
    vector<MapAsHex*> rankedList;
    rank(root, rankedList);
    return rankedList;
};

/*
    Destructor for MapsBST.
    Uses post-order traversal to deallocate all BST nodes.
    Note: The MapAsHex* objects are NOT deleted—only the tree structure is cleaned up.
*/
MapsBST::~MapsBST(){
    destroy(root);
    root = nullptr;
    size = 0;
};
