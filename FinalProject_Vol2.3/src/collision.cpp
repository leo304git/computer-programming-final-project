
// false if collide ; true is does not collide ; 
bool operator ^ (Humanoid1& , Humanoid2& ){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = Humanoid1.getPosX() ;
    rightA = Humanoid1.getPosX()+Humanoid1.getMWidth() ;
    topA = Humanoid1.getPosY() ;
    bottomA =Humanoid1.getPosY()+Humanoid1.getMheight()  ;

    leftB = Humanoid2.getPosX();
    rightB = Humanoid1.getPosX() + Humanoid2.getMwidth();
    topB =  Humanoid2.getPosY();
    bottomB = Humanoid2.getPosY() + Humanoid2.getMWidth() ;
     
     if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;

   


}
