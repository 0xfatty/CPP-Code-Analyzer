// main.cpp

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "main.h"

// Define TEST true if tests should be run
#define TEST false
// Define BENCH true if benchmarks should be run
#define BENCH false

#define STOPWORDSFN "stopwords.txt"

IndexInterface* main_table;

using std::cout;
using std::cin;

// Basic usage info template from other projects
void usage(char* argv) {
	std::cout << "Usage: " << std::endl;
	std::cout << argv << " filename.pdf [filename2.pdf ...]" << std::endl;
}

int runCatchTests( int argc, char* const argv[])
{
	// Run the tests in test.cpp.
	return Catch::Session().run(argc, argv);
}

void doBench(int argc, char* const argv[]) {
    QueryParser qp;

    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Loading PDF took ";

    for(int i=1;i<argc;i++) {
        std::string fnPDFfile(argv[i]);
        PDFReader::readPDF(fnPDFfile, main_table);
    }
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t1).count() << " microseconds\n";

    std::vector<IndexItem> top50 = main_table->topFifty();

    std::cout << "Pages: " << main_table->totalPagesCount() << "   Words: " << main_table->totalWordsCount() << std::endl;

    std::cout << "Saving index took "; 
    t1 = std::chrono::high_resolution_clock::now();
    main_table->saveIndex("index.dat");
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t1).count() << " microseconds\n";

    std::cout << "Query 1 (NOT " << top50[0].data << "): ";
    t1 = std::chrono::high_resolution_clock::now();
    qp.inputQuery("NOT " + top50[0].data);
    qp.processQuery(main_table);
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t1).count() << " microseconds\n";

    std::cout << "Query 2 (AND " << top50[1].data << " " << top50[2].data << "): ";
    t1 = std::chrono::high_resolution_clock::now();
    qp.inputQuery("AND " + top50[1].data + " " + top50[2].data);
    qp.processQuery(main_table);
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t1).count() << " microseconds\n";

    std::cout << "Query 3 (OR " << top50[3].data + " " + top50[4].data + "): ";
    t1 = std::chrono::high_resolution_clock::now();
    qp.inputQuery(top50[3].data + " " + top50[4].data);
    qp.processQuery(main_table);
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t1).count() << " microseconds\n";
}
void benchmarks(int argc, char* const argv[]) {

	// Validate number of parameters.
	if(argc<2) {
	   usage(argv[0]);
       return;
    }

    std::cout << "AVLTree ------" << std::endl;
    main_table = new AVLTree();
    doBench(argc, argv);
    delete main_table;

    std::cout << "HashTable 50 ------" << std::endl;
    main_table = new HashTable(50);
    doBench(argc, argv);
    delete main_table;

    std::cout << "HashTable 1000 ------" << std::endl;
    main_table = new HashTable(1000);
    doBench(argc, argv);
    delete main_table;
}

void newMainTable(int type) {
    if(type==0) 
        main_table = new AVLTree;
    else 
        main_table = new HashTable(10000);
}

int cinNumber() {
    int num;
    // Loop to handle bad input
    while(!(cin >> num)) {
        cin.clear(); // Clear bad flag
        cin.ignore(10000, '\n'); // Discard all input
        cout << "\n? ";
    }

    return num;
}

// Returns the number of microseconds it took to load the table
int loadTable() {
    auto t1 = std::chrono::high_resolution_clock::now();
    main_table->loadIndex("index.dat");
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t1).count();
}

int main( int argc, char* const argv[] ) 
{
    // Catch testing.
	if (TEST) {
		return runCatchTests(argc, argv);
	}
	
    // Load stop words
    PDFReader::readStopWords();

    // Benchmark mode
    if(BENCH) {
        benchmarks(argc, argv);
        return 0;
    }

    // Otherwise, UI mode
    
    // Default to AVLTree
    int main_type = 0;

    newMainTable(main_type);    

    // Attempt to load saved index
    // This fails gracefully, so it's okay if it doesn't exist
    int tableLoadTime;
    tableLoadTime = loadTable();

    bool mainLoop = true;
    int menu = 0, inp, i;
    std::string fnload, query;
    std::vector<IndexItem> top50;
    QueryParser qp;
    Results res;
    Result r;

    while(mainLoop) {
        cout << "pdfsearch\n\n";

        // We have a loaded Index
        if(main_table->totalPagesCount()) {
            if(main_type==0)
                cout << "AVL Tree :: ";
            else
                cout << "HashTable :: ";
            cout << "Pages (" << main_table->totalPagesCount() << ")  Words (" << main_table->totalWordsCount() << ")\n\n"; 
        }

        switch(menu) {
            case 0: 
                cout << "1. Maintenance Mode\n2. Query Mode\n3. Exit\n\n? ";
                inp = cinNumber();
                switch(inp) {
                    case 1:
                        menu = 1;
                        break;
                    case 2:
                        menu = 2;
                        break;
                    case 3:
                        mainLoop = false;
                        break;
                    default: 
                        menu = 0;
                }
                break;
            case 1:
                cout << "1. Add PDF to index\n2. Clear Index\n9. Back\n\n? ";
                inp = cinNumber();
                switch(inp) {
                    case 1:
                        cout << "Filename: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(cin, fnload);
                        PDFReader::readPDF(fnload, main_table);
                        main_table->saveIndex("index.dat");

                        cout << "File loaded.\n";
                        break;
                    case 2:
                        delete main_table;
                        remove("index.dat");
                        newMainTable(main_type);    
                        cout << "Index cleared.\n";
                        break;
                    case 9:
                        menu = 0;
                        break;
                }
                break;
            case 2:
                cout << "1. Query\n2. Index statistics\n";
                if(main_table->totalPagesCount()) {
                    cout << "3. Switch index to ";
                    if(main_type==0)
                        cout << "HashTable";
                    else 
                        cout << "AVL Tree";
                    cout << "\n";
                }
                cout << "9. Back\n\n? ";
                inp = cinNumber();
                switch(inp) {
                    case 1:
                        cout << "Query String: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(cin, query);
                        qp.inputQuery(query);
                        res = qp.processQuery(main_table);
                        for(i = 0; i < 15 && i < res.resultsVec.size(); i++) {
                            cout << i+1 << ": " << res.resultsVec[i].document << " (" << res.resultsVec[i].getScore() << ")\n";
                        }
                        cout << "(1-" << i << ") to view document, 0 to return.\n\n? ";
                        inp = cinNumber();

                        if(inp>=1 && inp<=i) {
                            PDFReader::dumpPDF(res.resultsVec[inp-1].document);
                        }
                        break;
                    case 2:
                        cout << "Total Pages: " << main_table->totalPagesCount() << std::endl;
                        cout << "Total Words: " << main_table->totalWordsCount() << std::endl; 
                        cout << "50 Most Popular Words and their Frequency:\n";
                        top50 = main_table->topFifty();
                        for(i=0;i<50&i<top50.size();i++) {
                            cout << top50[i].count << "\t" << top50[i].data << std::endl;
                        }
                        cout << "Time to load table from disk: " << tableLoadTime << " microseconds.\n";
                        break;
                    case 3:
                        if(main_type==0)
                            main_type=1;
                        else
                            main_type=0;
                        delete main_table;
                        newMainTable(main_type);
                        tableLoadTime = loadTable();
                        menu = 2;
                        break;
                    case 9:
                        menu = 0;
                        break;
                }
                break;
            default:
                menu = 0;
                break;
        }
        cout << "\n\n";
    }

    delete main_table;
	return 0;
}

