#include "inputData.h"
#include <fstream>
#include <sstream>
#include <iterator>

        inputData::inputData()
        {//ctor
        }

        void inputData::set_wallSet(int v){
            this->wallSet = v;
        }
        void inputData::set_painting(int v){
           this->painting = v;
        }
        void inputData::set_guards(int v){
            this->guards = v;
        }
        void inputData::set_wallNumber(int v){
            this->wallNumber = v;
        }

        int inputData::get_wallSet(){
            return wallSet;
        }
        int inputData::get_painting(){
            return painting;
        }
        int inputData::get_guards(){
            return guards;
        }
        int inputData::get_wallNumber(){
            return wallNumber;
        }
        std::vector<int> inputData::get_wall_EdgeArray(){
            return wall_EdgeArray;
        }

void inputData::readtext1(std::string s){
    std::ifstream infile(s.c_str());


    std::vector<int> val;
    int temp ;
    std::string line;
    std::stringstream ss;

    std::getline(infile,line);

    if(line.size() != 0){
        ss.clear();
        ss.str(line);
        while(ss>>temp){
            val.push_back(temp);
        }

    }


    this->set_wallSet(val[0]);
    this->set_painting(val[1]);
    this->set_guards(val[2]);


    //number of walls...
    int noOfwall;
    std::getline(infile,line);
    ss.clear();
    ss.str(line);
    while(ss>>temp){
        noOfwall = temp;
    }

    this->set_wallNumber(noOfwall);

}



    std::vector< std::vector<std::vector<int> > > inputData::get_wallSetVector(std::string st){
        int noOfwall = this->get_wallNumber();

        wall_EdgeArray.push_back(noOfwall);

        int wallset_num = this->get_wallSet();
        std::vector<std::vector<std::vector<int> > > finish;


        std::ifstream infile(st.c_str());
        int temp ;
        std::string line;
        std::stringstream ss;
        int dd=0;

        size_t f;

        std::getline(infile,line);
        std::getline(infile,line);



        for(int j=0;j < wallset_num;++j){
            std::vector<std::vector<int> >  wall_setV;

            for(int i = 0; i < noOfwall; ++i){
                //count line...
                ++dd;
                std::vector<int> inner_vec;
                std::getline(infile,line);

                if((line.find("s")) != std::string::npos){
                    f = line.find("s");
                    line.erase(f, 1);
                }else{
                    f = line.find("c");
                    line.erase(f, 1);
                }


                if(line.size() != 0){

                    ss.clear();
                    ss.str(line);
                    while(ss>>temp){
                        inner_vec.push_back(temp);
                    }
                }

                wall_setV.push_back(inner_vec);

            }

            finish.push_back(wall_setV);

            if(wallset_num>1 && j < wallset_num -1){
                std::getline(infile,line);
                noOfwall = std::atoi(line.c_str());
                //push back into the loop size vector...
                wall_EdgeArray.push_back(noOfwall);

                    ++dd;
            }
        }
        set_wallNumber(dd);
        return finish;
    }

 std::vector< std::vector<int> > inputData::get_paintVector(std::string st){

        std::ifstream infile(st.c_str());
        int paint_set = this->get_painting();
        int temp ;
        std::string line;
        std::stringstream ss;

        std::getline(infile,line);
        std::getline(infile,line);

        int loop = this->get_wallNumber();

        for(int i= 0;i < loop; ++i){
            std::getline(infile,line);
        }


        for(int i = 0; i < paint_set; ++i){

            std::vector<int> inner_vec;

            std::getline(infile,line);
            ss.clear();
            ss.str(line);
            while(ss>>temp){
                inner_vec.push_back(temp);
            }

            paint_setVector.push_back(inner_vec);

        }
        return paint_setVector;

    }


    std::vector< std::vector<int> > inputData::get_guardVector(std::string st){
        int guard_set = this->get_guards();
        std::ifstream infile(st.c_str());

        int temp ;
        std::string line;
        std::stringstream ss;

        std::getline(infile,line);
        std::getline(infile,line);


        int loop = this->get_wallNumber() + this->get_painting();

        for(int i= 0;i < loop; ++i){
            std::getline(infile,line);
        }

        for(int i = 0; i < guard_set; ++i){

            std::vector<int> inner_vec;
            std::getline(infile,line);
            ss.clear();
            ss.str(line);
            while(ss>>temp){
                inner_vec.push_back(temp);
            }

            guard_setVector.push_back(inner_vec);

        }
        return guard_setVector;
    }


void inputData::print_wallSet(std::vector< std::vector<std::vector<int> > >ws){
    for(auto it = ws.begin();it != ws.end();++it){
        for(auto jt = it->begin(); jt != it->end(); ++jt){
                for(auto ht = jt->begin();ht != jt->end();++ht){
                     std::cout<<*ht<<" ";
                }
            std::cout<<std::endl;

        }
        std::cout<<std::endl;
    }

}

void inputData::print_paintSet(std::vector< std::vector<int> > ps){
    for(std::vector< std::vector<int> >::iterator it = ps.begin();it != ps.end();++it){
        for(std::vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt){
            std::cout<<*jt<<" ";
        }
        std::cout<<std::endl;
    }

}

void inputData::print_guardSet(std::vector< std::vector<int> > gs){
    for(std::vector< std::vector<int> >::iterator it = gs.begin();it != gs.end();++it){
        for(std::vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt){
            std::cout<<*jt<<" ";
        }
        std::cout<<std::endl;

    }

}




inputData::~inputData()
{
    //dtor
}