#ifndef GITSIMULATOR_H
#define GITSIMULATOR_H

#include "Commit.h"
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>

class GitSimulator {
private:
    std::list<Commit> commits;               // Doubly linked list of commits
    std::stack<Commit*> stash;               // Stack of pointers to commits (LIFO)
    std::queue<Commit*> cherryQueue;         // Queue for cherry-pick (FIFO)

    std::unordered_map<std::string, Commit*> branches; // branch name -> latest commit pointer
    std::string currentBranch;
    int nextId;

    // Helper: find commit by id, returns iterator or nullptr
    std::list<Commit>::iterator findCommitById(int id);
    std::list<Commit>::const_iterator findCommitById(int id) const;

public:
    GitSimulator();

    // Basic commands
    void commit(const std::string& msg);
    void log() const;
    void checkout(int id);                 // detached HEAD
    void checkoutBranch(const std::string& branchName);
    void reset(int id);                    // hard reset
    void stashPush();
    void stashPop();
    void createBranch(const std::string& name);
    void merge(const std::string& branchName);
    void search(const std::string& keyword) const;
    void status() const;

    // Advanced
    void cherryPick(int id);
    void cherryPickProcess();
};

#endif
