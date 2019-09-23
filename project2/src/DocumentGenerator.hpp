/**
 * CSE 100 PA2 Document Generator
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "dirent.h"
using namespace std;

class DocumentGenerator
{
public:
	unordered_map<string,vector<string> > m;
 /**
 * Builds a document generator from the documents in the given directory
 * This should open all files in the directory, read them in, tokenize them into words,
 * and build the datastructure from that stream of words.
 *
 * To tokenize a document, you are required to do the following,
 * in this order (or in a manner that is logically equivalent
 * to doing them in this order):
 * * remove all UNWANTED_CHARACTERS from the document
 * * split the document into different tokens based on whitespace
 *  (treat all whitespace breaks equally - newlines and spaces should be treated the same way. Whitespace is thrown away and not included in tokens. There should be no empty tokens.)
 * * additionally split each PUNCTUATION character into its own token
 *   (equivalently - treat all punctuation as if it was surrounded on both sides by a space)
 * * characters that are neither UNWANTED_CHARACTERS nor PUNCTUATION should be treated normally, the same way as any alphabetic character. This includes single apostrophes and accented characters.
 * * from here on, we'll use the word "word" to refer to all tokenized strings, such as "hello", "." or ","
 *
 * So, for instance, the short sentence
 * "I like the man's $10,000 trains. Sally jumped $ ov^er the moon, I think? I. I think."
 * Would be tokenized into ["I", "like", "the", "man's", "10", ",", "000", "trains", ".", "Sally",
 *   "jumped", "over", "the", "moon", ",", "I", "think", "?", "I", ".", "I" "think", "."]
 * and the frequencies of the words after "I" would be;
 *  like - 1
 *  think - 2
 *  . - 1
 *
 * A few notes:
 * 1) you must treat words with different capitalizatoins differently
 * * (so "foo" and "Foo" are different words, and the frequencies of the words that follow (or precede)
 * * "foo" will be different than the frequencies of the words that follow (or precede) "Foo" )
 * 2) pretend that the first word in each document is preceeded by a periood (That way, it is considered when starting any new sentence)
 */
  DocumentGenerator(const string & documentsDirectory);

/**
 * Suppose you're in the middle of generating a document and that you've just added the word prevWord
 * to the document. generateNextWord(prevWord) should generate the next word at random for the document,
 * according to the frequencies of all the words that followed prevWord in the input documents
 *
 * So, for instance, if in all the input documents the word "foo" was followed by the word "bar" twice and "baz" 8 times,
 * then 80% of the time generateNextWord("foo") should return "baz" and 20% of the time you should return "bar".
 * 
 * This method should return punctuation words like "." and "," as if they were any other word.
 * Likewise, it should be able to take punctuation words as input (generateNextWord(","))
 * 
 * You can assume that prevWord is always a word that's present in one of the documents you've read in.
 */
  string generateNextWord(const string & prevWord);

  /**
 * Generate a document with numWords words in it.
 *
 * See the docs on generateNextWord for a description of what it means to generate a word.
 * After generating all the words - concatenate them all into a single string representing the entire document, and return that string.
 *
 * Notes:
 * The first word you generate should be as if the previous word was '.'
 * Your document should not contain whitespace except for spaces.
 * Your should insert a single space in front of each word except:
 * * Don't insert spaces in front of punctuation marks
 * * Don't insert a space at the start of the document
 * Punctuation "words" count against this word total.
 * If you generate a word which has no successor in the documents you
 *   are mimicing (because the word only appeared at the ends of documents)
 *   generate '.' as the next word.
 *
 * The document will likely not end at the end of a sentence. That's okay.
 */
  string generateDocument(const int numWords);

  ~DocumentGenerator();

private:
  const string PUNCTUATION = ".!,?";
  const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
};

#endif //DOCUMENT_GENERATOR_HPP
