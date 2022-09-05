#include "Admin.h"
bool Admin::check_account(std::string Username,std::string Password) const{
    if(Username == user_name && password == Password)
      return true;
    return false;
}
Admin::Admin() : user_name{}, password{}{

}
Admin::Admin(std::string user_Name,std::string Password) 
: user_name(user_Name), password(Password){

}
std::string Admin::get_user_name() const{
    return user_name;
}
