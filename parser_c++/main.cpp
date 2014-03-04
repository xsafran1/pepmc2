#include <cstdlib>
#include <iostream>
#include <fstream>
#include "parser/Parser.h"

using namespace std;

int main (int argc, char **argv)
{
    if(argc == 2) {
        std::ifstream fin(argv[1]);
        Parser parser(fin);
        parser.parse();
        Skusobna &storage = parser.returnStorage();

        cout << "VARs: \n";
        for(string v : storage.var) {
            cout << "\t" << v << endl;
        }
        cout << "CONSTs: \n";
        for(double v : storage.constant) {
            cout << "\t" << v << endl;
        }
        cout << "RAMPs: \n";
        for(string v : storage.ramp) {
            cout << "\t" << v << endl;
        }
        cout << "SIGMs: \n";
        for(string v : storage.sigm) {
            cout << "\t" << v << endl;
        }
        cout << "STEPs: \n";
        for(string v : storage.step) {
            cout << "\t" << v << endl;
        }
    } else {
        Parser parser(std::cin);
        parser.parse();
        Skusobna &storage = parser.returnStorage();

        cout << "VARs: \n";
        for(string v : storage.var) {
            cout << "\t" << v << endl;
        }
        cout << "CONSTs: \n";
        for(double v : storage.constant) {
            cout << "\t" << v << endl;
        }
        cout << "RAMPs: \n";
        for(string v : storage.ramp) {
            cout << "\t" << v << endl;
        }
        cout << "SIGMs: \n";
        for(string v : storage.sigm) {
            cout << "\t" << v << endl;
        }
        cout << "STEPs: \n";
        for(string v : storage.step) {
            cout << "\t" << v << endl;
        }
    }

	return 0;
}
