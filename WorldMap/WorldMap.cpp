#include "WorldMap.h"
#include <stdio.h>
#include <string.h>

void WorldMap::Create_Map(){
    FILE *fp;
    fp = fopen("map.dat", "r");

    char temp[101] = {};
    int unit_index = 0;
    while(fgets(temp, 100, fp) != NULL){        //讀檔案
        int money_index = 0;
        int temp_money[7] = {};
        char type_and_name[2][10] = {};
        char *token;
        const char s[4] = "\t \n";
        token = strtok(temp, s);
        strncpy(type_and_name[0], token, 1);    //存類型
        while(token != NULL){
            //printf(":%s\n", token);
            token = strtok(NULL, s);
            if(token == NULL){
                break;
            }
            //如果沒名字就先存名字，否則存金額
            if(type_and_name[1][0] == '\0'){    
                strncpy(type_and_name[1], token, strlen(token));
            }else{
                //printf("%d\n", atoi(token));
                temp_money[money_index] = atoi(token);
                money_index += 1;
            }
        }
        
        //根據不同類型，建立不同建築物
        if(type_and_name[0][0] == 'U'){
            units_[unit_index] = new UpUnit(type_and_name[1]);
            units_[unit_index]->SetPrice(temp_money[0]);
            units_[unit_index]->SetUpPrice(temp_money[1]);
            for(int i = 2; i < 7; ++i){
                units_[unit_index]->SetFine(temp_money[i]);
            }
        }else if(type_and_name[0][0] == 'C'){
            units_[unit_index] = new ColUnit(type_and_name[1]);
            units_[unit_index]->SetPrice(temp_money[0]);
            units_[unit_index]->SetFine(temp_money[1]);
        }else if(type_and_name[0][0] == 'R'){
            units_[unit_index] = new RandUnit(type_and_name[1]);
            units_[unit_index]->SetPrice(temp_money[0]);
            units_[unit_index]->SetFine(temp_money[1]);
        }else if(type_and_name[0][0] == 'J'){
            units_[unit_index] = new JailUnit(type_and_name[1]);
        }
        
        unit_index += 1;

        //清空暫存
        for(int i = 0; i < 7; ++i) { temp_money[i] = 0; }
        for(int i = 0; i < 10; ++i) { type_and_name[1][i] = '\0'; }
        money_index = 0;
    }
    Set_number_units(unit_index);
    fclose(fp);
}

void WorldMap::Display() const{
    int number_units = Get_number_units();
    for(int i = 0; i < number_units/2; ++i){
        //前半部
        printf("=");
        for(int j = 0; j < player_num; ++j){
            if(location_[j] == i){              //玩家目前在此位置
                printf("%d", j);
            }else{
                printf(" ");
            }
        }
        printf("=");
        units_[i]->Display();

        //後半部
        printf("=");
        for(int j = 0; j < player_num; ++j){
            if(location_[j] == (number_units-1 -i)){              //玩家目前在此位置
                printf("%d", j);
            }else{
                printf(" ");
            }
        }
        printf("=");
        units_[number_units-1 -i]->Display();
        printf("\n");
    }
}
void WorldMap::Set_number_units(int num) {number_units = num; }
int WorldMap::Get_number_units() const {return number_units; }
void WorldMap::Set_player_num(int num) {player_num = num; }
void WorldMap::Set_player_location(int player_id, int location) {location_[player_id] = location; }
MapUnit * WorldMap::Get_unit(int location) {return units_[location]; }
