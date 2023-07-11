#include <queue>
#include <map>

using namespace std;
 
// Maximum Height of Huffman Tree.
#define MAX_SIZE 1000
 
class HuffmanTreeNode {
public:
  // Stores character
  char data;
 
  // Stores frequency of
  // the character
  int freq;
 
  // Left child of the
  // current node
  HuffmanTreeNode* left;
 
  // Right child of the
  // current node
  HuffmanTreeNode* right;
 
  // Initializing the
  // current node
  HuffmanTreeNode(char character,
		  int frequency)
  {
    data = character;
    freq = frequency;
    left = right = NULL;
  }
};
 
// Custom comparator class
class Compare {
public:
  bool operator()(HuffmanTreeNode* a,
		  HuffmanTreeNode* b)
  {
    // Defining priority on
    // the basis of frequency
    return a->freq > b->freq;
  }
};
 
// Function to generate Huffman
// Encoding Tree
HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*,
                              vector<HuffmanTreeNode*>,
			      Compare> pq)
{
 
  // We keep on looping till
  // only one node remains in
  // the Priority Queue
  while (pq.size() != 1) {
 
    // Node which has least
    // frequency
    HuffmanTreeNode* left = pq.top();
 
    // Remove node from
    // Priority Queue
    pq.pop();
 
    // Node which has least
    // frequency
    HuffmanTreeNode* right = pq.top();
 
    // Remove node from
    // Priority Queue
    pq.pop();
 
    // A new node is formed
    // with frequency left->freq
    // + right->freq
 
    // We take data as '$'
    // because we are only
    // concerned with the
    // frequency
    HuffmanTreeNode* node = new HuffmanTreeNode('$',
						left->freq + right->freq);
    node->left = left;
    node->right = right;
 
    // Push back node
    // created to the
    // Priority Queue
    pq.push(node);
  }
 
  return pq.top();
}
 
// Function to print the
// huffman code for each
// character.
 
// It uses arr to store the codes

map<char, string> huffmanCode;

void printCodes(HuffmanTreeNode* root,
                int arr[], int top)
{
  // Assign 0 to the left node
  // and recur
  if (root->left) {
    arr[top] = 0;
    printCodes(root->left,
	       arr, top + 1);
  }
 
  // Assign 1 to the right
  // node and recur
  if (root->right) {
    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }
 
  // If this is a leaf node,
  // then we print root->data
 
  // We also print the code
  // for this character from arr
  if (!root->left && !root->right) {
    char ch = root->data;
    string res;
        for (int i = 0; i < top; i++) {
          res += to_string(arr[i]);
    }
    huffmanCode[ch] = res;
      }
}
 
void HuffmanCodes(map<char, int> hashmap)
{
 
  // Declaring priority queue
  // using custom comparator
  priority_queue<HuffmanTreeNode*,
		 vector<HuffmanTreeNode*>,
		 Compare>
    pq;
 
  // Populating the priority
  // queue
  for (auto it: hashmap) {
    HuffmanTreeNode* newNode
      = new HuffmanTreeNode(it.first, it.second);
    pq.push(newNode);
  }
 
  // Generate Huffman Encoding
  // Tree and get the root node
  HuffmanTreeNode* root = generateTree(pq);
 
  // Print Huffman Codes
  int arr[MAX_SIZE], top = 0;
  printCodes(root, arr, top);
}

map<char, int> createHashmap(vector<string> lst){

  string res = "";
  map<char, int> hashmap;
  
  for (auto s: lst){
    for (char ch: s) {
      hashmap[ch]++;
    };
  }
  hashmap['\n'] = lst.size() - 1;

  return hashmap;
};
