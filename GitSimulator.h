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
    std::list<Commit> commits;               
    std::stack<Commit*> stash;               
    std::queue<Commit*> cherryQueue;         

    std::unordered_map<std::string, Commit*> branches; 
    std::string currentBranch;
    int nextId;

    
    std::list<Commit>::iterator findCommitById(int id);
    std::list<Commit>::const_iterator findCommitById(int id) const;

public:
    GitSimulator();

    
    void commit(const std::string& msg);
    void log() const;
    void checkout(int id);                 
    void checkoutBranch(const std::string& branchName);
    void reset(int id);                    
    void stashPush();
    void stashPop();
    void createBranch(const std::string& name);
    void merge(const std::string& branchName);
    void search(const std::string& keyword) const;
    void status() const;

    
    void cherryPick(int id);
    void cherryPickProcess();
};

#endif
