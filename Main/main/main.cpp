#include <stdio.h>
#include "Player.h"
#include "WorldMap.h"
#include <iostream>

int main(){
    WorldMap map;
    map.Create_Map();                   //讀取檔案，建立地圖
    map.Set_player_num(4);              //設定玩家數量

    Player P1(0, "Apple"), P2(1, "Banana"), P3(2, "Cookie"), P4(3, "Dog");      //創角色
    Player Players[4] = {P1, P2, P3, P4};   //玩家陣列

    while(1){
        map.Display();
        for(int i = 0; i < 4; ++i){
            Players[i].Display();
        }
        //擲骰子，買房子...功能，每擲一次都要設位置
        map.Set_player_location(0,4);       //(Id, 新位置)

        //範例：繳罰鍰 or 買房子()
        P1.Pay_money(P2, 2000);
    }
}
