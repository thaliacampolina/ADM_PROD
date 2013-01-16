#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#include "period.cc"
#include "element.cpp"


int main() {



//**********************MENU*********************//

    //global
    int num_period=0;;
    int num_normal_prod=0;;
    float normal_prod_value=0.0;
    int extra_shift=0;
    int extra_shift_number=0;
    float extra_shift_value=0.0;
    int subcontract=0;
    int subcontract_number=0;
    float subcontract_value=0.0;
    int initial_stock=0;
    float stock_value=0.0;
    int delay=0;
    float delay_value=0.0;

    //each period
    vector<int> demand_vector;
    int num_demand=0;


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
    if(delay){
        cout << "Digite o valor (custo) por unidade dos _atrasos_  (utilize ponto ao invés de vírgula): ";	
        cin >> delay_value;
    }



    //each period

    cout << endl << "Digite a quantidade da _demanda_ por período: " << endl << endl;	
    for (int i=1; i <= num_period; i++ ) { 
        cout << "_Demanda_ no Período " << i <<" :";
        cin >> num_demand;
        demand_vector.push_back(num_demand);
    }

//********************** CONTEXT *********************//

    //creating element vector
    Element element[3];

    //setting context: DELAY, EXTRA SHIFT AND SUBCONTRACTION
    element[0].setElement(DELAY,delay_value,delay,0);
    element[1].setElement(SUBCONTRACTION,subcontract_value,subcontract,subcontract_number);
    element[2].setElement(EXTRA,extra_shift_value,extra_shift,extra_shift_number);


    //sort
    sort(element, element+3, compare); 
    cout<<"elements"<<element[0].id<<" "<<element[1].id<<" "<<element[2].id<<endl;

    //creating period matrix
    Period matrix[num_period+1];
    matrix[0].stock_initial = initial_stock;

    // setting all demands
    for(int i =0; i< num_period; ++i){
        // demand
        matrix[i].demand = demand_vector[i];

        // normal prod
        matrix[i].prod_normal =  num_normal_prod;
    }


//********************** ITERATION*********************//

    // iteration : periods
    for(int i =0; i< num_period; ++i) {

        int demand = matrix[i].demand;
        int prod_normal = matrix[i].prod_normal;
        int stock_initial = matrix[i].stock_initial;

        // real demand
        // is only the demand on 1st period
        int real_demand = 0;
        if( i == 0){
            real_demand = demand;
        }
        // it is the demand + the delay stock, if it exist
        else{
            real_demand = demand + matrix[i-1].stock_delay;
        }

//******************PRODUCING THE DEMAND*************//
        // if the demand can be produced
        if( real_demand < (prod_normal + stock_initial)){
            int stock_final = (prod_normal + stock_initial) - real_demand;
            matrix[i].stock_final = stock_final;
            //calculates the initial stock for the next period
            matrix[i+1].stock_initial = stock_final;
        }

        // if the demand can not be produced
        else{
            // calculates the delayed number of product
            int delay_to_remove = real_demand - prod_normal - stock_initial;


            for(int j = 0; (j < 3) && (delay_to_remove!=0); j++){
                switch (element[j].id){
//TODO:DELAY -> ver se a flag ta ligada, se nao tiver passar o delay pros periodos anteriores
                
                //
                    case DELAY:{
                        matrix[i].stock_delay = delay_to_remove;
                        matrix[i+1].stock_initial = -delay_to_remove;
                        matrix[i].stock_final = -delay_to_remove;
                        delay_to_remove = 0;
                        break; }
                    case SUBCONTRACTION:{
                        int to_produce = min(delay_to_remove, subcontract_number);
                        matrix[i].sub_contraction = to_produce; 
                        delay_to_remove -= to_produce;
                        break;}
                    case EXTRA:{
                        int to_produce = min(delay_to_remove, extra_shift_number);
                        matrix[i].extra_shift = to_produce; 
                        delay_to_remove -= to_produce;
                    break;}
                    default:
                        cerr<<"erro seu lesado"<<endl;
                }
            }
        }

        //general info for each period

        // costs
        matrix[i].cost_normal = normal_prod_value * num_normal_prod;
        matrix[i].cost_extra_shift = matrix[i].extra_shift * extra_shift_value;
        matrix[i].cost_subcontraction =  matrix[i].sub_contraction * subcontract_value;
        matrix[i].cost_stock = matrix[i].stock_mean * stock_value;
        matrix[i].cost_delay = matrix[i].stock_delay * delay_value;
        

        //prod - demand
        matrix[i].prod_demand = prod_normal - real_demand;
        //stock mean
        matrix[i].stock_mean = ( stock_initial + matrix[i].stock_final) / 2.0;
    }

    //dump the table on screen
    pprint(matrix,num_period);


}


