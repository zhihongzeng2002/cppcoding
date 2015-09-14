#include "oop.h"
#include <algorithm>
#include <bitset>

OOP::OOP()
{
}

// find the missing number in 4billion integers (nonnegative) with 10 MB memory
// 4 billion = 2^32 integers
// 10 MB = 2^20*8=2^23 MB = 2^21 integers (4B integer)
// rangeSize = bitSize > 2^32/2^21 = 2^11, choose 2^12;
// chunkSize = 2^32 / 2^12 = 2^20;
// or choose bitsize = 2^12, rangSize=2^20
int OOP::findMissNumber(fstream &fs) {
    const int rangeSize= 1<<12;
    vector<int> count(1<<20, 0);
    int x;
    while (fs>>x) {
        count[x/rangeSize]++;
    }

    int start=0;
    for (int i=0; i<count.size(); i++) {
        if( count[i]<rangeSize) {
            start=i*rangeSize;
            break;
        }
    }
    count.clear();
    bitset<rangeSize> bits;
    fs.clear();
    fs.seekg(0, ios::beg);
    while (fs>>x) {
        if (x>=start && x<start+rangeSize )
            bits.set(x-start);
    }
    fs.close();

    for (int i=0; i<rangeSize; i++) {
        if (bits.test(i)==0) {
            return start+i;
        }
    }
    return -1;

}

string OOP::tail(const string &filename, int numLine) {
    fstream fstr(filename.c_str());

    fstr.seekg(0, ios::end);
    int size = fstr.tellg();
    char c;
    string output;
    int count=0;
    for (int i=0; i<size; i++) {
        fstr.seekg(-1-i, ios::end);
        fstr.get(c);
        if (c=='\n') {
            count++;
            if (count>=numLine)
                break;
        }
        output.push_back(c);
    }
    reverse(output.begin(), output.end());
    cout << output << endl;
    return output;
}

void OOP::elevatorSystem() {
    // whole system: including car, managment office, motor control system, 911 communication
    // Car:including box, lights, weight and fire and other sensor, GUI,  motor control, network
    // GUI: buttons and indicators
    // emergency and safety:
    // management:
}

void OOP::searchqueryWithMultipleMachines() {
    //http://www.careercup.com/question?id=5377673471721472
    //depend on type of distributed index: string/url/other
    // master index server 1 to n that index documentations from the crawler.
    // for each index master server, there will be multiple slave servers with replicated indexes.
    //       slave server handle queries
    // process: query from browser, to a query analyzer, splid the query to multiple sub queries
    //      example: google mountain view jobs
    //               sub queries: 1. complete query as original,
    //                            2. boolean query: google AND mountain AND view AND jobs
    //                            3. distance/proximity query: google mountain AND mountain view
    //                                  AND view jobs AND google mountain view AND mountain view jobs
    //                            4. single word queries: google, mountain, view,jobs
    //                            5. single word fuzzy queries: google~, mountain~, view~, jobs
    //                            6. range query: if search term include date range, regular expression will generate date range query
    // the sub queries are fired across multiple slave servers in parallel.
    //      could be done using publish subscribe messaging model or directly to slave server using software/hardware load balanced way
    // each server will receive one query each and come up with maching doc result with type weight(vector like structure) and count weight
    // based on the weights, a dot product will be calculated to compute IR (information retrievel) score. and page rank score is calculated also
    // multiple results will be combined based on the weight rank and page rank and first k results will be sent back to the server for caching.
}

void OOP::FBNewsFeed() {
    // data struture: undirected social graph, users as vertices, friendship as edges
    //              vertice
    //
}
