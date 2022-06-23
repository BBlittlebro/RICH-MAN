#include "Player.h"

int Player::index = 0;

Player::Player(const char name[]):name_(name), id_(index){
    index++;
}
Player::Player(std::string name):name_(name.c_str()), id_(index){
    index++;
}

int Player::Get_id() const {return id_;}
const char* Player::Get_name() const {return name_;}
int Player::Get_location() const {return location_;}
int Player::Get_money() const {return money_;}
int Player::Get_num_units() const {return num_units_;}

void Player::Pay_money(int money){
    if(money_ < money){
        printf("Your money is lower than the price!\n");
    }else{
        money_ -= money;
        num_units_ += 1;
    }
}
void Player::Pay_money(Player &name ,int money){
    money_ -= money;
    name.money_ += money;

    if(money_ < 0){
        printf("Bankrupt!\n");
        location_ = -1;
        //歸還房屋
        num_units_ = 0;
    }
}
bool Player::Is_survive() const{
    if(location_ == -1){
        return false;   //die
    }else{
        return true;   //survive
    }
}
void Player::Start_reward(){
    money_ += 2000;
}
void Player::Display() const{
    printf("[%d]%17s  $%5d with %d units\n", id_, name_, money_, num_units_);
}
void Player::Set_location(int location){
    location_ = location;
}
Player & Player::operator = (const char name[]){
    name_ = name;
    return *this;
}
Player & Player::operator = (std::string name){
    name_ = name.c_str();
    return *this;
}
