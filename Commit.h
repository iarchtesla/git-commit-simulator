#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <ctime>
#include <iostream>

class Commit {
public:
    int id;
    std::string message;
    std::string timestamp;

    Commit(int id, const std::string& msg);
    void print() const;

    // للمقارنة (مطلوب لـ std::list::remove وغيرها)
    bool operator==(const Commit& other) const { return id == other.id; }
};

#endif
