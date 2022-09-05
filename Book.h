#include  <string>
#include <deque>
class Book {
public:
    Book() = default;
    Book(std::string book_name,int book_id);
    Book(std::string book_name,std::deque<std::string> Pages,int book_id);
    
    std::string get_name() const;
    
    int get_id() const;
    
    std::deque<std::string> get_pages() const;

    void add_page(std::string new_page);

private:
    std::string name;
    std::deque<std::string> pages{};
    int id{};  
};
