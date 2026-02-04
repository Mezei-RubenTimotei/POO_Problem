#pragma once
#include <vector>
#include <string>
#include <map>
#include "Book.h"
#include "Member.h"

class Library {
public:
    void addBook(const Book& book);
    void registerMember(const Member& member);
    
    // Returns true if successful
    bool issueBook(const std::string& memberId, const std::string& isbn, int days = 14);
    bool returnBook(const std::string& memberId, const std::string& isbn);

    void listOverdueBooks();
    void listMostBorrowedBooks();
    void displayAllBooks();
    
private:
    std::map<std::string, Book> books; // ISBN -> Book
    std::map<std::string, Member> members; // ID -> Member
};
