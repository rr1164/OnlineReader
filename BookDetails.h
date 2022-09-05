#include  <string>

class BookDetails {
public:
    BookDetails(): date{}, current_page {1}{

    }
    
    BookDetails(std::string,int);

    BookDetails(std::string);
    
    std::string get_date() const;
    
    void set_date(std::string);
    
    void set_current_page(int);
    
    int get_current_page() const;
private:
    std::string date;
    int current_page;
};