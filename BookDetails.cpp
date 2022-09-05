#include "BookDetails.h"
BookDetails::BookDetails(std::string bookDate,int lastreadPage) : date(bookDate), 
    current_page (lastreadPage){

}
BookDetails::BookDetails(std::string bookDate) : date(bookDate), current_page(1){
}
std::string BookDetails::get_date() const{
    return date;
}
int BookDetails::get_current_page() const{
    return current_page;
}
void BookDetails::set_date(std::string new_date){
    date = new_date;
}
void BookDetails::set_current_page(int new_page){
    current_page = new_page;
}