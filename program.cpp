#include <iostream>
#include <vector>
using namespace std;
#include "period.cc"

int use_extra( int a, int b){
    if(a <= b){
        return a;
    }
    else{
        return b;
    }
}

int main() {



//**********************MENU*********************//

    //global
    int num_period;
    int num_normal_prod;
    float normal_prod_value;
    int extra_shift;
    int extra_shift_number;
    float extra_shift_value;
    int subcontract;
    int subcontract_number;
    float subcontract_value;
    int initial_stock;
    float stock_value;
    int delay;
    float delay_value;

    //each period
    vector<int> demand_vector;
    int num_demand;


    //global

    cout << "Digite a quantidade de _períodos_: ";	
    cin >> num_period;

    cout << "Digite a quantidade da _produção__normal_: ";	
    cin >> num_normal_prod;
    cout << "Digite o valor (custo) por unidade da _produção__normal_  (utilize ponto ao invés de vírgula, por ex 1.0) :"; 
    cin >> normal_prod_value;


    cout << "Digite 1 se houver possibilidade de _turno__extra_, 0 caso contrario: ";	
    cin >> extra_shift;
    if (extra_shift){
        cout << "Digite o numero maximo para o _turno__extra_: ";	
        cin >> extra_shift_number;
        cout << "Digite o valor (custo) por unidade do _turno__extra_  (utilize ponto ao invés de vírgula): ";	
        cin >> extra_shift_value;
    }

    cout << "Digite 1 se houver possibilidade de _subcontratação_, 0 caso contrario: ";	
    cin >> subcontract;
    if (subcontract){
        cout << "Digite o numero maximo para a _subcontratação_: ";	
        cin >> subcontract_number;
        cout << "Digite o valor (custo) por unidade da _subcontratação_  (utilize ponto ao invés de vírgula): ";	
        cin >> subcontract_value;
    }

    cout << "Digite a quantidade do _estoque_inicial_ (mínimo = 0) : ";	
    cin >> initial_stock;
    cout << "Digite o valor (custo) por unidade do _estoque_inicial_  (utilize ponto ao invés de vírgula): ";	
    cin >> stock_value;

    cout << "Digite 1 se houver possibilidade de ter _atrasos_, 0 caso contrario: ";	
    cin >> delay;
    cout << "Digite o valor (custo) por unidade dos _atrasos_  (utilize ponto ao invés de vírgula): ";	
    cin >> delay_value;



    //each period

    cout << endl << "Digite a quantidade da _demanda_ por período: " << endl << endl;	
    for (int i=1; i <= num_period; i++ ) { 
        cout << "_Demanda_ no Período " << i <<" :";
        cin >> num_demand;
        demand_vector.push_back(num_demand);
    }
//********************** END: MENU*********************//


    Period matrix[num_period+1];
    matrix[0].stock_initial = initial_stock;

    // setting all demands
    for(int i =0; i< num_period; ++i){
        // demanda
        matrix[i].demand = demand_vector[i];

        // producao normal
        matrix[i].prod_normal =  num_normal_prod;
    }

    // iteracoes
    for(int i =0; i< num_period; ++i){

        int demand = matrix[i].demand;
        int prod_normal = matrix[i].prod_normal;
        int stock_initial = matrix[i].stock_initial;

        int real_demand = 0;
        if( i == 0){
            real_demand = demand;
        }
        else{
            real_demand = demand + matrix[i-1].stock_delay;
        }

        if( real_demand < (prod_normal + stock_initial)){
            matrix[i].prod_demand = prod_normal - real_demand;
            int stock_final = (prod_normal + stock_initial) - real_demand;
            matrix[i].stock_final = stock_final;
            matrix[i].stock_mean = ( stock_initial + stock_final) / 2.0;
            matrix[i+1].stock_initial = stock_final;
        }
        else{
            int delay_2_remove = real_demand - prod_normal - stock_initial;

            if( extra_shift & subcontract){
                // extra shift
                if( extra_shift_value < subcontract_value){

                    int removed = use_extra(delay_2_remove, extra_shift_number);
                    matrix[i].extra_shift = removed;
                    delay_2_remove -= removed;

                    if(delay_2_remove > 0){

                        removed = use_extra(delay_2_remove, subcontract_number);
                        matrix[i].sub_contraction = removed;
                        delay_2_remove -= removed;

                        if(delay_2_remove > 0){
                            matrix[i].stock_delay = delay_2_remove;
                        }
                    }
                }
                else{ //subcontract
                    int removed = use_extra(delay_2_remove, subcontract_number);
                    matrix[i].sub_contraction = removed;
                    delay_2_remove -= removed;

                    if(delay_2_remove > 0){

                        removed = use_extra(delay_2_remove, extra_shift_number);
                        matrix[i].extra_shift = removed;
                        delay_2_remove -= removed;

                        if(delay_2_remove > 0){
                            matrix[i].stock_delay = delay_2_remove;
                        }
                    }
                }
            }
        }

        // custos
        matrix[i].cost_normal = normal_prod_value * num_normal_prod;
        matrix[i].cost_extra_shift = matrix[i].extra_shift * extra_shift_value;
        matrix[i].cost_subcontraction =  matrix[i].sub_contraction * subcontract_value;
        matrix[i].cost_stock = matrix[i].stock_mean * stock_value;
        matrix[i].cost_delay = matrix[i].stock_delay * delay_value;
    }

    pprint(matrix,num_period);


}


