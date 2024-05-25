#include <iostream>
#include <vector>
#include <string>
//# define razdelitel 1000000000

//# define razdelitel 1000000000
//# define kol_znak 9

/*
Строка которая передается в объект big_integer хранится в std::vecor<unsignet int>. В каждой ячейки вектора хранится чеиыре знака числа. 
Можно вводить очень большие числа. Перемножать их и складывать.
*/
# define razdelitel 10000
# define kol_znak 4

class big_integer
{
    //
public:

    big_integer(std::string str_vvod) : shislo_str{ str_vvod }
    {
        long vrem1;
        int k, l;
        long i = 0;
        while (shislo_str[i] == '0')
            i++;
        shislo_str.erase(0, i);
        i = shislo_str.size();
        if (i == 0)
        {
            shislo_str = "0";
            shislo_num.push_back(0);
        } // if (i == 0)
        else
        {
            while (i > 0)
            {
                k = 1;
                vrem1 = 0;
                while ((k < razdelitel) && (i > 0)) {
                    l = shislo_str[--i] - '0';
                    if ((l < 0) || (l > 9)) throw ("nevern vvod shisla");
                    vrem1 += (k * l);
                    k *= 10;
                }//  while ((k < 1000000000) && (i > 0))
                shislo_num.push_back(vrem1);

            }//   while (i > 0)
            while (shislo_num.back() == 0) shislo_num.pop_back();
            if (shislo_num.size() == 0) shislo_num.push_back(0);
        }// else if (i == 0)
    }

    big_integer()
    {

        shislo_num.push_back(0);
        shislo_str = "0";

    }


    void num_v_str()
    {
        //long vrem1;
        int k, i, j;
        unsigned int s;
        std::string str_vrem1 = "";
        //std::string str_vrem2 = "";
        k = shislo_num.size();
        shislo_str = "";
        for (i = 0; i < k; i++)
        {

            str_vrem1 = std::to_string(shislo_num[i]);
            if (i != (k - 1))
            {
                for (j = 0; j < (kol_znak - str_vrem1.size()); j++) str_vrem1 = "0" + str_vrem1;
            }
           // std::cout << str_vrem1 << std::endl;
            shislo_str = str_vrem1 + shislo_str;

        }//  for (i = 0; i < k; i++)

        /*

        for (j=0; j<k; j++)
        {
            s = shislo_num[j];
            str_vrem2 = "";
        for (i = 0; i < 9; i++)
        {
            str_vrem2 = std::to_string(s % 10 )+str_vrem2;
            s /= 10;

        }//  for (i = 0; i < 9; i++)
        std::cout << str_vrem2 << std::endl;
        //str_vrem1 = str_vrem2+str_vrem1;
        }//  for (j=0; j<k; j++)
        shislo_str = str_vrem1;


        */

    }
    void vivod()
    {
        std::cout << "Объект " << shislo_str << std::endl;
    }

    long kol_elem_str()
    {
        return shislo_str.size();
    }

    long kol_elem_num()
    {
        return shislo_num.size();
    }
    unsigned int elemen_num_i(long i)
    {
        return shislo_num[i];
    }
    std::vector<unsigned int> vivod_shisla()
    {
        return shislo_num;
    }

    std::string vivod_str()
    {
        return shislo_str;
    
    }

    void udal()
    {
        shislo_num.clear();
        shislo_str = "";
    
    }

    void move_shislo_num(std::vector <unsigned int>& other)
    {
        shislo_num = other;

    }

    big_integer ( big_integer & other)
    {
        shislo_num = other.vivod_shisla();
        shislo_str = other.vivod_str();
    }

    big_integer (big_integer&& other)
    {
        shislo_num = other.vivod_shisla();
        shislo_str = other.vivod_str();
        other.udal();
    }

    big_integer& operator=(big_integer & other )
    {
        if (this!=& other)
        { 
        shislo_num = other.vivod_shisla();
        shislo_str = other.vivod_str();
        }
        return *this;
    
    }

    big_integer& operator=(big_integer&& other)
    {
        if (this != &other)
        {
            shislo_num = other.vivod_shisla();
            shislo_str = other.vivod_str();
            other.udal();
        }
        return *this;

        

    }

   

    

    big_integer operator + (big_integer& other)
    {
        long k1, k2, k;
        long long vrem1{ 0 }, vrem2{ 0 };
        k1 = kol_elem_num();
        k2 = other.kol_elem_num();
        k = (k1 > k2) ? k1 : k2;
        big_integer VR;
        std::vector <unsigned int> vr_plus;
        for (long i = 0; i < k; i++)
        {
            if (i < k1) vrem1 += elemen_num_i(i);
            if (i < k2) vrem1 += other.elemen_num_i(i);
            vrem1 += vrem2;
            vr_plus.push_back(vrem1 % razdelitel);

            vrem2 = vrem1 / razdelitel;
            vrem1 = 0;

        }
        if (vrem2 != 0) vr_plus.push_back(vrem2);
        VR.move_shislo_num(vr_plus);
        VR.num_v_str();
        return VR;
    }

    big_integer operator * (big_integer& other)
    {

        //int r;
        long k1, k2, k, m, n;
        long long vrem1{ 0 };
        unsigned int vrem2{ 0 };
        k1 = kol_elem_num();
        k2 = other.kol_elem_num();
        k = k1 + k2;
        big_integer VR;
        std::vector <unsigned int> vr_mult;
        for (m = 0; m < k; m++) vr_mult.push_back(0);
        for (m = 0; m < k2; m++)
        {
            //vrem2 = 0;
            for (n = 0; n < k1; n++)
            {
                vrem1 = ((other.elemen_num_i(m) * elemen_num_i(n)) + vr_mult[m + n] + vrem2);
                vr_mult[m + n] = vrem1 % razdelitel;
                vrem2 = vrem1 / razdelitel;
                
            } // for (n = 0; n < k1; n++)
            // if (vrem2 != 0) vr_mult[m + k1] += vrem2;   //??????
            if (vrem2 != 0)
            {
                vr_mult[m + k1] = vrem2;
                vrem2 = 0;
            }
           /* r = 0;
            while (vrem2 != 0)
            {
                vr_mult[m + k1 + r++] = vrem2 % razdelitel;
                vrem2 /= razdelitel;
            }*/
        } // for (m = 0; m < k2; m++)
        while (vr_mult.back() == 0) vr_mult.pop_back();
        if (vr_mult.size() == 0) vr_mult.push_back(0);
        VR.move_shislo_num(vr_mult);
        VR.num_v_str();
        return VR;

    }


private:
    std::string shislo_str;
    std::vector <unsigned int> shislo_num;

};
std::ostream& operator << (std::ostream& os, big_integer& person)
{
    return os << person.vivod_str()<<std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    // std::cout << "Hello World!\n";
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099
    auto result2 = number1 * number2;
    std::cout << result2;


    auto number3 = big_integer("114577890656321456750097645332245655");
    auto number4 = big_integer("78524578596707877863423465768799908800808087665");
    auto result3 = number3 + number4;
    std::cout << result3; // 193099
    auto result4 = number3 * number4;
    std::cout << result4;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
