#include <assert.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Admin.h"
#include "Book.h"
#include "BookDetails.h"
#include "User.h"
class UsersManager {
   public:
    UsersManager() : users{}, current_user{} {
    }
    void add_user(std::string username, std::string password, std::string email) {
        User new_user(username, password, email);
        users.push_back(new_user);
        current_user = users[0];
    }
    bool log_in(std::string username, std::string password) {
        for (User& check_user : users) {
            if (username == check_user.get_user_name() &&
                check_user.check_password(password)) {
                current_user = check_user;
                return true;
            }
        }
        return false;
    }
    User& get_current_user() {
        return current_user;
    }

   private:
    std::vector<User> users;
    User current_user;
};
class HelperAdmin {
   public:
    HelperAdmin() : admins{}, current_admin{}, admin_password{} {
        Admin admin{"mostafa", "111"};
        admins.push_back(admin);
    }
    bool check_admin(std::string Username, std::string Password) {
        for (Admin& admin : admins) {
            if (admin.check_account(Username, Password)) {
                current_admin = admin;
                admin_password = Password;
                return true;
            }
        }
        return false;
    }
    Admin& get_admin() {
        return current_admin;
    }
    std::string get_admin_password() {
        return admin_password;
    }

   private:
    std::vector<Admin> admins;
    Admin current_admin;
    std::string admin_password;
};
class BooksManager {
   public:
    BooksManager() : books{} {
    }
    bool add_new_book(std::string admin_username, std::string admin_password,
                      Book book_to_add) {
        HelperAdmin helper;
        if (helper.check_admin(admin_username, admin_password)) {
            books.push_back(book_to_add);
            return true;
        }
        return false;
    }
    const std::deque<Book>& get_books() {
        return books;
    }
    std::optional<Book> get_book_by_id(int id) {
        for (Book& cur_book : books) {
            if (cur_book.get_id() == id) {
                return std::optional<Book>(cur_book);
            }
        }
        return std::optional<Book>();
    }

