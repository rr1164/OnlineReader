#include  <string>
#include <deque>
class User {
public:
    User() : user_name{}, password{}, email{}{
        
    }
    User(std::string user_Name,std::string Password,
                std::string Email);
    User(std::string user_Name,std::string Password);
    std::string get_user_name() const;

    std::string get_email() const;
    
    bool check_password(std::string Password) const;
private:
    std::string user_name;
    std::string password;
    std::string email;
    
};
