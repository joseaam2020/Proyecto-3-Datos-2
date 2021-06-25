#include "Huffman.h"
void Huffman::printCodes(struct MinHeapNode* root, string str){
    if (!root)
        return;
    if (root->data != '$')
        //cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void Huffman::storeCodes(struct MinHeapNode* root, string str)
{
    if (root==NULL){
        return;
    }
    if (root->data != '$'){
        codes[root->data]=str;
    }
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

void Huffman::HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void Huffman::calcFreq(string str, int n)
{
    for (int i=0; i<str.size(); i++)
        freq[str[i]]++;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string Huffman::decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans+'\0';
}

string Huffman::decodeHuffman(string s, vector<string> symbol, vector<string> code_num){
    string delimiter = "|";
    size_t pos1 = 0;
    string token1;
    int j = 0;
    string decoded = "";

    while ((pos1 = s.find(delimiter)) != std::string::npos) {
        token1 = s.substr(0, pos1);

        // loop through the array elements
        for (size_t i = 0; i < code_num.size(); i++) {
            if (token1 == code_num[i]){
                decoded += symbol[i];
                break;
            }
        }
        //std::cout << token << std::endl;
        s.erase(0, pos1 + delimiter.length());
    }
    return decoded;
}

string Huffman::prepare_dictionary(){
    string map_str;
    //cout << "Character With there Frequencies:\n";
    for (auto v=codes.begin(); v!=codes.end(); v++){
        cout << v->first <<' ' << v->second << endl;
        map_str += "|";
        map_str += v->first;
        map_str += "&";
        map_str += v->second;
        map_str += "&";
    };
    map_str += "|";
    return map_str;
}

string Huffman::compressed_message(string str){
    string encodedString;
    for (auto i: str){
        encodedString+=codes[i];
        encodedString+= "|";
    }
    return encodedString;
}

string Huffman::start_huffman(string str){
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    string map_str = prepare_dictionary();
    return map_str;
}

string Huffman::decompress(string map_str, string encodedString){
    std::string delimiter = "|";
    std::vector<std::string> symbol;
    std::vector<std::string> code_num;
    size_t pos1 = 0;
    size_t pos2 = 0;
    std::string token1;
    std::string token2;
    bool first = true;
    int moment = 0;

    while ((pos1 = map_str.find(delimiter)) != std::string::npos) {
        token1 = map_str.substr(0, pos1);
        if (first == true){
            first = false;
        }
        else{
            while ((pos2 = token1.find("&")) != std::string::npos) {
                token2 = token1.substr(0, pos2);
                if(moment == 0){
                    symbol.push_back(token2);
                    moment += 1;
                }else{
                    code_num.push_back(token2);
                }
                token1.erase(0, pos2 + 1);
            }
            moment = 0;
        }
        //std::cout << token << std::endl;
        map_str.erase(0, pos1 + delimiter.length());
    }
    //cout << "bout to shoot symbols" << endl;
    for (const auto &value: symbol) {
        //std::cout << value << ' ';
    }
    //cout << "\nbout to shoot code_nums" << endl;
    for (const auto &value: code_num) {
        //std::cout << value << ' ';
    }

    string decodedString = decodeHuffman(encodedString, symbol, code_num);
    return decodedString;
}