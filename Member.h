#pragma once
#include <string>
#include <vector>
#include <ctime>

struct BorrowedBookInfo {
    std::string isbn;
    std::time_t dueDate;
};

class Member {
public:
    Member() = default;
    Member(std::string name, std::string id);

    std::string getName() const;
    std::string getId() const;
    const std::vector<BorrowedBookInfo>& getBorrowedBooks() const;

    void borrowBook(std::string isbn, int daysToReturn = 14);
    bool returnBook(std::string isbn);

private:
    std::string name;
    std::string id;
    std::vector<BorrowedBookInfo> borrowedBooks;
};
