#pragma once
#include <string>

class Book {
public:
    Book() = default;
    Book(std::string title, std::string author, std::string isbn, int copies);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    int getAvailableCopies() const;
    int getTotalCopies() const;
    int getBorrowCount() const;

    bool borrowCopy();
    void returnCopy();

private:
    std::string title;
    std::string author;
    std::string isbn;
    int totalCopies;
    int availableCopies;
    int borrowCount;
};
