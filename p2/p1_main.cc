#include "bigint.h"


std::vector<std::vector<std::string>> tabla;
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

/**
 * @brief Busca valor de etiquta
 * 
 * @param etiqueta 
 * @return std::string 
 */
std::string Buscar(std::string etiqueta) {
    for (int i = 0; i < tabla.size(); i++) {
        if (tabla[i].size() != 3) continue;
        if (tabla[i][0] == etiqueta) return tabla[i][2];
    }
    return "";
}

/**
 * @brief Calculo
 * 
 * @param op1 
 * @param op2 
 * @param operando 
 * @param base 
 * @return std::string 
 */
std::string Calculo(std::string op1, std::string op2, std::string operando, int base) {
    // std::cout << "hace " << op1 << operando << op2 << "\n";
    std::string resultado = "";
    if (base == 2) {
        BigInt<2> bin1(op1);
        BigInt<2> bin2(op2);

        BigInt<2> res("");
        switch (operando[0]) {
            case '+':
                res = bin1 + bin2;
                break;
            case '-':
                res = bin1 - bin2;
                break;
            case '/':
                res = bin1 / bin2;
                break;
            case '*':
                res = bin1 * bin2;
                break;
            case '%':
                res = bin1 % bin2;
                break;

        }
        for (int i = 0; i < res.vbool().size(); i++) {
            resultado.push_back(res.vbool()[i]);
        }

    } else if (base == 8) {
        BigInt<8> operando1(op1);
        BigInt<8> operando2(op2);
        BigInt<2> bin1(operando1);
        BigInt<2> bin2(operando2);

        BigInt<2> res("");
        switch (operando[0]) {
            case '+':
                res = bin1 + bin2;
                break;
            case '-':
                res = bin1 - bin2;
                break;
            case '/':
                res = bin1 / bin2;
                break;
            case '*':
                res = bin1 * bin2;
                break;
            case '%':
                res = bin1 % bin2;
                break;

        }
        BigInt<8>res_op1 = res;
        for (int i = 0; i < res_op1.numero().size(); i++) {
            resultado.push_back(res_op1.numero()[i]);
        }
    }else if (base == 10) {
        BigInt<10> operando1(op1);
        BigInt<10> operando2(op2);
        BigInt<2> bin1(operando1);
        BigInt<2> bin2(operando2);

        BigInt<2> res("");
        switch (operando[0]) {
            case '+':
                res = bin1 + bin2;
                break;
            case '-':
                res = bin1 - bin2;
                break;
            case '/':
                res = bin1 / bin2;
                break;
            case '*':
                res = bin1 * bin2;
                break;
            case '%':
                res = bin1 % bin2;
                break;

        }
        BigInt<10>res_op1 = res;
        for (int i = 0; i < res_op1.numero().size(); i++) {
            resultado.push_back(res_op1.numero()[i]);
        }
        //std::cout << bin1 << " " << op2 << operando[0] << res<< "\n";
    }else if (base == 16) {
        BigInt<16> operando1(op1);
        BigInt<16> operando2(op2);
        BigInt<2> bin1(operando1);
        BigInt<2> bin2(operando2);

        BigInt<2> res("");
        switch (operando[0]) {
            case '+':
                res = bin1 + bin2;
                break;
            case '-':
                res = bin1 - bin2;
                break;
            case '/':
                res = bin1 / bin2;
                break;
            case '*':
                res = bin1 * bin2;
                break;
            case '%':
                res = bin1 % bin2;
                break;

        }
        BigInt<16>res_op1 = res;
        for (int i = 0; i < res_op1.numero().size(); i++) {
            resultado.push_back(res_op1.numero()[i]);
        }
    }else {
        std::cout << "base: "<< base << "no admitida\n";
        exit(EXIT_FAILURE);
    }

    return resultado;
}

/**
 * @brief Resuelve la tabla
 * 
 * @param base 
 */
void ResolverTabla(int base) {
    for (int i = 0 ; i  < tabla.size(); i++) {
        if (tabla[i].size() == 3) continue;
        // std::cout << "haciendo " << tabla[i][0] << "\n";
        std::vector<std::string> stack_vector = tabla[i];
        stack_vector.erase(stack_vector.begin());
        stack_vector.erase(stack_vector.begin());
        // reverse(stack_vector.begin(), stack_vector.end());
        //std::cout << stack.size();

        std::stack<std::string> stack;
        std::string resultado = "";
        for(int i = 0; i < stack_vector.size();i++) {
            std::string s = stack_vector[i];
            if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%") {    
                std::string op2 = stack.top();
                stack.pop();
                std::string op1 = stack.top();
                stack.pop();
                if (Buscar(op2) != "") op2 = Buscar(op2);
                if (Buscar(op1) != "") op1 = Buscar(op1);

                resultado = Calculo(op1, op2, s, base);
                stack.push(resultado);
            } else {
                stack.push(s);
            }
        }
        // std::cout << resultado << "\n";
        resultado = stack.top();
        std::vector<std::string> slot_nuevo;
        slot_nuevo.push_back(tabla[i][0]);
        slot_nuevo.push_back(tabla[i][1]);
        slot_nuevo.push_back(resultado);
        tabla[i] = slot_nuevo;
        // print ();
    }
}

int main(){

    std::ifstream file1("input.txt");
    std::ofstream file2("output.txt");

    std::string line; 

    std::getline(file1,line);
    int base = std::stoi(SeparaLineas(line)[2]);

    while (std::getline(file1,line)) {
        tabla.push_back(SeparaLineas(line));
    }

    ResolverTabla(base);



    for (int i = 0; i < tabla.size(); i++) {
        for (int j = 0 ; j < tabla[i].size();j++) {
            file2 << tabla[i][j] << " ";
        }
        file2 << "\n";
    }

    // BigInt<2> a("1010100110");

    // BigInt<8> b = a;
    // BigInt<10> C = a;

    // BigInt<16> a("98484");

    // BigInt<2> aa = a;
    BigInt<2> a("0111011011");
    size_t resul = a.sizeOFnumero();
    std::cout << resul << "\n";



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