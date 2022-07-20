#pragma once

#ifdef BRANCH_EXPORTS
#define BRANCH_API __declspec(dllexport)
#else
#define BRANCH_API __declspec(dllimport)
#endif

#include "framework.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//Used to store and process data after a get request.
#include <nlohmann/json.hpp> 

//Used for get request.
#include <cpr/cpr.h> 

//Used to parse the package version.
#include <boost/algorithm/string.hpp> 

namespace classBranch {
	class Branch {
	private:
		nlohmann::json length;
		nlohmann::json name;
		nlohmann::json version;
		nlohmann::json::object_t keyValue;

	public:
		void BRANCH_API init(std::string);

		nlohmann::json BRANCH_API getLength();

		nlohmann::json BRANCH_API getNameElem(int);

		nlohmann::json BRANCH_API getVersionElem(int);

		nlohmann::json BRANCH_API getKeyValue();
	};
}

namespace classReturn {
	class Return {
	private:
		//Definition of the future json structure.
		nlohmann::json::object_t jsonFirstTask = { {"length",0}, {"packages",{{ {"name",""},{"version",""}}}} };
		nlohmann::json::object_t jsonSecondTask = { {"length",0}, {"packages",{{ {"name",""},{"version",""}}}} };
		nlohmann::json::object_t jsonThirdTask = { {"length",0}, {"packages",{{ {"name",""},{"version",""}}}} };

	public:

		//A function that processes input data and distributes the processing results over three output json.
		void BRANCH_API init(classBranch::Branch, classBranch::Branch, std::string);


		//Parsing a string with the package version using boost and comparison.
		bool BRANCH_API cmpVersion(std::string, std::string);
	};
}
