#include "User.h"

User::User(std::string user_Name,std::string Password,
                std::string Email) : user_name(user_Name), password(Password),
                 email(Email){
}
User::User(std::string user_Name,std::string Password) :
     user_name(user_Name), password(Password), email(""){
}
std::string User::get_email() const{
    return email;
}
std::string User::get_user_name() const{
    return user_name;
}
bool User::check_password(std::string Password) const{
    return (Password[0]==password[0] && password == Password);
}
