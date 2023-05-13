// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include "main.h"

// bool sum(int a, int b, int sum) {
//     return a + b == sum;
// }

// int main() {
//     std::string button;
//     std::cout << "Enter 'RUN' or 'SUBMIT': ";
//     std::cin >> button;
//     std::string file_name;
//     if(button == "RUN"){
//         file_name = "run_cases.txt";
//     } 
//     if(button == "SUBMIT"){
//         file_name = "submit_cases.txt";
//     }  
//     std::ifstream infile(file_name);
//     std::ofstream outfile("result.txt");
//     if (!infile) {
//         std::cerr << "Error opening input file\n";
//         return 1;
//     }
//     if (!outfile) {
//         std::cerr << "Error opening output file\n";
//         return 1;
//     }
//     std::string line;
//     std::vector<bool> results;
//     int line_count = 0;
//     while (std::getline(infile, line)) {
//         ++line_count;
//         std::istringstream ss(line);
//         int a, b, c;
//         if (ss >> a >> b >> c) {
//             int trueSum = c;
//             int yourSum = solution(a, b);
//             bool result = (yourSum == trueSum);
//             results.push_back(result);
//             if (!result) {
//                 outfile << "Case " << line_count << " is false\n";
//                 outfile << "Expected: " << trueSum << "\n";
//                 outfile << "Output: " << yourSum << "\n";
//             }
//         }
//         else {
//             std::cerr << "Error parsing line " << line_count << std::endl;
//             return 1;
//         }
//     }
//     bool all_results = true;
//     for (bool r : results) {
//         if (!r) {
//             all_results = false;
//             break;
//         }
//     }
//     if (all_results) {
//         outfile << "Success\n";
//     }

//     return 0;
// }


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "json.hpp"
#include "main.h"

bool sum(int a, int b, int sum) {
    return a + b == sum;
}

int main() {
    std::string button;
    std::cout << "Enter 'RUN' or 'SUBMIT': ";
    std::cin >> button;
    std::string file_name;
    if(button == "RUN"){
        file_name = "run_cases.txt";
    } 
    if(button == "SUBMIT"){
        file_name = "submit_cases.txt";
    }  
    std::ifstream infile(file_name);
    if (!infile) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    nlohmann::json results;
    int line_count = 0;
    std::string line;
    while (std::getline(infile, line)) {
        ++line_count;
        std::istringstream ss(line);
        int a, b, c;
        if (ss >> a >> b >> c) {
            int trueSum = c;
            int yourSum = solution(a, b);
            bool result = (yourSum == trueSum);
            results.push_back({{"case", line_count},
                               {"expected", trueSum},
                               {"output", yourSum},
                               {"result", result}});
        } else {
            std::cerr << "Error parsing line " << line_count << std::endl;
            return 1;
        }
    }

    bool all_results = true;
    for (auto& r : results) {
		all_results &= r.at("result").get<bool>();
        if (!r["result"]) {
            std::cout << "Case " << r["case"] << " is false\n";
            std::cout << "Expected: " << r["expected"] << "\n";
            std::cout << "Output: " << r["output"] << "\n";
        }
    }

    results.push_back({{"success", all_results}});
    std::ofstream outfile("result.json");
    outfile << results.dump(4) << std::endl;

    return 0;
}
