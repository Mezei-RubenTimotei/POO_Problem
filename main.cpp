#include <iostream>
#include "Library.h"

int main() {
    Library lib;

    // 1. Setup Data
    std::cout << "--- Initializing Library System ---\n";
    lib.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "11111", 2));
    lib.addBook(Book("1984", "George Orwell", "22222", 2));
    lib.addBook(Book("C++ Programming", "Bjarne Stroustrup", "33333", 1));

    lib.registerMember(Member("Alice Smith", "M001"));
    lib.registerMember(Member("Bob Jones", "M002"));

    lib.displayAllBooks();

    // 2. Borrowing Logic
    std::cout << "\n--- Testing Borrowing ---\n";
    // Alice borrows Gatsby
    lib.issueBook("M001", "11111"); 
    
    // Bob borrows Gatsby
    lib.issueBook("M002", "11111"); 

    // Alice tries to borrow Gatsby again (Should fail due to stock, available 0)
    lib.issueBook("M001", "11111");

    // Borrow 1984 with negative days to simulate overdue
    std::cout << "\n--- Testing Overdue Logic ---\n";
    lib.issueBook("M001", "22222", -5); // Due 5 days ago

    lib.displayAllBooks();

    // 3. Reporting
    lib.listOverdueBooks();
    lib.listMostBorrowedBooks();

    // 4. Returning Logic
    std::cout << "\n--- Testing Returning ---\n";
    lib.returnBook("M001", "11111"); 
    lib.displayAllBooks();

    // Check reporting again
    lib.listMostBorrowedBooks();

    return 0;
}
