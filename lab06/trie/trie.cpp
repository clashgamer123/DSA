#include "trie.h"
#include <iostream>

Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* node = new TrieNode ;
	return node ;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	if (!root) { root = getNode() ; }
	int len  = key.size() ;
	int i = 0;
	while(i<len)
	{
		root = root->children[CHAR_TO_INDEX(key[i])] ;
		if (root==nullptr)
		{
			root = getNode() ;
		}
		i++;
	}
	root->isWordEnd = true ;
	return ;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	int len = key.size() ;
	int i = 0;
	while(i<len)
	{
		root = root->children[CHAR_TO_INDEX(key[i])] ;
		if (root==nullptr)
		{
			break ;
		}
		i++;
	}
	if (i == len && root->isWordEnd)
	{
		return true ;
	}
	return false;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for (int i = 0; i<ALPHABET_SIZE; i++)
	{
		if (root->children[i] != nullptr)
		{
			return false ;
		}
	}
	return true;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	int len = currPrefix.size() ;
	int i = 0 ;
	while (i<len)
	{
		if (root->children[CHAR_TO_INDEX(currPrefix[i])] == nullptr)
		{
			return ;
		}
		root = root->children[CHAR_TO_INDEX(currPrefix[i])] ;
		i++;
	}
	if (root->isWordEnd)
	{
		std :: cout<<(currPrefix) ;
	}
	for (int i = 0; i<ALPHABET_SIZE; i++)
	{
		if (!root->children[i])
		{
			char e = int('a') + i ;
			suggestionsRec(root->children[i], (currPrefix+e)) ;
		}
	}
	return ;
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	return 0;
}
