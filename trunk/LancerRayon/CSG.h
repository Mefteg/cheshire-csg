#ifndef CSG_H
#define CSG_H

#include "Objet3D.hpp"


class CSG: public Objet3D
{
        protected:
                Objet3D *obj1;
                Objet3D *obj2;
                char op;         //pour savoir quelle operation effectuer sur la liste des objets

        public:
                CSG(Objet3D *o1, Objet3D* o2, char c){
                        obj1 = o1;
                        obj2 = o2;
                        op = c;
                };

                //lecture :
                Objet3D objet1(){
                        return *obj1;
                }
                Objet3D objet2(){
                        return *obj2;
                }
                char operation(){
                        return op;
                }

                //ecriture :
                void objet1(Objet3D *o){
                        obj1 = o;
                }
                void objet2(Objet3D *o){
                        obj2 = o;
                }
                void operation(char c){
                        op = c;
                }

                bool calculIntersection(const Rayon & ,Intersection &);

};

#endif // CSG_H
