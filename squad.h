#pragma once
#include <allegro5/allegro5.h>
#include <string>

struct stats
{
    int damage;
    int hp;
    float speed;
    int gold_cost;
};

struct animation
{
	int maxFrame;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int attackDelay;
	ALLEGRO_BITMAP *image;
	int icon_number;
};

class Squad
{
    private:
        int level;                  //Poziom jednostki
        float experience;           //Punkty doswiadczenia ktore ma jednostka
        int gold_cost;              //Ile zlota kosztuje przywolanie jednej jednostki
        int FRACTION;
        //Taken from stats
        int damage;                 //Obrazenia ktore zadaje jednostka
        int hp;                     //Ilosc pkt zycia ktore posiada jednostka
        float speed;                //Szybkosc ruchu jednostki
        //Taken from anim
        int maxFrame;
        int frameDelay;
        int frameWidth;
        int frameHeight;
        int animationColumns;
        int attackDelay;
        int icon_number;


        //int unit_number;          //Aktualny stan osobowy squadu
        //int max_unit_number;      //Maksymalny stan osobowy squadu
        //float squad_reinforce;    //Ile unitow przybywa miedzy misjami

    public:
        Squad(int FRACTION, stats sq_stat, animation sq_anim);
        //Public visibility
        stats *squad_stat; //Pointer do bazowych statow jednostki
        animation *squad_anim; //Pointer do IMG oraz informacji o animacji jednostki
        ALLEGRO_BITMAP *image;
        //Setters:
        void AwardSquadXP(int var) {experience += var;}
        //Getters:
        float GetSquadXP() {return experience;}
        float GetSpeed() {return speed;}
        int GetGoldCost() {return gold_cost;}
        int GetDamage() {return damage;}
        int GetHp() {return hp;}
        int GetMaxFrame() {return maxFrame;}
        int GetFrameDelay() {return frameDelay;}
        int GetFrameWidth() {return frameWidth;}
        int GetFrameHeight() {return frameHeight;}
        int GetAnimationColumns() {return animationColumns;}
        int GetFraction() {return FRACTION;}
        int GetAttackDelay() {return attackDelay;}
        int GetIconNumber() {return icon_number;}

        //Other:
        bool CheckLevel(); //Sprawdza, czy exp > exp potrzebny do nastepnego levelu i awarduje level.
        void UpdateStats(); //Updatuje staty(zmiany eq lub level upy)
        //bool isDeploying; //Jesli jest isDeploying to znika z listy do deploy
        //bool isSelected; //Jesli jest wybrane, to pokazuje staty i img wybranego Squada
};

