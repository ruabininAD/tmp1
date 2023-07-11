#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <bitset>
#include <ctime>
using namespace std


struct Node
{
    char ch;
    int freq;
    Node* left, * right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

Node* buildHuffmanTree(string text)
{
    if (text == "") { return NULL; }


    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;

    for (auto pair : freq) { pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); }

    while (pq.size() != 1)
    {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }


    Node* root = pq.top();
    return root;
}





class Coder
{
    Node* root = NULL;
public:
	std::pair<string, Node*> Huffman(bool action, string text);
};


pair<string, Node*> Coder::Huffman(bool action, string text )
{
    
	string res;
	if (action == 0) {
        
        float cod_price = 0;
		
	    root = buildHuffmanTree(text);
       
        unordered_map<char, string> huffmanCode;
        encode(root, "", huffmanCode);

        cout <<"\t" << "���� ����: ";
        for (auto pair : huffmanCode) {
            cout << pair.first << "-" << pair.second << " ";
            //������� ���� �����������
            float count_char = count(text.begin(), text.end(), pair.first);
            float p_char = count_char / text.length();
            cod_price += p_char * pair.second.length();
        }
        cout << endl;



        // �������� �������������� ������
        string str;
        for (char ch : text) {   str += huffmanCode[ch];   }

        cout << "\t" << "��� ������: " << text.size() << " ����" << endl;
        cout << "\t" << "��� �������������� ������: " << str.size()/8 << " ����" << endl;
        cout << "\t" << "K���������� ������ : " << float(text.size()) / (str.size() / 8 ) << endl;


        cout << "\t" << "���� ����������� : " << cod_price << endl;
        return make_pair(str, root);
        
	}
	else if (action == 1) {
        if (root == NULL) {
            cout << "����� �� ����������� ";
            return make_pair(" ", nullptr);
        }
		

        if (isLeaf(root)) { while (root->freq--) {  cout << root->ch;  }        }
        else {
            int index = -1;
            while (index < (int)text.size() - 1) {
                 decode(root, index, text, res);
                
            }
        }
        cout << endl;
	}
	return make_pair( res, root);
}
