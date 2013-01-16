#ifndef PERIOD_398213921
#define PERIOD_398213921

#include <iostream>
using namespace std;

#define FIELDS (1+4+3+1+5 +1)
#define TAB "\t"

class Period{
    public:
        // variables
        int demand;

        int prod_normal;
        int extra_shift;
        int sub_contraction;
        int prod_demand;

        int stock_initial;
        int stock_final;
        int stock_delay;
        float stock_mean;

        float cost_normal;
        float cost_extra_shift;
        float cost_subcontraction;
        float cost_stock;
        float cost_delay;

        // functions
        Period(){
            demand = 0;

            prod_normal = 0;
            extra_shift = 0;
            sub_contraction = 0;
            prod_demand = 0;

            stock_initial = 0;
            stock_final = 0;
            stock_delay = 0;
            stock_mean = 0.0;
 
            cost_normal = 0.0;
            cost_extra_shift = 0.0;
            cost_subcontraction = 0.0;
            cost_stock = 0.0;
            cost_delay = 0.0;
        }

        ~Period(){}

        float print(int field){
            switch(field){
                // demand
                case 0:
                    cout << TAB << demand;
                    return demand;
                break;

                // prod
                case 1:
                    cout << TAB << prod_normal;
                    return prod_normal;
                break;
                case 2:
                    cout << TAB << extra_shift;
                    return extra_shift;
                break;

                case 3:
                    cout << TAB << sub_contraction;
                    return sub_contraction;
                break;

                case 4:
                    cout << TAB << prod_demand;
                    return prod_demand;
                break;

                // stock
                case 5:
                    cout << TAB << stock_initial;
                    return stock_initial;
                break;
                case 6:
                    cout << TAB << stock_final;
                    return stock_final;
                break;

                case 7:
                    cout << TAB <<stock_mean;
                    return stock_mean;
                break;

                case 8:
                    cout << TAB <<stock_delay;
                    return stock_delay;
                break;

                // cost
                case 9:
                    cout << TAB << cost_normal;
                    return cost_normal;
                break;
                case 10:
                    cout << TAB << cost_extra_shift;
                    return cost_extra_shift;
                break;
                case 11:
                    cout << TAB << cost_subcontraction;
                    return cost_subcontraction;
                break;
                case 12:
                    cout << TAB << cost_stock;
                    return cost_stock;
                break;
                case 13:
                    cout << TAB << cost_delay;
                    return cost_delay;
                break;

                case 14:
                    cout << TAB << (cost_normal+cost_extra_shift
                                     +cost_subcontraction+cost_stock+cost_delay);
                    return (cost_normal+cost_extra_shift +cost_subcontraction+cost_stock+cost_delay);
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
                case 10:
                    cout << "Turno Extra";
                break;

                case 3:
                case 11:
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
                    cout << "Final"<< TAB;
                break;

                case 7:
                    cout << "Média"<< TAB;
                break;

                case 8:
                    cout << "Atrasos"<< TAB;
                break;

                case 9:
                    cout << endl << "Custos de Produção" << endl;
                    cout << "Normal"<< TAB;
                break;

                case 12:
                    cout << "Estoques";
                break;

                case 13:
                    cout << "Atrasos" << TAB;
                break;

                case 14:
                    cout << "Total R$ -->" ;
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
    cout << TAB  << "Total";
    cout << endl;

    // printing table
    for(int i=0; i< FIELDS; ++i){
        matrix[0].printHeader(i);
        float total = 0.0;
        for(int j=0; j< size; j++){
            total += matrix[j].print(i);
        }
        // imprime o total referente ao iéssimo campo
        cout << TAB << total;
        cout << endl;
    }
};

#endif
