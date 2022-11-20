// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    std::string& in,
    std::vector<int>& floatingVec,
    const std::set<std::string>& dict,
    unsigned index, char c, std::set<std::string>& words);

void floatingStringToVec(const std::string& floating, unsigned index, std::vector<int>& floatingVec);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //in is empty, in which it is not a word
    //in is a word in dict
    //when recursing, if floating is used as a letter check,
    //shorten it when recursing
    //if in has less empty spaces than floating has characters, then 
    //something has messed up

    //index 0-25 represent alphabetical characters, index 26 represents
    // how many elements are currently in the Vector (to avoid loops)
    std::vector<int> floatingVec(27);
    floatingStringToVec(floating, 0, floatingVec);
    string inCopy = in;
    std::set<std::string> words;

    wordleHelper(inCopy, floatingVec, dict, 0, 'a', words);

    return words;
}

// Define any helper functions here
void wordleHelper(
    std::string& in,
    std::vector<int>& floatingVec,
    const std::set<std::string>& dict,
    unsigned index, char c, std::set<std::string>& words)
{ 
    //base case
    if(index >= in.length()) {
        if(floatingVec[26] == 0) {
            if(dict.count(in) != 0) words.insert(in);
        }
        return;
    } 

    //checks to see if the number of floating characters remaining
    //is greater than the rest of the string
    if(floatingVec[26] > (int)(in.size() - index)) return;

    //if the current character is not a dash, we continue
    if(in[index] != '-') {
        wordleHelper(in, floatingVec, dict, index+1, 'a', words);
        return;
    }

    //if the current character is a word in floating, we update
    //the floatingVector accordingly by decrementing the corresponding character
    //and the total element number
    bool changed = false;
    if(floatingVec[c - 'a'] != 0) {
        floatingVec[c - 'a'] -= 1;
        floatingVec[26] -= 1;
        changed = true;
    }

    //tests the character c, and recurses to see if there are any words 
    //that exist with character c inserted at this dash
    in[index] = c;
    wordleHelper(in, floatingVec, dict, index+1, 'a', words);
    
    //resets all changed parameters 
    in[index] = '-';
    if(changed) {
        floatingVec[c - 'a'] += 1;
        floatingVec[26] += 1;
    }

    //if char c has reached z, then we return and try new words by incrementing index
    if(c == 'z') return;
    wordleHelper(in, floatingVec, dict, index, c+1, words);
}

void floatingStringToVec(const std::string& floating, unsigned index, std::vector<int>& floatingVec) {
    if(index >= floating.length()) return;

    floatingVec[floating[index] - 'a'] += 1;
    floatingVec[26] += 1;
    floatingStringToVec(floating, index+1, floatingVec);
}
