#include "GitSimulator.h"
#include <iostream>
#include <string>
#include <limits>

void showMenu() {
    std::cout << "\n========== Git Simulator () ==========\n";
    std::cout << "1.  git commit\n";
    std::cout << "2.  git log\n";
    std::cout << "3.  git checkout <id>\n";
    std::cout << "4.  git checkout branch <name>\n";
    std::cout << "5.  git reset --hard <id>\n";
    std::cout << "6.  git stash\n";
    std::cout << "7.  git stash pop\n";
    std::cout << "8.  git branch <name>\n";
    std::cout << "9.  git merge <name>\n";
    std::cout << "10. git grep <keyword>\n";
    std::cout << "11. git status\n";
    std::cout << "12. git cherry-pick <id>\n";
    std::cout << "13. git cherry-pick --continue\n";
    std::cout << "0.  Exit\n";
    std::cout << "Choice: ";
}

int main() {
    GitSimulator git;
    int choice;
    std::string input;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "Commit message: ";
                std::getline(std::cin, input);
                git.commit(input);
                break;
            case 2:
                git.log();
                break;
            case 3:
                std::cout << "Commit id: ";
                std::getline(std::cin, input);
                git.checkout(std::stoi(input));
                break;
            case 4:
                std::cout << "Branch name: ";
                std::getline(std::cin, input);
                git.checkoutBranch(input);
                break;
            case 5:
                std::cout << "Reset to commit id: ";
                std::getline(std::cin, input);
                git.reset(std::stoi(input));
                break;
            case 6:
                git.stashPush();
                break;
            case 7:
                git.stashPop();
                break;
            case 8:
                std::cout << "Branch name: ";
                std::getline(std::cin, input);
                git.createBranch(input);
                break;
            case 9:
                std::cout << "Merge branch: ";
                std::getline(std::cin, input);
                git.merge(input);
                break;
            case 10:
                std::cout << "Keyword: ";
                std::getline(std::cin, input);
                git.search(input);
                break;
            case 11:
                git.status();
                break;
            case 12:
                std::cout << "Commit id to cherry-pick: ";
                std::getline(std::cin, input);
                git.cherryPick(std::stoi(input));
                break;
            case 13:
                git.cherryPickProcess();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
