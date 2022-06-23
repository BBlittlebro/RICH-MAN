#ifndef CMapUnit_
#define CMapUnit_
#include <iostream>
#include <cstdlib>
#include <ctime>
constexpr int MaxLv = 5, Init = -1; //最高等級，初始參數
class MapUnit
{
public:
    MapUnit(const char name[] = "") //自動建立ID
    {
        name_ = name;
        id_ = index;
        index++;
    };
    virtual ~MapUnit(){};
    virtual void Display() const = 0;                      //印地圖
    virtual char Type() const = 0;                         //回傳形式(U,C,R,J)
    int Id() const { return id_; }                         //回傳ID
    int Price() const { return price_; }                   //回傳購買價格
    int Host() const { return host_; }                     //回傳擁有者
    std::string Name() const { return name_; }             //回傳名稱
    virtual int Fine() const { return fine_; }             //回傳罰金
    void SetPrice(const int price) { price_ = price; }     //設定購買價格
    void SetHost(const int host) { host_ = host; }         //設定擁有者
    virtual void SetFine(const int fine) { fine_ = fine; } //設定罰金
    virtual int Level() const { return Init; }
    virtual int UpPrice() const { return Init; }
    virtual void SetLevel(const int level) {}
    virtual void SetUpPrice(const int upprice) {}

private:
    static int index; // ID
    int id_ = Init, price_ = Init, host_ = Init, fine_ = Init;
    std::string name_ = "";
};
class UpUnit : public MapUnit
{
public:
    UpUnit(const char name[] = "") : MapUnit(name) {}
    virtual void Display() const;
    virtual int Level() const { return level_; }                             //土地等級
    virtual int UpPrice() const { return upgrade_price_; }                   //回傳升級價格
    virtual int Fine() const { return fine_list_[level_ - 1]; }              //回傳當前等級罰金
    virtual void SetLevel(const int level) { level_ = level; }               //設定土地等級
    virtual void SetFine(const int num[], const int n);                      //設定罰金陣列
    virtual void SetUpPrice(const int upprice) { upgrade_price_ = upprice; } //設定升級價格
    virtual char Type() const { return 'U'; }

private:
    int upgrade_price_ = Init, fine_list_[MaxLv], level_ = 0;
};
class ColUnit : public MapUnit
{
public:
    ColUnit(const char name[] = "") : MapUnit(name){};
    virtual void Display() const;
    virtual char Type() const { return 'C'; }

private:
};
class RandUnit : public MapUnit
{
public:
    RandUnit(const char name[] = "") : MapUnit(name){};
    virtual void Display() const;
    virtual char Type() const { return 'R'; }
    virtual int Fine() const; //回傳隨機罰金

private:
};
class JailUnit : public MapUnit
{
public:
    JailUnit(const char name[] = "") : MapUnit(name){};
    virtual void Display() const;
    virtual char Type() const { return 'J'; }

private:
};
#endif // CMapUnit_