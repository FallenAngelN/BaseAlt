#include "Branch.h"

int main() {
	std::string nameFirstBranch;
	std::string nameSecondBranch;
	std::string pathOutputData;

    std::cout << "First brunch (example: p10,p9,sisyphus): ";
    std::cin >> nameFirstBranch;
    std::cout << "\nSecond brunch: ";
    std::cin >> nameSecondBranch;
    std::cout << "\nOutput file location (example: E:\\example\\example.txt): ";
    std::cin >> pathOutputData;

    std::string firstUrl = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + nameFirstBranch;
    std::string secondUrl = "https://rdb.altlinux.org/api/export/branch_binary_packages/" + nameSecondBranch;

    classBranch::Branch firstBranch;
    std::cout << "\nLoading the first branch:\n";
    firstBranch.classBranch::Branch::init(firstUrl);

    classBranch::Branch secondBranch;
    std::cout << "\nLoading the second branch:\n";
    secondBranch.classBranch::Branch::init(secondUrl);

    classReturn::Return answer;
    answer.classReturn::Return::init(firstBranch, secondBranch, pathOutputData);

    system("pause");
    return 0;
}