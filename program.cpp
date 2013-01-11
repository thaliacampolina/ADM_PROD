#include <iostream>
#include <vector>
using namespace std;
#include "period.cc"


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
    int stock;
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
    cin >> stock;
    cout << "Digite o valor (custo) por unidade do _estoque_inicial_  (utilize ponto ao invés de vírgula): ";	
    cin >> stock_value;

    cout << "Digite 1 se houver possibilidade de ter _atrasos_, 0 caso contrario: ";	
    cin >> delay;
    cout << "Digite o valor (custo) por unidade dos _atrasos_  (utilize ponto ao invés de vírgula): ";	
    cin >> delay_value;



    //each period

    cout << endl << "Digite a quantidade da _demanda_ por período: " << endl << endl;	
    for (int i=1; i < num_period; i++ ) { 
        cout << "_Demanda_ no Período " << i <<" :";
        cin >> num_demand;
        demand_vector.push_back(num_demand);
    }
//********************** END: MENU*********************//




    Period matrix[num_period];
    pprint(matrix,num_period);


}
