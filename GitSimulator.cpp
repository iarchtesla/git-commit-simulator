#include "GitSimulator.h"
#include <iostream>
#include <algorithm>
#include <vector>

GitSimulator::GitSimulator() : nextId(1), currentBranch("main") {
    branches["main"] = nullptr;
}

std::list<Commit>::iterator GitSimulator::findCommitById(int id) {
    return std::find_if(commits.begin(), commits.end(),
                        [id](const Commit& c) { return c.id == id; });
}

std::list<Commit>::const_iterator GitSimulator::findCommitById(int id) const {
    return std::find_if(commits.begin(), commits.end(),
                        [id](const Commit& c) { return c.id == id; });
}

void GitSimulator::commit(const std::string& msg) {
    commits.push_back(Commit(nextId++, msg));
    // update current branch pointer
    branches[currentBranch] = &commits.back();
    std::cout << "Commit " << commits.back().id << " created on branch '"
              << currentBranch << "'\n";
}

void GitSimulator::log() const {
    std::cout << "Commits on branch '" << currentBranch << "':\n";
    for (auto it = commits.rbegin(); it != commits.rend(); ++it) {
        it->print();
    }
}

void GitSimulator::checkout(int id) {
    auto it = findCommitById(id);
    if (it == commits.end()) {
        std::cout << "Commit " << id << " not found.\n";
        return;
    }
    // Detached HEAD: just store the pointer, but we don't update branches
    std::cout << "HEAD now at commit " << id << " (detached)\n";
}

void GitSimulator::checkoutBranch(const std::string& branchName) {
    if (branches.find(branchName) == branches.end()) {
        std::cout << "Branch '" << branchName << "' does not exist.\n";
        return;
    }
    currentBranch = branchName;
    std::cout << "Switched to branch '" << branchName << "'.\n";
    if (branches[currentBranch] == nullptr)
        std::cout << "Branch has no commits yet.\n";
    else
        std::cout << "HEAD at commit " << branches[currentBranch]->id << "\n";
}

void GitSimulator::reset(int id) {
    auto it = findCommitById(id);
    if (it == commits.end()) {
        std::cout << "Commit " << id << " not found.\n";
        return;
    }
    // Erase from it to end
    commits.erase(it, commits.end());
    // Update branch pointer if needed
    if (!commits.empty())
        branches[currentBranch] = &commits.back();
    else
        branches[currentBranch] = nullptr;
    std::cout << "Reset to commit " << id << ". Later commits removed.\n";
}

void GitSimulator::stashPush() {
    if (commits.empty()) {
        std::cout << "No commits to stash.\n";
        return;
    }
    Commit* latest = &commits.back();
    stash.push(latest);
    std::cout << "Stashed commit " << latest->id << "\n";
}

void GitSimulator::stashPop() {
    if (stash.empty()) {
        std::cout << "Stash is empty.\n";
        return;
    }
    Commit* stashed = stash.top();
    stash.pop();
    // Re-apply as a new commit (simple)
    commit("Restored from stash: " + stashed->message);
    std::cout << "Stashed commit applied and removed from stash.\n";
}

void GitSimulator::createBranch(const std::string& name) {
    if (branches.find(name) != branches.end()) {
        std::cout << "Branch '" << name << "' already exists.\n";
        return;
    }
    Commit* currentHead = commits.empty() ? nullptr : &commits.back();
    branches[name] = currentHead;
    std::cout << "Branch '" << name << "' created at commit ";
    if (currentHead) std::cout << currentHead->id;
    else std::cout << "none";
    std::cout << "\n";
}

void GitSimulator::merge(const std::string& branchName) {
    if (branches.find(branchName) == branches.end()) {
        std::cout << "Branch '" << branchName << "' does not exist.\n";
        return;
    }
    Commit* sourceHead = branches[branchName];
    if (!sourceHead) {
        std::cout << "Branch '" << branchName << "' has no commits.\n";
        return;
    }
    if (commits.empty()) {
        std::cout << "Current branch has no commits.\n";
        return;
    }
    // Simple merge: copy all commit messages from source branch that are not in current
    // Since we don't track DAG, we just copy all commits from sourceHead backwards
    // but avoid duplicates by id.
    // Collect all commit ids from source branch (walk backwards using list)
    // But we don't have direct prev pointer. Instead, we can iterate over the whole list
    // and find commits that are part of source branch chain? Complicated.
    // For simulation, we'll just add a new commit that says "Merged branch X"
    commit("Merged branch '" + branchName + "'");
    std::cout << "Merge completed (simplified).\n";
}

void GitSimulator::search(const std::string& keyword) const {
    bool found = false;
    for (const auto& commit : commits) {
        if (commit.message.find(keyword) != std::string::npos) {
            commit.print();
            found = true;
        }
    }
    if (!found) std::cout << "No commits contain '" << keyword << "'\n";
}

void GitSimulator::status() const {
    std::cout << "On branch '" << currentBranch << "'\n";
    if (!commits.empty())
        std::cout << "HEAD at commit " << commits.back().id << "\n";
    else
        std::cout << "No commits yet.\n";
    std::cout << "Stash size: " << stash.size() << "\n";
    std::cout << "Cherry-pick queue size: " << cherryQueue.size() << "\n";
}

void GitSimulator::cherryPick(int id) {
    auto it = findCommitById(id);
    if (it == commits.end()) {
        std::cout << "Commit " << id << " not found.\n";
        return;
    }
    cherryQueue.push(&(*it));
    std::cout << "Commit " << id << " added to cherry-pick queue.\n";
}

void GitSimulator::cherryPickProcess() {
    if (cherryQueue.empty()) {
        std::cout << "No cherry-picks queued.\n";
        return;
    }
    Commit* toPick = cherryQueue.front();
    cherryQueue.pop();
    commit("Cherry-picked commit " + std::to_string(toPick->id) + ": " + toPick->message);
    std::cout << "Cherry-pick applied.\n";
}
