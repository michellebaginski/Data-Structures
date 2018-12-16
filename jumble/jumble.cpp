#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string.h>

/*
*  this function rearranges the characters in a string
*    so that they are sorted (according to their ASCII
*    value).
*/
void ssort(std::string &s) {
  /*
     strings are "iterable" objects and so have the begin()
     and end() functions.  These functions (in a pretty
     abstract way) return "iterators" which specify the
     "beginning" and "end" of the associated object).

     Thus, this call is asking the sort function to sort
     the entire string s.
  */
  std::sort(s.begin(), s.end()); 
}


int main(int argc, char *argv[]){
    std::unordered_map<std::string, std::vector<std::string> > word_map;
    std::ifstream file;
    std::string word, max, key;
    int size, maxsize, num_words = 0;
    
    if(argc != 2) {
        std::cout << "usage:  ./freq <filename>\n";
        std::cout << "goodbye\n";
        return 1;
  }

    /*
     *  argv[1] is a C-string which is the filname specified
     *    by the user.  Let's try to open it.
     */
    file.open(argv[1], std::ios::in);

    if (!file.is_open()) {
        std::cout << "Error: could not open file '" << argv[1] << "'\n";
        std::cout << "goodbye\n";
    return 1;
  }

    std::cout << "reading input file...\n";

    while(!file.eof()) {
        ++num_words;
        file >> word;
        key = word;
        ssort(key);     // sort alphabetically by ascii value - serves as the key
        word_map[key].push_back(word);  // map the word to the anagram vector for the specified key
        size = word_map[key].size();    // save the vector size
        // update the max size if it is the greatest in the entire map
        if (size > maxsize) {
            maxsize = size;
            max = key;
        }
  }
    
    std::cout << "enter a word and I will tell you what I know about it\n";
    std::cout << "  when you are done, type ctrl-d (ctrl-z on windows)\n\n";
    std::cout << "> ";

    while(std::cin >> word) {
        key = word;
        ssort(key);
        // check to see if the key exists
        std::unordered_map<std::string, std::vector<std::string> >::const_iterator search = word_map.find(key);
        // if it doesn't exist, word doesn't exist
        if (search == word_map.end())
            std::cout << "the word cannot be found\n";
        // print out all existing anagrams
        else {
            size = word_map[key].size();
            std::cout << "English anagrams found: " << size << "\n";
            for (int i = 0; i < word_map[key].size(); i++)
                std::cout << word_map[key].at(i) << "\n";
        }
        std::cout << "\n";
        std::cout << "> ";
    }
    // user has quit.  Let's dump the map contents

    // display report
    std::cout << "> REPORT: \n\n";
    printf("  num_words           %10d\n", num_words);
    printf("  num_classes         %10lu\n", word_map.size());
    printf("  size-of-largest-class: %3d\n", maxsize);
    std::cout <<
           "  largest-class-key:      '"  << max << "'\n";
    printf("  members-of-largest-class: \n\n");
    
    ssort(max);
    // display all the anagrams in the largest equivalence class
    for (int i = 0; i < maxsize; i++) {
        std::cout<< "    '" << word_map[max].at(i) << "'\n";
    }
    
    return 0;
}
