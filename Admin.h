#include  <string>
class Admin {
public:
    Admin();
    Admin(std::string user_Name,std::string Password);

    std::string get_user_name() const;
 
    bool check_account(std::string Username,std::string Password) const;
private:
    std::string user_name;
    std::string password;
    
};
