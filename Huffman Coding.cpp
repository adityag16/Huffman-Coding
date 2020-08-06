
///////////////////////////////////////////////////
//        Please compile using C++11 Flag        //
///////////////////////////////////////////////////
/*
	First name	Aditya
	Last name	Gupta	
*/

//IMPORTANT: before submitting your source code, please make sure to comment your main function (needed for automated testing)


#include <iostream>
#include <string>
#include <map>
#include <vector> 

struct hufftreenode {
	char character;
	int frequency;
	hufftreenode* left;
	hufftreenode* right;
};


typedef hufftreenode* hufftreeptr;


/////////////////////////////////////////
// Functions declarations (prototypes) //
/////////////////////////////////////////



//utility function
bool valid_hufftree(const hufftreeptr hufftree);
// returns true if the input hufftree is a valid Huffman tree
// i.e. all the terminal nodes (leaves) have characters,
// all the non-leaf nodes have two sub-trees each,
// and the occurence frequency of a non-leaf node equals
// the sum of the occurence frequencies of its two sub-trees.



std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable);
// encodes an input message (a string of characters) into an encoded message (string of bits) using the Huffman coding
// builds the Huffman tree and its associated encoding table (i.e. the association between the characters in the tree leaves and their encodings (string of bits))

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree);
// decodes an encoded message (a string of bits) into the original message (a string of characters) using the Huffman tree built during the encoding

void unique_char(std::string message, std::vector<char>& all_char);
// checks the string to store all unique characters in a string and stroes them

bool found_in_vect(char letter, std::vector<char> v);
// checks if an element is already part of a vector 

int frequency_calc(char letter, std::string message); 
// calculates the frequency of a given char

void tree_index_to_combine(int& position1, int& position2, std::vector<hufftreeptr> forest);
// calculate which nodes have the lowest frequency and hence which to combine to make a new tree

void make_hufftable(hufftreeptr hufftree, std::map<char, std::string>& hufftable, std::string path);
// makes the table with individual char encodings

std::string find_path(char symbol, std::map<char, std::string>& hufftable);
//finds the encoding for each char from the hufftable


///////////////////
// main function //
///////////////////


/*int main() {

	// YOUR CODE HERE FOR TESTING YOUR PROGRAM

	// an example of basic encoding/decoding
	std::string message, encodedmessage, decodedmessage;
	hufftreeptr hufftree;
	std::map<char, int> freqtable;
	std::map<char, std::string> hufftable;
	message = "fgh";
        
	// 1) encoding (compression)
	encodedmessage = huffencode(message, freqtable, hufftree, hufftable);
	// freqtable should be as in Table 1.
	// hufftree might be as in Figure 2 (remember, the Huffman coding tree IS NOT UNIQUE. If we swap two siblings in a Huffman tree, it is still a Huffman tree of the same message.)
	// hufftable should correspond to hufftree, and might be as in Table 2 <' ',"100">, <'g',"00">, <'o',"01">, <'p',"1110">, <'h',"1101">, <'e',"101">, <'r',"1111">, <'s',"1100">.
	// encodedmessage might then be the 37-bits string "0001100000110000011110110110111111100" (i.e. "00.01.100.00.01.100.00.01.1110.1101.101.1111.1100")

	if(valid_hufftree(hufftree))  {
		std::cout << "valid Huffman tree." << std::endl;
	}
	else {
		std::cout << "not valid Huffman tree." << std::endl;
	}

	// 2) decoding (uncompression)
	decodedmessage = huffdecode(encodedmessage, hufftree);
	// should be "go go gophers"
	
	if(decodedmessage == message) {
		std::cout << "decoding OK." << std::endl;
	}
	else {
		std::cout << "decoding not OK." << std::endl;
	}

    
	return 0;
}*/





/////////////////////////////////////////////
// Functions definitions (implementations) //
/////////////////////////////////////////////

// YOUR CODE HERE FOR THE FUNCTIONS IMPLEMENTATIONS

bool found_in_vect(char letter, std::vector<char> v){
    
    for(int i=0; i<v.size(); i++){
        if(v[i] == letter){
            return true;
        }
    }
    
    return false;
}        
        
        
void unique_char(std::string message, std::vector<char>& all_char){
    
    for(int i=0; i<message.size(); i++){
        if(!found_in_vect(message[i],all_char)){
            all_char.push_back(message[i]);
        }
    }
    
    
}

int frequency_calc(char letter, std::string message){
    int frequency = 0;
    
    for(int i = 0; i<message.size(); i++){
        if(message[i] == letter){
            frequency++;
        }
        
    }
    
    return frequency; 
}

