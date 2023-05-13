#include <iostream>
#include <string>
#include <cstdlib>

int main(){
	std::string language;
	std::cout << "Input language ('C++', 'Python', 'Java' or 'JS'): ";
	std::cin >> language;
	if(language == "C++"){
		system("g++ main.cpp check.cpp");
		system("./a.out");
	}
	else if(language == "Python"){
		system("python3 check.py");
	}
	else if(language == "Java"){
		system("javac check.java");
		system("java check");
	}
	else if(language == "JS"){
		system("node check.js");
	}
	else{
		std::cout << "Language like this doesn't exist." << std::endl;
	}
}