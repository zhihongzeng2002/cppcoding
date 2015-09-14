#include "moderate.h"
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <climits>
#include <iterator>
#include <algorithm>

Moderate::Moderate()
{
}

int flip(int x) {
    return 1^x;
}

int sign(int x) {
    return flip((x>>31) & 1);
}

int Moderate::calcMax(int a, int b) {
    int c=a-b;

    int signa = sign(a);
    int signb = sign(b);
    int signc = sign(c);

    int samesignab = signa ^ signb;
    int k = samesignab * signa + flip(samesignab) * signc;

    return k*a + flip(k) *b;

}

void Moderate::masterMind(string guess, string solution) {
    if (guess.length() != solution.length()) {
        throw invalid_argument("the lengths of two string are not equal");
    }
    unordered_map<char, int> table;

    int hit=0, pseudo_hit=0;
    for (int i=0; i<guess.length(); i++) {
        if (guess[i]==solution[i])
            hit++;
        else {
            table[solution[i]]++;
        }
    }

    for (int i=0; i<guess.length(); i++) {
        if (guess[i]!=solution[i] && table.find(guess[i])!=table.end()) {
            pseudo_hit++;
            table[guess[i]]--;
        }
    }
    cout << "hit=" << hit << ", pseudo_hit=" << pseudo_hit << endl;
}

/**
 * @brief Moderate::findSubarrayToSorted
 * @param A
 * divided A to left middle right, and left and right and sorted subarray
 */
void Moderate::findSubarrayToSorted(vector<int> &A) {
    if (A.size()<=1) return ;
    int i=1, j=A.size()-2;
    // find the end of left sorted subarray
    for (; i<A.size(); i++) {
        if (A[i] < A[i-1]) {
            i--;
            break;
        }
    }
    // find the end of right sorted subarray
    for (; j>=0; j--) {
        if (A[j]>A[j+1]) {
            j++;
            break;
        }
    }
    cout << i << ", " << j << endl;
    if (i==A.size()) { // the sorted array
        cout << "already sorted array" << endl;
        return;
    }

    // find the min and max in the middle subarray
    int minV=INT_MAX;
    int maxV=INT_MIN;
    for (int k=i; k<=j; k++) {
        if (minV>A[k])
            minV=A[k];
        if (maxV<A[k])
            maxV=A[k];
    }

    // shrink left side
    int m=0, n=A.size()-1;
    for (int k=i-1; k>=0; k--) {
        if (A[k]<=minV)
            m=k+1;
    }
    // shrink right side
    for (int k=j+1; k<A.size(); k++) {
        if (A[k]>=maxV)
            n=k-1;
    }
    cout << m << "," << n << endl;
}

