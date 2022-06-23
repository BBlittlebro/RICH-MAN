#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "WorldMap.h"
//#define current_unit map.Get_unit(Players[current_player].Get_location())

//================================
//dice random
//================================
const int dice()
{
    srand(time(NULL));
    int dice = rand()%6+1;
    return dice;
}


int main(){
    //================================
    //local data
    //================================
    const int MaxLv = 5, Init = -1;
    WorldMap map;
    int player_num = 0,current_player=0;
    bool isEnd = 0;
    Player Players[4];
    std::string player_name[4]={};
    std::string default_player_name[4]={"A-Tu","Little-Mei","King-Baby","Mrs.Money"};

    //================================
    //set map ,number of player and name
    //================================
    std::cout<<"How many players? (Maximum:4)...>";
    std::cin>>player_num;
    std::cin.ignore();
    for(int i=0;i<player_num;i++)
    {
        std::string player_name;
        std::cout<<"Please input player "<<i+1<<"'s name (Default: "<<default_player_name[i]<<")...>";
        getline(std::cin,player_name);
        if(player_name=="")  player_name = default_player_name[i];
        Players[i] = player_name;
    }
    //system("cls");
    map.Create_Map();                   //讀取檔案，建立地圖
    map.Set_player_num(player_num);     //設定玩家數量

    //================================
    //entering the game
    //================================
    while(!isEnd)
    {
        map.Display();
        std::string player_action;
        if(!Players[current_player].Is_survive())
        {
            current_player = (current_player+1)%player_num;
            continue; //if player don't exist
        }
        for(int i=0;i<player_num;i++)
        {
            if(i==current_player)
            {
                std::cout<<"=>";
                Players[i].Display();
            }
            else
            {
                std::cout<<"  ";
                Players[i].Display();
            }
        }
        //================================
        //dice and move
        //================================
        if(Players[current_player].isFrozen())
        {
            Players[current_player].Set_frozen(false);
            std::cout<<Players[current_player].Get_name()<<", you are at jail."<<std::endl;
            system("pause");
        }
        else
        {
            std::cout<<std::endl<<Players[current_player].Get_name()<<", your action? (1:Dice [default] / 2:Exit)...>";
            getline(std::cin,player_action);
            if(player_action=="2") isEnd = 1;
            else
            {
                //decide next pos
                int new_pos = (dice()+Players[current_player].Get_location());
                if(new_pos>=map.Get_number_units()) //reach start point
                {
                    Players[current_player].Start_reward();
                    new_pos = new_pos%(map.Get_number_units());
                }
                Players[current_player].Set_location(new_pos);
                map.Set_player_location(current_player,new_pos);
                //system("cls");

                //refresh
                map.Display();
                for(int i=0;i<player_num;i++)
                {
                    if(i==current_player&&Players[current_player].Get_location()!=Init)
                    {
                        std::cout<<"=>";
                        Players[i].Display();
                    }
                    else if(Players[current_player].Get_location()!=Init)
                    {
                        std::cout<<"  ";
                        Players[i].Display();
                    }
                }
                MapUnit* current_unit = map.Get_unit(Players[current_player].Get_location());


                if(current_unit->Host()==Init)
                {
                    if(current_unit->Type()=='J')
                    {
                        Players[current_player].Set_frozen(true);
                    }
                    else
                    {
                        std::cout<<Players[current_player].Get_name()<<", do you want to buy "<<current_unit->Name()<<"? ";
                        std::cout<<"(1: Yes [default] / 2: No) ...>";
                        getline(std::cin,player_action);
                        if(player_action!="2")
                        {
                            std::cout<<"You pay $"<<current_unit->Price()<<" to buy "<<current_unit->Name()<<std::endl;
                            Players[current_player].Pay_money(current_unit->Price());
                            current_unit->SetHost(current_player);
                            system("pause");
                        }
                    }
                }
                else
                {
                    if(current_unit->Host()==Players[current_player].Get_id())
                    {
                        if(current_unit->Type()=='U')
                        {
                            if(Players[current_player].Get_money()>current_unit->UpPrice())
                            std::cout<<Players[current_player].Get_name()<<", do you want to upgrade "<<current_unit->Name()<<"? ";
                            std::cout<<"(1: Yes [default] / 2: No) ...>";
                            getline(std::cin,player_action);
                            if(player_action!="2")
                            {
                                if(current_unit->Level()==MaxLv)
                                {
                                    std::cout<<Players[current_player].Get_name()<<"your "<<current_unit->Name()<<"already reaches the highest level!";
                                    system("pause");
                                }
                                else
                                {
                                    current_unit->SetLevel(current_unit->Level()+1);
                                    Players[current_player].Pay_money(current_unit->UpPrice());
                                    std::cout<<"You pay $"<<current_unit->UpPrice()<<" to upgrade "<<current_unit->Name();
                                    std::cout<<"to Lv."<<current_unit->Level()<<std::endl;
                                    system("pause");
                                }
                            }
                        }
                    }
                    else
                    {
                        if(current_unit->Type()=='U')
                        {
                            int fine = current_unit->Fine();
                            std::cout<<"Ufine"<<fine<<std::endl;
                            if(Players[current_player].Get_money()<fine)
                            {
                                std::cout<<Players[current_player].Get_name()<<", you must pay $"<<fine<<" to Player ";
                                std::cout<<current_unit->Host()<<" ("<<Players[current_unit->Host()].Get_name()<<")"<<std::endl;
                                Players[current_player].Pay_money(Players[current_unit->Host()],Players[current_player].Get_money());
                                Players[current_player].Set_location(Init);
                            }
                            else
                            {
                                std::cout<<Players[current_player].Get_name()<<", you must pay $"<<fine<<" to Player ";
                                std::cout<<current_unit->Host()<<" ("<<Players[current_unit->Host()].Get_name()<<")"<<std::endl;
                                Players[current_player].Pay_money(Players[current_unit->Host()],fine);
                            }
                            system("pause");
                        }
                        else if(current_unit->Type()=='C')
                        {
                            int fine = current_unit->Fine()*Players[current_player].Get_num_units();
                            std::cout<<"Cfine"<<fine<<std::endl;
                            if(Players[current_player].Get_money()<fine)
                            {
                                std::cout<<Players[current_player].Get_name()<<", you must pay $"<<fine<<" to Player ";
                                std::cout<<current_unit->Host()<<" ("<<Players[current_unit->Host()].Get_name()<<")"<<std::endl;
                                Players[current_player].Pay_money(Players[current_unit->Host()],Players[current_player].Get_money());
                                Players[current_player].Set_location(Init);
                            }
                            else
                            {
                                std::cout<<Players[current_player].Get_name()<<", you must pay $"<<fine<<" to Player ";
                                std::cout<<current_unit->Host()<<" ("<<Players[current_unit->Host()].Get_name()<<")"<<std::endl;
                                Players[current_player].Pay_money(Players[current_unit->Host()],fine);
                            }
                            system("pause");
                        }
                        else if(current_unit->Type()=='R')
                        {
                            int fine = current_unit->Fine()*dice();
                            std::cout<<"Rfine"<<fine<<std::endl;
                            if(Players[current_player].Get_money()<fine)
                            {
                                std::cout<<Players[current_player].Get_name()<<", you must pay $"<<fine<<" to Player ";
                                std::cout<<current_unit->Host()<<" ("<<Players[current_unit->Host()].Get_name()<<")"<<std::endl;
                                Players[current_player].Pay_money(Players[current_unit->Host()],Players[current_player].Get_money());
                                Players[current_player].Set_location(Init);
                            }
                            else
                            {
                                std::cout<<Players[current_player].Get_name()<<", you must pay $"<<fine<<" to Player ";
                                std::cout<<current_unit->Host()<<" ("<<Players[current_unit->Host()].Get_name()<<")"<<std::endl;
                                Players[current_player].Pay_money(Players[current_unit->Host()],fine);
                            }
                            system("pause");
                        }
                    }
                }
            }
        }
        //system("cls");
        current_player = (current_player+1)%player_num;
        int player_survive = player_num;
        for(int i=0;i<player_num;i++)
        {
            if(!Players[i].Is_survive())
            {
                int unit_num = map.Get_number_units();
                for(int j=0;j<unit_num;j++)
                {
                    if(map.Get_unit(j)->Host()==i)
                    {
                        map.Get_unit(j)->SetHost(Init);
                        map.Get_unit(j)->SetLevel(0);
                    }
                }
                player_survive --;
            }
        }
        if(player_survive==1)
            isEnd = 1;
    }
    std::cout<<"The winner is determined!"<<std::endl;
    system("pause");
    return 0;
}
