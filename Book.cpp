#include "Book.h"
std::string Book::get_name() const{
    return name;
}
std::deque<std::string> Book::get_pages() const{
    return pages;
}
void Book::add_page(std::string new_page){
    pages.push_back(new_page);
}
int Book::get_id() const{
    return id;
}
Book::Book(std::string book_name,int book_id) : name(book_name), id(book_id){
}
Book::Book(std::string book_name,std::deque<std::string> Pages,int book_id) 
: name(book_name) , pages(Pages), id(book_id){
}