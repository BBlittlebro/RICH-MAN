#include "CMapUnit.h"

class WorldMap
{
public:
    void Create_Map();                  //創建地圖
    void Display() const;               //展示地圖資訊
    void Set_number_units(int num);     //設置建築物數量
    int Get_number_units() const;       //取得建築物數量
    void Set_player_num(int num);       //設置玩家數量
    void Set_player_location(int player_id, int location);  //設置玩家位置
    MapUnit * Get_unit(int location);   //取得其中一個建築物 
private:
    MapUnit *units_[20] = {};
    int number_units = 0;
    int player_num = 0;
    int location_[4] = {0};
};
