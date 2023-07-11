#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <bitset>
#include <ctime>


#include "coder.h"
#include "generator.h"

std::vector<int> divideNumber(int a, int b) {
    std::vector<int> result;
    int quotient = a / b;
    int remainder = a % b;

    for (int i = 0; i < b; i++) {
        int chunkSize = quotient + (i < remainder ? 1 : 0);
        result.push_back(chunkSize);
    }

    return result;
}

std::pair<std::string, std::map<char, int>> processVectors(const std::vector<std::pair<std::string, std::map<char, int>>>& input, const std::vector<char>& keys) {
    std::string concatenatedString;
    std::map<char, int> resultMap;

    for (const auto& pair : input) {
        concatenatedString += pair.first;

        for (const auto& key : keys) {
            resultMap[key] += pair.second[key];
        }
    }

    return { concatenatedString, resultMap };
}

std::vector<char> stringToVector(const std::string& str) {
    std::vector<char> result(str.begin(), str.end());
    return result;
}

std::vector<std::string> divideString(const std::string& a, int b) {
    std::vector<std::string> result;
    int length = a.length();
    int chunkSize = length / b;
    int extraChars = length % b;

    int startIndex = 0;
    for (int i = 0; i < b; i++) {
        int chunkLength = chunkSize + (extraChars > 0 ? 1 : 0);
        std::string chunk = a.substr(startIndex, chunkLength);
        result.push_back(chunk);
        startIndex += chunkLength;
        extraChars--;
    }

    return result;
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> substrings;
    std::stringstream ss(str);
    std::string substring;

    while (std::getline(ss, substring, delimiter)) {
        substrings.push_back(substring);
    }

    return substrings;
}

void createNodeInfoType(MPI_Datatype* mpiNodeInfoType) {
    MPI_Datatype types[2] = { MPI_CHAR, MPI_UNSIGNED_LONG_LONG };
    int blocklengths[2] = { 1, 1 };
    MPI_Aint offsets[2];
    offsets[0] = offsetof(NodeInfo, str);
    offsets[1] = offsetof(NodeInfo, node);
    MPI_Type_create_struct(2, blocklengths, offsets, types, mpiNodeInfoType);
    MPI_Type_commit(mpiNodeInfoType);
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc,&argv);
	

	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Datatype mpiNodeInfoType;
    createNodeInfoType(&mpiNodeInfoType);

	
	std::string alphabet = "abcd";
    int len_text = 1000;


    // 
	if(rank == 0){
		vector<int> len_texts = divideNumber(len_text, size-1); //fixme mb rank -1 tk 0 - root
//raspregelaem dlinnu generiruemogo texta
		for(int i =1;i<size;i++){
			MPI_Send(&len_texts[i-1],sizeof(int),MPI_INT,i,0,MPI_COMM_WORLD);
			std::cout<<"[LOG DATA] Root send data to " << i << "\n";
		}

	}
	else{
        //generiruem text
		MPI_Status status;
		MPI_Probe(0,0,MPI_COMM_WORLD,&status);

		int len_text;
		
	
		MPI_Recv(len_text,sizeof(int),MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		std::cout<<"[LOG DATA] Process " << rank << "recieve data from root\n";

        // i otpravlaem
        a = generator(alphobet , len_text)
        pair <string, map<char, int>> result (a.get_string(), a.get_map())
        MPI_Send(&result, sizeof(result),MPI_UNSIGNED_CHAR,0,0,MPI_COMM_WORLD);
	}


    if(rank == 0){
        //lovim texts i skleivaem ih
        std::vector<pair <string, map<char, int>> >vectorPair ;
        for(int i = 1;i<size;i++){
			std::pair <string, map<char, int> >now_pair;
			
			MPI_Recv(&now_pair, sizeof(now_pair),MPI_UNSIGNED_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			vectorPair.push_back(now_pair);
        }
        pair<std::string, std::map<char, int>> my_pair_haff = processVectors(vectorPair,stringToVector(alphobet) )

        //stroim derevo  haffmana
        Node* root = buildHuffmanTree(text);

        
        // otpravlaem chasti texts i root
        vector<std::string> strs = divideString(my_pair_haff.first, size-1)
        for(int i =1;i<size;i++){
            auto p1 = std::make_pair(strs[i-1], root);
			MPI_Send( &p1, p1.size() * sizeof(char),mpiNodeInfoType,i,0,MPI_COMM_WORLD);
		}
    } else {

        
        //lovim  chasti texts i root
		MPI_Status status;
		MPI_Probe(0,0,MPI_COMM_WORLD,&status);

		int len_text;
		pair <string, Node*> pa;
	
		MPI_Recv(pa,pa.size() * sizeof(char),mpiNodeInfoType,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		
        //obrabativaem
        Coder a;

        // otsilaem zakodirovaniy text
        code_huffman = a.Huffman(0, pa.first, ps.second);
        MPI_Send(code_huffman.data(), code_huffman.size(), ,MPI_CHAR,0,0,MPI_COMM_WORLD);
    }


     if(rank == 0){//prinimaem cod i ckleivaem
         std::string code_huffman  = "";
        for(int i = 1;i<size;i++){
			std::string now_s = "";
		
			MPI_Recv(now_s.data(), now_s.size(),MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            //sohranaem
			code_huffman += now_s+"*" ;
        }
        
        //delim cod i otpravlaem c root
        vector<std::string> cods  =  splitString(code_huffman, "*");

          
        vector<std::string> strs = divideString(my_pair_haff.first, size-1)
        for(int i =1;i<size;i++){
            auto p1 = std::make_pair(cods[i-1], root);
			MPI_Send( p1, p1.size(),mpiNodeInfoType,i,0,MPI_COMM_WORLD);
		}
    } else {//lovim  cod i root//decoding// otsilaem zakodirovaniy text

        
		MPI_Status status;
		MPI_Probe(0,0,MPI_COMM_WORLD,&status);

		int len_text;
		pair <string, Node*> pa;
	
		MPI_Recv(pa,pa.size(),mpiNodeInfoType,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		
        //decoding
        Coder a;

        
        text = a.Huffman(1, pa.first, ps.second);

        // otsilaem zakodirovaniy text
        MPI_Send(text.data(), text.size() * sizeof(char), MPI_CHAR,0,0,MPI_COMM_WORLD);


        //otpravlaem
    }

    if(rank == 0){//soedinaem v root
        //lovim 
        //sklenvaem

        std::string all_text  = "";
        for(int i = 1;i<size;i++){
			std::string now_s = "";
		
			MPI_Recv(now_s.data(),now_s.size() * sizeof(char),MPI_CHAR,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            //sohranaem
			all_text += now_s ;
        }

        //konchaem
        if (all_text == a.get_string()) {
            cout << "yep";
        }
    }

	
		
	MPI_Finalize();
	return 0;

	
}
