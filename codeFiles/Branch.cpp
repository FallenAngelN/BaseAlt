#include "pch.h"
#include "Branch.h"

namespace classBranch {
	void Branch::init(std::string url) {
		cpr::Response branch = cpr::Get(cpr::Url{ url });
		std::cout << "Loading is complete.\n\n";
		std::cout << "Parsing the received data:\n";
		nlohmann::json json = nlohmann::json::parse(branch.text);
		length = json["length"];
		for (int i = 0; i < length; i++) {
			name[i] = json["packages"][i]["name"];
			version[i] = json["packages"][i]["version"];
		}
		for (int i = 0; i < length; i++) {
			keyValue.insert(keyValue.end(), { name[i],version[i] });
		}
		std::cout << "Parsing completed.\n";
	}

	nlohmann::json Branch::getLength() {
		return length;
	}

	nlohmann::json Branch::getNameElem(int i) {
		return name[i];
	}

	nlohmann::json Branch::getVersionElem(int i) {
		return version[i];
	}

	nlohmann::json Branch::getKeyValue() {
		return keyValue;
	}
}


namespace classReturn {
	void Return::init(classBranch::Branch firstBranch, classBranch::Branch secondBranch, std::string path) {
		int firstSize = firstBranch.getLength();
		int secondSize = firstBranch.getLength();

		nlohmann::json keyValueFirstBranch = firstBranch.getKeyValue();
		nlohmann::json keyValueSecondBranch = secondBranch.getKeyValue();

		std::string local;

		std::cout << "\nComparison of loaded data:\n";

		int countFirst = 0, countSecond = 0, countThird = 0;

		for (int i = 0; i < firstSize; i++) {

			if (!keyValueSecondBranch.contains(firstBranch.getNameElem(i))) {
				jsonFirstTask["packages"][countFirst]["name"] = firstBranch.getNameElem(i);
				jsonFirstTask["packages"][countFirst]["version"] = firstBranch.getVersionElem(i);
				countFirst++;
			}

			else if (keyValueSecondBranch.contains(firstBranch.getNameElem(i))) {
				local = firstBranch.getNameElem(i);
				if (cmpVersion(firstBranch.getVersionElem(i), keyValueSecondBranch[local])) {
					jsonThirdTask["package"][countThird]["name"] = firstBranch.getNameElem(i);
					jsonThirdTask["packages"][countThird]["version"] = firstBranch.getVersionElem(i);
					countThird++;
				}
			}
		}

		for (int i = 0; i < secondSize; i++) {

			if (!keyValueFirstBranch.contains(secondBranch.getNameElem(i))) {
				jsonSecondTask["packages"][countSecond]["name"] = secondBranch.getNameElem(i);
				jsonSecondTask["packages"][countSecond]["version"] = secondBranch.getVersionElem(i);
				countSecond++;
			}
		}

		jsonFirstTask["length"] = countFirst;
		jsonSecondTask["length"] = countSecond;
		jsonThirdTask["length"] = countThird;

		std::cout << "Comparison completed.\n\n";

		std::cout << "Data output: \n";

		std::ofstream out(path);

		out << "List of packages that are in the first branch, but not in the second:" << std::endl;
		out << jsonFirstTask << "\n\n";

		out << "List of packages that are in the second branch, but not in the first:" << std::endl;
		out << jsonSecondTask << "\n\n";

		out << "List of packages in the first branch whose version is greater than in the second:" << std::endl;
		out << jsonThirdTask;

		std::cout << "Data output completed.\n\n";
	}

	bool Return::cmpVersion(std::string firstVersion, std::string secondVersion) {
		std::vector<std::string> firstSplitVersion, secondSplitVersion;
		boost::split(firstSplitVersion, firstVersion, boost::is_any_of("."));
		boost::split(secondSplitVersion, secondVersion, boost::is_any_of("."));
		int sizeVersion = min(firstSplitVersion.size(), secondSplitVersion.size());
		for (int i = 0; i < sizeVersion; i++) {
			if (atoi(firstSplitVersion[i].c_str()) > atoi(secondSplitVersion[i].c_str())) {
				return true;
			}
		}
		return false;
	}
}
