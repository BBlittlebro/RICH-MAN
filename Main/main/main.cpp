#include <stdio.h>
#include "Player.h"
#include "WorldMap.h"
#include <iostream>

int main(){
    WorldMap map;
    map.Create_Map();                   //Ū���ɮסA�إߦa��
    map.Set_player_num(4);              //�]�w���a�ƶq

    Player P1(0, "Apple"), P2(1, "Banana"), P3(2, "Cookie"), P4(3, "Dog");      //�Ш���
    Player Players[4] = {P1, P2, P3, P4};   //���a�}�C

    while(1){
        map.Display();
        for(int i = 0; i < 4; ++i){
            Players[i].Display();
        }
        //�Y��l�A�R�Фl...�\��A�C�Y�@�����n�]��m
        map.Set_player_location(0,4);       //(Id, �s��m)

        //�d�ҡGú�@�� or �R�Фl()
        P1.Pay_money(P2, 2000);
    }
}
