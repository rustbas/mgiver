#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <sys/stat.h>

#include "huffmanCoderV2.hpp"
#include "Coding.hpp" 

#define READ_SUFFIX ".reads"
#define QUAL_SUFFIX ".qual"
#define HEAD_SUFFIX ".head"

#define PREFIX "mgiver."

long GetFileSize(string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void readFASTQ(string file_name,
	       vector<string> *headers,
	       vector<string> *reads,
	       vector<string> *quality){

  fstream file(file_name);
  string line;
  
  int count = 0;

  while(getline(file, line)){
    switch(count++ % 4) {
    case 0:
      (*headers).push_back(line);
      break;
    case 1:
      (*reads).push_back(line);
      break;
    case 3:
      (*quality).push_back(line);
      break;
    }
  }
}

int main(int argc, char *argv[]) {

  auto start = chrono::high_resolution_clock::now();
  
  vector<string> headers;
  vector<string> reads;
  vector<string> quality;

  // const string FILENAME = "mgi_R967_3M.part_001.temp.fq";
  string FILENAME = string(argv[2]);
  

  
  // huffman test;
  // test.createMap(&reads);

  // for (auto item: test.hashmap){
  //   if (item.first != '\n') {
  //     cout << item.first << ":" << item.second << endl;
  //   } else {
  //     cout << "\\n" << ":" << item.second << endl;
  //   };
  // };

  // cout << test.hashmap.size() << endl;
  


  assert(("Must define option and file", argc > 2));
  
  if (string(argv[1]) == "-e") {
    readFASTQ(FILENAME, &headers, &reads, &quality);
    cout << "Encoding file..." << endl;
    
    HuffmanCodes(createHashmap(reads));
    encode(PREFIX+FILENAME+READ_SUFFIX, reads, huffmanCode);

    huffmanCode.clear();
    
    HuffmanCodes(createHashmap(quality));    
    encode(PREFIX+FILENAME+QUAL_SUFFIX, quality, huffmanCode);

    huffmanCode.clear();
   
    HuffmanCodes(createHashmap(headers));
    encode(PREFIX+FILENAME+HEAD_SUFFIX, headers, huffmanCode);
    
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cerr << "Compression time: " << duration.count() << " seconds" << endl;

    long prev_file = GetFileSize(FILENAME);
    long new_files = GetFileSize(PREFIX+FILENAME+HEAD_SUFFIX) +
      GetFileSize(PREFIX+FILENAME+READ_SUFFIX) +
      GetFileSize(PREFIX+FILENAME+QUAL_SUFFIX);
    cerr << "Compression ratio: " << (float) prev_file / (float) new_files << endl;
    
  } else if (string(argv[1]) == "-d") {
    cerr << "Decoding file" << endl;
    // auto res = decode(FILENAME+SUFFIX);
    
    auto reads = decode(PREFIX+FILENAME+READ_SUFFIX);
    auto quality = decode(PREFIX+FILENAME+QUAL_SUFFIX);
    auto headers = decode(PREFIX+FILENAME+HEAD_SUFFIX);
    


    // cout << reads.size() << endl;
    // cout << headers.size() << endl;
    // cout << quality.size() << endl;
    for (int i = 0; i < reads.size(); i++) {
      cout << headers[i] << endl;
      cout << reads[i] << endl;
      cout << "+" << endl;
      cout << quality[i] << endl;
    }

    auto stop = chrono::high_resolution_clock::now();
    
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cerr << "Decompression time: " << duration.count() << " seconds" << endl;
  }

  
  return 0;
}
