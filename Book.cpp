#include "Book.h"

Book::Book(std::string title, std::string author, std::string isbn, int copies)
    : title(std::move(title)), author(std::move(author)), isbn(std::move(isbn)), 
      totalCopies(copies), availableCopies(copies), borrowCount(0) {}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getISBN() const { return isbn; }
int Book::getAvailableCopies() const { return availableCopies; }
int Book::getTotalCopies() const { return totalCopies; }
int Book::getBorrowCount() const { return borrowCount; }

bool Book::borrowCopy() {
    if (availableCopies > 0) {
        availableCopies--;
        borrowCount++;
        return true;
    }
    return false;
}

void Book::returnCopy() {
    if (availableCopies < totalCopies) {
        availableCopies++;
    }
}
