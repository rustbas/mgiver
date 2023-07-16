#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include <sys/stat.h>
#include <filesystem>

#include "huffmanCoderV2.hpp"
#include "Coding.hpp" 

// #define READ_SUFFIX ".reads"
// #define QUAL_SUFFIX ".qual"
// #define HEAD_SUFFIX ".head"

// #define PREFIX "mgiver."

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

  string READ_SUFFIX = ".reads";
  string QUAL_SUFFIX = ".qual";
  string HEAD_SUFFIX = ".head";

  string PREFIX = "mgiver";


  auto start = chrono::high_resolution_clock::now();
  
  vector<string> headers;
  vector<string> reads;
  vector<string> quality;
  
  string FILENAME;
  string DIRNAME;

  bool verbose = false;
  bool code; // true -- encode; false -- decode
  
  // Parsing arguments
  for (int i=1; i < argc; ++i) {
    if ((string) argv[i] == "-v") {
      verbose = true;
    } else if ((string) argv[i] == "-i") {
      FILENAME = argv[++i];
    } else if ((string) argv[i] == "-o") {
      DIRNAME = argv[++i];
    } else if ((string) argv[i] == "-e") {
      code = true;
    } else if ((string) argv[i] == "-d") {
      code = false;
    } else {
      cout << argv[i] << endl;
      exit(1);
    }
  }

  
  assert(("Must define option and file", argc > 2));
  
  if (code) {
    readFASTQ(FILENAME, &headers, &reads, &quality);

    if (verbose) {
      cerr << "Encoding file..." << endl;
    }

    // struct stat sb;
    // assert(("Folder already exists!", stat(DIRNAME, &sb)) != 0);

    filesystem::create_directory(DIRNAME);
    
    HuffmanCodes(createHashmap(reads));
    encode(DIRNAME, PREFIX+READ_SUFFIX, reads, huffmanCode);
    huffmanCode.clear();
    
    HuffmanCodes(createHashmap(quality));    
    encode(DIRNAME, PREFIX+QUAL_SUFFIX, quality, huffmanCode);
    huffmanCode.clear();
   
    HuffmanCodes(createHashmap(headers));
    encode(DIRNAME, PREFIX+HEAD_SUFFIX, headers, huffmanCode);
    // huffmanCode.clear();
    
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    if (verbose) {
      cerr << "Compression time: " << duration.count() << " seconds" << endl;
    }

    long prev_file = GetFileSize(FILENAME);
    long new_files = GetFileSize(DIRNAME + "/" + PREFIX+HEAD_SUFFIX) +
      GetFileSize(DIRNAME + "/" + PREFIX+READ_SUFFIX) +
      GetFileSize(DIRNAME + "/" + PREFIX+QUAL_SUFFIX);

    if (verbose) {
      cerr << "Compression ratio: " << (float) prev_file / (float) new_files << endl;
    }
    
  } else {

    if (verbose) {
      cerr << "Decoding file" << endl;
    }      
    // auto res = decode(FILENAME+SUFFIX);
    
    auto reads = decode(FILENAME, PREFIX+READ_SUFFIX);
    auto quality = decode(FILENAME, PREFIX+QUAL_SUFFIX);
    auto headers = decode(FILENAME, PREFIX+HEAD_SUFFIX);
    


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
    if (verbose) {
      cerr << "Decompression time: " << duration.count() << " seconds" << endl;
    }
  }

  
  return 0;
}
