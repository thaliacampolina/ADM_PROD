#ifndef PERIOD_398213921
#define PERIOD_398213921

#include <iostream>
using namespace std;

#define FIELDS (1+4+3+1)
#define TAB "\t"

class Period{
    public:
        // variables
        int demand;

        //  0- prod_normal
        //  1- extra_shift
        //  2- sub_contracting
        //  3- prod_demand
        int prod[4];

        // 0- stock_initial
        // 1- stock_final
        // 2- stock_delay
        int stock[3];
        float stock_mean;

        // functions
        Period(){
            setDemand(0);
            for(int i =0; i < 4; ++i){
                setProd(i, 0);
            }

            for(int i=0; i<3; ++i){
                setStock(i, 0);
            }

            setStockMean(0.0);
        }

        ~Period(){}

        Period(int demand, int prod_normal, int extra_shift,
                int sub_contract, int prod_demand, int stock_initial,
                int stock_final, float stock_mean, int stock_delay
                ){

            setDemand(demand);
            setProd(0, prod_normal);
            setProd(1, extra_shift);
            setProd(2, sub_contract);
            setProd(3, prod_demand);

            setStock(0, stock_initial);
            setStock(1, stock_final);
            setStockMean(stock_mean);
            setStock(2, stock_delay);
        }

        void setDemand(int demand){
            this->demand = demand;
        }

        void setProd(int offset, int value){
            this->prod[offset] = value;
        }

        void setStock(int offset, int value){
            this->stock[offset] = value;
        }

        void setStockMean(float stock_mean){
            this->stock_mean = stock_mean;
        }

        void print(int field){
            switch(field){
                // demand
                case 0:
                    cout << TAB << demand;
                break;

                // prod
                case 1:
                case 2:
                case 3:
                case 4:
                    cout << TAB << prod[field-1];
                break;

                // stock
                case 5:
                case 6:
                    cout << TAB << stock[field-5];
                break;
                case 7:
                    cout << TAB << stock_mean;
                break;
                case 8:
                    cout << TAB << stock[field-6];
                break;

            }
        }

        void printHeader(int field){
            switch(field){
                case 0:
                    cout << "Demanda" << TAB;
                break;

                case 1:
                    cout << "Produção:" << endl;
                    cout <<  "Normal" << TAB;
                break;

                case 2:
                    cout << "Turno Extra";
                break;

                case 3:
                    cout << "Subcontratação";
                break;

                case 4:
                    cout << "Prod - Demanda";
                break;

                case 5:
                    cout << endl <<  "Estoques" << endl;
                    cout <<  "Inicial" << TAB;
                break;

                case 6:
                    cout << "Final"<< TAB;;
                break;

                case 7:
                    cout << "Média"<< TAB;;
                break;

                case 8:
                    cout << "Atrasos"<< TAB;;
                break;
            }
        }
};

void pprint(Period* matrix, int size){
    // printing period
    cout << "Período" << TAB;
    for(int i =0; i< size; i++){
        cout << TAB << i +1 ;
    }
    cout << endl;

    // printing table
    for(int i=0; i< FIELDS; ++i){
        matrix[0].printHeader(i);
        for(int j=0; j< size; j++){
            matrix[j].print(i);
        }
        cout << endl;
    }
};

#endif
