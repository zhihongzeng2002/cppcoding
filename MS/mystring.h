#ifndef MYSTRING_H
#define MYSTRING_H

#include <string.h>
#include <vector>
#include <string>

using namespace std;

class MyString
{
public:
    MyString(){}

    static void sortAnagramsByhashing(vector<string> &words);
    static void printWords(vector<string> &words);
    static void sortAnagrams(std::vector<std::string> & words);
    static void reverseSentence(char * sentence);
    static void reverseBuffer(char * buff, int start, int end);
    static void LCS(char * seq1, char * seq2);
    static void LCSubstring(char *seq1, char *seq2);
    static void rotation(char *seq1, int numRotation);
    static void permutation(char *str);
    static void combination(char *str);
    static void combination_2(char *str, std::vector<char> &seq);
    static void deleteChars(char *pSource, char *pDelete);
};

class CMyString
{
public:
    CMyString(char *pData=NULL)
    {
        int length = strlen(pData);
        m_pData = new char [length+1];
        memcpy(m_pData, pData, length+1);

    }
    CMyString(CMyString & str){
        char *pData = str.getData();
        int len = strlen(str.getData());
        m_pData = new char [len+1];
        memcpy(m_pData, pData, len+1);
    }
    ~CMyString()
    {
        if (m_pData) delete [] m_pData;
        m_pData=NULL;
    }

    char * getData() { return m_pData;}

    CMyString operator=(CMyString & str){

        if (this != &str)
        {
            if (m_pData) delete [] m_pData;
            int len = strlen(str.getData());
            m_pData = new char [len+1];
            memcpy(m_pData, str.getData(), len+1);


//        CMyString temp(str);
//        char *x = temp.getData();
//        char * y =temp.getData();
//        y = m_pData;
//        m_pData = x;

        }
        return *this;
    }

private:
    char *m_pData;

};

#endif // MYSTRING_H
