#include "Library.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void Library::addBook(const Book& book) {
    books[book.getISBN()] = book;
}

void Library::registerMember(const Member& member) {
    members[member.getId()] = member;
}

bool Library::issueBook(const std::string& memberId, const std::string& isbn, int days) {
    if (members.find(memberId) == members.end()) {
        std::cout << "Member not found!\n";
        return false;
    }
    if (books.find(isbn) == books.end()) {
        std::cout << "Book not found!\n";
        return false;
    }

    Member& member = members[memberId];
    Book& book = books[isbn];

    if (book.borrowCopy()) {
        member.borrowBook(isbn, days);
        std::cout << "Book issued successfully to " << member.getName() << ".\n";
        return true;
    } else {
        std::cout << "Book is not available.\n";
        return false;
    }
}

bool Library::returnBook(const std::string& memberId, const std::string& isbn) {
    if (members.find(memberId) == members.end()) {
        std::cout << "Member not found!\n";
        return false;
    }
    
    Member& member = members[memberId];
    // Check if the book exists in the library records even if we don't strictly need it to return from member
    // But we need to increment book availability
    if (books.find(isbn) == books.end()) {
         std::cout << "Book ISBN not found in library system!\n";
         // Proceeding might be risky if we can't update book stock, but let's assume we just return from member if so? 
         // Better to fail safe.
         return false;
    }

    if (member.returnBook(isbn)) {
        books[isbn].returnCopy();
        std::cout << "Book returned successfully.\n";
        return true;
    } else {
        std::cout << "This member has not borrowed this book.\n";
        return false;
    }
}

void Library::listOverdueBooks() {
    std::time_t now = std::time(nullptr);
    std::cout << "\n--- Overdue Books Report ---\n";
    bool anyOverdue = false;

    for (const auto& pair : members) {
        const Member& member = pair.second;
        for (const auto& info : member.getBorrowedBooks()) {
            if (info.dueDate < now) {
                // Book is overdue
                std::string bookTitle = "Unknown Title";
                if (books.find(info.isbn) != books.end()) {
                    bookTitle = books.at(info.isbn).getTitle();
                }

                std::cout << "Member: " << member.getName() << " (ID: " << member.getId() << ")\n";
                std::cout << "  Book: " << bookTitle << " (ISBN: " << info.isbn << ")\n";
                
                // Optional: Show how many days overdue
                double secondsOverdue = std::difftime(now, info.dueDate);
                int daysOverdue = static_cast<int>(secondsOverdue / (60 * 60 * 24));
                std::cout << "  Days Overdue: " << daysOverdue << "\n";
                anyOverdue = true;
            }
        }
    }

    if (!anyOverdue) {
        std::cout << "No overdue books found.\n";
    }
    std::cout << "----------------------------\n";
}

void Library::listMostBorrowedBooks() {
    std::vector<Book> allBooks;
    for (const auto& pair : books) {
        allBooks.push_back(pair.second);
    }

    // Sort descending by borrow count
    std::sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {
        return a.getBorrowCount() > b.getBorrowCount();
    });

    std::cout << "\n--- Most Borrowed Books Report ---\n";
    for (const auto& book : allBooks) {
        if (book.getBorrowCount() > 0) {
             std::cout << book.getTitle() << " by " << book.getAuthor() 
                       << " - Borrowed " << book.getBorrowCount() << " times.\n";
        }
    }
    std::cout << "----------------------------------\n";
}

void Library::displayAllBooks() {
    std::cout << "\n--- Library Catalog ---\n";
    for (const auto& pair : books) {
        const Book& b = pair.second;
        std::cout << "Title: " << b.getTitle() 
                  << " | Author: " << b.getAuthor()
                  << " | ISBN: " << b.getISBN()
                  << " | Available: " << b.getAvailableCopies() << "/" << b.getTotalCopies() << "\n";
    }
    std::cout << "-----------------------\n";
}
