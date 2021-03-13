class mana{
    friend player ;
    public:
    mana();
    int check ( player&player) ;
    private:
    int total  = 100  ;
    int blood, ammo = 0   ;

};
mana::mana(){
    blood = 0 ;
    ammo = 0 ;
}
int  mana::check(player&player){
    if (player.blood>100) {
        player.ammo += 50 ;

    }
    else {
        player.blood += 50 ;
    }
}