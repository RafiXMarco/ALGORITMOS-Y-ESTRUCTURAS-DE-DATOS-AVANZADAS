#include "bigint.h"


struct Slot {
    std::string etiqueta;
    Number* numero;
    long unsigned int base_awee;
};

std::vector<std::vector<std::string>> tabla;

std::vector<Slot> tabla_final;

/**
 * @brief print tabla
 * 
 */
void print() {
    for (int i = 0; i < tabla.size(); i++) {
        for (int j = 0 ; j < tabla[i].size();j++) {
            std::cout << tabla[i][j] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * @brief separa lineas
 * 
 * @param line 
 * @return std::vector<std::string> 
 */
std::vector<std::string> SeparaLineas(std::string &line) {
    std::vector<std::string> vector;
    std::istringstream iss(line);
    std::string word; 
    while (iss >> word) {
        vector.push_back(word);
    }
    return vector;
}

Number* Buscar(std::string eti) {
    for (int i = 0; i < tabla_final.size();i++) {
        if (eti == tabla_final[i].etiqueta) {
            return tabla_final[i].numero;
        }
    }
    return nullptr;
}

long unsigned int Buscarbase(std::string eti) {
    for (int i = 0; i < tabla_final.size();i++) {
        if (eti == tabla_final[i].etiqueta) {
            return tabla_final[i].base_awee;
        }
    }
    return 0;
}
/**
 * @brief Resuelve la tabla
 * 
 * @param base 
 */
Number* ResolverStack(std::vector<std::string> stack_vector) {
    std::stack<Number*> stack;
    for (int i = 0 ; i  < stack_vector.size(); i++) {
        std::string s = stack_vector[i];
        if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%") {    
            Number* resultado;
            Number* op2 = stack.top();
            stack.pop();
            Number* op1 = stack.top();
            stack.pop();

            if (s == "+") resultado = op1->add(op2);
            if (s == "-") resultado = op1->subtract(op2);
            if (s == "*") resultado = op1->multiply(op2);
            if (s == "/") resultado = op1->divide(op2);
            if (s == "%") resultado = op1->module(op2);

            stack.push(resultado);
        } else {
            
            Number* num2 = Buscar(s);
            stack.push(num2);
        }
    }
    Number* result = stack.top();
    return result;
}

int main(){

    // PRUEBA
    // Number* num1 = Number::create(2, "000100110110");
    // std::cout << *num1 << "\n";
    // Number* num2 = Number::create(16, "AB64");
    // std::cout << *num2 << "\n";
    // Number* res = num2->add(num1);
    // std::cout << *res << "\n";

    std::ifstream file1("input.txt");
    std::ofstream file2("output.txt");

    std::string line; 
try {

    while (std::getline(file1,line)) {
        tabla.push_back(SeparaLineas(line));
    }
    for (int i = 0; i < tabla.size(); i++) {
        if (tabla[i][1] == "=") {
            Slot slot;
            slot.etiqueta = tabla[i][0];
            std::string s = tabla[i][2];
            s.erase(s.end()-1);

            long unsigned int base = std::stoi(tabla[i][2]);
            if (base != 2 && base != 8 && base != 10 && base != 16) throw BigIntBaseNotImplemented();
            std::string num1 = tabla[i][3];
            Number* num = Number::create(base, num1);
            slot.numero = num;
            
            slot.base_awee = base;
            tabla_final.push_back(slot);
        }
        if (tabla[i][1] == "?") {
            Slot slot;
            long unsigned int base = Buscarbase(tabla[i][2]);
            if (base != 2 && base != 8 && base != 10 && base != 16) throw BigIntBaseNotImplemented();
            slot.base_awee = base;
            slot.etiqueta = tabla[i][0];
            tabla[i].erase(tabla[i].begin());
            tabla[i].erase(tabla[i].begin());
            std::vector<std::string> stack_vector = tabla[i];
            Number* res = ResolverStack(stack_vector);

            slot.numero = res;
            tabla_final.push_back(slot);
        }
        
    }


    for (int i = 0 ; i < tabla_final.size(); i++) {
        file2 << tabla_final[i].etiqueta << " = " << tabla_final[i].base_awee << ", ";
        file2 << *tabla_final[i].numero;
    }

} catch (const std::exception& EX1) {
    std::cerr << EX1.what()<< "\n";
    return 1;
}
    // // BigInt<2> a("1010100110");

    // // BigInt<8> b = a;
    // // BigInt<10> C = a;

    // // BigInt<16> a("98484");

    // // BigInt<2> aa = a;
    // BigInt<2> a("0111011011");
    // size_t resul = a.sizeOFnumero();
    // std::cout << resul << "\n";



    // BigInt<2> b("00000000000110");
    // BigInt<2> c = ("");
    // c =pow(a,b);
    // std::cout << c;
    // BigInt<16> b = aa;
    // std::cout << "\n";
    // std::cout << b;



    // std::string a = "-457418";
    // std::string b = "2";
    //  std::string c = "-1000";
    //  std::string d = "-9000";
    //  size_t base = 10;
    // const size_t  base2 = 10;


    //   BigInt<10> aa("2");
    //  BigInt<10> bb("488793485263218");

    // // // BigInt<2> a = aa;
    //  BigInt<2> b = bb;
    //  BigInt<10> res("");
    //  res = bb / aa;
    //  BigInt<10> re = res;
    //  std::cout << res;


//     std::cout << a;
// std::string d ("01101111001000111000011010000011101100000101110010");
// for(int i = 0 ; i < d.length(); i++) std::cout << d[i] << "";
// std::cout << "\n";
//     std::cout << b;
// std::string f ("01011001111011001001011101101010011110111011111110");
// for(int i = 0 ; i < f.length(); i++) std::cout << f[i] << "";
// std::cout << "\n";



    // //  BigInt<base2> cc(c);
    // //  BigInt<base2> dd(d);

    // // while(true) {
    // //   std::cin >> aa;
    // //   std::cin >> bb;

    //     res = pow(aa,bb);
    //     std::cout << aa << " " << bb  << res<< "\n";
    // // }


    return 0;
}