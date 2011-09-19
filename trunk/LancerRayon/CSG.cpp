#include "CSG.h"

bool CSG::calculIntersection(const Rayon &ray ,Intersection &i){
        if(op == 'u'){
                //cas union
                Intersection *inter = new Intersection();
                if(obj1->calculIntersection(ray , i) || obj2->calculIntersection(ray , i))
                {       //si intersection avec au moins un des 2 ojb => union
                        if(obj1->calculIntersection(ray, *inter) && obj2->calculIntersection(ray,i)){
                                // si intersection avec les 2 => on doit renvoyer le plus proche
                                if(i>*inter)
                                        i = *inter;
                        }
                        return true;
                }
        }else{
                if(op == 'i' ){
                        //cas intersection
                        if(obj1->calculIntersection(ray , i) && obj2->calculIntersection(ray , i))
                                return true;
                }else{
                        if( op == 'd' ){
                                //cas difference
                                //difference = obj1 - obj2
                                if( obj1->calculIntersection(ray , i) && !obj2->calculIntersection(ray , i) )
                                        return true;
                        }
                }
        }
        return false;
}
