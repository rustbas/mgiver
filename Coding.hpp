#include <fstream>
#include <filesystem>
#include <cmath>
#include <algorithm>

#define BATCH_SIZE 32


unsigned sbtoi(string str){

  long long int size = str.size();
  int result = 0;
  for (int i = size - 1; i > -1; i--) {
    // 48 -- shift to zero while char -> int
    result += (int(str[i])-48)*pow(2, size - i - 1);
    // cout << int('0')-48 << " ";
  }

  return result;
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

void encode(string prefix,
	  vector<string> arr,
	  map<char, string> dict) {

  fstream output_bin(prefix, ios_base::binary|ios_base::out);
  ofstream output_ohs(prefix + ".ohs", fstream::out);

  if(!output_bin.is_open() || !output_ohs.is_open())
    {
      cout<<"Unable to open the file\n";
      exit(1);
    }

  string str;

  for (auto line: arr){
    str = str + line + "\n";
  }

  // cout << arr[0] << endl;

  string myStr;
  
  for (char ch: str) {
    myStr += dict[ch];
  }

  // myStr = string(BATCH_SIZE - myStr.size() % BATCH_SIZE, '0') + myStr;

  output_bin.write(myStr.data(), myStr.size());
  output_ohs << myStr.size() << endl;
  
  for (auto it: dict){
    if (it.first != '\n') {
      output_ohs << it.first << " " << it.second << endl;
    } else {
      output_ohs << "\\n" << " " << it.second << endl;
    }
  }
 
  output_bin.close();
  output_ohs.close();
}

vector<string> decode(string prefix) {
  fstream input_bin(prefix, ios_base::binary|ios_base::in);
  ifstream input_ohs(prefix + ".ohs", ios::in);

  vector<string> result;
  
  if(!input_bin.is_open() || !input_ohs.is_open())
    {
      cout<<"Unable to open the file\n";
      exit(1);
    }
  
  string line;

  getline(input_ohs, line);

  long unsigned size = stoi(line);
  // cerr << prefix << " " << size << endl;
  
  map<string, char> reverseDict;
  vector<string> dictVec;
  
  while (getline(input_ohs, line)){
      // cout << line << endl;
      split(line, dictVec, ' ');
      // cout << dictVec[0] << " " << dictVec[1] << endl;
      if (dictVec[0] == "\\n") {
	reverseDict[dictVec[1]] = '\n';
      } else {
	reverseDict[dictVec[1]] = dictVec[0][0];
      }
    }
  
  string buffer;
  buffer.resize(size);

  input_bin.read(&buffer[0],  buffer.size() );
  
  string word;
  line = "";

  vector<string> alS;
  
  for (auto it: reverseDict) {
    alS.push_back(it.first);
  };

  for (char ch: buffer) {
    word += string(1, ch);

    if (find(alS.begin(), alS.end(), word) != alS.end() &&
	reverseDict[word] != '\n') {
      line += reverseDict[word];
      word = "";
    } else if (reverseDict[word] == '\n'){
      result.push_back(line);
      // cerr << line << endl;
      line = "";
      word = "";
    } else {
    }

    
  }
  
  input_bin.close();
  input_ohs.close();

  // output.read
  return result;
}