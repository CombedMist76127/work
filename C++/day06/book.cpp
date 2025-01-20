#include <iostream>
#include <vector>
#include <string>
 
class Book {
public:
    Book(const std::string& title, const std::string& author) : title_(title), author_(author) {}
 
    void print() const {
        std::cout << "Title: " << title_ << "\nAuthor: " << author_ << std::endl;
    }
 
private:
    std::string title_;
    std::string author_;
};
 
class Library {
public:
    void addBook(const std::string& title, const std::string& author) {
        books_.push_back(Book(title, author));
    }
 
    void listBooks() const {
        for (const auto& book : books_) {
            book.print();
        }
    }
 
private:
    std::vector<Book> books_;
};
 
int main() {
    Library library;
    std::string title, author;
 
    while (true) {
        std::cout << "Enter 'add' to add a book, 'list' to list books, or 'exit' to quit: ";
        std::string command;
        std::cin >> command;
 
        if (command == "add") {
            std::cout << "Enter book title: ";
            std::cin >> title;
            std::cout << "Enter book author: ";
            std::cin >> author;
            library.addBook(title, author);
        } else if (command == "list") {
            library.listBooks();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
 
    return 0;
}
