#include "Commit.h"
#include <sstream>
#include <iomanip>

Commit::Commit(int id, const std::string& msg) : id(id), message(msg) {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(local, "%Y-%m-%d %H:%M:%S");
    timestamp = oss.str();
}

void Commit::print() const {
    std::cout << "Commit " << id << ": " << message
              << " (" << timestamp << ")\n";
}
