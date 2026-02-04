#include "Member.h"
#include <algorithm>
#include <iostream>

Member::Member(std::string name, std::string id)
    : name(std::move(name)), id(std::move(id)) {}

std::string Member::getName() const { return name; }
std::string Member::getId() const { return id; }
const std::vector<BorrowedBookInfo>& Member::getBorrowedBooks() const { return borrowedBooks; }

void Member::borrowBook(std::string isbn, int daysToReturn) {
    std::time_t now = std::time(nullptr);
    std::time_t due = now + (daysToReturn * 24 * 60 * 60);
    borrowedBooks.push_back({std::move(isbn), due});
}

bool Member::returnBook(std::string isbn) {
    auto it = std::find_if(borrowedBooks.begin(), borrowedBooks.end(),
        [&isbn](const BorrowedBookInfo& info) { return info.isbn == isbn; });
    
    if (it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
        return true;
    }
    return false;
}
