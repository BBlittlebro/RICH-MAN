#include <string>

class Player
{
public:
    Player();
    Player(std::string name);
    int Get_id() const;                         //回傳 ID
    const std::string Get_name() const;               //回傳 name
    int Get_location() const;                   //回傳位置
    int Get_money() const;                      //回傳金錢
    int Get_num_units() const;                  //回傳目前擁有建築物單位
    void Pay_money(int money);                  //用於買房子
    void Pay_money(Player &name ,int money);    //用於踩到地給對方錢
    bool Is_survive() const;                    //判斷是否存活
    void Start_reward();                        //回到終點獲得 2000 元
    void Display() const;                       //展示玩家資料
    void Set_location(int location);            //設定玩家位置
    void Set_frozen(int isFrozen);
    void Set_num_nuits(int num_units);
    int isFrozen() const;
    Player & operator = (std::string name);
protected:
    static int index;
    int id_ = -1;
    std::string name_;
    int location_ = 0;
    int money_ = 30000;
    int num_units_ = 0;
    int isFrozen_ = 0;
};