static string print2(int n) {
    vector<string> nums{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    vector<string> nums10{"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                          "eighteen", "ninteen"};
    vector<string> nums2090{"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eight", "ninety"};

    string out;
    if (n/100) {
        out += nums[n/100-1]+" hundred ";
    }
    n %= 100;
    if (n==0)
        return out;

    if (n>=20) {
        out += nums2090[n/10-2]+" ";
        n %= 10;
        if (n) out += nums[n-1]+" ";
    } else if (n>=10  && n<20) {
        out += nums10[n-10]+" ";
    } else {
        out += nums[n-1]+" ";
    }
    return out;
}

string Moderate::printInterger_better(int x) {
    vector<string> bigs{"", "thousand", "million", "billion"};
    string out;
    if (!x) {
        return "Zero";
    } else if (x<0) {
        return  "Negative " + printInterger_better(x*(-1));
    }

    int count=0;
    while (x) {
        if (x%1000) {
            out = print2(x%1000) + bigs[count] + " " + out;
        }
        x /= 1000;
        count++;
    }
    return out;
}

void Moderate::printInterger(int x) {
    if (!x)
    {
        cout << "Zero" << endl;
        return;
    }
    string num;
    if (x<0) {
        num += "negative ";
        x *=-1;
    }

    // billion
    int n=x/1000000000;
    if (n>0) {
        num += print2(n);
        num += "billion ";
    }

    x=x%1000000000;
    if (x==0) {
        cout << num << endl;
        return;
    }
    // million
    n=x/1000000;
    if (n>0) {
        num += print2(n);
        num += "million ";
    }
    x=x%1000000;
    if (x==0) {
        cout << num << endl;
        return;
    }

    // thousand
    n=x/1000;
    if (n>0) {
        num += print2(n);
        num += "thousand ";
    }
    x=x%1000;
    if (x==0) {
        cout << num << endl;
        return;
    }

    num+=print2(x);
    cout << num << endl;
}

int Moderate::findMaxSubarray(const vector<int> &A) {
    int maxV=INT_MIN;
    int sum=0;
    vector<int> index;
    vector<int> maxArray;
    for (int i=0; i<A.size(); i++) {
        sum += A[i];
        index.push_back(i);
        if (sum>maxV) {
            maxV=sum;
            maxArray=index;
        }
        if (sum<0) {
            sum=0;
            index.clear();
        }
    }
    copy(maxArray.begin(), maxArray.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    return maxV;
}

struct ParseResult {
    int minLen;
    string parseStr;
    ParseResult(int x, string y) : minLen(x), parseStr(y) {}
};

static ParseResult parseMin(ParseResult & exact, ParseResult & extend) {
    if (exact.minLen<extend.minLen) {
        return exact;
    } else
        return extend;
}

static ParseResult parseSentence_helper(string & sentence, unordered_set<string> & dict,
                                        int start, int end, unordered_map<int, ParseResult> & table) {
    if (end>=sentence.length()) {
        string str = sentence.substr(start);
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        return ParseResult(end-start, str);
    } else if (table.find(start)!=table.end()){
//        cout << "it is in table, start=" << start << ", " << table.find(start)->second.minLen << "."
//             << table.find(start)->second.parseStr << endl; ;
        return table.find(start)->second;
    }

    string word=sentence.substr(start, end+1);
    ParseResult  exact = parseSentence_helper(sentence, dict, end+1, end+1, table);
//    cout << word << endl;
    if (dict.find(word)!=dict.end()) {
    } else {
        exact.minLen += word.length();
        transform(word.begin(), word.end(), word.begin(), ::toupper);
    }

    cout << start<<"**" << exact.parseStr ;
    exact.parseStr = word + " " + exact.parseStr;
    cout << "**" << exact.parseStr << endl;


    ParseResult extend = parseSentence_helper(sentence, dict, start, end+1, table);
    ParseResult best = parseMin(exact, extend);

//    if (start==0) {
        cout << "-------------start=" << start << endl;
        cout << exact.minLen << ":" << exact.parseStr << endl;
        cout << extend.minLen << ":" << extend.parseStr << endl;
        cout << best.minLen << ":" << best.parseStr << endl;
//    }

    auto it = table.emplace(start, best);
    if (!it.second && best.minLen<it.first->second.minLen) {
        table.erase(start);
        table.emplace(start, best);
    }
    return best;
}

/** the result is partiall wrong:JESS look, JESSLOOK brother(wrong)
 * @brief Moderate::parseSentence
 * @param sentence
 * @param dict
 */
void Moderate::parseSentence(string sentence, unordered_set<string> &dict) {
    unordered_map<int, ParseResult> table;
    ParseResult res = parseSentence_helper(sentence, dict, 0,0, table);
    cout << res.parseStr << endl;
    cout << res.minLen << endl;
    for (auto x : table) {
        cout << x.first << "->" << x.second.minLen << ", " << x.second.parseStr << endl;
    }
}

static ParseResult parseSentence_helper2(string & sentence, unordered_set<string> & dict,
                                        int start, int end, unordered_map<int, ParseResult> & table) {
    if (start>=end) {
        return ParseResult(0, "");
    }
    else if (table.find(start)!=table.end()){
        return table.find(start)->second;
    }

    ParseResult best(INT_MAX, "");
    for (int i=start+1; i<=end; i++) {
        string word = sentence.substr(start, i-start);
//        cout << "word=" << word << endl;
        ParseResult latter = parseSentence_helper2(sentence, dict, i, end, table);
//        cout << "latter=" << latter.minLen << "," << latter.parseStr << endl;
        if (dict.find(word) == dict.end()) {
            latter.minLen += word.size();
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            latter.parseStr = word + latter.parseStr;
        } else {
            latter.parseStr = " " + word + " " + latter.parseStr;
        }

        if (latter.minLen < best.minLen)
            best=latter;
    }
    table.emplace(start, best);
    return best;
}

static ParseResult parseSentence_helper3(string & sentence, unordered_set<string> & dict,
                                        unordered_map<string, ParseResult> & table) {
    if (sentence.empty()) {
        return ParseResult(0, "");
    }
    else if (table.find(sentence)!=table.end()){
        return table.find(sentence)->second;
    }

    ParseResult best(INT_MAX, "");
    for (int i=1; i<=sentence.size(); i++) {
        string word = sentence.substr(0, i);
        string right = sentence.substr(i);
//        cout << "word=" << word << endl;
        ParseResult latter = parseSentence_helper3(right, dict, table);
//        cout << "latter=" << latter.minLen << "," << latter.parseStr << endl;
        if (dict.find(word) == dict.end()) {
            latter.minLen += word.size();
            transform(word.begin(), word.end(), word.begin(), ::toupper);
            latter.parseStr = word + latter.parseStr;
        } else {
            latter.parseStr = " " + word + " " + latter.parseStr;
        }

        if (latter.minLen < best.minLen)
            best=latter;
    }
    table.emplace(sentence, best);
    return best;
}

void Moderate::parseSentence2(string sentence, unordered_set<string> &dict) {
    unordered_map<string, ParseResult> table;
    ParseResult res = parseSentence_helper3(sentence, dict, table);
    cout << res.parseStr << endl;
    cout << res.minLen << endl;
}