   private:
    std::deque<Book> books;
};
class SessionManagement {
   public:
    SessionManagement() : sessions{} {
    }
    std::string GetCurrentTimeDate() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }
    void create_session(int book_id) {
        std::string dateTime = GetCurrentTimeDate();
        BookDetails details = sessions[book_id];
        details.set_date(dateTime);
        sessions[book_id] = details;
    }
    void update_session(int book_id,int new_page) {
        std::string dateTime = GetCurrentTimeDate();
        BookDetails details{dateTime,new_page};
        sessions[book_id] = details;
    }
    BookDetails& update_book_details(int book_id) {
        return sessions[book_id];
    }
    
    const std::unordered_map<int, BookDetails>& get_sessions() {
        return sessions;
    }

   private:
    std::unordered_map<int, BookDetails> sessions;
};
class OnlineReader {
   public:
    OnlineReader() = default;
    bool LoginUser() {
        int prompt = -1;
        int logged_in = 0;
        while (logged_in == 0) {
            std::cout << "      "
                      << "1: Login" << std::endl;
            std::cout << "      "
                      << "2: Sign up" << std::endl;
            std::cout << "Enter Numbers in range 1-2: ";
            std::cin >> prompt;
            switch (prompt) {
                case 1: {
                    std::string username, password;
                    std::cout << "Enter User name: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;
                    if (!usersmanager.log_in(username, password)) {
                        if (adminHelper.check_admin(username, password))
                            logged_in = 2;
                        else
                            std::cout << "Wrong Log-in details" << std::endl;
                    } else
                        logged_in = 1;
                    break;
                }
                case 2: {
                    std::string username, password, email;
                    std::cout << "Enter User name: ";
                    std::cin >> username;
                    std::cout << "Enter password: ";
                    std::cin >> password;
                    std::cout << "Enter email: ";
                    std::cin >> email;
                    usersmanager.add_user(username, password, email);
                    break;
                }
                default:
                    break;
            }
        }
        return logged_in == 2;
    }
    void WelcomeScreen(bool is_admin) {
        if (is_admin) {
            std::cout << "Hello " << adminHelper.get_admin().get_user_name()
                      << "| Admin View" << std::endl;
            std::cout << "Menu: " << std::endl;
            std::cout << "      1: View Profile" << std::endl;
            std::cout << "      2: Add Book" << std::endl;
            std::cout << "      3: Log out" << std::endl;
            std::cout << "Enter number in range 1-3: ";
        } else {
            std::cout << "Hello " << usersmanager.get_current_user().get_user_name()
                      << "| User View" << std::endl;

            std::cout << "Menu: " << std::endl;
            std::cout << "      1: View Profile" << std::endl;
            std::cout << "      2: List & select from My Reading History" << std::endl;
            std::cout << "      3: List & Select from Available books" << std::endl;
            std::cout << "      4: Log out" << std::endl;
            std::cout << "Enter number in range 1-4: ";
        }
    }
    void viewProfileScreen(bool is_admin) {
        std::string username, email;
        if (is_admin) {
            username = adminHelper.get_admin().get_user_name();
            std::cout << "Admin Name: " << username
                      << std::endl;
        } else {
            username = usersmanager.get_current_user().get_user_name();
            email = usersmanager.get_current_user().get_email();
            std::cout << "User Name: " << username
                      << std::endl;
            std::cout << "Email: " << email
                      << std::endl;
        }
    }
    void print_book_page(Book book_to_print, int page) {
        std::cout << "Current Page: " << page << "/"
                  << book_to_print.get_pages().size() << std::endl;
        size_t index = page - 1;
        std::cout << book_to_print.get_pages().at(index) << std::endl;
    }
    int bookprompt() {
        std::cout << "Menu:" << std::endl;
        std::cout << "      1: Next Page" << std::endl;
        std::cout << "      2: Previous Page" << std::endl;
        std::cout << "      3: Stop Reading" << std::endl;
        std::cout << "Enter number in range 1-3: ";
        int prompt_book = 0;
        std::cin >> prompt_book;
        return prompt_book;
    }
    void bookReaderScreen(Book book_to_read, BookDetails& details_to_update) {
        const std::deque<std::string>& book_pages = book_to_read.get_pages();

        unsigned int current_page = details_to_update.get_current_page();
        assert(current_page >= 1 && current_page <= book_pages.size());

        print_book_page(book_to_read, current_page);

        int prompt = bookprompt();

        while (prompt != 3 && prompt > 0) {
            switch (prompt) {
                case 1:
                    if (current_page == book_pages.size()) {
                        print_book_page(book_to_read, current_page);
                        std::cout << "reached last page! " << std::endl;
                    } else
                        print_book_page(book_to_read, ++current_page);
                    break;
                case 2:
                    if (current_page == 1) {
                        print_book_page(book_to_read, current_page);
                        std::cout << "first page! " << std::endl;
                    } else
                        print_book_page(book_to_read, --current_page);
                    break;
                default:
                    break;
            }
           // update session
           sessionsmanager.update_session(book_to_read.get_id(),current_page);
           prompt = bookprompt();
        }
    }
    void avaialableBooksScreen() {
        const std::deque<Book>& books = booksmanager.get_books();
        if (books.size() == 0) {
            std::cout << "sorry, no books are available" << std::endl;
            return;
        }
        std::cout << "Our current book collection: " << std::endl;
        int index = 1;
        for (const Book& book : books) {
            std::cout << index << ": " << book.get_name() << std::endl;
            index++;
        }
        std::cout << "Which book would you like to read?: ";
        std::cout << "Enter numbers in range 1-" << books.size() << " (-1 to cancel): ";

        unsigned int book_number = 0;
        std::cin >> book_number;

        if (book_number != -1 && book_number > 0 && book_number <= books.size()) {
            int id = books[book_number - 1].get_id();
            sessionsmanager.create_session(id);
            BookDetails& details = sessionsmanager.update_book_details(id);
            bookReaderScreen(books[book_number - 1], details);
        }
    }
    void add_bookScreen() {
        std::cout << "Enter book name: ";
        std::string book_name;
        std::cin >> book_name;

        std::cout << "Enter book id: ";
        int book_id;
        std::cin >> book_id;

        std::cout << "Enter how many pages: ";
        unsigned int number_of_pages = 0, current_page = 1;
        std::cin >> number_of_pages;

        std::deque<std::string> pages(number_of_pages);
        while (current_page <= number_of_pages) {
            std::cout << "Enter page # " << current_page << ": ";
            std::string page;
            std::cin >> page;

            pages[current_page - 1] = page;
            current_page++;
        }

        Book book_to_add{book_name, pages, book_id};
        booksmanager.add_new_book(adminHelper.get_admin().get_user_name(),
                                  adminHelper.get_admin_password(),
                                  book_to_add);
    }
    void historyScreen() {
        const std::unordered_map<int, BookDetails>& session =
            sessionsmanager.get_sessions();
        std::vector<Book> books;
        for (auto& it : session) {
            std::optional<Book> book = booksmanager.get_book_by_id(it.first);
            if (book)
                books.push_back(*book);
        }
        if(books.size() == 0){
            std::cout << "sorry, no available books in history! " << std::endl;
            return;
        }
        int index = 0;
        for (Book book : books) {
            int book_size = book.get_pages().size();
            const BookDetails& book_details =
                sessionsmanager.update_book_details(book.get_id());
            std::cout << ++index << ": " << book.get_name() << " Page: "
                      << book_details.get_current_page() << '/' << book_size << " - "
                      << book_details.get_date() << std::endl;
        }
        std::cout << "Which session to open?: " << std::endl;
        std::cout << "Enter numbers in range: 1 - " << books.size() << std::endl;
        int session_number = 0;
        std::cin >> session_number;
        if (session_number > 0 && session_number <= books.size()) {
            Book book_to_read = books.at(session_number - 1);
            sessionsmanager.create_session(book_to_read.get_id());
            BookDetails& details = sessionsmanager.update_book_details(book_to_read.get_id());
            bookReaderScreen(book_to_read, details);
        }
    }
    void MainSystem() {
        WelcomeScreen(false);
        int prompt = -1;
        while (std::cin >> prompt && prompt > 0 && prompt < 4) {
            switch (prompt) {
                case 1:
                    viewProfileScreen(false);
                    break;
                case 2:
                    historyScreen();
                    break;
                case 3:
                    avaialableBooksScreen();
                    break;
                default:
                    break;
            }
            WelcomeScreen(false);
        }
    }
    void AdminSystem() {
        WelcomeScreen(true);
        int prompt = -1;
        while (std::cin >> prompt && prompt > 0 && prompt < 3) {
            switch (prompt) {
                case 1:
                    viewProfileScreen(true);
                    break;
                case 2:
                    add_bookScreen();
                    break;
                default:
                    break;
            }
            WelcomeScreen(true);
        }
    }
    void Run() {
        while (true) {
            // user logged in, not an admin
            if (!LoginUser()) {
                MainSystem();
            } else {
                AdminSystem();
            }
        }
    }

   private:
    UsersManager usersmanager{};
    HelperAdmin adminHelper{};
    BooksManager booksmanager{};
    SessionManagement sessionsmanager{};
};
int main() {
    OnlineReader readerSystem{};
    readerSystem.Run();
    return EXIT_SUCCESS;
}