void tree_index_to_combine(int& position1, int& position2, std::vector<hufftreeptr> forest){
    
    int min_frequency = forest[0] -> frequency; 
    
    for(int i = 1; i<forest.size(); i++){
        if(forest[i] -> frequency < min_frequency){
            min_frequency = forest[i] -> frequency; 
        }
    }
    
    for(int i =0; i<forest.size(); i++){
        if(forest[i] -> frequency == min_frequency){
            position1 =i;
            break;
        }
    }
    
    if(position1 == 0){
        min_frequency = forest[1] -> frequency;
    }
    else{
        min_frequency = forest[0] -> frequency;
    }
    for(int i = 1; i<forest.size(); i++){
        if(i != position1){
            if(forest[i] -> frequency < min_frequency){
                min_frequency = forest[i] -> frequency; 
            }
        }
    }
    
    for(int i =0; i<forest.size(); i++){
        if(i !=position1){
            if(forest[i] -> frequency == min_frequency){
                position2 =i;
                break;
            }
        }    
    }
}

void make_hufftable(hufftreeptr hufftree, std::map<char, std::string>& hufftable, std::string path){

    if(hufftree -> character != '\0'){
        hufftable.insert(std::pair<char, std::string>(hufftree -> character, path));
    }
    else{
        make_hufftable(hufftree -> left, hufftable, path + '0');
        make_hufftable(hufftree -> right, hufftable, path + '1');
    }
}

std::string find_path(char symbol, std::map<char, std::string>& hufftable){
    std::map<char, std::string>::iterator i;

    for(i = hufftable.begin(); i != hufftable.end(); i++){
        if(i -> first == symbol){
            return i -> second;
        }
    }
}

std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable){
    
    std::vector<char> all_char;
    
    std::string encoded_message = "";
    
    unique_char(message, all_char);
    
    for(int i=0; i<all_char.size(); i++){
        
        int freq = frequency_calc(all_char[i], message);
        freqtable.insert(std::pair<char, int>(all_char[i], freq));
        
    }
    
    std::map<char, int>::iterator it;
    std::vector<hufftreeptr> forest; 
    
    for(it = freqtable.begin(); it != freqtable.end(); it++){
        hufftreeptr letter = new hufftreenode;
        letter -> character = it-> first;
        letter -> frequency = it-> second; 
        letter -> left = NULL;
        letter -> right = NULL; 
        
        forest.push_back(letter);
    
    }

    if(forest.size() >1 ){
        int position1 =0,position2=0;
        while(forest.size() !=1 ){

            tree_index_to_combine(position1, position2, forest);
            
            hufftreeptr node = new hufftreenode; 
            node -> character = '\0';
            node -> frequency = (forest[position1] -> frequency) + (forest[position2] -> frequency);
            node -> left = forest[position1];
            node -> right = forest[position2];
            
            std::vector<hufftreeptr>forest_copy;
            
            for(int i= 0; i<forest.size(); i++){
                if(i!=position1 && i!=position2){
                    forest_copy.push_back(forest[i]);
                }
            }
            
            forest = forest_copy;
            
            forest.push_back(node);
        }
    
        hufftree = forest[0];

        std::string path; 
        make_hufftable(hufftree, hufftable, path);

    
        for(int i=0; i<message.size(); i++){
            std::string bit_path = find_path(message[i], hufftable);
            encoded_message += bit_path;
        }
    }

    else{
        hufftree = forest[0];
    }
    

    return encoded_message;
}

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree){
    hufftreeptr tree = hufftree;
    std::string decoded_message;

    if(encodedmessage.size() == 0){
        for(int i=0 ; i<tree -> frequency; i++){
            decoded_message += (tree -> character);
        }
    }
    else{
        for(int i = 0; i<=encodedmessage.size(); i++){
            if(tree -> character == '\0'){
                if(encodedmessage[i] == '0'){
                    tree = tree -> left;
                }
                else if(encodedmessage[i] == '1'){
                    tree = tree -> right; 
                }
            }
            else{
                decoded_message += (tree -> character);
                i--;
                tree = hufftree;
            }
        }
    }

    return decoded_message;
}


bool valid_hufftree(const hufftreeptr hufftree){
    if(hufftree -> character == '\0'){
        if(hufftree->left == NULL || hufftree -> right == NULL || hufftree -> frequency != (hufftree -> left -> frequency) + (hufftree -> right -> frequency)){
            return false;
             
        }
        else{
            return true && valid_hufftree(hufftree -> left) && valid_hufftree(hufftree -> right);
        }
    }
    else if(hufftree -> character != '\0' && hufftree -> left == NULL && hufftree -> right == NULL){
        return true;
    }
}
    